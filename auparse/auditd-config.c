/* auditd-config.c -- 
 * Copyright 2007 Red Hat Inc., Durham, North Carolina.
 * All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Authors:
 *   Steve Grubb <sgrubb@redhat.com>
 * 
 */

#include "config.h"
#include "internal.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <libgen.h>
#include <dirent.h>
#include <ctype.h>

/* Local prototypes */
struct _pair
{
	const char *name;
	const char *value;
};

struct kw_pair 
{
	const char *name;
	int (*parser)(const char *, int, struct daemon_conf *);
};

struct nv_list
{ 
	const char *name;
	int option;
};

static char *get_line(FILE *f, char *buf);
static int nv_split(char *buf, struct _pair *nv);
static const struct kw_pair *kw_lookup(const char *val);
static int log_file_parser(const char *val, int line, 
		struct daemon_conf *config);
static int num_logs_parser(const char *val, int line, 
		struct daemon_conf *config);
static int log_format_parser(const char *val, int line, 
		struct daemon_conf *config);

static const struct kw_pair keywords[] = 
{
  {"log_file",                 log_file_parser },
  {"log_format",               log_format_parser },
  {"num_logs",                 num_logs_parser },
  { NULL,                      NULL }
};

static const struct nv_list log_formats[] =
{
  {"raw",  LF_RAW },
  {"nolog", LF_NOLOG },
  { NULL,  0 }
};


/*
 * Set everything to its default value
*/
static void clear_config(struct daemon_conf *config)
{
	config->qos = QOS_NON_BLOCKING;
	config->sender_uid = 0;
	config->sender_pid = 0;
	config->sender_ctx = NULL;
	config->log_file = strdup("/var/log/audit/audit.log");
	config->log_format = LF_RAW;
	config->log_group = 0;
	config->priority_boost = 3;
	config->flush =  FT_NONE;
	config->freq = 0;
	config->num_logs = 0L;
	config->dispatcher = NULL;
	config->node_name_format = N_NONE;
	config->node_name = NULL;
	config->max_log_size = 0L;
	config->max_log_size_action = SZ_IGNORE;
	config->space_left = 0L;
	config->space_left_action = FA_IGNORE;
	config->space_left_exe = NULL;
	config->action_mail_acct = strdup("root");
	config->admin_space_left= 0L;
	config->admin_space_left_action = FA_IGNORE;
	config->admin_space_left_exe = NULL;
	config->disk_full_action = FA_IGNORE;
	config->disk_full_exe = NULL;
	config->disk_error_action = FA_SYSLOG;
	config->disk_error_exe = NULL;
}

int load_config(struct daemon_conf *config, log_test_t lt)
{
	int fd, rc, lineno = 1;
	struct stat st;
	FILE *f;
	char buf[128];

	clear_config(config);
	lt = lt;

	/* open the file */
	rc = open(CONFIG_FILE, O_RDONLY|O_NOFOLLOW);
	if (rc < 0) {
		if (errno != ENOENT) {
			audit_msg(LOG_ERR, "Error opening config file (%s)", 
				strerror(errno));
			return 1;
		}
		audit_msg(LOG_WARNING,
			"Config file %s doesn't exist, skipping", CONFIG_FILE);
		return 0;
	}
	fd = rc;

	/* check the file's permissions: owned by root, not world writable,
	 * not symlink.
	 */
	if (fstat(fd, &st) < 0) {
		audit_msg(LOG_ERR, "Error fstat'ing config file (%s)", 
			strerror(errno));
		close(fd);
		return 1;
	}
	if (st.st_uid != 0) {
		audit_msg(LOG_ERR, "Error - %s isn't owned by root", 
			CONFIG_FILE);
		close(fd);
		return 1;
	}
	if (!S_ISREG(st.st_mode)) {
		audit_msg(LOG_ERR, "Error - %s is not a regular file", 
			CONFIG_FILE);
		close(fd);
		return 1;
	}

	/* it's ok, read line by line */
	f = fdopen(fd, "r");
	if (f == NULL) {
		audit_msg(LOG_ERR, "Error - fdopen failed (%s)", 
			strerror(errno));
		close(fd);
		return 1;
	}

	while (get_line(f, buf)) {
		// convert line into name-value pair
		const struct kw_pair *kw;
		struct _pair nv;
		rc = nv_split(buf, &nv);
		switch (rc) {
			case 0: // fine
				break;
			case 1: // not the right number of tokens.
				audit_msg(LOG_ERR, 
				"Wrong number of arguments for line %d in %s", 
					lineno, CONFIG_FILE);
				break;
			case 2: // no '=' sign
				audit_msg(LOG_ERR, 
					"Missing equal sign for line %d in %s", 
					lineno, CONFIG_FILE);
				break;
			default: // something else went wrong... 
				audit_msg(LOG_ERR, 
					"Unknown error for line %d in %s", 
					lineno, CONFIG_FILE);
				break;
		}
		if (nv.name == NULL) {
			lineno++;
			continue;
		}
		if (nv.value == NULL) {
			fclose(f);
			return 1;
		}

		/* identify keyword or error */
		kw = kw_lookup(nv.name);
		if (kw->name) {
			/* dispatch to keyword's local parser */
			rc = kw->parser(nv.value, lineno, config);
			if (rc != 0) {
				fclose(f);
				return 1; // local parser puts message out
			}
		}

		lineno++;
	}

	fclose(f);
	return 0;
}

static char *get_line(FILE *f, char *buf)
{
	if (fgets_unlocked(buf, 128, f)) {
		/* remove newline */
		char *ptr = strchr(buf, 0x0a);
		if (ptr)
			*ptr = 0;
		return buf;
	}
	return NULL;
}

static int nv_split(char *buf, struct _pair *nv)
{
	/* Get the name part */
	char *ptr;

	nv->name = NULL;
	nv->value = NULL;
	ptr = strtok(buf, " ");
	if (ptr == NULL)
		return 0; /* If there's nothing, go to next line */
	if (ptr[0] == '#')
		return 0; /* If there's a comment, go to next line */
	nv->name = ptr;

	/* Check for a '=' */
	ptr = strtok(NULL, " ");
	if (ptr == NULL)
		return 1;
	if (strcmp(ptr, "=") != 0)
		return 2;

	/* get the value */
	ptr = strtok(NULL, " ");
	if (ptr == NULL)
		return 1;
	nv->value = ptr;

	/* Make sure there's nothing else */
	ptr = strtok(NULL, " ");
	if (ptr)
		return 1;

	/* Everything is OK */
	return 0;
}

static const struct kw_pair *kw_lookup(const char *val)
{
	int i = 0;
	while (keywords[i].name != NULL) {
		if (strcasecmp(keywords[i].name, val) == 0)
			break;
		i++;
	}
	return &keywords[i];
}
 
static int log_file_parser(const char *val, int line,struct daemon_conf *config)
{
	char *dir = NULL, *tdir, *base;
	DIR *d;
	int fd, mode;
	struct stat buf;

	/* split name into dir and basename. */
	tdir = strdup(val);
	if (tdir)
		dir = dirname(tdir);
	if (dir == NULL || strlen(dir) < 4) { //  '/var' is shortest dirname
		audit_msg(LOG_ERR, 
			"The directory name: %s is too short - line %d", 
			dir, line);
		free((void *)tdir);
		return 1;
	}

	base = basename((char *)val);
	if (base == 0 || strlen(base) == 0) {
		audit_msg(LOG_ERR, "The file name: %s is too short - line %d", 
			base, line);
		free((void *)tdir);
		return 1;
	}
	
	/* verify the directory path exists */
	d = opendir(dir);
	if (d == NULL) {
		audit_msg(LOG_ERR, "Could not open dir %s (%s)", dir, 
			strerror(errno));
		free((void *)tdir);
		return 1;
	}
	free((void *)tdir);
	closedir(d);

	/* if the file exists, see that its regular, owned by root, 
	 * and not world anything */
	mode = O_RDONLY;

	fd = open(val, mode);
	if (fd < 0) {
		audit_msg(LOG_ERR, "Unable to open %s (%s)", val, 
					strerror(errno));
		return 1;
	}
	if (fstat(fd, &buf) < 0) {
		audit_msg(LOG_ERR, "Unable to stat %s (%s)", 
					val, strerror(errno));
		close(fd);
		return 1;
	}
	close(fd);
	if (!S_ISREG(buf.st_mode)) {
		audit_msg(LOG_ERR, "%s is not a regular file", val);
		return 1;
	}
	if (buf.st_uid != 0) {
		audit_msg(LOG_ERR, "%s is not owned by root", val);
		return 1;
	}
	if ( (buf.st_mode & (S_IXUSR|S_IWGRP|S_IXGRP|S_IRWXO)) ) {
		audit_msg(LOG_ERR, "%s permissions should be 0600 or 0640",
				val);
		return 1;
	}
	if ( !(buf.st_mode & S_IWUSR) ) {
		audit_msg(LOG_ERR, "audit log is not writable by owner");
		return 1;
	}

	free((void *)config->log_file);
	config->log_file = strdup(val);
	if (config->log_file == NULL)
		return 1;
	return 0;
}

static int num_logs_parser(const char *val, int line, 
		struct daemon_conf *config)
{
	const char *ptr = val;
	unsigned long i;

	/* check that all chars are numbers */
	for (i=0; ptr[i]; i++) {
		if (!isdigit(ptr[i])) {
			audit_msg(LOG_ERR, 
				"Value %s should only be numbers - line %d",
				val, line);
			return 1;
		}
	}

	/* convert to unsigned long */
	errno = 0;
	i = strtoul(val, NULL, 10);
	if (errno) {
		audit_msg(LOG_ERR, 
			"Error converting string to a number (%s) - line %d",
			strerror(errno), line);
		return 1;
	}
	if (i > 99) {
		audit_msg(LOG_ERR, "num_logs must be 99 or less");
		return 1;
	}
	config->num_logs = i;
	return 0;
}

static int log_format_parser(const char *val, int line, 
		struct daemon_conf *config)
{
	int i;

	for (i=0; log_formats[i].name != NULL; i++) {
		if (strcasecmp(val, log_formats[i].name) == 0) {
			config->log_format = log_formats[i].option;
			return 0;
		}
	}
	audit_msg(LOG_ERR, "Option %s not found - line %d", val, line);
	return 1;
}

void free_config(struct daemon_conf *config)
{
	free((void*)config->sender_ctx);
	free((void*)config->log_file);
	free((void*)config->dispatcher);
	free((void *)config->node_name);
	free((void *)config->action_mail_acct);
	free((void *)config->space_left_exe);
	free((void *)config->admin_space_left_exe);
	free((void *)config->disk_full_exe);
	free((void *)config->disk_error_exe);
}


/*
* ausearch-parse.c - Extract interesting fields and check for match
* Copyright (c) 2005-08, 2011 Red Hat Inc., Durham, North Carolina.
* All Rights Reserved. 
*
* This software may be freely redistributed and/or modified under the
* terms of the GNU General Public License as published by the Free
* Software Foundation; either version 2, or (at your option) any
* later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; see the file COPYING. If not, write to the
* Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*
* Authors:
*   Steve Grubb <sgrubb@redhat.com>
*/

#include "config.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
#include <limits.h>	/* PATH_MAX */
#include <ctype.h>
#include "libaudit.h"
#include "ausearch-options.h"
#include "ausearch-lookup.h"
#include "ausearch-parse.h"

#define NAME_OFFSET 36
static const char key_sep[2] = { AUDIT_KEY_SEPARATOR, 0 };

static int parse_syscall(lnode *n, search_items *s);
static int parse_dir(const lnode *n, search_items *s);
static int common_path_parser(search_items *s, char *path);
static int avc_parse_path(const lnode *n, search_items *s);
static int parse_path(const lnode *n, search_items *s);
static int parse_user(const lnode *n, search_items *s);
static int parse_obj(const lnode *n, search_items *s);
static int parse_login(const lnode *n, search_items *s);
static int parse_daemon1(const lnode *n, search_items *s);
static int parse_daemon2(const lnode *n, search_items *s);
static int parse_sockaddr(const lnode *n, search_items *s);
static int parse_avc(const lnode *n, search_items *s);
static int parse_integrity(const lnode *n, search_items *s);
static int parse_kernel_anom(const lnode *n, search_items *s);
static int parse_simple_message(const lnode *n, search_items *s);
static int parse_tty(const lnode *n, search_items *s);
static int parse_pkt(const lnode *n, search_items *s);


static int audit_avc_init(search_items *s)
{
	if (s->avc == NULL) {
		//create
		s->avc = malloc(sizeof(alist));
		if (s->avc == NULL)
			return -1;
		alist_create(s->avc);
	}
	return 0;
}

/*
 * This function will take the list and extract the searchable fields from it.
 * It returns 0 on success and 1 on failure.
 */
int extract_search_items(llist *l)
{
	int ret = 0;
	lnode *n;
	search_items *s = &l->s;
	list_first(l);
	n = list_get_cur(l);
	if (n) {
		do {
			switch (n->type) {
			case AUDIT_SYSCALL:
				ret = parse_syscall(n, s);
				break;
			case AUDIT_CWD:
				ret = parse_dir(n, s);
				break;
			case AUDIT_AVC_PATH:
				ret = avc_parse_path(n, s);
				break;
			case AUDIT_PATH:
				ret = parse_path(n, s);
				break;
			case AUDIT_USER:
			case AUDIT_FIRST_USER_MSG...AUDIT_LAST_USER_MSG:
			case AUDIT_FIRST_USER_MSG2...AUDIT_LAST_USER_MSG2:
				ret = parse_user(n, s);
				break;
			case AUDIT_SOCKADDR:
				ret = parse_sockaddr(n, s);
				break;
			case AUDIT_LOGIN:
				ret = parse_login(n, s);
				break;
			case AUDIT_OBJ_PID:
				ret = parse_obj(n, s);
				break;
			case AUDIT_DAEMON_START:
			case AUDIT_DAEMON_END:
			case AUDIT_DAEMON_ABORT:
			case AUDIT_DAEMON_CONFIG:
			case AUDIT_DAEMON_ROTATE:
			case AUDIT_DAEMON_RESUME:
				ret = parse_daemon1(n, s);
				break;
			case AUDIT_DAEMON_ACCEPT:
			case AUDIT_DAEMON_CLOSE:
				ret = parse_daemon2(n, s);
				break;
			case AUDIT_CONFIG_CHANGE:
				ret = parse_simple_message(n, s);
				break;
			case AUDIT_AVC:
				ret = parse_avc(n, s);
				break;
			case AUDIT_NETFILTER_PKT:
				ret = parse_pkt(n, s);
				break;
			case
			   AUDIT_FIRST_KERN_ANOM_MSG...AUDIT_LAST_KERN_ANOM_MSG:
				ret = parse_kernel_anom(n, s);
				break;
			case AUDIT_MAC_POLICY_LOAD...AUDIT_MAC_UNLBL_STCDEL:
				ret = parse_simple_message(n, s);
				break;
			case AUDIT_INTEGRITY_DATA...AUDIT_INTEGRITY_RULE:
				ret = parse_integrity(n, s);
				break;
			case AUDIT_KERNEL:
			case AUDIT_IPC:
			case AUDIT_SELINUX_ERR:
			case AUDIT_EXECVE:
			case AUDIT_BPRM_FCAPS:
			case AUDIT_NETFILTER_CFG:
				// Nothing to parse
				break;
			case AUDIT_TTY:
				ret = parse_tty(n, s);
				break;
			default:
				// printf("unparsed type:%d\n", n->type);
				break;
			}
			// if (ret) printf("type:%d ret:%d\n", n->type, ret);
		} while ((n=list_next(l)) && ret==0);
	}
	return ret;
}

static int parse_syscall(lnode *n, search_items *s)
{
	char *ptr, *str, *term;

	term = n->message;
	if (report_format > RPT_DEFAULT) {
		// get arch
		str = strstr(term, "arch=");
		if (str == NULL) 
			return 1;
		ptr = str + 5;
		term = strchr(ptr, ' ');
		if (term == NULL) 
			return 2;
		*term = 0;
		errno = 0;
		s->arch = (int)strtoul(ptr, NULL, 16);
		if (errno) 
			return 3;
		*term = ' ';
	} 
	// get syscall
	str = strstr(term, "syscall=");
	if (str == NULL)
		return 4;
	ptr = str + 8;
	term = strchr(ptr, ' ');
	if (term == NULL)
		return 5;
	*term = 0;
	errno = 0;
	s->syscall = (int)strtoul(ptr, NULL, 10);
	if (errno)
		return 6;
	*term = ' ';
	// get success
	if (event_success != S_UNSET) {
		str = strstr(term, "success=");
		if (str) { // exit_group does not set success !?!
			ptr = str + 8;
			term = strchr(ptr, ' ');
			if (term == NULL)
				return 7;
			*term = 0;
			if (strcmp(ptr, "yes") == 0)
				s->success = S_SUCCESS;
			else
				s->success = S_FAILED;
			*term = ' ';
		}
	}
	// get exit
	if (event_exit_is_set) {
		str = strstr(term, "exit=");
		if (str == NULL)
			return 8;
		ptr = str + 5;
		term = strchr(ptr, ' ');
		if (term == NULL)
			return 9;
		*term = 0;
		errno = 0;
		s->exit = strtoul(ptr, NULL, 0);
		if (errno)
			return 10;
		s->exit_is_set = 1;
		*term = ' ';
	}
	// get a0
	str = strstr(term, "a0=");
	if (str == NULL)
		return 11;
	ptr = str + 3;
	term = strchr(ptr, ' ');
	if (term == NULL)
		return 12;
	*term = 0;
	errno = 0;
	// 64 bit dump on 32 bit machine looks bad here - need long long
	n->a0 = strtoull(ptr, NULL, 16); // Hex
	if (errno)
		return 13;
	*term = ' ';
	// ppid
	if (event_ppid != -1) {
		str = strstr(term, "ppid=");
		if (str != NULL) { // ppid is an optional field
			ptr = str + 5;
			term = strchr(ptr, ' ');
			if (term == NULL)
				return 14;
			*term = 0;
			errno = 0;
			s->ppid = strtoul(ptr, NULL, 10);
			if (errno)
				return 15;
			*term = ' ';
		}
	}
	// pid
	if (event_pid != -1) {
		str = strstr(term, " pid=");
		if (str == NULL)
			return 16;
		ptr = str + 5;
		term = strchr(ptr, ' ');
		if (term == NULL)
			return 17;
		*term = 0;
		errno = 0;
		s->pid = strtoul(ptr, NULL, 10);
		if (errno)
			return 18;
		*term = ' ';
	}
	// loginuid
	str = strstr(term, "auid=");
	if (str == NULL) {
		str = strstr(term, "loginuid=");
		if (str == NULL)
			return 19;
		ptr = str + 9;
	} else
		ptr = str + 5;
	term = strchr(ptr, ' ');
	if (term == NULL)
		return 20;
	*term = 0;
	errno = 0;
	s->loginuid = strtoul(ptr, NULL, 10);
	if (errno)
		return 21;
	// uid
	*term = ' ';
	str = strstr(term, "uid=");
	if (str == NULL)
		return 22;
	ptr = str + 4;
	term = strchr(ptr, ' ');
	if (term == NULL)
		return 23;
	*term = 0;
	errno = 0;
	s->uid = strtoul(ptr, NULL, 10);
	if (errno)
		return 24;
	// gid
	*term = ' ';
	str = strstr(term, "gid=");
	if (str == NULL)
		return 25;
	ptr = str + 4;
	term = strchr(ptr, ' ');
	if (term == NULL)
		return 26;
	*term = 0;
	errno = 0;
	s->gid = strtoul(ptr, NULL, 10);
	if (errno)
		return 27;
	// euid
	*term = ' ';
	str = strstr(term, "euid=");
	if (str == NULL)
		return 28;
	ptr = str + 5;
	term = strchr(ptr, ' ');
	if (term == NULL)
		return 29;
	*term = 0;
	errno = 0;
	s->euid = strtoul(ptr, NULL, 10);
	if (errno)
		return 30;
	// egid
	*term = ' ';
	str = strstr(term, "egid=");
	if (str == NULL)
		return 31;
	ptr = str + 5;
	term = strchr(ptr, ' ');
	if (term == NULL)
		return 32;
	*term = 0;
	errno = 0;
	s->egid = strtoul(ptr, NULL, 10);
	if (errno)
		return 33;
	*term = ' ';

	if (event_terminal) {
		// dont do this search unless needed
		str = strstr(term, "tty=");
		if (str) {
			str += 4;
			term = strchr(str, ' ');
			if (term == NULL)
				return 34;
			*term = 0;
			s->terminal = strdup(str);
			*term = ' ';
		}
	}
	// ses
	if (event_session_id != -2 ) {
		str = strstr(term, "ses=");
		if (str) {
			ptr = str + 4;
			term = strchr(ptr, ' ');
			if (term == NULL)
				return 35;
			*term = 0;
			errno = 0;
			s->session_id = strtoul(ptr, NULL, 10);
			if (errno)
				return 36;
			*term = ' ';
		}
	}
	if (event_comm) {
		// dont do this search unless needed
		str = strstr(term, "comm=");
		if (str) {
			/* Make the syscall one override */
			if (s->comm)
				free(s->comm);
			str += 5;
			if (*str == '"') {
				str++;
				term = strchr(str, '"');
				if (term == NULL)
					return 37;
				*term = 0;
				s->comm = strdup(str);
				*term = '"';
			} else 
				s->comm = unescape(str);
		} else
			return 38;
	}
	if (event_exe) {
		// dont do this search unless needed
		str = strstr(n->message, "exe=");
		if (str) {
			str += 4;
			if (*str == '"') {
				str++;
				term = strchr(str, '"');
				if (term == NULL)
					return 39;
				*term = 0;
				s->exe = strdup(str);
				*term = '"';
			} else 
				s->exe = unescape(str);
		} else
			return 40;
	}
	if (event_subject) {
		// scontext
		str = strstr(term, "subj=");
		if (str != NULL) {
			str += 5;
			term = strchr(str, ' ');
			if (term == NULL)
				return 41;
			*term = 0;
			if (audit_avc_init(s) == 0) {
				anode an;

				anode_init(&an);
				an.scontext = strdup(str);
				alist_append(s->avc, &an);
				*term = ' ';
			} else
				return 42;
		}
	}
	if (event_key) {
		str = strstr(term, "key=");
		if (str) {
			if (!s->key) {
				//create
				s->key = malloc(sizeof(slist));
				if (s->key == NULL)
					return 43;
				slist_create(s->key);
			}
			str += 4;
			if (*str == '"') {
				str++;
				term = strchr(str, '"');
				if (term == NULL)
					return 44;
				*term = 0;
				if (s->key) {
					// append
					snode sn;
					sn.str = strdup(str);
					sn.key = NULL;
					sn.hits = 1;
					slist_append(s->key, &sn);
				}
				*term = '"';
			} else { 
				if (s->key) {
					char *saved=NULL;
					char *keyptr = unescape(str);
					char *kptr = strtok_r(keyptr,
							key_sep, &saved);
					while (kptr) {
						snode sn;
						// append
						sn.str = strdup(kptr);
						sn.key = NULL;
						sn.hits = 1;
						slist_append(s->key, &sn);
						kptr = strtok_r(NULL,
							key_sep, &saved);
					}
					free(keyptr);

				}
			}
		}
	}
	return 0;
}

static int parse_dir(const lnode *n, search_items *s)
{
	char *str, *term;

	if (event_filename) {
	// dont do this search unless needed
		str = strstr(n->message+NAME_OFFSET, " cwd=");
		if (str) {
			str += 5;
			if (*str == '"') {
				/* string is normal */
				str++;
				term = strchr(str, '"');
				if (term == NULL)
					return 1;
				*term = 0;
				if (!s->cwd) 
					s->cwd = strdup(str);
				*term = '"';
			} else if (!s->cwd) 
				s->cwd = unescape(str);
		}
	}
	return 0;
}

static int common_path_parser(search_items *s, char *path)
{
	char *term;

	if (!s->filename) {
		//create
		s->filename = malloc(sizeof(slist));
		if (s->filename == NULL)
			return 1;
		slist_create(s->filename);
	}
	if (*path == '"') {
		/* string is normal */
		path++;
		term = strchr(path, '"');
		if (term == NULL)
			return 2;
		*term = 0;
		if (s->filename) {
			// append
			snode sn;
			sn.str = strdup(path);
			sn.key = NULL;
			sn.hits = 1;
			// Attempt to rebuild path if relative
			if ((sn.str[0] == '.') && ((sn.str[1] == '.') ||
				(sn.str[1] == '/')) && s->cwd) {
				char *tmp = malloc(PATH_MAX);
				if (tmp == NULL)
					return 3;
				snprintf(tmp, PATH_MAX,
					"%s/%s", s->cwd, sn.str);
				free(sn.str);
				sn.str = tmp;
			}
			slist_append(s->filename, &sn);
		}
		*term = '"';
	} else { 
		if (s->filename) {
			// append
			snode sn;
			sn.key = NULL;
			sn.hits = 1;
			if (strcmp(path, "(null)")) {
				sn.str = strdup(path);
				goto append;
			}
			if (!isxdigit(path[0]))
				return 4;
			if (path[0] == '0' && path[1] == '0')
				sn.str = unescape(&path[2]); // Abstract name
			else
				sn.str = unescape(path);
			// Attempt to rebuild path if relative
			if ((sn.str[0] == '.') && ((sn.str[1] == '.') ||
				(sn.str[1] == '/')) && s->cwd) {
				char *tmp = malloc(PATH_MAX);
				if (tmp == NULL)
					return 5;
				snprintf(tmp, PATH_MAX, "%s/%s", 
					s->cwd, sn.str);
				free(sn.str);
				sn.str = tmp;
			}
append:
			slist_append(s->filename, &sn);
		}
	}
	return 0;
}

/* Older AVCs have path separate from the AVC record */
static int avc_parse_path(const lnode *n, search_items *s)
{
	char *str;

	if (event_filename) {
		// dont do this search unless needed
		str = strstr(n->message, " path=");
		if (str) {
			str += 6;
			return common_path_parser(s, str);
		}
		return 1;
	}
	return 0;
}

static int parse_path(const lnode *n, search_items *s)
{
	// We add 32 to message because we do not nee to look at
	// anything before that. Its only time and type.
	char *str, *term = n->message+NAME_OFFSET;

	if (event_filename) {
		// dont do this search unless needed
		str = strstr(term, " name=");
		if (str) {
			int rc;
			str += 6;
			rc = common_path_parser(s, str);
			if (rc)
				return rc;
		}
	}
	if (event_object) {
		// tcontext
		str = strstr(term, "obj=");
		if (str != NULL) {
			str += 4;
			term = strchr(str, ' ');
			if (term)
				*term = 0;
			if (audit_avc_init(s) == 0) {
				anode an;

				anode_init(&an);
				an.tcontext = strdup(str);
				alist_append(s->avc, &an);
				if (term)
					*term = ' ';
			} else
				return 7;
		}
	}
	return 0;
}

static int parse_obj(const lnode *n, search_items *s)
{
	char *str, *term;

	term = n->message;
	if (event_object) {
		// obj context
		str = strstr(term, "obj=");
		if (str != NULL) {
			str += 4;
			term = strchr(str, ' ');
			if (term)
				*term = 0;
			if (audit_avc_init(s) == 0) {
				anode an;

				anode_init(&an);
				an.tcontext = strdup(str);
				alist_append(s->avc, &an);
				if (term)
					*term = ' ';
			} else
				return 1;
		}
	}
	return 0;
}

static int parse_user(const lnode *n, search_items *s)
{
	char *ptr, *str, *term, saved, *mptr;

	term = n->message;

	// get pid
	if (event_pid != -1) {
		str = strstr(term, "pid=");
		if (str == NULL)
			return 1;
		ptr = str + 4;
		term = strchr(ptr, ' ');
		if (term == NULL)
			return 2;
		*term = 0;
		errno = 0;
		s->pid = strtoul(ptr, NULL, 10);
		if (errno)
			return 3;
		*term = ' ';
	}
	// get uid
	str = strstr(term, "uid=");
	if (str == NULL)
		return 4;
	ptr = str + 4;
	term = strchr(ptr, ' ');
	if (term == NULL)
		return 5;
	*term = 0;
	errno = 0;
	s->uid = strtoul(ptr, NULL, 10);
	if (errno)
		return 6;
	*term = ' ';
	// get loginuid
	*term = ' ';
	str = strstr(term, "auid=");
	if (str == NULL) { // Try the older one
		str = strstr(term, "loginuid=");
		if (str == NULL) 
			return 7;
		ptr = str + 9;
	} else
		ptr = str + 5;
	term = strchr(ptr, ' ');
	if (term == NULL)
		return 8;
	*term = 0;
	errno = 0;
	s->loginuid = strtoul(ptr, NULL, 10);
	if (errno)
		return 9;
	*term = ' ';
	// ses
	if (event_session_id != -2 ) {
		str = strstr(term, "ses=");
		if (str) {
			ptr = str + 4;
			term = strchr(ptr, ' ');
			if (term == NULL)
				return 10;
			*term = 0;
			errno = 0;
			s->session_id = strtoul(ptr, NULL, 10);
			if (errno)
				return 11;
			*term = ' ';
		}
	}
	if (event_subject) {
		// scontext
		str = strstr(term, "subj=");
		if (str != NULL) {
			str += 5;
			term = strchr(str, ' ');
			if (term == NULL)
				return 12;
			*term = 0;
			if (audit_avc_init(s) == 0) {
				anode an;

				anode_init(&an);
				an.scontext = strdup(str);
				alist_append(s->avc, &an);
				*term = ' ';
			} else
				return 13;
		}
	}
	// get uid - something has uid after auid ??
	str = strstr(term, "uid=");
	if (str != NULL) {
		ptr = str + 4;
		term = ptr;
		while (isdigit(*term))
			term++;
		if (term == ptr)
			return 14;

		saved = *term;
		*term = 0;
		errno = 0;
		s->uid = strtoul(ptr, NULL, 10);
		if (errno)
			return 15;
		*term = saved;
	}
	mptr = term + 1;

	if (event_comm) {
		// dont do this search unless needed
		str = strstr(mptr, "comm=");
		if (str) {
			str += 5;
			if (*str == '"') {
				str++;
				term = strchr(str, '"');
				if (term == NULL)
					return 16;
				*term = 0;
				s->comm = strdup(str);
				*term = '"';
			} else 
				s->comm = unescape(str);
		}
	}

	// Get acct for user/group add/del
	str = strstr(mptr, "acct=");
	if (str != NULL) {
		ptr = str + 5;
		term = ptr + 1;
		if (*ptr == '"') {
			while (*term != '"')
				term++;
			saved = *term;
			*term = 0;
			ptr++;
			s->acct = strdup(ptr);
			*term = saved;
		} else { 
			/* Handle legacy accts */
			char *end = ptr;
			int legacy = 0;

			while (*end != ' ') {
				if (!isxdigit(*end))
					legacy = 1;
				end++;
			}
			term = end;
			if (!legacy)
				s->acct = unescape(ptr);
			else {
				saved = *term;
				*term = 0;
				s->acct = strdup(ptr);
				*term = saved;
			}
		}
	}
	mptr = term + 1;

	// get hostname
	if (event_hostname) {
		// dont do this search unless needed
		str = strstr(mptr, "hostname=");
		if (str) {
			str += 9;
			term = strchr(str, ',');
			if (term == NULL) {
				term = strchr(str, ' ');
				if (term == NULL)
					return 17;
			}
			saved = *term;
			*term = 0;
			s->hostname = strdup(str);
			*term = saved;

			// Lets see if there is something more
			// meaningful in addr
			if (strcmp(s->hostname, "?") == 0) {
				term++;
				str = strstr(term, "addr=");
				if (str) {
					str += 5;
					term = strchr(str, ',');
					if (term == NULL) {
						term = strchr(str, ' ');
						if (term == NULL)
							return 18;
					}
					saved = *term;
					*term = 0;
					free(s->hostname);
					s->hostname = strdup(str);
					*term = saved;
				}
			}
		}
	}
	if (event_terminal) {
		// dont do this search unless needed
		str = strstr(mptr, "terminal=");
		if (str) {
			str += 9;
			term = strchr(str, ' ');
			if (term == NULL) {
				term = strchr(str, ')');
				if (term == NULL)
					return 19;
			}
			*term = 0;
			s->terminal = strdup(str);
			*term = ' ';
		}
	}
	if (event_exe) {
	// dont do this search unless needed
		str = strstr(mptr, "exe=");
		if (str) {
			str += 4;
			if (*str == '"') {
				str++;
				term = strchr(str, '"');
				if (term == NULL)
					return 20;
				*term = 0;
				s->exe = strdup(str);
				*term = '"';
			} else {
				char *end = str;
				int legacy = 0;

				while (*end != ' ') {
					if (!isxdigit(*end)) {
						legacy = 1;
					}
					end++;
				}
				term = end;
				if (!legacy)
					s->exe = unescape(str);
				else {
					saved = *term;
					*term = 0;
					s->exe = strdup(str);
					*term = saved;
				}
			}
		}
	}
	
	// get success
	if (event_success != S_UNSET) {
		str = strstr(mptr, "res=");
		if (str) {
			ptr = str + 4;
			term = strchr(ptr, '\'');
			if (term == NULL)
				return 21;
			*term = 0;
			if (strncmp(ptr, "failed", 6) == 0)
				s->success = S_FAILED;
			else
				s->success = S_SUCCESS;
			*term = '\'';
		} else if ((str = strstr(mptr, "result="))) {
			ptr = str + 7;
			term = strchr(ptr, ')');
			if (term == NULL)
				return 22;
			*term = 0;
			if (strcasecmp(ptr, "success") == 0)
				s->success = S_SUCCESS;
			else
				s->success = S_FAILED;
			*term = ')';
		}
	}
	return 0;
}

static int parse_login(const lnode *n, search_items *s)
{
	char *ptr, *str, *term = n->message;

	// get pid
	if (event_pid != -1) {
		str = strstr(term, "pid=");
		if (str == NULL)
			return 1;
		ptr = str + 4;
		term = strchr(ptr, ' ');
		if (term == NULL)
			return 2;
		*term = 0;
		errno = 0;
		s->pid = strtoul(ptr, NULL, 10);
		if (errno)
			return 3;
		*term = ' ';
	}
	// get uid
	str = strstr(term, "uid=");
	if (str == NULL)
		return 4;
	ptr = str + 4;
	term = strchr(ptr, ' ');
	if (term == NULL)
		return 5;
	*term = 0;
	errno = 0;
	s->uid = strtoul(ptr, NULL, 10);
	if (errno)
		return 6;
	// get loginuid
	*term = ' ';
	str = strstr(term, "new auid=");
	if (str == NULL) {
		str = strstr(term, "new loginuid=");
		if (str == NULL)
			return 7;
		ptr = str + 13;
	} else
		ptr = str + 9;
	term = strchr(ptr, ' ');
	if (term)
		*term = 0;
	errno = 0;
	s->loginuid = strtoul(ptr, NULL, 10);
	if (errno)
		return 8;
	if (term)
		*term = ' ';

	// success
	if (event_success != S_UNSET) {
		str = strstr(ptr, "res=");
		if (str != NULL) {
			ptr = str + 4;
			term = strchr(ptr, ' ');
			if (term)
				*term = 0;
			errno = 0;
			s->success = strtoul(ptr, NULL, 10);
			if (errno)
				return 9;
			if (term)
				*term = ' ';
		} else	// Assume older kernel where always successful
			s->success = S_SUCCESS; 
	}
	// ses
	if (event_session_id != -2 ) {
		if (term == NULL)
			term = n->message;
		str = strstr(term, "new ses=");
		if (str) {
			ptr = str + 8;
			term = strchr(ptr, ' ');
			if (term)
				*term = 0;
			errno = 0;
			s->session_id = strtoul(ptr, NULL, 10);
			if (errno)
				return 11;
			if (term)
				*term = ' ';
		}
	}
	return 0;
}

static int parse_daemon1(const lnode *n, search_items *s)
{
	char *ptr, *str, *term, saved, *mptr;

	// Not all messages have a ')', use it if its there
	mptr = strchr(n->message, ')');
	if (mptr == NULL)
		mptr = n->message;

	// auid
	str = strstr(mptr, "auid=");
	if (str == NULL)
		return 1;
	ptr = str + 5;
	term = strchr(ptr, ' ');
	if (term == NULL)
		return 2;
	saved = *term;
	*term = 0;
	errno = 0;
	s->loginuid = strtoul(ptr, NULL, 10);
	if (errno)
		return 3;
	*term = saved;

	// pid
	if (event_pid != -1) {
		str = strstr(term, "pid=");
		if (str == NULL)
			return 4;
		ptr = str + 4;
		term = strchr(ptr, ' ');
		if (term == NULL) 
			return 5;
		saved = *term;
		*term = 0;
		errno = 0;
		s->pid = strtoul(ptr, NULL, 10);
		if (errno)
			return 6;
		*term = saved;
	}

	if (event_subject) {
		// scontext
		str = strstr(term, "subj=");
		if (str != NULL) {
			str += 5;
			term = strchr(str, ' ');
			if (term == NULL)
				return 7;
			*term = 0;
			if (audit_avc_init(s) == 0) {
				anode an;

				anode_init(&an);
				an.scontext = strdup(str);
				alist_append(s->avc, &an);
				*term = ' ';
			} else
				return 8;
		}
	}

	// success
	if (event_success != S_UNSET) {
		str = strstr(mptr, "res=");
		if (str) {
			ptr = term = str + 4;
			while (isalpha(*term))
				term++;
			if (term == ptr)
				return 9;
			saved = *term;
			*term = 0;
			if (strncmp(ptr, "failed", 6) == 0)
				s->success = S_FAILED;
			else
				s->success = S_SUCCESS;
			*term = saved;
		}
	}

	return 0;
}

static int parse_daemon2(const lnode *n, search_items *s)
{
	char *str, saved, *term = n->message;

	if (event_hostname) {
		str = strstr(term, "addr=");
		if (str) {
			str += 5;
			term = strchr(str, ':');
			if (term == NULL) {
				term = strchr(str, ' ');
				if (term == NULL)
					return 1;
			}
			saved = *term;
			*term = 0;
			free(s->hostname);
			s->hostname = strdup(str);
			*term = saved;
		} else
			term = n->message; 
	}

	if (event_success != S_UNSET) {
		char *str = strstr(term, "res=");
		if (str) {
			char *ptr, *term, saved;

			ptr = term = str + 4;
			while (isalpha(*term))
				term++;
			if (term == ptr)
				return 2;
			saved = *term;
			*term = 0;
			if (strncmp(ptr, "failed", 6) == 0)
				s->success = S_FAILED;
			else
				s->success = S_SUCCESS;
			*term = saved;
		}
	}

	return 0;
}

static int parse_sockaddr(const lnode *n, search_items *s)
{
	char *str;

	if (event_hostname || event_filename) {
		str = strstr(n->message, "saddr=");
		if (str) {
			int len;
			struct sockaddr *saddr;
			char name[NI_MAXHOST];

			str += 6;
			len = strlen(str)/2;
			s->hostname = unescape(str);
			saddr = (struct sockaddr *)s->hostname;
			if (saddr->sa_family == AF_INET) {
				if (len < sizeof(struct sockaddr_in)) {
					fprintf(stderr,
						"sockaddr len too short\n");
					return 1;
				}
				len = sizeof(struct sockaddr_in);
			} else if (saddr->sa_family == AF_INET6) {
				if (len < sizeof(struct sockaddr_in6)) {
					fprintf(stderr,
						"sockaddr6 len too short\n");
					return 2;
				}
				len = sizeof(struct sockaddr_in6);
			} else if (saddr->sa_family == AF_UNIX) {
				struct sockaddr_un *un =
					(struct sockaddr_un *)saddr;
				if (un->sun_path[0])
					len = strlen(un->sun_path);
				else // abstract name
					len = strlen(&un->sun_path[1]);
				if (len == 0) {
					fprintf(stderr,
						"sun_path len too short\n");
					return 3;
				}
				if (event_filename) {
					if (!s->filename) {
						//create
						s->filename =
							malloc(sizeof(slist));
						if (s->filename == NULL)
							return 4;
						slist_create(s->filename);
					}
					if (s->filename) {
						// append
						snode sn;
						sn.str = strdup(un->sun_path);
						sn.key = NULL;
						sn.hits = 1;
						slist_append(s->filename, &sn);
					}
					free(s->hostname);
					s->hostname = NULL;
					return 0;
				} else { // No file name - no need for socket
					free(s->hostname);
					s->hostname = NULL;
					return 0;
				}
			} else {
				// addr family we don't care about
				free(s->hostname);
				s->hostname = NULL;
				return 0;
			}
			if (!event_hostname) {
				// we entered here for files - discard
				free(s->hostname);
				s->hostname = NULL;
				return 0;
			}
			if (getnameinfo(saddr, len, name, NI_MAXHOST, 
					NULL, 0, NI_NUMERICHOST) ) {
				free(s->hostname);
				s->hostname = NULL;
			} else {
				free(s->hostname);
				s->hostname = strdup(name);
			}
		}
	}
	return 0;
}

static int parse_integrity(const lnode *n, search_items *s)
{
	char *ptr, *str, *term;

	term = n->message;
	// get pid
	str = strstr(term, "pid=");
	if (str) {
		ptr = str + 4;
		term = strchr(ptr, ' ');
		if (term == NULL)
			return 1;
		*term = 0;
		errno = 0;
		s->pid = strtoul(ptr, NULL, 10);
		if (errno)
			return 2;
		*term = ' ';
	}

	// get uid
	str = strstr(term, " uid=");
	if (str) {
		ptr = str + 4;
		term = strchr(ptr, ' ');
		if (term == NULL)
			return 3;
		*term = 0;
		errno = 0;
		s->uid = strtoul(ptr, NULL, 10);
		if (errno)
			return 4;
		*term = ' ';
	}

	// get loginuid
	str = strstr(n->message, "auid=");
	if (str) {
		ptr = str + 5;
		term = strchr(ptr, ' ');
		if (term == NULL)
			return 5;
		*term = 0;
		errno = 0;
		s->loginuid = strtoul(ptr, NULL, 10);
		if (errno)
			return 6;
		*term = ' ';
	}

	str = strstr(term, "comm=");
	if (str) {
		str += 5;
		if (*str == '"') {
			str++;
			term = strchr(str, '"');
			if (term == NULL)
				return 7;
			*term = 0;
			s->comm = strdup(str);
			*term = '"';
		} else
			s->comm = unescape(str);
	}

	str = strstr(term, " name=");
	if (str) {
		str += 6;
		if (common_path_parser(s, str))
			return 8;
	}

	// and results (usually last)
	str = strstr(term, "res=");
	if (str != NULL) {
		ptr = str + 4;
		term = strchr(ptr, ' ');
		if (term)
			*term = 0;
		errno = 0;
		s->success = strtoul(ptr, NULL, 10);
		if (errno)
			return 9;
		if (term)
			*term = ' ';
	}

	return 0;
}


/* FIXME: If they are in permissive mode or hit an auditallow, there can 
 * be more that 1 avc in the same syscall. For now, we pickup just the first.
 */
static int parse_avc(const lnode *n, search_items *s)
{
	char *str, *term;
	anode an;
	int rc=0;

	term = n->message;
	anode_init(&an);

	// get the avc message info.
	str = strstr(term, "avc: ");
	if (str) {
		str += 5;
		term = strchr(str, '{');
		if (term == NULL)
			return 1;
		if (event_success != S_UNSET) {
			*term = 0;
			// FIXME. Do not override syscall success if already
			// set. Syscall pass/fail is the authoritative value.
			if (strstr(str, "denied")) {
				s->success = S_FAILED; 
				an.avc_result = AVC_DENIED;
			} else {
				s->success = S_SUCCESS;
				an.avc_result = AVC_GRANTED;
			}
			*term = '{';
		}

		// Now get permission
		str = term + 1;
		while (*str == ' ')
			str++;
		term = strchr(str, '}');
		if (term == NULL)
			return 2;
		while (*(term-1) == ' ')
			term--;
		*term = 0;
		an.avc_perm = strdup(str);
		*term = ' ';
	}

	// get pid
	if (event_pid != -1) {
		str = strstr(term, "pid=");
		if (str) {
			str = str + 4;
			term = strchr(str, ' ');
			if (term == NULL)
				return 3;
			*term = 0;
			errno = 0;
			s->pid = strtoul(str, NULL, 10);
			if (errno)
				return 4;
			*term = ' ';
		}
	}

	if (event_comm && s->comm == NULL) {
	// dont do this search unless needed
		str = strstr(term, "comm=");
		if (str == NULL) {
			rc = 5;
			goto err;
		}
		str += 5;
		if (*str == '"') {
			str++;
			term = strchr(str, '"');
			if (term == NULL) {
				rc = 6;
				goto err;
			}
			*term = 0;
			s->comm = strdup(str);
			*term = '"';
		} else { 
			s->comm = unescape(str);
			term = str + 6;
		}
	}
	if (event_filename) {
		// do we have a path?
		str = strstr(term, " path=");
		if (str) {
			str += 6;
			rc = common_path_parser(s, str);
			if (rc)
				goto err;
			term += 7;
		}
	}
	if (event_subject) {
		// scontext
		str = strstr(term, "scontext=");
		if (str != NULL) {
			str += 9;
			term = strchr(str, ' ');
			if (term == NULL) {
				rc = 7;
				goto err;
			}
			*term = 0;
			an.scontext = strdup(str);
			*term = ' ';
		}
	}

	if (event_object) {
		// tcontext
		str = strstr(term, "tcontext=");
		if (str != NULL) {
			str += 9;
			term = strchr(str, ' ');
			if (term == NULL) {
				rc = 8;
				goto err;
			}
			*term = 0;
			an.tcontext = strdup(str);
			*term = ' ';
		}
	}

	// Now get the class...its at the end, so we do things different
	str = strstr(term, "tclass=");
	if (str == NULL) {
		rc = 9;
		goto err;
	}
	str += 7;
	term = strchr(str, ' ');
	if (term)
		*term = 0;
	an.avc_class = strdup(str);
	if (term)
		*term = ' ';

	if (audit_avc_init(s) == 0) {
		alist_append(s->avc, &an);
	} else {
		rc = 10;
		goto err;
	}

	return 0;
err:
	anode_clear(&an);
	return rc;
}

static int parse_kernel_anom(const lnode *n, search_items *s)
{
	char *str, *ptr, *term;

	// get loginuid
	str = strstr(n->message, "auid=");
	if (str == NULL)
		return 1;
	ptr = str + 5;
	term = strchr(ptr, ' ');
	if (term)
		*term = 0;
	errno = 0;
	s->loginuid = strtoul(ptr, NULL, 10);
	if (errno)
		return 2;
	if (term)
		*term = ' ';
	else
		term = n->message;

	// get uid
	str = strstr(term, "uid="); // if promiscuous, we start over
	if (str) {
		ptr = str + 4;
		term = strchr(ptr, ' ');
		if (term == NULL)
			return 3;
		*term = 0;
		errno = 0;
		s->uid = strtoul(ptr, NULL, 10);
		if (errno)
			return 4;
		*term = ' ';
	}

	// get gid
	str = strstr(term, "gid=");
	if (str) {
		ptr = str + 4;
		term = strchr(ptr, ' ');
		if (term == NULL)
			return 5;
		*term = 0;
		errno = 0;
		s->gid = strtoul(ptr, NULL, 10);
		if (errno)
			return 6;
		*term = ' ';
	}

	str = strstr(term, "ses=");
	if (str) {
		ptr = str + 4;
		term = strchr(ptr, ' ');
		if (term)
			*term = 0;
		errno = 0;
		s->session_id = strtoul(ptr, NULL, 10);
		if (errno)
			return 7;
		if (term)
			*term = ' ';
		else
			term = ptr;
	}

	if (event_subject) {
		// scontext
		str = strstr(term, "subj=");
		if (str) {
			str += 5;
			term = strchr(str, ' ');
			if (term == NULL)
				return 8;
			*term = 0;
			if (audit_avc_init(s) == 0) {
				anode an;

				anode_init(&an);
				an.scontext = strdup(str);
				alist_append(s->avc, &an);
				*term = ' ';
			} else
				return 9;
		}
	}

	// get pid
	if (event_pid != -1) {
		str = strstr(term, "pid=");
		if (str) {
			ptr = str + 4;
			term = strchr(ptr, ' ');
			if (term == NULL)
				return 10;
			*term = 0;
			errno = 0;
			s->pid = strtoul(ptr, NULL, 10);
			if (errno)
				return 11;
			*term = ' ';
		}
	}

	if (event_comm) {
		// dont do this search unless needed
		str = strstr(term, "comm=");
		if (str) {
			str += 5;
			if (*str == '"') {
				str++;
				term = strchr(str, '"');
				if (term == NULL)
					return 12;
				*term = 0;
				s->comm = strdup(str);
				*term = '"';
			} else 
				s->comm = unescape(str);
		} 
	}

	return 0;
}

// This is for messages that only have the loginuid as the item
// of interest.
static int parse_simple_message(const lnode *n, search_items *s)
{
	char *str, *ptr, *term  = n->message;

	// get loginuid - note some kernels don't have auid for CONFIG_CHANGE
	str = strstr(term, "auid=");
	if (str == NULL && n->type != AUDIT_CONFIG_CHANGE)
		return 1;
	if (str) {
		ptr = str + 5;
		term = strchr(ptr, ' ');
		if (term)
			*term = 0;
		errno = 0;
		s->loginuid = strtoul(ptr, NULL, 10);
		if (errno)
			return 2;
		if (term)
			*term = ' ';
		else
			term = ptr;
	}

	// ses
	if (event_session_id != -2 ) {
		str = strstr(term, "ses=");
		if (str) {
			ptr = str + 4;
			term = strchr(ptr, ' ');
			if (term)
				*term = 0;
			errno = 0;
			s->session_id = strtoul(ptr, NULL, 10);
			if (errno)
				return 3;
			if (term)
				*term = ' ';
			else
				term = ptr;
		}
	}

	// Now get subj label
	if (event_subject) {
		// scontext
		str = strstr(term, "subj=");
		if (str != NULL) {
			str += 5;
			term = strchr(str, ' ');
			if (term)
				*term = 0;
			if (audit_avc_init(s) == 0) {
				anode an;

				anode_init(&an);
				an.scontext = strdup(str);
				alist_append(s->avc, &an);
				if (term)
					*term = ' ';
				else	// Set it back to something sane
					term = str;
			} else
				return 4;
		}
	}

	if (event_key) {
		str = strstr(term, "key=");
		if (str != NULL) {
			if (!s->key) {
				//create
				s->key = malloc(sizeof(slist));
				if (s->key == NULL)
					return 5;
				slist_create(s->key);
			}
			ptr = str + 4;
			if (*ptr == '"') {
				ptr++;
				term = strchr(ptr, '"');
				if (term != NULL) {
					*term = 0;
					if (s->key) {
						// append
						snode sn;
						sn.str = strdup(ptr);
						sn.key = NULL;
						sn.hits = 1;
						slist_append(s->key, &sn);
					}
					*term = '"';
				} else
					return 6;
			} else {
				if (s->key) {
					char *saved=NULL;
					char *keyptr = unescape(ptr);
					char *kptr = strtok_r(keyptr,
						key_sep, &saved);
					while (kptr) {
						snode sn;
						// append
						sn.str = strdup(kptr);
						sn.key = NULL;
						sn.hits = 1;
						slist_append(s->key, &sn);
						kptr = strtok_r(NULL,
							key_sep, &saved);
					}
					free(keyptr);
				}
			}
		}
	}

	// defaulting this to 1 for these messages. The kernel generally
	// does not log the res since it can be nothing but success. 
	// But it can still be overriden below if res= is found in the event
	if (n->type == AUDIT_CONFIG_CHANGE) 
		s->success = S_SUCCESS;

	// and results (usually last)
	if (event_success != S_UNSET) {
		str = strstr(term, "res=");
		if (str != NULL) {
			ptr = str + 4;
			term = strchr(ptr, ' ');
			if (term)
				*term = 0;
			errno = 0;
			s->success = strtoul(ptr, NULL, 10);
			if (errno)
				return 7;
			if (term)
				*term = ' ';
		}
	}

	return 0;
}

static int parse_tty(const lnode *n, search_items *s)
{
	char *str, *ptr, *term=n->message;

	// get pid
	if (event_pid != -1) {
		str = strstr(n->message, "pid=");
		if (str) {
			ptr = str + 4;
			term = strchr(ptr, ' ');
			if (term == NULL)
				return 1;
			*term = 0;
			errno = 0;
			s->pid = strtoul(ptr, NULL, 10);
			if (errno)
				return 2;
			*term = ' ';
		}
	}

	// get uid
	str = strstr(term, " uid="); // if promiscuous, we start over
	if (str) {
		ptr = str + 4;
		term = strchr(ptr, ' ');
		if (term == NULL)
			return 3;
		*term = 0;
		errno = 0;
		s->uid = strtoul(ptr, NULL, 10);
		if (errno)
			return 4;
		*term = ' ';
	}

	// get loginuid
	str = strstr(term, "auid=");
	if (str == NULL)
		return 5;
	ptr = str + 5;
	term = strchr(ptr, ' ');
	if (term)
		*term = 0;
	errno = 0;
	s->loginuid = strtoul(ptr, NULL, 10);
	if (errno)
		return 6;
	if (term)
		*term = ' ';
	else
		term = ptr;

	// ses
	if (event_session_id != -2 ) {
		str = strstr(term, "ses=");
		if (str) {
			ptr = str + 4;
			term = strchr(ptr, ' ');
			if (term == NULL)
				return 7;
			*term = 0;
			errno = 0;
			s->session_id = strtoul(ptr, NULL, 10);
			if (errno)
				return 8;
			*term = ' ';
		}
	}

/*	if (event_subject) {
		// scontext
		str = strstr(term, "subj=");
		if (str) {
			str += 5;
			term = strchr(str, ' ');
			if (term == NULL)
				return 9;
			*term = 0;
			if (audit_avc_init(s) == 0) {
				anode an;

				anode_init(&an);
				an.scontext = strdup(str);
				alist_append(s->avc, &an);
				*term = ' ';
			} else
				return 10;
		}
	} */

	if (event_comm) {
		// dont do this search unless needed
		str = strstr(term, "comm=");
		if (str) {
			str += 5;
			if (*str == '"') {
				str++;
				term = strchr(str, '"');
				if (term == NULL)
					return 11;
				*term = 0;
				s->comm = strdup(str);
				*term = '"';
			} else 
				s->comm = unescape(str);
		} 
	}

	return 0;
}

static int parse_pkt(const lnode *n, search_items *s)
{
	char *str, *ptr, *term=n->message;

	// get hostname
	if (event_hostname) {
		str = strstr(n->message, "saddr=");
		if (str) {
			ptr = str + 6;
			term = strchr(ptr, ' ');
			if (term == NULL)
				return 1;
			*term = 0;
			s->hostname = strdup(ptr);
			*term = ' ';
		}
	}

	return 0;
}

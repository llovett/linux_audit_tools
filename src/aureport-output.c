/*
* aureport-output.c - Print the report
* Copyright (c) 2005-06, 2008 Red Hat Inc., Durham, North Carolina.
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
#include <ctype.h>
#include "aureport-scan.h"
#include "aureport-options.h"
#include "ausearch-lookup.h"

/* Locale functions */
static void print_title_summary(void);
static void print_title_detailed(void);
static void do_summary_output(void);
static void do_file_summary_output(slist *sptr);
static void do_string_summary_output(slist *sptr);
static void do_user_summary_output(slist *sptr);
static void do_int_summary_output(ilist *sptr);
static void do_syscall_summary_output(ilist *sptr);
static void do_type_summary_output(ilist *sptr);

/* Local Data */
unsigned int line_item;


void print_title(void)
{
	line_item = 0U;
	printf("\n");
	switch (report_detail)
	{
		case D_SUM:
			print_title_summary();
			break;
		case D_DETAILED:
			print_title_detailed();
			break;
		case D_SPECIFIC:
		default:
			break;
	}
}

static void print_title_summary(void)
{
	if (event_failed == F_FAILED) printf("Failed ");
	if (event_failed == F_SUCCESS) printf("Success ");
	switch (report_type)
        {
		case RPT_SUMMARY:
			printf("Summary Report\n");
			printf("======================\n");
			break;
		case RPT_AVC:
			printf("Avc Object Summary Report\n");
			printf("=================================\n");
			printf("total  obj\n");
			printf("=================================\n");
			break;
		case RPT_MAC:
			printf("MAC Summary Report\n");
			printf("======================\n");
			printf("total  type\n");
			printf("======================\n");
			break;
		case RPT_CONFIG:
			UNIMPLEMENTED;
			break;
		case RPT_AUTH:
			printf("Authentication Summary Report\n");
			printf("=============================\n");
			printf("total  acct\n");
			printf("=============================\n");
			break;
		case RPT_LOGIN:
			printf("Login Summary Report\n");
			printf("============================\n");
			printf("total  auid\n");
			printf("============================\n");
			break;
		case RPT_ACCT_MOD:
			UNIMPLEMENTED;
			break;
		case RPT_TIME:
			UNIMPLEMENTED;
			break;
		case RPT_EVENT:
			printf("Event Summary Report\n");
			printf("======================\n");
			printf("total  type\n");
			printf("======================\n");
			break;
		case RPT_FILE:
			printf("File Summary Report\n");
			printf("===========================\n");
			printf("total  file\n");
			printf("===========================\n");
			break;
		case RPT_HOST:
			printf("Host Summary Report\n");
			printf("===========================\n");
			printf("total  host\n");
			printf("===========================\n");
			break;
		case RPT_PID:
			printf("Pid Summary Report\n");
			printf("==========================\n");
			printf("total  pid\n");
			printf("==========================\n");
			break;
		case RPT_SYSCALL:
			printf("Syscall Summary Report\n");
			printf("==========================\n");
			printf("total  syscall\n");
			printf("==========================\n");
			break;
		case RPT_TERM:
			printf("Terminal Summary Report\n");
			printf("===============================\n");
			printf("total  terminal\n");
			printf("===============================\n");
			break;
		case RPT_USER:
			printf("User Summary Report\n");
			printf("===========================\n");
			printf("total  auid\n");
			printf("===========================\n");
			break;
		case RPT_EXE:
			printf("Executable Summary Report\n");
			printf("=================================\n");
			printf("total  file\n");
			printf("=================================\n");
			break;
		case RPT_ANOMALY:
			printf("Anomaly Summary Report\n");
			printf("======================\n");
			printf("total  type\n");
			printf("======================\n");
			break;
		case RPT_RESPONSE:
			printf("Anomaly Response Summary Report\n");
			printf("===============================\n");
			printf("total  type\n");
			printf("===============================\n");
			break;
		case RPT_CRYPTO:
			printf("Crypto Summary Report\n");
			printf("======================\n");
			printf("total  type\n");
			printf("======================\n");
			break;
		case RPT_KEY:
			printf("Key Summary Report\n");
			printf("===========================\n");
			printf("total  key\n");
			printf("===========================\n");
			break;
		case RPT_TTY:
			UNIMPLEMENTED;
			break;
		default:
			break;
	}
}

static void print_title_detailed(void)
{
	switch (report_type)
        {
		case RPT_AVC:
			printf("AVC Report\n");
			printf(
		  "========================================================\n");
			printf(
		  "# date time comm subj syscall class permission obj event\n");
			printf(
		  "========================================================\n");
			break;
		case RPT_CONFIG:
			printf("Config Change Report\n");
			printf("===================================\n");
			printf("# date time type auid success event\n");
			printf("===================================\n");
			break;
		case RPT_AUTH:
			printf("Authentication Report\n");
			printf(
			  "============================================\n");
			printf(
			  "# date time acct host term exe success event\n");
			printf(
			  "============================================\n");
			break;
		case RPT_LOGIN:
			printf("Login Report\n");
			printf(
			  "============================================\n");
			printf(
			  "# date time auid host term exe success event\n");
			printf(
			  "============================================\n");
			break;
		case RPT_ACCT_MOD:
			printf("Account Modifications Report\n");
			printf(
			 "=================================================\n");
			printf(
			 "# date time auid addr term exe acct success event\n");
			printf(
			 "=================================================\n");
			break;
		case RPT_TIME:
			printf("Log Time Range Report\n");
			printf("=====================\n");
			break;
		case RPT_EVENT:
			if (report_detail == D_DETAILED) {
				printf("Event Report\n");
				printf("===================================\n");
				printf("# date time event type auid success\n");
				printf("===================================\n");
			} else {
				printf("Specific Event Report\n");
				printf("=====================\n");
			}
			break;
		case RPT_FILE:
			if (report_detail == D_DETAILED) {
			    printf("File Report\n");
			    printf(
			"===============================================\n");
			    printf(
			"# date time file syscall success exe auid event\n");
			    printf(
			"===============================================\n");
			} else {
				printf("Specific File Report\n");
				printf("====================\n");
			}
			break;
		case RPT_HOST:
			if (report_detail == D_DETAILED) {
				printf("Host Report\n");
				printf("===================================\n");
				printf("# date time host syscall auid event\n");
				printf("===================================\n");
			} else {
				printf("Specific Host Report\n");
				printf("====================\n");
			}
			break;
		case RPT_PID:
			if (report_detail == D_DETAILED) {
				printf("Process ID Report\n");
				printf(
				  "======================================\n");
				printf(
				  "# date time pid exe syscall auid event\n");
				printf(
				  "======================================\n");
			} else {
				printf("Specific Process ID Report\n");
				printf("==========================\n");
			}
			break;
		case RPT_SYSCALL:
			if (report_detail == D_DETAILED) {
				printf("Syscall Report\n");
				printf(
				  "=======================================\n");
				printf(
				  "# date time syscall pid comm auid event\n");
				printf(
				  "=======================================\n");
			} else {
				printf("Specific Syscall Report\n");
				printf("=======================\n");
			}
			break;
		case RPT_TERM:
			if (report_detail == D_DETAILED) {
				printf("Terminal Report\n");
				printf(
				  "====================================\n");
				printf(
				  "# date time term host exe auid event\n");
				printf(
				  "====================================\n");
			} else {
				printf("Specific Terminal Report\n");
				printf("========================\n");
			}
			break;
		case RPT_USER:
			if (report_detail == D_DETAILED) {
				printf("User ID Report\n");
				printf(
				  "====================================\n");
				printf(
				  "# date time auid term host exe event\n");
				printf(
				  "====================================\n");
			} else {
				printf("Specific User ID Report\n");
				printf("=======================\n");
			}
			break;
		case RPT_EXE:
			if (report_detail == D_DETAILED) {
				printf("Executable Report\n");
				printf(
				  "====================================\n");
				printf(
				  "# date time exe term host auid event\n");
				printf(
				  "====================================\n");
			} else {
				printf("Specific Executable Report\n");
				printf("==========================\n");
			}
			break;
		case RPT_ANOMALY:
			if (report_detail == D_DETAILED) {
				printf("Anomaly Report\n");
				printf(
				"=========================================\n");
				printf(
				"# date time type exe term host auid event\n");
				printf(
				"=========================================\n");
			} else {
				printf("Specific Anomaly Report\n");
				printf("=======================\n");
			}
			break;
		case RPT_RESPONSE:
			if (report_detail == D_DETAILED) {
				printf("Response to Anomaly Report\n");
				printf("==============================\n");
				printf("# date time type success event\n");
				printf("==============================\n");
			} else {
				printf("Specific Response to Anomaly Report\n");
				printf("===================================\n");
			}
			break;
		case RPT_MAC:
			if (report_detail == D_DETAILED) {
				printf("MAC Report\n");
				printf("===================================\n");
				printf("# date time auid type success event\n");
				printf("===================================\n");
			} else {
				printf("Specific Mandatory Access Control (MAC) Report\n");
				printf("===================================\n");
			}
			break;
		case RPT_CRYPTO:
			if (report_detail == D_DETAILED) {
				printf("Crypto Report\n");
				printf("===================================\n");
				printf("# date time auid type success event\n");
				printf("===================================\n");
			} else {
				printf("Specific Crypto Report\n");
				printf("===================================\n");
			}
			break;
		case RPT_KEY:
			if (report_detail == D_DETAILED) {
			    printf("Key Report\n");
			    printf(
			"===============================================\n");
			    printf(
			"# date time key success exe auid event\n");
			    printf(
			"===============================================\n");
			} else {
				printf("Specific Key Report\n");
				printf("====================\n");
			}
			break;
		case RPT_TTY:
			if (report_detail == D_DETAILED) {
			    printf("TTY Report\n");
			    printf(
			"===============================================\n");
			    printf(
			"# date time event auid term sess comm data\n");
			    printf(
			"===============================================\n");
			} else {
				printf("Specific TTY Report\n");
				printf("====================\n");
			}
			break;
		default:
			break;
	}
}

void print_per_event_item(llist *l)
{
	char buf[128];
	char name[64];
	char date[32];
	struct tm *tv;

	// The beginning is common to all reports
	tv = localtime(&l->e.sec);
	strftime(date, sizeof(date), "%x %T", tv);
	if (report_type != RPT_AVC) {
		line_item++;
		printf("%u. %s ", line_item, date);
	}

	switch (report_type)
	{
		case RPT_AVC:
			alist_find_avc(l->s.avc);
			do {
				anode *an = l->s.avc->cur;
				line_item++;
				printf("%u. %s ", line_item, date);
		// command subject syscall action obj res event
			printf("%s %s %s %s %s %s %s %lu\n", 
				l->s.comm ? l->s.comm : "?",
				an->scontext, 
				aulookup_syscall(l, buf,sizeof(buf)),
				an->avc_class, an->avc_perm,
				an->tcontext, aulookup_result(an->avc_result),
				l->e.serial);
//printf("items:%d\n", l->s.avc->cnt);
			} while (alist_next_avc(l->s.avc));
			break;
		case RPT_CONFIG:
			// FIXME:who, action, what, outcome, event
			// NOW: type auid success event
			printf("%s %s %s %lu\n",
				audit_msg_type_to_name(l->head->type),
				aulookup_uid(l->s.loginuid, name, sizeof(name)),
				aulookup_success(l->s.success), l->e.serial);
			break;
		case RPT_AUTH:
			// who, addr, terminal, exe, success, event
			// Special note...uid is used here because that is
			// the way that the message works. This is because
			// on failed logins, loginuid is not set.
			printf("%s %s %s %s %s %lu\n",
				l->s.acct ? l->s.acct :
				aulookup_uid(l->s.uid, name, sizeof(name)),
				l->s.hostname, l->s.terminal,
				l->s.exe, aulookup_success(l->s.success),
				l->e.serial);
			break;
		case RPT_LOGIN:
			// who, addr, terminal, exe, success, event
			// Special note...uid is used here because that is
			// the way that the message works. This is because
			// on failed logins, loginuid is not set.
			printf("%s %s %s %s %s %lu\n", 
				((l->s.success == S_FAILED) && l->s.acct) ?
				l->s.acct :
				aulookup_uid(l->s.uid, name, sizeof(name)),
				l->s.hostname, l->s.terminal,
				l->s.exe, aulookup_success(l->s.success),
				l->e.serial);
			break;
		case RPT_ACCT_MOD:
			// who, addr, terminal, exe, success, event
			printf("%s %s %s %s %s %s %lu\n",
				aulookup_uid(l->s.loginuid, name, sizeof(name)),
				l->s.hostname ? l->s.hostname : "?",
				l->s.terminal ? l->s.terminal : "?",
				l->s.exe ? l->s.exe : "?",
				l->s.acct ? l->s.acct : "?",
				aulookup_success(l->s.success),
				l->e.serial);
			break;
		case RPT_EVENT:	// report_detail == D_DETAILED
			//        event, type, who, success
			printf("%lu %s %s %s\n",
				l->e.serial,
				audit_msg_type_to_name(l->head->type),
				aulookup_uid(l->s.loginuid, name, 
					sizeof(name)),
					aulookup_success(l->s.success));
			break;
		case RPT_FILE:	// report_detail == D_DETAILED
			// file, syscall, success, exe, who, event
			slist_first(l->s.filename);
			printf("%s %s %s %s %s %lu\n",
				l->s.filename->cur->str,
				aulookup_syscall(l,buf,sizeof(buf)),
				aulookup_success(l->s.success),
				l->s.exe ? l->s.exe : "?",
				aulookup_uid(l->s.loginuid, name, sizeof(name)),
				l->e.serial);
			break;
		case RPT_HOST:	// report_detail == D_DETAILED
			// host, syscall, who, event
			printf("%s %s %s %lu\n",
				l->s.hostname,
				aulookup_syscall(l,buf,sizeof(buf)),
				aulookup_uid(l->s.loginuid, name, sizeof(name)),
				l->e.serial);
			break;
		case RPT_PID:	// report_detail == D_DETAILED
			// pid, exe, syscall, who, event
			printf("%u %s %s %s %lu\n",
				l->s.pid,
				l->s.exe ? l->s.exe : "?",
				aulookup_syscall(l,buf,sizeof(buf)),
				aulookup_uid(l->s.loginuid, name, sizeof(name)),
				l->e.serial);
			break;
		case RPT_SYSCALL:	// report_detail == D_DETAILED
			// syscall, pid, comm, who, event
			printf("%s %u %s %s %lu\n", 
				aulookup_syscall(l,buf,sizeof(buf)),
				l->s.pid,
				l->s.comm ? l->s.comm : "?",
				aulookup_uid(l->s.loginuid, name, sizeof(name)),
				l->e.serial);
			break;
		case RPT_TERM:	// report_detail == D_DETAILED
			// terminal, host, exe, who, event
			printf("%s %s %s %s %lu\n",
				l->s.terminal, l->s.hostname,
				l->s.exe,
				aulookup_uid(l->s.loginuid, name, sizeof(name)),
				l->e.serial);
			break;
		case RPT_USER:	// report_detail == D_DETAILED
			// who, terminal, host, exe, event
			printf("%s %s %s %s %lu\n",
				aulookup_uid(l->s.loginuid, name, sizeof(name)),
				l->s.terminal ? l->s.terminal : "?",
				l->s.hostname ? l->s.hostname : "?",
				l->s.exe ? l->s.exe : "?",
				l->e.serial);
			break;
		case RPT_EXE:	// report_detail == D_DETAILED
			// exe, terminal, host, who, event
			printf("%s %s %s %s %lu\n",
				l->s.exe ? l->s.exe : "?", 
				l->s.terminal ? l->s.terminal : "?",
				l->s.hostname ? l->s.hostname : "?",
				aulookup_uid(l->s.loginuid, name, sizeof(name)),
				l->e.serial);
			break;
		case RPT_ANOMALY:	// report_detail == D_DETAILED
			// type exe term host auid event
			printf("%s %s %s %s %s %lu\n",
				audit_msg_type_to_name(l->head->type),
				l->s.exe ? l->s.exe : l->s.comm ? l->s.comm: "?", 
				l->s.terminal ? l->s.terminal : "?",
				l->s.hostname ? l->s.hostname : "?",
				aulookup_uid(l->s.loginuid, name, sizeof(name)),
				l->e.serial);
			break;
		case RPT_RESPONSE:	// report_detail == D_DETAILED
			// type success event
			printf("%s %s %lu\n",
				audit_msg_type_to_name(l->head->type),
				aulookup_success(l->s.success),
				l->e.serial);
			break;
		case RPT_MAC:
			// auid type success event
			printf("%s %s %s %lu\n",
				aulookup_uid(l->s.loginuid, name, sizeof(name)),
				audit_msg_type_to_name(l->head->type),
				aulookup_success(l->s.success),
				l->e.serial);
			break;
		case RPT_CRYPTO:
			// auid type success event
			printf("%s %s %s %lu\n",
				aulookup_uid(l->s.loginuid, name, sizeof(name)),
				audit_msg_type_to_name(l->head->type),
				aulookup_success(l->s.success),
				l->e.serial);
			break;
		case RPT_KEY:	// report_detail == D_DETAILED
			// key, success, exe, who, event
			slist_first(l->s.key);
			printf("%s %s %s %s %lu\n",
				l->s.key->cur->str,
				aulookup_success(l->s.success),
				l->s.exe ? l->s.exe : "?",
				aulookup_uid(l->s.loginuid, name, sizeof(name)),
				l->e.serial);
			break;
		case RPT_TTY: {
			char *ch, *ptr = strstr(l->head->message, "data=");
			if (!ptr)
				break;
			ptr += 5;
			ch = strrchr(ptr, ' ');
			if (ch)
				*ch = 0;
			// event who term sess data
			printf("%lu %s %s %u %s ",
				l->e.serial,
				aulookup_uid(l->s.loginuid, name, sizeof(name)),
				l->s.terminal ? l->s.terminal : "?",
				l->s.session_id,
				l->s.comm ? l->s.comm: "?");
			print_tty_data(ptr);
			printf("\n");
			}
			break;
		default:
			break;
	}
}

void print_wrap_up(void)
{
	if (report_detail != D_SUM)
		return;

	switch (report_type)
	{
		case RPT_SUMMARY:
			do_summary_output();
			break;
		case RPT_AVC:
			slist_sort_by_hits(&sd.avc_objs);
			do_string_summary_output(&sd.avc_objs);
			break;
		case RPT_CONFIG:
			break;
		case RPT_AUTH:
			slist_sort_by_hits(&sd.users);
			do_user_summary_output(&sd.users);
			break;
		case RPT_LOGIN:
			slist_sort_by_hits(&sd.users);
			do_user_summary_output(&sd.users);
			break;
		case RPT_ACCT_MOD:
			break;
		case RPT_EVENT: /* We will borrow the pid list */
			ilist_sort_by_hits(&sd.pids);
			do_type_summary_output(&sd.pids);
			break;
		case RPT_FILE:
			slist_sort_by_hits(&sd.files);
			do_file_summary_output(&sd.files);
			break;
		case RPT_HOST:
			slist_sort_by_hits(&sd.hosts);
			do_string_summary_output(&sd.hosts);
			break;
		case RPT_PID:
			ilist_sort_by_hits(&sd.pids);
			do_int_summary_output(&sd.pids);
			break;
		case RPT_SYSCALL:
			ilist_sort_by_hits(&sd.sys_list);
			do_syscall_summary_output(&sd.sys_list);
			break;
		case RPT_TERM:
			slist_sort_by_hits(&sd.terms);
			do_string_summary_output(&sd.terms);
			break;
		case RPT_USER:
			slist_sort_by_hits(&sd.users);
			do_user_summary_output(&sd.users);
			break;
		case RPT_EXE:
			slist_sort_by_hits(&sd.exes);
			do_file_summary_output(&sd.exes);
			break;
		case RPT_ANOMALY:
			ilist_sort_by_hits(&sd.anom_list);
			do_type_summary_output(&sd.anom_list);
			break;
		case RPT_RESPONSE:
			ilist_sort_by_hits(&sd.resp_list);
			do_type_summary_output(&sd.resp_list);
			break;
		case RPT_MAC:
			ilist_sort_by_hits(&sd.mac_list);
			do_type_summary_output(&sd.mac_list);
			break;
		case RPT_CRYPTO:
			ilist_sort_by_hits(&sd.crypto_list);
			do_type_summary_output(&sd.crypto_list);
			break;
		case RPT_KEY:
			slist_sort_by_hits(&sd.keys);
			do_file_summary_output(&sd.keys);
			break;
		default:
			break;
	}
}

static void do_summary_output(void)
{
	extern event very_first_event;
	extern event very_last_event;

	printf("Range of time in logs: ");
	{
		struct tm *btm;
		char tmp[48];

		btm = localtime(&very_first_event.sec);
		strftime(tmp, sizeof(tmp), "%x %T", btm);
		printf("%s.%03d - ", tmp, very_first_event.milli);
		btm = localtime(&very_last_event.sec);
		strftime(tmp, sizeof(tmp), "%x %T", btm);
		printf("%s.%03d\n", tmp, very_last_event.milli);
	}
	printf("Selected time for report: ");
	{
		struct tm *btm;
		char tmp[48];

		if (start_time)
			btm = localtime(&start_time);
		else
			btm = localtime(&very_first_event.sec);
		strftime(tmp, sizeof(tmp), "%x %T", btm);
		printf("%s - ", tmp);
		if (end_time) 
			btm = localtime(&end_time);
		else 
			btm = localtime(&very_last_event.sec);
		strftime(tmp, sizeof(tmp), "%x %T", btm);
		if (end_time) 
			printf("%s\n", tmp);
		else 
			printf("%s.%03d\n", tmp, very_last_event.milli);
	}
	printf("Number of changes in configuration: %lu\n", sd.changes);
	printf("Number of changes to accounts, groups, or roles: %lu\n",
							 sd.acct_changes);
	printf("Number of logins: %lu\n", sd.good_logins);
	printf("Number of failed logins: %lu\n", sd.bad_logins);
	printf("Number of authentications: %lu\n", sd.good_auth);
	printf("Number of failed authentications: %lu\n", sd.bad_auth);
	printf("Number of users: %u\n", sd.users.cnt);
	printf("Number of terminals: %u\n", sd.terms.cnt);
	printf("Number of host names: %u\n", sd.hosts.cnt);
	printf("Number of executables: %u\n", sd.exes.cnt);
	printf("Number of files: %u\n", sd.files.cnt);
	printf("Number of AVC's: %lu\n", sd.avcs);
	printf("Number of MAC events: %lu\n", sd.mac);
	printf("Number of failed syscalls: %lu\n", sd.failed_syscalls);
	printf("Number of anomaly events: %lu\n", sd.anomalies);
	printf("Number of responses to anomaly events: %lu\n", sd.responses);
	printf("Number of crypto events: %lu\n", sd.crypto);
	printf("Number of keys: %u\n", sd.keys.cnt);
	printf("Number of process IDs: %u\n", sd.pids.cnt);
	printf("Number of events: %lu\n", sd.events);
	printf("\n");
}

static void do_file_summary_output(slist *sptr)
{
	const snode *sn;

	if (sptr->cnt == 0) {
		printf("<no events of interest were found>\n\n");
		return;
	}
	slist_first(sptr);
	sn=slist_get_cur(sptr);
	while (sn) {
		printf("%u  %s\n", sn->hits, sn->str);
		sn=slist_next(sptr);
	}
}

static void do_string_summary_output(slist *sptr)
{
	const snode *sn;

	if (sptr->cnt == 0) {
		printf("<no events of interest were found>\n\n");
		return;
	}
	slist_first(sptr);
	sn=slist_get_cur(sptr);
	while (sn) {
		printf("%u  %s\n", sn->hits, sn->str);
		sn=slist_next(sptr);
	}
}

static void do_user_summary_output(slist *sptr)
{
	const snode *sn;

	if (sptr->cnt == 0) {
		printf("<no events of interest were found>\n\n");
		return;
	}
	slist_first(sptr);
	sn=slist_get_cur(sptr);
	while (sn) {
		long uid;
		char name[64];

		if (sn->str[0] == '-' || isdigit(sn->str[0])) {
			uid = strtol(sn->str, NULL, 10);
			printf("%u  %s\n", sn->hits, 
				aulookup_uid(uid, name, sizeof(name)));
		} else 
			printf("%u  %s\n", sn->hits, sn->str); 
		sn=slist_next(sptr);
	}
}

static void do_int_summary_output(ilist *sptr)
{
	const int_node *in;

	if (sptr->cnt == 0) {
		printf("<no events of interest were found>\n\n");
		return;
	}
	ilist_first(sptr);
	in=ilist_get_cur(sptr);
	while (in) {
		printf("%u  %d\n", in->hits, in->num);
		in=ilist_next(sptr);
	}
}

static void do_syscall_summary_output(ilist *sptr)
{
	const int_node *in;

	if (sptr->cnt == 0) {
		printf("<no events of interest were found>\n\n");
		return;
	}
	ilist_first(sptr);
	in=ilist_get_cur(sptr);
	while (in) {
		const char *sys = NULL;
		int machine = audit_elf_to_machine(in->aux1);
		if (machine >= 0) 
			sys = audit_syscall_to_name(in->num, machine);
		if (sys) 
			printf("%u  %s\n", in->hits, sys);
		else
			printf("%u  %d\n", in->hits, in->num);
		in=ilist_next(sptr);
	}
}

static void do_type_summary_output(ilist *sptr)
{
	const int_node *in;

	if (sptr->cnt == 0) {
		printf("<no events of interest were found>\n\n");
		return;
	}
	ilist_first(sptr);
	in=ilist_get_cur(sptr);
	while (in) {
		const char *name = audit_msg_type_to_name(in->num);
		if (report_format == RPT_DEFAULT)
			printf("%u  %d\n", in->hits, in->num);
		else
			printf("%u  %s\n", in->hits, name);
		in=ilist_next(sptr);
	}
}


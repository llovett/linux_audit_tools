/*
* ausearch-llist.c - Minimal linked list library
* Copyright (c) 2005-2008, 2011 Red Hat Inc., Durham, North Carolina.
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

#include <stdlib.h>
#include <string.h>
#include "ausearch-llist.h"

void list_create(llist *l)
{
	l->head = NULL;
	l->cur = NULL;
	l->cnt = 0;
	l->e.milli = 0L;       
	l->e.sec = 0L;         
	l->e.serial = 0L;      
	l->e.node = NULL;      
	l->e.type = 0;      
	l->s.gid = -1;          
	l->s.egid = -1;         
	l->s.ppid = -1;            
	l->s.pid = -1;            
	l->s.success = S_UNSET;
	l->s.uid = -1;            
	l->s.euid = -1;           
	l->s.loginuid = -2;
	l->s.hostname = NULL;
	l->s.filename = NULL;
	l->s.terminal = NULL;
	l->s.cwd = NULL;
	l->s.exe = NULL;
	l->s.key = NULL;
	l->s.comm = NULL;
	l->s.avc = NULL;
	l->s.acct = NULL;
	l->s.arch = 0;
	l->s.syscall = 0;
	l->s.session_id = -2;
	l->s.exit = 0;
	l->s.exit_is_set = 0;
}

void list_last(llist *l)
{
        register lnode* window;
	
	if (l->head == NULL)
		return;

        window = l->head;
	while (window->next)
		window = window->next;
	l->cur = window;
}

lnode *list_next(llist *l)
{
	if (l->cur == NULL)
		return NULL;
	l->cur = l->cur->next;
	return l->cur;
}

lnode *list_prev(llist *l)
{
	if (l->cur == NULL)
		return NULL;

	if (l->cur->item == 0)
		return NULL;

	list_find_item(l, l->cur->item-1);
	return l->cur;
}

void list_append(llist *l, lnode *node)
{
	lnode* newnode;

	newnode = malloc(sizeof(lnode));

	if (node->message)
		newnode->message = node->message;
	else
		newnode->message = NULL;

	newnode->type = node->type;
	newnode->a0 = node->a0;
	newnode->item = l->cnt; 
	newnode->next = NULL;

	// if we are at top, fix this up
	if (l->head == NULL)
		l->head = newnode;
	else	// Otherwise add pointer to newnode
		l->cur->next = newnode;

	// make newnode current
	l->cur = newnode;
	l->cnt++;
}

int list_find_item(llist *l, unsigned int i)
{
        register lnode* window;
                                                                                
	if (l->cur && (l->cur->item <= i))
		window = l->cur;	/* Try to use where we are */
	else
        	window = l->head;	/* Can't, start over */

	while (window) {
		if (window->item == i) {
			l->cur = window;
			return 1;
		} else
			window = window->next;
	}
	return 0;
}

void list_clear(llist* l)
{
	lnode* nextnode;
	register lnode* current;

	current = l->head;
	while (current) {
		nextnode=current->next;
		free(current->message);
		free(current);
		current=nextnode;
	}
	l->head = NULL;
	l->cur = NULL;
	l->cnt = 0;
	l->e.milli = 0L;       
	l->e.sec = 0L;         
	l->e.serial = 0L;      
	free((char *)l->e.node);
	l->e.node = NULL;
	l->e.type = 0;         
	l->s.gid = -1;
	l->s.egid = -1;
	l->s.ppid = -1;
	l->s.pid = -1;
	l->s.success = S_UNSET;
	l->s.uid = -1;
	l->s.euid = -1;
	l->s.loginuid = -2;
	free(l->s.hostname);
	l->s.hostname = NULL;
	if (l->s.filename) {
		slist_clear(l->s.filename);
		free(l->s.filename);
		l->s.filename = NULL;
	}
	free(l->s.terminal);
	l->s.terminal = NULL;
	free(l->s.cwd);
	l->s.cwd = NULL;
	free(l->s.exe);
	l->s.exe = NULL;
	if (l->s.key) {
		slist_clear(l->s.key);
		free(l->s.key);
		l->s.key = NULL;
	}
	free(l->s.comm);
	l->s.comm = NULL;
	if (l->s.avc) {
		alist_clear(l->s.avc);
		free(l->s.avc);
		l->s.avc = NULL;
	}
	free(l->s.acct);
	l->s.acct = NULL;
	l->s.arch = 0;
	l->s.syscall = 0;
	l->s.session_id = -2;
	l->s.exit = 0;
	l->s.exit_is_set = 0;
}

int list_get_event(llist* l, event *e)
{
	if (l == NULL || e == NULL)
		return 0;

	e->sec = l->e.sec;
        e->milli = l->e.milli;
        e->serial = l->e.serial;
	return 1;
}

lnode *list_find_msg(llist *l, int i)
{
        register lnode* window;
                                                                                
       	window = l->head;	/* start at the beginning */
	while (window) {
		if (window->type == i) {
			l->cur = window;
			return window;
		} else
			window = window->next;
	}
	return NULL;
}

lnode *list_find_msg_range(llist *l, int low, int high)
{
        register lnode* window;

	if (high <= low)
		return NULL;

       	window = l->head;	/* Start at the beginning */
	while (window) {
		if (window->type >= low && window->type <= high) {
			l->cur = window;
			return window;
		} else
			window = window->next;
	}
	return NULL;
}


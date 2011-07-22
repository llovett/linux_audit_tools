/*
* nvlist.h - Header file for nvlist.c
* Copyright (c) 2006-07 Red Hat Inc., Durham, North Carolina.
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

#ifndef NVLIST_HEADER
#define NVLIST_HEADER

#include "config.h"
#include "private.h"
#include <sys/types.h>
#include "rnode.h"
#include "ellist.h"


void nvlist_create(nvlist *l) hidden;
void nvlist_clear(nvlist* l) hidden;
static inline unsigned int nvlist_get_cnt(nvlist *l) { return l->cnt; }
static inline void nvlist_first(nvlist *l) { l->cur = l->head; }
static inline nvnode *nvlist_get_cur(const nvlist *l) { return l->cur; }
nvnode *nvlist_next(nvlist *l) hidden;
static inline const char *nvlist_get_cur_name(const nvlist *l) {return l->cur->name;}
static inline const char *nvlist_get_cur_val(const nvlist *l) {return l->cur->val;}
static inline const char *nvlist_get_cur_val_interp(const nvlist *l) {return l->cur->interp_val;}
int nvlist_get_cur_type(const rnode *r) hidden;
const char *nvlist_interp_cur_val(const rnode *r) hidden;
void nvlist_append(nvlist *l, nvnode *node) hidden;

/* Given a numeric index, find that record. */
int nvlist_find_name(nvlist *l, const char *name) hidden;

#endif


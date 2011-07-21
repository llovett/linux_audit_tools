/* aureport-scan.h -- 
 * Copyright 2011-2012 Oberlin College, Oberlin, OH.
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
 *   Luke Lovett <luke.lovett@cs.oberlin.edu>
 * 
 */


#ifndef AUREPORT_HT_H
#define AUREPORT_HT_H

#include "event.h"

int compar(const void *a, const void *b);
unsigned long hash(const char *key);
void event_to_key(char *key, event *e);

#endif

/*
* expression.h - Expression parsing and handling
* Copyright (C) 2008 Red Hat Inc., Durham, North Carolina.
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
*   Miloslav Trmač <mitr@redhat.com>
*/

#ifndef EXPRESSION_H__
#define EXPRESSION_H__

#include <regex.h>
#include <sys/types.h>

#include "internal.h"

enum {
	EO_NOT,			/* Uses v.sub[0] */
	EO_AND, EO_OR,		/* Uses v.sub[0] and v.sub[1] */
	/* All of the following use v.p */
	EO_RAW_EQ, EO_RAW_NE, EO_INTERPRETED_EQ, EO_INTERPRETED_NE,
	EO_VALUE_EQ, EO_VALUE_NE, EO_VALUE_LT, EO_VALUE_LE, EO_VALUE_GT,
	EO_VALUE_GE,
	/* Uses v.p.field.  Cannot be specified by an expression. */
	EO_FIELD_EXISTS,
	EO_REGEXP_MATCHES,	/* Uses v.regexp */
	NUM_EO_VALUES,
};

enum field_id {
	EF_TIMESTAMP, EF_RECORD_TYPE,
};

struct expr {
	unsigned op : 8;	/* EO_* */
	unsigned virtual_field : 1;
	/* Can be non-zero only if virtual_field != 0 */
	unsigned precomputed_value : 1;
	union {
		struct expr *sub[2];
		struct {
			union {
				char *name;
				enum field_id id; /* If virtual_field != 0 */
			} field;
			union {
				char *string;
				/* A member from the following is selected
				   implicitly by field.id. */
				struct {
					time_t sec;
					unsigned int milli;
				} timestamp; /* EF_TIMESTAMP */
				int int_value; /* EF_RECORD_TYPE */
			} value;
		} p;
		regex_t *regexp;
	} v;
};

/* Free EXPR and all its subexpressions. */
void expr_free(struct expr *expr) hidden;

/* Parse STRING.
   On success, return the parsed expression tree.
   On error, set *ERROR to an error string (for free()) or NULL, and return
   NULL.  (*ERROR == NULL is allowed to handle out-of-memory errors) */
struct expr *expr_parse(const char *string, char **error) hidden;

/* Create a comparison-expression for FIELD, OP and VALUE.
   On success, return the created expression.
   On error, set errno and return NULL. */
struct expr *expr_create_comparison(const char *field, unsigned op,
				    const char *value) hidden;

/* Create a \timestamp comparison-expression for with OP, SEC, MILLI.
   On success, return the created expression.
   On error, set errno and return NULL. */
struct expr *expr_create_timestamp_comparison(unsigned op, time_t sec,
					      unsigned milli) hidden;

/* Create an EO_FIELD_EXISTS-expression for FIELD.
   On success, return the created expression.
   On error, set errno and return NULL. */
struct expr *expr_create_field_exists(const char *field) hidden;

/* Create a \regexp expression for regexp comparison.
   On success, return the created expression.
   On error, set errno and return NULL. */
struct expr *expr_create_regexp_expression(const char *regexp) hidden;

/* Create a binary expresion for OP and subexpressions E1 and E2.
   On success, return the created expresion.
   On error, set errno and return NULL. */
struct expr *expr_create_binary(unsigned op, struct expr *e1, struct expr *e2)
	hidden;

/* Evaluate EXPR on RECORD in AU->le.
   Return 1 if EXPR is true, 0 if it false or if it fails.
   (No error reporting facility is provided; an invalid term is considered to
   be false; e.g. !invalid is true.) */
int expr_eval(auparse_state_t *au, rnode *record, const struct expr *expr)
	hidden;

#endif

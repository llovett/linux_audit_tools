#include "ausearch-llist.h"
#include <stdio.h>
#include <string.h>
#include "hashtab-util.h"

/**
 * event_to_key(char *key, event e)
 *
 * Store a hash key in 'key' for the event 'e'.
 * Note that 'key' must already be large enough to
 * hold the key.
 **/
void event_to_key(char *key, event *e) {
  snprintf(key, 20, "%d%d", e->sec, e->milli);
}

/**
 * int compar(const void *a, const void *b)
 * 
 * This is the comparator to test for equality
 * that the hashtable uses for removals.
 *
 * Since the hashtable will be returning indices
 * inside of the lol, our a and b here will be ints.
 **/

int compar(const void *a, const void *b) {
  int a2, b2;
  memcpy(&a2, a, sizeof(int));
  memcpy(&b2, b, sizeof(int));
  return a2 - b2;
}

/**
 * int hash(const char *key)
 * This is the hash function that runs the table.
 *
 * The key will be the concatenation of the number
 * of seconds and milliseconds stored in an event.
 **/

unsigned long hash(const char *key) {
  return atol(key);
}

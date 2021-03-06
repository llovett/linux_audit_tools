#ifndef HASHTAB_H
#define HASHTAB_H

#define LF_THRESH 0.75

static int PRIMES[] = { 53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593,
		      49157, 98317, 196613, 393241, 786433, 1572869, 3145739,
		      6291469, 12582917, 25165843, 50331653, 100663319,
		      201326611, 402653189, 805306457, 1610612741 };
static int PRIME_INDEX = 0;

/** Element in a chain of the table **/
typedef struct ht_entry {
  char key[256];
  void *datum;

  struct ht_entry *next, *prev;
} ht_entry;

/** A chain of the table **/
typedef struct hash_node {
  ht_entry *datum;
  int length;
} hnode;

typedef struct htable {
  hnode *array; /** Chains in the table **/
  int size;     /** Number of entries in the table **/
  int length;   /** Number of buckets in the table **/
  int (*compar)(const void *, const void *); /** Comparator function **/
  unsigned long (*hash)(const char *key); /** Hash function **/
} htable;

htable *ht_create(int size, 
		  int (*compar)(const void *, const void *),
		  unsigned long (*hash)(const char *));
int ht_resize(htable *table);
ht_entry *ht_insert(htable *table, ht_entry *entry);
ht_entry *ht_find(htable *table, const char *key);
ht_entry *ht_remove(htable *table, const char *key, const void *datum);
void ht_clear(htable *table);
void ht_destroy(htable *table);
void print_entry(const ht_entry *entry);

#endif

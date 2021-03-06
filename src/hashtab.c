/***
 * hashtab.c
 * 
 * A dynamically resizing hashtable with separate-chaining.
 * This table is designed with the idea that there will be
 * loads of collisions. For that reason, when you look up
 * a key in the table, a doubly-linked list of all entries
 * that hash to that key is returned, rather than just one
 * entry. It is up to you do search through this list to
 * find what you want. On the positive side, this allows you
 * to insert entries into the table that have exactly the
 * same key.
 *
 * It should be noted that the values for all entries in the
 * table are all dynamically allocated. This means that you
 * should not try to store anything less than 8 bytes, as
 * this will cause invalid reads when resizing the table.
 *
 * Author: Luke Lovett
 * 18 July 2011
 *
 * This software is distributed with ABSOLUTELY NO WARRANTY
 * under the GPLv3 license.
 *
 ***/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "hashtab.h"

/**
 * A mini-test program for demonstrating the table's usage
 * follows this comment, then function definitions for
 * the table itself.
 **/

// #define TABLE_SIZE 100

// int streq(const void *a, const void *b);
// int hash(const char *key);

/* int main(int argc, char *argv[]) { */

/*   // Parse arguments */
/*   if (argc < 2) { */
/*     fputs("USAGE: hashtab <file>\n", stderr); */
/*     return 1; */
/*   } */

/*   // Create the hash table */
/*   htable *table = ht_create(100, streq, hash); */
  
/*   // Parse the file that was supplied, and start */
/*   // inserting stuff into the table */
/*   FILE *INPUT = fopen(argv[1], "r"); */
/*   char key[256]; */
/*   int counter = 0; */
/*   while (fscanf(INPUT, "%s", key) > 0) { */
/*     // Create an entry to be inserted into the table. */
/*     ht_entry *entry = (ht_entry *)malloc(sizeof(ht_entry)); */

/*     // Copy over the key. */
/*     strncpy(entry->key, key, 255); */

/*     // This would be the part where you would allocate the */
/*     // memory necessary to store whatever it is you want to store. */
/*     // In this demo, we are storing int's, which are only 4 bytes long. */
/*     // Here, we expand that to 8 bytes, since memcpy is capable of */
/*     // copying only 8 bytes or more at a time. */
/*     entry->datum = malloc(8); */
/*     memcpy(entry->datum, &counter, sizeof entry->datum); */

/*     // This is where we insert 'entry' into the table. */
/*     ht_insert(table, entry); */

/*     counter++; */
/*   } */
  
/*   fclose(INPUT); */


/*   char *lookup = (char *)malloc(sizeof(char)*256); */
/*   fprintf(stdout, "Enter a key: "); */
/*   fscanf(stdin, "%s", lookup); */

/*   // Find an entry in the table. The LHS of this is */
/*   // going to be a doubly-linked list of all entries */
/*   // that match our string in "lookup". */
/*   ht_entry *result = ht_find(table, lookup); */

/*   if (NULL == result) */
/*     fprintf(stdout, "No results turned up for key %s.\n", lookup); */

/*   while (result) { */
/*     int res = 0; */
/*     memcpy(&res, result->datum, sizeof(int)); */
/*     fprintf(stdout, "Result: %d\n", res); */
/*     result = result->next; */
/*   } */

/*   // Deletion loop */
/*   int lookup_val; */
/*   int i; */
/*   for (i=0; i<sizeof(lookup); i++) */
/*     lookup[i] = (char)0; */
/*   lookup_val = 0; */

/*   fprintf(stdout, "Enter another key (for deletion): "); */
/*   fscanf(stdin, "%s", lookup); */
/*   fprintf(stdout, "Enter the value of that key (for deletion): "); */
/*   fscanf(stdin, "%d", &lookup_val); */

/*   // Aren't we losing memory here? */
/*   ht_entry *removed = ht_remove(table, lookup, &lookup_val); */
/*   if (removed) { */
/*     free(removed->datum); */
/*     free(removed); */
/*   } else { */
/*     fputs("Nothing to remove.", stderr); */
/*   } */
/*   puts("Printing chain of deleted item:"); */
/*   result = ht_find(table, lookup); */

/*   if (NULL == result) */
/*     fprintf(stdout, "No results turned up for key %s.\n", lookup); */

/*   while (result) { */
/*     int res = 0; */
/*     memcpy(&res, result->datum, sizeof(int)); */
/*     fprintf(stdout, "Result: %d\n", res); */
/*     result = result->next; */
/*   } */

/*   // Destroy the table */
/*   fputs("Destroying the table.", stderr); */

/*   // Destroy the table and clean up memory. */
/*   ht_destroy(table); */

/*   // Destroy the string we were using to do lookups. */
/*   free(lookup); */
  
/*   return 0; */
/* } */

// Simple comparator for strings
int streq(const void *a, const void *b) {
  char *a2 = (char *)a;
  char *b2 = (char *)b;
  
  return strcmp(a2, b2);
}

/**
 * ht_create(size, 
 *           int (*compar)(const void *, const void *),
 *           long (*hash)(const char *))
 *
 * Creates a new hash table with a size being a
 * convenient hashing prime number of at least 'size'.
 * "compar" is a pointer to a function returning an integer
 *  > 0 if the first argument is greater than the second,
 *  < 0 if the second argument is greater than the first,
 * == 0 if the two elements are "equal".
 * "hash" is a pointer to a hash function returning a
 * long unsigned integer.
 * 
 * Returns a pointer to the newly created hash table on success,
 *         NULL on error.
 **/
htable *ht_create(int size, 
		  int (*compar)(const void *, const void *),
		  unsigned long (*hash)(const char *)) {

  htable *table = (htable *)malloc(sizeof(htable));

  // Find a good table size.
  int tabsize = PRIMES[PRIME_INDEX];
  while (tabsize < size) {
    PRIME_INDEX++;
    tabsize = PRIMES[PRIME_INDEX];
  }

  // Allocate space for the table.
  tabsize *= sizeof(hnode);
  table->array = (hnode *)malloc(tabsize);

  if (! table->array) {
    fputs("Not enough memory.", stderr);
    return NULL;
  }

  // Initialize the table for use.
  table->length = PRIMES[PRIME_INDEX];
  table->size = 0;
  table->compar = compar;
  table->hash = hash;
  memset(table->array, 0, tabsize);
  
  int i;
  for (i=0; i<table->length; i++) {
    hnode *chain = &table->array[i];
    chain->length = 0;
  }
  
  return table;
}

/**
 * ht_resize
 *
 * Resizes table if necessary.
 *
 * Returns 1 if table was resized, 
 *         2 if no resize was necessary,
 *         0 if error.
 **/
int ht_resize(htable *table) {
  // Find the load factor
  double loadfactor = (double)table->size/(double)table->length;

  // Check to see if our table is getting too crowded.
  if (loadfactor >= LF_THRESH) {
    // Find our new size
    PRIME_INDEX++;

    if (PRIME_INDEX > sizeof(PRIMES)/sizeof(int)) {
      fputs("Hash table is already too big. Cannot resize.\n", stderr);
      return 0;
    }
    
    int newsize = PRIMES[PRIME_INDEX] * sizeof(hnode);

    // Make another array for the table
    htable temp;

    // Copy over the pointer to the hash function
    temp.hash = table->hash;
    hnode *arr = (hnode *)malloc(newsize);
    if (! arr) {
      fputs("Not enough memory to resize the hash table.\n", stderr);
      return 0;
    }


    // Initialize the new array for use.
    temp.array = arr;
    temp.length = PRIMES[PRIME_INDEX];
    temp.size = 0;
    memset(temp.array, 0, newsize);

    int i;
    for (i=0; i<temp.length; i++) {
      hnode *chain = &temp.array[i];
      chain->length = 0;
    }

    // Rehash the contents of the table
    for (i=0; i<table->length; i++) {
      hnode chain = table->array[i];
      if (chain.length == 0) continue;
      ht_entry *cur = chain.datum;
      while (NULL != cur) {

	ht_entry *entry = (ht_entry *)malloc(sizeof(ht_entry));

	strncpy(entry->key, cur->key, 256);

	// Copy over the data at cur->datum to
	// entry->datum. this seems much cleaner.
	entry->datum = malloc(sizeof cur->datum);
	memcpy(entry->datum, cur->datum, sizeof cur->datum);

	ht_insert(&temp, entry);

	cur = cur->next;
      }
    }

    ht_clear(table);
    free(table->array);
    table->array = temp.array;
    table->length = temp.length;

    return 1;
  }

  return 2;

}

/**
 * ht_insert(htable *table, ht_entry *entry)
 *
 * Insert entry into table.
 * Returns the inserted entry.
 **/
ht_entry *ht_insert(htable *table, ht_entry *entry) {
  // Get the bucket that the entry hashes to.
  long bucket = (*table->hash)(entry->key) % table->length;

  // Get the chain for that bucket.
  ht_entry *chain = table->array[bucket].datum;

  // Put our new entry at the head of the chain.
  // If the chain does not yet exist, then create
  // it starting with our new entry.
  if (! chain) {
    chain = entry;
    entry->next = NULL;
    entry->prev = NULL;
    table->array[bucket].datum = chain;
  }
  else {
    entry->next = chain;
    entry->prev = NULL;
    chain->prev = entry;
    table->array[bucket].datum = entry;
    chain = entry;
  }

  table->size++;
  table->array[bucket].length++;

  // Check to see if the table should be resized.
  ht_resize(table);

  // Return the head of the chain.
  return chain;
}

/**
 * ht_find(hnode *table, char *key)
 *
 * Find all entries in the table matching the given key.
 *
 * Returns a doubly-linked list of all things matching the key, or
 *         NULL if nothing matches
 **/
ht_entry *ht_find(htable *table, const char *key) {
  long bucket = (*table->hash)(key) % table->length;

  if (0 == table->array[bucket].length) return NULL;
  return table->array[bucket].datum;
}

/**
 * ht_remove(htable *table, char *key, void *datum)
 *
 * Removes the entry in table matching specified
 * key and datum. The comparator function supplied in ht_create
 * is used to make equality assessments.
 *
 * Returns the entry removed, or
 *         NULL, if nothing matches the key and datum
 **/
ht_entry *ht_remove(htable *table, const char *key, const void *datum) {
  long bucket = (*table->hash)(key) % table->length;
  hnode *chain = &table->array[bucket];

  // There is nothing to remove
  if (0 == chain->length)
    return NULL;

  ht_entry *cur = chain->datum;
  while (NULL != cur) {
    if (cur->datum) {

      // Use the table's comparator to find the appropriate entry
      if (0 == (*table->compar)(cur->datum, datum)) {

	if (cur->prev)
	  cur->prev->next = cur->next;
	// If there is no previous element, we should adjust the pointer
	// in our hnode.
	else
	  chain->datum = cur->next;

	if (cur->next)
	  cur->next->prev = cur->prev;
	return cur;
      }
    }
    cur = cur->next;
  }

  // Nothing matched
  return NULL;
}


/**
 * ht_clear(hnode *table)
 *
 * Clears out all the entries from the table,
 * but still leaves the table and its buckets intact.
 *
 **/
void ht_clear(htable *table) {
  int i;

  // Go through each bucket of the hash table (hnode)
  for (i=0; i<table->length; i++) {
    hnode chain = table->array[i];

    // If this hnode has no entries, continue on.
    if (0 == chain.length) continue;

    // Go through each entry in this hnode and free up the memory
    ht_entry *cur = chain.datum;

    while (cur) {
      ht_entry *buff = cur;
      cur = cur->next;
      free(buff->datum);
      free(buff);
    }
  }
}

/**
 * ht_destroy(hnode *table)
 *
 * Destroys and frees all the memory used by table.
 **/
void ht_destroy(htable *table) {
  // Free all the entries in the table.
  ht_clear(table);

  // Free the chains of the table.
  free(table->array);
  
  // Free the table itself
  free(table);
}

/**
 * Prints an entry in the hash table.
 **/
void print_entry(const ht_entry *entry) {
  int res = 0;
  memcpy(&res, entry->datum, sizeof(int));
  fprintf(stdout, "ENTRY : < %s : %d >\n", (char *)entry->key, res);
}

/* /\** */
/*  * The hash function itself, a pointer to */
/*  * which lives inside of the hash table. */
/*  **\/ */
/* int hash(const char *key) { */
/*   int ret = 0; */

/*   // Dumbest hash function EVER. */
/*   // For testing purposes only. */
/*   int i; */
/*   for (i=0; i<strlen(key); i++ ) */
/*     ret += (int)key[i]; */
  
/*   return ret; */
/* } */

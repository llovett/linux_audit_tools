/***
 * queue.c
 *  
 * A simple queue.
 *
 * Author: Luke Lovett
 * 18 July 2011
 *
 * This software is distributed with ABSOLUTELY NO WARRANTY
 * under the GPLv3 license.
 *
 ***/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

/**
 * queue_create(void)
 *
 * Constructs a queue.
 * Returns a pointer to the newly created queue on success,
 *         NULL if failure.
 **/
queue *queue_create(void) {
  queue *q = (queue *)malloc(sizeof(queue));

  q->size = 0;
  q->front = NULL;
  q->back = NULL;
  
  return q;
}

/**
 * queue_pop(queue *q)
 *
 * Pops off and returns the front element of q.
 * The caller of this function becomes resposible for the memory of
 * the item returned.
 *
 * Returns NULL if failure.
 **/
void *queue_pop(queue *q) {
  if (0 == q->size) return NULL;

  queue_el *ret = q->front;

  if (ret->next)
    ret->next->prev = NULL;

  q->front = ret->next;
  q->size--;

  if (0 == q->size)
    q->back = NULL;

  void *val = ret->datum;
  free(ret);

  return val;
}

/**
 * queue_push(queue *q, void *datum)
 *
 * Pushes datum onto the back of q.
 * Returns a pointer to datum in the queue if successful,
 *         NULL, otherwise.
 **/
void *queue_push(queue *q, void *datum) {
  if (! q) {
    fprintf(stdout, "THERE IS NO QUEUE TO PUSH ONTO!!!");
    return NULL;
  }
  queue_el *qel = (queue_el *)malloc(sizeof(queue_el));

  if (! qel) {
    fputs("Not enough memory to add to the queue.", stderr);
    return NULL;
  }

  qel->datum = malloc(sizeof datum);

  if (! qel->datum) {
    fputs("Not enough memory to add to the queue.", stderr);
    free(qel);
    return NULL;
  }

  memcpy(qel->datum, datum, sizeof datum);
  qel->next = NULL;

  if (NULL == q->back) {
    q->back = qel;
    q->front = qel;
    
    qel->prev = NULL;
  }
  else {
    q->back->next = qel;
    qel->prev = q->back;
    q->back = qel;
  }

  q->size++;

  return q->back;
}

/**
 * queue_destroy(queue *q)
 *
 * Destroys and frees the memory used by q.
 **/
void queue_destroy(queue *q) {
  queue_el *cur = q->front;

  /** Remove all the elements in the queue **/
  while (cur) {
    queue_el *buff = cur;
    cur = cur->next;

    free(buff->datum);
    free(buff);

    puts("Bing!");
  }

  /** Destroy the queue itself **/
  free(q);
}

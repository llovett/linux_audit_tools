/***
 * queue.h
 *  
 * A simple queue (header file).
 *
 * Author: Luke Lovett
 * 18 July 2011
 *
 * This software is distributed with ABSOLUTELY NO WARRANTY
 * under the GPLv3 license.
 *
 ***/

#ifndef QUEUE_H
#define QUEUE_H

/** structure defining a queue **/
typedef struct queue_list {
  int size;
  struct queue_el *front, *back;
} queue;

/** structure defining an element of the queue **/
typedef struct queue_el {
  void *datum;
  struct queue_el *next, *prev;
} queue_el;

queue *queue_create(void);
void *queue_pop(queue *q);
void *queue_push(queue *q, void *datum);
void queue_destroy(queue *q);

#endif

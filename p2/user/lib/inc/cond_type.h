/** @file cond_type.h
 *  @brief This file defines the type for condition variables.
 */

#ifndef _COND_TYPE_H
#define _COND_TYPE_H

typedef struct node{

  int tid;
  int *oldflag;
  struct node *next;

} node_t;


typedef struct cond {

  int valid; //verifies if the cv should be used
  node_t *qhead;
  node_t *qtail;


} cond_t;

#endif /* COND_TYPE_H */

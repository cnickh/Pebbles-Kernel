/** @file mutex_type.h
 *  @brief This file defines the type for mutexes.
 */

#ifndef _MUTEX_TYPE_H
#define _MUTEX_TYPE_H


typedef struct mutex {
  unsigned int valid; //Determines if lock its valid and should be repected
  int holder; //gets called if lock is tried and not available

} mutex_t;

#endif /* _MUTEX_TYPE_H */

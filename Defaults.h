/*
 * Defaults.h
 *
 *  Created on: Apr 25, 2014
 *      Author: jp
 */

#ifndef DEFAULTS_H_
#define DEFAULTS_H_

#define PATH "/home/"

#define PROCESS_NAME "Visitor"

#define DOORS_AMOUNT 3
#define DOORS_SEMAPHORE_ID 14
#define MUTEX_ID DOORS_SEMAPHORE_ID+1
#define SHARED_MEMORY_ID MUTEX_ID+1

#define SLEEP_TIME_MAX 5
#define SLEEP_TIME_MIN 3
#endif /* DEFAULTS_H_ */

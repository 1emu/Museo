/*
 * Defaults.h
 *
 *  Created on: Apr 25, 2014
 *      Author: jp
 */

#ifndef DEFAULTS_H_
#define DEFAULTS_H_

#define PATH "/home/"

#define PRODUCER_PROCESS_NAME "Agent"
#define CONSUMER_PROCESS_NAME "Smoker"

#define PAPER_SEMAPHORE_ID 14
#define TOBACO_SEMAPHORE_ID PAPER_SEMAPHORE_ID+1
#define MATCHES_SEMAPHORE_ID TOBACO_SEMAPHORE_ID+1

#define AMOUNT_OF_SMOKERS 1
#define AMOUNT_OF_AGENTS 1

#define SLEEP_TIME_MAX 5
#define SLEEP_TIME_MIN 3
#endif /* DEFAULTS_H_ */

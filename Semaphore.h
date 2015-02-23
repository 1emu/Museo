/*
 * Semaphore.h
 *
 *  Created on: Feb 22, 2015
 *      Author: jp
 */

#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

#include "SemaphoreArray.h"

class Semaphore {
private:
    SemaphoreArray * semArr;
    int index;
    unsigned int identifier;
public:
    Semaphore(unsigned int identifier);
    Semaphore(SemaphoreArray * semArr, int index);
    void get();
    void destroy();
    void wait();
    void post();
};

#endif /* SEMAPHORE_H_ */

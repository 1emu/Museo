/*
 * Semaphore.cpp
 *
 *  Created on: Feb 22, 2015
 *      Author: jp
 */

#include "Semaphore.h"
#include "SemaphoreArray.h"

Semaphore::Semaphore(unsigned int identifier) {
    this->index = 0;
    this->identifier = identifier;
    semArr = SemaphoreArray::create(identifier);
}

void Semaphore::get(void)
{
    semArr->get(identifier);
}

void Semaphore::destroy(void)
{
    semArr->destroy(identifier, 1);
}

void Semaphore::post(void)
{
    semArr->post(index);

}

void Semaphore::wait(void)
{
    semArr->wait(index);
}

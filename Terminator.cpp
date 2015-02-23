/*
 * Terminator.cpp
 *
 *  Created on: May 4, 2014
 *      Author: jp
 */

#include "Includes.h"
#include "SemaphoreArray.h"
#include "SharedMemory.h"

int main(){
	SemaphoreArray::destroy(DOORS_SEMAPHORE_ID);
	SemaphoreArray::destroy(MUTEX_ID);
	SharedMemory::destroy(SHARED_MEMORY_ID, sizeof(Museum));
    std::string msg = "Termination complete.";
    Colors::writeout(msg, UNDERLINEDGREEN);
    return 0;
}




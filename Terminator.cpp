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
	SemaphoreArray::destroy(PAPER_SEMAPHORE_ID);
	SemaphoreArray::destroy(TOBACO_SEMAPHORE_ID);
	SemaphoreArray::destroy(MATCHES_SEMAPHORE_ID);
    std::string msg = "Termination complete.";
    Colors::writeout(msg, UNDERLINEDGREEN);
    return 0;
}




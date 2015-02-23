/*
 * SharedMemory.cpp
 *
 *  Created on: May 12, 2014
 *      Author: jp
 */

#include "SharedMemory.h"

SharedMemory::SharedMemory() {
	this->id = -1;
	this->sharedMemoryId = -1;
	this->attached = false;
	this->attachAddress = NULL;
}

SharedMemory::~SharedMemory() {
    //dettach();
}


void* SharedMemory::create(unsigned int id, unsigned int size){
	SharedMemory* newSharedMemory = new SharedMemory();
	key_t key = ftok(PATH, id);
	if (key == -1)	{
		notifyError(id, "create - ftok");
		exit(EXIT_FAILURE);
	}
	else {
		int sharedMemoryId = shmget(key, size, IPC_CREAT | IPC_EXCL | 0660);
		if (sharedMemoryId == -1) {
            notifyError(id, "create - shmget");
			exit(EXIT_FAILURE);
		}
		newSharedMemory->setId(id);
		newSharedMemory->setSharedMemoryId(sharedMemoryId);
	}
    return newSharedMemory->attach();
}

void* SharedMemory::get(unsigned int id, unsigned int size){
	SharedMemory* newSharedMemory = new SharedMemory();
	int sharedMemoryId = getSharedMemoryId(id, size);
	newSharedMemory->setId(id);
	newSharedMemory->setSharedMemoryId(sharedMemoryId);
    return newSharedMemory->attach();
}

void SharedMemory::destroy(int id, unsigned int size){
	int sharedMemoryId = getSharedMemoryId(id, size);
    int removeResult = shmctl(sharedMemoryId, IPC_RMID, (struct shmid_ds*) 0);
	bool removeFailed = removeResult == -1;
	if (removeFailed) {
		notifyError(id, "destroy");
	}
}

void SharedMemory::setSharedMemoryId(unsigned int sharedMemoryId){
	this->sharedMemoryId = sharedMemoryId;
}

void* SharedMemory::attach() {
	if (!attached) {
		attachAddress = shmat(sharedMemoryId, 0, 0);
		if (attachAddress == (void *) - 1) {
			notifyError(id, "attach");
		}
		attached = true;
	}
	return attachAddress;
}

void SharedMemory::dettach() {
	if (attached){
		if (shmdt(attachAddress) == -1){
			notifyError(id, "dettach");
		}
		attached = false;
	}
}

void SharedMemory::setId(unsigned int id){
	this->id = id;
}

int SharedMemory::getSharedMemoryId(unsigned int id, unsigned int size) {
	int sharedMemoryIdTemp;
	key_t key = ftok(PATH, id);
	if (key == -1)	{
		notifyError(id, "getSharedMemoryId - ftok");
		exit(EXIT_FAILURE);
	}
	else {
        sharedMemoryIdTemp = shmget(key, size, 0660);
		if (sharedMemoryIdTemp == -1) {
            notifyError(id, "getSharedMemoryId - shmget");
			exit(EXIT_FAILURE);
		}
	}
	return sharedMemoryIdTemp;
}

void SharedMemory::notifyError(unsigned int id, std::string failingMethod){
	std::string msg = "Error on sharedMemory with id #";
	msg = msg + Utils::intToString(id) + " when trying to " + failingMethod;
	Colors::writeerr(msg, RED);
}




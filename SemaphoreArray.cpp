/*
 * SemaphoreArray.cpp
 *
 *  Created on: May 8, 2014
 *      Author: jp
 */

#include "SemaphoreArray.h"

SemaphoreArray::SemaphoreArray() {
	this->id = -1;
	this->semaphoreArrayId = -1;

}

SemaphoreArray::~SemaphoreArray() {
	// TODO Auto-generated destructor stub
}

SemaphoreArray* SemaphoreArray::create(unsigned int id, unsigned int size,
		unsigned int* initStatus) {
	SemaphoreArray* newSemaphoreArray = new SemaphoreArray();
	key_t key = ftok(PATH, id);
	if (key == -1)	{
		notifyError(id, "create - ftok");
		exit(EXIT_FAILURE);
	} else {
		int semaphoreArrayId = semget(key, size, IPC_CREAT | IPC_EXCL | PERMISSIONS);
		if (semaphoreArrayId == -1) {
			notifyError(id, "create - semget");
			exit(EXIT_FAILURE);
		}
		newSemaphoreArray->setId(id);
		newSemaphoreArray->setSemaphoreArrayId(semaphoreArrayId);
		newSemaphoreArray->init(size, initStatus);
	}
	return newSemaphoreArray;
}

// for mutex creation.
SemaphoreArray *SemaphoreArray::create(unsigned int id)
{
    unsigned int size = 1;
    unsigned int initVector[1] = {1};
    return create(id, size, initVector);
}

SemaphoreArray* SemaphoreArray::get(unsigned int id, unsigned int size) {
	SemaphoreArray* newSemaphoreArray = new SemaphoreArray();
	int semaphoreArrayId = getSemaphoreArrayId(id, size);
	newSemaphoreArray->setId(id);
	newSemaphoreArray->setSemaphoreArrayId(semaphoreArrayId);
	return newSemaphoreArray;
}

SemaphoreArray* SemaphoreArray::get(unsigned int id) {
	unsigned int size = 1;
	return get(id, size);
}

void SemaphoreArray::init(unsigned int size, unsigned int* initStatus) {
	union semun {
        int val;
        struct semid_ds *buf;
        unsigned short *array;
        struct seminfo *__buf;
    } arg;
	for (unsigned int sem = 0; sem < size; ++sem) {
		arg.val = initStatus[sem];
		int e = semctl(semaphoreArrayId, sem, SETVAL, arg);
		if(e == -1) {
			std::string failingMethod = "init - ";
			failingMethod = failingMethod + "on index: " + Utils::intToString(sem);
			notifyError(id, failingMethod);
		}
	}
}

void SemaphoreArray::setSemaphoreArrayId(int id) {
	this->semaphoreArrayId = id;
}

void SemaphoreArray::destroy(unsigned int id) {
	destroy(id, 1);
}

void SemaphoreArray::destroy(unsigned int id, unsigned int size) {
	int semaphoreArrayId = getSemaphoreArrayId(id, size);
	int removeResult = semctl(semaphoreArrayId, IPC_RMID, NULL);
	bool removeFailed = removeResult == -1;
	if (removeFailed) {
		notifyError(id, "destroy");
	}
}

void SemaphoreArray::setId(int id) {
	this->id = id;
}

unsigned int SemaphoreArray::getSemaphoreArrayId(unsigned int id, unsigned int size) {
	int semaphoreArrayIdTemp;
	key_t key = ftok(PATH, id);
	if (key == -1)	{
		notifyError(id, "getSemaphoreId - ftok");
		exit(EXIT_FAILURE);
	}
	else {
		semaphoreArrayIdTemp = semget(key, size , PERMISSIONS);
		if (semaphoreArrayIdTemp == -1) {
			notifyError(id, "getSemaphoreId - semget");
			exit(EXIT_FAILURE);
		}
	}
	return semaphoreArrayIdTemp;
}

void SemaphoreArray::wait(unsigned int index) {
	struct sembuf oper;
	oper.sem_num = index;
	oper.sem_op = -1;
	oper.sem_flg = 0;
	int e = semop(semaphoreArrayId, &oper, 1);
	if(e == -1) {
		std::string failingMethod = "wait - ";
		failingMethod = failingMethod + "on index: " + Utils::intToString(index);
		notifyError(id, failingMethod);
	}
}

void SemaphoreArray::post(unsigned int index) {
	 struct sembuf oper;
	oper.sem_num = index;
	oper.sem_op = 1;
	oper.sem_flg = 0;
	int e = semop(semaphoreArrayId, &oper, 1);
	if(e == -1) {
		std::string failingMethod = "post - ";
		failingMethod = failingMethod + "on index: " + Utils::intToString(index);
		notifyError(id, failingMethod);
	}
}

void SemaphoreArray::notifyError(int id, std::string failingMethod) {
	std::string msg = "Error on SemaphoreArray with id #";
	msg = msg + Utils::intToString(id) + " when trying to " + failingMethod;
	Colors::writeerr(msg, RED);
}

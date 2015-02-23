/*
 * SemaphoreArray.h
 *
 *  Created on: May 8, 2014
 *      Author: jp
 */

#ifndef SEMAPHOREARRAY_H_
#define SEMAPHOREARRAY_H_

#ifndef PERMISSIONS
#define PERMISSIONS 0660
#endif

#include "Includes.h"

class SemaphoreArray {
public:
	SemaphoreArray();
	virtual ~SemaphoreArray();
	static SemaphoreArray* create(unsigned int id,unsigned int size, unsigned int* initStatus);
	static SemaphoreArray* get(unsigned int id, unsigned int size);

	/* We redefine create, get and destroy for a mutex */
	static SemaphoreArray* create(unsigned int id);
	static SemaphoreArray* get(unsigned int id);
	static void destroy(unsigned int id);

	/* Defaults are for mutex */
	void wait(unsigned int index = 0);
	void post(unsigned int index = 0);

	static void destroy(unsigned int id, unsigned int size);
private:
	int semaphoreArrayId;
	int id;
	void setSemaphoreArrayId(int id);
	void setId(int id);
	void init(unsigned int size, unsigned int* initStatus);
	static unsigned int getSemaphoreArrayId(unsigned int id, unsigned int size);
	static void notifyError(int id, std::string failingMethod);
};

#endif /* SEMAPHOREARRAY_H_ */

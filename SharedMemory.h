/*
 * SharedMemory.h
 *
 *  Created on: May 12, 2014
 *      Author: jp
 */

#ifndef SHAREDMEMORY_H_
#define SHAREDMEMORY_H_

#include "Includes.h"

class SharedMemory {
public:

    virtual ~SharedMemory();
    static void* create(unsigned int id, unsigned int size);
    static void* get(unsigned int id, unsigned int size);
	static void destroy(int id, unsigned int size);

private:
	int sharedMemoryId;
	int id;
	bool attached;
	void* attachAddress;
    SharedMemory();
    void* attach();
    void dettach();
	static int getSharedMemoryId(unsigned int id, unsigned int size);
	static void notifyError(unsigned int id, std::string failingMethod);
	void setSharedMemoryId(unsigned int sharedMemoryId);
	void setId(unsigned int id);
};

#endif /* SHAREDMEMORY_H_ */

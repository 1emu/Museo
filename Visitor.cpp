/*
 * Visitor.cpp
 *
 * Created on: Feb 20, 2015
 * Author: jp
 */

#include "Includes.h"
#include "SemaphoreArray.h"
#include "SharedMemory.h"

using namespace std;

void outputMuseumStatus(int id, Museum* museum) {
	string museumStatus = "Museum status [";
	museumStatus += Utils::intToString(museum->inside);
	museumStatus += "/";
	museumStatus += Utils::intToString(museum->capacity);
	museumStatus += "];";
	Process::announce(PROCESS_NAME, id, GREEN, museumStatus.c_str());
}

int main(int argc, char** argv) {

	char* processName = argv[0];
	string id_str;
	int id = getpid();

	// Si se ingresan menos argumentos de los necesarios
	if (argc < 3) {
		string msg = "Usage ";
		msg = msg + processName + " <first visitor ? 1|0> <door number>\n";
		Colors::writeerr(msg, RED);
		exit(EXIT_FAILURE);
	}

	int isFirstVisitor = atoi(argv[1]);
	int doorNumber = atoi(argv[2]);

	Process::announce(PROCESS_NAME, id, UNDERLINEDGREEN, "initializing.");

	srand(time(NULL) * id);

	unsigned int initialState[DOORS_AMOUNT] = {0, 0, 0,};

	if(isFirstVisitor){
		SemaphoreArray::create(DOORS_SEMAPHORE_ID, DOORS_AMOUNT, initialState);
		SemaphoreArray::create(MUTEX_ID);
		SharedMemory::create(SHARED_MEMORY_ID, sizeof(Museum));

	}

	SemaphoreArray* doors = SemaphoreArray::get(DOORS_SEMAPHORE_ID, DOORS_AMOUNT);
	SemaphoreArray* mutex = SemaphoreArray::get(MUTEX_ID);
	Museum* museum = (Museum*) SharedMemory::get(SHARED_MEMORY_ID, sizeof(Museum));

	if(isFirstVisitor){
		museum->capacity= 2;
		museum->inside = 0;
		museum->last = -1;
	}

	Process::announce(PROCESS_NAME, id, UNDERLINEDGREEN, "ipcs succesfully created.");

	Process::announce(PROCESS_NAME, id, YELLOW, "trying to get inside.");
	mutex->wait();

	outputMuseumStatus(id, museum);

	if(museum->capacity > museum-> inside) {
		museum->inside++;
		mutex->post();
	} else{
		string waitMessage = "Cannot enter: waiting at door " + Utils::intToString(doorNumber);
		Process::announce(PROCESS_NAME, id, YELLOW, waitMessage.c_str());
	 	museum->queue[doorNumber]++;
	  	mutex->post();
	  	doors->wait(doorNumber);
	}

	Process::announce(PROCESS_NAME, id, UNDERLINEDYELLOW, "got inside");

	sleep(Process::sleepTime()); //visit

	mutex->wait();

	museum->inside--;

	for(int i = (museum->last+1)%3, j = 0; j < 3; i=(i+1)%3, j++){
		if(museum->queue[i] > 0 and museum->capacity > museum->inside){
			string exitMessage = "Exiting through door " + Utils::intToString(doorNumber);
			Process::announce(PROCESS_NAME, id, YELLOW, exitMessage.c_str());
			museum->queue[i]--;
			doors->post(i);
			museum->inside++;
			museum->last = i;
		}
	}

	outputMuseumStatus(id, museum);
	mutex->post();

	Process::announce(PROCESS_NAME, id, UNDERLINEDGREEN, "finished.");
	return 0;
}

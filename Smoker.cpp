/*
 * Smoker.cpp
 *
 * Created on: Feb 20, 2015
 * Author: jp
 */

#include "Includes.h"
#include "SemaphoreArray.h"
#include "SharedMemory.h"

using namespace std;

int main(int argc, char** argv) {

	char* processName = argv[0];
	string id_str;

	int id = getpid();
	Process::announce(CONSUMER_PROCESS_NAME, id, UNDERLINEDPURPLE, "initializing.");

	srand(time(NULL) * id);

	SemaphoreArray* paper = SemaphoreArray::get(PAPER_SEMAPHORE_ID);
	SemaphoreArray* tobaco = SemaphoreArray::get(TOBACO_SEMAPHORE_ID);
	SemaphoreArray* matches = SemaphoreArray::get(MATCHES_SEMAPHORE_ID);

	Process::announce(CONSUMER_PROCESS_NAME, id, UNDERLINEDPURPLE, "waiting for input to continue...");
	string res;
	while(cin>>res){

		Process::announce(CONSUMER_PROCESS_NAME, id, PURPLE, "waiting for paper...");
		paper->wait();
		Process::announce(CONSUMER_PROCESS_NAME, id, PURPLE, "waiting for tobaco...");
		tobaco->wait();
		Process::announce(CONSUMER_PROCESS_NAME, id, PURPLE, "waiting for matches...");
		matches->wait();

		string cigar =
				"\n";
		cigar += 	"                   (  )\n";
		cigar +=	"                    )(\n" ;
		cigar += 	" ________________  ( )\n" ;
		cigar += 	"()__)____________)))))  ";
		cigar +=    "\n";

		Process::announce(CONSUMER_PROCESS_NAME, id, PURPLE, cigar.c_str());
		Process::announce(CONSUMER_PROCESS_NAME, id, UNDERLINEDPURPLE, "waiting for input to smoke again...");

	}

	Process::announce(CONSUMER_PROCESS_NAME, id, UNDERLINEDPURPLE, "finished.");
	return 0;
}


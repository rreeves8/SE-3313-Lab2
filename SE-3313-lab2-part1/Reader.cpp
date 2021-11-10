#include <iostream>
#include "SharedObject.h"

using namespace std;

struct SharedMemoryObject{
	int threadID;
	int reportID;
	int elapsedTime;
};

int main(void){
	std::cout << "I am a reader" << std::endl;
	
	//get a refernece to the stored memory
	Shared<SharedMemoryObject> sharedMemory("sharedMemory");

	while(1){ //run forever until someone kills the terminal
		cout<< //print the shared memory every second
			"Thread ID: " << sharedMemory->threadID << " "
			"Report ID: " << sharedMemory->reportID << " "
			"Elapsed Time " << sharedMemory->elapsedTime << endl;

		sleep(1);
	}

}

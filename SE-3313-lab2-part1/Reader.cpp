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
	
	Shared<SharedMemoryObject> sharedMemory("sharedMemory");

	while(1){
		cout<< 
			"Thread ID: " << sharedMemory->threadID << " "
			"Report ID: " << sharedMemory->reportID << " "
			"Elapsed Time " << sharedMemory->elapsedTime << endl;

		sleep(3);
	}

}

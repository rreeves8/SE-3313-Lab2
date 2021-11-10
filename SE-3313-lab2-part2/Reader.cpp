#include <iostream>
#include "SharedObject.h"

using namespace std;

//the semaphore for stopping changes to the SharedMemoryObject
Semaphore writeSemaphore("writeSemaphore", 1, true);
	
//the semaphore for notifying of changes
Semaphore notifySemaphore("notifySemaphore", 1, true);	

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
		
		//tell other threads to wait the shared memory is being read
		writeSemaphore.wait();
		notifySemaphore.wait();
		
		cout<< //print the shared memory every second
			"Thread ID: " << sharedMemory->threadID << " "
			"Report ID: " << sharedMemory->reportID << " "
			"Elapsed Time " << sharedMemory->elapsedTime << endl;

		sleep(1);
		
		//signal other threads its finished being read
		writeSemaphore.Signal();
	}

}

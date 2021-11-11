#include <iostream>
#include "SharedObject.h"
#include "Semaphore.h"

using namespace std;



struct SharedMemoryObject{
	int threadID;
	int reportID;
	int elapsedTime;
};

int main(void){
	std::cout << "I am a readerr" << std::endl;
	
	//get a refernece to the stored memory
	Shared<SharedMemoryObject> sharedMemory("sharedMemory");
	//the semaphore for stopping changes to the SharedMemoryObject
	Semaphore writeSemaphore("writeSemaphore", 1, false);
	
	//the semaphore for notifying of changes
	Semaphore notifySemaphore("notifySemaphore", 1, false);	

	while(true){ //run forever until someone kills the terminal
		
		//tell other threads to wait the shared memory is being read
		notifySemaphore.Wait();
		writeSemaphore.Wait();
		cout<< //print the shared memory every second
			"Thread ID: " << sharedMemory->threadID << " "
			"Report ID: " << sharedMemory->reportID << " "
			"Elapsed Time " << sharedMemory->elapsedTime << endl;
		
		//signal other threads its finished being read
		writeSemaphore.Signal();
	}

}

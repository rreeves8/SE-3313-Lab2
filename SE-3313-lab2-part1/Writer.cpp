#include <iostream>
#include <sstream>
#include "thread.h"
#include "SharedObject.h"

using namespace std;

struct SharedMemoryObject{
	int threadID;
	int reportID;
	int elapsedTime;
};

class WriterThread : public Thread{
	public:
		int 	threadNum; //the thread number
		int 	threadReported; //the number of times reported
		int 	delay; //the delay time
		bool	flag;
		
		WriterThread(int threadNum, int delay):Thread(8*1000){ //constructor for a new thread taking the number and its delay time
			this->threadNum = threadNum; //or whatever you want/need here
			this->delay = delay;
			this->threadReported = 0;
		}

		virtual long ThreadMain(void) override{ //the thread method to run
			//declare shared memory var so this thread can access it
			Shared<SharedMemoryObject> sharedMemory ("sharedMemory");
			
			while(true){ // store values in shared, then sleep, if flag detected kill loop
				sharedMemory->threadID = this->threadNum;
				sharedMemory->reportID = threadReported++;
				sharedMemory->elapsedTime = delay;

				sleep(delay);
				
				if(flag){ //Exit loop to end the thread
					break;
				}
			}
		}
};

int main(void){
	cout << "I am a Writer" << std::endl;

	int threadCount = 0; //thread counter
	Shared<SharedMemoryObject> shared("sharedMemory", true); //This is the owner of sharedMamory
	vector<WriterThread*> threads; //store a reference to each thread

	while(true){
		string input;
		cout << "Would you like to create a new thread?" << endl; 
		cin >> input;
		
		if(!input.compare("yes")){
			int N;
			cout << "Enter sleep time" << endl;
			cin >> N; //get delay input

			WriterThread* newThread = new WriterThread(++threadCount, N); //create new thread and pass new variables
			threads.push_back(newThread); //store new threas

		}
		else{//if input not yes kill threads
			for(WriterThread* currentThread : threads){
				currentThread->flag = true;
				delete currentThread;
			}
			break;
		}	
	}
	//example for one thread thread1

}



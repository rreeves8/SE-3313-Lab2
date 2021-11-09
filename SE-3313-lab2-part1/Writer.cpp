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
		int 	threadNum;
		int 	threadReported;
		int 	delay;
		bool	flag;
		
		WriterThread(int threadNum, int delay):Thread(8*1000){
			this->threadNum = threadNum; //or whatever you want/need here
			this->delay = delay;
			this->threadReported = 0;
		}

		virtual long ThreadMain(void) override{
			
			//declare shared memory var so this thread can access it
			Shared<SharedMemoryObject> sharedMemory ("sharedMemory");
			while(true){
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

	int threadCount;
	Shared<SharedMemoryObject> shared("sharedMemory", true); //This is the owner of sharedMamory
	vector<WriterThread*> threads;

	while(true){
		string input;
		cout << "Would you like to create a new thread?" << endl;
		cin >> input;
		
		if(!input.compare("yes")){
			int N;
			cout << "Enter sleep time" << endl;
			cin >> N;

			WriterThread* newThread = new WriterThread(++threadCount, N);

		}
		else{
			for(WriterThread* currentThread : threads){
				currentThread->flag = true;
				delete currentThread;
			}
		}	
	}
	//example for one thread thread1

}



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

int main(void){
    cout << "I am a Writer" << std::endl;

    int threadCount;
    Shared<SharedMemoryObject> shared("sharedMemory", true); //This is the owner of sharedMamory
    vector<WriterThread*> threads;

    while(true){
        char input;
        cout << "Would you like to create a new thread?" << endl;
        cin >> input;
        
        if(input == 'yes'){
            int N;
            cout << "Enter sleep time" << endl;
            cin >> N;

            WriterThread* newThread = new WriterThread(++threadCount, N);

        }
        else{
            for(WriterThread* currentThread : threads){
                currentThread -> flag = true;
                delete currentThread;
            }
        }   
    }
    //example for one thread thread1

}



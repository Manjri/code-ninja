#include <pthread.h>
#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

//global queue
std::queue<string> str_q;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;


void* print(void* arg){

    while(true){

        pthread_mutex_lock(&lock);
        while(str_q.empty()){
            pthread_cond_wait(&cond, &lock); //while nothing in queue, just wait 
            /* this instruction does following internally: wait()
            it unlocks the lock and moves the thread to blocked state(sleep) from ready state. so some one else can take this
            mutex.
            when someone signals this cond var, the thread will come out of sleep. then this thread will acquire this lock to
            enter cs..

            just assume that once i come out of this wait: i am holding the lock and someone has siganled me to wake up.
            check if q is empty. dont asusme it is not empty
            */
        }

        string tp = str_q.front();
        str_q.pop();
        cout << "hello  " << tp << endl;
        pthread_mutex_unlock(&lock);
    }
    return nullptr;
}

int main(){

    //main trhread will wait for input form console
    string str;
    //child thread will read and pop from queue and print on console
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&tid, &attr, print, NULL);

    while(1){
        cout<<">> ";
        cin>>str;

        if(str == "exit"){
            break;
        }

        pthread_mutex_lock(&lock);
        str_q.push(str);
        pthread_cond_signal(&cond); //signal
        pthread_mutex_unlock(&lock);

    }


    return 0;
}


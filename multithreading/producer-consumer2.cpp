#include <cstdio>
#include <pthread.h>
#include <queue>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
/*solve the problem using: 
    1. mutex and conditional varibales
    2.solve it using semaphores
*/
using namespace std;

#define MAX_COUNT 10

pthread_mutex_t mut =  PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

std::queue<int> cnt;

void* Producer(void* arg){
//initialize the random number generator.this is same as seed in c.
    std::srand(time(nullptr));

    int count = 0;
    while(count < MAX_COUNT){ 
        pthread_mutex_lock(&mut);
        cnt.push(count);
        cout<<" Producer produced item: "<< count <<endl;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mut);
        count++;
//wait for 2 microseconds
        const int delay = (rand() % 10) * 200000;
        usleep(delay);
    }
    return nullptr;
}

void* Consumer(void* arg){

    int count = 0;

    while(1){

        if(count == MAX_COUNT){
            return nullptr;
        }

        pthread_mutex_lock(&mut);
        while(cnt.empty()){ //sleep while queue is empty
            pthread_cond_wait(&cond, &mut); 
            /*commenting this line, ie without conditionl var will cause busy-waiting.
            ie the thread will keep on spinning/runnign while q is empty but another thread cannot be scehduled bcs this thread
            is busy. (now consider both cases when OS is pre-emptive vs non-preemptive)
            */
        }
        int item = cnt.front();
        cnt.pop();
        cout<<" consumed item: "<< item <<endl;
        pthread_mutex_unlock(&mut);
        count++;
    }

    return nullptr;
}

int main(){

    pthread_t tc;
    pthread_t tp;

    pthread_attr_t attr1;
    pthread_attr_t attr2;

    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);

    pthread_create(&tc, &attr1, Producer, nullptr);
    pthread_create(&tp, &attr2, Consumer, nullptr);


    pthread_join(tc, nullptr);
    pthread_join(tp, nullptr);


}

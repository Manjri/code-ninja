#include <pthread.h>
#include <iostream>
#include <cstdio>

/* demo to print even and odd numbers using only one function but with 2 threads. for smaller limits, no concurrency
issues sene. but when i increased the limit, saw that sometimes even and odd both numbers were getting printed. this is 
bcs for small limit, the threads exits the fn even before the second comes into it. to avoid concurrency used mutex to 
serialize access to common shared buffer (printf-writes on the console). usually concurrency issues are seen in writing. 
*/

using namespace std;

int limit = 200;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* print(void* arg) {

    //cout<<"       print     "<<endl;
    int flag = *(int *)arg;

    int i = 0;
    if(flag == 1) {//print odd. reading is fine for 2 threads.
        i = 1;
    }

    while(i <= limit) {
        pthread_mutex_lock(&mutex); //mutex lock and unlock is a system call and takes time
        cout<<" " << i <<" "<<endl;
        pthread_mutex_unlock(&mutex);
        i = i+2;
    }
    //cout<<endl;

    return nullptr;
}


int main(){
    cout<<"this demonstrates passing args to a thread fn using dynamically allocated space & returning using same " <<endl;
    pthread_t tid_even;
    pthread_t tid_odd;
    pthread_attr_t attr;
    pthread_attr_init(&attr); //initialise the attributes
    int flag_even = 0;
    int flag_odd = 1;

    //create background thread and provide it with fn to work on. executing multiple copies of same fn
    pthread_create(&tid_even, &attr, print, &flag_even); //passing inout to fn via limit arg
    pthread_create(&tid_odd, &attr, print, &flag_odd);

    pthread_join(tid_even,NULL);
    pthread_join(tid_odd,NULL);

    return 0;
}
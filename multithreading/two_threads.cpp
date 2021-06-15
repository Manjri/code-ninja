#include <pthread.h>
#include <iostream>
#include <cstdio>

using namespace std;

//sum computed by the background thread. global variable so other threads can access
//long long ans = 0;

//instead of accesing global var by 3 threads and using mutex to protect access,we are 
//going to return ans in via ptr in struct
struct sum_runner_struct{
    long long limit;
    long long ans;
};

void* sum_runner(void* arg){

    cout<<"       Inside sum()     "<<endl;
    sum_runner_struct *limit_struct = (struct sum_runner_struct*)arg;
    long long ans = 0; //each thread first calculating answer in local variable and then dumping it into global

    for(long long i = 0; i <= limit_struct->limit; i++){
        ans += i;
    }

    limit_struct->ans = ans;
    pthread_exit(0); //0 gets passed back to pthread_join NULL. means dont catch the answer
}

int main(){

    cout<<"this main will create a new background thread to execute a small fn" <<endl;

/*
       int pthread_create(pthread_t *restrict thread,
                          const pthread_attr_t *restrict attr,
                          void *(*start_routine)(void *),
                          void *restrict arg);
*/

    pthread_t tids[2];

    struct sum_runner_struct args[2];

    for(int i = 0; i < 2; i++){ //creating 2 threads now. they have diff thread ids and attributes

        args[i].limit = i + 10; //input for each thread
        pthread_attr_t attr;
        pthread_attr_init(&attr); //initialise the attributes  

    //create background thread and provide it with fn to work on. executing multiple copies of same fn
        pthread_create(&tids[i], &attr, sum_runner, &args[i]); //passing inout to fn via limit arg
    }

    for(int i = 0; i < 2; i++){
        //wait until thread is done its work. join the thread. this "waits"
        pthread_join(tids[i], NULL);
        cout<<"thread: " << tids[i]<<" sum is "<< args[i].ans <<endl;
    }


    
    return 0;
}
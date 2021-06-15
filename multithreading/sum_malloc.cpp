#include <pthread.h>
#include <iostream>
#include <cstdio>

using namespace std;

/* this demos how to pass varibales via thread fn using dynamic memory. pthread_exit and join are used to pass answer. 
 * imp point to keep in mind is where to free the memory.!
*/



void* sum_runner(void* arg){

    cout<<"       Inside sum()     "<<endl;

    long long* limit_ptr = (long long *)arg;
    long long limit = *limit_ptr;

    //IMP: assuming the input arg has been dynamically allocated in caller fn, free it here
    free(arg);

    long long ans = 0;
    for(long long i = 0; i <= limit; i++){
        ans += i;
    }

    //pass back data in dynamically allocated memory throw back answer now
    long long* answer = malloc(sizeof(*answer)); //giving out memory after allocating. wont be memory leak if 
    //fn calling it, frees it
    *answer = ans;
    pthread_exit(answer); //IMP: answer gets passed back to pthread_join. void * conversion is done automatically
}

int main(){

    cout<<"this demonstrates passing args to a thread fn using dynamically allocated space & returning using same " <<endl;
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr); //initialise the attributes

    long long* limit = malloc(sizeof(limit)); //IMP: malloc input in this fn and pass it to fn and then free it in sum_runner

    //create background thread and provide it with fn to work on. executing multiple copies of same fn
    pthread_create(&tid, &attr, sum_runner, limit); //passing inout to fn via limit arg

    //this result has been allocated by sum_runner fn.
    long long* result;
    pthread_join(tid, (void **)&result);
    cout<<" sum is "<< *result <<endl;
    free(result);

    return 0;
}
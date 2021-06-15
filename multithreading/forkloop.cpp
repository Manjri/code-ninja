#include <pthread.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;


int main(){


    for(int i = 0; i < 2; i++){
        fork(); //very careful for doing fork in a loop
        cout<< i <<" MY PID = " << (int)getpid()<<endl;
    }

    sleep(2);
    cout<<"---> MY PID = " <<(int)getpid() <<endl;

/*
    while(1){
        fork(); //fork bomb
    } */
    return 0;
}
/* write small fn to demo creating new process. demo if 2 processes share same address space.
refer: https://www.youtube.com/watch?v=9seb8hddeK4
fork: spawns a new process and it duplicates memory space of current process and ot returns twice! one for child and then for parent process
*/

#include <pthread.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int i = 0; //global variable. separate address space for both process unless you use interprocess communication

void dosomework(string s){
    const int NUM_TIMES = 2;
    for(; i < NUM_TIMES; i++){
        sleep(rand() % 4);
        cout<<"done pass "<< i <<" for "<< s <<endl;
    }

}
int main(void){

    cout<<"I am process "<< (int)getpid() <<endl;

    pid_t pid = fork(); //fork returned twice, one in each process!! wow
    srand((int) pid);
    cout<<" fork() returned "<< (int)pid <<endl;

    if(pid < 0){
        cout<<"ERROR fork failed "<< endl;
    }

    if(pid == 0){
        cout<<"I am child with pid "<< (int)getpid() <<endl;
        //sleep(5);
        dosomework("child");
        cout<<"child exiting... "<<endl;
        exit(42); //if you do 0 here then wait in parent should have NULL
    }

    //we must be parent
    cout<<"I am parent with pid: "<< (int)getpid() << " waiting for child to end" <<endl;
    sleep(30); //this is in seconds...this shows child has finished but parent is still slepeing. so child is waiting to be waiting on. it is defnuct fn (child process)
    dosomework("parent");
    int status = 0;
    pid_t childpid = wait(&status); //wait until child process terminates
    cout<<"parent knows child "<< (int) childpid <<" finished with status  "<< status << endl;

    int childreturnvalue = WEXITSTATUS(status);  //mask of the value which is returned from child process
    cout<<"   return value  was "<< childreturnvalue <<endl;
    return 0;
}
/* implement/demo mutex using test_and_set hardware instruction https://en.wikipedia.org/wiki/Test-and-set
https://www.geeksforgeeks.org/introduction-of-process-synchronization/
this demo shows how to make a mutex using HW test_and_set instruction (like HW instructions jump etc)
*/

//This is a psuedo code in c. will not compile.
#define LOCKED 1
int test_and_set(int* lockptr){

    int old_Value = *lockptr;
    *lockptr = LOCKED; //set it to 1
    return old_value;
}

volatile int lock = 0;
void critical(){

    while(test_and_set(&lock) == 1){ //locked
        ; //just wait
    }
    //unlock -- bcs lock is now 0
    enter_critical_Section //only one process can be here at a time
    lock = 0; // release lock
}

//NOTE: for multithreaded programming, always visualize in terms of 2 threads atleast. while one is waiting line 18, locked. the other is at line 23, exiting so it
//needs to release lock and set it to 0
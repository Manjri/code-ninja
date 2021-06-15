/*given a binary semaphore b_sem, implement counting sempahore of count C*/

#define MAX_SEM_COUNT 5

// given operations on binary semaphore
struct bsem;
bsem_init(bsem *s);
bsem_deinit(bsem *s);
bsem_wait(bsem *s);
bsem_signal(bsem *s);

//Implement counting semaphore
struct csem
{
    int count;
    int max;
    bsem cond; //using conditional variable for signal/wait
    bsem mutex; //to be used as a lock to protect shared resource
}

csem_init(csem *s,int C)
{
    s->count = C;
    s->max = C;
    bsem_init(&s->cond);
    bsem_init(&s->mutex);
}

csem_deinit(csem *s)
{
    s->count = 0;
    bsem_deinit(&s->cond);
    bsem_deinit(&s->mutex);
}

csem_wait(csem *s)
{
    bsem_wait(&s->mutex); //lock mutex before reading/modifying shared variable.
/*    if(s->count > 0){
        s->count--;
        bsem_signal(&s->mutex);  //unlock -- 
        return;
    }*/

    //wait no resource available, until there is signal. remember you still have the mutex from line36.
    while(s->count == 0)
    {
        bsem_signal(&s->mutex);  //unlock
        //when next instr at line#48 is executed, you can assume that someone has called signal on condition variable
        bsem_wait(&s->cond); // this is blocking == sleeping.  
        bsem_wait(&s->mutex);  //lock mutex again for entering next iteration of while
    }
    s->count--;
    bsem_signal(&s->mutex);  //unlock

}

csem_signal(csem *s)
{
    bsem_wait(&s->mutex);  //lock
    if(s->count < s->max)
    {
        s->count++;
        bsem_signal(&s->cond);
    }
    bsem_signal(&s->mutex); //unlock
}

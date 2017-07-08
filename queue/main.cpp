#include "queue.h"
#include <iostream>

using namespace std;
int main()
{
    queue *q = queue_create(10);
    for(int i=0; i<10; i++)
    {
        queue_enqueue(q, i); 
    }

    cout<<"printing:"<<"\n";
    queue_print(q);

    for(int i=0; i<11; i++)
    {
        queue_dequeue(q); 
    }

    cout<<"printing:"<<"\n";
    queue_print(q);

    return 1;
}
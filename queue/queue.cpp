/*Queue implementation using struct*/
#include <cstdio>
#include <iostream>
#include "queue.h"

using namespace std;

#define MAXSIZE 10;

struct queue
{
    int *array;
    int head;
    int tail;
    int size;
    int capacity; 
};

queue *queue_create(int capacity)
{
    queue *q = (queue *)malloc(sizeof(queue));
    if(q != NULL)
    {
        q->capacity = capacity;
        q->head = -1;
        q->tail = -1;
        q->array = (int*)malloc(sizeof(int)*capacity);
    }
    cout<<"created q"<<"\n";
    return q;
}

void queue_destroy(queue *q)
{
    free(q->array);
    free(q);
}

/*add from tail*/
void queue_enqueue(queue* q, int n) 
{

    if(q->head == -1 && q->tail == -1) //empty
    {
        q->array[0] = n;
        q->tail = 0;
        q->head = 0;
        q->size++;
    }
    else if((q->tail + 1) % (q->capacity) == q->head)//full. current element at tail
    {
        cout<<"Queue Full!"<<"\n";
    }
    else
    {
        //increment tail
        
        q->tail = (q->tail + 1) % (q->capacity);  
        q->array[q->tail] = n;
        q->size++;
    }

}

/*delete from head*/
void queue_dequeue(queue* q)
{ 
    int n;
    //check for empty queue
    if(q->head == -1 && q->tail == -1)
    {
        cout<<"Queue Empty!"<<"\n";       
    }
    else if(q->head == q->tail) //1 element
    {
        n = q->array[q->head];
        cout<<"removing: "<< n <<"\n";
        q->head = -1;
        q->tail = -1;
        q->size--;
    }
    else
    {
        n = q->array[q->head];
        cout<<"removing: "<< n <<"\n";
        //increase head
        q->head = (q->head + 1) % (q->capacity);
        q->size--;
    }
}

int queue_front(queue *q)
{
    return(q->array[q->head]);
}

void queue_print(queue *q)
{
    //check for empty queue
    if(q->head == -1 && q->tail == -1)
    {
        cout<<"Queue Empty!"<<"\n";       
    }
    else
    {
        int i = q->head; 
        while(i != q->tail)
        {
            cout<<q->array[i]<<" ";
            i = (i + 1) % (q->capacity);
        }
        if(i == q->tail)
        {
            cout<<q->array[i]<<" ";
        }
        cout<<"\n";
    }
}

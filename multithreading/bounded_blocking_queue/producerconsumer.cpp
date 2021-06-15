#include <pthread.h>
#include <cstdio>
#include <iostream>
#include <cassert>
#include <unistd.h>
#include <cstdlib>

using namespace std;

#define MAX_CAP 10

//can i use same mutex but with 2 diff cond variables? or should i use 2 diff locks: 1 for full and 1 for empty ?
struct boundedq{
    int head;
    int tail;
    int size;
    int capacity;
    int* array;
    pthread_mutex_t mutex;
    pthread_cond_t cond_has_space;
    pthread_cond_t cond_has_item;
};

void enqueue(boundedq* q, int x){

    assert(q != nullptr);

    pthread_mutex_lock(&q->mutex);

    //full..block until space
    while(q->size == q->capacity){
        pthread_cond_wait(&q->cond_has_space, &q->mutex);
        //printf("Queue is full!! Cannot Enqueue anymore! \n");
    }
    

    //empty. signal to deq after adding?
    if(q->head == -1 && q->tail == -1){
        q->tail++;
        q->array[q->tail] = x;
        q->head++;
    }
    else{ // signal to deq after adding?
        q->tail = (q->tail + 1) % q->capacity;
        q->array[q->tail] = x;
    }
    q->size++;
    printf("Queue size after enqueue: %d\n", q->size);
    pthread_cond_signal(&q->cond_has_item);
    pthread_mutex_unlock(&q->mutex);
}

int dequeue(boundedq* q){

    //printf("%s:%d\n", __func__, __LINE__);
    pthread_mutex_lock(&q->mutex);
    //empty.. block untill have element
    while(q->size == 0){
        pthread_cond_wait(&q->cond_has_item, &q->mutex);
        //printf("Empty \n");
    }

    //printf("%s:%d\n", __func__, __LINE__);

    int x;
    //1 element..signal to enqueue after removing?
    if(q->head == q->tail){
        printf("only 1 element left \n");
        x = q->array[q->head];
        q->head = -1;
        q->tail = -1;
    }
    else{ //signal to enqueue after removing
        x = q->array[q->head];
        q->head = (q->head + 1) % q->capacity;
    }
    q->size--;
    printf("Queue size after Dequeue: %d\n", q->size);
    pthread_cond_signal(&q->cond_has_space);
    pthread_mutex_unlock(&q->mutex);
        //printf("%s:%d\n", __func__, __LINE__);
    return x;
}


int front(boundedq* q){
    assert(q != nullptr);
    assert(q->size > 0);
    int x;
    pthread_mutex_lock(&q->mutex);
    x =  q->array[q->head];
    pthread_mutex_unlock(&q->mutex);
    return x;
}

void create_queue(boundedq* q){
    //it exists program if the condition is false
    assert(q != nullptr); 
    q->head = -1;
    q->tail = -1;
    q->capacity = MAX_CAP;
    q->array = (int*)malloc(q->capacity * sizeof(int));
    q->size = 0;
    q->mutex = PTHREAD_MUTEX_INITIALIZER;
    q->cond_has_item = PTHREAD_COND_INITIALIZER;
    q->cond_has_space = PTHREAD_COND_INITIALIZER;
}

/* TESTING CODE */
void* producer(void* arg){

    std::srand(time(nullptr));
    printf("    PRODUCER STARTED!\n");
    boundedq* q = (boundedq*)arg;
    for(int i = 0; i < 30; i++){
        enqueue(q, i);
        printf("ENQUEUE %d \n", i);
        const int delay = (rand() % 100000);
        usleep(delay);
    }
    return nullptr;
}

void* consumer(void* arg){
    std::srand(time(nullptr));
    printf("    CONSUMER STARTED!\n");
    boundedq* q = (boundedq*)arg;
    for(int i = 0; i < 30; i++){
        int x = dequeue(q);
        printf("DEQUEUED: %d\n", x);
        const int delay = (rand() %  300000);
        usleep(delay);
    }
    return nullptr;
}

int main(){
    pthread_t tp;
    pthread_t tc;
    pthread_attr_t attr1;
    pthread_attr_t attr2;
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);

    boundedq q;
    create_queue(&q);

//pass some value instead of null and check the size after each operation
    pthread_create(&tp, &attr1, producer, &q);
    pthread_create(&tc, &attr2, consumer, &q);

//check if you need to return some value
    pthread_join(tp, nullptr);
    pthread_join(tc, nullptr);
    return 0;
}
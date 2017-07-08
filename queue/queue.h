/*Queue implementation using struct*/
#pragma once

struct queue;

queue *queue_create(int capacity);

void queue_destroy(queue *q);

/*add from tail*/
void queue_enqueue(queue* q, int n); 

int queue_front(queue *q);

/*delete from head*/
void queue_dequeue(queue* q);

void queue_print(queue *q);






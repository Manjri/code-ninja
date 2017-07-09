#ifndef STACK_H
#define STACK_H

#define MAXSIZE 10

class mystack
{
    public:
        void push(int num);
        void pop();
        void print();
        int top();

        /* constructor using initializer list */
        mystack(int size) :
            tp(0)
        { 
            p = new int[size];
        }

    private:
        int *p;
        int tp;
};

#endif
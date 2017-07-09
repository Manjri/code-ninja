#ifndef DYNAMIC_STACK_H
#define DYNAMIC_STACK_H
#include <vector>

#define MAXSIZE 10

class dynamic_stack
{
    public:
        void push(int num);
        void pop();
        void print();
        int top();

        /* constructor using initializer list */
        dynamic_stack() :
            tp(0)
        { 
        }

    private:
        std::vector<int> vec;
        int tp;
};

#endif
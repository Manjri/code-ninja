#include "dynamic_stack.h"
#include <iostream>
#include <vector>

using namespace std;


void test1()
{
    dynamic_stack s;
    for(uint32_t i=0; i<25; i++)
    {
        s.push(i+1);
    }
     
    s.print();
    int top = s.top();
    cout<<"top element: "<< top <<"\n";
    for(uint32_t i=0; i<26; i++)
    {
        s.pop();
    }
    try{
        top = s.top();
        cout<<"top element: "<< top <<"\n";
    }
    catch(exception &e)
    {
        cout<<e.what();
    }
    
}


int main()
{
    cout << "Dynamic Stack Test\n";
    test1();

    return 0;
}
#include "stack.h"
#include <iostream>

using namespace std;

void test1()
{
    mystack s(10);
    s.push(12); 
    s.push(78);
    s.push(90); 
    s.print();
    int top = s.top();
    cout<<"top element: "<< top <<"\n";
    s.pop();
    s.pop();
    s.pop();
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
    cout << "Stack Test\n";
    test1();

    return 0;
}
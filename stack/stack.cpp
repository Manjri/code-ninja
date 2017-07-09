#include "stack.h"
#include <iostream>

using namespace std;

void mystack::print()
{
    for(int i=0; i<tp; i++)
    {
        cout<< p[i] <<" ";
    }
    cout<<"\n";
}

void mystack::push(int num)
{
    p[tp] = num;
    tp++;
}

void mystack::pop()
{
    cout<<"poping!"<<"\n";
    if(tp != 0)
    {
        tp--;
        cout<<"tp: "<< tp <<"\n";
    }
}


int mystack::top()
{
   if(tp != 0)
   {
        return p[tp-1];
   } 
   throw runtime_error("Stack Empty!");
}
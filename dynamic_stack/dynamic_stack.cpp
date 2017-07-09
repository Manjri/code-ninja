#include "dynamic_stack.h"
#include <iostream>

using namespace std;

void dynamic_stack::print()
{
    for(uint32_t i=0; i<vec.size(); i++)
    {
        cout<< vec[i] <<" ";
    }
    cout<<"\n";
}

void dynamic_stack::push(int num)
{
    vec.push_back(num);
}

void dynamic_stack::pop()
{
    cout<<"poping!"<<"\n";
    if(!vec.empty())
    {
        vec.pop_back();
    }
}

int dynamic_stack::top()
{
   int sz = vec.size();
   if(sz != 0)
   {
        return vec[sz-1];
   } 
   throw runtime_error("Stack Empty!");
}
#include <iostream>
#include <vector>

using namespace std;

class queue
{
    public:
        void enqueue(int val);
        void dequeue();
        int front();
    private:
        vector<int> stack1;
        vector<int> stack2;
};
/*using vectors*/
void queue::enqueue(int val)
{
    stack1.push_back(val);
    cout<<"enqueued: "<< val <<"\n";
}

/*dequeue from top*/
void queue::dequeue()
{
    //logic here
    if(!stack2.empty()) /*deq from stack2 if its not empty*/
    {
        stack2.pop_back();
    } 
    else /*stack2 empty, move elements from s1 to s2 and then delete from s2*/
    {
        while(!stack1.empty())
        {
            int v = stack1.back();
            stack2.push_back(v); 
            stack1.pop_back();
        }
        stack2.pop_back();
    }
}

int queue::front()
{
    int n;
    while(!stack1.empty())
    {
        int v = stack1.back();
        stack2.push_back(v); 
        stack1.pop_back();
    }
    n = stack2.front();
    return n;
}


int main(void)
{
   /* Create a queue with items 1 2 3*/
   queue q;
   cout<<"enq 1,2,3"<<"\n";
   q.enqueue(1);
   q.enqueue(2);
   q.enqueue(3);

   cout<<"deq 1,2,3"<<"\n";
   q.dequeue();
   q.dequeue();
   q.dequeue();

   return EXIT_SUCCESS;
}
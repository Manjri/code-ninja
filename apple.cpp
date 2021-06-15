/* Postorder traversal BST - iteratively

          10
      1          20
      
  post - order: left child, right child, rootnode
  
  1 ,20, 10

*/

#include <iostream>
#include <stack>
using namespace std;

typedef struct TreeNode{
  TreeNode* node;
  TreeNode* left;
  TreeNode* right;
  int value;
};

//recursivly
void postorder_recusive(TreeNode* node){
  
  if(!node){
    return;
  }
  
  
  //visit left child
  postorder(node->left);
  postorder(node->right);
  
  //visit current node
  cout<<"I am : "<< node->value <<endl;  
}

Home (1481 Nelson Ct)
void postorder_itr(TreeNode* node, stack<TreeNode*> st){
 
  if(!node){
    return;
  }
  
  //left, right, node . fill the stack
  while(node){
    
    if(node->right){
      st.push(node->right);
    }
    st.push(node);
    
    node = node->left;
  }
  

 while(!st.empty()){
    node = st.top();
    if(node->right ){  //leftmost node has a right child

      st.push(node);
      node = node->right;
    }
    else{ //no more right child
      cout<<"visit current node: " <<node->value <<endl;
      
    }
 }
  
  
}


// To execute C++, please define "int main()"
int main() {
  auto words = { "Hello, ", "World!", "\n" };
  for (const string& word : words) {
    cout << word;
  }
  return 0;
}


============================================================================================

void publisher_thread(Counter *c)
{
  while (true)
  {
    c->countOnce();
    printf("%d ", c->getCount());
  }
}

void consumer_thread(Counter *c)
{
  while (true)
  {
    printf("%d ", c->getCount());
  }
}

int main ()
{
  thread_t publisher;
  thread_t consumer1;
  thread_t consumer2;

  Counter c = new Counter();

  mutex_init(&c->mtx);
  cond_init(&c->cvar);

  publisher = thr_create(publisher_thread, &c);
  consumer1 = thr_create(consumer_thread, &c);
  consumer2 = thr_create(consumer_thread, &c);
}


class Counter
{
private:
  mutex_t mtx;
  cond_var_t cvar;

  int count;
  bool waitForConsumer = false;

public:
  void countOnce()
  {
    mutex_lock(&mtx);
    while (waitForConsumer)
    {
      cond_wait(&cvar, &mtx);
    }

    count++;
    waitForConsumer = true;
    cond_broadcast(&cvar);
    mutex_unlock(&mtx);
  }

  int getCount()
  {
    mutex_lock(&mtx);
    while (!waitForConsumer)
    {
      cond_wait(&cvar, &mtx);
    }

    int ret = count;
    waitForConsumer = false;
    cond_broadcast(&cvar);
    mutex_unlock(&mtx);
    return ret;
  }
}


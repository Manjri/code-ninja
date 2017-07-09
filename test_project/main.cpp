#include <cstdio>
#include <iostream>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
	  ListNode(){}
  };

ListNode* detectCycle(ListNode* A) {
    
    ListNode* p = A;
    ListNode* q = A;
    bool hascycle = false;

    while( p != NULL && q != NULL && p->next != NULL)
    {   
	    cout<<"p val = " << p->val << " ,q val = "<< q->val <<"\n";
		q = q->next;
		p = p->next->next;
		if(p == q)
    	{
            cout<<"INSIDE: p val = " << p->val << " ,q val = "<< q->val <<"\n";
			cout<<"returning val = " << p->val <<"\n";
			hascycle =true;
			break; //this is where both are same but not where cycle begins
    	}
    }

int i=0;
	if(hascycle == false)
	{
		return NULL;
	}
    else
	{
		p = A;
		while(p != q)
		{
			p = p->next;
			q = q->next;
			i++;
		}
 cout<< "i = "<< i << "\n";
		return p;
	}   


} 

//add node in back
ListNode* addNode(ListNode* head, int value)
{
	ListNode* temp = new ListNode;
	temp->val = value;
	temp->next = NULL;
	//if no elements in list, head is null wont be abe to deref it
	if(head == NULL) 
	{
		return temp;
	}
	//at end

	ListNode* p = head;
	while(p->next != NULL)
    {
		p = p->next;
	}

	p->next = temp;
	
	return head;
}

//add node in front
ListNode* addNodeFront(ListNode* head, int value)
{
	ListNode* temp = new ListNode;
	temp->val = value;
	temp->next = NULL;
	//if no elements in list, head is null wont be abe to deref it
	if(head == NULL) 
	{
		head = temp;
		head->next = NULL;
		return head;
	}
	//at front
	ListNode* p = head;
	temp->next = p->next;	
	p->next = temp;
	return head;
}

//add node at a given location
ListNode* addNodePos(ListNode* head, int value, int index)
{
	int i=0;
	ListNode* temp = head;
	if(head == NULL)
	{
		return 0; //ask punit
	}
	while(i < index-1 && temp->next != NULL)
	{
		temp = temp->next;
		i++;
	}

	ListNode* newNode = new ListNode;
	newNode->val = value;
    newNode->next = temp->next;
	temp->next = newNode;

	return head;
}

//create cycle
 void createCycle(ListNode* head, int position)
 {
	ListNode* temp = head;
	ListNode* cycle = head;
	int i=0;
	int length=0;
	while(temp->next != NULL)
	{
		temp = temp->next;
		length++;	
	}
	cout<<"leng = " << length <<"\n";
	if(position > length-1)
	{
		throw runtime_error("position is beyond list, cant make cycle");
	}

    cout<<" position = " << position << "\n";
	while(i < position && cycle != NULL)
	{
		cycle = cycle->next;
		i++;
		cout<<" i = " << i << "\n";
	}


	temp->next = cycle;
	cout<<"cycle at = " << cycle->val <<"\n";
	
 }

//print node
int printNode(ListNode* head)
{
	if(head == NULL)
    {
		cout<<"Empty List!";
		return 0;
	}
	ListNode* temp = head;
	while(temp != NULL)
	{
		cout<< temp->val << " ";
		temp = temp->next;
	}
	return 0;
}

int main()
{
	printf("HELLO\n");
	//how to pass head node?
	ListNode* hd = NULL;

	for(int i=0; i<10; i++)
	{
		hd = addNode(hd, i);
	}
		printNode(hd);
		cout<<"\n";
/*
		addNodeFront(hd,10);
		printNode(hd);
		cout<<"\n";
		addNodePos(hd,11,3);
		printNode(hd);
*/
	createCycle(hd, 5);
	//hd->next->next->next->next = hd;

	ListNode* p = detectCycle(hd);
	cout<<"cycle found at  = " << p->val << " \n";

	return 0;
}
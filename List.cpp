#include"List.h"
#include<assert.h>


void List::PushBack(DataType value)
{
  Node* newnode=new Node(value);

  Node* prev=_head->_prev;
  Node* next=_head;

  newnode->_next=next;
  _head->_prev=newnode;
  newnode->_prev=prev;
  prev->_next=newnode;
}

void List::PushFront(DataType value)
{
  Node* newnode=new Node(value);

  Node* next=_head->_next;

  newnode->_prev=_head;
  _head->_next=newnode;
  newnode->_next=next;
  next->_prev=newnode;
}

void List::PopBack()
{
  assert((_head->_next)!=_head);
  Node* cur=_head->_prev;

  cur->_prev->_next=_head;
  _head->_prev=cur->_prev;
  delete cur;
}

void List::PopFront()
{
  assert(_head->_next!=_head);

  Node* cur=_head->_next;

  _head->_next=cur->_next;
  cur->_next->_prev=_head;
  delete cur;
}

List::Node* List::Find(DataType value)
{
  Node* cur=_head->_next;
  while(cur!=_head)
  {
    if(cur->_data==value)
    {
      return cur;
    }
    cur=cur->_next;
  }
  return NULL;
}

void List::Insert(Node* pos,DataType value)
{
  assert(pos);
  Node* newnode=new Node(value);
  Node* prev=pos->_prev;

  newnode->_next=pos;
  pos->_prev=newnode;
  prev->_next=newnode;
  newnode->_prev=prev;
}

void List::Erase(Node* pos)
{
  assert(pos!=_head);

  Node* prev=pos->_prev;
  Node* next=pos->_next;

  prev->_next=next;
  next->_prev=prev;
  delete pos;
}

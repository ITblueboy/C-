#pragma once 
#include<iostream>
using namespace std;
typedef int DataType;

struct ListNode
{
  ListNode* _next;
  ListNode* _prev;
  DataType _data;

  ListNode(DataType value)
    :_data(value)
    ,_next(NULL)
    ,_prev(NULL)
  {

  }
};

class List 
{
  typedef ListNode Node;
  public:
  List()
    :_head(new Node(DataType()))
  {
    _head->_next=_head;
    _head->_prev=_head;
  }

  List(const List& l)
    :_head(new Node(DataType()))
  {
    _head->_next=_head;
    _head->_prev=_head;

    Node* cur=l._head->_next;
    while(cur!=l._head)
    {
      PushBack(cur->_data);
      cur=cur->_next;
    }
  }

  List& operator=(List l)
  {
    swap(_head,l._head);
    return *this;
  }

  ~List()
  {
    Node* cur=_head->_next;
    while(cur!=_head)
    {
      Node* next=cur->_next;
      delete cur;
      cur=next;
    }
    delete _head;
    _head=NULL;
  }

  void PushBack(DataType value);
  void PushFront(DataType value);
  void PopBack();
  void PopFront();
  Node* Find(DataType value);
  void Insert(Node* pos,DataType value);
  void Erase(Node* pos);

  void Printf()
  {
    Node* cur=_head->_next;
    while(cur!=_head)
    {
      cout<<cur->_data;
      cur=cur->_next;
    }
    cout<<endl;
  }
  private:
  Node* _head;
};

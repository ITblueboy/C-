#include<iostream>
#include<string>
using namespace std;

class Person
{
public:
  Person(const char* name="",int id=0)
    :_name(name)
    ,_num(id)
  {}
  void display()
  {
    cout<<_name<<endl;
    cout<<_num<<endl;
  }
protected:
  string _name;
  int _num;
};

class Student:public Person 
{
  public:
    Student(const char* name,int id,int stunum=0)
      :Person(name,id)
      ,_num(stunum)
  {}
    void display()
    {
     //cout<<"身份证号"<<Person::_num<<endl;
     //cout<<"姓名"<<Person::_name<<endl;
     //cout<<"学号"<<_num<<endl;
     cout<<"display()"<<endl;
    }
  protected:
    int _num;
};

void test()
{
  Student* p=NULL;
  p->display();
}
int main()
{
  test();
  return 0;
}

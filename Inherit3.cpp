#include<iostream>
#include<stdio.h>
using namespace std;
class Person
{
  public:
    void fun(int num)
    {
      cout<<num<<endl;
    }
    void fun(char* p)
    {
      cout<<p<<endl;
    }
   void virtual fun1(int num)
   {
     cout<<"Person::fun1()"<<num<<endl;
   }
  protected:
    int _num;
};

class Student:public Person 
{
  public:
    void fun1(int num)
    {
      cout<<"Student::fun1()"<<num<<endl;
    }

};
int main()
{
  Person p;
  Student s;
  p.fun(5);
  p.fun("hello worid!");
  s.fun1(2);
  p.fun1(0);
  return 0;
}

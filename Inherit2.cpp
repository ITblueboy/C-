#include<iostream>
#include<string>
using namespace std;

class Person
{
public:
  Person(const char* name="",int id=0)
    :_name(name)
    ,_num(id)
  {
    cout<<"Person()"<<endl;
  }

  Person(const Person& p)
    :_name(p._name)
    ,_num(p._num)
  {
    cout<<"Person(const Person& p)"<<endl;
  }

  ~Person()
  {
    cout<<"~Person()"<<endl;
  }
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
    Student(const char* name,int id,int stunum)
      :Person(name,id)
      ,_num(stunum)
  {
    cout<<"Student()"<<endl;
  }
    Student(const Student& s)
      :Person(s)
      ,_num(s._num)
  {
    cout<<"Student(const Student& s)"<<endl;
  }

    ~Student()
    {
      cout<<"~Student()"<<endl;
    }
    void display()
    {
      cout<<"身份证号"<<Person::_num<<endl;
      cout<<"姓名"<<Person::_name<<endl;
      cout<<"学号"<<_num<<endl;
    }
  protected:
    int _num;
};

void test()
{
  Student s("Paul",101,001);
}
int main()
{
  test();
  return 0;
}

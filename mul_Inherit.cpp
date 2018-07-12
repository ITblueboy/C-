#include<iostream>
#include<string>
using namespace std;

class A
{

  protected:
    int _stunum;
};

class B:public A
{
  protected:
    int _num;
};

class C:public A
{
protected:
	string _name;
};

class D :public B, public C
{

};
//int main()
//{
//	D d;
//  return 0;
//}

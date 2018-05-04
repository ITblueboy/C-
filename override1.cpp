#include<iostream>
using namespace std;

void fun(char a)
{
  cout<<a<<endl;
}

void fun(int b)
{
  cout<<b<<endl;
}

int main()
{
  int x=3;
  char y='a';
  fun(y);
  fun(x);
  return 0;
}

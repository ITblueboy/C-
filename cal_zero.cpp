#include<stdio.h>
#include<iostream>
using namespace std;

int calculate(int n)
{
  if(n>=0&&n<5)
  {
    return 0;
  }
  return n/5+calculate(n/5);
}
int main()
{
  int num=0;
  cin>>num;
  cout<<calculate(num)<<endl;

  return 0;
}

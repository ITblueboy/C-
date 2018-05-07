#include<iostream>
#include<stdio.h>
using namespace std;

void swap(int& c,int& d)
{
  int tmp=c;
  c=d;
  d=tmp;
  printf("c=%p\n",&c);
  printf("d=%p\n",&d);
}
int main()
{
  int a=3;
  int b=4;
  printf("a=%p\n",&a);
  printf("b=%p\n",&b);
  swap(a,b);
  return 0;
}

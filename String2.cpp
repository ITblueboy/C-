#include<iostream>
#include"String.h"
using namespace std;

int main()
{
  String s("");
  String s1("hello world");
  String s2(s1);
  String s3=s2;
  s1=s1;
  cout<<s.C_str()<<endl;
  cout<<s1.C_str()<<endl;
  cout<<s2.C_str()<<endl;
  cout<<s3.C_str()<<endl;
  return 0;
}

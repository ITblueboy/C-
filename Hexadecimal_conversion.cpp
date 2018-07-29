#include<stdio.h>
#include<string>
#include<iostream>
using namespace std;

int main()
{
  string s=" ";
  string table="0123456789ABCDEF";
  int M=0;
  int N=0;
  cin>>M>>N;
  if(M==0)
  {
    s="0";
  }
  while(M)
  {
    if(M<0)
    {
      M=-M;
      cout<<"-";
    }
    s=s+table[M%N];
    M=M/N;
  }
  cout<<s<<endl;
  return 0;
}

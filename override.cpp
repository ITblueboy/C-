#include <iostream>
using namespace std;
void fun(int num)
{
  cout<<num<<endl;
}

void fun()
{
  cout<<"hello C++"<<endl;
}
int main()
{
  int a=1314;
  fun(a);
  fun();
  return 0;
}

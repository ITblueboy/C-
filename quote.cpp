#include <iostream>
using namespace std;

int main()
{
  int a=3;
  int& b=a;
  int& c=a;
  const int& d=5;
  cout<<a<<endl;
  cout<<b<<endl;
  cout<<c<<endl;
  cout<<d<<endl;
  return 0;
}

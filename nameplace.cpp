#include <iostream>
using namespace std;
namespace name1
{
  int a=1;
}
namespace name2
{
  int a=2;
}
int main()
{
  name1::a=3;
  name2::a=4;
  cout<<name1::a<<endl;
  cout<<name2::a<<endl;
  return 0;
}

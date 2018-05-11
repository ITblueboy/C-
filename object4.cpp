#include<iostream>
#include<stdlib.h>
using namespace std;

class Array
{
  public:
  Array(int size)
  {
    _ptr=(int*)malloc(size*(sizeof(int)));
  }
  void display()
  {
    cout<<_ptr<<endl;
  }
  ~Array()
  {
    if(_ptr!=NULL)
    {
      free(_ptr);
      _ptr=NULL;
    }
  }
  private:
 int*  _ptr;
};
int main()
{
  Array a1(3);
  a1.display();
  return 0;
}

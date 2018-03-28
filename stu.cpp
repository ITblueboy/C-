#include <iostream>
using namespace std;

class STU
{
  public:
    STU(int num=1001,int age=18,int score=100)
    {
      _num=num;
      _age=age;
      _score=score;
      cout<<"STU()"<<endl;
    }
    STU(const STU& s)
    {
      _num=s._num;
      _age=s._age;
      _score=s._score;
      cout<<"STU(const STU&)"<<endl;
     
    }
    STU& operator=(const STU& s)
    {
      if(this!=&s)
      {
        this->_num=s._num;
        this->_age=s._age;
        this->_score=s._score;
        cout<<"operator="<<endl;
      }
    }
    ~STU()
    {
      cout<<"~STU()"<<endl;
    }
   void show()
    {
      cout<<_num<<"-"<<_age<<"-"<<_score<<endl;
    }
  private:
   int _num;
   int _age;
   int _score;
};

int main()
{
  STU s1(1000,18,94);
  s1.show();
  STU s2;
  s2.show();
  STU s3(1002,19);
  s3.show();
  STU s4(s1);
  s4.show();
  STU s5=s2;
  s5.show();
  STU s6;
  s6=s2;
  s6.show();
  return 0;
}

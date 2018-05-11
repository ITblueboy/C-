#include<iostream>
using namespace std;

class Date
{
  public :
    Date (int x)
      : _day(x )
      , _month(_day)
      , _year(x )
  {
    cout<<"Date()"<<endl;
  }
    void Display ()
    {
      cout<<"year:"<<_year<<endl;
      cout<<"month:"<<_month<<endl;
      cout<<"day:"<<_day<<endl;

    }
  private :
    int _year ; // 年
    int _month ; // 月
    int _day ; // 日

};

int main()
{
  Date d(1);
  d.Display();
  return 0;
}

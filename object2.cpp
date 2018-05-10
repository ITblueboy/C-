#include <iostream>
using namespace std;

class Date
{
  public:
    Date()
    {
      cout<<"Date()"<<endl;
    }
    Date(int year,int month,int day)
    { 
      _year=year;
      _month=month;
      _day=day;
      cout<<"非默认成员函数"<<endl;
    }
    void display()
    {
      cout<<_year<<"-"<<_month<<"-"<<_day<<endl;
    }
  private:
    int _year;
    int _month;
    int _day;
};

int main()
{
  Date date;
  date.display();
  Date date2(2018,5,9);
  date2.display();
  Date date3();
  return 0;
}

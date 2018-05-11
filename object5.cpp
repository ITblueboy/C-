#include<iostream>
using namespace std;
class Date
{
  public:
    Date(int year=1900,int month=1,int day=1)
    {
      _year=year;
      _month=month; 
      _day=day; 
    }
    Date(const Date& d)
    :_year(d._year)
    ,_month(d._month)
    ,_day(d._day)
  {}
    Date& operator=(const Date& d1)
    {
      if(this!=&d1)
      {
        _year=d1._year;
        _month=d1._month;
        _day=d1._day;
      }
      return *this;
    }
    bool operator==(const Date& d2)
    {
      return _year==d2._year&&_month==d2._month&&_day==d2._day;
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
  Date date1(2018,5,11);
  date1.display();
  Date date2(date1);
  date2.display();
  Date date3;
  date3=date2;
  date3.display();
  Date date4(2018,5,12);
  date4.display();
  cout<<(date2==date3)<<endl;
  cout<<(date3==date4)<<endl;
  return 0;
}

#include <iostream>
using namespace std;
class Date
{
  public:
  Date(int year,int month,int day)
  {
    _year=year;
    _month=month;
    _day=day;
  }
  Date(const Date& d)
  {
    _year=d._year;
    _month=d._month;
    _day=d._day;
  }

  void display()
  {
     cout<<_year<<_month<<_day<<endl;
  }
  private:
  int _year;
  int _month;
  int _day;
};
int main()
{
  Date d(2018,5,10);
  d.display();
  Date d1=d;
  d1.display();
  return 0;
}

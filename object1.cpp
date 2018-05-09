#include <iostream>
using namespace std;

class Date
{
  public:
    Date(int year=1900,int month=1,int day=1)
      :_year(year)
      ,_month(month)
      ,_day(day)
  {}
    void display();
  private:
    int _year;
    int _month;
    int _day;
};
void Date::display()
{
      cout<<_year<<"-"<<_month<<"-"<<_day<<endl;
}
int main()
{
  Date date;
  date.display();
  Date date2(2018,5,9);
  date2.display();
  return 0;
}

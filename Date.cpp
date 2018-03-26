#include<iostream>
#include<stdio.h>
#include<assert.h>
using namespace std;
class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
		:_year(year)
		, _month(month)
		, _day(day)
	{
		if (!IsInvalid()) // this->IsInvalid(this) 
		{
			assert(false);
			//cout<<"非法日期"<	//exit(-1); 
		}
	}

	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;


	}
	Date& operator=(const Date& d)
	{
		if (this == &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		return *this;
	}
	~Date()
	{
		count << ~Date() << endl;
	}
	
	void Show()
	{
		printf("%d-%d-%d", this->_year,this->_month,this->_day);
	}
	bool IsInvalid();
	bool isLeapYear(int year);
	int GetMonthDay(int year, int month);
	bool operator==(const Date& d);
	bool operator!=(const Date& d);
	bool operator>=(const Date& d);
	bool operator<=(const Date& d);
	bool operator>(const Date& d);
		// d1 < d2 
	bool operator<(const Date& d);
		// d1 + 10 
	Date operator+(int day);
	Date& operator+=(int day);
	Date operator-(int day);
	Date& operator-=(int day);
	int operator-(const Date& d);

	//++d1 
	Date& operator++();// 前置 
		//d1++ 
	Date operator++(int); // 后置 
	Date operator--();
	Date operator--(int);
private:
	int _year;
	int _month;
	int _day;
};

bool Date::IsInvalid()
{
	return (_year > 1900) && (_month > 0 && _month < 13) && (_day>0 && _day <= GetMonthDay(_year, _month));
}
bool isLeapYear(int year)
{
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
	{
		return true;
	}
	return false;
}
int GetMonthDay(int year, int month)
{
	assert(month > 0 && month <= 12);
	int day = 0;
	int array_month[] = { 0,31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int ret = isLeapYear(year);
	if (ret == 1&&month==2)
	{
		day = array_month[month] + 1;
	}
	day = array_month[month];
	return day;
	
}
bool Date::operator==(const Date& d)
{
	return (_year == d._year) && (_month == d._month) && (_day == d._day);
}
bool Date::operator!=(const Date& d)
{
	return (_year != d._year) || (_month != d._month) || (_day != d._day);
}
bool Date::operator>=(const Date& d)
{
	return (*this == d)||(*this > d); 
}
bool Date::operator<=(const Date& d)
{
	return (*this == d) || (*this < d);
}
bool Date::operator>(const Date& d)
{
	return (_year > d._year) || ((_year == d._year) && (_month > d._month)) 
		|| ((_year == d._year) && (_month == d._month) && (_day > d._day));
}
// d1 < d2 
bool Date::operator<(const Date& d)
{
	return (_year < d._year) || ((_year == d._year) && (_month < d._month))
		|| ((_year == d._year) && (_month == d._month) && (_day < d._day));
}
// d1 + 10 
Date Date::operator+(int day)
{
	Date tmp(*this);
	if (day < 0)
	{
		return tmp - (-day);
	}
	tmp._day += day;
	while (tmp._day>GetMonthDay(tmp._year, tmp._month))
	{
		tmp._day -= GetMonthDay(tmp._year, tmp._month);
		if (tmp._month == 12)
		{
			tmp._year++;
			tmp._month = 1;
		}
		else
		{
			tmp._month++;
		}
		return tmp;
	}
}
Date& Date::operator+=(int day)
{
	*this =*this+ day;
	return *this;
}
Date Date::operator-(int day)
{
	Date tmp(*this);
	if (day < 0)
	{
		return tmp + (-day);
	}
	tmp._day -= day;
	while (tmp._day<=0)
	{
		if (tmp._month == 1)
		{
			tmp._year--;
			tmp._month = 12;
		}
		else
		{
			--tmp._month;
		}
		tmp._day += GetMonthDay(tmp._year, tmp._month);
	}
	return tmp;
}
Date& Date::operator-=(int day)
{
	*this =*this- day;
	return *this;
}
int Date::operator-(const Date& d)
{
	 Date max(*this);
	 Date min(d);
	 int day = 0;
	 int flag = 1;
	 if (max < min)
	 {
		 std::swap(max, min);
		 flag = -1;
	 }
	 while (max != min)
	 {
		 max--;
		 day++;
	 }
	 return day*flag;
}


Date& Date::operator++()// 前置 
{
	_day++;
	if (_day > GetMonthDay(_year, _month))
	{
		_day -= GetMonthDay(_year, _month);
		_month++;
		if (_month > 12)
		{
			_year++;
			_month = 1;
		}
	}
	return *this;
}

Date Date:: operator++(int) // 后置 
{
	Date tmp(*this);
	_day++;
	if (_day > GetMonthDay(_year, _month))
	{
		_day -= GetMonthDay(_year, _month);
		_month++;
		if (_month > 12)
		{
			_year++;
			_month = 1;
		}
	}
	return tmp;
}
Date Date::operator--()
{
	_day--;
	if (_day<1)
	{
		_month;
		if (_month < 1)
		{
			_year--;
			_month = 12;
		}
		_day += GetMonthDay(_year, _month);
	}
	return *this;
}

Date Date::operator--(int)
{
	Date tmp(*this);
	_day--;
	if (_day<1)
	{
		_month;
		if (_month < 1)
		{
			_year--;
			_month = 12;
		}
		_day += GetMonthDay(_year, _month);
	}
	return tmp;
}

int main()
{
	Date d1;
	//d1.Show(); 

	Date d2(2017, 2, 28);
	//d2.Show(); 

	++d1; // d1.operator++(&d1); 
	d1++; // d1.operator++(&d1, 0); 

	return 0;
}
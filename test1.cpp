#include<iostream>
#include<stdio.h>
#include<windows.h>
using namespace std;

//class Date//const类函数
//{
//	friend void Display(const Date & d);
//private:
//	int _year; // 年
//	int _month; // 月
//	int _day; // 日
//};
//void Display(const Date& d)
//{
//	cout << "Display" << endl;
//	cout << "year:" << d._year << endl;
//	cout << "month:" << d._month << endl;
//	cout << "day:" << d._day << endl;
//}
//void Test()
//{
//	Date d1;
//	Display(d1);
//}
//
//int main()
//{
//	Test();
//	system("pause");
//	return 0;
//}
class Time
{
	// Date是Time 的友元，所以 Date可以访问Time的所有成员。
	friend class Date;
private:
	int _hour;
	int _minute;
	int _second;
};
class Date
{
public:
	void Display()
	{
		cout << "year:" << _year << endl;
		cout << "month:" << _month << endl;
		cout << "day:" << _day << endl;
		// 定义为友元类后，可以访问Time类对象的所有成员
		cout << "hour:" << _t._hour << endl;
		cout << "minute:" << _t._minute << endl;
		cout << "second:" << _t._second << endl << endl;
	}
private:
	int _year; // 年
	int _month; // 月
	int _day; // 日
	Time _t;
};
void Test()
{
	Date d1;
	d1.Display();
}
int main()
{
	Test();
	system("pause");
	return 0;
}
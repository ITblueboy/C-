#include<iostream>
#include<stdio.h>
#include<windows.h>
using namespace std;

//class Date//const�ຯ��
//{
//	friend void Display(const Date & d);
//private:
//	int _year; // ��
//	int _month; // ��
//	int _day; // ��
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
	// Date��Time ����Ԫ������ Date���Է���Time�����г�Ա��
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
		// ����Ϊ��Ԫ��󣬿��Է���Time���������г�Ա
		cout << "hour:" << _t._hour << endl;
		cout << "minute:" << _t._minute << endl;
		cout << "second:" << _t._second << endl << endl;
	}
private:
	int _year; // ��
	int _month; // ��
	int _day; // ��
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
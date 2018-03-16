#include<iostream>
#include<Windows.h>
using namespace std;

int main()
{
	int a = 0;
	int& b = a;
	cout << "a:address:" << &a << endl;
	cout << "b:address:" << &b << endl;
	system("pause");
	return 0;
}


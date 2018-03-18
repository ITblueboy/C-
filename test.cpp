#include<iostream>
#include<Windows.h>
using namespace std;

int ret = 0;
int Add1(int m, int n)
{
	int ret1 = m + n;
	return ret1;
}
int& Add2(int m, int n)
{
	int ret = m + n;
	return ret;
}
int main()
{
	int a = 1;
	int b = 5;
	printf("%d", Add1(a, b));
	printf("%d", Add2(a, b));
	system("pause");
	return 0;
}

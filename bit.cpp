#include<stdio.h>
#include<Windows.h>


struct AA
{
	int _a : 2;
	int _b : 5;
	int _c : 10;
	int _d : 30;
}aa;

int main()
{
	printf("%d\n", sizeof(aa));
	system("pause");
	return 0;
}
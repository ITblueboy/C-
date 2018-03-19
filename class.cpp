#include<iostream>
#include<stdio.h>
#include<stddef.h>
using namespace std;

class B
{
public:
	void fun()
	{
		printf("hello world\n");
	}
private:
	char _a = 5;
};
typedef struct A
{
	char a = 5;
}A;
int main()
{
	B b;
	cout << "%d "<< sizeof(b) << endl;
	cout << "%d" << sizeof(A) << endl;
	return 0;
}

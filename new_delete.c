#include<iostream>
#include<Windows.h>
using namespace std;

class Array
{
public:
	Array(size_t size = 10)
		: _size(size)
		, _a(0)
	{
		cout << "Array(size_t size)" << endl;
		if (_size > 0)
		{
			_a = new int[size];
		}
	}
	~Array()
	{
		cout << "~Array()" << endl;
		if (_a)
		{
			delete[] _a;
			_a = 0;
			_size = 0;
		}
	}
private:
	int*_a;
	size_t _size;
};

void Test()
{
	Array* p1 = (Array*)malloc(sizeof(Array));
	Array* p2 = new Array;
	Array* p3 = new Array(20);
	Array* p4 = new Array[10];
	free(p1);
	delete p2;
	delete p3;
	delete[] p4;
}

int main()
{
	Test();
	system("pause");
	return 0;
}


#include <iostream>
using namespace std;

#include <vector>
#include <map>
#include <string>
#include <list>

void test1()
{
	vector<int> v{1,2,3,4};
	for (size_t i = 0; i < v.size(); ++i)
	{
		cout << v[i] << endl;
	}

	map<string, string> dict{ { "insert", "����" }, { "sort", "����" } };
	map<string, string>::iterator dit = dict.begin();
	while (dit != dict.end())
	{
		cout << dit->first << ":" << dit->second << endl;
		++dit;
	}
	cout << endl;
}

void test2()
{
	int a = 10;
	auto b = 11;
	auto c = 1.1;
	//auto d;

	// RTTI
	cout << typeid(b).name() << endl;
	cout << typeid(c).name() << endl;

	map<string, string> dict{ { "insert", "����" }, { "sort", "����" } };
	map<string, string>::iterator dit1 = dict.begin();
	while (dit1 != dict.end())
	{
		cout << dit1->first << ":" << dit1->second << endl;
		++dit1;
	}

	auto dit2 = dict.begin();
	while (dit2 != dict.end())
	{
		cout << dit2->first << ":" << dit2->second << endl;
		++dit2;
	}

	for (auto kv : dict)
	{
		cout << kv.first << ":" << kv.second << endl;
	}

	//int array[] = { 1, 2, 3, 4, 5 };
	//for (auto& e : array) // ��ֵ
	//{
	//	if (e % 2 == 0)
	//		e *= 2;
	//}
	//cout << endl;

	//for (auto e : array)
	//{
	//	cout << e << " ";
	//}
	//cout<<endl;
}

void test3()
{
	/*int x = 10;
	auto a = &x;
	auto* b = &x;
	auto& c = x;
	int& e = x;
	cout << typeid(a).name() << endl;
	cout << typeid(b).name() << endl;
	cout << typeid(c).name() << endl;
	cout << typeid(e).name() << endl;*/

	// const ���� auto�������ܴ���
	/*const int x = 10;
	auto y = x;
	auto z = 10;
	y = 19;*/

	// volatile���� auto�������Դ���
	volatile const int x = 10;
	int* p = (int*)&x;
	*p = 20;
	cout << x << endl;

	const auto y = x;
	int* pp = (int*)&y;
	*pp = 30;
	cout << y << endl;

	//cout << typeid(y).name() << endl;
}

void test4()
{
	int a = 10;
	auto b = a;
	decltype(a) c;
}

int add1(int x, int y)
{
	return x + y;
}

struct Add2
{
	int operator()(int x, int y)
	{
		return x + y;
	}
};

//template<class Container>
//void PrintContainer(const Container& c)
//{
//	typename Container::const_iterator it = c.begin();
//	while (it != c.end())
//	{
//		cout << *it << " ";
//		++it;
//	}
//	cout << endl;
//}

//template<class Container>
//void PrintContainer(const Container& c)
//{
//	auto it = c.begin();
//	while (it != c.end())
//	{
//		cout << *it << " ";
//		++it;
//	}
//	cout << endl;
//}

template<class Container>
void PrintContainer(const Container& c)
{
	for (auto e : c)
	{
		cout << e << " ";
	}
	cout << endl;
}

void test5()
{
	cout << add1(1, 2) << endl;

	Add2 add2;
	cout << add2(1, 2) << endl;

	double rate = 1.2;

	// ��򵥵�lambda���ʽ
	auto lam = []{};

	auto add3 = [](int x, int y, double rate)->double{return (x + y)*rate; };
	cout << add3(1, 2, rate) << endl;

	//auto add4 = [=](int x, int y)->double{return (x + y)*rate; };
	//auto add4 = [&](int x, int y)->double{return (x + y)*rate; };
	auto add4 = [rate](int x, int y)->double{return (x + y)*rate; };
	//auto add4 = [&rate](int x, int y)->double{return (x + y)*rate; };

	cout << add4(1, 2) << endl;

	int a = 10, b = 20;
	auto swap1 = [](int& x1, int& x2){int x = x1; x1 = x2; x2 = x; };
	swap1(a, b);
	cout << a << " " << b << endl;

	auto swapab = [&a,&b](){int x = a; a = b; b = x; };
	swapab();
	cout << a << " " << b << endl;

	auto swap3 = [&](){int x = a; a = b; b = x; };
	swap3();
	cout << a << " " << b << endl;

	vector<int> v1{ 1, 2, 3, 4, 5 };
	vector<string> v2{ "11", "22", "33", "44", "55"};
	list<int> l1{ 10, 20, 30 };

	PrintContainer(v1);
	PrintContainer(v2);
	PrintContainer(l1);

	auto print_containerv1 = [&v1]()
	{
		for (auto e : v1)
		{
			cout << e << " ";
		}
		cout << endl;
	};

	print_containerv1();
}

// C++11���˽�ʲô����

// 1.RTTI
// auto/decltype(�˽�)/typeid/dynamic_cast
// a. auto��ʲô����
// b. auto��ʲô�ô�(�򻯴���)����ʲô����(�ɶ��Ա��)

// 2.for 
// ���ã������޸����顢����
// ȱ�㣺Υ����ͳC�÷����ɶ����ϵ�����

// 3.lambda
// a.дһ��lambda���ʽ����������
// b.���������lambda��ô�ã�С����������Ҫ��������
// �ŵ㣺��ࡢ���ٵ�������Ⱦ��
// ȱ�㣺�ɶ��Ա�ά���ɱ���ߡ���������ԡ�

int main()
{
	//test1();
	//test2();
	//test3();
	test5();

	return 0;
}
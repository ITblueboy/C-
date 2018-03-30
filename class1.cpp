//#include <iostream>
//using namespace std;
//
//class Date
//{
//public :
//	Date()
//	{
//		cout<<"Date()" <<endl;
//	}
//
//	Date(const Date& d)
//	{
//		cout<<"Date(const Date& d)" <<endl;
//	}
//
//	Date& operator =(const Date& d )
//	{
//		cout<<"Date& operator=(const Date& d)"<< endl;
//
//		return *this ;
//	}
//
//	~ Date()
//	{
//		cout<<"~Date()" <<endl;
//	}
//};
//
//void fun1 (Date d) //void fun1(Date& d)
//{}
//
//Date func2()
//{
//	//Date ret;
//	return Date();
//}
//
//class AA
//{
//public:
//	AA()
//	{
//	}
//	AA(const AA& a)
//	{
//		cout<<"AA(const AA& a)"<<endl;
//	}
//};
//AA f (AA a)
//{
//	return a ;
//}
//void Test1 ()
//{
//	AA a1 ;
//	a1 = f(a1);
//}
//void Test2 ()
//{
//	AA a1 ;
//	AA a2 = f(a1);
//}
//
//void Test3 ()
//{
//	AA a1 ;
//	AA a2 = f(f(a1));
//}
//
//
//struct BB
//{
//	int _b;
//
//	void f()
//	{
//		cout<<"aaaaaa"<<endl;
//	}
//};
//
//int main()
//{
//	//fun1(Date());
//	//Date d2 = func2();
//	//Test3();
//
//	//struct BB b;
//
//	//BB b;
//	//b.f();
//
//	int i = 10;
//	i = int();
//	i = int(20);	
//
//	return 0;
//}


#include <iostream>
using namespace std;

class AA
{
public:
	AA()
	{
		cout<<"AA()"<<endl;

		_a = new int[10];
	}

	~AA()
	{
		cout<<"~AA()"<<endl;

		delete[] _a;
	}

	int* _a;
};

int main()
{
	/*int* p4 = new int;
	int* p6 = new int[3];*/
	int* p7 = (int*) malloc(sizeof (int));

	/*free(p4);
	free(p6);*/
	delete[] p7;

	/*AA* p4 = new AA;
	delete p4;
	free(p4);

	delete[] p4;

	AA* p6 = new AA[10];
	free(p6);
	delete p6;

	int* p7 = new int;
	delete[] p7;
	AA* p5 = (AA*)malloc(sizeof(AA));
	free(p5);
*/
	return 0;
}

//#include <iostream>
//using namespace std;
//
//class AA
//{
//public:
//	//AA()
//	//{
//	//	cout<<"AA()"<<endl;
//	//}
//
//	~AA()
//	{
//		cout << "~AA()" << endl;
//	}
//
//private:
//	int _a;
//};
//int main()
//{
//	//int* p1 = (int*)operator new(4);
//
//	//AA* p1 = new AA;
//	//delete p1;
//
//	//try
//	//{
//	//	char* p2 = (char*)operator new(0x7fffffff); // == malloc
//	//	printf("%p\n", p2);
//	//}
//	//catch (exception e)
//	//{
//	//	cout<<e.what()<<endl;
//	//}
//
//	/*AA* p0 = new AA;
//	free(p0);
//	int a = 0;
//	delete[] p0;*/
//
//	AA* p1 = new AA[10];
//	/*free(p1);*/
//	delete p1;
//	/*delete p1;*/
//
//	/*int* p2 = new int[10];
//	delete p2;
//*/
//
//	return 0;
//}
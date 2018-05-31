 
#include<stdint.h>
#include<string.h>
#include<iostream>
using namespace std;
class String
{
public:
	String(const char* str = "")
    :_str(new char[strlen(str)+1])
  {
    _size=strlen(str);
    _capacity=_size;
    strcpy(_str,str);
  }
		// s1.Swap(s2); 
	void Swap(String& s)
  {
    swap(_str,s._str);
    swap(_size,s._size);
    swap(_capacity,s._capacity);
  }

		// String s2(s1) 
	String(const String& s)
    :_str(NULL)
    ,_size(0)
    ,_capacity(0)
  {
    String tmp(s._str);
    Swap(tmp);
  }
	// s1 = s2 
	String& operator=(String s)
  {
    Swap(s);
    return *this;
  }

	~String()
  {
    if(_str)
    {
      delete[] _str;
      _str=NULL;
    }
  }

	const char* c_str()
  {
    return _str;
  }
	void Expand(size_t n)
  {
    if(n>_capacity)
    {
      char* str=new char[(n+1)];
      strcpy(str,_str);
      delete[] _str;
      _str=str;
      _capacity=n;
    }
  }
	void PushBack(char ch);
	void PushBack(const char* str);
  void PushFront(char ch);
  void PushFront(const char* str);
	void PopBack();
	void Insert(size_t pos, char ch);
	void Insert(size_t pos, const char* str);
	void Erase(size_t pos, size_t n = 1);


	size_t Find(char ch);
	size_t Find(const char* str); // ? 

	// s1 + 'a' 
	String operator+(char ch);
	String& operator+=(char ch);
	String operator+(const char* str);
	String& operator+=(const char* str);

	bool operator>(const String& s);
	bool operator>=(const String& s);
	bool operator<(const String& s);
	bool operator<=(const String& s);
	bool operator==(const String& s);
	bool operator!=(const String& s);

private:
	char* _str;
	size_t _size;
	size_t _capacity;
};


#include<iostream>
#include<string.h>
using namespace std;

class String
{
  public:
    String(char* str="" )
      :_str(new char[strlen(str)+5])
    {
      *(int*)_str=1;
      _str+=4;
      strcpy(_str,str);
    }

    String(const String& s)
      :_str(s._str)
    {
      ++(*(int*)(s._str-4));
    }

    String& operator=(const String& s)
    {
      if(--(*(int*)(_str-4))==0)
      {
        delete[] (_str-4);
        _str=s._str;
        ++(*(int*)(_str-4));
      }
      return *this;
    }

    ~String()
    {
      if(--(*(int*)(_str-4))==0)
      {
        delete[] (_str-4);
      }
    }

    void CopyOnWrite()
    {
      if((*(int*)(_str-4))>1)
      {
        char* newstr=new char[strlen(_str)+5];
        --(*(int*)(_str-4));
        strcpy(newstr+4,_str);
        _str=newstr+4;
        *((int*)(_str-4))=1;
      }
    }

    char& operator[](size_t pos)
    {
      CopyOnWrite();
      return _str[pos];
    }

    const char* c_str()
    {
      return _str;
    }


  private:
    char* _str;
};

int main()
{
  String s1("");
  String s2("i love you!");
  String s3(s2);
  s1=s3;
  s3.operator[](0)='h';
  cout<<s1.c_str()<<endl;
  cout<<s2.c_str()<<endl;
  cout<<s3.c_str()<<endl;
  cout<<(*(int*)(s2.c_str()-4))<<endl;
  cout<<(*(int*)(s3.c_str()-4))<<endl;
  return 0;
}

#include<iostream>
#include<string.h>
using namespace std;

class String
{
  public:
    String(char* str="")
      :_str(new char[strlen(str)+1])
      ,_pcount(new size_t(1))
    {
      strcpy(_str,str);
    }

    String(const String& s )
      :_str(s._str)
      ,_pcount(s._pcount)
    {
      _pcount++;
    }

    String& operator=(const String& s)
    {
      if(_str!=s._str)
      {
        if(--(*_pcount)==0)
        {
          delete[] _str;
          delete _pcount;
        }
        _str=s._str;
        _pcount=s._pcount;
        (*_pcount)++;
      }
      return *this; 
    }

    ~String()
    {
      if(--(*_pcount)==0)
      {
        delete[] _str;
        delete _pcount;
      }
    }

    const char* c_str()
    {
      return _str;
    }

    char& operator[](size_t pos)
    {
      CopyOnWrite();
      return *(_str+pos);
    }

    void CopyOnWrite()
    {
      if(*_pcount>1)
      {
        char* newstr=new char[strlen(_str)+1];
        strcpy(newstr,_str);
        --(*_pcount);

        _str=newstr;
        _pcount=new size_t(1);
      }
    }
  private:
    char* _str;
    size_t* _pcount;
};

int main()
{
  String s1("");
  String s2("i love you!");
  String s3(s2);
  s1=s2;
  cout<<s1.c_str()<<endl;
  cout<<s2.c_str()<<endl;
  cout<<s3.c_str()<<endl;
  s3.operator[](0)='h';
  cout<<s3.c_str()<<endl;
  return 0;
}

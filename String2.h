#pragma once 
#include<unistd.h>
#include<string.h>

class String
{
  public:
    String(const char* str)
      :_str(new char[strlen(str)+1])
    {
      strcpy(_str,str);
    }
    String(const String& s)
    {
      _str=new char[strlen(s._str)+1];
      strcpy(_str,s._str);
    }
    String& operator=(const String& s)
    {
      if(this!=&s)
      {
        delete[] _str;
        _str=new char[strlen(s._str)+1];
        strcpy(_str,s._str);
      }
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
   const char* C_str()
    {
      return _str;
    }
  private:
    char* _str;
};

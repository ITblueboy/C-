#include"String.h"
#include<assert.h>

void String::PushBack(char ch)
{
  if(_size>=_capacity)
  {
    Expand(_capacity*2);
  }
  _str[_size++]=ch;
  _str[_size]='\0';
}

void String::PushBack(const char* str)
{
  size_t len=strlen(str);
  if(_size+len>_capacity)
  {
    Expand(_size+len);
  }
  strcpy(_str+_size,str);
  _size=_size+len;
}

void String::PushFront(char ch)
{
  if(_size>=_capacity)
  {
    Expand(_capacity*2);
  }
  int i=_size;
  while(i>=0)
  {
    _str[i+1]=_str[i];
    i--;
  }
  _str[0]=ch;
  _size++;
}

void String::PushFront(const char* str)
{
  size_t len=strlen(str);
  if(_size+len>_capacity )
  {
    Expand(_size+len);
  }
  int i=_size;
  while(i>=0)
  {
    _str[len+i]=_str[i];
    i--;
  }
  char* p=_str;
  while(*str!='\0')
  {
    *p++=*str++;
  }
  _size=_size+len;
}

void String:: PopBack()
{
  _str[--_size]='\0';
}

void String:: Insert(size_t pos,char ch)
{
  assert(pos<=_size);
  if(_size>=_capacity)
  {
    Expand(_capacity*2);
  }
  int i=_size;
  while((int)pos<=i)
  {
    _str[i+1]=_str[i];
    i--;
  }
  _str[pos]=ch;
  _size++;
}

void String::Insert(size_t pos,const char* str)
{
  assert(pos<=_size);
  size_t len=strlen(str);
  if((_size+len)>_capacity)
  {
    Expand(_size+len);
  }
  int i=_size;
  while(i>=(int)pos)
  {
    _str[len+i]=_str[i];
    i--;
  }
  while(*str!='\0')
  {
    _str[pos++]=*str++;
  }
  _size=_size+len;
}

void String::Erase(size_t pos,size_t n)
{
  assert(pos<_size);
  size_t i=pos+n;
  if(i>=_size)
  {
    _str[pos]='\0';
    _size-=n;
  }
  else 
  {
    while((int)i<(int)_size) 
  {
    _str[pos++]=_str[i];
    i++;
  }
  _size-=n;
  }
}

size_t String::Find(char ch)
{
  int i=0;
  while(i<=(int)_size)
  {
    if(_str[i]==ch)
    {
      return (size_t)i;
    }
    i++;
  }
  return size_t(-1);
}

size_t String::Find(const char* str)
{
  assert(_str!=NULL&&str!=NULL);
  int cur=0;
  int res=0;
  int len=strlen(str);
  while(cur<(int)_size-len)
  {
    int begin=res=cur;
    int str_cur=0;
    while(str_cur<len && begin<(int)_size && _str[begin]==str[str_cur])
    {
      str_cur++;
      begin++;
    }
    if(str_cur==len)
    {
      return (size_t)res;
    }
    cur++;
  }
  return size_t(-1);
}

String String::operator+(char ch)
{
  String tmp(_str);
  tmp.PushBack(ch);
  return tmp;
}

String& String::operator+=(char ch)
{
  PushBack(ch);
  return *this;
}

String String::operator+(const char* str)
{
  String tmp(_str);
  tmp.PushBack(str);
  return tmp;
}

String& String::operator+=(const char* str)
{
  PushBack(str);
  return *this;
}

bool String::operator>(const String& s)
{
  const char* p1=_str;
  const char* p2=s._str;
  while(*p1&&*p2)
  {
    if(*p1>*p2)
    {
      return true;
    }
    else if(*p1<*p2)
    {
      return false;
    }
    else 
    {
      p1++;
      p2++;
    }
  }
  if(*p1)
  {
    return true;
  }
  else 
  {
    return false;
  }
}

bool String::operator>=(const String& s)
{
  return _str>s._str || _str==s._str;
}

bool String::operator<(const String& s)
{
  return !(_str>=s._str);
}

bool String::operator<=(const String& s)
{
  return !(_str>s._str);
}

bool String::operator==(const String& s)
{
  const char* p1=_str;
  const char* p2=s._str;
  while(*p1&&*p2)
  {
    if(*p1!=*p2)
    {
      return false;
    }
    else 
    {
      p1++;
      p2++;
    }
  }
    if(*p1=='\0'&&*p2=='\0')
    {
      return true;
    }
    else 
    {
      return false;
    }
}

bool String::operator!=(const String& s)
{
  return !(_str==s._str);
}

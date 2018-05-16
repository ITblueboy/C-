#include <stdio.h>
#include<iostream>
#include<stdlib.h>
using namespace std;
int main()
{
  char* env=getenv("MYENV");
  if(env)
  {
    printf("%s\n",env);
  }
  return 0;
}

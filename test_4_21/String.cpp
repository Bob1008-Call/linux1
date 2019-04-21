#include <assert.h>
#include "String.hpp"
void String::Show()
{
  cout<<"_str"<<_str<<endl;
}

void String::Swap(String& s)
{
  _size = s._size;
  _capacity = s._capacity;
  delete _str;
  _str = s._str;
  s._str = new char[1];
}

String& String::operator=(String s)
{
  Swap(s);
  return *this;
}

const char* String::c_Str()
{
  return _str;
}

void String::Expand(size_t n)
{
  char* tmp = new char[n];
  memcpy(tmp,_str,_size+1);
  delete _str;
  _str = tmp;
  _capacity = n;
}

void String::PushBack(char c)
{

}

void String::Insert(size_t pos,char c)
{
  assert(_size>pos);
  if(_size >= _capacity-1)
  {
    Expand(2*_capacity+1);
  }
  for(size_t i = _size;i>pos;--i)
  {
    _str[i] = _str[i-1];
  }
  _str[pos] = c;
  ++_size;
}

void String::Insert(size_t pos,const char* str)
{
  assert(pos < _size);
  
}

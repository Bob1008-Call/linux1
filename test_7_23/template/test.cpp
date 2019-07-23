#include "test.h"

template void Swap<int>(int &a,int &b);

template<class T>
void Swap(T& a, T& b)
{
  T temp = a;
  a = b;
  b = temp;
}

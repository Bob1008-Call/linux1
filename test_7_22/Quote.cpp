#include <iostream>
using namespace std;

int value[10];
int error = 1;

int& func(int n)
{
  if(n >= 0 && n <= 10)
  {
    return value[n];
  }
  else 
  {
    return error;
  }
}

int main()
{
  func(10) = 1;
  func(5) = 12;
  cout << "value[10]:" << value[10] << " value[5]:" << value[5] << endl;
  return 0;
}

#include <iostream>
using namespace std;

float temp;
float func1(float r)
{
  temp = r * r * 3.14;
  return temp;
}

float& func2(float r)
{
  temp = r * r * 3.14;
  return temp;
}

int main()
{
  float a = func1(5.0);

  float b = func2(5.0);

  //float& c = func1(5.0);

  float& d = func2(5.0);

  cout << "a:" << a << endl;
  cout << "b:" << b << endl;
  //cout << "c:" << c << endl;
  cout << "d:" << d << endl;
  return 0;
}

#pragma once
#include <iostream>
#include <vector>

using namespace std;

#if 0
int main()
{
  vector<int> v;
  size_t sz = 0;
  for(int i = 0;i<100;++i)
  {
    v.push_back(i);
    if(sz != v.capacity())
    {
      cout<<"capacity changed:"<<sz<<endl;
      sz = v.capacity();
    }
  }
  return 0;
}
#endif

class A
{
public:
  virtual void fun()
  {
    cout<<"virtual"<<endl;
  }
};

int main()
{
  cout<<sizeof(A)<<endl;
  return 0;
}

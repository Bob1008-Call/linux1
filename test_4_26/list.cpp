#include <list>
#include <iostream>
#include <typeinfo>
using namespace std;
#if 0

int main()
{
  list<int> l1;

  int array[] = {1,2,3,4};
  
  list<int> l2(array,array+sizeof(array)/sizeof(int));
  for(list<int>::iterator it = l2.begin();it != l2.end();++it)
  {
    cout<<*it<<" ";
  }
  cout<<endl;

  for(list<int>::reverse_iterator it = l2.rbegin();it != l2.rend();++it)
  {
    cout<<*it<<" ";
  }
  cout<<endl;

  auto cit = l2.begin();
  cout<<typeid(cit).name()<<endl;
  return 0;
}
#endif

int main()
{
  int array[] = {1,2,3,4,5,6,7,8,9,0};
  list<int> l1(array,array+sizeof(array)/sizeof(int));
  l1.front() = 10;
  l1.back() = 10;
  
  for(auto& e : l1)
  {
    cout<<e<<" ";
  }
  cout<<endl;

  const list<int> l2(array,array + sizeof(array)/sizeof(int));
  const int& c = l2.front();
  return 0;
}



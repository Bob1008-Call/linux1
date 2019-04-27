#include <set>
#include <map>
#include <string>
#include <iostream>
using namespace std;

#if 0
int main()
{
  multimap<string,string> m;
  m.insert(make_pair("李逵","黑旋风"));
  m.insert(make_pair("林冲","豹子头"));
  m.insert(make_pair("李逵","铁牛"));
  for(auto& e : m)
  {
    cout<<e.first<<"-->"<<e.second<<endl;
  }
  cout<<m.count("李逵");
  return 0;
}
#endif
//
//int main()
//{
//  multimap<int,int,less<int>> m;
//  m.insert(make_pair(1,2));
//  m.insert(make_pair(3,3));
//  m.insert(make_pair(6,8));
//  m.insert(make_pair(2,6));
//  m.insert(make_pair(5,5));
//  m.insert(make_pair(9,7));
//  for(auto e = m.begin();e != m.end();++e)
//  {
//    cout<<e->first<<"->"<<e->second<<endl;
//  }
//  return 0;
//}

//
//int main()
//{
//  multiset<int,less<int>> s;
//  s.insert(2);
//  s.insert(1);
//  s.insert(1);
//  s.insert(5);
//  s.insert(6);
//  s.insert(8);
//  for(auto e = s.begin();e != s.end();++e)
//  {
//    cout<<*e<<endl;
//  }
//  return 0;
//}

int main()
{
  
  return 0;
}

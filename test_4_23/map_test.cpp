#include <map>
#include <iostream>
using namespace std;
#if 0
int main()
{
  
  map<int,string,greater<int>> stringmap;
  map<int,string>::const_iterator it;
  stringmap[2] = "天蓬元帅";
  stringmap[1] = "齐天大圣";
  it = stringmap.find(1);
  //find函数返回值是迭代器
  stringmap.insert(make_pair<int,string>(3,"阿弥陀佛"));
  for(auto e : stringmap)
  {
    cout<<e.first<<":"<<e.second<<endl;
  }
  return 0;
}
#endif

int main()
{
  map<string,string> m;
  m["apple"] = "苹果";
  m["apple"] = "小苹果";
  m["apple"] = "小苹果";
  for(auto e = m.begin();e != m.end();++e)
  {
    cout<<e->first<<"-->"<<e->second<<endl;
  }
  m.insert(pair<string,string>("banana","香蕉"));
  cout<<m.at("banana")<<endl;
  return 0;
}

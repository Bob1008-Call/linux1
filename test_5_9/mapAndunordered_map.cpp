#include <map>
#include <unordered_map>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
  map<string,int> m;
  unordered_map<string,int> u_m;
  m.insert(pair<string,int>("abc",1));
  u_m.insert(pair<string,int>("xyz",2));

  map<string,int>::iterator it1 = m.begin();
  unordered_map<string,int>::iterator it2 = u_m.begin();

  m.insert(it1,pair<string,int>("uvw",3));
  vector<string> v_s{"abc","def","ghi","jkl"};
  for(int i = 0;i<4;++i)
  {
    u_m.insert(it2,pair<string,int>(v_s[i],i));
  }

  for(auto e1 : m)
  {
    cout<<e1.first<<"->"<<e1.second<<endl;
  }

  for(auto e2 : u_m)
  {
    cout<<e2.first<<"->"<<e2.second<<endl;
  }
  return 0;
}


#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
class solution
{
public:
  std::vector<int> topKFrequent(std::vector<int> v,int k)
  {
    for(auto& e : v)
    {
      up[e]++;
    }
    for(auto& e : up)
    {
      mp.insert(std::make_pair(e.second,e.first));
    }
    for(auto e = mp.begin();e != mp.end();++e)
    {
      if(k == res.size())
      {
        break;
      }
      res.push_back(e->first);
    }
    return res;
  }
private:
  std::vector<int> res;
  std::unordered_map<int,int> up;
  std::multimap<int,int,std::greater<int>> mp;
};

int main()
{
  std::vector<int> v{1,2,3,4,5,6,7,6,6,5,6,7,7,7};
  solution s;
  std::vector<int> res;
  res = s.solution::topKFrequent(v,2);
  for(int i = 0;i<res.size();++i)
  {
    std::cout<<res[i]<<std::endl;
  }
  return 0;
}

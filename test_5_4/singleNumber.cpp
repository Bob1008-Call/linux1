#include <vector>
#include <iostream>
using namespace std;

class Solution
{
  public:
    vector<int> SingleNumber(vector<int>& nums)
    {
      int temp = 0;
      //for(int i = 0;i<nums.size();++i)
      //{
      //  temp ^= nums[i];
      //}
      for(auto e : nums)
      {
        temp ^= e;
      }
      size_t j;
      for(j = 0;j<nums.size();++j)
      {
        if(((temp >> j) & 1) == 1)
        {
          break;
        }
      }
      int res1 = 0;
      int res2 = 0;
      for(auto e : nums)
      {
        if(((e >> j) & 1) == 1)
        {
          res1 ^= e;
        }
        else 
        {
          res2 ^= e;
        }
      }
      return {res1,res2};
    }
};

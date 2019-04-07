//区域和检索 - 数组不可变
#include <vector>
using namespace std;
class NumArray {
public:
    NumArray(vector<int>& nums) {
       if(!nums.empty())
       {
            _arr.push_back(nums[0]);
            for(int i = 1;i < nums.size();++i)
            {
                _arr.push_back(_arr.back() + nums[i]);
            }
       }
    }
    
    int sumRange(int i, int j) {
        if(i == 0)
        {
            return _arr[j];
        }
        return _arr[j] - _arr[i-1];
    }
private:
    vector<int> _arr;
};

//
// Your NumArray object will be instantiated and called as such:
// NumArray* obj = new NumArray(nums);
// int param_1 = obj->sumRange(i,j);
//

//打家劫舍
class Solution1 {
public:
    int rob(vector<int>& nums) {
        if(nums.size() == 0)
            return 0;
        if(nums.size() == 1)
            return nums[0];
        vector<int> res;
        res.push_back(nums[0]);
        if(nums.size() == 2)
            return nums[0]>nums[1]?nums[0]:nums[1];
        res.push_back(max(nums[0],nums[1]));
        for(int i = 2;i < nums.size();++i)
            res.push_back(max(nums[i]+res[i-2],res[i-1]));
        
        return res[res.size()-1];
    }
};

//买卖股票的最佳时机
class Solution2 {
public:
    int maxProfit(vector<int>& prices) {
        int max = 0;
        int tmp = 0;
        for(int i = 0;i<prices.size();++i)
        {
            for(int j = i;j<prices.size();++j)
            {
                tmp = prices[j] - prices[i];
                if(max < tmp)
                    max = tmp;
            }
        }
        return max;
    }
};

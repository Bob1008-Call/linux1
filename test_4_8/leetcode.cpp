#include <vector>
using namespace std;
#include <iostream>
//最大子序列普通解法
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int max = INT_MIN;
        int sum = 0;
        int i = 0;
        while(i<nums.size())
        {
            sum += nums[i];
            if(sum > max)
            {
                max = sum;
            }  
            if(sum < 0)
            {
                sum = 0;
            }   
            i++;
        }
        return max;
    }
};
class Solution1 {
public:
    int maxSubArray(vector<int>& nums) {
        int ans;
        int len = nums.size();
        vector<int>dp(len);
        dp[0] = ans = nums[0];
        for(int i = 1;i < len;++i)
        {
            dp[i] = max(dp[i-1] + nums[i],nums[i]);
            ans = max(ans,dp[i]);
        }
        return ans;
    }
};
//花费最小爬楼梯
class Solution3 {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        vector<int> res(cost.size()+1,0);
        for(int i = 2;i<cost.size()+1;++i)
        {
            res[i] = min(res[i-1]+cost[i-1],res[i-2]+cost[i-2]);
        }
        return res.back();
    }
};


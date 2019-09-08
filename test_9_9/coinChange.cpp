#include <vector>
#include <algorithm>
using namespace std;

class Solution {
  public:
    int coinChange(vector<int>& coins, int amount) {
          int INF = amount + 1;
              vector<int> dp(amount + 1, INF);
                  dp[0] = 0;
                  for (int i = 0; i<coins.size(); i++){
                    for (int j = coins[i]; j<amount + 1; j++){
                              dp[j] = min(dp[j], dp[j - coins[i]] + 1);//状态转移方程
                                    
                    }
                        
                  }
                      return dp[amount]<INF ? dp[amount] : -1;
                        
    }

};

int main()
{
    Solution s;
      vector<int> v{ 1, 2, 5  };
        int a = 11;
          s.coinChange(v, a);
            return 0;

}

#include <algorithm>
#include <vector>
#include <iostream>
#include <stdio.h>
using namespace std;
double Result(vector<vector<int> > map)
{
	int N = map.size();
	int M = map[0].size();
	vector<vector<double> > dp(N, vector<double>(M, 0));
	for (int i = 1; i < N; ++i)
	{
		for (int j = 1; j < M; ++j)
		{
			if (i == 1 && j == 1)
			{
				dp[i][j] = map[i][j] == 1 ? 0 : 1;
				continue;
			}
			if (map[i][j] == 1)
			{
				dp[i][j] = 0;
			}
			else
			{
				if (i == N-1 && j == M-1)
				{
					dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
				}
				else if (i == N-1)
				{
					dp[i][j] = dp[i - 1][j] * 0.5 + dp[i][j - 1];
				}
				else if (j == M-1)
				{
					dp[i][j] = dp[i - 1][j] + dp[i][j - 1] * 0.5;
				}
				else
				{
					dp[i][j] = (dp[i - 1][j] + dp[i][j - 1])*0.5;
				}
			}
		}
	}
	return dp[N-1][M-1];
}

int main()
{
  int N,M,K;
  while(scanf("%d%d%d",&N,&M,&K)!=EOF)
  {
    vector<vector<int> > map(N+1,vector<int>(M+1,0));
    while(K--)
    {
      int x,y;
      cin>>x>>y;
      map[x][y] = 1;
    }
    double res = Result(map);
    cout<<res<<endl;
  }
  return 0;
}

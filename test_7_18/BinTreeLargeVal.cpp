#include <vector>
#include <queue>
#include <limits.h>
#include <stdlib.h>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<int> largestValues(TreeNode* root) 
		{
      queue<TreeNode*> q; 
      vector<int> res;
      if(root == NULL)
      {
        return res;
      }
      q.push(root);
      while(!q.empty())
      {
        int size = q.size();
        int max = INT_MIN;
        for(int i = 0; i < size;++i)
        {
          struct TreeNode* cur = q.front();
          q.pop();
          if(cur->val > max)
            max = cur->val;
          if(cur->left)
            q.push(cur->left);
          if(cur->right)
            q.push(cur->right);
        }
        res.push_back(max);
      }
      return res;
    }
};

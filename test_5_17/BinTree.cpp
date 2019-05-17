#include <stdlib.h>
#include <queue>
#include <vector>
using namespace std;
  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };
class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> res;
        if(NULL == root)
        {
            return {};
        }
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty())
        {
            vector<int> tmp;
            int size = q.size();
            while(size > 0)
            {
                TreeNode* node = q.front();
                q.pop();
                
                tmp.push_back(node->val);
                if(node->left)
                {
                    q.push(node->left);
                }
                if(node->right)
                {
                    q.push(node->right);
                }
                size--;
            }
            res.insert(res.begin(),tmp);
        }
        return res;
    }
};

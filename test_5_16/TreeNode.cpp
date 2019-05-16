#include <vector>
#include <stack>
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
    vector<int> postorderTraversal(TreeNode* root) 
    {
      stack<TreeNode*> s;
      TreeNode* cur = root;
      TreeNode* visit = NULL;
      while(cur || s.empty())
      {
        while(cur)
        {
          s.push(cur);
          cur = cur->left;
        }
        cur = s.top();
        if(cur->right == NULL || cur->right == visit)
        {
          res.push_back(cur->val);
          s.pop();
          visit = cur;
          cur = NULL;
        }
        else 
        {
          cur = cur->right;
        }
      }
      return res;
    }
private:
    vector<int> res;
};

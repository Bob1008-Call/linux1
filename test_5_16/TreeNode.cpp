#include <vector>
#include <queue>
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

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution1 {
public:
    vector<int> rightSideView(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        if(root == NULL)
        {
            return {};
        }
        while(!q.empty())
        {
            int size = q.size();
            while(size--)
            {
                TreeNode* tmp = q.front();
                q.pop();
                if(0 == size)
                {
                    res.push_back(tmp->val);
                }
                if(tmp->left)
                {
                    q.push(tmp->left);
                }
                if(tmp->right)
                {
                    q.push(tmp->right);
                }
            }
        }
        return res;
    }
private:
    vector<int> res;
};

#include <stdlib.h>

  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };
class Solution {
public:
    bool isUnivalTree(TreeNode* root) {
        return _isUnivalTree(root,root->val);
    }
    
    bool _isUnivalTree(TreeNode* root,const int& value)
    {
        if(!root)
            return true;
        if(root->val == value)
            return _isUnivalTree(root->left,value) && _isUnivalTree(root->right,value);
        return false;
    }
};

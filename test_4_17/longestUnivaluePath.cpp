#include <algorithm>
#include <stdlib.h>
struct TreeNode
{
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class solution
{
public:
  //最长同值路径
  int longestUnivaluePath(TreeNode* root)
  {
    if(NULL == root)
      return 0;
    maxP = GetMaxP(root,root->val);
    return maxP;
  }

  int GetMaxP(TreeNode* root,int val)
  {
    if(root == NULL)
      return 0;
    int left = GetMaxP(root->left,root->val);
    int right= GetMaxP(root->right,root->val);
    maxP = std::max(left+right,maxP);
    if(root->val == val)
    {
      return std::max(left,right)+1;
    }
    return 0;
  }
private:
  int maxP;
};



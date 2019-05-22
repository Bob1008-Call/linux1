#include <iostream>
#include <vector>
#include <stack>
using namespace std;
template <typename T> class Tree;
template <typename T>
class TreeNode
{
	friend class Tree<T>;
private:
	
public:
	TreeNode<T>*left;
	TreeNode<T>*right;
	T val;
	 
	TreeNode() 
		:val(0)
		, left(NULL)
		, right(NULL)
	{}
	TreeNode(T x) 
		:val(x)
		, left(NULL)
		, right(NULL)
	{}
};


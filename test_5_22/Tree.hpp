#include "BinTree.hpp"
#include <assert.h>
using namespace std;

template <typename T> class TreeNode;

template  <typename T>
class Tree
{
	typedef TreeNode<T> NodeType;
private:
	NodeType *root;
	
	void PreOrder_(NodeType *, vector<T>&);
	void InOrder_(NodeType *, vector<T>&);
	void PostOrder_(NodeType *, vector<T>&);
	void PreOrderNonRescursion_(NodeType *, vector<T>&);
	void InOrderNonRescursion_(NodeType *, vector<T>&);
	void PostOrderNonRescursion_(NodeType *, vector<T>&);
	void DestroyAllNode_(NodeType *);
public:
	Tree();
	~Tree();
	static void CreateBTree(NodeType** root, string s, int size, int* index);
	void PreOrder(vector<T>&);
	void InOrder(vector<T>&);
	void PostOrder(vector<T>&);
	void PreOrderNonRescursion(vector<T>&);
	void InOrderNonRescursion(vector<T>&);
	void PostOrderNonRescursion(vector<T>&);

};

//////////////constructor and destructor//////////////////////////////
template <typename T>
void Tree<T>::DestroyAllNode_(NodeType*root)
{
	if (root == NULL)
		return;
	DestroyAllNode_(root->left);
	DestroyAllNode_(root->right);
	delete root;
	root = NULL;
	return;
}

template<class T>
void Tree<T>::CreateBTree(NodeType** root, string s, int size, int* index)
{
	assert(root);
	assert(index);
	if (*index < size && s[*index] != '#')
	{
		*root = new TreeNode<char>(s[*index]);
		++(*index);
		CreateBTree(&(*root)->left, s, size, index);
		++(*index);
		CreateBTree(&(*root)->right, s, size, index);
	}
}

template <typename T>
Tree<T>::~Tree()
{
	DestroyAllNode_(root);
}
/////////////////PreOrder Traversal//////////////////////////////////////////////////////
template <typename T>
void Tree<T>::PreOrder_(NodeType*root, vector<T>&res)
{
	if (root == NULL)
	{
		return;
	}
	res.push_back(root->val);
	PreOrder_(root->left, res);
	PreOrder_(root->right, res);
}

template <typename T>
void Tree<T>::PreOrder(vector<T>&res)
{
	PreOrder_(root, res);
}

template <typename T>
void Tree<T>::PreOrderNonRescursion_(NodeType*root, vector<T>&res)
{
	NodeType *p = root;
	stack<NodeType*>s;
	while (NULL != p || !s.empty())
	{
		while (NULL != p)
		{
			s.push(p);
			res.push_back(p->val);
			p = p->left;
		}
		if (!s.empty())
		{
			p = s.top();
			s.pop();
			p = p->right;
		}
	}
}
template <typename T>
void Tree<T>::PreOrderNonRescursion(vector<T>&res)
{
	PreOrderNonRescursion_(root, res);
}

//////////////////InOrder Traversal///////////////////////////////////////
template <typename T>
void Tree<T>::InOrder_(NodeType*root, vector<T>&res)
{
	if (root == NULL)
	{
		return;
	}
	InOrder_(root->left, res);
	res.push_back(root->val);
	InOrder_(root->right, res);
}

template <typename T>
void Tree<T>::InOrder(vector<T>&res)
{
	InOrder_(root, res);
}

template <typename T>
void Tree<T>::InOrderNonRescursion_(NodeType*root, vector<T>&res)
{
	NodeType *p = root;
	stack<NodeType*>s;
	while (NULL != p || !s.empty())
	{
		while (NULL != p)
		{
			s.push(p);
			p = p->left;
		}
		if (!s.empty())
		{
			p = s.top();
			res.push_back(p->val);
			s.pop();
			p = p->right;
		}
	}
}
template <typename T>
void Tree<T>::InOrderNonRescursion(vector<T>&res)
{
	InOrderNonRescursion_(root, res);
}

/////////////////PostOrder Traversal////////////////////////////////////////
template <typename T>
void Tree<T>::PostOrder_(NodeType*root, vector<T>&res)
{
	if (root == NULL)
	{
		return;
	}
	PostOrder_(root->left, res);
	PostOrder_(root->right, res);
	res.push_back(root->val);
}

template <typename T>
void Tree<T>::PostOrder(vector<T>&res)
{
	PostOrder_(root, res);
}

template <typename T>
void Tree<T>::PostOrderNonRescursion_(NodeType*root, vector<T>&res)
{
	NodeType *pre = NULL;
	//NodeType *cur=root;
	NodeType *cur;
	stack<NodeType*>s;
	s.push(root);
	while (!s.empty())
	{
		cur = s.top();
		if (((cur->left == NULL) && (cur->right == NULL)) ||
			(pre != NULL && (pre == cur->left || pre == cur->right)))
		{
			res.push_back(cur->val);
			s.pop();
			pre = cur;
		}
		else
		{
			if (cur->right != NULL)
				s.push(cur->right);
			if (cur->left != NULL)
				s.push(cur->left);
		}
	}
}
template <typename T>
void Tree<T>::PostOrderNonRescursion(vector<T>&res)
{
	PostOrderNonRescursion_(root, res);
}

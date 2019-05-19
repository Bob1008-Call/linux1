#include <stdlib.h>
struct BinaryNode
{
	BinaryNode* _left;
	BinaryNode* _right;
	BinaryNode* _parent;
	int _value;
 
	BinaryNode(const int& value)
		:_value(value)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
	{}
};

//第一种方法
BinaryNode * GetLastCommonAncestor(BinaryNode * root, BinaryNode * node1, BinaryNode * node2)
{
	BinaryNode * temp;
	while (node1 != NULL)
	{
		node1 = node1->_parent;
		temp = node2;
		while (temp != NULL)
		{
			if (node1 == temp->_parent)
				return node1;
			temp = temp->_parent;
		}
	}
}



int Hight(BinaryNode* root, BinaryNode* node)
{
	int len = 0;
	for (; node != NULL; node = node->_parent)
		len++;
 
	return len;
}

BinaryNode* GetLastCommonAncestor(BinaryNode* root, BinaryNode* node1, BinaryNode* node2)
{
 
	if (root == NULL || node1 == NULL || node2==NULL)
		return NULL;
 
	int len1 = Hight(root,node1);
	int len2 = Hight(root,node2);
	
 
	for (; len1 > len2; len1--)
		node1 = node1->_parent;
	for (; len2 > len1; len2--)
		node2 = node2->_parent;
 
	while (node1 && node2 && node1 != node2)
	{
		node1 = node1->_parent;
		node2 = node2->_parent;
	}
    
	if (node1 == node2)
		return node1;
	else
		return NULL;
}


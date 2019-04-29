#pragma once
#include <stdio.h>
#include <utility>
using namespace std;

template<class K,class V>
struct AVLTreeNode
{
	AVLTreeNode(const K& key, const V& value)
		:_pLeft(nullptr)
		, _pRight(nullptr)
		, _pParent(nullptr)
		, _data(key,value)
		, _bf(0)
	{}

	AVLTreeNode<K, V>* _pLeft;
	AVLTreeNode<K, V>* _pRight;
	AVLTreeNode<K, V>* _pParent;
	pair<K, V> _data;
	int _bf;
};

template<class K,class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
	typedef Node* PNode;

public:
	AVLTree()
		:_pRoot(nullptr)
	{}

	bool Insert(const K& key, const V& value)
	{
		if (_pRoot == nullptr)
		{
			_pRoot = new Node(key, value);
			return true;
		}
		//找data插入位置
		PNode pCur = _pRoot;
		PNode pParent = nullptr;
		while (pCur)
		{
			pParent = pCur;
			if (key < pCur->_data.first)
			{
				pCur = pCur->_pLeft;
			}
			else if (key > pCur->_data.first)
			{
				pCur = pCur->_pRight;
			}
			else
			{
				return true;
			}
		}
		pCur = new Node(key, value);
		if (key < pParent->_data.first)
		{
			pParent->_pLeft = pCur;
		}
		else
		{
			pParent->_pRight = pCur;
		}
		pCur->_pParent = pParent;
		//更新节点的平衡因子
		while ()
		{
			if (pCur == pParent->_pLeft)
			{
				pParent->_bf--;
			}
			else
			{
				pParent->_bf++;
			}
			if (0 == pParent->_bf)
			{
				return;
			}
			else if (1 == pParent->_bf || -1 == pParent->_bf)
			{
				//说明子树的高度增加，需要继续向上更新
				pCur = pParent;
				pParent = pCur->_pParent;
			}
			else
			{
				//parent的平衡因子为 2 或 -2 以parent为根的AVL树平衡性被破坏
				  
			}
		}
	}
private:
	void RotateR(PNode pParent)
	{
		PNode pSubL = pParent->_pLeft;
		PNode pSubLR = pSubL->_pRight;
		pParent->_pLeft = pSubLR;

		if (pSubLR)
		{
			pSubLR->_pParent = pParent;
		}

		pSubL->_pRight = pParent;

		PNode pPParent = pParent->_pParent;

		pParent->_pParent = pSubL;

		pSubL->_pParent = pPParent;

		if (pPParent == NULL)
		{
			_pRoot = pSubL;
			pSubL->_pParent = NULL;
		}
		else
		{
			if (pParent == pPParent->_pLeft)
			{
				pPParent->_pLeft = pSubL;
			}
			else
			{
				pPParent->_pRight = pSubL;
			}
		}
		pParent->_bf = pSubL->_bf = 0;
	}

	void RotateL(PNode pParent)
	{
		PNode pSubR = pParent->_pRight;
		PNode pSubRL = pSubR->_pLeft;

		pParent->_pRight = pSubRL;
		if (pSubRL)
		{
			pSubRL->_pParent = pParent;
		}

		pSubR->_pLeft = pParent;

		PNode pPParent = pParent->_pParent;

		pParent->_pParent = pSubR;

		pSubR->_pParent = pPParent;


		if (NULL == pPParent)
		{
			_pRoot = pSubR;
			pSubR->_pParent = NULL;
		}
		else
		{
			if (pPParent->_pLeft == pParent)
			{
				pPParent->_pLeft = pSubR;
			}
			else
			{
				pPParent->_pRight = pSubR;
			}
		}
		pParent->_bf = pSubR->_bf = 0; 
	}
private:
	PNode _pRoot;
};

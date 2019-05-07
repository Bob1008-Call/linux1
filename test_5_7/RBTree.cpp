#include <iostream>
using namespace std;

enum Color{ RED, BLACK };

template<class V>
struct RBTreeNode
{
	RBTreeNode(const V& data = V(), Color color = RED)
		:_pLeft(nullptr)
		, _pRight(nullptr)
		, _pParent(nullptr)
		, _data(data)
		, _color(color)
	{}

	RBTreeNode<V>* _pLeft;
	RBTreeNode<V>* _pRight;
	RBTreeNode<V>* _pParent;
	V _data;
	Color _color;
};

template<class V>
struct RBTreeIterator
{
	typedef RBTreeNode<V> Node;
	typedef Node* PNode;
	typedef RBTreeIterator<V> Self;

	RBTreeIterator(PNode pNode = nullptr)
		:_pNode(pNode)
	{}

	RBTreeIterator(Self& s)
		:_pNode(s._pNode)
	{}

	V& operator*()
	{
		return _pNode->_data;
	}

	V* operator->()
	{
		return &(operator*());
	}

	Self& operator++()
	{
		Increasement();
		return *this;
	}

	Self operator++(int)
	{
		Self temp(*this);
		Increasement();
		return temp;
	}
	 
	Self& operator--()
	{
		Decreasement();
		return *this;
	}

	Self operator--(int)
	{
		Self temp(*this);
		Decreasement();
		return temp;
	}
	void Increasement()
	{
		if(_pNode->_pRight)
		{
			_pNode = _pNode->_pRight;
			while (_pNode->_pLeft)
			{
				_pNode = _pNode->_pLeft;
			}
		}
		else
		{
			PNode pParent = _pNode->_pParent;
			while (_pNode == pParent->_pRight)
			{
				_pNode = pParent;
				pParent = _pNode->_pParent;
			}
			if (_pNode->_pRight != pParent)//根节点没有右孩子的情况
			{
				_pNode = pParent;//存在一种极端情况（只有头节点和根节点）
			}
		}
	}

	void Decreasement()
	{
		if (_pNode->_pParent->_pParent == _pNode && _pNode->_color == RED)
		{
			_pNode = _pNode->_pRight;
		}
		else if (_pNode->_pLeft)
		{
			_pNode = _pNode->_pLeft;
			while (_pNode->_pRight)
			{
				_pNode = _pNode->_pRight;
			}
		}
		else
		{
			PNode pParent = _pNode->_pParent;
			while (_pNode == pParent->_pLeft)
			{
				_pNode = pParent;
				pParent = _pNode->_pParent;
			}
			_pNode = pParent;
		}
	}

	bool operator!=(const Self& s)
	{
		return _pNode != s._pNode;
	}

	bool operator==(const Self& s)
	{
		return _pNode == s._pNode;
	}

	PNode _pNode;
};

template<class V>
class RBTree
{
	typedef RBTreeNode<V> Node;
	typedef Node* PNode;

public:
	typedef RBTreeIterator<V> Iterator;
public:
	RBTree()
	{
		_pHead = new Node();
		_pHead->_pLeft = _pHead;
		_pHead->_pRight = _pHead;
	}

	Iterator Begin()
	{
		return Iterator(_pHead->_pLeft);
	}

	Iterator End()
	{
		return Iterator(_pHead);
	}

	~RBTree()
	{
		Destroy(GetRoot());
	}

	bool Insert(const V& data)
	{
		PNode& _pRoot = GetRoot();
		if (nullptr == _pRoot)
		{
			_pRoot = new Node(data, BLACK);
			_pRoot->_pParent = _pHead;
		}
		else
		{
			//按照二叉搜索树的性质将节点插入
			PNode pCur = _pRoot;
			PNode pParent = nullptr;
			while (pCur)
			{
				pParent = pCur;
				if (data < pCur->_data)
				{
					pCur = pCur->_pLeft;
				}
				else if (data > pCur->_data)
				{
					pCur = pCur->_pRight;
				}
				else
				{
					return false;
				}
			}
			//插入节点
			pCur = new Node(data);
			if (data < pParent->_data)
			{
				pParent->_pLeft = pCur;
			}
			else
			{
				pParent->_pRight = pCur;
			}
			pCur->_pParent = pParent;

			//更新节点的颜色
			while (_pHead != pParent && RED == pParent->_color)
			{
				PNode grandFather = pParent->_pParent;//如果双亲是红色，那么根节点一定存在，因为根节点是黑色
				if (pParent == grandFather->_pLeft)
				{
					PNode uncle = grandFather->_pRight;
					if (uncle && RED == uncle->_color)//情况一
					{
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						grandFather->_color = RED;
						pCur = grandFather;
						pParent = pCur->_pParent;
					}
					else
					{
						//叔叔节点不存在 / 叔叔节点存在 && 黑色
						if (pCur == pParent->_pRight)
						{
							RotateL(pParent);
							swap(pParent, pCur);
						}
						//情况二
						grandFather->_color = RED;
						pParent->_color = BLACK;
						RotateR(grandFather);
					}
				}
				else
				{
					PNode uncle = grandFather->_pLeft;
					if (uncle && RED == uncle->_color)
					{
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						grandFather->_color = RED;
						pCur = grandFather;
						pParent = pCur->_pParent;
					}
					else
					{
						if (pCur == pParent->_pLeft)
						{
							RotateR(pParent);
							swap(pParent, pCur);
						}
						grandFather->_color = RED;
						pParent->_color = BLACK;
						RotateL(grandFather);
					}
				}
			}
		}

		_pRoot->_color = BLACK;
		_pHead->_pLeft = LeftMost();
		_pHead->_pRight = RightMost();
		return true;
	}

	void InOrder()
	{
		_InOrder(GetRoot());
	}

	bool IsValidRBTree()
	{
		PNode pRoot = GetRoot();
		if (nullptr == pRoot)
		{
			return true;
		}
		if (pRoot->_color != BLACK)
		{
			cout << "性质1" << endl;
			return false;
		}
		size_t blackCount = 0;
		PNode pCur = pRoot;
		while (pCur)
		{
			if (BLACK == pCur->_color)
			{
				blackCount++;
			}
			pCur = pCur->_pLeft;
		}
		size_t pathBlackCount = 0;
		return _IsValidRBTree(pRoot, blackCount, pathBlackCount);
	}

private:
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

		if (pPParent == _pHead)
		{
			_pHead->_pParent = pSubR;
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
	}

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

		if (pPParent == _pHead)
		{
			_pHead->_pParent = pSubL;
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
	}

	PNode& GetRoot()
	{
		return _pHead->_pParent;
	}

	PNode LeftMost()
	{
		PNode pCur = GetRoot();
		if (nullptr == pCur)
		{
			return _pHead;
		}

		while (pCur->_pLeft)
		{
			pCur = pCur->_pLeft;
		}
		return pCur;
	}

	PNode RightMost()
	{
		PNode pCur = GetRoot();
		if (nullptr == pCur)
		{
			return _pHead;
		}

		while (pCur->_pRight)
		{
			pCur = pCur->_pRight;
		}
		return pCur;
	}

	void _InOrder(PNode pRoot)
	{
		if (pRoot)
		{
			_InOrder(pRoot->_pLeft);
			cout << pRoot->_data << " ";
			_InOrder(pRoot->_pRight);
		}
	}

	void Destroy(PNode& pRoot)
	{
		if (pRoot)
		{
			Destroy(pRoot->_pLeft);
			Destroy(pRoot->_pRight);
			delete pRoot;
			pRoot = nullptr;
		}
	}

	bool _IsValidRBTree(PNode pRoot, size_t blackCount, size_t pathBlackCount)
	{
		if (nullptr == pRoot)
		{
			return true;
		}
		if (pRoot->_color == BLACK)
		{
			pathBlackCount++;
		}
		PNode pParent = pRoot->_pParent;
		if (pParent && RED == pParent->_color && RED == pRoot->_color)
		{
			cout << "性质3" << endl;
			return false;
		}
		if (nullptr == pRoot->_pLeft && nullptr == pRoot->_pRight)
		{
			if (pathBlackCount != blackCount)
			{
				cout << "性质4" << endl;
				return false;
			}
		}
		return _IsValidRBTree(pRoot->_pLeft, blackCount, pathBlackCount)
			&& _IsValidRBTree(pRoot->_pRight, blackCount, pathBlackCount);
	}

private:
	PNode _pHead;
};

void TestRBTree()
{
	int array[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	RBTree<int> t;
	for (auto e : array)
	{
		t.Insert(e);
	}
	t.InOrder();

	if (t.IsValidRBTree())
	{
		cout << "t is RBTree" << endl;
	}
	cout << endl;
}

#pragma once

enum Colour
{
	RED,
	BLACK,
};

template<class T>
struct RBTreeNode
{
	T _data;

	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;

	Colour _colour; // 颜色

	RBTreeNode(const T& x)
		:_data(x)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
	{}
};

template<class T>
struct __RBTreeIterator
{
	typedef RBTreeNode<T> Node;
	typedef __RBTreeIterator<T> Self;
	Node* _node;

	__RBTreeIterator(Node* node)
		:_node(node)
	{}

	T& operator*()
	{
		return _node->_data;
	}

	T* operator->()
	{
		return &(operator*());
	}

	//operator->

	Self& operator++()
	{
		//1.右为空 找祖先里面不为右的
		//2.右不为空， 找右树中序第一个
		if (_node->_right)
		{
			_node = _node->_right;
			while(_node->_left)
				_node = _node->_left;
		}
		else
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent)
			{
				if (cur == parent->_right)
				{
					cur = parent;
					parent = parent->_parent;
				}
				else
				{
					break;
				}
			}

			_node = parent;
		}

		return *this;
	}

	Self operator++(int)
	{
		Self tmp(*this);
		++(*this);
		return tmp;
	}

	Self operator--()
	{
		if (_node->_left)
		{
			_node = _node->_left;
			while (_node->_right)
			{
				_node = _node->_right;
			}
		}
		else
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			while(parent)
			{
				if (cur == parent->_left)
				{
					cur = parent;
					parent = cur->_parent;
				}
				else
				{
					break;
				}
			}

			_node = parent;
		}
	}

	Self operator--(int)
	{
		Self tmp(*this);
		--(*this);

		return tmp;
	}

	bool operator==(const Self& s)
	{
		return _node == s._node;
	}

	bool operator!=(const Self& s)
	{
		return _node != s._node;
	}
};

template<class K, class T, class KeyOfValue>
class RBtree
{
	typedef RBTreeNode<T> Node;
public:
	typedef __RBTreeIterator<T> Iterator;

	RBtree()
		:_root(NULL)
	{}

	Iterator Begin()
	{
		Node* cur = _root;
		while(cur && cur->_left)
		{
			cur = cur->_left;
		}

		return Iterator(cur);
	}
	
	Iterator End()
	{
		return Iterator(NULL);
	}

	pair<Iterator, bool> Insert(const T& data)
	{
		if (_root == NULL)
		{
			_root = new Node(data);
			_root->_colour = BLACK;
			return make_pair(Iterator(_root), true);
		}

		Node* parent = NULL;
		Node* cur = _root;

		KeyOfValue kov;
		while (cur)
		{
			if (kov(cur->_data) > kov(data))
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (kov(cur->_data) < kov(data))
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return make_pair(Iterator(cur), false);
			}
		}

		cur = new Node(data);
		Node* newnode = cur;

		cur->_colour = RED;
		if (kov(parent->_data) < kov(cur->_data))
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}

		// 颜色调节，保证近似平衡
		while (parent && parent->_colour == RED)
		{
			// 关键看uncle
			Node* grandfather = parent->_parent;
			if (grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;
				// 1.u存在且为红
				// 2.u不存在/u存在且为黑
				if (uncle && uncle->_colour == RED)
				{
					parent->_colour = uncle->_colour = BLACK;
					grandfather->_colour = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					if(parent->_right == cur)
					{
						RotateL(parent);
						swap(cur, parent);
					}

					RotateR(grandfather);
					parent->_colour = BLACK;
					grandfather->_colour = RED;
				}
			}
			else //grandfather->_right == parent
			{
				Node* uncle = grandfather->_left;
				if (uncle && uncle->_colour == RED)
				{
					parent->_colour = uncle->_colour = BLACK;
					grandfather->_colour = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					if (parent->_left == cur)
					{
						RotateR(parent);
						swap(cur, parent);
					}

					RotateL(grandfather);
					parent->_colour = BLACK;
					grandfather->_colour = RED;
				}
			}
		}

		_root->_colour = BLACK;

		return make_pair(Iterator(newnode), true);
	}

	Iterator Find(const K& key)
	{
		Node* cur = _root;
		KeyOfValue kov;
		while (cur)
		{
			if (kov(cur->_data) > key)
			{
				cur = cur->_left;
			}
			else if (kov(cur->_data) < key)
			{
				cur = cur->_right;
			}
			else
			{
				return Iterator(cur);
			}
		}

		return End();
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* ppNode = parent->_parent;

		parent->_left = subLR;
		if(subLR)
			subLR->_parent = parent;

		subL->_right = parent;
		parent->_parent = subL;

		if (ppNode == NULL)
		{
			_root = subL;
		}
		else
		{
			if (ppNode->_left == parent)
				ppNode->_left = subL;
			else
				ppNode->_right = subL;
		}

		subL->_parent = ppNode;
	}

	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* ppNode = parent->_parent;

		parent->_right = subRL;
		if(subRL)
			subRL->_parent = parent;

		subR->_left = parent;
		parent->_parent = subR;

		if (ppNode == NULL)
		{
			_root = subR;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subR;
			}
			else
			{
				ppNode->_right = subR;
			}
		}

		subR->_parent = ppNode;
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		_InOrder(root->_left);
		cout<<root->_key<<"  ";
		_InOrder(root->_right);
	}

	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}

	bool _IsBalance(Node* root, size_t blackNum, const size_t N)
	{
		if (root == NULL)
		{
			if (N != blackNum)
			{
				cout<<"黑色节点的数量不相等"<<endl;
				return false;
			}
			else
			{
				return true;
			}
		}

		if (root->_colour == BLACK)
		{
			++blackNum;
		}

		if (root->_colour == RED 
			&& root->_parent->_colour == RED)
		{
			cout<<"存在连续的红节点"<<_root->_key<<endl;

			return false;
		}

		return _IsBalance(root->_left, blackNum, N)
			&& _IsBalance(root->_right, blackNum, N);
	}

	bool IsBalance()
	{
		if (_root && _root->_colour ==  RED)
		{
			return false;
		}

		size_t N = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_colour == BLACK)
			{
				++N;
			}

			cur = cur->_left;
		}

		size_t blackNum = 0;
		return _IsBalance(_root, blackNum, N);
	}

private:
	Node* _root;
};

//void TestRBTree()
//{
//	int a[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
//	RBtree<int, int> t;
//	for (size_t i = 0; i < sizeof(a)/sizeof(int); ++i)
//	{
//		t.Insert(a[i], i);
//		cout<<a[i]<<"->IsBalance?"<<t.IsBalance()<<endl;
//	}
//	
//	cout<<"IsBalance?"<<t.IsBalance()<<endl;
//	t.InOrder();
//}
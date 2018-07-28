#pragma once

template<class K, class V>
struct AVLTreeNode
{
	K _key;
	V _value;
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;

	int _bf; // 平衡因子

	AVLTreeNode(const K& key, const V& value)
		:_key(key)
		,_value(value)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
		,_bf(0)
	{}
};

template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}

	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}

		Node* parent = NULL;
		Node* cur = _root;

		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if(cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}

		cur = new Node(key, value);
		if (parent->_key < key)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}

		// 是否平衡？
		while (parent)
		{
			if (parent->_left == cur)
				parent->_bf--;
			else
				parent->_bf++;

			if (parent->_bf == 0)
			{
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2)
			{
				// 已经不平衡，需要旋转
				if (parent->_bf == 2)
				{
					if (cur->_bf == 1)
					{
						RotateL(parent);
					}
					else // -1
					{
						RotateRL(parent);
					}
				}
				else // -2
				{
					if (cur->_bf == -1)
					{
						RotateR(parent);
					}
					else // 1
					{
						RotateLR(parent);
					}
				}
				break;
			}
			else
			{
				assert(false);
			}
		}

		return true;
	}

	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		RotateL(parent->_left);
		RotateR(parent);
		if (bf == 0)
		{
			subL->_bf = subLR->_bf = parent->_bf = 0;
		}
		else if (bf == 1)
		{
			parent->_bf = 0;
			subL->_bf = -1;
			subLR->_bf = 0;
		}
		else if (bf == -1)
		{
			subL->_bf = 0;
			parent->_bf = 1;
			subLR->_bf = 0;
		}
		else
		{
			assert(false);
		}
	}

	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;

		RotateR(parent->_right);
		RotateL(parent);

		if (bf == 0)
		{
			subRL->_bf = subR->_bf = parent->_bf = 0;
		}
		else if (bf == 1)
		{
			subR->_bf = 0;
			parent->_bf = -1;
			subRL->_bf = 0;
		}
		else if (bf == -1)
		{
			parent->_bf = 0;
			subR->_bf = 1;
			subRL->_bf = 0;
		}
		else
		{
			assert(false);
		}
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

		subL->_bf = parent->_bf = 0;
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

		subR->_bf = parent->_bf = 0;
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		_InOrder(root->_left);
		cout<<root->_key<<" ";
		_InOrder(root->_right);
	}

	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}

	bool _IsBalance(Node* root)
	{
		if (root == NULL)
			return true;

		int leftHeight = Height(root->_left);
		int rightHeight = Height(root->_right);

		return abs(leftHeight-rightHeight) < 2
			&& _IsBalance(root->_left)
			&& _IsBalance(root->_right);
	}

	bool _IsBalance(Node* root, int& height)
	{
		if (root == NULL)
		{
			height = 0;
			return true;
		}

		int leftHeight = 0;
		if (_IsBalance(root->_left, leftHeight) == false)
			return false;

		int rightHeight = 0;
		if (_IsBalance(root->_right, rightHeight) == false)
			return false;

		if (rightHeight-leftHeight != root->_bf)
		{
			cout<<"平衡因子异常"<<root->_key<<endl;
			return false;
		}
		
		height = leftHeight > rightHeight ? leftHeight+1:rightHeight+1;
		return abs(leftHeight- rightHeight) < 2;
	}

	bool IsBalance()
	{
		//return _IsBalance(_root);
		int height = 0;
		return _IsBalance(_root, height);
	}

	Node* Find(const K& key);
	bool Remove(const K& key);

private:
	Node* _root;
};

void TestAVLTree()
{
	//int a[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
	int a[] = {4, 2, 6, 1, 3, 5, 15, 7, 16, 14};
	AVLTree<int, int> t1;
	for (size_t i = 0; i < sizeof(a)/sizeof(a[0]); ++i)
	{
		t1.Insert(a[i], i);
		cout<<a[i]<<" IsBalance:"<<t1.IsBalance()<<endl;
	}

	cout<<"IsBalance:"<<t1.IsBalance()<<endl;
	t1.InOrder();
}
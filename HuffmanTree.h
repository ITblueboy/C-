#pragma once

#include <queue>

template<class W>
struct HuffmanTreeNode
{
	W _w;
	HuffmanTreeNode<W>* _left;
	HuffmanTreeNode<W>* _right;
	HuffmanTreeNode<W>* _parent;

	HuffmanTreeNode(const W& w)
		:_w(w)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
	{}
};

template<class W>
class HuffmanTree
{
	typedef HuffmanTreeNode<W> Node;

	struct PtrNodeCompare
	{
		bool operator()(Node* n1, Node* n2)
		{
			return n1->_w > n2->_w;
		}
	};
public:
	HuffmanTree(W* a, size_t n, const W& invalid)
	{
		
	}

	Node* GetRoot()
	{
		return _root;
	}

	~HuffmanTree()
	{
		Destory(_root);
		_root = NULL;
	}

	void Destory(Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		Destory(root->_left);
		Destory(root->_right);

		delete root;
	}

private:
	HuffmanTree(const HuffmanTree<W>& t);
	HuffmanTree<W>& operator=(const HuffmanTree<W>& t);

protected:
	Node* _root;
};


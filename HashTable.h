#pragma once

#include <vector>
template<class V>
struct HashNode
{
	V _data; // set->key   map->pair<k, v>
	HashNode<V>* _next;
};

template<class K, class V, class KeyOfValue>
class HashTable
{
	typedef HashNode<V> Node;
public:
	HashTable()
		:_size(0)
	{}

	bool Insert(const V& data)
	{
		CheckCapacity();

		KeyOfValue kov;
		size_t index = HashFunc(kov(data));

		Node* cur = _tables[index];
		while (cur)
		{
			if (kov(data) == kov(cur->_data))
			{
				return false;
			}

			cur = cur->_next;
		}

		Node* newnode = new Node(data);
		newnode->_next = _tables[index];
		_tables[index] = newnode;

		return true;
	}

	size_t HashFunc(const K& key)
	{
		return key % _tables.size();
	}
private:
	vector<Node*> _tables;
	size_t _size;
};
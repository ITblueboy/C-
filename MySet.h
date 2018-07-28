#pragma once

#include "RBTree.h"

template<class K>
class MySet
{
	struct SetKeyOfValue
	{
		const K& operator()(const K& key)
		{
			return key;
		}
	};

public:
	typedef typename RBtree<K, K,SetKeyOfValue>::Iterator Iterator;

public:
	pair<Iterator, bool> Insert(const K& key)
	{
		return _t.Insert(key);
	}

	Iterator Begin()
	{
		return _t.Begin();
	}

	Iterator End()
	{
		return _t.End();
	}

protected:
	RBtree<K, K, SetKeyOfValue> _t;
};

void TestMySet()
{
	MySet<int> s;
	s.Insert(3);
	s.Insert(1);
	s.Insert(2);
	s.Insert(7);
	s.Insert(2);
	s.Insert(9);
	s.Insert(10);

	MySet<int>::Iterator it = s.Begin();
	while (it != s.End())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
}
#pragma once
#include <string>

template<class K, class V>
class MyMap
{
	struct MapKeyOfValue
	{
		const K& operator()(const pair<K, V>& kv)
		{
			return kv.first;
		}
	};
public:
	typedef typename RBtree<K, pair<K, V>,MapKeyOfValue>::Iterator Iterator;
public:
	pair<Iterator, bool> Insert(const pair<K, V>& kv)
	{
		return _t.Insert(kv);
	}

	V& operator[](const K& key)
	{
		pair<Iterator, bool> ret = Insert(make_pair(key, V()));
		return ret.first->second;
	}

	Iterator Begin()
	{
		return _t.Begin();
	}

	Iterator End()
	{
		return _t.End();
	}

	Iterator Find(const K& key)
	{
		return _t.Find(key);
	}

protected:
	RBtree<K, pair<K, V>, MapKeyOfValue> _t;
};

void TestMyMap()
{
	MyMap<string, string> dict;
	/*dict.Insert(make_pair("insert", "²åÈë"));
	dict.Insert(make_pair("left", "×ó±ß"));
	dict.Insert(make_pair("string", "×Ö·û´®"));
	dict.Insert(make_pair("value", "Öµ"));
	dict.Insert(make_pair("key", "¹Ø¼ü×Ö"));*/
	dict["insert"] = "²åÈë";
	dict["left"] = "×ó±ß";
	dict["left"] = "Ê£Óà";
	dict["key"];

	MyMap<string, string>::Iterator it = dict.Begin();
	while (it != dict.End())
	{
		//cout<<(*it).first<<":"<<(*it).second<<endl;
		cout<<it->first<<" "<<it->second<<endl;
		++it;
	}

	/*string strs[] = {"insert", "first", "first", "insert","end","insert", "insert"};
	MyMap<string, int> countMap;
	typedef MyMap<string, int>::Iterator CountMapIter;
	for (size_t i = 0; i < sizeof(strs)/sizeof(string); ++i)
	{
	/*	MyMap<string, int>::Iterator ret = countMap.Find(strs[i]);
		if (ret != countMap.End())
		{
			ret->second++;
		}
		else
		{
			countMap.Insert(make_pair(strs[i], 1));
		}*/
		/*pair<CountMapIter, bool> ret = countMap.Insert(make_pair(strs[i], 1));
		if (ret.second == false)
		{
			ret.first->second++;
		}*/

	//	countMap[strs[i]]++;
	//}

	//CountMapIter it = countMap.Begin();
	//while (it != countMap.End())
	//{
	//	cout<<it->first<<" "<<it->second<<endl;
	//	++it;
	//}
	//*/
}
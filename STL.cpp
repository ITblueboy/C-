#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <string>
#include <time.h>
#include <array>
using namespace std;

void test_set()
{
	multiset<int> s;
	s.insert(6);
	s.insert(1);
	s.insert(4);
	s.insert(9);
	s.insert(9);
	set<int>::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	unordered_multiset<int> us;
	us.insert(6);
	us.insert(1);
	us.insert(4);
	us.insert(9);
	us.insert(9);
	unordered_set<int>::iterator uit = us.begin();
	while (uit != us.end())
	{
		cout << *uit << " ";
		++uit;
	}
	cout << endl;
}

void test_map()
{
	typedef map<string, string> Dict;
	typedef map<string, string>::iterator DictIter;

	typedef unordered_map<string, string> UDict;
	typedef unordered_map<string, string>::iterator UDictIter;

	Dict m;
	m.insert(make_pair("string", "×Ö·û´®"));
	m.insert(pair<string, string>("left", "×ó±ß"));
	m.insert(pair<string, string>("left", "Ê£Óà"));
	m["test"] = "²âÊÔ"; // ²åÈë+ĞŞ¸Ä
	m["left"] = "Ê£Óà"; // ĞŞ¸Ä
	DictIter it = m.begin();
	while (it != m.end())
	{
		cout << it->first << ":" << it->second << endl; // pair<k,v>& operator*(){return _node->kv;}
		++it;
	}
	cout << endl;
	
	unordered_map<string, string> um;
	um.insert(make_pair("string", "×Ö·û´®"));
	um.insert(pair<string, string>("left", "×ó±ß"));
	um.insert(pair<string, string>("left", "Ê£Óà"));
	um["test"] = "²âÊÔ"; // ²åÈë+ĞŞ¸Ä
	um["left"] = "Ê£Óà"; // ĞŞ¸Ä
	UDictIter uit = um.begin();
	while (uit != um.end())
	{
		cout << uit->first << ":" << uit->second << endl; // pair<k,v>& operator*(){return _node->kv;}
		++uit;
	}
	cout << endl;

	multimap<string, string> mm;
	mm.insert(make_pair("string", "×Ö·û´®"));
	mm.insert(pair<string, string>("left", "×ó±ß"));
	mm.insert(pair<string, string>("left", "Ê£Óà"));
}

void test_op()
{
	const size_t N = 100000;
	size_t begin1 = clock();
	map<int, string> m;
	for (size_t i = 0; i < N; ++i)
	{
		//m[to_string(i)] = i;
		//m[i] = "1111111111111111111111111111111";
		m.insert(make_pair(i, "111111111111111"));
	}
	size_t end1 = clock();

	size_t begin2 = clock();
	unordered_map<int, string> um;
	for (size_t i = 0; i < N; ++i)
	{
		//um[to_string(i)] = i;
		//um[i] = "1111111111111111111111111111111";
		um.insert(make_pair(i, "111111111111111"));
	}
	size_t end2 = clock();

	cout << end1 - begin1 << endl;
	cout << end2 - begin2 << endl;
}

#include <algorithm>
void test_algorithm()
{
	string s("hello world");
	string::iterator start = s.begin();
	string::iterator finish;
	do
	{
		finish = find(start, s.end(), ' ');
		reverse(start, finish);
		if (finish != s.end())
		{
			start = ++finish;
		}
		else
		{
			break;
		}
	} while (1);

	//reverse(s.begin(), s.end());

	cout << s << endl;
}

int main()
{
	test_set();
	test_map();
	//test_op();
	//test_algorithm();

	string s("hello world");
	sort(s.begin(), s.end());

	char str[] = "hello world";
	sort(str, str + strlen(str));

	cout << s << endl;
	cout << str << endl;

	return 0;
}

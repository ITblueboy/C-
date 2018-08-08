#pragma once
#include <string>
#include <fstream>

#include "HuffmanTree.h"

typedef long long LongType;

struct CharInfo
{
	char _ch;
	LongType _count;
	string _code;

	CharInfo operator+(const CharInfo& info)
	{
		CharInfo ret;
		ret._count = _count + info._count;
		return ret;
	}

	// w1 > w2
	bool operator>(const CharInfo& info)
	{
		return _count > info._count;
	}

	bool operator!=(const CharInfo& info)
	{
		return _count != info._count;
	}
};

class FileCompress
{
	typedef HuffmanTreeNode<CharInfo> Node;
public:
	FileCompress()
	{
		for (size_t i = 0; i < 256; ++i)
		{
			_hashInfos[i]._ch = i;
			_hashInfos[i]._count = 0;
		}
	}

	void Compress(const char* file)
	{
		// 1.统计文件中字符出现的次数
		ifstream ifs(file);
		char ch;
		while (ifs.get(ch))
		{
			_hashInfos[ch]._count++;
		}

		// 2.构建huffman tree
		CharInfo invalid;
		invalid._count = 0;
		HuffmanTree<CharInfo> tree(_hashInfos, 256, invalid);
		GenerateHuffmanCode(tree.GetRoot());
	}

	void GenerateHuffmanCode(Node* root)
	{
		
	}

	void Uncompress(const char* file);
protected:
	CharInfo _hashInfos[256];
};

void TestFileCompress()
{
	FileCompress fc;
	fc.Compress("input.txt");

}
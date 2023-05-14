#pragma once
#ifndef _TOOLS_H_
#define _TOOLS_H_
#include <vector>
#include <string>

namespace tools
{
	using uchar = unsigned char;
	inline std::vector<std::string> SplitString(std::string str, std::string pattern)
		// https://www.cnblogs.com/dfcao/p/cpp-FAQ-split.html
	{
		using namespace std;
		vector<string> v;
		string::size_type pos1{ 0 }, pos2{ str.find(pattern) };
		while (pos2 != string::npos)
		{
			v.push_back(str.substr(pos1, pos2 - pos1));

			pos1 = pos2 + pattern.size();
			pos2 = str.find(pattern, pos1);
		}
		if (pos1 != str.length())
			v.push_back(str.substr(pos1));
		return v;
	}
	inline std::string decoder(std::string& str)//字符串解密算法
	{
		using namespace std;
		string result;
		int len = str.length(); if (len % 2 != 0) { len--; }
		for (int i = 0; i < len; i += 2) //恢复反序字符串的奇偶位
		{
			char temp = str[i];
			str[i] = str[i + 1];
			str[i + 1] = temp;
		}
		len = str.length();
		for (int i = 0; i < len; i++) //恢复每个字节的原始状态以及字符串的原始顺序
		{
			uchar BA = str[len - i - 1];
			uchar B = BA >> 4; uchar A = BA - (B << 4);
			uchar AB = (A << 4) + B;
			result += AB;
		}
		str = result;
		return result;
	}
	inline std::string encoder(std::string& str) //字符串加密算法
	{
		using namespace std;
		string result;
		int len = str.length();
		for (int i = 0; i < len; i++) //置换每个字节的前四位和后四位，并将字符串反序（字符串以字节而不是字符为单位）
		{
			uchar AB = str[len - i - 1];
			uchar A = AB >> 4; uchar B = AB - (A << 4);
			uchar BA = (B << 4) + A;
			result += BA;
		}
		if (len % 2 != 0) { len--; }
		for (int i = 0; i < len; i += 2) //交换反序字符串的奇偶位
		{
			char temp = result[i];
			result[i] = result[i + 1];
			result[i + 1] = temp;
		}
		str = result;
		return result;
	}
}

#endif // !_TOOLS_H_

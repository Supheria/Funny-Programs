#pragma once

#include <vector>
using std::vector;
class Convert
{
public:
	vector<int> m_result;
	int m_ori = 0;
	Convert(int scale, vector<int>& result, int original)
	{
		m_scale = scale <= 1 ? 15 : scale;
		m_ori = original;
		convert();
		result = m_result;
	}
private:
	void convert();
public:
	int m_scale = 10;
private:
	int xScale(int power = 2);
};
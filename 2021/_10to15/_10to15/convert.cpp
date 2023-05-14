#include "pch.h"
#include "convert.h"

void Convert::convert()
{
	int ori = m_ori;
	int digiCount = 1; // ×ÜÎ»Êý
	while (ori /= m_scale)
	{
		digiCount++;
	}
	while (digiCount > 0)
	{
		int xscale = xScale(--digiCount);
		int xdigit = m_ori / xscale;
		m_result.push_back(xdigit);
		m_ori -= xscale * xdigit;
	}
}

int Convert::xScale(int power)
{
	int result = 1;
	for (int i = 0; i < power; i++)
	{
		result *= m_scale;
	}
	return result;
}
#pragma once

#ifndef _PCH_H_
#define _PCH_H_

#include <fstream>
#include <random>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <io.h>
#include <direct.h>
#include <Windows.h>

using uchar = unsigned char;
using ushrt = unsigned short;
using uint = unsigned int;
typedef std::time_t span1970;
typedef std::tm sTime;
// �ָ���
inline static const std::string& SPLITPATTERN_CARR()
{
	static const std::string SPLITPATTERN_CARR = "|"; // ְҵ�����ļ�
	return SPLITPATTERN_CARR;
}
inline static const std::string& SPLITPATTERN_SVREG()
{
	static const std::string SPLITPATTERN_SVREG = "><"; // �浵ע���
	return SPLITPATTERN_SVREG;
}
inline static const std::string& SPLITPATTERN_PLYR()
{
	static const std::string SPLITPATTERN_PLYR = " = "; // ��������ļ�
	return SPLITPATTERN_PLYR;
}

#endif
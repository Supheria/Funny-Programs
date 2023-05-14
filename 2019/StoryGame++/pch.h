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
// 分隔符
inline static const std::string& SPLITPATTERN_CARR()
{
	static const std::string SPLITPATTERN_CARR = "|"; // 职业配置文件
	return SPLITPATTERN_CARR;
}
inline static const std::string& SPLITPATTERN_SVREG()
{
	static const std::string SPLITPATTERN_SVREG = "><"; // 存档注册表
	return SPLITPATTERN_SVREG;
}
inline static const std::string& SPLITPATTERN_PLYR()
{
	static const std::string SPLITPATTERN_PLYR = " = "; // 身份配置文件
	return SPLITPATTERN_PLYR;
}

#endif
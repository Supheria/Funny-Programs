#pragma once
#include "pch.h"
#include "convert.h"
//#include <fstream>

#define thePath "..\\10to15.ini"
struct IniFile
{
	int scale = 15; // 进制
	int original = 0; // 初始值
	int times = 0; // 迭代次数
	int add = 0; // 叠加值
	int pos = 0; // 选中行
	CRect mainRect{ 0, 0, 252, 359 };
};

inline bool ReadIniFile(IniFile& inifile)
{
	CFile infile;
	if (infile.Open(thePath, CFile::modeRead | CFile::shareDenyNone))
	{
		infile.Read(&inifile, sizeof(inifile)); // 返回读取到的字节数
		return true;
	}
	else
		return false;
	infile.Close();
}
	

inline void OutIniFile(IniFile& inifile)
{
	CFile outfile;
	if (outfile.Open(thePath, CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive))
	{
		outfile.Write(&inifile, sizeof(inifile));
	}
	else
		AfxMessageBox("配置文件保存失败。");
	outfile.Close();
}
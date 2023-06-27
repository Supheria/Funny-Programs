#pragma once
#include "pch.h"
#include "Helper.h"
//#include <fstream>

#define thePath "./TuneHelperIniFile.ini"
struct IniFile
{
	short pos = 0;
	short tunemode = Helper::main;
	short chrdmod = Helper::third;
	
};

inline bool ReadIniFile(IniFile& inifile)
{
	CFile infile;
	if (infile.Open(thePath, CFile::modeRead | CFile::shareDenyNone))
	{
		infile.Read(&inifile, sizeof(inifile)); // ���ض�ȡ�����ֽ���
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
		AfxMessageBox("�����ļ�����ʧ�ܡ�");
	outfile.Close();
}
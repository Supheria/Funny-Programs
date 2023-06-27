#pragma once
#include "pch.h"
#include "convert.h"
//#include <fstream>

#define thePath "..\\10to15.ini"
struct IniFile
{
	int scale = 15; // ����
	int original = 0; // ��ʼֵ
	int times = 0; // ��������
	int add = 0; // ����ֵ
	int pos = 0; // ѡ����
	CRect mainRect{ 0, 0, 252, 359 };
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
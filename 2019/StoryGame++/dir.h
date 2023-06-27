#pragma once

#ifndef _DIR_H_
#define _DIR_H_

#include "pch.h"

#pragma region ��Ҫ·��
inline static const std::string& RootDir()
{
	static const std::string RootDir = ".\\StoryGame\\"; // ��Ŀ¼
	return RootDir;
}
inline static const std::string& DataDir()
{
	static const std::string DataDir = RootDir() + "data\\"; //�����ļ�Ŀ¼
	return DataDir;
}
inline static const std::string& SaveDir()
{
	static const std::string SaveDir = DataDir() + "save\\"; //�浵Ŀ¼
	return SaveDir;
}
inline static const std::string& IniDir()
{
	static const std::string IniDir = DataDir() + "ini\\"; //�����ļ�Ŀ¼
	return IniDir;
}
static const std::string dirs[] = {
	RootDir(),
	DataDir(),
	SaveDir(),
	IniDir(),
};
#pragma endregion
#pragma region �ļ���
// �浵Ŀ¼��
inline static const std::string& sv_PassportName()
{
	static const std::string sv_PassportName = "passport"; // ͨ��֤
	return sv_PassportName;
}
inline static const std::string& sv_AdvanceName()
{
	static const std::string sv_AdvanceName = "advance"; // ����
	return sv_AdvanceName;
}
// �����ļ�Ŀ¼��
inline static const std::string& sv_RegisterPath()
{
	static const std::string sv_RegisterPath = IniDir() + "svreg.reg"; // �浵��ע���ļ�
	return sv_RegisterPath;
}
inline static const std::string& ini_CareerPath()
{
	static const std::string ini_CareerPath = IniDir() + "carr.ini";
	return ini_CareerPath;
}
inline static const std::string& ini_PlayerPath()
{
	static const std::string ini_PlayerPath = IniDir() + "plyr.ini"; // ���˿ڣ�����Ĺ־��ݣ�
	return ini_PlayerPath;
}
#pragma endregion

#endif
#pragma once

#ifndef _DIR_H_
#define _DIR_H_

#include "pch.h"

#pragma region 主要路径
inline static const std::string& RootDir()
{
	static const std::string RootDir = ".\\StoryGame\\"; // 根目录
	return RootDir;
}
inline static const std::string& DataDir()
{
	static const std::string DataDir = RootDir() + "data\\"; //数据文件目录
	return DataDir;
}
inline static const std::string& SaveDir()
{
	static const std::string SaveDir = DataDir() + "save\\"; //存档目录
	return SaveDir;
}
inline static const std::string& IniDir()
{
	static const std::string IniDir = DataDir() + "ini\\"; //配置文件目录
	return IniDir;
}
static const std::string dirs[] = {
	RootDir(),
	DataDir(),
	SaveDir(),
	IniDir(),
};
#pragma endregion
#pragma region 文件名
// 存档目录下
inline static const std::string& sv_PassportName()
{
	static const std::string sv_PassportName = "passport"; // 通行证
	return sv_PassportName;
}
inline static const std::string& sv_AdvanceName()
{
	static const std::string sv_AdvanceName = "advance"; // 进度
	return sv_AdvanceName;
}
// 配置文件目录下
inline static const std::string& sv_RegisterPath()
{
	static const std::string sv_RegisterPath = IniDir() + "svreg.reg"; // 存档的注册文件
	return sv_RegisterPath;
}
inline static const std::string& ini_CareerPath()
{
	static const std::string ini_CareerPath = IniDir() + "carr.ini";
	return ini_CareerPath;
}
inline static const std::string& ini_PlayerPath()
{
	static const std::string ini_PlayerPath = IniDir() + "plyr.ini"; // 总人口（包含墓志身份）
	return ini_PlayerPath;
}
#pragma endregion

#endif
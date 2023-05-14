#pragma once
/*m_pos在ReadSaveInfo()时被赋值， 或新建的身份在UpdateReg()时被赋值*/
#ifndef _SAVE_H_
#define _SAVE_H_

#include "player.h"

class Save;

class SaveReg
{
public:
	friend class Save;
public:
	//bool bad_reg; // 注册表异常（无法读写、无法新建）指示器
	std::vector<std::string>* content_living; // 充口容器（正常和非法身份）
	std::vector<std::string>* content_canceled; // 墓志容器（注销身份）
	uint thelastnum; // 
public:
	SaveReg();
	~SaveReg();
private:
	//bool ReadReg();
	//bool OutputReg();
	bool GetClauseNum();
	bool UpdatePlayerNum();
public:
	bool ReadReg();
	bool OutputReg();
	int ShowLivingContent();
};

class Save : public Player
{
public:
	friend class SaveReg;
private:
	std::string m_vrfcode; // 效验码
	span1970 m_settime; // 创建时间
	uint m_pos; // 存档位
	span1970 m_edittime; // 修改时间
	//std::vector<std::string> m_content; // 注册表内容
	std::string m_svdir; // 存档文件夹路径
public:
	Save(
		std::string name = "",
		uint career = 0,
		std::vector<ushrt> _3Q = { 0, 0, 0 },
		uint wealth = 0);
	~Save();
private:
	std::string AcquireVrfcode(); // 获取效验码
	std::string FormRegClause(); // 生成注册条目
	//bool ReadReg();
	//bool OutputReg();
	void UpdateLivingContent(); // 更新充口容器
	//bool FindPosition();
	bool ReadPassport();
	bool ReadAdvance();
	bool OutputPassport();
	bool OutputAdvance();
public:
	bool ReadSaveInfo(uint pos);
	bool OutputSaveInfo();
	bool CancelAccount(uint pos = 0);
};

#endif
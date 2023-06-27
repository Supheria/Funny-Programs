#pragma once
/*m_pos��ReadSaveInfo()ʱ����ֵ�� ���½��������UpdateReg()ʱ����ֵ*/
#ifndef _SAVE_H_
#define _SAVE_H_

#include "player.h"

class Save;

class SaveReg
{
public:
	friend class Save;
public:
	//bool bad_reg; // ע����쳣���޷���д���޷��½���ָʾ��
	std::vector<std::string>* content_living; // ��������������ͷǷ���ݣ�
	std::vector<std::string>* content_canceled; // Ĺ־������ע����ݣ�
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
	std::string m_vrfcode; // Ч����
	span1970 m_settime; // ����ʱ��
	uint m_pos; // �浵λ
	span1970 m_edittime; // �޸�ʱ��
	//std::vector<std::string> m_content; // ע�������
	std::string m_svdir; // �浵�ļ���·��
public:
	Save(
		std::string name = "",
		uint career = 0,
		std::vector<ushrt> _3Q = { 0, 0, 0 },
		uint wealth = 0);
	~Save();
private:
	std::string AcquireVrfcode(); // ��ȡЧ����
	std::string FormRegClause(); // ����ע����Ŀ
	//bool ReadReg();
	//bool OutputReg();
	void UpdateLivingContent(); // ���³������
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
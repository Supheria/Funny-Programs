#pragma once

#ifndef _CAREER_H_
#define _CAREER_H_

#include "pch.h"

struct CarrInfo;
static class Career
{
	uint m_carrnum; // ְҵ��Ψһ���
	std::string m_carrname; // ְҵ����
	ushrt m_gift; // �츳����
	float m_gift_variance; // �츳����
	uint m_wealth; // �Ƹ�����
	float m_wlth_variance; // �Ƹ�����
	ushrt m_last_gift; // �����츳����
	uint m_last_wlth; // ���²Ƹ�ֵ
	Career()
	{
		m_carrnum = 0;
		m_carrname = "";
		m_gift = 0;
		m_gift_variance = 2.5;
		m_wealth = 0;
		m_wlth_variance = 50;
		m_last_gift = 0;
		m_last_wlth = 0;
	}
public:
	friend bool IniCareer();
	friend void OutputCareer();
	friend uint ShowCareer();
	friend CarrInfo SelectCareer(uint pos);
	friend void UpdateSelectedCareer(CarrInfo& carrinfo);
	friend std::string GetCareerName(uint carrnum);
};
struct CarrInfo
{
	uint m_carrnum; // ְҵ���
	ushrt m_last_gift; // �����츳����
	uint m_last_wlth; // ���²Ƹ�ֵ
	std::string m_carrname;
};

bool IniCareer();
void OutputCareer();
uint ShowCareer();
CarrInfo SelectCareer(uint pos);
void UpdateSelectedCareer(CarrInfo& carrinfo);
std::string GetCareerName(uint carrnum);

#endif
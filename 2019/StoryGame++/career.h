#pragma once

#ifndef _CAREER_H_
#define _CAREER_H_

#include "pch.h"

struct CarrInfo;
static class Career
{
	uint m_carrnum; // 职业的唯一编号
	std::string m_carrname; // 职业名称
	ushrt m_gift; // 天赋期望
	float m_gift_variance; // 天赋方差
	uint m_wealth; // 财富期望
	float m_wlth_variance; // 财富方差
	ushrt m_last_gift; // 最新天赋点数
	uint m_last_wlth; // 最新财富值
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
	uint m_carrnum; // 职业编号
	ushrt m_last_gift; // 最新天赋点数
	uint m_last_wlth; // 最新财富值
	std::string m_carrname;
};

bool IniCareer();
void OutputCareer();
uint ShowCareer();
CarrInfo SelectCareer(uint pos);
void UpdateSelectedCareer(CarrInfo& carrinfo);
std::string GetCareerName(uint carrnum);

#endif
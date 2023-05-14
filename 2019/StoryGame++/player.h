#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "pch.h"

class Player
{
private:
	uint m_num; // 身份的唯一编号
	ushrt m_status; // 身份状态
	//Player(const Player&); // ?
protected:
	std::string m_name; // 身份名称
	uint m_career; // 职业
	ushrt m_moral; // 道德值-100~100
	std::vector<ushrt> m_3Q; // 三商
	uint m_wealth; // 财富
public:
	enum {
		eCancel, // 注销
		eNatural, // 正常
		eIllegal // 非法
	};
protected:
	Player(
		std::string name,
		uint career,
		std::vector<ushrt> _3Q,
		uint wealth)
	{
		m_num = 0;
		m_status = eNatural;
		m_name = name;
		m_career = career;
		m_moral = 0;
		for (auto it = _3Q.begin(); it != _3Q.end(); it++)
		{
			m_3Q.push_back(*it);
		}
		m_wealth = wealth;
	}
	~Player() {};
protected:
	void set_num(uint num) { m_num = num; } uint get_num() { return m_num; }
	void set_status(ushrt status) { m_status = status; }
	void cancel() { m_status = eCancel; }
	void illegal() { m_status = eIllegal; }
	ushrt get_status() { return m_status; }
};

#endif
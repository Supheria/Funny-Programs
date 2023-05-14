#pragma once

#ifndef _SAVE_H_
#define _SAVE_H_

#include "tools.h"
#include "dir.h"
#include "career.h"
#include "player.h"

namespace sv
{
	const int MAX_POPULATION = 200;
	const std::string reg = sv_RegisterPath(); // 注册表路径
	const std::string SPLITPATTERN_SVREG() = "><";
	static uint position = 0; // 全局存档位指示器
	static std::string save = ""; // 存档位路径
	const enum {
		badsetnew = -2,
		empty,
		missing,
		right
	};
	inline char TestReg(bool DoSetnew = true)
	{
		using namespace std; using namespace myTools;
		if (!TestFileExistence(reg)) // 注册表丢失
		{
			if (DoSetnew)
			{
				ofstream fout(reg);
				if (!fout.is_open())
				{
					cout << "\n\nFatalErro：无法生成注册表！\n\n";
					return badsetnew;
				}
			}
			else
				return missing;
		}
		else if (!TestFileContent(reg)) { return empty; } // 文件为空
		else
			return right;
	}
	inline std::vector<std::string> ReadReg(bool DoDecode = true)
	{
		using namespace std; using namespace myTools;
		ifstream fin;
		fin.open(reg);
		vector<string> content; string svrec;
		while (fin.peek() != EOF)
		{
			getline(fin, svrec);
			if (DoDecode) { decoder(svrec); }
			content.push_back(svrec);
		}
		fin.close();
		return content;
	}
	inline void OutputReg(std::vector<std::string>& content)
	{
		using namespace std; using namespace myTools;
		ofstream fout(reg);
		for (auto it = content.begin(); it != content.end(); it++) // 输出注册表
		{
			fout << encoder(*it) << endl;
		}

	}
	struct Passport {
		//Passport(通行证)是每个身份独有的身份识别数据，除非必要，否则不要变更这部分数据
		uint num; // 身份编号
		ushrt status; // 身份状态
		span1970 settime; // 身份确立时间
		std::string name; // 名称
		uint career; // 职业
	} passport;
	struct Advance {
		// Advance（进度）记录每个存档的游戏进度
		std::string vrfcode; // 存档效验码
		span1970 edittime; // 编辑时间
		std::vector<ushrt> _3Q; // 三商
		uint wealth; // 财富
	} advance;
	inline bool ReadPassport(Passport& pa = passport)
	{
		using namespace std; using namespace myTools;
		const string pass = save + sv_PassportName();
		if (TestFileExistence(pass) && TestFileContent(pass))
		{
			ifstream fin(pass);
			string num; getline(fin, num); pa.num = atoi(num.c_str());
			string sta; getline(fin, sta); pa.status = atoi(sta.c_str());
			string set; getline(fin, set); pa.settime = _atoi64(set.c_str());
			getline(fin, pa.name); decoder(pa.name);
			string crr; getline(fin, crr); pa.career = atoi(crr.c_str());
			return true;
		}
		else
			return false;
	}
	inline bool OutputPassport(Passport& pa = passport)
	{
		using namespace std; using namespace myTools;
		const string pass = save + sv_PassportName();
		ofstream fout(pass);
		if (!fout.is_open()) { return false; }
		fout << pa.num << endl
			<< pa.status << endl
			<< pa.settime << endl
			<< encoder(pa.name) << endl
			<< pa.career;
		return true;
	}
	inline bool ReadAdvance(Advance& ad = advance)
	{
		using namespace std; using namespace myTools;
		const string advc = save + sv_AdvanceName();
		if (TestFileExistence(advc) && TestFileContent(advc))
		{
			ifstream fin(advc);
			getline(fin, ad.vrfcode);
			string edt; getline(fin, edt); ad.edittime = _atoi64(edt.c_str());
			string IQ; getline(fin, IQ); ad._3Q[0] = atoi(IQ.c_str());
			string HQ; getline(fin, HQ); ad._3Q[1] = atoi(HQ.c_str());
			string EQ; getline(fin, EQ); ad._3Q[2] = atoi(EQ.c_str());
			string wea; getline(fin, wea); ad.wealth = atoi(wea.c_str());
			return true;
		}
		else
			return false;
	}
	inline bool OutputAdvance(Advance& ad = advance)
	{
		using namespace std; using namespace myTools;

		const string advc = save + sv_AdvanceName();
		ofstream fout(advc);
		if (!fout.is_open()) { return false; }
		fout << ad.vrfcode << endl
			<< ad.edittime << endl
			<< ad._3Q[0] << endl
			<< ad._3Q[1] << endl
			<< ad._3Q[2] << endl
			<< ad.wealth;
		return true;
	}
	struct VerifyCode {
		Passport& pa;
		Advance& ad;
		std::string vrfcode;
		uint pos; // 存档位
	} code{ passport, advance, "", 0 };
	inline void GetVerifyCode()
	{
		using namespace std; using namespace myTools;
		uint a = (code.pa.num % code.pos) + code.pa.status + (code.ad.edittime % code.pa.settime) + code.pa.career + code.ad._3Q[0] + code.ad._3Q[1] + code.ad._3Q[2];
		code.vrfcode = to_string((code.ad.wealth + a) % a) + code.pa.name;
		encoder(code.vrfcode);
	}
	inline std::string GetRegClause(Player& player, span1970& span) // 注册表条目格式
	{
		using namespace std;
		// 存档记录格式（未加密）：
		// 身份编号><身份状态><名称><职业><编辑时间
		time(&span); // 获取自1970/01/01至今已经过的秒数
		return to_string(player.get_num()) + SPLITPATTERN_SVREG() + to_string(player.get_status()) + SPLITPATTERN_SVREG() + player.get_name() + SPLITPATTERN_SVREG() + to_string(player.get_carr()) + SPLITPATTERN_SVREG() + to_string(span);
	}
	inline void SetSaveInfo(Player& player, span1970 edittime, span1970 settime = passport.settime)
	{
		passport.num = player.get_num(); // 身份编号
		passport.status = player.get_status(); // 身份状态
		passport.settime = settime; // 身份确立时间
		passport.name = player.get_name(); // 名称
		passport.career = player.get_carr(); // 职业
		advance.edittime = edittime; // 存档最近一次编辑时间
		advance._3Q = player.get_3Q(); // 三商
		advance.wealth = player.get_wlth(); // 财富
		code.pos = position; // 存档位
		code.pa = passport;
		code.ad = advance;
		GetVerifyCode();
		advance.vrfcode = code.vrfcode; // 存档效验码
	}
	inline uint FindPosition(Player& player, std::vector<std::string>content)
	{
		using namespace std; using namespace ieTools;
		uint pos = 1;
		for (auto it = content.begin(); it != content.end(); it++)
		{
			auto test = SplitString(*it, SPLITPATTERN_SVREG());
			if (test[0] == to_string(player.get_num())) // 存在该身份
			{
				position = pos;
				return position;
			}
			if (atoi(test[1].c_str()) != Player::eCancel) { pos++; } // 已注销身份不计入存档位
		}
		position = 0; // 无记录
		return position;
	}

	inline bool IfPopulationFilled()
	{
		using namespace std; using namespace ieTools;
		if (bool test = TestReg)
		{
			auto content = ReadReg();
			uint population = 0;
			for (auto it = content.begin(); it != content.end(); it++)
			{
				auto test = SplitString(*it, SPLITPATTERN_SVREG());
				if (atoi(test[1].c_str()) != Player::eCancel) // 已注销身份不算入人口
				{
					population++;
				}
			}
			if (population > MAX_POPULATION)
			{
				cout << "\n\n人口已满，无法再建立新的身份信息。";
				return true;
			}
			return false;
		}
		else
			return false;

	}
	inline bool OutputSaveFolder(Player& player)
	{
		using namespace std; using namespace ieTools; using namespace myTools;
		if (badsetnew == TestReg()) { return false; }
		vector<string> content = ReadReg();
		span1970 span;
		enum { IsNew, IsIllegal, IsOld };
		ushrt status = IsNew;
#pragma region 更新注册表

		if (FindPosition(player, content))
		{
			string clause = GetRegClause(player, span);
			status = IsOld;
			content[player.get_num() - 1] = clause;
		}
		else
		{
			if (player.get_num()) { status = IsIllegal; }
			else
			{
				player.set_num(content.size() + 1);
				string clause = GetRegClause(player, span);
				content.push_back(clause);
				position = content.size();

			}
		}
#pragma endregion
#pragma region 输出存档文件
		save = SaveDir() + "save" + to_string(position) + "\\";
		if (IsNew == status)
		{
			CreateDir(save);
			SetSaveInfo(player, span, span);
			if (!OutputPassport() || !OutputAdvance())
			{
				cout << "\n\nFatalErro：无法生成存档！\n\n";
				return false;
			}
			OutputReg(content);
			return true;
		}
		else if (IsOld == status && ReadPassport() && ReadAdvance())
		{
			SetSaveInfo(player, span);
			OutputPassport();
			OutputAdvance();
			OutputReg(content);
			return true;
		}
		else
		{
			player.illegal();
			string clause = GetRegClause(player, span);
			content[player.get_num() - 1] = clause;
			OutputReg(content);
			return false;
		}
#pragma endregion
	}
	inline bool NewSave(Player& newone)
	{
		using namespace std; using namespace myTools;
#pragma region 输入名称
		cout << "请输入玩家名称：";
		string name; getline(cin, name);
		if (bool isblk = IfABlankString(name))
		{
			cout << "输入错误！";
			//cin.clear(); if (!isblk) { iclear(); }
			return false;
		}
#pragma endregion
#pragma region 选择角色
		cout << "请选择角色：";
	P:
		for (int i = 0; i < CARRNUM; i++) // 显示职业目录
		{
			cout << endl << i + 1 << ". " << carr[i].carrname;
		}
		ushrt pos;
		if (!(cin >> pos) || pos <= 0 || pos > CARRNUM)
		{
			cout << "输入错误！";
			cin.clear(); iclear();
			return false;
		}
		iclear();
		pos--;
		cout << "\n天赋点数：" << (short)carr[pos].gift;
		cout << "\n既有财产：" << carr[pos].iniwealth;
		cout << "\n是否选择" << carr[pos].carrname << "（Y or N，其他键放弃新建）";
		if (cin.peek() == 'N' || cin.peek() == 'n')
		{
			cout << "请重新选择角色：";
			iclear(); goto P;
		}
		else if (cin.peek() != 'Y' && cin.peek() != 'y')
		{
			cin.clear(); iclear(); // if (cin.peek() != '\n') iclear();
			return false;
		}
		iclear();
#pragma endregion
#pragma region 分配点数
		cout << "请为" << carr[pos].carrname << name << "分配天赋点数\n";
	Q:
		vector<ushrt> _3Q;
		std::map<ushrt, string> mp = { {0, "【智慧】"},  {1, "【健康】"},  {2, "【社交】"}, };
		ushrt gift = carr[pos].gift;
		for (int i = 0; i < 2; i++)
		{
			ushrt choice;
			cout << mp[i] << "\n";;
			while (!(cin >> choice) || choice <= 0 || choice >= gift)
			{
				cout << "输入错误，请重新输入：";
				cin.clear(); iclear();
				cin >> choice;
			}
			_3Q.push_back(choice);
			gift -= choice;
		}
		_3Q.push_back(gift);
		for (int i = 0; i < 3; i++)
		{
			cout << mp[i] << _3Q[i] << "\n";
		}
		iclear();
		cout << "\n请确认" << carr[pos].carrname << "（键入Y确认，其他键重新分配）";
		if (cin.peek() != 'Y' && cin.peek() != 'y')
		{
			cout << "请重新为" << carr[pos].carrname << name << "分配天赋点数\n"
				<< "（拥有" << (short)carr[pos].gift << "点天赋）\n";
			iclear(); goto Q;
		}
#pragma endregion
#pragma region 初始化newone
		cout << name << "是一位" << carr[pos].carrname;
		newone.set_name(name);
		newone.set_carr(carr[pos].num);
		newone.set_3Q(_3Q);
		newone.set_wlth(carr[pos].iniwealth);
#pragma endregion
		if (OutputSaveFolder(newone)) { return true; }
		else
			return false;
	}

}

#endif
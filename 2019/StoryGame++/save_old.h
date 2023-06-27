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
	const std::string reg = sv_RegisterPath(); // ע���·��
	const std::string SPLITPATTERN_SVREG() = "><";
	static uint position = 0; // ȫ�ִ浵λָʾ��
	static std::string save = ""; // �浵λ·��
	const enum {
		badsetnew = -2,
		empty,
		missing,
		right
	};
	inline char TestReg(bool DoSetnew = true)
	{
		using namespace std; using namespace myTools;
		if (!TestFileExistence(reg)) // ע���ʧ
		{
			if (DoSetnew)
			{
				ofstream fout(reg);
				if (!fout.is_open())
				{
					cout << "\n\nFatalErro���޷�����ע���\n\n";
					return badsetnew;
				}
			}
			else
				return missing;
		}
		else if (!TestFileContent(reg)) { return empty; } // �ļ�Ϊ��
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
		for (auto it = content.begin(); it != content.end(); it++) // ���ע���
		{
			fout << encoder(*it) << endl;
		}

	}
	struct Passport {
		//Passport(ͨ��֤)��ÿ����ݶ��е����ʶ�����ݣ����Ǳ�Ҫ������Ҫ����ⲿ������
		uint num; // ��ݱ��
		ushrt status; // ���״̬
		span1970 settime; // ���ȷ��ʱ��
		std::string name; // ����
		uint career; // ְҵ
	} passport;
	struct Advance {
		// Advance�����ȣ���¼ÿ���浵����Ϸ����
		std::string vrfcode; // �浵Ч����
		span1970 edittime; // �༭ʱ��
		std::vector<ushrt> _3Q; // ����
		uint wealth; // �Ƹ�
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
		uint pos; // �浵λ
	} code{ passport, advance, "", 0 };
	inline void GetVerifyCode()
	{
		using namespace std; using namespace myTools;
		uint a = (code.pa.num % code.pos) + code.pa.status + (code.ad.edittime % code.pa.settime) + code.pa.career + code.ad._3Q[0] + code.ad._3Q[1] + code.ad._3Q[2];
		code.vrfcode = to_string((code.ad.wealth + a) % a) + code.pa.name;
		encoder(code.vrfcode);
	}
	inline std::string GetRegClause(Player& player, span1970& span) // ע�����Ŀ��ʽ
	{
		using namespace std;
		// �浵��¼��ʽ��δ���ܣ���
		// ��ݱ��><���״̬><����><ְҵ><�༭ʱ��
		time(&span); // ��ȡ��1970/01/01�����Ѿ���������
		return to_string(player.get_num()) + SPLITPATTERN_SVREG() + to_string(player.get_status()) + SPLITPATTERN_SVREG() + player.get_name() + SPLITPATTERN_SVREG() + to_string(player.get_carr()) + SPLITPATTERN_SVREG() + to_string(span);
	}
	inline void SetSaveInfo(Player& player, span1970 edittime, span1970 settime = passport.settime)
	{
		passport.num = player.get_num(); // ��ݱ��
		passport.status = player.get_status(); // ���״̬
		passport.settime = settime; // ���ȷ��ʱ��
		passport.name = player.get_name(); // ����
		passport.career = player.get_carr(); // ְҵ
		advance.edittime = edittime; // �浵���һ�α༭ʱ��
		advance._3Q = player.get_3Q(); // ����
		advance.wealth = player.get_wlth(); // �Ƹ�
		code.pos = position; // �浵λ
		code.pa = passport;
		code.ad = advance;
		GetVerifyCode();
		advance.vrfcode = code.vrfcode; // �浵Ч����
	}
	inline uint FindPosition(Player& player, std::vector<std::string>content)
	{
		using namespace std; using namespace ieTools;
		uint pos = 1;
		for (auto it = content.begin(); it != content.end(); it++)
		{
			auto test = SplitString(*it, SPLITPATTERN_SVREG());
			if (test[0] == to_string(player.get_num())) // ���ڸ����
			{
				position = pos;
				return position;
			}
			if (atoi(test[1].c_str()) != Player::eCancel) { pos++; } // ��ע����ݲ�����浵λ
		}
		position = 0; // �޼�¼
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
				if (atoi(test[1].c_str()) != Player::eCancel) // ��ע����ݲ������˿�
				{
					population++;
				}
			}
			if (population > MAX_POPULATION)
			{
				cout << "\n\n�˿��������޷��ٽ����µ������Ϣ��";
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
#pragma region ����ע���

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
#pragma region ����浵�ļ�
		save = SaveDir() + "save" + to_string(position) + "\\";
		if (IsNew == status)
		{
			CreateDir(save);
			SetSaveInfo(player, span, span);
			if (!OutputPassport() || !OutputAdvance())
			{
				cout << "\n\nFatalErro���޷����ɴ浵��\n\n";
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
#pragma region ��������
		cout << "������������ƣ�";
		string name; getline(cin, name);
		if (bool isblk = IfABlankString(name))
		{
			cout << "�������";
			//cin.clear(); if (!isblk) { iclear(); }
			return false;
		}
#pragma endregion
#pragma region ѡ���ɫ
		cout << "��ѡ���ɫ��";
	P:
		for (int i = 0; i < CARRNUM; i++) // ��ʾְҵĿ¼
		{
			cout << endl << i + 1 << ". " << carr[i].carrname;
		}
		ushrt pos;
		if (!(cin >> pos) || pos <= 0 || pos > CARRNUM)
		{
			cout << "�������";
			cin.clear(); iclear();
			return false;
		}
		iclear();
		pos--;
		cout << "\n�츳������" << (short)carr[pos].gift;
		cout << "\n���вƲ���" << carr[pos].iniwealth;
		cout << "\n�Ƿ�ѡ��" << carr[pos].carrname << "��Y or N�������������½���";
		if (cin.peek() == 'N' || cin.peek() == 'n')
		{
			cout << "������ѡ���ɫ��";
			iclear(); goto P;
		}
		else if (cin.peek() != 'Y' && cin.peek() != 'y')
		{
			cin.clear(); iclear(); // if (cin.peek() != '\n') iclear();
			return false;
		}
		iclear();
#pragma endregion
#pragma region �������
		cout << "��Ϊ" << carr[pos].carrname << name << "�����츳����\n";
	Q:
		vector<ushrt> _3Q;
		std::map<ushrt, string> mp = { {0, "���ǻۡ�"},  {1, "��������"},  {2, "���罻��"}, };
		ushrt gift = carr[pos].gift;
		for (int i = 0; i < 2; i++)
		{
			ushrt choice;
			cout << mp[i] << "\n";;
			while (!(cin >> choice) || choice <= 0 || choice >= gift)
			{
				cout << "����������������룺";
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
		cout << "\n��ȷ��" << carr[pos].carrname << "������Yȷ�ϣ����������·��䣩";
		if (cin.peek() != 'Y' && cin.peek() != 'y')
		{
			cout << "������Ϊ" << carr[pos].carrname << name << "�����츳����\n"
				<< "��ӵ��" << (short)carr[pos].gift << "���츳��\n";
			iclear(); goto Q;
		}
#pragma endregion
#pragma region ��ʼ��newone
		cout << name << "��һλ" << carr[pos].carrname;
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
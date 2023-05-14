#include "save class.h"
#include "career.h"
#include "tools.h"

extern SaveReg savereg;

bool NewSave()
{
	using namespace std; using namespace myTools;
#pragma region 输入名称
	cout << "请输入玩家名称：";
	string name; getline(cin, name);
	if (bool isblk = IfABlankString(name))
	{
		cout << "输入错误！新建角色失败。";
		//cin.clear(); if (!isblk) { iclear(); }
		return false;
	}
#pragma endregion
#pragma region 选择角色
	cout << "请选择职业：\n";
P:
	int carrnum = ShowCareer();
	uint pos;
	if (!(cin >> pos) || pos <= 0 || pos > carrnum)
	{
		cout << "输入错误！新建角色失败";
		cin.clear(); iclear();
		return false;
	}
	iclear();
	CarrInfo carrinfo = SelectCareer(pos);
	cout << "\n天赋点数：" << carrinfo.m_last_gift;
	cout << "\n既有财产：" << carrinfo.m_last_wlth;
	cout << "\n是否选择" << carrinfo.m_carrname << "（Y or N，其他键放弃新建）";
	if (cin.peek() == 'N' || cin.peek() == 'n')
	{
		cout << "请重新选择职业：\n";
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
	cout << "请为" << name << "分配天赋点数\n";
Q:
	vector<ushrt> _3Q;
	std::map<ushrt, string> mp = { {0, "【智慧】"},  {1, "【健康】"},  {2, "【社交】"}, };
	ushrt gift = carrinfo.m_last_gift;
	for (int i = 0; i < 2; i++)
	{
		ushrt choice;
		cout << mp[i] << "\n";
		for (int i = 1; !(cin >> choice) || choice <= 0 || choice >= gift - i; i--)
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
	cout << "\n请确认（键入Y确认，其他键重新分配）";
	if (cin.peek() != 'Y' && cin.peek() != 'y')
	{
		cout << "请重新为" << name << "分配天赋点数\n"
			<< "（拥有" << carrinfo.m_last_gift << "点天赋）\n";
		if (cin.peek() != '\n') iclear();; goto Q;
	}
	iclear();
#pragma endregion
#pragma region 初始化newsave
	Save newsave(name, carrinfo.m_carrnum, _3Q, carrinfo.m_last_wlth);
	if (!newsave.OutputSaveInfo()) { return false; }
#pragma endregion
	UpdateSelectedCareer(carrinfo);
	return true;
}

bool SelectSave()
{
	using namespace std; using namespace myTools;
	Save save;
	int record;
	//if ((record = savereg.ShowLivingContent()) == -1) { return false; }
	record = savereg.ShowLivingContent();
	if (!record)
	{
		cout << "请先新建身份。";
		return false;
	}
	cout << "请选择身份：";
	uint pos;
	if (!(cin >> pos) || pos <= 0 || pos > record)
	{
		cout << "输入错误！读取身份信息失败。";
		cin.clear(); iclear(); return false;
	}
	iclear();
	if (!save.ReadSaveInfo(pos))
	{
		cout << "标记为非法身份，请向" << GetCareerName(0001) << "询问解禁方式！";
	}
	return true;
}

void DeleteSave()
{
	using namespace std; using namespace myTools;
	int record;
	if ((record = savereg.ShowLivingContent()) == -1) { return; }
	if (!record)
	{
		cout << "没有身份记录。";
		return;
	}
	cout << "请选择要注销的身份：";
	uint pos;
	if (!(cin >> pos) || pos <= 0 || pos > record)
	{
		cout << "输入错误！注销身份失败。";
		cin.clear(); iclear(); return;
	}
	iclear();
#pragma 中文数字
	string chinum[] = { "\0", "一", "二", "三", "四" , "五", "六", "七", "八", "九", "十" };
	int A = 0; int B = 0; int C = 0; string ten = "\0"; string h_ten = "\0";  string hundr = "\0"; string zero = "\0";
	if (pos <= 10) { B = pos; } //一到十
	else if (pos % 10 == 0 && pos < 100) { A = pos / 10; B = 10; } //整十
	else if (pos < 100) { A = pos / 10; B = pos - A * 10; ten = "十"; A = A == 1 ? 0 : A; } //十一到九十九的非整数
	else // 一百到九百九十
	{
		A = pos / 100; hundr = "百"; pos -= A * 100;
		if (pos <= 10) { C = pos; zero = "零"; zero = C == 0 || C == 10 ? "\0" : zero; B = C == 10 ? 1 : B; } //一到十
		else if (pos % 10 == 0) { B = pos / 10; C = 10; } //整十
		else { B = pos / 10; C = pos - B * 10; h_ten = "十"; }//十一到九十九的非整数
	}
#pragma endregion
	cout << "\n确实要注销第" << chinum[A] << hundr << ten << zero << chinum[B] << h_ten << chinum[C] << "个身份吗？（键入Y确认，键入其他键保留）";
	if (cin.peek() != 'Y' && cin.peek() != 'y')
	{
		cout << "\n已保留。";
		iclear(); return;
	}
	cout << "\n注销中...";
	Save delsave;
	if (delsave.CancelAccount(pos))
	{
		cout << "注销成功！";
	}
	else
	{
		cout << "注销失败！";
	}
	iclear();
	return;
}
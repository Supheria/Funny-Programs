#include "save class.h"
#include "career.h"
#include "tools.h"

extern SaveReg savereg;

bool NewSave()
{
	using namespace std; using namespace myTools;
#pragma region ��������
	cout << "������������ƣ�";
	string name; getline(cin, name);
	if (bool isblk = IfABlankString(name))
	{
		cout << "��������½���ɫʧ�ܡ�";
		//cin.clear(); if (!isblk) { iclear(); }
		return false;
	}
#pragma endregion
#pragma region ѡ���ɫ
	cout << "��ѡ��ְҵ��\n";
P:
	int carrnum = ShowCareer();
	uint pos;
	if (!(cin >> pos) || pos <= 0 || pos > carrnum)
	{
		cout << "��������½���ɫʧ��";
		cin.clear(); iclear();
		return false;
	}
	iclear();
	CarrInfo carrinfo = SelectCareer(pos);
	cout << "\n�츳������" << carrinfo.m_last_gift;
	cout << "\n���вƲ���" << carrinfo.m_last_wlth;
	cout << "\n�Ƿ�ѡ��" << carrinfo.m_carrname << "��Y or N�������������½���";
	if (cin.peek() == 'N' || cin.peek() == 'n')
	{
		cout << "������ѡ��ְҵ��\n";
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
	cout << "��Ϊ" << name << "�����츳����\n";
Q:
	vector<ushrt> _3Q;
	std::map<ushrt, string> mp = { {0, "���ǻۡ�"},  {1, "��������"},  {2, "���罻��"}, };
	ushrt gift = carrinfo.m_last_gift;
	for (int i = 0; i < 2; i++)
	{
		ushrt choice;
		cout << mp[i] << "\n";
		for (int i = 1; !(cin >> choice) || choice <= 0 || choice >= gift - i; i--)
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
	cout << "\n��ȷ�ϣ�����Yȷ�ϣ����������·��䣩";
	if (cin.peek() != 'Y' && cin.peek() != 'y')
	{
		cout << "������Ϊ" << name << "�����츳����\n"
			<< "��ӵ��" << carrinfo.m_last_gift << "���츳��\n";
		if (cin.peek() != '\n') iclear();; goto Q;
	}
	iclear();
#pragma endregion
#pragma region ��ʼ��newsave
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
		cout << "�����½���ݡ�";
		return false;
	}
	cout << "��ѡ����ݣ�";
	uint pos;
	if (!(cin >> pos) || pos <= 0 || pos > record)
	{
		cout << "������󣡶�ȡ�����Ϣʧ�ܡ�";
		cin.clear(); iclear(); return false;
	}
	iclear();
	if (!save.ReadSaveInfo(pos))
	{
		cout << "���Ϊ�Ƿ���ݣ�����" << GetCareerName(0001) << "ѯ�ʽ����ʽ��";
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
		cout << "û����ݼ�¼��";
		return;
	}
	cout << "��ѡ��Ҫע������ݣ�";
	uint pos;
	if (!(cin >> pos) || pos <= 0 || pos > record)
	{
		cout << "�������ע�����ʧ�ܡ�";
		cin.clear(); iclear(); return;
	}
	iclear();
#pragma ��������
	string chinum[] = { "\0", "һ", "��", "��", "��" , "��", "��", "��", "��", "��", "ʮ" };
	int A = 0; int B = 0; int C = 0; string ten = "\0"; string h_ten = "\0";  string hundr = "\0"; string zero = "\0";
	if (pos <= 10) { B = pos; } //һ��ʮ
	else if (pos % 10 == 0 && pos < 100) { A = pos / 10; B = 10; } //��ʮ
	else if (pos < 100) { A = pos / 10; B = pos - A * 10; ten = "ʮ"; A = A == 1 ? 0 : A; } //ʮһ����ʮ�ŵķ�����
	else // һ�ٵ��Űپ�ʮ
	{
		A = pos / 100; hundr = "��"; pos -= A * 100;
		if (pos <= 10) { C = pos; zero = "��"; zero = C == 0 || C == 10 ? "\0" : zero; B = C == 10 ? 1 : B; } //һ��ʮ
		else if (pos % 10 == 0) { B = pos / 10; C = 10; } //��ʮ
		else { B = pos / 10; C = pos - B * 10; h_ten = "ʮ"; }//ʮһ����ʮ�ŵķ�����
	}
#pragma endregion
	cout << "\nȷʵҪע����" << chinum[A] << hundr << ten << zero << chinum[B] << h_ten << chinum[C] << "������𣿣�����Yȷ�ϣ�����������������";
	if (cin.peek() != 'Y' && cin.peek() != 'y')
	{
		cout << "\n�ѱ�����";
		iclear(); return;
	}
	cout << "\nע����...";
	Save delsave;
	if (delsave.CancelAccount(pos))
	{
		cout << "ע���ɹ���";
	}
	else
	{
		cout << "ע��ʧ�ܣ�";
	}
	iclear();
	return;
}
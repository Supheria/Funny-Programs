// AddYourAccount.cpp : �������̨Ӧ�ó������ڵ㡣
/*BUG��¼��1.���id�ļ���ʧ���ǹ���Ա�½��˻�ʱ��Ȩ���½�һ��idΪ#1��id�ļ�����ᵼ�¸��½��˻�id�������˻���ͻ
           2.�û����������������������������ǻ�ù���ԱȨ��*/

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int INPUT_MAX = 21;
struct user
{
	char account[INPUT_MAX];
	char password[INPUT_MAX];
	char info_name[INPUT_MAX+5];
};

inline void iclear(){while (cin.get() != '\n') ;}
inline string file_name(user* temp)
{
	strcpy(temp->info_name, temp->account);
	strcat(temp->info_name, "_info.info");
	return temp->info_name;
}
inline bool get_alg(int n)
{
	if (n == 1) return 0;
	if ((n%2) != 0) return 0;
	return 1;
}

bool menu(user* temp);
void A(user* temp);
void B(user* temp);
void C(user* temp);
void D(user* temp);
void E(user* temp);
bool old_input(user* temp);
short test(user* temp);
bool new_actinput(user* temp);
bool new_pasinput(user* temp);
void set_new(user* temp);
int act_id();
void show_inf(user* temp);
void change_inf(user* temp);
int get_act_id(user* temp);
void administrator(user* temp);
typedef char* form(char* password);
typedef char* (*sec)(char* password);
form Phonix, Supheria;
sec alg[2] = {Phonix, Supheria};


int main()
{
	user* temp = new user;
	while (menu(temp)){}
	//delete temp;
	return 0;
}


bool menu(user* temp)
{
	cout<< "��ѡ��������ҵ��: \n\n";
	cout<< "��A���鿴�����˻���Ϣ��\n";
	cout<< "��B���½��˻���\n";
	cout<< "��C�����������˻���Ϣ��\n";
	cout<< "��D���޸������˻����롣\n";
	cout<< "��E��ע�������˻���\n";
	cout<< "���������˳�����\n";
	char choice[INPUT_MAX];
	cin.get(choice, INPUT_MAX);
	if (!strcmp(choice, "phonixsupheria"))
	{
		iclear();
		administrator(temp);
		return true;
	}
	cin.clear();
	iclear();
	cout<< endl;
	switch (choice[0])
	{
	case 'A' :
	case 'a' : A(temp);
		return true;
		break;
	case 'B' :
	case 'b' : B(temp);
		return true;
		break;
	case 'C' :
	case 'c' : C(temp);
		return true;
		break;
	case 'D' :
	case 'd' : D(temp);
		return true;
		break;
	case 'E' :
	case 'e' : E(temp);
		return true;
		break;
	default :
		return false;
	}
}


void A(user* temp)
{
	if (old_input(temp))
	{
		cout<< endl;
		show_inf(temp);
	}
	cout<< "���س������ز˵�\n";
	cin.get();
}


void B(user* temp)
{
	cout<< "�������˻�����" << INPUT_MAX - 1 << "λ���ڣ���\n";
	if (!new_actinput(temp))
	{
		cout<< "�����˻�ʧ�ܣ�";
		cout<< "���س������ز˵�\n";
		cin.get();
		return;
	}
	cout<< "���������루" << INPUT_MAX - 1 << "λ���ڣ���������6λ����\n";
	if (new_pasinput(temp))
		set_new(temp);
	else
		cout<< "�����˻�ʧ�ܣ�";
	cout<< "���س������ز˵�\n";
	cin.get();
}


void C(user* temp)
{
	if (old_input(temp))
	{
		cout<< endl;
		change_inf(temp);
		cout<< "�˻���Ϣ���ĳɹ���";
	}
	else
		cout<< "�˻���Ϣ����ʧ�ܣ�";
	cout<< "���س������ز˵�\n";
	cin.get();
}


void D(user* temp)
{
	if (old_input(temp))
	{
		if (!get_act_id(temp))
		{
		cout<< "�˻���Ϣ�𻵻�ʧ���������ʧ�ܣ�";
		cout<< "\n���س������ز˵�\n";
		cin.get();
		return;
		}
		cout<< "�����������루20λ���ڣ���������6λ����\n";
		if (new_pasinput(temp))
		{
			ofstream fout;
			fout.open(temp->account);
			fout<< alg[get_alg(get_act_id(temp))](temp->password);
			fout.close();
			cin.get();
			cout<< "\n������³ɹ���";
		}
		else
			cout<< "\n�������ʧ�ܣ�";
	}
	cout<< "���س������ز˵�\n";
	cin.get();
}


void E(user* temp)
{
	if (old_input(temp))
	{
		cout<< "�Ƿ�ȷ��ע�����˻�����Y or N��";
		cout<< "\n�������˻����е���Ϣ���޷���أ���";
		char a;
		cin>> a;
		iclear();
		if (a != 'Y'&&a != 'y')
		{
			cout<< "\n�˻�δע����";
			cout<< "���س������ز˵�\n";
			cin.get();
			return;
		}
		ofstream fout;
		fout.open(file_name(temp));
		fout<< "���˻���ע��\n";
		cout<< "\n���˻���ע����";
	}
	cout<< "���س������ز˵�\n";
	cin.get();
}


bool old_input(user* temp)
{
 
	cout<< "�������˻�����\n";
	if (!cin.get(temp->account, INPUT_MAX))
		cin.clear();
	iclear();
	while (!test(temp))
	{
		cout<< "�˻��������ڻ��˻���Ϣ��ʧ����������";
		cout<< "���˻�����\n��ֱ�Ӱ��س����˳����룩\n";
		if (!cin.get(temp->account, INPUT_MAX))
		{cin.clear(); iclear(); return false;}
		iclear();
	}
	cout<< "���������룺 \n";
	if (!cin.get(temp->password, INPUT_MAX))
		cin.clear();
	iclear();
	while (test(temp) == 1)
	{
		cout<< "��������������������룺";
		cout<< "\n��ֱ�Ӱ��س����˳����룩\n";
		if (!cin.get(temp->password, INPUT_MAX))
		{cin.clear(); iclear(); return false;}
		cin.clear();
		iclear();
	}
	return true;
}


short test(user* temp)
{
	ifstream fin;
	fin.open(file_name(temp));
	if (!fin.is_open())
		return 0;
	string right;
	getline(fin, right);
	if (right == ""||right == "���˻���ע��")
		return 0;
	fin.close();
	fin.open(temp->account);
	if (!getline(fin, right))
		return 0;
	if (right != alg[get_alg(get_act_id(temp))](temp->password))
		return 1;
	fin.close();
	return 2;
}


bool new_actinput(user* temp)
{
P :	cin.get(temp->account, INPUT_MAX);
	while (!cin||cin.get() != '\n')
	{
		cin.clear();
		iclear();
		cout<< "�������򳬹��޶�λ�������������룺";
		cout<< "\n(ֱ�Ӱ��س����˳�����)\n";
		if (!cin.get(temp->password, INPUT_MAX))
		{cin.clear(); iclear(); return false;}
	}
	ifstream fin;
	fin.open(file_name(temp));
	while (fin.is_open())
	{	
		string temp;
		getline(fin, temp);
		if (temp == "���˻���ע��")
			break;
		cout<< "�˻����Ѵ��ڣ����������룺\n";
		goto P;
	}
	char* a = temp->account;
	for (int n = strlen(temp->account); n > 0; --n)
	{
		if(a[n-1]=='!'||a[n-1]=='@'||a[n-1]=='#'||a[n-1]=='$'||
			a[n-1]=='%'||a[n-1]=='^'||a[n-1]=='&'||a[n-1]=='*')
		{
			cout<< "�˻������Ϸ������������룺\n";
			cout<< "���˻������ܰ��������ַ� ! @ # $ % ^ & *��\n";
			goto P;
		}
	}
	return true;
}


bool new_pasinput(user* temp)
{
	for (;;)
	{
		cout<< "(ֱ�Ӱ��س����˳�����)\n";
		if (!cin.get(temp->password, INPUT_MAX))
		{cin.clear(); iclear(); return false;}
		else if (strlen(temp->password) < 6)
		{
			cout<< "����λ�����٣����������룺\n";
            iclear();	
			continue;
		}
		else if (cin.get() != '\n')
		{
			cout<< "���볬���޶�λ�������������룺\n";
			iclear();	
			continue;
		}
		else
			break;
	}
	cout<< "��ȷ�����룺\n";
	char confirm[INPUT_MAX];
	cin.get(confirm, INPUT_MAX);
	while (strcmp(confirm, temp->password))
	{
		cin.clear();
		iclear();
		cout<< "�����������벻һ�£����������룺";
		cout<< "\n(ֱ�Ӱ��س����˳�����)\n";
		if (!cin.get(confirm, INPUT_MAX))
		{cin.clear(); iclear(); return false;}
	}
	iclear();
	return true;
}


void set_new(user* temp)
{
	ofstream fout;
	fout.open(temp->account);
	if (!fout.is_open())
	{
		cout<< "�˻�δ�����ɹ���\n\n";
		return;
	}
    int n = act_id();
	fout<< alg[get_alg(n)](temp->password);
	fout.close();
	fout.open(file_name(temp));
	if (!fout.is_open())
	{
		cout<< "�˻���Ϣδ�����ɹ���\n\n";
		return;
	}
	cout<< "�����뿪����������\n";
	string name;
	getline(cin, name);
	while (name == "")
	{
		cout<< "��������������Ϊ�գ�";
		cout<< "���������뿪����������\n";
		getline(cin, name);
	}
	cout<< "�����뱸ע��Ϣ��\n";
	string info;
	getline(cin, info);
	if (info =="")
		info = "��";
	fout<< "������" << name << endl;
	fout<< "�˻�ID��" << "#" << n << endl;
	fout<< "��ע��" << info << endl;
	cout<< "�˻������ɹ���";
	fout.close();
}


int act_id()
{
	ifstream fin;
    int num;
	fin.open("id_number.id");
	if (!fin.is_open())
		num = 0;
	else 
		fin>> num;
	++num;
	fin.close();
	ofstream fout;
	fout.open("id_number.id");
	fout<< num;
	fout.close();
	return num;
}


void show_inf(user* temp)
{
	if (!get_act_id(temp))
	{
		cout<< "�˻���Ϣ�𻵻�ʧ��";
		return;
	}
	ifstream fin;
	fin.open(file_name(temp));
	string inform;
	while (getline(fin, inform))
		cout<< inform << endl;
	cout<< endl;
	fin.close();
	return;

}


void change_inf(user* temp)
{
	int num = get_act_id(temp);
	if (!num)
	{
		cout<< "�˻���Ϣ�𻵻�ʧ��";
		return;
	}
	ofstream fout;
	fout.open(file_name(temp));
	cout<< "�������µĿ�����������\n";
	string name;
	getline(cin, name);
	while (name == "")
	{
		cout<< "��������������Ϊ�գ�";
		cout<< "�����������µĿ�����������\n";
		getline(cin, name);
	}
	cout<< "�����뱸ע��Ϣ��\n";
	string info;
	getline(cin, info);
	if (info =="")
		info = "��";
	fout<< "������" << name << endl;
	fout<< "�˻�ID��" << "#" << num << endl;
	fout<< "��ע��" << info << endl;
	fout.close();
	cout<< endl;
}


int get_act_id(user* temp)
{
	ifstream fin;
	fin.open(file_name(temp));
	fin.get();
	if (!fin.good())
		return 0;
	while (fin.get() != '#')
	{
		if (!fin)
			return 0;
	}
	int num;
	fin >> num;
	fin.close();
	if (num <= 0)
		return 0;
	return num;
}


inline void input(user* temp)
{
	for(;;)
	{
		cout<< "�������˻����� \n";
		if (!cin.get(temp->account, INPUT_MAX))
			cin.clear();
		iclear();
		ifstream fin;
		fin.open(file_name(temp));
		string a;
		getline(fin, a);
		if (a == "���˻���ע��")
		{
			cout<< "���˻���ע����";
			continue;
		}
		if (!fin.is_open())
		{
			cout<< "�˻��������ڣ�";
			continue;
		}
		else
			break;
	}
}


inline void show_id(user* temp)
{
	ifstream fin;
	fin.open("id_number.id");
	int num;
	if (fin.is_open())
	{
		fin>> num;
		cout<< "��ǰID�ļ�ID��" << num << endl;
		fin.close();
	}
	else
		cout<< "ԭID�ļ���ʧ��" << endl;
}


void administrator(user* temp)
{
	char ch;
	ofstream fout;
	do
	{
		cout<< "\n��ѡ�����Ա�";
		cout<< "\n��A���鿴�˻���Ϣ\n��B���޸��˻���Ϣ\n";
		cout<< "��C���޸�����\n��D���޸�ID�ļ�\n";
		cout<< "��E��ע���˻�\n";
		if (!cin.get(ch))
		{
			cout<< "���س������ز˵�\n";
			cin.clear();
			iclear();
			return;
		}
		if (ch == 'A'||ch == 'a')
		{
			iclear();
			input(temp);
			show_inf(temp);
		}
		else if (ch == 'B'||ch == 'b')
		{
			iclear();
			input(temp);
			fout.open(file_name(temp));
			show_id(temp);
			cout<< "\n�������µĿ�����������";
			string name;
			cin>> name;
			fout<< "������" << name << endl;
			int num = 0;
			cout<< "�������µ��˻�ID��������0ϵͳĬ�ϸ��裩";
			cin>> num;
			while (num < 0)
			{
				cout<< "ID����Ϊ������\n���������룺";
				cin.clear();
				iclear();
				cin>> num;
			}
			if (!num)
				num = act_id();
			fout<< "�˻�ID��" << "#" << num << endl;
			fout<< "��ע������Ա�޸�\n";
			fout.close();
			cout<< endl;
		}
		else if (ch == 'C'||ch == 'c')
		{
			iclear();
			input(temp);
			fout.open(temp->account);
			cout<< "�����������루20λ���ڣ���������6λ����\n";
			new_pasinput(temp);
			fout<< alg[get_alg(get_act_id(temp))](temp->password);
			fout.close();
		}
		else if (ch == 'D'||ch == 'd')
		{
			iclear();
			show_id(temp);
			fout.open("id_number.id");
			cout<< "�������µ�ID��";
			int num;
			cin>> num;
			while (num <= 0)
			{
				cout<< "ID����Ϊ������0��\n���������룺";
				cin.clear();
				iclear();
				cin>> num;
			}
			fout<< num;
			fout.close();
		}
		else if (ch == 'E'||ch == 'e')
		{
			iclear();
			input(temp);
			cout<< "�Ƿ�ȷ��ע�����˻�����Y or N��";
			cout<< "\n�����˻����е���Ϣ���޷���أ���";
			char a;
			cin>> a;
			iclear();
			if (a != 'Y'&&a != 'y')
				cout<< "\n�˻�δע����\n";
			else
			{
				fout.open(file_name(temp));
				fout<< "���˻���ע��\n";
				cout<< "\n���˻���ע����";
			}
		}
		iclear();
		cout<< "\n���س�������";
		cin.get();
	} while (ch == 'A'||ch == 'a'||ch == 'B'||ch == 'b'
		||ch == 'C'||ch == 'c'||ch == 'D'||ch == 'd'||
		ch == 'E'||ch == 'e');
	cout<< "\n�����ѷ������˵���\n\n";
}


char* Phonix(char* password)
{
	for (int i = 0, n = strlen(password); i < n; ++i, --n)
	{
		password[i] += password[n-1];
		password[n-1] *= 2;
	}
	return password;
}


char* Supheria(char* password)
{
	for (int i = 0, n = strlen(password); i < n; ++i, --n)
	{
		password[n-1] += password[i];
		password[i] *= 2;
	}
	return password;
}
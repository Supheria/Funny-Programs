// AddYourAccount.cpp : 定义控制台应用程序的入口点。
/*BUG记录：1.如果id文件丢失，非管理员新建账户时有权限新建一个id为#1的id文件，这会导致该新建账户id与现有账户冲突
           2.用户不可以随意变更开户人姓名，除非获得管理员权限*/

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
	cout<< "请选择您所需业务: \n\n";
	cout<< "（A）查看已有账户信息。\n";
	cout<< "（B）新建账户。\n";
	cout<< "（C）更新已有账户信息。\n";
	cout<< "（D）修改已有账户密码。\n";
	cout<< "（E）注销已有账户。\n";
	cout<< "按其他键退出程序。\n";
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
	cout<< "按回车键返回菜单\n";
	cin.get();
}


void B(user* temp)
{
	cout<< "请输入账户名（" << INPUT_MAX - 1 << "位以内）：\n";
	if (!new_actinput(temp))
	{
		cout<< "创建账户失败！";
		cout<< "按回车键返回菜单\n";
		cin.get();
		return;
	}
	cout<< "请输入密码（" << INPUT_MAX - 1 << "位以内，但不少于6位）：\n";
	if (new_pasinput(temp))
		set_new(temp);
	else
		cout<< "创建账户失败！";
	cout<< "按回车键返回菜单\n";
	cin.get();
}


void C(user* temp)
{
	if (old_input(temp))
	{
		cout<< endl;
		change_inf(temp);
		cout<< "账户信息更改成功！";
	}
	else
		cout<< "账户信息更新失败！";
	cout<< "按回车键返回菜单\n";
	cin.get();
}


void D(user* temp)
{
	if (old_input(temp))
	{
		if (!get_act_id(temp))
		{
		cout<< "账户信息损坏或丢失！密码更新失败！";
		cout<< "\n按回车键返回菜单\n";
		cin.get();
		return;
		}
		cout<< "请输入新密码（20位以内，但不少于6位）：\n";
		if (new_pasinput(temp))
		{
			ofstream fout;
			fout.open(temp->account);
			fout<< alg[get_alg(get_act_id(temp))](temp->password);
			fout.close();
			cin.get();
			cout<< "\n密码更新成功！";
		}
		else
			cout<< "\n密码更新失败！";
	}
	cout<< "按回车键返回菜单\n";
	cin.get();
}


void E(user* temp)
{
	if (old_input(temp))
	{
		cout<< "是否确认注销该账户？（Y or N）";
		cout<< "\n（您该账户所有的信息将无法挽回！）";
		char a;
		cin>> a;
		iclear();
		if (a != 'Y'&&a != 'y')
		{
			cout<< "\n账户未注销！";
			cout<< "按回车键返回菜单\n";
			cin.get();
			return;
		}
		ofstream fout;
		fout.open(file_name(temp));
		fout<< "该账户已注销\n";
		cout<< "\n该账户已注销！";
	}
	cout<< "按回车键返回菜单\n";
	cin.get();
}


bool old_input(user* temp)
{
 
	cout<< "请输入账户名：\n";
	if (!cin.get(temp->account, INPUT_MAX))
		cin.clear();
	iclear();
	while (!test(temp))
	{
		cout<< "账户名不存在或账户信息丢失！请重新输";
		cout<< "入账户名：\n（直接按回车键退出输入）\n";
		if (!cin.get(temp->account, INPUT_MAX))
		{cin.clear(); iclear(); return false;}
		iclear();
	}
	cout<< "请输入密码： \n";
	if (!cin.get(temp->password, INPUT_MAX))
		cin.clear();
	iclear();
	while (test(temp) == 1)
	{
		cout<< "密码错误！请重新输入密码：";
		cout<< "\n（直接按回车键退出输入）\n";
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
	if (right == ""||right == "该账户已注销")
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
		cout<< "输入错误或超过限定位数！请重新输入：";
		cout<< "\n(直接按回车键退出输入)\n";
		if (!cin.get(temp->password, INPUT_MAX))
		{cin.clear(); iclear(); return false;}
	}
	ifstream fin;
	fin.open(file_name(temp));
	while (fin.is_open())
	{	
		string temp;
		getline(fin, temp);
		if (temp == "该账户已注销")
			break;
		cout<< "账户名已存在！请重新输入：\n";
		goto P;
	}
	char* a = temp->account;
	for (int n = strlen(temp->account); n > 0; --n)
	{
		if(a[n-1]=='!'||a[n-1]=='@'||a[n-1]=='#'||a[n-1]=='$'||
			a[n-1]=='%'||a[n-1]=='^'||a[n-1]=='&'||a[n-1]=='*')
		{
			cout<< "账户名不合法！请重新输入：\n";
			cout<< "（账户名不能包含特殊字符 ! @ # $ % ^ & *）\n";
			goto P;
		}
	}
	return true;
}


bool new_pasinput(user* temp)
{
	for (;;)
	{
		cout<< "(直接按回车键退出输入)\n";
		if (!cin.get(temp->password, INPUT_MAX))
		{cin.clear(); iclear(); return false;}
		else if (strlen(temp->password) < 6)
		{
			cout<< "输入位数过少！请重新输入：\n";
            iclear();	
			continue;
		}
		else if (cin.get() != '\n')
		{
			cout<< "输入超过限定位数！请重新输入：\n";
			iclear();	
			continue;
		}
		else
			break;
	}
	cout<< "请确认密码：\n";
	char confirm[INPUT_MAX];
	cin.get(confirm, INPUT_MAX);
	while (strcmp(confirm, temp->password))
	{
		cin.clear();
		iclear();
		cout<< "两次输入密码不一致！请重新输入：";
		cout<< "\n(直接按回车键退出输入)\n";
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
		cout<< "账户未创建成功！\n\n";
		return;
	}
    int n = act_id();
	fout<< alg[get_alg(n)](temp->password);
	fout.close();
	fout.open(file_name(temp));
	if (!fout.is_open())
	{
		cout<< "账户信息未建立成功！\n\n";
		return;
	}
	cout<< "请输入开户人姓名：\n";
	string name;
	getline(cin, name);
	while (name == "")
	{
		cout<< "开户人姓名不能为空！";
		cout<< "请重新输入开户人姓名：\n";
		getline(cin, name);
	}
	cout<< "请输入备注信息：\n";
	string info;
	getline(cin, info);
	if (info =="")
		info = "无";
	fout<< "姓名：" << name << endl;
	fout<< "账户ID：" << "#" << n << endl;
	fout<< "备注：" << info << endl;
	cout<< "账户创建成功！";
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
		cout<< "账户信息损坏或丢失！";
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
		cout<< "账户信息损坏或丢失！";
		return;
	}
	ofstream fout;
	fout.open(file_name(temp));
	cout<< "请输入新的开户人姓名：\n";
	string name;
	getline(cin, name);
	while (name == "")
	{
		cout<< "开户人姓名不能为空！";
		cout<< "请重新输入新的开户人姓名：\n";
		getline(cin, name);
	}
	cout<< "请输入备注信息：\n";
	string info;
	getline(cin, info);
	if (info =="")
		info = "无";
	fout<< "姓名：" << name << endl;
	fout<< "账户ID：" << "#" << num << endl;
	fout<< "备注：" << info << endl;
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
		cout<< "请输入账户名： \n";
		if (!cin.get(temp->account, INPUT_MAX))
			cin.clear();
		iclear();
		ifstream fin;
		fin.open(file_name(temp));
		string a;
		getline(fin, a);
		if (a == "该账户已注销")
		{
			cout<< "该账户已注销！";
			continue;
		}
		if (!fin.is_open())
		{
			cout<< "账户名不存在！";
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
		cout<< "当前ID文件ID：" << num << endl;
		fin.close();
	}
	else
		cout<< "原ID文件丢失！" << endl;
}


void administrator(user* temp)
{
	char ch;
	ofstream fout;
	do
	{
		cout<< "\n请选择管理员项：";
		cout<< "\n（A）查看账户信息\n（B）修改账户信息\n";
		cout<< "（C）修改密码\n（D）修改ID文件\n";
		cout<< "（E）注销账户\n";
		if (!cin.get(ch))
		{
			cout<< "按回车键返回菜单\n";
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
			cout<< "\n请输入新的开户人姓名：";
			string name;
			cin>> name;
			fout<< "姓名：" << name << endl;
			int num = 0;
			cout<< "请输入新的账户ID：（输入0系统默认赋予）";
			cin>> num;
			while (num < 0)
			{
				cout<< "ID不能为负数！\n请重新输入：";
				cin.clear();
				iclear();
				cin>> num;
			}
			if (!num)
				num = act_id();
			fout<< "账户ID：" << "#" << num << endl;
			fout<< "备注：管理员修改\n";
			fout.close();
			cout<< endl;
		}
		else if (ch == 'C'||ch == 'c')
		{
			iclear();
			input(temp);
			fout.open(temp->account);
			cout<< "请输入新密码（20位以内，但不少于6位）：\n";
			new_pasinput(temp);
			fout<< alg[get_alg(get_act_id(temp))](temp->password);
			fout.close();
		}
		else if (ch == 'D'||ch == 'd')
		{
			iclear();
			show_id(temp);
			fout.open("id_number.id");
			cout<< "请输入新的ID：";
			int num;
			cin>> num;
			while (num <= 0)
			{
				cout<< "ID不能为负数或0！\n请重新输入：";
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
			cout<< "是否确认注销该账户？（Y or N）";
			cout<< "\n（该账户所有的信息将无法挽回！）";
			char a;
			cin>> a;
			iclear();
			if (a != 'Y'&&a != 'y')
				cout<< "\n账户未注销！\n";
			else
			{
				fout.open(file_name(temp));
				fout<< "该账户已注销\n";
				cout<< "\n该账户已注销！";
			}
		}
		iclear();
		cout<< "\n按回车键继续";
		cin.get();
	} while (ch == 'A'||ch == 'a'||ch == 'B'||ch == 'b'
		||ch == 'C'||ch == 'c'||ch == 'D'||ch == 'd'||
		ch == 'E'||ch == 'e');
	cout<< "\n（您已返回主菜单）\n\n";
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
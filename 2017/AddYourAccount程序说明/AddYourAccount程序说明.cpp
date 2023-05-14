// AddYourAccount程序说明.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
// 以下为程序所要使用的常量及结构声明
const int INPUT_MAX = 21;// 最多输入20位，字符串包括‘\0’
struct user
{
	char account[INPUT_MAX];// 账户名输入存储
	char password[INPUT_MAX];// 密码输入存储
	char info_name[INPUT_MAX+5];// 账户信息文件名
};
// 以下为内联函数原型及定义
inline void iclear(){while (cin.get() != '\n') ;}// 清除多余输入
inline string file_name(user* temp)// 命名信息文件名称
{// 返回string和返回char*都是返回字符串地址
	strcpy(temp->info_name, temp->account);
	// char字符串复制需要strcpy()函数（后复制于前）
	strcat(temp->info_name, "_info");
	// char字符串链接需要strcat()函数（后连接于前）
	return temp->info_name;
}
inline bool get_alg(int n)// 密码加密算法的选择
{                         //（ID为奇数选择Phonix，否则选Supheria）
	if (n == 1) return 0;// 1%2 = 0
	if ((n%2) != 0) return 0;
	return 1;
}
// 以下为普通函数原型
bool menu(user* temp);// 显示菜单
void A(user* temp);// 选项A
void B(user* temp);// 选项B
void C(user* temp);// 选项C
void D(user* temp);// 选项D
bool old_input(user* temp);// 已有账户账户名及密码输入
short test(user* temp);// 已有账户账户名及密码验证
void new_actinput(user* temp);// 新建账户账户名输入
bool new_pasinput(user* temp);// 新建账户密码输入
void set_new(user* temp);// 新建账户及账户信息
int act_id();// 获取主系统赋予新建账户的ID
void show_inf(user* temp);// 显示已有账户信息
void change_inf(user* temp);// 更改已有账户信息
int get_act_id(user* temp);// 获取已有账户的ID（防止ID在更改账户信息fout时被丢失）
void administrator(user* temp);// 系统管理员选项
// 以下为密码加密算法函数类型定义及函数名和函数指针数组声明
typedef char* form(char* password);// 函数名类型定义
typedef char* (*sec)(char* password);// 函数指针类型定义
form Phonix, Supheria;// 声明两个不同的算法函数
sec alg[2] = {Phonix, Supheria};// 声明一个指向两种算法函数的指针数组

// 以下为主程序及函数定义
// 注意，结构user类型变量的传递（或调用函数接口），都是通过指针传递temp的地址
int main()
{
F : user* temp = new user;// 每轮循环开辟一次新的内存空间，旨在保护账户信息
	while (menu(temp))    // 缺点是用户需要每一轮都要输入一次账户名和密码
	{
		delete temp;// menu()调用的选项函数结束，释放temp
		goto F;// 注意：在while中开辟新的user不可行，
	}          //       因为while内部指针对外部不可见！
	return 0;// 循环结束，程序退出
}


bool menu(user* temp)// 显示菜单选项
{// 使用字母而不是数字是为了让char能将数字输入转化为字符编码，
 // 而不会因为使用整型不能存储意外输入的字母而造成输入错误！
	cout<< "请选择您所需业务: \n\n";
	cout<< "（A）查看已有账户信息。\n";
	cout<< "（B）新建账户。\n";
	cout<< "（C）更新已有账户信息。\n";
	cout<< "（D）修改已有账户密码。\n";
	cout<< "按其他键退出程序。\n";
	char choice[INPUT_MAX];
	cin.get(choice, INPUT_MAX);// 输入选项或直接输入管理员密码
	if (!strcmp(choice, "299PSupheriax406"))// 管理员密码判断
	{
		iclear();// 清除换行符
		administrator(temp);
		return true;// 继续main()下一周期循环
	}
	cin.clear();
	iclear();
	cout<< endl;
	switch (choice[0])
	{
	case 'A' :
	case 'a' : A(temp);// 调用选项A函数，余下同理
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
	default :// 输入其他字符，或输入管理员密码错误，将直接结束main()循环
		return false;
	}
}


void A(user* temp)
{
	if (old_input(temp))
	{// 已有账户名及密码输入成功会返回true，否则返回false结束函数
		cout<< endl;// 显示内容前空一行
		show_inf(temp);// 如果if为true，则调用显示账户信息函数
	}
	cout<< "按回车键返回菜单\n";
	cin.get();// 拾取一个回车
}


void B(user* temp)
{
	cout<< "请输入账户名（20位以内）：\n";
	new_actinput(temp);// 调用新建账户名输入函数
	cout<< "请输入密码（20位以内，但不少于6位）：\n";
	if (new_pasinput(temp))
	{// 新建账户名密码输入确认成功返回true，否则返回false
		set_new(temp);// 如果if为true，调用新建账户信息函数
		cin.get();
	}
	else// 如果if为false，显示提示消息，且不建立账户文件
		cout<< "创建账户失败！";
	cout<< "按回车键返回菜单\n";
	cin.get();
}


void C(user* temp)
{
	if (old_input(temp))
	{
		cout<< endl;
		change_inf(temp);// 如果if为true，则调用修改账户信息函数
	}
	else
		cout<< "账户信息更新失败！";
	cout<< "按回车键返回菜单\n";
	cin.get();
}


void D(user* temp)
{
	if (old_input(temp))
	{// 此时输入的账户名会被temp->account保存
		cout<< "请输入新密码（20位以内，但不少于6位）：\n";
		if (new_pasinput(temp))
		{
			ofstream fout;
			fout.open(temp->account);// 打开以此用户名命名的密码文件
			fout<< alg[get_alg(get_act_id(temp))](temp->password);
			// 在此文件中输出通过加密算法函数加密后的密码
/* 关于此处算法函数调用的说明：
该函数基础调用结构为alg[i]()，其中alg[i]是指向alg指针数组的第i+1个
函数名（Phonix或Supheria），而i则是由get_alg()函数的返回值所决定；
get_alg()判断的参数则是由被调用的get_act_id()返回的账户的ID所决定。
换句话说就是由账户ID决定要使用哪个的算法函数对输出文本密码进行加密*/
			fout.close();// 关闭账户名文件
			cin.get();
			cout<< "\n密码更新成功！";
		}
		else
			cout<< "\n密码更新失败！";
	}
	cout<< "按回车键返回菜单\n";
	cin.get();
}


bool old_input(user* temp)
{
 
	cout<< "请输入账户名： \n";
	if (!cin.get(temp->account, INPUT_MAX))
		// 直接用cin对象来做判断：
		// 如果直接键入一个回车，那么cin返回一个false，
		// 同时设立一个失效位，断开以后的输入，需要用
		// cin.clear()来清除失效位
		cin.clear();
	iclear();// 清除保留在输入候选区的多余输入
	while (!test(temp))
	{// 如果账户名不存在或密码信息丢失，test()函数返回一个0
		cout<< "账户名不存在或账户信息丢失！\n";
		cout<< "请重新输入账户名：";
		cout<< "（直接按回车键退出输入）\n";
		if (!cin.get(temp->account, INPUT_MAX))
			// 因为cin.get()会保留回车，所以输入
			// 回车后，需要用iclear()清除保留的回车
		{cin.clear(); iclear(); return false;}
		iclear();
	}
	cout<< "请输入密码： \n";
	if (!cin.get(temp->password, INPUT_MAX))
		cin.clear();
	iclear();
	while (test(temp) == 1)
	{
		cout<< "密码错误！\n请重新输入密码：";
		cout<< "（直接按回车键退出输入）\n";
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
	fin.open(temp->account);
	if (!fin.is_open())// 密码文件打开返回ture，否则返回false
		return 0;
	string right;
	if (!getline(fin, right))
		// fin和cin同理，读入成功返回true，读入为空或失败返回false
		// string对象不能调用get()
		return 0;
	if (right != alg[get_alg(get_act_id(temp))](temp->password))
		// 将输入的密码用算法函数转化后与密码文件比对
		return 1;
	fin.close();
	return 2;
}


void new_actinput(user* temp)
{
P :	while (!cin.get(temp->account, INPUT_MAX)||cin.get() != '\n')
	{
			cout<< "输入错误或超过限定位数！请重新输入：\n";
			cin.clear();
			iclear();
	}
	ifstream fin;
	fin.open(temp->account);
	if (fin.is_open())
	{// 如果成功打开了已有的账户名密码文件，就会返回true	
		cout<< "账户名已存在！请重新输入：\n";
		goto P;
	}
	char* a = temp->account;// char*指针指向字符串
	for (int n = strlen(temp->account); n > 0;)
	{// 利用循环逐字检查账户名是否包含非法字符
		if(a[n-1]=='!'||a[n-1]=='@'||a[n-1]=='#'||a[n-1]=='$'||
			a[n-1]=='%'||a[n-1]=='^'||a[n-1]=='&'||a[n-1]=='*')
		{
			cout<< "账户名不合法！请重新输入：\n";
			cout<< "（账户名不能包含特殊字符 ! @ # $ % ^ & *）\n";
			goto P;
		}
		if(--n == 0)// 全部检查完时，结束循环
			break;
	}
}


bool new_pasinput(user* temp)
{
	cin.get(temp->password, INPUT_MAX);
	while (strlen(temp->password) < 6)
	{
		cin.clear();
		cout<< "输入位数过少，请重新输入！\n";
		cin.get(temp->password, INPUT_MAX);
	}
	while (cin.get() != '\n')
	{
			cout<< "输入超过限定位数！请重新输入：\n";
			iclear();
			cin.get(temp->password, INPUT_MAX);
	}
	cout<< "请确认密码：\n";
	char confirm[INPUT_MAX];
	cin.get(confirm, INPUT_MAX);
	while (strcmp(confirm, temp->password))
	{// 比较两个char*或C风格字符串时只能用strcmp()函数，
	 //而不能用比较运算符！两者相同时会返回0！
		cin.clear();
		iclear();
		cout<< "两次输入密码不一致！";
		cout<< "\n请重新输入：";
		cout<< "(直接按回车键退出输入)\n";
		if (!cin.get(confirm, INPUT_MAX))
		{cin.clear(); iclear(); return false;}
	}
	return true;
}


void set_new(user* temp)
{
	ofstream fout;
	fout.open(temp->account);
	if (!fout.is_open())
	{// 创建密码文件成功返回true，否则返回false
		cout<< "账户未创建成功！\n\n";
		return;
	}
    int n = act_id();
	fout<< alg[get_alg(n)](temp->password);
	// 算法加密密码后然后输出（这里有些不同的是，
	// 因为是新建账户，所以账户ID由id_number
	// 文件赋予，因此调用到act_id()函数）
	fout.close();
	fout.open(file_name(temp));
	if (!fout.is_open())
	{// 创建账户信息文件成功返回true，否则返回false
		cout<< "账户信息未建立成功！\n\n";
		return;
	}
	cout<< "请输入开户人姓名：";
	string name;
	cin>> name;
	fout<< "姓名：" << name << endl;
	fout<< "账户ID：" << "#" << n;// #为ID标识符
	cout<< "账户创建成功！\n\n";
	fout.close();
}


int act_id()
{
	ifstream fin;
    int num;
	fin.open("id_number");
	if (!fin.is_open())
		num = 0;// ID文件默认ID为0
	fin>> num;
	++num;// 每创建一个账户，ID加1
	fin.close();
	ofstream fout;
	fout.open("id_number");
	fout<< num;// 加1后的ID输出到ID文件
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
		cout<< "账户信息丢失或损坏！";
		return;
	}
	ofstream fout;
	fout.open(file_name(temp));
	cout<< "请输入新的开户人姓名：";
	string name;
	cin>> name;
	fout<< "姓名：" << name << endl;
	fout<< "账户ID：" << "#" << num;
	fout.close();
	cout<< endl;
	cout<< "账户信息更改成功！";
	iclear();
}


int get_act_id(user* temp)
{// 因为规定ID不能为负数或0，所以正常会返回一个正整数
	ifstream fin;
	fin.open(file_name(temp));
	fin.get();
	if (!fin.good())
		return 0;
	while (fin.get() != '#')
		// 通过查询账户信息文件里的#符号来确定ID
		// 一个缺陷是，如果#缺失了，那么程序将死机
		;
	int num;
	fin >> num;
	fin.close();
	if (num <= 0)
		return 0;
	return num;
}

// 此函数验证管理员输入的账户名
inline void input(user* temp)
{
	for(;;)
	{
		cout<< "请输入账户名： \n";
		if (!cin.get(temp->account, INPUT_MAX))
			cin.clear();
		iclear();
		ifstream fin;
		fin.open(temp->account);
		if (!fin.is_open())
		{// 输入账户名不存在就返回循环
			cout<< "账户名不存在！";
			continue;
		}
		else// 账户名正确就结束循环
			break;
	}
}

// 基本上综合了以上函数的功能，且省略了输入密码的要求
void administrator(user* temp)
{
	char ch;
	ofstream fout;
	cout<< "\n请选择管理员项：";
	cout<< "\n（A）查看账户信息\n（B）查看ID文件\n（C）";
	cout<< "修改账户信息\n（D）修改密码\n（E）修改ID文件\n";
	cin.get(ch);
	if (ch == 'A'||ch == 'a')
	{
		iclear();// 清除换行符
		input(temp);
		show_inf(temp);
	}
	else if (ch == 'B'||ch == 'b')
	{
		iclear();
		ifstream fin;
		fin.open("id_number");
		int num;
		if (fin.is_open())
		{
			fin>> num;
			cout<< "当前ID文件ID：" << num << endl;
			fin.close();
		}
		else
			cout<< "原ID文件丢失！";
	}
	else if (ch == 'C'||ch == 'c')
	{
		iclear();
		input(temp);
		fout.open(file_name(temp));
		cout<< "\n请输入新的开户人姓名：";
		string name;
		cin>> name;
		fout<< "姓名：" << name << endl;
		int num;
		cout<< "请输入新的账户ID：";
		cin>> num;
		while (num <= 0)
		{
			cout<< "ID不能为负数或0！\n请重新输入：";
			cin.clear();
			iclear();
			cin>> num;
		}
		fout<< "账户ID：" << "#" << num;
		fout.close();
		cout<< endl;
	}
	else if (ch == 'D'||ch == 'd')
	{
		iclear();
		input(temp);
		fout.open(temp->account);
		cout<< "请输入新密码（20位以内，但不少于6位）：\n";
		new_pasinput(temp);
		fout<< alg[get_alg(get_act_id(temp))](temp->password);
		fout.close();
	}
	else if (ch == 'E'||ch == 'e')
	{
		iclear();
		fout.open("id_number");
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
	cin.clear();
	iclear();
	cout<< "按回车键返回菜单\n";
	cin.get();
}

// 一下两个为密码算法函数（旨在即使看到了密码文件也不能知道密码）
char* Phonix(char* password)
{
	for (int i = 0, n = strlen(password); i < n; ++i, --n)
	{
		password[i] += password[n-1];
		// 方法说明：头字符编码加上尾字符编码得到新的头字符，
		// 位置向内递增，直到到达中间字符
		password[n-1] *= 2;// 尾字符编码乘2得到新的尾字符
	}// 破解方法：后一半的字符编码除以2，
	// 再用前一半字符编码减对应的后一半的字符（Supehria()相反）
	return password;
}


char* Supheria(char* password)
{
	for (int i = 0, n = strlen(password); i < n; ++i, --n)
	{
		password[n-1] += password[i];// 和Phonix()刚好相反
		password[i] *= 2;
	}
	return password;
}
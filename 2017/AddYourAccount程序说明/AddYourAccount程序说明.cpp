// AddYourAccount����˵��.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
// ����Ϊ������Ҫʹ�õĳ������ṹ����
const int INPUT_MAX = 21;// �������20λ���ַ���������\0��
struct user
{
	char account[INPUT_MAX];// �˻�������洢
	char password[INPUT_MAX];// ��������洢
	char info_name[INPUT_MAX+5];// �˻���Ϣ�ļ���
};
// ����Ϊ��������ԭ�ͼ�����
inline void iclear(){while (cin.get() != '\n') ;}// �����������
inline string file_name(user* temp)// ������Ϣ�ļ�����
{// ����string�ͷ���char*���Ƿ����ַ�����ַ
	strcpy(temp->info_name, temp->account);
	// char�ַ���������Ҫstrcpy()������������ǰ��
	strcat(temp->info_name, "_info");
	// char�ַ���������Ҫstrcat()��������������ǰ��
	return temp->info_name;
}
inline bool get_alg(int n)// ��������㷨��ѡ��
{                         //��IDΪ����ѡ��Phonix������ѡSupheria��
	if (n == 1) return 0;// 1%2 = 0
	if ((n%2) != 0) return 0;
	return 1;
}
// ����Ϊ��ͨ����ԭ��
bool menu(user* temp);// ��ʾ�˵�
void A(user* temp);// ѡ��A
void B(user* temp);// ѡ��B
void C(user* temp);// ѡ��C
void D(user* temp);// ѡ��D
bool old_input(user* temp);// �����˻��˻�������������
short test(user* temp);// �����˻��˻�����������֤
void new_actinput(user* temp);// �½��˻��˻�������
bool new_pasinput(user* temp);// �½��˻���������
void set_new(user* temp);// �½��˻����˻���Ϣ
int act_id();// ��ȡ��ϵͳ�����½��˻���ID
void show_inf(user* temp);// ��ʾ�����˻���Ϣ
void change_inf(user* temp);// ���������˻���Ϣ
int get_act_id(user* temp);// ��ȡ�����˻���ID����ֹID�ڸ����˻���Ϣfoutʱ����ʧ��
void administrator(user* temp);// ϵͳ����Աѡ��
// ����Ϊ��������㷨�������Ͷ��弰�������ͺ���ָ����������
typedef char* form(char* password);// ���������Ͷ���
typedef char* (*sec)(char* password);// ����ָ�����Ͷ���
form Phonix, Supheria;// ����������ͬ���㷨����
sec alg[2] = {Phonix, Supheria};// ����һ��ָ�������㷨������ָ������

// ����Ϊ�����򼰺�������
// ע�⣬�ṹuser���ͱ����Ĵ��ݣ�����ú����ӿڣ�������ͨ��ָ�봫��temp�ĵ�ַ
int main()
{
F : user* temp = new user;// ÿ��ѭ������һ���µ��ڴ�ռ䣬ּ�ڱ����˻���Ϣ
	while (menu(temp))    // ȱ�����û���Ҫÿһ�ֶ�Ҫ����һ���˻���������
	{
		delete temp;// menu()���õ�ѡ����������ͷ�temp
		goto F;// ע�⣺��while�п����µ�user�����У�
	}          //       ��Ϊwhile�ڲ�ָ����ⲿ���ɼ���
	return 0;// ѭ�������������˳�
}


bool menu(user* temp)// ��ʾ�˵�ѡ��
{// ʹ����ĸ������������Ϊ����char�ܽ���������ת��Ϊ�ַ����룬
 // ��������Ϊʹ�����Ͳ��ܴ洢�����������ĸ������������
	cout<< "��ѡ��������ҵ��: \n\n";
	cout<< "��A���鿴�����˻���Ϣ��\n";
	cout<< "��B���½��˻���\n";
	cout<< "��C�����������˻���Ϣ��\n";
	cout<< "��D���޸������˻����롣\n";
	cout<< "���������˳�����\n";
	char choice[INPUT_MAX];
	cin.get(choice, INPUT_MAX);// ����ѡ���ֱ���������Ա����
	if (!strcmp(choice, "299PSupheriax406"))// ����Ա�����ж�
	{
		iclear();// ������з�
		administrator(temp);
		return true;// ����main()��һ����ѭ��
	}
	cin.clear();
	iclear();
	cout<< endl;
	switch (choice[0])
	{
	case 'A' :
	case 'a' : A(temp);// ����ѡ��A����������ͬ��
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
	default :// ���������ַ������������Ա������󣬽�ֱ�ӽ���main()ѭ��
		return false;
	}
}


void A(user* temp)
{
	if (old_input(temp))
	{// �����˻�������������ɹ��᷵��true�����򷵻�false��������
		cout<< endl;// ��ʾ����ǰ��һ��
		show_inf(temp);// ���ifΪtrue���������ʾ�˻���Ϣ����
	}
	cout<< "���س������ز˵�\n";
	cin.get();// ʰȡһ���س�
}


void B(user* temp)
{
	cout<< "�������˻�����20λ���ڣ���\n";
	new_actinput(temp);// �����½��˻������뺯��
	cout<< "���������루20λ���ڣ���������6λ����\n";
	if (new_pasinput(temp))
	{// �½��˻�����������ȷ�ϳɹ�����true�����򷵻�false
		set_new(temp);// ���ifΪtrue�������½��˻���Ϣ����
		cin.get();
	}
	else// ���ifΪfalse����ʾ��ʾ��Ϣ���Ҳ������˻��ļ�
		cout<< "�����˻�ʧ�ܣ�";
	cout<< "���س������ز˵�\n";
	cin.get();
}


void C(user* temp)
{
	if (old_input(temp))
	{
		cout<< endl;
		change_inf(temp);// ���ifΪtrue��������޸��˻���Ϣ����
	}
	else
		cout<< "�˻���Ϣ����ʧ�ܣ�";
	cout<< "���س������ز˵�\n";
	cin.get();
}


void D(user* temp)
{
	if (old_input(temp))
	{// ��ʱ������˻����ᱻtemp->account����
		cout<< "�����������루20λ���ڣ���������6λ����\n";
		if (new_pasinput(temp))
		{
			ofstream fout;
			fout.open(temp->account);// ���Դ��û��������������ļ�
			fout<< alg[get_alg(get_act_id(temp))](temp->password);
			// �ڴ��ļ������ͨ�������㷨�������ܺ������
/* ���ڴ˴��㷨�������õ�˵����
�ú����������ýṹΪalg[i]()������alg[i]��ָ��algָ������ĵ�i+1��
��������Phonix��Supheria������i������get_alg()�����ķ���ֵ��������
get_alg()�жϵĲ��������ɱ����õ�get_act_id()���ص��˻���ID��������
���仰˵�������˻�ID����Ҫʹ���ĸ����㷨����������ı�������м���*/
			fout.close();// �ر��˻����ļ�
			cin.get();
			cout<< "\n������³ɹ���";
		}
		else
			cout<< "\n�������ʧ�ܣ�";
	}
	cout<< "���س������ز˵�\n";
	cin.get();
}


bool old_input(user* temp)
{
 
	cout<< "�������˻����� \n";
	if (!cin.get(temp->account, INPUT_MAX))
		// ֱ����cin���������жϣ�
		// ���ֱ�Ӽ���һ���س�����ôcin����һ��false��
		// ͬʱ����һ��ʧЧλ���Ͽ��Ժ�����룬��Ҫ��
		// cin.clear()�����ʧЧλ
		cin.clear();
	iclear();// ��������������ѡ���Ķ�������
	while (!test(temp))
	{// ����˻��������ڻ�������Ϣ��ʧ��test()��������һ��0
		cout<< "�˻��������ڻ��˻���Ϣ��ʧ��\n";
		cout<< "�����������˻�����";
		cout<< "��ֱ�Ӱ��س����˳����룩\n";
		if (!cin.get(temp->account, INPUT_MAX))
			// ��Ϊcin.get()�ᱣ���س�����������
			// �س�����Ҫ��iclear()��������Ļس�
		{cin.clear(); iclear(); return false;}
		iclear();
	}
	cout<< "���������룺 \n";
	if (!cin.get(temp->password, INPUT_MAX))
		cin.clear();
	iclear();
	while (test(temp) == 1)
	{
		cout<< "�������\n�������������룺";
		cout<< "��ֱ�Ӱ��س����˳����룩\n";
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
	if (!fin.is_open())// �����ļ��򿪷���ture�����򷵻�false
		return 0;
	string right;
	if (!getline(fin, right))
		// fin��cinͬ������ɹ�����true������Ϊ�ջ�ʧ�ܷ���false
		// string�����ܵ���get()
		return 0;
	if (right != alg[get_alg(get_act_id(temp))](temp->password))
		// ��������������㷨����ת�����������ļ��ȶ�
		return 1;
	fin.close();
	return 2;
}


void new_actinput(user* temp)
{
P :	while (!cin.get(temp->account, INPUT_MAX)||cin.get() != '\n')
	{
			cout<< "�������򳬹��޶�λ�������������룺\n";
			cin.clear();
			iclear();
	}
	ifstream fin;
	fin.open(temp->account);
	if (fin.is_open())
	{// ����ɹ��������е��˻��������ļ����ͻ᷵��true	
		cout<< "�˻����Ѵ��ڣ����������룺\n";
		goto P;
	}
	char* a = temp->account;// char*ָ��ָ���ַ���
	for (int n = strlen(temp->account); n > 0;)
	{// ����ѭ�����ּ���˻����Ƿ�����Ƿ��ַ�
		if(a[n-1]=='!'||a[n-1]=='@'||a[n-1]=='#'||a[n-1]=='$'||
			a[n-1]=='%'||a[n-1]=='^'||a[n-1]=='&'||a[n-1]=='*')
		{
			cout<< "�˻������Ϸ������������룺\n";
			cout<< "���˻������ܰ��������ַ� ! @ # $ % ^ & *��\n";
			goto P;
		}
		if(--n == 0)// ȫ�������ʱ������ѭ��
			break;
	}
}


bool new_pasinput(user* temp)
{
	cin.get(temp->password, INPUT_MAX);
	while (strlen(temp->password) < 6)
	{
		cin.clear();
		cout<< "����λ�����٣����������룡\n";
		cin.get(temp->password, INPUT_MAX);
	}
	while (cin.get() != '\n')
	{
			cout<< "���볬���޶�λ�������������룺\n";
			iclear();
			cin.get(temp->password, INPUT_MAX);
	}
	cout<< "��ȷ�����룺\n";
	char confirm[INPUT_MAX];
	cin.get(confirm, INPUT_MAX);
	while (strcmp(confirm, temp->password))
	{// �Ƚ�����char*��C����ַ���ʱֻ����strcmp()������
	 //�������ñȽ��������������ͬʱ�᷵��0��
		cin.clear();
		iclear();
		cout<< "�����������벻һ�£�";
		cout<< "\n���������룺";
		cout<< "(ֱ�Ӱ��س����˳�����)\n";
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
	{// ���������ļ��ɹ�����true�����򷵻�false
		cout<< "�˻�δ�����ɹ���\n\n";
		return;
	}
    int n = act_id();
	fout<< alg[get_alg(n)](temp->password);
	// �㷨���������Ȼ�������������Щ��ͬ���ǣ�
	// ��Ϊ���½��˻��������˻�ID��id_number
	// �ļ����裬��˵��õ�act_id()������
	fout.close();
	fout.open(file_name(temp));
	if (!fout.is_open())
	{// �����˻���Ϣ�ļ��ɹ�����true�����򷵻�false
		cout<< "�˻���Ϣδ�����ɹ���\n\n";
		return;
	}
	cout<< "�����뿪����������";
	string name;
	cin>> name;
	fout<< "������" << name << endl;
	fout<< "�˻�ID��" << "#" << n;// #ΪID��ʶ��
	cout<< "�˻������ɹ���\n\n";
	fout.close();
}


int act_id()
{
	ifstream fin;
    int num;
	fin.open("id_number");
	if (!fin.is_open())
		num = 0;// ID�ļ�Ĭ��IDΪ0
	fin>> num;
	++num;// ÿ����һ���˻���ID��1
	fin.close();
	ofstream fout;
	fout.open("id_number");
	fout<< num;// ��1���ID�����ID�ļ�
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
		cout<< "�˻���Ϣ��ʧ���𻵣�";
		return;
	}
	ofstream fout;
	fout.open(file_name(temp));
	cout<< "�������µĿ�����������";
	string name;
	cin>> name;
	fout<< "������" << name << endl;
	fout<< "�˻�ID��" << "#" << num;
	fout.close();
	cout<< endl;
	cout<< "�˻���Ϣ���ĳɹ���";
	iclear();
}


int get_act_id(user* temp)
{// ��Ϊ�涨ID����Ϊ������0�����������᷵��һ��������
	ifstream fin;
	fin.open(file_name(temp));
	fin.get();
	if (!fin.good())
		return 0;
	while (fin.get() != '#')
		// ͨ����ѯ�˻���Ϣ�ļ����#������ȷ��ID
		// һ��ȱ���ǣ����#ȱʧ�ˣ���ô��������
		;
	int num;
	fin >> num;
	fin.close();
	if (num <= 0)
		return 0;
	return num;
}

// �˺�����֤����Ա������˻���
inline void input(user* temp)
{
	for(;;)
	{
		cout<< "�������˻����� \n";
		if (!cin.get(temp->account, INPUT_MAX))
			cin.clear();
		iclear();
		ifstream fin;
		fin.open(temp->account);
		if (!fin.is_open())
		{// �����˻��������ھͷ���ѭ��
			cout<< "�˻��������ڣ�";
			continue;
		}
		else// �˻�����ȷ�ͽ���ѭ��
			break;
	}
}

// �������ۺ������Ϻ����Ĺ��ܣ���ʡ�������������Ҫ��
void administrator(user* temp)
{
	char ch;
	ofstream fout;
	cout<< "\n��ѡ�����Ա�";
	cout<< "\n��A���鿴�˻���Ϣ\n��B���鿴ID�ļ�\n��C��";
	cout<< "�޸��˻���Ϣ\n��D���޸�����\n��E���޸�ID�ļ�\n";
	cin.get(ch);
	if (ch == 'A'||ch == 'a')
	{
		iclear();// ������з�
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
			cout<< "��ǰID�ļ�ID��" << num << endl;
			fin.close();
		}
		else
			cout<< "ԭID�ļ���ʧ��";
	}
	else if (ch == 'C'||ch == 'c')
	{
		iclear();
		input(temp);
		fout.open(file_name(temp));
		cout<< "\n�������µĿ�����������";
		string name;
		cin>> name;
		fout<< "������" << name << endl;
		int num;
		cout<< "�������µ��˻�ID��";
		cin>> num;
		while (num <= 0)
		{
			cout<< "ID����Ϊ������0��\n���������룺";
			cin.clear();
			iclear();
			cin>> num;
		}
		fout<< "�˻�ID��" << "#" << num;
		fout.close();
		cout<< endl;
	}
	else if (ch == 'D'||ch == 'd')
	{
		iclear();
		input(temp);
		fout.open(temp->account);
		cout<< "�����������루20λ���ڣ���������6λ����\n";
		new_pasinput(temp);
		fout<< alg[get_alg(get_act_id(temp))](temp->password);
		fout.close();
	}
	else if (ch == 'E'||ch == 'e')
	{
		iclear();
		fout.open("id_number");
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
	cin.clear();
	iclear();
	cout<< "���س������ز˵�\n";
	cin.get();
}

// һ������Ϊ�����㷨������ּ�ڼ�ʹ�����������ļ�Ҳ����֪�����룩
char* Phonix(char* password)
{
	for (int i = 0, n = strlen(password); i < n; ++i, --n)
	{
		password[i] += password[n-1];
		// ����˵����ͷ�ַ��������β�ַ�����õ��µ�ͷ�ַ���
		// λ�����ڵ�����ֱ�������м��ַ�
		password[n-1] *= 2;// β�ַ������2�õ��µ�β�ַ�
	}// �ƽⷽ������һ����ַ��������2��
	// ����ǰһ���ַ��������Ӧ�ĺ�һ����ַ���Supehria()�෴��
	return password;
}


char* Supheria(char* password)
{
	for (int i = 0, n = strlen(password); i < n; ++i, --n)
	{
		password[n-1] += password[i];// ��Phonix()�պ��෴
		password[i] *= 2;
	}
	return password;
}
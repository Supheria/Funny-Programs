//#include "stdafx.h"
#include "pch.h"
#include "InfoFile.h"
#include <vector>

CInfoFile::CInfoFile()
{
}

CInfoFile::~CInfoFile()
{
}

//��ȡ��¼��Ϣ
void CInfoFile::ReadLogin(CString& name, CString& pwd)
{
	ifstream ifs; //�����ļ��������
	ifs.open(_F_LOGIN);
	char buf[1024] = { 0 };

	ifs.getline(buf, sizeof(buf));	//��ȡһ������
	name = CString(buf);	//��char* ת��ΪCString

	ifs.getline(buf, sizeof(buf));	//��ȡһ������
	pwd = CString(buf);	//��char* ת��ΪCString

	ifs.close();	//�ر��ļ�
}

//�޸�����
void CInfoFile::WritePwd(char* name, char* pwd)
{
	ofstream ofs; //�����ļ��������
	ofs.open(_F_LOGIN); //���ļ�

	ofs << name << endl;	//nameд���ļ�
	ofs << pwd << endl;	//pwdд���ļ�

	ofs.close();	//�ر��ļ�
}

//��ȡ��Ʒ����Ϣ
void CInfoFile::ReadDocline()
{
	ifstream ifs(_F_STOCK); //���뷽ʽ���ļ�

	char buf[1024] = { 0 };
	num = 0;	//��ʼ����Ʒ����Ϊ0
	ls.clear();
	//ȡ����ͷ
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof())	//û���ļ���β
	{
		msg tmp;

		ifs.getline(buf, sizeof(buf));	//��ȡһ��
		num++;	//��Ʒ������һ

		//AfxMessageBox(CString(buf));
		char* sst = strtok(buf, "|");	//��"|"�ָ�
		if (sst != NULL)
		{
			tmp.id = atoi(sst);	//��Ʒid
		}
		else
		{
			break;
		}

		sst = strtok(NULL, "|");
		tmp.name = sst;	//��Ʒ����

		sst = strtok(NULL, "|");
		tmp.price = atoi(sst);	//��Ʒ�۸�

		sst = strtok(NULL, "|");
		tmp.num = atoi(sst);	//��Ʒ��Ŀ

		ls.push_back(tmp);	//��������ĺ���
	}

	ifs.close();	//�ر��ļ�
}

//��Ʒд���ļ�
void CInfoFile::WriteDocline()
{
	ofstream ofs(_F_STOCK); //�����ʽ���ļ�
	string bt = "��ƷID | ��Ʒ�� | ���� | ���";

	if (ls.size() > 0)	//��Ʒ���������ݲ�ִ��
	{
		ofs << bt << endl;	//д���ͷ

		//ͨ��������ȡ���������ݣ�д���ļ�����"|"�ָ��β�ӻ���
		for (list<msg>::iterator it = ls.begin(); it != ls.end(); it++)
		{
			ofs << it->id << "|";
			ofs << it->name << "|";
			ofs << it->price << "|";
			ofs << it->num << endl;
		}
	}
	ofs.close();
}

//�������Ʒ
//name:��Ʒ���ƣ�num:��棬price:�۸�
void CInfoFile::Addline(CString name, int num, int price)
{
	msg tmp;

	if (ls.size() > 0)
	{
		//��Ʒ���ƣ���棬�۸���Ч
		if (!name.IsEmpty() && num > 0 && price > 0)
		{
			tmp.id = ls.size() + 1;	//id�Զ���1
			CStringA str;
			str = name;					//CString תCStringA
			tmp.name = str.GetBuffer();//CString תΪchar *, ��Ʒ����
			tmp.num = num;			//���
			tmp.price = price;		//�۸�

			ls.push_back(tmp);			//��������ĺ���
		}
	}
}

// ɾ����Ʒ��Ŀ
void CInfoFile::DeleteDocline(CString cID, CString cname, CString cprice, CString cnum)
{
	ifstream fin(_F_STOCK);
	vector<string> content; string line;
	for (int i = 0; fin.peek() != EOF; i++)
	{
		getline(fin, line);
		content.push_back(line);
	}
	fin.close();
	
	CString test = cID + "|" + cname + "|" + cprice + "|" + cnum;
	//MessageBox(test);
	ofstream fout(_F_STOCK);
	fout << content[0] << endl;
	for (int i = 1; i < content.size(); i++)
	{
		if (content[i] != (string)CW2A(test.GetBuffer()))
		{
			fout << content[i] << endl;
		}
	}
	fout.close();
}
#pragma once

#ifndef _TOOLS_H_
#define _TOOLS_H_

#include "pch.h"

namespace ieTools
{
	inline std::vector<std::string> SplitString(std::string str, std::string pattern)
		// https://www.cnblogs.com/dfcao/p/cpp-FAQ-split.html
	{
		using namespace std;
		vector<string> v;
		string::size_type pos1{ 0 }, pos2{ str.find(pattern) };
		while (pos2 != string::npos)
		{
			v.push_back(str.substr(pos1, pos2 - pos1));

			pos1 = pos2 + pattern.size();
			pos2 = str.find(pattern, pos1);
		}
		if (pos1 != str.length())
			v.push_back(str.substr(pos1));
		return v;
	}
#pragma region ·��ɾ������
	// https://blog.csdn.net/CV2017/article/details/100672264
	// �ж��Ƿ���".."Ŀ¼��"."Ŀ¼
	inline static bool IsSpecialDir(const char* path)
	{
		return strcmp(path, "..") == 0 || strcmp(path, ".") == 0;
	}
	// �ж��ļ�������Ŀ¼�����ļ�
	inline static bool IsDir(int attrib)
	{
		return attrib == 16 || attrib == 18 || attrib == 20;
	}
	// ��ʾɾ��ʧ��ԭ��
	inline static void ShowError(const char* file_name = NULL)
	{
		errno_t err;
		_get_errno(&err);
		switch (err)
		{
		case ENOTEMPTY:
			printf("Given path is not a directory, the directory is not empty, or the directory is either the current working directory or the root directory.\n");
			break;
		case ENOENT:
			printf("Path is invalid.\n");
			break;
		case EACCES:
			printf("%s had been opend by some application, can't delete.\n", file_name);
			break;
		}
	}
	inline static void GetFilePath(const char* path, const char* file_name, char* file_path)
	{
		strcpy_s(file_path, sizeof(char) * _MAX_PATH, path);
		file_path[strlen(file_path) - 1] = '\0';
		strcat_s(file_path, sizeof(char) * _MAX_PATH, file_name);
	}
	// �ݹ�����Ŀ¼���ļ���ɾ��
	inline static void DeleteFile(const char* path)
	{
		char pcSearchPath[_MAX_PATH];
		sprintf_s(pcSearchPath, _MAX_PATH, "%s\\*", path); // pcSearchPath Ϊ����·����* ����ͨ���

		_finddata_t DirInfo; // �ļ�����Ϣ
		_finddata_t FileInfo; // �ļ���Ϣ
		intptr_t f_handle; // ���Ҿ��

		char pcTempPath[_MAX_PATH];
		if ((f_handle = _findfirst(pcSearchPath, &DirInfo)) != -1)
		{
			while (_findnext(f_handle, &FileInfo) == 0)
			{
				if (IsSpecialDir(FileInfo.name))
					continue;
				if (FileInfo.attrib & _A_SUBDIR) // �����Ŀ¼������������·��
				{
					GetFilePath(pcSearchPath, FileInfo.name, pcTempPath);
					DeleteFile(pcTempPath); // ��ʼ�ݹ�ɾ��Ŀ¼�е�����
					if (FileInfo.attrib == 20)
						printf("This is system file, can't delete!\n");
					else
					{
						// ɾ����Ŀ¼�������ڵݹ鷵��ǰ����_findclose,�����޷�ɾ��Ŀ¼
						if (_rmdir(pcTempPath) == -1)
						{
							ShowError(); // Ŀ¼�ǿ������ʾ����ԭ��
						}
					}
				}
				else
				{
					strcpy_s(pcTempPath, pcSearchPath);
					pcTempPath[strlen(pcTempPath) - 1] = '\0';
					strcat_s(pcTempPath, FileInfo.name); // �����������ļ�·��

					if (remove(pcTempPath) == -1)
					{
						ShowError(FileInfo.name);
					}

				}
			}
			_findclose(f_handle); // �رմ򿪵��ļ���������ͷŹ�����Դ�������޷�ɾ����Ŀ¼
		}
		else
		{
			//ShowError(); // ��·�������ڣ���ʾ������Ϣ
		}
	}
	inline void DeleteAllFile(const char* pcPath)
	{
		DeleteFile(pcPath); // ɾ�����ļ�����������ļ�

		if (_rmdir(pcPath) == -1) // ɾ�����ļ���
		{
			//ShowError();
		}
	}
#pragma endregion
}

namespace myTools
{
	inline void CreateDir(std::string path)
	{
		using namespace std;
		string command; command = "mkdir " + path;
		system(command.c_str());
	}
	inline void CleanDir(std::string path)
	{
		const char* _path = path.c_str();
		ieTools::DeleteFile(_path);
	}
	inline void DeleteDir(std::string path)
	{
		const char* _path = path.c_str();
		ieTools::DeleteAllFile(_path);
	}
	inline void iclear() { while (std::cin.get() != '\n'); }
	inline bool IfABlankString(std::string str)
	{
		if (ieTools::SplitString(str, " ").size()) { return false; }
		else
			return true;
	}

	inline bool TestFileExistence(std::string _path, bool createnew = true) // ����ļ��Ƿ����
	{
		using namespace std;
		ifstream fin(_path);
		if (fin.is_open()) { return true; }
		if (createnew)
		{
			ofstream fout(_path);
			if (fout.is_open()) { return true; }
		}
		return false;
	}
	inline bool TestFileContent(std::string _path, bool spaceiscontent = false) // ����ļ������Ƿ�Ϊ��
	{
		using namespace std;
		ifstream fin(_path);
		while (fin.peek() != EOF)
		{
			if (spaceiscontent || (fin.peek() != '\n' && fin.peek() != ' ')) { fin.close(); return true; }
			fin.get();
		}
		fin.close();
		return false;
	}

	inline std::string encoder(std::string &str) //�ַ��������㷨
	{
		using namespace std;
		string result;
		int len = str.length();
		for (int i = 0; i < len; i++) //�û�ÿ���ֽڵ�ǰ��λ�ͺ���λ�������ַ��������ַ������ֽڶ������ַ�Ϊ��λ��
		{
			uchar AB = str[len - i - 1];
			uchar A = AB >> 4; uchar B = AB - (A << 4);
			uchar BA = (B << 4) + A;
			result += BA;
		}
		if (len % 2 != 0) { len--; }
		for (int i = 0; i < len; i += 2) //���������ַ�������żλ
		{
			char temp = result[i];
			result[i] = result[i + 1];
			result[i + 1] = temp;
		}
		str = result;
		return result;
	}
	inline std::string encoder(char* ch) //�ַ��������㷨
	{
		using namespace std;
		string result;
		int len = strlen(ch);
		for (int i = 0; i < len; i++) //�û�ÿ���ֽڵ�ǰ��λ�ͺ���λ�������ַ��������ַ������ֽڶ������ַ�Ϊ��λ��
		{
			uchar AB = ch[len - i - 1];
			uchar A = AB >> 4; uchar B = AB - (A << 4);
			uchar BA = (B << 4) + A;
			result += BA;
		}
		len = result.length(); if (len % 2 != 0) { len--; }
		for (int i = 0; i < len; i += 2) //���������ַ�������żλ
		{
			char temp = result[i];
			result[i] = result[i + 1];
			result[i + 1] = temp;
		}
		return result;
	}
	inline std::string decoder(std::string &str)//�ַ��������㷨
	{
		using namespace std;
		string result;
		int len = str.length(); if (len % 2 != 0) { len--; }
		for (int i = 0; i < len; i += 2) //�ָ������ַ�������żλ
		{
			char temp = str[i];
			str[i] = str[i + 1];
			str[i + 1] = temp;
		}
		len = str.length();
		for (int i = 0; i < len; i++) //�ָ�ÿ���ֽڵ�ԭʼ״̬�Լ��ַ�����ԭʼ˳��
		{
			uchar BA = str[len - i - 1];
			uchar B = BA >> 4; uchar A = BA - (B << 4);
			uchar AB = (A << 4) + B;
			result += AB;
		}
		str = result;
		return result;
	}

	inline sTime SpanToTime(span1970 span)
	{
		sTime t;
		localtime_s(&t, &span); // ��������ת��Ϊʱ���
		return t;
	}
	inline bool myCopyFile(std::string fromPath, std::string toPath)
	{
		using namespace std;
		ifstream fin(fromPath);
		if (fin.is_open())
		{
			vector<string> file;
			while (fin.peek() != EOF)
			{
				string line;
				getline(fin, line);
				file.push_back(line);
			}
			ofstream fout(toPath);
			if (fout.is_open())
			{
				for (auto it = file.begin(); it != file.end(); it++)
				{
					fout << *it << endl;
				}
				return true;
			}
		}
		return false;
	}
}

#endif
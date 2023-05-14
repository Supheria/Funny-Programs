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
#pragma region 路径删除工具
	// https://blog.csdn.net/CV2017/article/details/100672264
	// 判断是否是".."目录和"."目录
	inline static bool IsSpecialDir(const char* path)
	{
		return strcmp(path, "..") == 0 || strcmp(path, ".") == 0;
	}
	// 判断文件属性是目录还是文件
	inline static bool IsDir(int attrib)
	{
		return attrib == 16 || attrib == 18 || attrib == 20;
	}
	// 显示删除失败原因
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
	// 递归搜索目录中文件并删除
	inline static void DeleteFile(const char* path)
	{
		char pcSearchPath[_MAX_PATH];
		sprintf_s(pcSearchPath, _MAX_PATH, "%s\\*", path); // pcSearchPath 为搜索路径，* 代表通配符

		_finddata_t DirInfo; // 文件夹信息
		_finddata_t FileInfo; // 文件信息
		intptr_t f_handle; // 查找句柄

		char pcTempPath[_MAX_PATH];
		if ((f_handle = _findfirst(pcSearchPath, &DirInfo)) != -1)
		{
			while (_findnext(f_handle, &FileInfo) == 0)
			{
				if (IsSpecialDir(FileInfo.name))
					continue;
				if (FileInfo.attrib & _A_SUBDIR) // 如果是目录，生成完整的路径
				{
					GetFilePath(pcSearchPath, FileInfo.name, pcTempPath);
					DeleteFile(pcTempPath); // 开始递归删除目录中的内容
					if (FileInfo.attrib == 20)
						printf("This is system file, can't delete!\n");
					else
					{
						// 删除空目录，必须在递归返回前调用_findclose,否则无法删除目录
						if (_rmdir(pcTempPath) == -1)
						{
							ShowError(); // 目录非空则会显示出错原因
						}
					}
				}
				else
				{
					strcpy_s(pcTempPath, pcSearchPath);
					pcTempPath[strlen(pcTempPath) - 1] = '\0';
					strcat_s(pcTempPath, FileInfo.name); // 生成完整的文件路径

					if (remove(pcTempPath) == -1)
					{
						ShowError(FileInfo.name);
					}

				}
			}
			_findclose(f_handle); // 关闭打开的文件句柄，并释放关联资源，否则无法删除空目录
		}
		else
		{
			//ShowError(); // 若路径不存在，显示错误信息
		}
	}
	inline void DeleteAllFile(const char* pcPath)
	{
		DeleteFile(pcPath); // 删除该文件夹里的所有文件

		if (_rmdir(pcPath) == -1) // 删除此文件夹
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

	inline bool TestFileExistence(std::string _path, bool createnew = true) // 检测文件是否存在
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
	inline bool TestFileContent(std::string _path, bool spaceiscontent = false) // 检测文件内容是否为空
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

	inline std::string encoder(std::string &str) //字符串加密算法
	{
		using namespace std;
		string result;
		int len = str.length();
		for (int i = 0; i < len; i++) //置换每个字节的前四位和后四位，并将字符串反序（字符串以字节而不是字符为单位）
		{
			uchar AB = str[len - i - 1];
			uchar A = AB >> 4; uchar B = AB - (A << 4);
			uchar BA = (B << 4) + A;
			result += BA;
		}
		if (len % 2 != 0) { len--; }
		for (int i = 0; i < len; i += 2) //交换反序字符串的奇偶位
		{
			char temp = result[i];
			result[i] = result[i + 1];
			result[i + 1] = temp;
		}
		str = result;
		return result;
	}
	inline std::string encoder(char* ch) //字符串加密算法
	{
		using namespace std;
		string result;
		int len = strlen(ch);
		for (int i = 0; i < len; i++) //置换每个字节的前四位和后四位，并将字符串反序（字符串以字节而不是字符为单位）
		{
			uchar AB = ch[len - i - 1];
			uchar A = AB >> 4; uchar B = AB - (A << 4);
			uchar BA = (B << 4) + A;
			result += BA;
		}
		len = result.length(); if (len % 2 != 0) { len--; }
		for (int i = 0; i < len; i += 2) //交换反序字符串的奇偶位
		{
			char temp = result[i];
			result[i] = result[i + 1];
			result[i + 1] = temp;
		}
		return result;
	}
	inline std::string decoder(std::string &str)//字符串解密算法
	{
		using namespace std;
		string result;
		int len = str.length(); if (len % 2 != 0) { len--; }
		for (int i = 0; i < len; i += 2) //恢复反序字符串的奇偶位
		{
			char temp = str[i];
			str[i] = str[i + 1];
			str[i + 1] = temp;
		}
		len = str.length();
		for (int i = 0; i < len; i++) //恢复每个字节的原始状态以及字符串的原始顺序
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
		localtime_s(&t, &span); // 将总秒数转换为时间戳
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
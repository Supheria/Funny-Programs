// NormalDistribution.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

//原文：https://blog.csdn.net/fengbingchun/article/details/73770856

#include <iostream>
#include <fstream>
#include <random>
#include <map>
#include <iomanip>
//#include <cmath>
#include <windows.h>

inline int pow10(int pow)
{
	int base = 10;
	for (int i = 1; i < pow; i++)
	{
		base *= base;
	}
	return base;
}

int main()
{
	using namespace std;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY); //暗
	cout << "【特别注意】";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN); //原
	cout << "侧列数字仅表示取值区间。\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY); //暗
	cout << "【程序算法】";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED); //亮黄
	cout << "<random.h>std::random_device产生随机数种子，<random.h>std::default_random_engine产生随机数，<random.h>std::normal_distribution<>以随机数产生正态分布随机结果。\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY); //暗
	cout << "【参考原文】";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE); //青
	cout << "https://blog.csdn.net/fengbingchun/article/details/73770856 \n\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN); //原
	//
	//全局变量
	bool aturn = false;
	double mu{ 0.0 }, sigma{ 1.0 };
	float ratioofmu = 1.0;
	int loops{ 0 }, precise{ 1 }, bigloop{ 1 }, orimupos{ 0 };
	int* maxorder{ new int }, * average{ new int[0] };
	do
	{
		//输入
		cout << "输入期望（#精确位数*机显倍数）\n";
		if (!((cin.peek() >= '0' && cin.peek() <= '9') || cin.peek() == '\n' || cin.peek() == '-')) { cout << "\n程序已退出。"; break; }
		if (cin.peek() == '\n' && aturn) { cin.get(); goto P; } else cin >> mu; ratioofmu = 1;
		if (cin.peek() == '#') { cin.get(); cin >> precise; precise = precise == 0 ? 1 : pow10(precise); } else { precise = 1; }
		if (cin.peek() == '*') { cin.get(); cin >> ratioofmu; ratioofmu = ratioofmu == 0 ? 1.0 : ratioofmu; } else { ratioofmu = 1.0; }
		cout << "输入方差（必须大于0）\n"; cin >> sigma; cin.get(); sigma = sigma < 0 ? -sigma : sigma; sigma == 0 ? 1 : sigma;
		cout << "输入样本数量（默认1万）\n"; if (cin.peek() == '\n') { cin.get(); loops = 10000; } else { cin >> loops; cin.get(); } loops = loops < 0 ? -loops : loops;
		bigloop = 1;

		//参数输出
	P:	cout << "\n期望" << mu * ratioofmu; if (ratioofmu != 1) { cout << "(" << ratioofmu << "*)"; } cout << " 方差" << sigma << " 样本" << (double)loops / 10000 << "万个" << "\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
		cout << "值域";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
		cout << " 样本含量";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY); 
		cout << " 含量占比"; 
		if (bigloop > 1) 
		{ 
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN); 
			cout << " 前";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
			cout << '-' << bigloop << '-';
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
			cout << "次平均占比" << endl;
		} 
		else cout << endl;

		//正态分布算法
		std::normal_distribution<> norm(mu, sigma);
		std::random_device seed; std::default_random_engine gen(seed()); //随机数种子
		std::map<int, int> hist; for (int n = 0; n < loops; ++n) { ++hist[(norm(gen) + 0.5) * precise]; } //生成统计数对

		//输出统计数据
		int _mu = mu * precise;
		int inloop{ 0 }, sub{ 0 };
		for (auto p : hist) //获取数列纵向位移
		{
			if (p.first == _mu && bigloop > 1)
			{
				sub = inloop - orimupos;
				//break;
			}
			inloop++;
		}
		if (bigloop == 1)
		{
			delete[] average;
			average = new int[inloop]; //初始化average
		}
		inloop = 0;
		int min{ 0 }, max{ 0 }, mean{ 0 }, percent{ 0 }, permax{ 0 }, permin{ 0 }, permean{ 0 }, maxordernum{ 0 };
		bool first{ true };
		double perresult{ 0.0 }, averaperofmu{ 0.0 };
		for (auto p : hist)
		{
			percent = (double)p.second / loops * 10000;
			if (first) { min = max = p.second; permin = permax = percent; }
			if (min > p.second) { min = p.second; permin = percent; }
			if (max < p.second) { max = p.second; permax = percent; maxordernum = 0; }
			if (p.second == max) { maxorder[maxordernum] = p.first; maxordernum++; }
			if (bigloop == 1) //初始化average第一列表
			{
				if (p.first == _mu) { orimupos = inloop; }
				average[inloop] = percent;
			}
			//校准后续列表位置
			else
			{
				if (sub < 0)
				{
					average[inloop - sub] += percent;
					perresult = (double) average[inloop - sub] / bigloop / 100;
				}
				else if (sub > 0 && inloop >= sub)
				{
					average[inloop - sub] += percent;
					perresult = (double)average[inloop - sub] / bigloop / 100;
				}
				else if (sub == 0)
				{
					average[inloop] += percent;
					perresult = (double)average[inloop] / bigloop / 100;
				}
				else
					perresult = 0.0;
			}
			//输出
			if (p.first == _mu) 
			{ 
				mean = p.second; permean = percent;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN); 
				cout << (double)p.first * ratioofmu / precise << '\t' << p.second << ' ' << '\t' << (double)percent / 100 << '%';
				if (bigloop > 1 && perresult != 0)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
					cout << "\t=" << perresult << '%' << std::endl; averaperofmu = perresult;
				}
				else
					cout << endl;
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
				cout << (double)p.first * ratioofmu / precise;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
				cout << '\t' <<p.second << ' ';
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
				cout << '\t' << (double)percent / 100 << '%';
				if (bigloop > 1)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
					if (perresult != 0)
						cout << "\t=" << perresult << '%' << std::endl;
					else
						cout << "\t-" << endl;
				}
				else
					cout << endl;
			}

			first = false; inloop++;
			//循环结束
		}
		
		//辅助数据输出
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
		cout << "最多"; 
		for (int i = 0; i < maxordernum; i++) { cout << (double)maxorder[i] * ratioofmu / precise; if (i + 1 != maxordernum) cout << "、"; }
		if (ratioofmu != 1) { cout << "(" << ratioofmu << "*)"; } cout << "内 " << max << "【" << (double)permax / 100 << "%】个样本，";
		cout << "最少" << min << "【" << (double)permin / 100 << "%】个样本\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN);
		cout << "期望";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
		cout << mu * ratioofmu;
		if (ratioofmu != 1) { cout << "(" << ratioofmu << "*)"; } cout << "内 " << mean << "【" << (double)permean / 100 << '%'; 
		if (bigloop > 1) 
		{ 
			cout << ",";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
			cout << (double)averaperofmu << '%';
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
			cout << '(' << bigloop << ')';
		}
		cout << "】个样本（方差" << sigma << " 总样本" << (double)loops / 10000 << "万）" << "\n";
		
		aturn = true; bigloop++; maxordernum = 0;
		cout << "\n\n>>键入回车以使用相同数据\n>>键入其他键退出程序\n\n";
		//循环结束
	} while (TRUE);

	delete[] average; delete maxorder;
	cin.clear(); while (cin.get() != '\n'); cin.get();
	return 0;

    //std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

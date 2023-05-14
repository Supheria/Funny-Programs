#include <iostream>
#include "n!.h"

using std::cin;
using std::cout;

int f(int n); //阶乘函数
int TB(int MAX, int m);
//循环重新输入m，TB是"Too Big"的简称

int main()
{
	cout << "This program multiples ";
	cout << "all\nnumbers from the ";
	cout << "one input to 1.\n(Negatives ";
	cout << "are NOT included)\n\nSo, ";

	int MAX = 20; //最大阶乘基数
	int m; //阶乘基数
	cout << "number, please(<";
	cout << MAX << "): ";
	cin >> m; //客户为m赋值
	if (m >= MAX) //m越限则进入TB循环
	{
		m = TB(MAX, m);
	}
	while (m < MAX) //m限内则进入计算循环
	{
		cout << "result:" << f(m);
		//计算并输出结果
		cout << "\n\n";
		//下一次客户为m赋值开始
		cout << "number, please(<";
		cout << MAX << ")";
		cout << "\n<Input 0 to Finish>: ";
		cin >> m;
		if (m == 0) //m赋值为0则结束程序
		{
			cout << "\nSee You.";
			return 0;
		}
		if (m >= MAX) //m越限则进入TB循环
		{
			m = TB(MAX, m);
		}
	}
}

int TB(int MAX, int m) //TB循环体
{
	while (m >= MAX) //m越限则循环输入m
	{
		cout << "Too Big!\n";
		cout << "\nagain please(<";
		cout << MAX << "):";
		cin >> m;
	}
	return m; //m终于限内则返回m
}
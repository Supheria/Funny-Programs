// CP's Ks.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

typedef std::vector<int> vInt;

int main()
{
    using namespace std;
    map<int, vInt> iClause;
    for (int k1 = 1; k1 <= 15; k1++) // k1
    {
        for (int k2 = 1; k2 <= 16; k2++) // k2
        {
            for (auto it = iClause.begin(); ; it++) // 比对已有键值
            {
                if (it == iClause.end()) // 新建键值
                {
                    vInt v;
                    v.push_back(k1);
                    iClause.insert(pair<int, vInt>(k1 * k2, v));
                    break;
                }
                if (k1 * k2  == it->first) // 存在一个已有键值
                {
                    it->second.push_back(k1);
                   break;
                }
            }
        }
    }
    int i = 1;
    for (auto p : iClause)
    {
        sort(p.second.rbegin(), p.second.rend()); // 从大到小排列vInt容器
        //cout << p.second[0] << endl; // 输出k1
        //cout << p.first / p.second[0] << endl; // 输出k2
        //cout << p.first << endl; // 输出k
        cout << p.second[0] << " * " << p.first / p.second[0] << " = " << p.first << endl;
        i++;
    }
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

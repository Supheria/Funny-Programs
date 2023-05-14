#include "tools.h"
#include "player.h"
#include "prototype.h"

bool menu()
{
	using namespace std; using namespace myTools;
	cout << "\n\n菜单: \n\n"
		<< "（A）选择身份\n"
		<< "（B）新身份\n"
		<< "（C）设置\n"
		<< "（D）开发人员\n"
		<< "按其他键退出游戏。\n";
	char choice[5]; cin.get(choice, 5); cin.clear(); iclear();
	cout << endl;
	switch (choice[0])
	{
	case 'A':
	case 'a': A();
		return true;
		break;
	case 'B':
	case 'b': B();
		return true;
		break;
	case 'C':
	case 'c': while (C());
		return true;
		break;
	case 'D':
	case 'd': D();
		return true;
		break;
	default:
		return false;
	}
}

// 选择身份
void A()
{
	using namespace std;
	if (!SelectSave()) { return; }
}

// 新身份
void B()
{
	using namespace std;
	if (!NewSave()) { return; }
	//newone.show_info();
}

bool C()
{
	using namespace std; using namespace myTools;
	cout << "\n\n设置: \n\n"
		<< "（A）设置存盘路径\n"
		<< "（B）广告位\n"
		<< "（C）删除存档\n"
		<< "（D）开发人员\n"
		<< "按其他键返回菜单。\n";
	char choice; cin.get(choice); cin.clear(); iclear();
	cout << endl;
	switch (choice)
	{
	case 'A':
	case 'a': cout << "\n\n“等待开发！”";
		return true;
		break;
	case 'B':
	case 'b':;
		return true;
		break;
	case 'C':
	case 'c': DeleteSave();
		return true;
		break;
	case 'D':
	case 'd': D();
		return true;
		break;
	default:
		return false;
	}
	return 0;
}

void D()
{

}
#include "tools.h"
#include "player.h"
#include "prototype.h"

bool menu()
{
	using namespace std; using namespace myTools;
	cout << "\n\n�˵�: \n\n"
		<< "��A��ѡ�����\n"
		<< "��B�������\n"
		<< "��C������\n"
		<< "��D��������Ա\n"
		<< "���������˳���Ϸ��\n";
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

// ѡ�����
void A()
{
	using namespace std;
	if (!SelectSave()) { return; }
}

// �����
void B()
{
	using namespace std;
	if (!NewSave()) { return; }
	//newone.show_info();
}

bool C()
{
	using namespace std; using namespace myTools;
	cout << "\n\n����: \n\n"
		<< "��A�����ô���·��\n"
		<< "��B�����λ\n"
		<< "��C��ɾ���浵\n"
		<< "��D��������Ա\n"
		<< "�����������ز˵���\n";
	char choice; cin.get(choice); cin.clear(); iclear();
	cout << endl;
	switch (choice)
	{
	case 'A':
	case 'a': cout << "\n\n���ȴ���������";
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
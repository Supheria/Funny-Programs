#include "tools.h"
#include "dir.h"
#include "prototype.h"
#include "save class.h"
#include "career.h"

BOOL CtrlHandler(DWORD fdwCtrlType)
{
	switch (fdwCtrlType)
	{
		/* handle the CTRL-CLOSE signal */
	case CTRL_CLOSE_EVENT:
		//EndGame();
		return TRUE;
	default:
		return FALSE;
	}
}

extern SaveReg savereg;

bool Initialize()
{
	using namespace std;
	DirIni();
	if (!IniCareer()) 
	{ 
		cout << "\n\nFatalErro：无法初始化Career！\n\n";
		cin.get();
		return false; 
	}
	if (!savereg.ReadReg())
	{
		cout << "\n\nFatalErro：无法读取注册表！\n\n";
		cin.get();
		return false;
	}
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE);
}

void EndGame()
{
	using namespace std;
	if (!savereg.OutputReg())
	{
		cout << "\n\nFatalErro：无法写入注册表！\n\n";
		cin.get();
	}
	savereg.~SaveReg();
	OutputCareer();
}

void DirIni()
{
	using namespace std; using namespace myTools;
	for (int i = 0; i < sizeof(dirs) / sizeof(*dirs); i++)
	{
		CreateDir(dirs[i]);
	}
}
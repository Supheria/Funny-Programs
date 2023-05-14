
// TuneHelper.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "framework.h"
#include "TuneHelper.h"
#include "TuneHelperDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTuneHelperApp

BEGIN_MESSAGE_MAP(CTuneHelperApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTuneHelperApp 构造

CTuneHelperApp::CTuneHelperApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CTuneHelperApp 对象

CTuneHelperApp theApp;


// CTuneHelperApp 初始化

BOOL CTuneHelperApp::InitInstance()
{
	CTuneHelperDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	return FALSE;
}



// QQ Login.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "framework.h"
#include "QQ Login.h"
#include "QQ LoginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CQQLoginApp

BEGIN_MESSAGE_MAP(CQQLoginApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CQQLoginApp 构造

CQQLoginApp::CQQLoginApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CQQLoginApp 对象

CQQLoginApp theApp;


// CQQLoginApp 初始化

BOOL CQQLoginApp::InitInstance()
{
	CQQLoginDlg indlg;
//	m_pMainWnd = &indlg;// 若该指针未被显式初始化，则会自动将当前的父窗口作为程序的主窗口
						// 程序在任务栏中的图标是当前的主窗口的图标。
						// 若主窗口被隐藏或当前没有主窗口，则程序将不出现任务栏中
						// 销毁了该指针所指向的窗口就等于结束了整个程序，
						// 但如果该指针没有被显式初始化，则会在当前主窗口销毁后自动获取新的父窗口的指针
	while (DONTSTOPIT == indlg.DoModal());
	if (!this->WriteProfileInt("Settings", "BackColor", m_backcolor))
	{
		AfxMessageBox("无法写入配置文件，需要管理员权限");
	}



	return FALSE;
}



void CQQLoginApp::SetDialogBkColor(COLORREF clrCtlBk, COLORREF clrCtlText) // CWinApp::SetDialogBkColor()是CWindApp类的protected成员，因此需要设置一个接口来访问它
																		   // protected成员 : 仅自身类方法和派生类方法可以访问
{
	// TODO: 在此处添加实现代码.

//	CWinApp::SetDialogBkColor(clrCtlBk, clrCtlText); // 该函数已经被弃用了，无法再被调用
}

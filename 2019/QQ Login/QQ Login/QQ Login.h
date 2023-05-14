
// QQ Login.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号


// CQQLoginApp:
// 有关此类的实现，请参阅 QQ Login.cpp
//

class CQQLoginApp : public CWinApp
{
public:
	CQQLoginApp();

// 重写
public:
	virtual BOOL InitInstance();
	SUser gUser; // 充当该程序的全局变量

// 实现

	DECLARE_MESSAGE_MAP()

public:
	void SetDialogBkColor(COLORREF clrCtlBk = RGB(192, 192, 192), COLORREF clrCtlText = RGB(0, 0, 0));
	COLORREF m_backcolor;
};

extern CQQLoginApp theApp;


// QQ LoginDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "QQ Login.h"
#include "QQ LoginDlg.h"
#include "afxdialogex.h"
#include "CInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CQQLoginDlg 对话框



CQQLoginDlg::CQQLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_QQLOGIN_DIALOG, pParent)
{
	theApp.m_backcolor = theApp.GetProfileIntA("Settings", "BackColor", RGB(255, 255, 255)); // RGB(红, 绿, 蓝)

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQQLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CQQLoginDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EXIT, &CQQLoginDlg::OnBnClickedExit)
	ON_BN_CLICKED(IDC_RELOGIN, &CQQLoginDlg::OnBnClickedRelogin)
	ON_BN_CLICKED(IDC_ADMIN, &CQQLoginDlg::OnBnClickedAdmin)
	ON_BN_CLICKED(IDC_INFO, &CQQLoginDlg::OnBnClickedInfo)
	ON_BN_CLICKED(IDC_BACKCOLOR, &CQQLoginDlg::OnBnClickedBackcolor)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CQQLoginDlg 消息处理程序


void CQQLoginDlg::Login()
{
	CLoginDlg dlg;
	if (IDCANCEL == dlg.DoModal())
	{
		this->EndDialog(-1);
	}
}

BOOL CQQLoginDlg::OnInitDialog()
{
	Login();

	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	CString ctile;
	ctile = "控制面板 - " + CString(theApp.gUser.m_prior ? "管理员 " : "用户 ") + CString(theApp.gUser.m_name);
	SetWindowText(ctile);

	GetDlgItem(IDC_ADMIN)->ShowWindow(theApp.gUser.m_prior ? SW_SHOW : SW_HIDE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CQQLoginDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CQQLoginDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CQQLoginDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

//	CDialogEx::OnOK();
}


void CQQLoginDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnCancel();
}


void CQQLoginDlg::OnBnClickedExit()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(-1);
}


// 重新登录
void CQQLoginDlg::OnBnClickedRelogin()
{
	// TODO: 在此添加控件通知处理程序代码
	
	this->EndDialog(DONTSTOPIT);
}

// 管理面板
void CQQLoginDlg::OnBnClickedAdmin()
{
	// TODO: 在此添加控件通知处理程序代码

	this->ShowWindow(SW_HIDE);
	CPriorDlg dlg;
	if (LETUSDIE == dlg.DoModal())
	{
		OnBnClickedRelogin();
	}
	ShowWindow(SW_SHOW);
}



void CQQLoginDlg::OnBnClickedInfo()
{
	// TODO: 在此添加控件通知处理程序代码

	this->ShowWindow(SW_HIDE);
	CInfoDlg dlg;
	dlg.DoModal();
	ShowWindow(SW_SHOW);
}


void CQQLoginDlg::OnBnClickedBackcolor()
{
	// TODO: 在此添加控件通知处理程序代码

	CColorDialog dlg; // 系统对话框::颜色选取对话框
	if (IDCANCEL == dlg.DoModal())
	{
		return;
	}
	theApp.m_backcolor = dlg.GetColor(); // 颜色类型
	//EndDialog(DONTSTOPIT);
	Invalidate(); // 更新窗口
}


HBRUSH CQQLoginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (nCtlColor)
	{
	case CTLCOLOR_DLG: //更改对话框背景色
	{
		HBRUSH b = CreateSolidBrush(theApp.m_backcolor);
		return b;
	}
	default:
	return hbr;
	}
}


void CQQLoginDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码

}
// CLoginDlg.cpp: 实现文件
//

#include "pch.h"
#include "SaleSystem.h"
#include "CLoginDlg.h"
#include "afxdialogex.h"
#include "InfoFile.h"

// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN, pParent)
	, m_name(_T(""))
	, m_psw(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LOGINNAME_EDIT, m_name);
	DDX_Text(pDX, IDC_LOGINPSW_EDIT, m_psw);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_LOGINOK_BUTTON, &CLoginDlg::OnBnClickedLoginokButton)
	ON_BN_CLICKED(IDC_LOGINCANCEL_BUTTON, &CLoginDlg::OnBnClickedLogincancelButton)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序

// 单击按钮 : 验证登录信息
void CLoginDlg::OnBnClickedLoginokButton()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_name.IsEmpty() || m_psw.IsEmpty()) // 输入为空
	{
		return;
	}

	// 验证身份信息
	CInfoFile info;
	CString name, psw;
	info.ReadLogin(name, psw); // 读取在录身份信息
	if (name != m_name || psw != m_psw)
	{
		MessageBox(L"身份不合法。", L"对您说：");
		return;
	}
	
	CDialog::OnCancel(); // 验证通过，关闭登录对话框
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	// 默认登录信息
	CInfoFile info;
	CString name, psw;
	info.ReadLogin(name, psw);
	m_name = name;
	m_psw = psw;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

// 单击按钮 : 退出整个程序
void CLoginDlg::OnBnClickedLogincancelButton()
{
	// TODO: 在此添加控件通知处理程序代码

	exit(0);
}


void CLoginDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	// CDialogEx::OnOK();
}

// 点击× : 退出整个程序
void CLoginDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	// CDialogEx::OnClose(); // 关闭当前对话框，等同于CDialog::OnCancel();
	exit(0);
}

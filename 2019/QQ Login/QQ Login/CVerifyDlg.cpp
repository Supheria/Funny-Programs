// CVerifyDlg.cpp: 实现文件
//

#include "pch.h"
#include "QQ Login.h"
#include "CVerifyDlg.h"
#include "afxdialogex.h"


// CVerifyDlg 对话框

IMPLEMENT_DYNAMIC(CVerifyDlg, CDialogEx)

CVerifyDlg::CVerifyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VERIFY, pParent)
{

}

CVerifyDlg::~CVerifyDlg()
{
}

void CVerifyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVerifyDlg, CDialogEx)
END_MESSAGE_MAP()


// CVerifyDlg 消息处理程序


INT_PTR CVerifyDlg::DoMyModal(CString name, CString pass)
{
	// TODO: 在此处添加实现代码.
	m_name = name;
	m_pass = pass;
	return this->DoModal();
}


void CVerifyDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();

	CString szPass;
	GetDlgItemText(IDC_PASS, szPass);
	if (szPass != m_pass)
	{
		AfxMessageBox("密码不一致！");
		return;
	}
	EndDialog(IDOK);
}


BOOL CVerifyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	SetDlgItemText(IDC_NAME, m_name);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

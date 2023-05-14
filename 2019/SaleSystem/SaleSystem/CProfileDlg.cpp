// CProfileDlg.cpp: 实现文件
//

#include "pch.h"
#include "SaleSystem.h"
#include "CProfileDlg.h"
#include "InfoFile.h"


// CProfileDlg

IMPLEMENT_DYNCREATE(CProfileDlg, CFormView)

CProfileDlg::CProfileDlg()
	: CFormView(IDD_PROFILE)
	, m_career(_T(""))
	, m_name(_T(""))
	, m_firstpsw(_T(""))
	, m_secondpsw(_T(""))
	, m_statetxt(_T(""))
	, m_stateuptxt(_T(""))
{

}

CProfileDlg::~CProfileDlg()
{
}

void CProfileDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PROFILEIDCAREER_EDIT, m_career);
	DDX_Text(pDX, IDC_PROFILEIDNAME_EDIT, m_name);
	DDX_Text(pDX, IDC_PROFILECHANGEPASSWORDFIRST_EDIT, m_firstpsw);
	DDX_Text(pDX, IDC_PROFILECHANGEPASSWORDSECOND_EDIT, m_secondpsw);
	DDX_Control(pDX, IDC_PROFILECHANGEPASSWORDSECOND_EDIT, m_secondpswctrl);
	DDX_Control(pDX, IDC_PROFILECHANGEPASSWORDFAKE_BUTTON, m_fakebutton);
	DDX_Control(pDX, IDC_PROFILECHANGEPASSWORDSTATE_TEXT, m_statectrl);
	DDX_Text(pDX, IDC_PROFILECHANGEPASSWORDSTATE_TEXT, m_statetxt);
	DDX_Control(pDX, IDC_STATEUP_TEXT, m_stateupctrl);
	DDX_Text(pDX, IDC_STATEUP_TEXT, m_stateuptxt);
}

BEGIN_MESSAGE_MAP(CProfileDlg, CFormView)
	ON_EN_KILLFOCUS(IDC_PROFILECHANGEPASSWORDSECOND_EDIT, &CProfileDlg::OnEnKillfocusProfilechangepasswordsecondEdit)
//	ON_EN_SETFOCUS(IDC_PROFILECHANGEPASSWORDFIRST_EDIT, &CProfileDlg::OnEnSetfocusProfilechangepasswordfirstEdit)
ON_EN_CHANGE(IDC_PROFILECHANGEPASSWORDFIRST_EDIT, &CProfileDlg::OnEnChangeProfilechangepasswordfirstEdit)
ON_EN_KILLFOCUS(IDC_PROFILECHANGEPASSWORDFIRST_EDIT, &CProfileDlg::OnEnKillfocusProfilechangepasswordfirstEdit)
ON_EN_SETFOCUS(IDC_PROFILECHANGEPASSWORDFIRST_EDIT, &CProfileDlg::OnEnSetfocusProfilechangepasswordfirstEdit)
ON_EN_SETFOCUS(IDC_PROFILECHANGEPASSWORDSECOND_EDIT, &CProfileDlg::OnEnSetfocusProfilechangepasswordsecondEdit)
ON_STN_CLICKED(IDC_STATEUP_TEXT, &CProfileDlg::OnStnClickedStateupText)
ON_EN_CHANGE(IDC_PROFILECHANGEPASSWORDSECOND_EDIT, &CProfileDlg::OnEnChangeProfilechangepasswordsecondEdit)
END_MESSAGE_MAP()


// CProfileDlg 诊断

#ifdef _DEBUG
void CProfileDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CProfileDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CProfileDlg 消息处理程序

// 初始化
void CProfileDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	m_career = L"二级管理员";
	CInfoFile info;
	CString name, psw;
	info.ReadLogin(name, psw);
	m_name = name;
	UpdateData(FALSE);
}

// 失去输入焦点 : 更新密码
void CProfileDlg::OnEnKillfocusProfilechangepasswordsecondEdit()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);
	if (m_secondpsw.IsEmpty())
	{
		return;
	}
	if (m_firstpsw != m_secondpsw)
	{
		m_statetxt = L"两次输入不一致";
		m_secondpsw.Empty();
		UpdateData(FALSE);
		m_statectrl.ShowWindow(SW_SHOW);
		//MessageBox(L"更新失败！两次输入不一致。", L"注意：");
		return;
	}
	CInfoFile info;
	CStringA caname; caname = m_name;
	CStringA capsw; capsw = m_firstpsw;
	info.WritePwd(caname.GetBuffer(), capsw.GetBuffer());
	MessageBox(L"修改成功。", L"对您说：");
	
	//清空密码显示
	m_firstpsw.Empty();
	m_secondpsw.Empty();
	UpdateData(FALSE);
	m_secondpswctrl.EnableWindow(FALSE);
	m_fakebutton.ShowWindow(SW_HIDE);
}

// 获得焦点 : 解锁确认密码输入框
//void CProfileDlg::OnEnSetfocusProfilechangepasswordfirstEdit()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	m_secondpswctrl.EnableWindow(TRUE);
//}

// 文本已变更并更新显示 : 检测第一密码框是否为空
void CProfileDlg::OnEnChangeProfilechangepasswordfirstEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CFormView::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	UpdateData(TRUE);
	if (m_firstpsw.IsEmpty())
	{
		m_secondpsw.Empty();
		UpdateData(FALSE);
		m_secondpswctrl.EnableWindow(FALSE);
		//m_fakebutton.ShowWindow(SW_HIDE);
		return;
	}
	//m_fakebutton.ShowWindow(SW_SHOWDEFAULT);
	m_secondpswctrl.EnableWindow(TRUE);
}

// 失去焦点 : 检测新密码是否和原密码相同
void CProfileDlg::OnEnKillfocusProfilechangepasswordfirstEdit()
{
	// TODO: 在此添加控件通知处理程序代码

	CInfoFile info;
	CString name, psw;
	info.ReadLogin(name, psw);

	if (m_firstpsw == psw)
	{
		m_stateuptxt = L"和原密码相同";
		m_secondpsw.Empty();
		UpdateData(FALSE);
		m_secondpswctrl.EnableWindow(FALSE);
		m_stateupctrl.ShowWindow(SW_SHOWDEFAULT);
		m_fakebutton.ShowWindow(SW_HIDE);
		//MessageBox(L"和原密码相同。", L"注意：");
		return;
	}
}

// 获得焦点 : 关闭提示文字
void CProfileDlg::OnEnSetfocusProfilechangepasswordfirstEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	m_statectrl.ShowWindow(SW_HIDE);
	m_stateupctrl.ShowWindow(SW_HIDE);
}

// 获得焦点 : 关闭提示文字
void CProfileDlg::OnEnSetfocusProfilechangepasswordsecondEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	m_statectrl.ShowWindow(SW_HIDE);
	m_stateupctrl.ShowWindow(SW_HIDE);
}


void CProfileDlg::OnStnClickedStateupText()
{
	// TODO: 在此添加控件通知处理程序代码
}

// 文本已变更并更新显示 : 显示按钮
void CProfileDlg::OnEnChangeProfilechangepasswordsecondEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CFormView::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	UpdateData(TRUE);
	if (m_secondpsw.IsEmpty())
	{
		m_fakebutton.ShowWindow(SW_HIDE);
		return;
	}
	m_fakebutton.ShowWindow(SW_SHOWDEFAULT);
	//m_secondpswctrl.EnableWindow(TRUE);
}

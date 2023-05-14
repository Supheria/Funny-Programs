// CInputDlg.cpp: 实现文件
//

#include "pch.h"
#include "QQ Login.h"
#include "CInputDlg.h"
#include "afxdialogex.h"


// CInputDlg 对话框

IMPLEMENT_DYNAMIC(CInputDlg, CDialogEx)

CInputDlg::CInputDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INPUT, pParent)
{

}

CInputDlg::~CInputDlg()
{
}

void CInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInputDlg, CDialogEx)
END_MESSAGE_MAP()


// CInputDlg 消息处理程序


BOOL CInputDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	const CTime t(2000, 1, 1, 0, 0, 0);
	((CDateTimeCtrl*/*必须强制转化为派生类*/)GetDlgItem(IDC_BIRTH))->SetTime(&t); // 设置默认日期
	((CComboBox*/*必须强制转化为派生类*/)GetDlgItem(IDC_DEPARTMENT))->SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CInputDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	if (GetFocus() != GetDlgItem(IDC_SALARY)) // 焦点不在IDOK上
	{
		CString szTest;
		CWnd* pWnd = GetFocus();
		pWnd->GetWindowText(szTest);
		if (!szTest.GetLength())
		{
			AfxMessageBox("请输入内容");
			pWnd->SetFocus();
			return;
		}
		else
		{
			CDialog::NextDlgCtrl(); // 将焦点设置在TAB顺序中的下一个控件上
			return;
		}
		
	}

	CListCtrl& list = m_pInfoDlg->m_list; // 引用
	int nCount = list.GetItemCount();
	CString szNumb, szName, szBrth, szDprt, szSalr;
	GetDlgItemText(IDC_NUMB, szNumb); // 工号
	for (int i = 0; i < nCount; i++)
	{
		if (szNumb == list.GetItemText(i, 1))
		{
			AfxMessageBox("已存在的员工编号：" + szNumb);
			GetDlgItem(IDC_NUMB)->SetFocus();
			return;
		}
	}
	if (!szNumb.GetLength())
	{
		AfxMessageBox("不完整的员工信息");
		GetDlgItem(IDC_NUMB)->SetFocus();
		return;
	}
	GetDlgItemText(IDC_NAME, szName); // 姓名
	if (!szName.GetLength())
	{
		AfxMessageBox("不完整的员工信息");
		GetDlgItem(IDC_NAME)->SetFocus();
		return;
	}
	GetDlgItemText(IDC_BIRTH, szBrth); // 生日
	if (!szBrth.GetLength())
	{
		AfxMessageBox("不完整的员工信息");
		GetDlgItem(IDC_BIRTH)->SetFocus();
		return;
	}
	GetDlgItemText(IDC_DEPARTMENT, szDprt); // 部门
	if (!szDprt.GetLength())
	{
		AfxMessageBox("不完整的员工信息");
		GetDlgItem(IDC_DEPARTMENT)->SetFocus();
		return;
	}
	GetDlgItemText(IDC_SALARY, szSalr); // 工资
	if (!szSalr.GetLength())
	{
		AfxMessageBox("不完整的员工信息");
		GetDlgItem(IDC_SALARY)->SetFocus();
		return;
	}

	CString series; series.Format("%d", nCount + 1);
	list.InsertItem(nCount, series); // 设置行号
	list.SetItemText(nCount, 1, szNumb); // 设置工号
	list.SetItemText(nCount, 2, szName); // 设置姓名
	list.SetItemText(nCount, 3, szBrth); // 设置生日
	list.SetItemText(nCount, 4, szDprt); // 设置部门
	list.SetItemText(nCount, 5, szSalr); // 设置工资

	SetDlgItemText(IDC_NUMB, "");
	SetDlgItemText(IDC_NAME, "");
	SetDlgItemText(IDC_SALARY, "");
	GetDlgItem(IDC_NUMB)->SetFocus();

	//CDialogEx::OnOK();
}

// CPriorDlg.cpp: 实现文件
//

#include "pch.h"
#include "QQ Login.h"
#include "CPriorDlg.h"
#include "afxdialogex.h"
#include "CVerifyDlg.h"
//#include <fstream>


// CPriorDlg 对话框

IMPLEMENT_DYNAMIC(CPriorDlg, CDialogEx)

CPriorDlg::CPriorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PRIORITY, pParent)
{

}

CPriorDlg::~CPriorDlg()
{
}

void CPriorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPriorDlg, CDialogEx)
	ON_BN_CLICKED(IDC_ADD, &CPriorDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_DELETE, &CPriorDlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_MODIFY, &CPriorDlg::OnBnClickedModify)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


void CPriorDlg::ReadUser(CListCtrl* pList) // 读取账户信息
{
	// TODO: 在此处添加实现代码.

	CFile inf; // C语言文件处理类
	if (!inf.Open(_USER_DAT_, CFile::modeRead | CFile::shareDenyNone))
	{
		return;
	}
	pList->DeleteAllItems(); // 规定 : 必须先清空原有的列表条目
	SUser u; CString sNum;
	for (int i = 0;  inf.Read(&u, sizeof(u)) == sizeof(u)/*>0*/; i++ )
	{
		sNum.Format("%d", i + 1); // 行号
		pList->InsertItem(i, sNum);
		pList->SetItemText(i, 1, u.m_name);
		pList->SetItemText(i, 2, u.m_pass);
		pList->SetItemText(i, 3, u.m_prior ? "高级" : "普通");
	}
	inf.Close();
}


BOOL CPriorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化

	CListCtrl* pList = (CListCtrl*/*必须强制转化为派生类*/)GetDlgItem(IDC_LIST);
	pList->SetExtendedStyle(pList->GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	pList->InsertColumn(0, "序号", 0, 40);
	pList->InsertColumn(1, "账户", 2, 100);
	pList->InsertColumn(2, "密码", 2, 100);
	pList->InsertColumn(3, "权限", 2, 100);
	ReadUser(pList);
	CComboBox* pComb = (CComboBox*/*必须强制转化为派生类*/)GetDlgItem(IDC_PRIORITY);
	if (-1 != theApp.gUser.m_prior)
	{
		pComb->AddString("普通");
		istemp = false;
	}
	pComb->AddString("高级");
	pComb->SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CPriorDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

//	CDialogEx::OnOK();
}


void CPriorDlg::OnBnClickedAdd()
{
	// TODO: 在此添加控件通知处理程序代码

	SUser u;
	CString name, pass;
	GetDlgItemText(IDC_NAME, name);
	GetDlgItemText(IDC_PASS, pass);
	if (!(name.GetLength() && pass.GetLength()))
	{
		AfxMessageBox("用户名或密码不能为空。");
		return;
	}
	if (name.GetLength() > sizeof(u.m_name) || pass.GetLength() > sizeof(u.m_pass))
	{
		CString text; text.Format("用户名长度不能大于%d，密码长度不能大于%d", sizeof(u.m_name), sizeof(u.m_pass));
		AfxMessageBox(text);
		return;
	}

	//strlwr(u.sName); // 将所有大写转换为小写（过时语法）
	name.MakeLower(); // 将所有大写转换为小写
	CListCtrl* pList = (CListCtrl*/*必须强制转化为派生类*/)GetDlgItem(IDC_LIST); // 获取列表控件指针
	int nCount = pList->GetItemCount();
	for (int i = 0; i < nCount; i++)
	{
		if (pList->GetItemText(i, 1) == name)
		{
			AfxMessageBox("用户已存在。");
			GetDlgItem(IDC_NAME)->SetFocus();
			return;
		}
	}

	if (istemp)
	{
		CVerifyDlg dlg;
		if (IDCANCEL == dlg.DoMyModal(name, pass))
		{
			return;
		}
	}

	CString sNum; sNum.Format("%d", nCount + 1); // 行号
	pList->InsertItem(nCount, sNum);
	pList->SetItemText(nCount, 1, name);
	pList->SetItemText(nCount, 2, pass);
	CComboBox* pComb = (CComboBox*/*必须强制转化为派生类*/)GetDlgItem(IDC_PRIORITY);
	int nSel = pComb->GetCurSel();
	CString prior;
	pComb->GetLBText(nSel, prior);
	pList->SetItemText(nCount, 3, prior);
	//pList->SetItemText(nCount, 3, nSel ? "高级" : "普通"); // A ? B : C语法 : 若A不为零(true)则返回B，若A为零(false)则返回C
														   // 此语法是A = A != 0 ? B : C的优化
	if (istemp)
	{
		this->EndDialog(LETUSDIE);
		return;
	}
	SetDlgItemText(IDC_NAME, "");
	SetDlgItemText(IDC_PASS, "");
	GetDlgItem(IDC_NAME)->SetFocus();
	((CComboBox*/*必须强制转化为派生类*/)GetDlgItem(IDC_PRIORITY))->SetCurSel(0);
}

// pList->GetSelectionMark()最好和pList->GetSelectedCount()一起使用
//
// 但pList->GetFirstSelectedItemPosition()和pList->GetNextSelectedItem()用得更多

void CPriorDlg::OnBnClickedDelete()
{
	// TODO: 在此添加控件通知处理程序代码

	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST);
	POSITION pos = pList->GetFirstSelectedItemPosition();
	int nSel = pList->GetNextSelectedItem(pos);
	if (nSel < 0)
	{
		AfxMessageBox("请先选中一个条目。");
		return;
	}

	if ("高级" == pList->GetItemText(nSel, 3))
	{
		int nCount = pList->GetItemCount();
		bool candele = false;
		for (int i{ 0 }; i < nCount; i++)
		{
			if ("高级" == pList->GetItemText(i, 3) && i != nSel)
			{
				candele = true;
				break;
			}
		}
		if (!candele)
		{
			AfxMessageBox("至少要有一个管理员！");
			return;
		}
		CString szText;
		szText = "确实要删除管理员 " + pList->GetItemText(nSel, 1) + " 吗？";
		if (IDYES == AfxMessageBox(szText, MB_YESNO))
		{
			pList->DeleteItem(nSel);
		}
		return;
	}
	CString szText;
	szText = "确实要删除用户 " + pList->GetItemText(nSel, 1) + " 吗？";
	if (IDYES == AfxMessageBox(szText, MB_YESNO))
	{
		pList->DeleteItem(nSel);
	}
}


void CPriorDlg::OnBnClickedModify()
{
	// TODO: 在此添加控件通知处理程序代码

	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST);
	POSITION pos = pList->GetFirstSelectedItemPosition();
	int nSel = pList->GetNextSelectedItem(pos);
	
	SUser u;
	CString name, pass;

	GetDlgItemText(IDC_NAME, name);
	GetDlgItemText(IDC_PASS, pass);
	if (name.GetLength() > sizeof(u.m_name) || pass.GetLength() > sizeof(u.m_pass))
	{
		CString text; text.Format("用户名长度不能大于%d，密码长度不能大于%d", sizeof(u.m_name), sizeof(u.m_pass));
		AfxMessageBox(text);
		return;
	}
	name.MakeLower(); // 将所有大写转换为小写
	int nCount = pList->GetItemCount();
	//CComboBox* pComb = (CComboBox*)GetDlgItem(IDC_PRIORITY);
	//int nSelOfComb = pComb->GetCurSel();
	CString szTest;
	//pComb->GetLBText(nSelOfComb, szTest); // 获取当前选择的权限
	GetDlgItemText(IDC_PRIORITY, szTest); // 获取当前选择的权限
	for (int i = 0; i < nCount; i++) // 寻找同名账户
	{
		if (pList->GetItemText(i, 1) == name)
		{
			if (szTest != pList->GetItemText(i, 3) || (pass.GetLength() && pList->GetItemText(i, 2) != pass))
			{
				nSel = i;
			}
			else
			{
				CString szText;
				szText = "存在" + CString(pList->GetItemText(i, 3) == "高级" ? "管理员 " : "用户 ") + pList->GetItemText(i, 1);
				AfxMessageBox(szText, MB_ICONINFORMATION);
				return;
			}
		}
	}
	if (nSel < 0)
	{
		AfxMessageBox("请先选中一个条目。");
		return;
	}

	const CString former_name{ pList->GetItemText(nSel, 1) }, former_pass{ pList->GetItemText(nSel, 2) };
	CString szText;
	szText = "确实要修改" + CString(pList->GetItemText(nSel, 3) == "高级" ? "管理员 " : "用户 ")  + pList->GetItemText(nSel, 1) + " 的账户吗？";
	if (( (name.GetLength() && former_name != name) || (pass.GetLength() && former_pass != pass) ) && IDNO == AfxMessageBox(szText, MB_YESNO))
	{
		return;
	}
	
	pList->SetItemText(nSel, 1, name.GetLength() ? name : former_name);
	pList->SetItemText(nSel, 2, pass.GetLength() ? pass : former_pass);
	if (szTest != pList->GetItemText(nSel, 3))
	{
		CString szText;
		szText = "您正试图修改" + CString(pList->GetItemText(nSel, 3) == "高级" ? "管理员 " : "用户 ") + pList->GetItemText(nSel, 1) + " 的权限，是要继续吗？";
		if (IDNO == AfxMessageBox(szText, MB_YESNO))
		{
			return;
		}
		
		if ("高级" == pList->GetItemText(nSel, 3))
		{
			int nCount = pList->GetItemCount();
			bool candele = false;
			for (int i{ 0 }; i < nCount; i++)
			{
				if ("高级" == pList->GetItemText(i, 3) && i != nSel)
				{
					candele = true;
					break;
				}
			}
			if (!candele)
			{
				AfxMessageBox("至少要有一个管理员！");
				return;
			}
		}
	}
	pList->SetItemText(nSel, 3, szTest);

	SetDlgItemText(IDC_NAME, "");
	SetDlgItemText(IDC_PASS, "");
}

void CPriorDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码

	CFile of; // C语言文件处理类
	//std::ofstream fout(_USER_DAT_);
	if (!of.Open(_USER_DAT_, CFile::modeCreate | CFile::modeWrite))
	{
		AfxMessageBox("保存文件失败！");
		return;
	}

	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST);
	int nCount = pList->GetItemCount(); // 获取列表条目数量
	SUser u;
	for (int i = 0; i < nCount; i++)
	{
		pList->GetItemText(i, 1, u.m_name, sizeof(u.m_name));
		pList->GetItemText(i, 2, u.m_pass, sizeof(u.m_pass));
		u.m_prior = (pList->GetItemText(i, 3) == "高级"/*如果是高级则为1(true)，否则为0(false)*/);
		of.Write(&u, sizeof(u));
	}

	of.Close();
}


void CPriorDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnCancel();
	EndDialog(7); // 模式对话框无论调用EndDialog(ID)还是Destroy()或EndDialog(-1)，都会经历Destroy()被直接销毁
				  // 非模式对话框若不调用Destroy()或EndDialog(-1)而是调用EndDialog(ID)，则只是暂时被隐藏起来，之后就仍可以用ShowWindow()显示
				  // 总之，模式对话框一定是一次性的，一定会马上经历Destroy()
				  // 而非模式对话框可以根据其实际需要决定何时经历Destroy()
}


// CInfoDlg.cpp: 实现文件
//

#include "pch.h"
#include "QQ Login.h"
#include "CInfoDlg.h"
#include "afxdialogex.h"
#include "CInputDlg.h"


// CInfoDlg 对话框

IMPLEMENT_DYNAMIC(CInfoDlg, CDialogEx)

CInfoDlg::CInfoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INFO, pParent)
{

}

CInfoDlg::~CInfoDlg()
{
}

void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDC_ADD, &CInfoDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_OPEN, &CInfoDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_SAVE, &CInfoDlg::OnBnClickedSave)
END_MESSAGE_MAP()


// CInfoDlg 消息处理程序


BOOL CInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST);
	m_list.SubclassDlgItem(IDC_LIST, this);
	m_list.InsertColumn(0, "序号", 0, 40);
	m_list.InsertColumn(1, "工号", 2, 80);
	m_list.InsertColumn(2, "姓名", 2, 80);
	m_list.InsertColumn(3, "生日", 2, 80);
	m_list.InsertColumn(4, "部门", 2, 80);
	m_list.InsertColumn(5, "工资", 2, 80);
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CInfoDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CInfoDlg::OnBnClickedAdd()
{
	// TODO: 在此添加控件通知处理程序代码

	CInputDlg dlg;
	dlg.m_pInfoDlg = this;
	dlg.DoModal();
}


void CInfoDlg::OnBnClickedOpen()
{
	// TODO: 在此添加控件通知处理程序代码

	LPCSTR szFilter = "员工信息文件(*.info)|*.info|测试类型(*.test)|*.test|所有文件|*.*||"; // "类型1名称|类型1|类型2名称|类型2|类型3名称|类型3……||"
	CFileDialog dlg(TRUE/*TRUE : 打开文件，FLASE : 保存文件*/, "info"/*默认后缀名*/, NULL/*默认文件名*/, OFN_HIDEREADONLY/*文件列表风格*/, szFilter/*文件类型筛选器*/); // 系统对话框::文件对话框

	if (IDCANCEL == dlg.DoModal())
	{
		return;
	}
	CString szPath = dlg.GetPathName(); // 获取文件路径

	CFile inf;
	if (!inf.Open(szPath, CFile::modeRead))
	{
		AfxMessageBox("文件打开失败");
		return;
	}
	m_list.DeleteAllItems(); // 清空列表中的所有条目
	SInfo info; CString szTemp;
	for (int i = 0; inf.Read(&info, sizeof(info)) == sizeof(info); i++)
	{
		szTemp.Format("%d", i + 1);
		m_list.InsertItem(i, szTemp); // 行号
		szTemp.Format("%d", info.m_numb);
		m_list.SetItemText(i, 1, szTemp); // 工号
		m_list.SetItemText(i, 2, info.m_name); // 姓名
		m_list.SetItemText(i, 3, info.m_birth); // 生日
		m_list.SetItemText(i, 4, info.m_dept); // 部门
		szTemp.Format("%0.2f"/*取浮点数的两位小数*/, info.m_salr);
		m_list.SetItemText(i, 5, szTemp); // 工资
	}

}


void CInfoDlg::OnBnClickedSave()
{
	// TODO: 在此添加控件通知处理程序代码

	CTime t = CTime::GetTickCount();
	int nYear = t.GetYear();
	int nMonth = t.GetMonth();
	int nDay = t.GetDay();
	//int nHour = t.GetHour();
	//int nMin = t.GetMinute();
	CString szFilename;
	szFilename.Format("员工信息%d%02d%02d", nYear, nMonth, nDay);

	LPCSTR szFilter = "员工信息文件(*.info)|*.info|测试类型(*.test)|*.test|所有文件|*.*||"; // "类型1名称|类型1|类型2名称|类型2|类型3名称|类型3……||"
	CFileDialog dlg(FALSE/*TRUE : 打开文件，FLASE : 保存文件*/, "info"/*默认后缀名*/, szFilename/*默认文件名*/, OFN_OVERWRITEPROMPT/*文件列表风格*/, szFilter/*文件类型筛选器*/); // 系统对话框::文件对话框
	
	if (IDCANCEL == dlg.DoModal())
	{
		return;
	}
	CString szPath = dlg.GetPathName(); // 获取文件路径

	CFile of;
	if (!of.Open(szPath, CFile::modeCreate | CFile::modeWrite))
	{
		AfxMessageBox("文件保存失败");
		return;
	}
	int nCount = m_list.GetItemCount();
	SInfo info;
	for (int i = 0; i < nCount; i++)
	{
		info.m_numb = atoi(m_list.GetItemText(i, 1)); // 获取工号，并利用atoi()将字符串转换为int
		m_list.GetItemText(i, 2, info.m_name,sizeof(info.m_name)); // 获取姓名
		m_list.GetItemText(i, 3, info.m_birth, sizeof(info.m_birth)); // 获取生日
		m_list.GetItemText(i, 4, info.m_dept, sizeof(info.m_dept)); // 获取部门
		info.m_salr = (float)atof(m_list.GetItemText(i, 5)); // 获取工资

		int n = sizeof(info);
		of.Write(&info, sizeof(info));
		
	}
	of.Close();
}

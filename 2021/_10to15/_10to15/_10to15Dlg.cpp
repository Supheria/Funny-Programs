
// _10to15Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "_10to15.h"
#include "_10to15Dlg.h"
#include "afxdialogex.h"
#include "iniFile.h"
#include "convert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
static IniFile ini;

// C_10to15Dlg 对话框



C_10to15Dlg::C_10to15Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD__10TO15_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C_10to15Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SCALE, m_scale);
	DDX_Control(pDX, IDC_EDIT_ORI, m_ori);
	DDX_Control(pDX, IDC_EDIT_TIMES, m_times);
	DDX_Control(pDX, IDC_EDIT_ADD, m_add);
	DDX_Control(pDX, IDC_LIST2, m_list);
}

BEGIN_MESSAGE_MAP(C_10to15Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_EN_CHANGE(IDC_EDIT_SCALE, &C_10to15Dlg::OnEnChangeEditScale)
//ON_BN_CLICKED(IDOK, &C_10to15Dlg::OnBnClickedOk)
ON_BN_CLICKED(IDC_BUTTON_GO, &C_10to15Dlg::OnBnClickedButtonGo)
ON_BN_CLICKED(IDC_TOPMOST, &C_10to15Dlg::OnBnClickedTopmost)
ON_WM_CLOSE()
//ON_WM_CREATE()
//ON_NOTIFY(HDN_ITEMCLICK, 0, &C_10to15Dlg::OnHdnItemclickList2)
ON_NOTIFY(NM_CLICK, IDC_LIST2, &C_10to15Dlg::OnNMClickList2)
ON_WM_SIZE()
//ON_WM_DESTROY()
END_MESSAGE_MAP()


// C_10to15Dlg 消息处理程序

BOOL C_10to15Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//IniFile ini;
	ReadIniFile(ini);
	CString cScale; cScale.Format("%d", ini.scale); m_scale.SetWindowText(cScale);
	CString cOriginal; cOriginal.Format("%d", ini.original); m_ori.SetWindowText(cOriginal);
	CString cTimes; cTimes.Format("%d", ini.times); m_times.SetWindowText(cTimes);
	CString cAdd; cAdd.Format("%d", ini.add); m_add.SetWindowText(cAdd);
	this->MoveWindow(ini.mainRect);

	SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); // 窗口始终置顶
	((CButton*)GetDlgItem(IDC_TOPMOST))->SetCheck(BST_CHECKED);

	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list.InsertColumn(0, "次");
	m_list.InsertColumn(1, "结果", LVCFMT_RIGHT);
	OnBnClickedButtonGo();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C_10to15Dlg::OnPaint()
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
HCURSOR C_10to15Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void C_10to15Dlg::OnEnChangeEditScale()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//	// TODO:  在此添加控件通知处理程序代码
//}


//void C_10to15Dlg::OnBnClickedOk()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	CDialogEx::OnOK();
//}


void C_10to15Dlg::OnBnClickedButtonGo()
{
	// TODO: 在此添加控件通知处理程序代码
	while (m_list.DeleteItem(0)); // 刷新列表
	CString cScale; m_scale.GetWindowText(cScale); int scale = _ttoi(cScale);
	CString cTimes; m_times.GetWindowText(cTimes); int times = _ttoi(cTimes);
	CString cOriginal; m_ori.GetWindowText(cOriginal); int original = _ttoi(cOriginal);
	CString cAdd; m_add.GetWindowText(cAdd); int add = _ttoi(cAdd);
	for (int i = 0; i < times; i++)
	{
		original += add;
		vector<int> vResult;
		Convert convert(scale, vResult, original);
		CString result = "";
		for (int j = 0;;)
		{
			CString temp; temp.Format("%d", vResult[j]);
			result += temp;
			if (++j == vResult.size())
			{
				break;
			}
			result += "-";
		}
		CString num; num.Format("%d", i + 1);
		m_list.InsertItem(i, num);
		m_list.SetItemText(i, 1, result);
	}
	//IniFile ini;
	ini.original = _ttoi(cOriginal);
	ini.add = _ttoi(cAdd);
	ini.scale = _ttoi(cScale);
	ini.times = _ttoi(cTimes);
	m_list.SetItemState(ini.pos, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	UpdateWindow();
}


void C_10to15Dlg::OnBnClickedTopmost()
{
	// TODO: 在此添加控件通知处理程序代码
	int nState = ((CButton*)GetDlgItem(IDC_TOPMOST))->GetCheck();
	if (BST_CHECKED == nState)
	{
		SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); // 窗口始终置顶
	}
	else
	{
		SetWindowPos(&CWnd::wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}
}

void C_10to15Dlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	// CDialogEx::OnOK();
}

// 点击× : 退出整个程序
void C_10to15Dlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	// CDialogEx::OnClose(); // 关闭当前对话框，等同于CDialog::OnCancel();
	OutIniFile(ini);
	exit(0);
}


//int C_10to15Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
//		return -1;
//
//	// TODO:  在此添加您专用的创建代码
//
//
//	return 0;
//}


//void C_10to15Dlg::OnHdnItemclickList2(NMHDR* pNMHDR, LRESULT* pResult)
//{
//	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
//	// TODO: 在此添加控件通知处理程序代码
//	
//
//	*pResult = 0;
//}


void C_10to15Dlg::OnNMClickList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		while (pos)
		{
			ini.pos = m_list.GetNextSelectedItem(pos);
		}
	}
	*pResult = 0;
}


void C_10to15Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	UpdateWindow();
	this->GetWindowRect(&ini.mainRect);
}

void C_10to15Dlg::UpdateWindow()
{
	if (m_list)
	{
		CRect mainRect;
		this->GetWindowRect(&mainRect);
		int width = mainRect.Width() < 252 ? 252 : mainRect.Width();
		int height = mainRect.Height() < 359 ? 359 : mainRect.Height(); // 最小窗口宽高
		this->MoveWindow(mainRect.left, mainRect.top, width, height);
		// 重新定位报表
		CRect listRect;
		m_list.GetWindowRect(&listRect);
		CRect clientRect;
		this->GetClientRect(&clientRect);
		ClientToScreen(&clientRect);
		m_list.MoveWindow(listRect.left - clientRect.left, listRect.top - clientRect.top, clientRect.right - listRect.left, clientRect.bottom - listRect.top - 14);
		CRect rect;
		m_list.GetClientRect(&rect);
		m_list.SetColumnWidth(0, rect.Width() / 4);
		m_list.SetColumnWidth(1, rect.Width() / 4 * 3);
	}
}

//void C_10to15Dlg::OnDestroy()
//{
//	CDialogEx::OnDestroy();
//
//	// TODO: 在此处添加消息处理程序代码
//	
//}

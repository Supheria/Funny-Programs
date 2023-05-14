
// TuneHelperDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "TuneHelper.h"
#include "TuneHelperDlg.h"
#include "afxdialogex.h"
#include "Helper.h"
#include "iniFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTuneHelperDlg 对话框



CTuneHelperDlg::CTuneHelperDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TUNEHELPER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTuneHelperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHORD1, m_chords[0]);
	DDX_Control(pDX, IDC_CHORD2, m_chords[1]);
	DDX_Control(pDX, IDC_CHORD3, m_chords[2]);
	DDX_Control(pDX, IDC_CHORD4, m_chords[3]);
	DDX_Control(pDX, IDC_CHORD5, m_chords[4]);
	DDX_Control(pDX, IDC_CHORD6, m_chords[5]);
	DDX_Control(pDX, IDC_CHORD7, m_chords[6]);
	DDX_Control(pDX, IDC_POT1, m_pots[0]);
	DDX_Control(pDX, IDC_POT2, m_pots[1]);
	DDX_Control(pDX, IDC_POT3, m_pots[2]);
	DDX_Control(pDX, IDC_POT4, m_pots[3]);
	DDX_Control(pDX, IDC_POT5, m_pots[4]);
	DDX_Control(pDX, IDC_POT6, m_pots[5]);
	DDX_Control(pDX, IDC_POT7, m_pots[6]);
	DDX_Control(pDX, IDC_TUNEMOD, m_tunemod);
	DDX_Control(pDX, IDC_CHORDMOD, m_chrdmod);
	DDX_Control(pDX, IDC_SELECTMAIN, m_selectMain);
	DDX_Control(pDX, IDC_MAIN, m_main);
	DDX_Control(pDX, IDC_CHILD, m_child);
	DDX_Control(pDX, IDC_PARENT, m_parent);
	DDX_Control(pDX, IDC_RELATION, m_related);
	DDX_Control(pDX, IDC_RPARENT, m_rParent);
	DDX_Control(pDX, IDC_RCHILD, m_rChild);
	DDX_Control(pDX, IDC_LABEL, m_labels);
	DDX_Control(pDX, IDC_LABEL1, m_label[0]);
	DDX_Control(pDX, IDC_LABEL2, m_label[1]);
	DDX_Control(pDX, IDC_LABEL3, m_label[2]);
	DDX_Control(pDX, IDC_LABEL4, m_label[3]);
	DDX_Control(pDX, IDC_LABEL5, m_label[4]);
	DDX_Control(pDX, IDC_LABEL6, m_label[5]);
	DDX_Control(pDX, IDC_LABEL7, m_label[6]);
	DDX_Control(pDX, IDC_STATIC_UP, m_tunelabelUP);
	DDX_Control(pDX, IDC_STATIC_DN, m_tunelabelDN);
}

BEGIN_MESSAGE_MAP(CTuneHelperDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
ON_CBN_SELCHANGE(IDC_TUNEMOD, &CTuneHelperDlg::OnCbnSelchangeTunemod)
ON_CBN_SELCHANGE(IDC_CHORDMOD, &CTuneHelperDlg::OnCbnSelchangeChordmod)
ON_BN_CLICKED(IDC_CONVERT1, &CTuneHelperDlg::OnBnClickedConvert1)
ON_BN_CLICKED(IDC_CONVERT2, &CTuneHelperDlg::OnBnClickedConvert2)
ON_BN_CLICKED(IDC_CONVERT3, &CTuneHelperDlg::OnBnClickedConvert3)
ON_BN_CLICKED(IDC_BUTTON3, &CTuneHelperDlg::OnBnClickedButton3)
ON_BN_CLICKED(IDC_BUTTON2, &CTuneHelperDlg::OnBnClickedButton2)
ON_BN_CLICKED(IDC_BUTTON1, &CTuneHelperDlg::OnBnClickedButton1)
ON_BN_CLICKED(IDC_BUTTON4, &CTuneHelperDlg::OnBnClickedButton4)
ON_BN_CLICKED(IDC_BUTTON5, &CTuneHelperDlg::OnBnClickedButton5)
ON_BN_CLICKED(IDC_BUTTON6, &CTuneHelperDlg::OnBnClickedButton6)
ON_BN_CLICKED(IDC_SHOWUP, &CTuneHelperDlg::OnBnClickedShowup)
ON_NOTIFY(NM_CUSTOMDRAW, IDC_SELECTMAIN, &CTuneHelperDlg::OnNMCustomdrawSelectmain)
ON_WM_CTLCOLOR()
ON_BN_CLICKED(IDC_TOPMOST, &CTuneHelperDlg::OnBnClickedTopmost)
ON_WM_DESTROY()
END_MESSAGE_MAP()


static Helper helper;


// CTuneHelperDlg 消息处理程序

BOOL CTuneHelperDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_selectMain.SetRange(0, 11);
	m_selectMain.SetLineSize(20);
	m_selectMain.SetTicFreq(1);
	helper = Helper(this);
	IniFile ini;
	if (ReadIniFile(ini))
	{
		m_selectMain.SetPos(ini.pos);
		m_tunemod.SetCurSel((int)ini.tunemode);
		m_chrdmod.SetCurSel((int)ini.chrdmod);
	}
	else
	{
		m_selectMain.SetPos(0);
		m_tunemod.SetCurSel(0);
		m_chrdmod.SetCurSel(0);
	}
	SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); // 窗口始终置顶
	((CButton*)GetDlgItem(IDC_TOPMOST))->SetCheck(BST_CHECKED);
	((CButton*)GetDlgItem(IDC_SHOWUP))->SetCheck(BST_CHECKED);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTuneHelperDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTuneHelperDlg::OnPaint()
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
HCURSOR CTuneHelperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTuneHelperDlg::OnCbnSelchangeTunemod()	// 调性
{
	// TODO: 在此添加控件通知处理程序代码
	helper.Update();
}


void CTuneHelperDlg::OnCbnSelchangeChordmod()	// 和弦种类
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = m_chrdmod.GetCurSel();
	if (nIndex == 0)
	{
		GetDlgItem(IDC_CONVERT1)->EnableWindow(TRUE);
		GetDlgItem(IDC_CONVERT2)->EnableWindow(TRUE);
		GetDlgItem(IDC_CONVERT3)->EnableWindow(FALSE);
		
		helper.SetThird();
	}
	else if (nIndex == 1) 
	{
		GetDlgItem(IDC_CONVERT1)->EnableWindow(TRUE);
		GetDlgItem(IDC_CONVERT2)->EnableWindow(TRUE);
		GetDlgItem(IDC_CONVERT3)->EnableWindow(TRUE);
		helper.SetSeventh();
	}
	else
	{
		GetDlgItem(IDC_CONVERT1)->EnableWindow(FALSE);
		GetDlgItem(IDC_CONVERT2)->EnableWindow(FALSE);
		GetDlgItem(IDC_CONVERT3)->EnableWindow(FALSE);
		helper.SetNinth();
	}
}


void CTuneHelperDlg::OnBnClickedConvert1()	// 第一转位
{
	// TODO: 在此添加控件通知处理程序代码
	int nState = ((CButton*)GetDlgItem(IDC_CONVERT1))->GetCheck();
	if (BST_CHECKED == nState)
	{
		helper.SetConvert1();
		((CButton*)GetDlgItem(IDC_CONVERT2))->SetCheck(BST_UNCHECKED);
		((CButton*)GetDlgItem(IDC_CONVERT3))->SetCheck(BST_UNCHECKED);
	}
	else
		helper.SetConvertNOP();
}


void CTuneHelperDlg::OnBnClickedConvert2()	// 第二转位
{
	// TODO: 在此添加控件通知处理程序代码
	int nState = ((CButton*)GetDlgItem(IDC_CONVERT2))->GetCheck();
	if (BST_CHECKED == nState)
	{
		helper.SetConvert2();
		((CButton*)GetDlgItem(IDC_CONVERT1))->SetCheck(BST_UNCHECKED);
		((CButton*)GetDlgItem(IDC_CONVERT3))->SetCheck(BST_UNCHECKED);
	}
	else
		helper.SetConvertNOP();
}


void CTuneHelperDlg::OnBnClickedConvert3()	// 第三转位
{
	// TODO: 在此添加控件通知处理程序代码
	int nState = ((CButton*)GetDlgItem(IDC_CONVERT3))->GetCheck();
	if (BST_CHECKED == nState)
	{
		helper.SetConvert3();
		((CButton*)GetDlgItem(IDC_CONVERT1))->SetCheck(BST_UNCHECKED);
		((CButton*)GetDlgItem(IDC_CONVERT2))->SetCheck(BST_UNCHECKED);
	}
	else
		helper.SetConvertNOP();
}


void CTuneHelperDlg::OnBnClickedButton1()	// 主音位置
{
	// TODO: 在此添加控件通知处理程序代码
	helper.Update();
}


void CTuneHelperDlg::OnBnClickedButton2()	// 上属调
{
	// TODO: 在此添加控件通知处理程序代码
	helper.SetModParent();
}


void CTuneHelperDlg::OnBnClickedButton3()	// 属调
{
	// TODO: 在此添加控件通知处理程序代码
	helper.SetModChild();
}



void CTuneHelperDlg::OnBnClickedButton4()	// 关系调
{
	// TODO: 在此添加控件通知处理程序代码
	helper.SetModRelated();
}


void CTuneHelperDlg::OnBnClickedButton5()	// 关系上属调
{
	// TODO: 在此添加控件通知处理程序代码
	helper.SetModRelated();
	helper.SetModParent();
}


void CTuneHelperDlg::OnBnClickedButton6()	// 关系属调
{
	// TODO: 在此添加控件通知处理程序代码
	helper.SetModRelated();
	helper.SetModChild();
}


void CTuneHelperDlg::OnBnClickedShowup()
{
	// TODO: 在此添加控件通知处理程序代码
	int nState = ((CButton*)GetDlgItem(IDC_SHOWUP))->GetCheck();
	if (BST_CHECKED == nState)
	{
		helper.SetShowUp();
		m_labels.SetWindowTextA("C	#C	D	#D	E	F	#F	G	#G	A	#A	B");
	}
	else
	{
		helper.SetShowDn();
		m_labels.SetWindowTextA("C	bD	D	bE	E	F	bG	G	bA	A	bB	B");
	}
}


void CTuneHelperDlg::OnNMCustomdrawSelectmain(NMHDR* pNMHDR, LRESULT* pResult)	// 绘制滑块儿时
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	helper.Update();
}


HBRUSH CTuneHelperDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	//if (pWnd->GetDlgCtrlID() == IDC_MAIN)// IDC_Display为所选文本框ID
	//{
	//	pDC->SetTextColor(RGB(255, 255, 255));//设置字体颜色
	//	//pDC->SetBkColor(RGB(0, 255, 255));//设置背景颜色
	//	//pDC->SetBkMode(TRANSPARENT);//设置背景透明             
	//}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CTuneHelperDlg::OnBnClickedTopmost()
{
	// TODO: 在此添加控件通知处理程序代码
	int nState = ((CButton*)GetDlgItem(IDC_TOPMOST))->GetCheck();
	if (BST_CHECKED == nState)
	{
		SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); // 窗口始终置顶
	}
	else
	{
		SetWindowPos(&CWnd::wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); // 窗口始终置顶
	}
}


void CTuneHelperDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	IniFile ini;
	ini.pos = m_selectMain.GetPos();
	ini.tunemode = m_tunemod.GetCurSel();
	ini.chrdmod = m_chrdmod.GetCurSel();
	OutIniFile(ini);
}

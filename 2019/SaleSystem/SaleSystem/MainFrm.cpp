
// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "SaleSystem.h"

#include "MainFrm.h"

#include "InfoFile.h"
#include "CSelectView.h"
#include "CDisplayView.h"
#include "CProfileDlg.h"
#include "CSalemanageDlg.h"
#include "CAddItemDlg.h"
#include "CStoreManageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()

	// 响应自定义消息。当ON_MESSAGE()接收到NM_X消息时会调用OnMyChange()，并将NM_X消息传递给OnMyChange()
	ON_MESSAGE(NM_A, OnMyChange)
	ON_MESSAGE(NM_B, OnMyChange)
	ON_MESSAGE(NM_C, OnMyChange)
	ON_MESSAGE(NM_D, OnMyChange)
	ON_MESSAGE(NM_E, OnMyChange)
	
	ON_COMMAND(ID_32771, &CMainFrame::On32771)
	ON_COMMAND(ID_32772, &CMainFrame::On32772)
	ON_COMMAND(ID_32773, &CMainFrame::On32773)
	ON_COMMAND(ID_32774, &CMainFrame::On32774)
	ON_COMMAND(ID_32775, &CMainFrame::On32775)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
	mainorderinfo = "";
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// Set型API方法 : 设置MainFrame（窗口框架）的初始化风格
	{
		// 设置图标
		SetClassLong(m_hWnd, GCL_HICON, (LONG)AfxGetApp()->LoadIconW(IDI_ICON_TITLE));
		// 设置副标题（右侧标题）
		SetTitle(L"v1.0"); // 主标题在Doc类的OnNewDocument()中设置
		// 设置窗口的初始位置和大小
		MoveWindow(0, 0, 800, 500); 
		CenterWindow(); // 居中窗口（强制忽略上一步设置的初始位置）
	}
	


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	// 手动切分窗口
	m_splitwnd.CreateStatic(this, 1, 2); // 切分成1行2列
	// 放置子窗口
	m_splitwnd.CreateView(0, 0, RUNTIME_CLASS(CSelectView), CSize(200, 500), pContext); // 参数 : 行索引值，列索引值，RUNTIME_CLASS(子窗口类名)，派分的窗口大小，pContext
	m_splitwnd.CreateView(0, 1, RUNTIME_CLASS(CDisplayView), CSize(/*省略参数可自动派分*/), pContext);
	return TRUE;

	// return CFrameWnd::OnCreateClient(lpcs, pContext);
}

// 接收并响应View类中OnTvnSelchanged()发来的NM_X消息
LRESULT CMainFrame::OnMyChange(WPARAM wParam, LPARAM lParam)
{
	CCreateContext Context;
	if (wParam == NM_A) // 挂载IDD_PROFILE对话框
	{
		// 预设将挂载的对话框
		Context.m_pNewViewClass = RUNTIME_CLASS(CProfileDlg);
		Context.m_pCurrentFrame = this;

		// 删除MainFrame右半部分（第1行第2列）的原对话框
		Context.m_pLastView = (CFormView*)m_splitwnd.GetPane(0, 1);
		m_splitwnd.DeleteView(0, 1);
		
		// 在MainFrame的右半部分创建并载入IDD_PROFILE对话框
		m_splitwnd.CreateView(0, 1, RUNTIME_CLASS(CProfileDlg), CSize(), &Context);
		CProfileDlg* pNewView = (CProfileDlg*)m_splitwnd.GetPane(0, 1);
		m_splitwnd.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitwnd.SetActivePane(0, 1);
	}
	else if (wParam == NM_B) // 挂载IDD_SALEMANAGE对话框
	{
		Context.m_pNewViewClass = RUNTIME_CLASS(CSalemanageDlg);
		Context.m_pCurrentFrame = this;

		Context.m_pLastView = (CFormView*)m_splitwnd.GetPane(0, 1);
		m_splitwnd.DeleteView(0, 1);

		m_splitwnd.CreateView(0, 1, RUNTIME_CLASS(CSalemanageDlg), CSize(), &Context);
		CSalemanageDlg* pNewView = (CSalemanageDlg*)m_splitwnd.GetPane(0, 1);
		m_splitwnd.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitwnd.SetActivePane(0, 1);
	}
	else if (wParam == NM_C) // 挂载IDD_STOREMANAGE对话框
	{
		Context.m_pNewViewClass = RUNTIME_CLASS(CStoreManageDlg);
		Context.m_pCurrentFrame = this;

		Context.m_pLastView = (CFormView*)m_splitwnd.GetPane(0, 1);
		m_splitwnd.DeleteView(0, 1);

		m_splitwnd.CreateView(0, 1, RUNTIME_CLASS(CStoreManageDlg), CSize(), &Context);
		CStoreManageDlg* pNewView = (CStoreManageDlg*)m_splitwnd.GetPane(0, 1);
		m_splitwnd.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitwnd.SetActivePane(0, 1);
	}
	else if (wParam == NM_D) // 挂载IDD_ADDITEM对话框
	{
		Context.m_pNewViewClass = RUNTIME_CLASS(CAddItemDlg);
		Context.m_pCurrentFrame = this;

		Context.m_pLastView = (CFormView*)m_splitwnd.GetPane(0, 1);
		m_splitwnd.DeleteView(0, 1);

		m_splitwnd.CreateView(0, 1, RUNTIME_CLASS(CAddItemDlg), CSize(), &Context);
		CAddItemDlg* pNewView = (CAddItemDlg*)m_splitwnd.GetPane(0, 1);
		m_splitwnd.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitwnd.SetActivePane(0, 1);
	}
//	else if (wParam == NM_E)
//	{
//		
//	}

	return 0;
}

// 菜单栏::开始::退出 : 退出程序
void CMainFrame::On32771()
{
	// TODO: 在此添加命令处理程序代码

	exit(0);
}


// 菜单栏::菜单::个人信息 : 挂载IDD_PROFILE对话框
void CMainFrame::On32772()
{
	// TODO: 在此添加命令处理程序代码
	::PostMessageW(AfxGetMainWnd()->GetSafeHwnd(), NM_A, (WPARAM)NM_A, (LPARAM)0); // 发送NM_A消息
	m_tree->SelectItem(sub1); // 同步树控件的选择节点
}

// 菜单栏::菜单::订购 : 挂载IDD_SALEMANAGE对话框
void CMainFrame::On32773()
{
	// TODO: 在此添加命令处理程序代码
	::PostMessageW(AfxGetMainWnd()->GetSafeHwnd(), NM_B, (WPARAM)NM_B, (LPARAM)0); // 发送NM_B消息
	m_tree->SelectItem(sub2); // 同步树控件的选择节点
}

// 菜单栏::菜单::管理库存 : 挂载IDD_STOREMANAGE对话框
void CMainFrame::On32774()
{
	// TODO: 在此添加命令处理程序代码
	::PostMessageW(AfxGetMainWnd()->GetSafeHwnd(), NM_C, (WPARAM)NM_C, (LPARAM)0); // 发送NM_C消息
	m_tree->SelectItem(sub3); // 同步树控件的选择节点
}

// 菜单栏::菜单::更新商品记录 : 挂载IDD_ADDITEM对话框
void CMainFrame::On32775()
{
	// TODO: 在此添加命令处理程序代码
	::PostMessageW(AfxGetMainWnd()->GetSafeHwnd(), NM_D, (WPARAM)NM_D, (LPARAM)0); // 发送NM_D消息
	m_tree->SelectItem(sub4); // 同步树控件的选择节点
}

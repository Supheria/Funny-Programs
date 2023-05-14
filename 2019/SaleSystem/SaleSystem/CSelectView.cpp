// CSelectView.cpp: 实现文件
//

#include "pch.h"
#include "SaleSystem.h"
#include "CSelectView.h"
#include "MainFrm.h"


// CSelectView

CTreeCtrl* m_tree;
HTREEITEM sub1, sub2, sub3, sub4;

IMPLEMENT_DYNCREATE(CSelectView, CTreeView)

CSelectView::CSelectView()
{

}

CSelectView::~CSelectView()
{
}

BEGIN_MESSAGE_MAP(CSelectView, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CSelectView::OnTvnSelchanged)
	/*
	ON_COMMAND(ID_32772, &CSelectView::On32772)
	ON_COMMAND(ID_32773, &CSelectView::On32773)
	ON_COMMAND(ID_32774, &CSelectView::On32774)
	ON_COMMAND(ID_32775, &CSelectView::On32775)
	*/
END_MESSAGE_MAP()


// CSelectView 诊断

#ifdef _DEBUG
void CSelectView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CSelectView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSelectView 消息处理程序


void CSelectView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	// 初始化树控件
	{
		// 获取树控件
		m_tree = &GetTreeCtrl();

		// 准备图片
		HICON icon[] = { AfxGetApp()->LoadIconW(IDI_READ), AfxGetApp()->LoadIconW(IDI_SET) };
		m_imglist.Create(30, 30, ILC_COLOR32, 2, 2);
		m_imglist.Add(icon[0]); m_imglist.Add(icon[1]);
		m_tree->SetImageList(&m_imglist, TVSIL_NORMAL);

		// 添加节点
		sub1 = m_tree->InsertItem(L"个人信息", 0, 1, NULL);
		sub2 = m_tree->InsertItem(L"订购", 0, 1, NULL);
		sub3 = m_tree->InsertItem(L"管理库存", 0, 1, NULL);
		sub4 = m_tree->InsertItem(L"更新商品记录", 0, 1, NULL);
		//m_tree->InsertItem(L"删除商品记录", 0, 1, NULL);

		// 设置默认节点
		m_tree->SelectItem(sub3);
	}
}

// 当前项已修改（树控件）
void CSelectView::OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	
	HTREEITEM item = m_tree->GetSelectedItem(); // 获取当前的选中项
	CString cstr = m_tree->GetItemText(item); // 获取当前项的文本
	
	// 向MainFrame发送当前项的变更消息
	{
		if (cstr == L"个人信息")
		{
			::PostMessageW(AfxGetMainWnd()->GetSafeHwnd(), NM_A, (WPARAM)NM_A, (LPARAM)0); // 发送NM_A消息
			// ::指调用原生API。因为该消息发送属于跨类发送，因此需要调用原生（即底层）API
		}
		else if (cstr == L"订购")
		{
			::PostMessageW(AfxGetMainWnd()->GetSafeHwnd(), NM_B, (WPARAM)NM_B, (LPARAM)0); // 发送NM_B消息
		}
		else if (cstr == L"管理库存")
		{
			::PostMessageW(AfxGetMainWnd()->GetSafeHwnd(), NM_C, (WPARAM)NM_C, (LPARAM)0); // 发送NM_C消息
		}
		else if (cstr == L"更新商品记录")
		{
			::PostMessageW(AfxGetMainWnd()->GetSafeHwnd(), NM_D, (WPARAM)NM_D, (LPARAM)0); // 发送NM_D消息
		}
//		else if (cstr == L"删除商品记录")
//		{
//			::PostMessageW(AfxGetMainWnd()->GetSafeHwnd(), NM_E, (WPARAM)NM_E, (LPARAM)0); // 发送NM_E消息
//		}
	}

}

/*
// 菜单栏::菜单::个人信息 : 挂载IDD_PROFILE对话框
void CSelectView::On32772()
{
	// TODO: 在此添加命令处理程序代码
	::PostMessageW(AfxGetMainWnd()->GetSafeHwnd(), NM_A, (WPARAM)NM_A, (LPARAM)0); // 发送NM_A消息
	m_tree->SelectItem(sub1);
}


// 菜单栏::菜单::订购 : 挂载IDD_SALEMANAGE对话框
void CSelectView::On32773()
{
	// TODO: 在此添加命令处理程序代码
	::PostMessageW(AfxGetMainWnd()->GetSafeHwnd(), NM_B, (WPARAM)NM_B, (LPARAM)0); // 发送NM_B消息
	m_tree->SelectItem(sub2);
}

// 菜单栏::菜单::管理库存 : 挂载IDD_STOREMANAGE对话框
void CSelectView::On32774()
{
	// TODO: 在此添加命令处理程序代码
	::PostMessageW(AfxGetMainWnd()->GetSafeHwnd(), NM_C, (WPARAM)NM_C, (LPARAM)0); // 发送NM_C消息
	m_tree->SelectItem(sub3);
}

// 菜单栏::菜单::更新商品记录 : 挂载IDD_ADDITEM对话框
void CSelectView::On32775()
{
	// TODO: 在此添加命令处理程序代码
	::PostMessageW(AfxGetMainWnd()->GetSafeHwnd(), NM_D, (WPARAM)NM_D, (LPARAM)0); // 发送NM_D消息
	m_tree->SelectItem(sub4);
}
*/

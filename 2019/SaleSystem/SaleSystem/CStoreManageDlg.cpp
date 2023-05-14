// CStoreManageDlg.cpp: 实现文件
//

#include "pch.h"
#include "SaleSystem.h"
#include "CStoreManageDlg.h"
#include "CStoreManageDlg.h"
#include "InfoFile.h"


// CStoreManageDlg

IMPLEMENT_DYNCREATE(CStoreManageDlg, CFormView)

CStoreManageDlg::CStoreManageDlg()
	: CFormView(IDD_STOREMANAGE)
{

}

CStoreManageDlg::~CStoreManageDlg()
{
}

void CStoreManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STOREMANAGE_LIST, m_list);
}

BEGIN_MESSAGE_MAP(CStoreManageDlg, CFormView)
	ON_BN_CLICKED(IDC_STOREMANAGE_DELETEBUTTON, &CStoreManageDlg::OnBnClickedStoremanageDeletebutton)
END_MESSAGE_MAP()


// CStoreManageDlg 诊断

#ifdef _DEBUG
void CStoreManageDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CStoreManageDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CStoreManageDlg 消息处理程序


void CStoreManageDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类


	// 添加表头
	const int colnum = 5;
	CString cstr[colnum] = {L"行数", L"商品ID", L"商品名", L"单价", L"库存" };
	for (int i = 0; i < colnum; i++)
	{
		m_list.InsertColumn(i, cstr[i], LVCFMT_CENTER, 66);
	}

	// 添加正文
	CInfoFile info;
	info.ReadDocline(); // 开始读取商品记录
	int row = 0;
	for (list<msg>::iterator it = info.ls.begin(); it != info.ls.end(); it++, row++) // 遍历商品记录
	{
		int col = 1;
		// 设置行标 : 行号
		m_list.InsertItem(row, CString(to_string(row+1).c_str()));
		// 写入第二列 : 商品ID
		m_list.SetItemText(row, col++, CString(to_string(it->id).c_str()));
		// 写入第三列 : 商品名
		m_list.SetItemText(row, col++, CString(it->name.c_str()));
		// 写入第四列 : 单价
		m_list.SetItemText(row, col++, CString(to_string(it->price).c_str()));
		// 写入第五列 : 库存
		m_list.SetItemText(row, col++, CString(to_string(it->num).c_str()));
	}
	// 设置列表风格
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
}

// 删除按钮::单击 : 删除选中行
void CStoreManageDlg::OnBnClickedStoremanageDeletebutton()
{
	// TODO: 在此添加控件通知处理程序代码

	int row = m_list.GetSelectionMark(); // 获取选中的行号
	// 获取选中行的商品信息
	CString cID = m_list.GetItemText(row, 1);
	CString cname = m_list.GetItemText(row, 2);
	CString cprice = m_list.GetItemText(row, 3);
	CString cnum = m_list.GetItemText(row, 4);

	if (row == -1) // 当前没有选中项
	{
		return;
	}
	CString text = L"确实要删除第" + m_list.GetItemText(row, 0) + "个条目吗？";
	if (MessageBox(text, L"注意：", MB_YESNO) == IDNO)
	{
		return;
	}
	m_list.DeleteItem(row); // 删除选中行
	UpdateData(FALSE);

	CInfoFile info;
	info.DeleteDocline(cID, cname, cprice, cnum);
}

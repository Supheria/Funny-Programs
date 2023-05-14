// CSalemanageDlg.cpp: 实现文件
//

#include "pch.h"
#include "SaleSystem.h"
#include "CSalemanageDlg.h"
#include "InfoFile.h"
#include "MainFrm.h"


// CSalemanageDlg

IMPLEMENT_DYNCREATE(CSalemanageDlg, CFormView)

CSalemanageDlg::CSalemanageDlg()
	: CFormView(IDD_SALEMANAGE)
	, m_storenum(0)
	, m_price(0)
	, m_buynum(0)
	, m_orderinfo(_T(""))
{

}

CSalemanageDlg::~CSalemanageDlg()
{
}

void CSalemanageDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SALEMANAGENAME_COMBO, m_combo);
	DDX_Text(pDX, IDC_SALEMANAGESTORE_EDIT, m_storenum);
	DDX_Text(pDX, IDC_SALEMANAGEPRICE_EDIT, m_price);
	DDX_Text(pDX, IDC_EMANAGENUMBER_EDIT, m_buynum);
	DDX_Text(pDX, IDC_SALEMANAGEORDERINFORMATION_EDIT, m_orderinfo);
}

BEGIN_MESSAGE_MAP(CSalemanageDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_SALEMANAGENAME_COMBO, &CSalemanageDlg::OnCbnSelchangeSalemanagenameCombo)
	ON_BN_CLICKED(IDC_BUY_BUTTON, &CSalemanageDlg::OnBnClickedBuyButton)
	ON_BN_CLICKED(IDC_ALLISMINE, &CSalemanageDlg::OnBnClickedAllismine)
END_MESSAGE_MAP()


// CSalemanageDlg 诊断

#ifdef _DEBUG
void CSalemanageDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSalemanageDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSalemanageDlg 消息处理程序

// 初始化
void CSalemanageDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	// 下拉框
	{
		CInfoFile info;
		info.ReadDocline(); // 开始读取商品记录
		for (list<msg>::iterator it = info.ls.begin(); it != info.ls.end(); it++) // 遍历商品记录
		{
			m_combo.AddString(CString(it->name.c_str()) /*string转CString*/); // 添加下拉项
		}
		m_combo.SetCurSel(0); // 默认当前选中项
		OnCbnSelchangeSalemanagenameCombo(); // 默认项的数据需要首次更新
	}

	// 更新订单数据
	m_orderinfo = mainorderinfo;
	UpdateData(FALSE);
	
}

// m_combo下拉框::已切换当前选中项 : 更新商品其他数据的显示
void CSalemanageDlg::OnCbnSelchangeSalemanagenameCombo()
{
	// TODO: 在此添加控件通知处理程序代码

	int index = m_combo.GetCurSel(); // 获取当前项索引
	CString cname;
	m_combo.GetLBText(index, cname); // 获取当前项文本

	// 比对商品记录以获取相应的商品数据
	CInfoFile info;
	info.ReadDocline(); // 开始读取商品记录
	for (list<msg>::iterator it = info.ls.begin(); it != info.ls.end(); it++) // 遍历商品记录
	{
		if ((CString)it->name.c_str() /*string也可强制转换为CString*/ == cname)
		{
			m_price = it->price; // 获取单价
			m_storenum = it->num; // 获取库存
			UpdateData(FALSE);
		}
	}

}

// BuyButton::单击 : 订购商品
void CSalemanageDlg::OnBnClickedBuyButton()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);
	int index = m_combo.GetCurSel(); // 获取当前项索引
	CString cname;
	m_combo.GetLBText(index, cname); // 获取当前项文本

	int buynum;
	if (m_buynum <= 0) // 购买数量太少
	{
		return;
	}
	if (m_storenum == 0)
	{
		MessageBoxW(L"没有库存。", L"注意：");
		return;
	}
	if (m_buynum > m_storenum) // 购买数量太多（多于库存）
	{
		string text = "库存不足。即将订购" + to_string(m_storenum) + "件" + (string)CW2A/*CString转string（在unicode字符集中）*/(cname.GetString()) + "。";
		if (MessageBoxW(CString(text.c_str()), L"注意：", MB_YESNO) == IDNO)
		{
			//MessageBoxW(L"已取消订购", L"对您说：");
			return;
		}
		buynum = m_storenum;
	}
	else
	{
		string text = "确实要订购" + to_string(m_buynum) + "件" + (string)CW2A/*CString转string（在unicode字符集中）*/(cname.GetString()) + "吗？";
		if (MessageBoxW(CString(text.c_str()), L"对您说：", MB_OKCANCEL) == IDCANCEL)
		{
			
			//MessageBoxW(L"已取消订购", L"对您说：");
			return;
		}
		buynum = m_buynum;
	}
	
	CInfoFile info;
	info.ReadDocline(); // 开始读取商品记录
	for (list<msg>::iterator it = info.ls.begin(); it != info.ls.end(); it++) // 遍历商品记录
	{
		if ((CString)it->name.c_str() == cname) // 购买的商品名称与商品记录一致
		{
			it->num -= buynum; // 商品记录减少相应库存
			m_storenum = it->num; // 库存同步至编辑框

			// 显示订单信息
			string infotext = "订购" + to_string(buynum) + "件 "+ (string)CW2A(cname.GetString()) +"，共花费￥" + to_string(buynum * m_price) + "，剩余" + to_string(m_storenum) + "件\r\n";
			mainorderinfo += CString(infotext.c_str());
			m_orderinfo = mainorderinfo;
			UpdateData(FALSE);
		}
	}
	MessageBox(L"订购成功！", L"对您说"); // 更新商品记录

	info.WriteDocline();
}


void CSalemanageDlg::OnBnClickedAllismine()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int index = m_combo.GetCurSel(); // 获取当前项索引
	CString cname;
	m_combo.GetLBText(index, cname); // 获取当前项文本

	if (m_storenum == 0)
	{
		MessageBoxW(L"没有库存。", L"注意：");
		return;
	}
	string text = "确实要订购全部" + to_string(m_storenum) + "件" + (string)CW2A/*CString转string（在unicode字符集中）*/(cname.GetString()) + "？";
	if (MessageBoxW(CString(text.c_str()), L"对您说：", MB_OKCANCEL) == IDCANCEL)
	{

		//MessageBoxW(L"已取消订购", L"对您说：");
		return;
	}
	
	CInfoFile info;
	info.ReadDocline(); // 开始读取商品记录
	for (list<msg>::iterator it = info.ls.begin(); it != info.ls.end(); it++) // 遍历商品记录
	{
		if ((CString)it->name.c_str() == cname) // 购买的商品名称与商品记录一致
		{
			it->num -= m_storenum; // 商品记录减少相应库存

			// 显示订单信息
			string infotext = "订购" + to_string(m_storenum) + "件 " + (string)CW2A(cname.GetString()) + "，共花费￥" + to_string(m_storenum * m_price) + "，剩余" + to_string(m_storenum) + "件\r\n";
			mainorderinfo += CString(infotext.c_str());
			m_orderinfo = mainorderinfo;
			m_storenum = it->num; // 库存同步至编辑框
			UpdateData(FALSE);
		}
	}
	MessageBox(L"订购成功！", L"对您说"); // 更新商品记录

	info.WriteDocline();
}

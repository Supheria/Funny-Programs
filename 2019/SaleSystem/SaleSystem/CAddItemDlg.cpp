// CAddItemDlg.cpp: 实现文件
//

#include "pch.h"
#include "SaleSystem.h"
#include "CAddItemDlg.h"
#include "InfoFile.h"


// CAddItemDlg

IMPLEMENT_DYNCREATE(CAddItemDlg, CFormView)

CAddItemDlg::CAddItemDlg()
	: CFormView(IDD_ADDITEM)
	, m_showprice(0)
	, m_addnum(0)
	, m_addname(_T(""))
	, m_addprice(0)
	, m_numofnew(0)
	, m_addnumstatetxt(_T(""))
	, m_addgdsstatetxt(_T(""))
	, m_addgdsstatetxt2(_T(""))
	, m_addgdsstatetxt3(_T(""))
{

}

CAddItemDlg::~CAddItemDlg()
{
}

void CAddItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADDITEM_NUMBER_COMBO, m_combo);
	DDX_Text(pDX, IDC_ADDITEM_NUMBER_PRICE_EDIT, m_showprice);
	DDX_Text(pDX, IDC_ADDITEM_NUMBER_NUMBER_EDIT, m_addnum);
	DDX_Text(pDX, IDC_ADDITEM_GOODS_NAME_EDIT, m_addname);
	DDX_Text(pDX, IDC_ADDITEM_GOODS_PRICE_EDIT, m_addprice);
	DDX_Text(pDX, IDC_ADDITEM_GOODS_NUMBER_EDIT, m_numofnew);
	DDX_Control(pDX, IDC_ADDITEM_NUMBER_BUTTON, m_addnumbutt);
	DDX_Control(pDX, IDC_ADDNUM_STATE, m_addnumstatectrl);
	DDX_Text(pDX, IDC_ADDNUM_STATE, m_addnumstatetxt);
	DDX_Control(pDX, IDC__ADDITEM_STATE, m_addgdsstatectrl);
	DDX_Text(pDX, IDC__ADDITEM_STATE, m_addgdsstatetxt);
	DDX_Control(pDX, IDC_ADDITEM_GOODS_BUTTON, m_addgdsbutt);
	DDX_Control(pDX, IDC__ADDITEM_STATE2, m_addgdsstatectrl2);
	DDX_Text(pDX, IDC__ADDITEM_STATE2, m_addgdsstatetxt2);
	DDX_Control(pDX, IDC__ADDITEM_STATE3, m_addgdsstatectrl3);
	DDX_Text(pDX, IDC__ADDITEM_STATE3, m_addgdsstatetxt3);
}

BEGIN_MESSAGE_MAP(CAddItemDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_ADDITEM_NUMBER_COMBO, &CAddItemDlg::OnCbnSelchangeAdditemNumberCombo)
	ON_BN_CLICKED(IDC_ADDITEM_NUMBER_BUTTON, &CAddItemDlg::OnBnClickedAdditemNumberButton)
	ON_EN_SETFOCUS(IDC_ADDITEM_NUMBER_NUMBER_EDIT, &CAddItemDlg::OnEnSetfocusAdditemNumberNumberEdit)
//	ON_EN_CHANGE(IDC_ADDITEM_NUMBER_NUMBER_EDIT, &CAddItemDlg::OnEnChangeAdditemNumberNumberEdit)
//	ON_EN_UPDATE(IDC_ADDITEM_NUMBER_NUMBER_EDIT, &CAddItemDlg::OnEnUpdateAdditemNumberNumberEdit)
ON_BN_CLICKED(IDC_ADDITEM_GOODS_BUTTON, &CAddItemDlg::OnBnClickedAdditemGoodsButton)
ON_EN_SETFOCUS(IDC_ADDITEM_GOODS_NAME_EDIT, &CAddItemDlg::OnEnSetfocusAdditemGoodsNameEdit)
ON_EN_SETFOCUS(IDC_ADDITEM_GOODS_PRICE_EDIT, &CAddItemDlg::OnEnSetfocusAdditemGoodsPriceEdit)
ON_EN_SETFOCUS(IDC_ADDITEM_GOODS_NUMBER_EDIT, &CAddItemDlg::OnEnSetfocusAdditemGoodsNumberEdit)
END_MESSAGE_MAP()


// CAddItemDlg 诊断

#ifdef _DEBUG
void CAddItemDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAddItemDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAddItemDlg 消息处理程序

// 初始化
void CAddItemDlg::OnInitialUpdate()
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
		OnCbnSelchangeAdditemNumberCombo(); // 默认项的数据需要首次更新
	}
}

// m_combo下拉框::已切换当前选中项 : 更新商品其他数据的显示
void CAddItemDlg::OnCbnSelchangeAdditemNumberCombo()
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
			m_showprice = it->price; // 获取单价
			//m_addnum = it->num;
			UpdateData(FALSE);
		}
	}
}

// AdditemNumber添加按钮::单击 : 删增加商品数量
void CAddItemDlg::OnBnClickedAdditemNumberButton()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);
	if (m_addnum == 0)
	{
		m_addnumstatetxt = L"操作禁止";
		m_addnumstatectrl.ShowWindow(SW_SHOWDEFAULT);
		m_addnumbutt.EnableWindow(FALSE);
		UpdateData(FALSE);
		return;
	}

	int index = m_combo.GetCurSel();
	CString cname;
	m_combo.GetLBText(index, cname);
	CInfoFile info;
	info.ReadDocline(); // 开始读取商品记录
	for (list<msg>::iterator it = info.ls.begin(); it != info.ls.end(); it++) // 遍历商品记录
	{
		if (CString(it->name.c_str()) == cname) // 添加相应商品的库存
		{
			if (it->num + m_addnum < 0)
			{
				m_addnumstatetxt = L"库存不足";
				m_addnumstatectrl.ShowWindow(SW_SHOWDEFAULT);
				m_addnumbutt.EnableWindow(FALSE);
				UpdateData(FALSE);
				return;
			}
			string text;
			if (m_addnum < 0)
			{
				text = "已删减" + to_string(-m_addnum) + "件";
			}
			else
			{
				text = "已添加" + to_string(m_addnum) + "件";
			}
			it->num += m_addnum;
			m_addnum = 0;
			m_addnumstatetxt = CString(text.c_str());
			m_addnumstatectrl.ShowWindow(SW_SHOWDEFAULT);
			UpdateData(FALSE);
		}
	}
	info.WriteDocline();
}

// AdditemNumberNumber编辑框::获得焦点
void CAddItemDlg::OnEnSetfocusAdditemNumberNumberEdit()
{
	// TODO: 在此添加控件通知处理程序代码

	m_addnumstatectrl.ShowWindow(SW_HIDE);
	m_addnumbutt.EnableWindow(TRUE);
}

// AdditemGoods添加按钮::单击 : 新增商品
void CAddItemDlg::OnBnClickedAdditemGoodsButton()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);
	if (m_addname.IsEmpty() || m_addprice <= 0 || m_numofnew <= 0)
	{

		m_addgdsstatetxt2 = L"操作禁止";
		m_addgdsstatetxt = m_addgdsstatetxt3 = L"";
		m_addgdsstatectrl.ShowWindow(SW_SHOWDEFAULT);
		m_addgdsstatectrl2.ShowWindow(SW_SHOWDEFAULT);
		m_addgdsstatectrl3.ShowWindow(SW_SHOWDEFAULT);
		m_addgdsbutt.EnableWindow(FALSE);
		UpdateData(FALSE);
		return;
	}

	CInfoFile info;
	info.ReadDocline();
	info.Addline(m_addname, m_addprice, m_numofnew);
	info.WriteDocline();

	// 将物品记录同步到AddNumber的下拉窗口中
	m_combo.InsertString(0, m_addname);
	m_combo.SetCurSel(0);
	OnCbnSelchangeAdditemNumberCombo();

	m_addname = "";
	m_addprice = m_numofnew = 0;
	string text = "添加成功";
	m_addgdsstatetxt2 = CString(text.c_str());
	m_addgdsstatetxt = m_addgdsstatetxt3 = L"";
	m_addgdsstatectrl.ShowWindow(SW_SHOWDEFAULT);
	m_addgdsstatectrl2.ShowWindow(SW_SHOWDEFAULT);
	m_addgdsstatectrl3.ShowWindow(SW_SHOWDEFAULT);
	UpdateData(FALSE);
}


void CAddItemDlg::OnEnSetfocusAdditemGoodsNameEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	m_addgdsstatectrl.ShowWindow(SW_HIDE);
	m_addgdsstatectrl2.ShowWindow(SW_HIDE);
	m_addgdsstatectrl3.ShowWindow(SW_HIDE);
	m_addgdsbutt.EnableWindow(TRUE);
}


void CAddItemDlg::OnEnSetfocusAdditemGoodsPriceEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	m_addgdsstatectrl.ShowWindow(SW_HIDE);
	m_addgdsstatectrl2.ShowWindow(SW_HIDE);
	m_addgdsstatectrl3.ShowWindow(SW_HIDE);
	m_addgdsbutt.EnableWindow(TRUE);
}


void CAddItemDlg::OnEnSetfocusAdditemGoodsNumberEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	m_addgdsstatectrl.ShowWindow(SW_HIDE);
	m_addgdsstatectrl2.ShowWindow(SW_HIDE);
	m_addgdsstatectrl3.ShowWindow(SW_HIDE);
	m_addgdsbutt.EnableWindow(TRUE);
}

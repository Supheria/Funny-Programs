#pragma once



// CAddItemDlg 窗体视图

class CAddItemDlg : public CFormView
{
	DECLARE_DYNCREATE(CAddItemDlg)

protected:
	CAddItemDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CAddItemDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDITEM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CComboBox m_combo;
	int m_showprice;
	int m_addnum;
	CString m_addname;
	int m_addprice;
	int m_numofnew;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnCbnSelchangeAdditemNumberCombo();
	afx_msg void OnBnClickedAdditemNumberButton();
private:
	CButton m_addnumbutt;
	CStatic m_addnumstatectrl;
	CString m_addnumstatetxt;
public:
	afx_msg void OnEnSetfocusAdditemNumberNumberEdit();
//	afx_msg void OnEnChangeAdditemNumberNumberEdit();
//	afx_msg void OnEnUpdateAdditemNumberNumberEdit();
	afx_msg void OnBnClickedAdditemGoodsButton();
private:
	CStatic m_addgdsstatectrl;
	CString m_addgdsstatetxt;
	CButton m_addgdsbutt;
	CStatic m_addgdsstatectrl2;
	CString m_addgdsstatetxt2;
	CStatic m_addgdsstatectrl3;
	CString m_addgdsstatetxt3;
public:
	afx_msg void OnEnSetfocusAdditemGoodsNameEdit();
	afx_msg void OnEnSetfocusAdditemGoodsPriceEdit();
	afx_msg void OnEnSetfocusAdditemGoodsNumberEdit();
};



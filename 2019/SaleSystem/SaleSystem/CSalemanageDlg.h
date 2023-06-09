﻿#pragma once



// CSalemanageDlg 窗体视图

class CSalemanageDlg : public CFormView
{
	DECLARE_DYNCREATE(CSalemanageDlg)

protected:
	CSalemanageDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CSalemanageDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SALEMANAGE };
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
	int m_storenum;
	int m_price;
	int m_buynum;
	CString m_orderinfo;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnCbnSelchangeSalemanagenameCombo();
	afx_msg void OnBnClickedBuyButton();
	afx_msg void OnBnClickedAllismine();
};



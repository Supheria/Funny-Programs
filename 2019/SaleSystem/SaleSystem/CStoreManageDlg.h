#pragma once



// CStoreManageDlg 窗体视图

class CStoreManageDlg : public CFormView
{
	DECLARE_DYNCREATE(CStoreManageDlg)

protected:
	CStoreManageDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CStoreManageDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STOREMANAGE };
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
	CListCtrl m_list;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedStoremanageDeletebutton();
};



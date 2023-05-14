#pragma once



// CProfileDlg 窗体视图

class CProfileDlg : public CFormView
{
	DECLARE_DYNCREATE(CProfileDlg)

protected:
	CProfileDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CProfileDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROFILE };
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
	CString m_career;
	CString m_name;
	CString m_firstpsw;
	CString m_secondpsw;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnEnKillfocusProfilechangepasswordsecondEdit();
//	afx_msg void OnEnSetfocusProfilechangepasswordfirstEdit();
private:
	CEdit m_secondpswctrl;
public:
	afx_msg void OnEnChangeProfilechangepasswordfirstEdit();
	afx_msg void OnEnKillfocusProfilechangepasswordfirstEdit();
private:
	CButton m_fakebutton;
	CStatic m_statectrl;
	CString m_statetxt;
public:
	afx_msg void OnEnSetfocusProfilechangepasswordfirstEdit();
	afx_msg void OnEnSetfocusProfilechangepasswordsecondEdit();
	afx_msg void OnStnClickedStateupText();
private:
	CStatic m_stateupctrl;
	CString m_stateuptxt;
public:
	afx_msg void OnEnChangeProfilechangepasswordsecondEdit();
};



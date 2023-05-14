#pragma once


// CLoginDlg 对话框

class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CLoginDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CString m_name;
	CString m_psw;
public:
	afx_msg void OnBnClickedLoginokButton();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedLogincancelButton();
	virtual void OnOK();
	afx_msg void OnClose();
};

#pragma once


// CInfoDlg 对话框

class CInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInfoDlg)

public:
	CInfoDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CInfoDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	afx_msg void OnBnClickedAdd();
	virtual BOOL OnInitDialog();
public:
	CListCtrl m_list;
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedSave();
};

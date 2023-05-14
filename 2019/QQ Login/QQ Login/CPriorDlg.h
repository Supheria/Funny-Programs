#pragma once


// CPriorDlg 对话框

class CPriorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPriorDlg)

public:
	CPriorDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPriorDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PRIORITY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedModify();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual void OnCancel();
private:
	void ReadUser(CListCtrl* pList);
	bool istemp = true;
};


// QQ LoginDlg.h: 头文件
//

#pragma once
#include "CLoginDlg.h"
#include "CPriorDlg.h"

// CQQLoginDlg 对话框
class CQQLoginDlg : public CDialogEx
{
// 构造
public:
	CQQLoginDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedRelogin();
	afx_msg void OnBnClickedAdmin();
private:
	void Login();
public:
	afx_msg void OnBnClickedInfo();
	afx_msg void OnBnClickedBackcolor();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg void OnDestroy();
};

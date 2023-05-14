
// _10to15Dlg.h: 头文件
//

#pragma once


// C_10to15Dlg 对话框
class C_10to15Dlg : public CDialogEx
{
// 构造
public:
	C_10to15Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD__10TO15_DIALOG };
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
public:
	CEdit m_scale;
//	afx_msg void OnEnChangeEditScale();
//	afx_msg void OnBnClickedOk();
	CEdit m_ori;
	CEdit m_times;
	CEdit m_add;
	CListCtrl m_list;
	afx_msg void OnBnClickedButtonGo();
	afx_msg void OnBnClickedTopmost();
	virtual void OnOK();
	afx_msg void OnClose();
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	afx_msg void OnHdnItemclickList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMClickList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg void OnDestroy();
	void UpdateWindow();
};

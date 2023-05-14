
// TuneHelperDlg.h: 头文件
//

#pragma once
#include "CMySlider.h"

// CTuneHelperDlg 对话框
class CTuneHelperDlg : public CDialogEx
{
// 构造
public:
	CTuneHelperDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TUNEHELPER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_chords[7];
	CEdit m_pots[7];
	CComboBox m_tunemod;
	afx_msg void OnCbnSelchangeTunemod();
	CComboBox m_chrdmod;
	afx_msg void OnCbnSelchangeChordmod();
	afx_msg void OnBnClickedConvert1();
	afx_msg void OnBnClickedConvert2();
	afx_msg void OnBnClickedConvert3();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedShowup();
	CSliderCtrl m_selectMain;
	afx_msg void OnNMCustomdrawSelectmain(NMHDR* pNMHDR, LRESULT* pResult);
	CEdit m_main;
	CEdit m_child;
	CEdit m_parent;
	CEdit m_related;
	CEdit m_rParent;
	CEdit m_rChild;
	CStatic m_labels;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedTopmost();
	CStatic m_label[7];
	CStatic m_tunelabelUP;
	CStatic m_tunelabelDN;
	afx_msg void OnDestroy();
};

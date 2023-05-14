#pragma once


// CVerifyDlg 对话框

class CVerifyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVerifyDlg)

public:
	CVerifyDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CVerifyDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VERIFY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	INT_PTR DoMyModal(CString name, CString pass);
private:
	CString m_name;
	CString m_pass;
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
};

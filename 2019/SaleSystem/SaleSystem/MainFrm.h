
// MainFrm.h: CMainFrame 类的接口
//

#pragma once
//#include <string>

// 定义树控件的五个选项所对应的消息常量
#define NM_A (WM_USER + 100) // 系统消息常量+任意数字 : 防止自定义消息与系统消息冲突
#define NM_B (WM_USER + 101)
#define NM_C (WM_USER + 102)
#define NM_D (WM_USER + 103)
#define NM_E (WM_USER + 104)

static CString mainorderinfo;

class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CStatusBar        m_wndStatusBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

private:
	CSplitterWnd m_splitwnd; // 创建切分窗口类对象

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	afx_msg LRESULT OnMyChange(WPARAM wParam, LPARAM lParam); // 在头文件中声明OnMyChange()
	
public:
	
	afx_msg void On32771();
	afx_msg void On32772();
	afx_msg void On32773();
	afx_msg void On32774();
	afx_msg void On32775();
};



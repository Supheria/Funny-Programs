#pragma once


// CSelectView 视图

extern CTreeCtrl* m_tree; // 创建树控件类对象
extern HTREEITEM sub1, sub2, sub3, sub4;

class CSelectView : public CTreeView
{
	DECLARE_DYNCREATE(CSelectView)

protected:
	CSelectView();           // 动态创建所使用的受保护的构造函数
	virtual ~CSelectView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

private:
	//CTreeCtrl* m_tree; // 创建树控件类对象
	CImageList m_imglist; // 创建图标列表类对象
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	/*
	afx_msg void On32772();
	afx_msg void On32773();
	afx_msg void On32774();
	afx_msg void On32775();
	*/
	
};



#pragma once
#include <afxcmn.h>
class CMySlider :
	public CSliderCtrl
{
	DECLARE_DYNAMIC(CMySlider)
public:
	CMySlider();
	virtual ~CMySlider();
protected:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void CustDraw(CDC* pDc);
	DECLARE_MESSAGE_MAP()
};


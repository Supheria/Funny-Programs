#include "pch.h"
#include "CMySlider.h"

IMPLEMENT_DYNAMIC(CMySlider, CSliderCtrl)

CMySlider::CMySlider()
{

}


CMySlider::~CMySlider()
{
}


BEGIN_MESSAGE_MAP(CMySlider, CSliderCtrl)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


void CMySlider::OnPaint()
{
	CSliderCtrl::OnPaint();
	CDC* pDc = this->GetDC();
	CustDraw(pDc);
}

void CMySlider::OnLButtonDown(UINT nFlags, CPoint point)
{
	CSliderCtrl::OnLButtonDown(nFlags, point);
	CRect   rectClient, rectChannel;
	GetClientRect(rectClient);
	GetChannelRect(rectChannel);
	int nMax = 0;
	int nMin = 0;
	GetRange(nMin, nMax);
	int nPos = (nMax - nMin) * (point.x - rectClient.left - rectChannel.left) / (rectChannel.right - rectChannel.left);
	SetPos(nPos);
}

#define SlIDER_BK_COLOR RGB(192, 192, 192)
#define SLIDER_LEFT_COLOR RGB(148, 40, 255)
#define SLIDER_THUMB_COLOR RGB(240, 240, 240)
#define DIALOG_BKCOLOR RGB(201,227,253)

void CMySlider::CustDraw(CDC* pDc)
{
	COLORREF colorLeft(SLIDER_LEFT_COLOR);

	COLORREF colorChannel(SlIDER_BK_COLOR);
	CPen penChannel(PS_DASHDOTDOT, 2, colorChannel);
	CBrush brushChannel;
	brushChannel.CreateSolidBrush(colorChannel);

	COLORREF colorThumb(SLIDER_THUMB_COLOR);
	CPen penThumb(PS_DASHDOTDOT, 2, colorThumb);
	CBrush brushThumb;
	brushThumb.CreateSolidBrush(colorThumb);


	CRect clientRect;
	GetClientRect(clientRect);

	CRect channelRect;
	GetChannelRect(&channelRect);

	//clientRect.bottom /= 2; 

	pDc->SetBkMode(TRANSPARENT);

	pDc->FillSolidRect(clientRect, DIALOG_BKCOLOR);

	clientRect.left = channelRect.left;
	clientRect.right = channelRect.right;

	pDc->FillSolidRect(clientRect, colorChannel);

	pDc->Draw3dRect(clientRect, colorChannel, colorChannel);

	CRect thumbRect;
	GetThumbRect(thumbRect);

	thumbRect.bottom *= 2;

	CRect leftRect;
	leftRect.left = clientRect.left;
	leftRect.top = clientRect.top;
	leftRect.bottom = clientRect.bottom;
	leftRect.right = thumbRect.left;


	pDc->SelectObject(&brushThumb);
	pDc->SelectObject(&penThumb);

	pDc->FillSolidRect(leftRect, colorLeft);

	pDc->Draw3dRect(leftRect, colorLeft, colorLeft);

	pDc->Ellipse(thumbRect);
}
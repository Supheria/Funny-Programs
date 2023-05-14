// CLoginDlg.cpp: 实现文件
//

#include "pch.h"
#include "QQ Login.h"
#include "CLoginDlg.h"
#include "afxdialogex.h"

//extern CQQLoginApp theApp;


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN, pParent)
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HIDEORSEE, m_hideorsee);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CLoginDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_HIDEORSEE, &CLoginDlg::OnBnClickedHideorsee)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


void CLoginDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	if (CheckUser())
	{
		CDialogEx::OnOK();
	}
	else
	{
		AfxMessageBox("用户名或密码错误");
		//SetDlgItemText(IDC_NAME, "");
		SetDlgItemText(IDC_PASS, "");
		GetDlgItem(IDC_PASS)->SetFocus();
	}
	
}


void CLoginDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

// File inf;
// inf.m_hFile成员变量 :
// -1(0xffffffff) 或 4G-1 : 未打开文件
//
// 读取失败 : 最有可能是因为指定文件（夹）不存在
// 保存失败 : 最有可能是因为文件是只读文件 或 磁盘设置成了禁止写入的安全模式

BOOL CLoginDlg::CheckUser() // 检查用户记录
{
	// TODO: 在此处添加实现代码.

	CFile file;
	//if (!inf.Open(_USER_DAT_, CFile::modeRead | CFile::modeNoTruncate | CFile::shareDenyNone)) // 第一位用户
	file.Open(_USER_DAT_, CFile::modeRead /*| CFile::modeNoTruncate*/ | CFile::shareDenyNone);
	if (-1 == (int)file.m_hFile)
	{
		CreateUser();
		this->EndDialog(IDOK);
		return TRUE;
	}

	CString szName, szPass;
	GetDlgItemText(IDC_NAME, szName);
	GetDlgItemText(IDC_PASS, szPass);
	szName.MakeLower();
	SUser u; int item = 0;
	while (file.Read(&u, sizeof(u)) == sizeof(u))
	{
		if (szName == u.m_name && szPass == u.m_pass)
		{
			theApp.gUser = u;
			return TRUE;
		}
		item++;
	}
	if (!item) // 第一位用户
	{
		theApp.gUser = { "临时用户", "", -1 };
		this->EndDialog(IDOK);
		return TRUE;
	}

	return FALSE;
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CheckUser();

	HBITMAP	hBmpHide = ::LoadBitmapA(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_HIDE));
	m_hideorsee.SetBitmap(hBmpHide);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CLoginDlg::CreateUser()
{
	// TODO: 在此处添加实现代码.

	CFile createf;
	if (!(createf.Open(_USER_DAT_, CFile::modeCreate)))
	{
		AfxMessageBox("无法创建用户文件！", MB_OKCANCEL);
		theApp.gUser = { "临时用户", "", 0 };
	}
	else
	{
		theApp.gUser = { "临时用户", "", -1 };
	}
}


void CLoginDlg::OnBnClickedHideorsee()
{
	// TODO: 在此添加控件通知处理程序代码

	if (ishide)
	{
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_PASS);
		pEdit->SetPasswordChar(0); // 显示格式为明文
		pEdit->Invalidate(); // 更新窗口

		HBITMAP	hBmpHide = ::LoadBitmapA(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_SEE)); // 获取位图句柄
		m_hideorsee.SetBitmap(hBmpHide); // 设置按钮图片
		ishide = false;
	}
	else
	{
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_PASS);
		pEdit->SetPasswordChar('*'); // 显示格式为星号
		pEdit->Invalidate(); // 更新窗口

		HBITMAP	hBmpHide = ::LoadBitmapA(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_HIDE)); // 获取位图句柄
		m_hideorsee.SetBitmap(hBmpHide); // 设置按钮图片
		ishide = true;
	}

	
}


HBRUSH CLoginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (nCtlColor)
	{
	case CTLCOLOR_DLG: //更改对话框背景色
	{
		HBRUSH b = CreateSolidBrush(theApp.m_backcolor);
		return b;
	}
	case CTLCOLOR_STATIC:
	{
		// 反色
		COLORREF B = 0xff - (theApp.m_backcolor >> 16); // 高位 : 蓝
		COLORREF G = 0xff - (theApp.m_backcolor << 16 >> 24); // 中位 : 绿
		COLORREF R = 0xff - (theApp.m_backcolor << 24 >> 24); // 低位 : 红
		COLORREF versecol = (B << 16) + (G << 8) + R;
		pDC->SetTextColor(versecol);  //字体颜色
		pDC->SetBkColor(theApp.m_backcolor);   //字体背景色
	}
	default:
		return hbr;
	}
}

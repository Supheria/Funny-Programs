
// DecoderDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Decoder.h"
#include "DecoderDlg.h"
#include "afxdialogex.h"
#include "tools.h"
#include <fstream>
#include <ctime>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDecoderDlg 对话框



CDecoderDlg::CDecoderDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DECODER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDecoderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDecoderDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ENCODER, &CDecoderDlg::OnBnClickedEncoder)
	ON_BN_CLICKED(IDC_DECODER, &CDecoderDlg::OnBnClickedDecoder)
	ON_BN_CLICKED(IDC_DECODEFILE, &CDecoderDlg::OnBnClickedDecodefile)
	ON_BN_CLICKED(IDC_ENCODEFILE, &CDecoderDlg::OnBnClickedEncodefile)
	ON_BN_CLICKED(IDC_GETCODE, &CDecoderDlg::OnBnClickedGetcode)
END_MESSAGE_MAP()


// CDecoderDlg 消息处理程序

BOOL CDecoderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDecoderDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDecoderDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDecoderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDecoderDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CDecoderDlg::OnBnClickedEncoder()
{
	// TODO: 在此添加控件通知处理程序代码
	using namespace std; using namespace tools;
	CString str;
	GetDlgItemText(IDC_INPUT, str);
	auto vStr = SplitString(str.GetString(), "\r\n");
	string result;
	for (int i = 0; i < vStr.size(); i++)
	{
		//vStr[i] += "\n";
		encoder(vStr[i]);
		result += vStr[i];
		result += "\r\n";
	}
	SetDlgItemText(IDC_OUTPUT, result.c_str());
}


void CDecoderDlg::OnBnClickedDecoder()
{
	// TODO: 在此添加控件通知处理程序代码
	using namespace std; using namespace tools;
	CString str;
	GetDlgItemText(IDC_INPUT, str);
	auto vStr = SplitString(str.GetString(), "\r\n");
	string result;
	for (int i = 0; i < vStr.size(); i++)
	{
		//vStr[i] += "\n";
		decoder(vStr[i]);
		result += vStr[i];
		result += "\r\n";
	}
	SetDlgItemText(IDC_OUTPUT, result.c_str());
}


void CDecoderDlg::OnBnClickedDecodefile()
{
	// TODO: 在此添加控件通知处理程序代码
	using namespace std; using namespace tools;
	CFileDialog dlg(TRUE);
	dlg.DoModal();
	CString path = dlg.GetPathName();
	ifstream fin(path);
	ofstream fout(path + "_decode");
	if (fin.is_open())
	{
		string result = "【解码】\r\n";
		string szOri;
		while (fin.peek() != EOF)
		{
			string line;
			getline(fin, line);
			szOri += line;
			szOri += "\r\n";
			decoder(line);
			fout << line << endl;
			result += line;
			result += "\r\n";
		}
		result += "\r\n\r\n原文：\r\n";
		result += szOri;
		SetDlgItemText(IDC_OUTPUT, result.c_str());
	}
	else 
		MessageBox("无法解码文件！");
}


void CDecoderDlg::OnBnClickedEncodefile()
{
	// TODO: 在此添加控件通知处理程序代码
	using namespace std; using namespace tools;
	CFileDialog dlg(TRUE);
	dlg.DoModal();
	CString path = dlg.GetPathName();
	ifstream fin(path);
	ofstream fout(path + "_encode");
	if (fin.is_open() && fout.is_open())
	{
		string result = "【编码】\r\n";
		string szOri;
		while (fin.peek() != EOF)
		{
			string line;
			getline(fin, line);
			szOri += line;
			szOri += "\r\n";
			encoder(line);
			fout << line << endl;
			result += line;
			result += "\r\n";
		}
		result += "\r\n\r\n原文：\r\n";
		result += szOri;
		SetDlgItemText(IDC_OUTPUT, result.c_str());
	}
	else
		MessageBox("无法编码文件！");
}

void CDecoderDlg::OnBnClickedGetcode()
{
	// TODO: 在此添加控件通知处理程序代码
	using namespace std; using namespace tools;
	typedef time_t span1970;
#pragma region 获取文件夹路径
	BROWSEINFO bi;
	bi.hwndOwner = NULL;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = NULL;
	bi.lpszTitle = NULL;
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.iImage = 0;
	LPCITEMIDLIST pidl = SHBrowseForFolder(&bi);
	if (!pidl) { return; }
	TCHAR szPath[255];
	SHGetPathFromIDList(pidl, szPath);
#pragma endregion
	CString path(szPath);
	string pass = path + "\\passport";
	string adva = path + "\\advance";
	string reg = path;
	reg.erase(reg.length() - 10, 12);
	reg += "ini\\svreg.reg";
	struct {
		int m_num; // 身份编号
		int m_status; // 身份状态
		span1970 m_settime; // 存档设立时间
		string m_name; // 名称
		int m_career; // 职业
		string m_vrfcode; // 效验码
		span1970 m_edittime; // 编辑时间
		int m_moral; // 道德值
		int m_3Q[3]; // 三商
		int m_wealth; // 财富
		std::string SetVrfcode(int m_pos)
		{
			int a = (m_num % (m_pos ? m_pos : 1)) + m_status + (m_edittime % (m_settime ? m_settime : 1)) + m_career + m_moral + m_3Q[0] + m_3Q[1] + m_3Q[2];
			string code = to_string((m_wealth * a) % ((m_wealth + a) ? (m_wealth + a) : 1)) + m_name;
			return code;
		}
		int GetPos(std::string path)
		{
			using namespace std; using namespace tools;
			ifstream fin(path);
			if (fin.is_open())
			{
				for (int pos = 1; fin.peek() != EOF; pos++)
				{
					string clause;
					getline(fin, clause);
					decoder(clause);
					auto vClause = SplitString(clause, "><");
					if (vClause[1] == to_string(0))
					{
						break;
					}
					else if (vClause[0] == to_string(m_num))
					{
						return pos;
					}
				}
				return 0;
			}
			return 0;
		}
		bool readinfo(string pass, string adva)
		{
			using namespace std;
			ifstream readpass(pass);
			ifstream readadva(adva);
			if (readpass.is_open() && readadva.is_open())
			{
				string num; getline(readpass, num); m_num = (atoi(num.c_str())); // 身份编号
				string sta; getline(readpass, sta); m_status = (atoi(sta.c_str())); // 身份状态
				string stt; getline(readpass, stt); m_settime = _atoi64(stt.c_str()); // 存档设立时间
				getline(readpass, m_name); // 名称
				string crr; getline(readpass, crr); m_career = atoi(crr.c_str()); // 职业
				getline(readadva, m_vrfcode); // 效验码
				string edt; getline(readadva, edt); m_edittime = _atoi64(edt.c_str()); // 编辑时间
				string mor; getline(readadva, mor); m_moral = atoi(mor.c_str()); // 道德值
				string IQ; getline(readadva, IQ); m_3Q[0] = atoi(IQ.c_str()); // IQ
				string HQ; getline(readadva, HQ); m_3Q[1] = atoi(HQ.c_str()); // HQ
				string EQ; getline(readadva, EQ); m_3Q[2] = atoi(EQ.c_str()); // EQ
				string wea; getline(readadva, wea); m_wealth = atoi(wea.c_str()); // 财富
				return true;
			}
			else
				return false;
		}
	} save;
	
	vector<string> content;
	if (save.readinfo(pass, adva))
	{
		if (int pos = save.GetPos(reg))
		{
			CString szRes;
			string code = save.SetVrfcode(pos);
			szRes = "存档效验码\r\n\r\n来自存档记录：" + (CString)encoder(save.m_vrfcode).c_str() + "   解密后：" + (CString)decoder(save.m_vrfcode).c_str() + "\r\n计算得到：" + (CString)decoder(code).c_str() + "   加密后：" + (CString)encoder(code).c_str();
			if (save.m_vrfcode == encoder(code))
			{
				szRes += "\r\n\r\n效验码与StoryGame++的算法结果匹配";
			}
			else
			{
				szRes += "\r\n\r\n效验码有误";
			}
			SetDlgItemText(IDC_OUTPUT, szRes);
			return;
		}
	}
	SetDlgItemText(IDC_OUTPUT, "无法计算验证码");

}

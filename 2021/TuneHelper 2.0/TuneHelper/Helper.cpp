#include "pch.h"
#include "Helper.h"
#include "resource.h"


void Helper::Check()	// 检索关键信息
{
	pos = m_dlg->m_selectMain.GetPos();	// 主调位置
	int nIndex = m_dlg->m_tunemod.GetCurSel();	// 调性
	if (nIndex == 0) { tunemode = main; } else if (nIndex == 1) { tunemode = mini; } else tunemode = chrdmn;
	nIndex = m_dlg->m_chrdmod.GetCurSel();	// 和弦类型
	if (nIndex == 0) { chrdmod = third; } else if (nIndex == 1) { chrdmod = seventh; } else chrdmod = ninth;
}

Helper::Helper(CTuneHelperDlg* dlg)
{
	m_dlg = dlg;
}


Helper::~Helper()
{
	//delete[] *notes;
	//*notes = NULL;
}

void Helper::Update()
{
	Check();
	WritePots();
	WriteChords();
}

void Helper::WritePots()	// 写入槽
{
	m_dlg->GetDlgItem(IDC_MAIN)->SetWindowTextA(tunes[sp][pos]);
	int i;
	i = pos + 5;  m_dlg->GetDlgItem(IDC_PARENT)->SetWindowTextA(tunes[sp][i % 12]);
	i = pos + 7;  m_dlg->GetDlgItem(IDC_CHILD)->SetWindowTextA(tunes[sp][i % 12]);
	if (main == tunemode)
	{
		i = pos + 9; m_dlg->GetDlgItem(IDC_RELATION)->SetWindowTextA(tunes[sp][i % 12]);
		i = pos + 2; m_dlg->GetDlgItem(IDC_RPARENT)->SetWindowTextA(tunes[sp][i % 12]);
		i = pos + 4; m_dlg->GetDlgItem(IDC_RCHILD)->SetWindowTextA(tunes[sp][i % 12]);
	}
	else
	{
		i = pos + 3; m_dlg->GetDlgItem(IDC_RELATION)->SetWindowTextA(tunes[sp][i % 12]);
		i = pos + 8; m_dlg->GetDlgItem(IDC_RPARENT)->SetWindowTextA(tunes[sp][i % 12]);
		i = pos + 10; m_dlg->GetDlgItem(IDC_RCHILD)->SetWindowTextA(tunes[sp][i % 12]);
	}
	for (int i = 0, j[7]; i < sizeof(m_dlg->m_pots) / sizeof(m_dlg->m_pots[0]); i++)	// 按调性（大小调）写出音阶
	{
		j[i] = Mm[tunemode][i] + pos;
		m_dlg->m_pots[i].SetWindowTextA(tunes[sp][j[i] % 12]);
	}
	CString labels[2][7] = {
		{"Ⅰ", "ⅱ", "ⅲ", "Ⅳ", "Ⅴ", "ⅵ", "ⅶ°" },
		{"ⅰ", "ⅱ°", "Ⅲ", "ⅳ", "ⅴ", "Ⅵ", "Ⅶ" }
	};
	if (main == tunemode)
	{
		for (int i = 0; i < sizeof(m_dlg->m_label) / sizeof(m_dlg->m_label[0]); i++)
		{
			m_dlg->m_label[i].SetWindowTextA(labels[0][i]);
		}
		m_dlg->m_tunelabelUP.SetWindowTextA("大调");
		if (chrdmn == m_dlg->m_tunemod.GetCurSel())
			m_dlg->m_tunelabelDN.SetWindowTextA("和声小调");
		else
			m_dlg->m_tunelabelDN.SetWindowTextA("小调");
	}
	else
	{

		for (int i = 0; i < sizeof(m_dlg->m_label) / sizeof(m_dlg->m_label[0]); i++)
		{
			m_dlg->m_label[i].SetWindowTextA(labels[1][i]);
		}
		if (chrdmn == tunemode)
			m_dlg->m_tunelabelUP.SetWindowTextA("和声小调");
		else
			m_dlg->m_tunelabelUP.SetWindowTextA("小调");
		m_dlg->m_tunelabelDN.SetWindowTextA("大调");
	}
}


void Helper::WriteChords()	// 写入和弦
{
	CString pTunes[12];
	for (int i = 0, j = pos; i < sizeof(tunes[sp]) / sizeof(tunes[sp][0]); i++, j++)	// 以主调位置为第0个，重新排列十二音阶
	{
		pTunes[i] = tunes[sp][j = j < 12 ? j : 0];
	}
	
	for (int i = 0; i < sizeof(m_dlg->m_chords) / sizeof(m_dlg->m_chords[0]); i++)	// 重置和弦列表
	{
		m_dlg->m_chords[i].ResetContent();
	}
	for (int i = 0; i < sizeof(m_dlg->m_chords) / sizeof(m_dlg->m_chords[0]); i++)	// 写出和弦于和弦列表
	{
		int k = i;
		m_dlg->m_chords[i].AddString(pTunes[Mm[tunemode][k]]);	// 根音
		m_dlg->m_chords[i].SetCurSel(0);
		k += 2;
		for (int j = 1; j < chrdmod; j++)
		{
			if (convert == j)	// 转位后所在低音
			{
				int nIndex = m_dlg->m_chords[i].GetCount();
				m_dlg->m_chords[i].InsertString(nIndex, pTunes[Mm[tunemode][k % 7]]);
			}
			else
				m_dlg->m_chords[i].InsertString(0, pTunes[Mm[tunemode][k % 7]]);
			k += 2;
		}
	}
}


void Helper::SetConvertNOP()
{
	convert = convertNOP;
	WriteChords();
}

void Helper::SetConvert1()
{
	convert = convert1;
	WriteChords();
}

void Helper::SetConvert2()
{
	convert = convert2;
	WriteChords();
}

void Helper::SetConvert3()
{
	convert = convert3;
	WriteChords();
}


void Helper::SetModChild()
{
	pos += 7;
	pos = pos % 12;
	WritePots();
	WriteChords();
}

void Helper::SetModParent()
{
	pos += 5;
	pos %= 12;
	WritePots();
	WriteChords();
}

void Helper::SetModRelated()
{
	if (main == tunemode)
	{
		pos += 9;
		pos %= 12;
		if (chrdmn == m_dlg->m_tunemod.GetCurSel())
			tunemode = chrdmn;
		else
			tunemode = mini;
	}
	else
	{
		pos += 3;
		pos %= 12;
		tunemode = main;
	}
	WritePots();
	WriteChords();
}

void Helper::SetShowDn()
{
	sp = false;
	WritePots();
	WriteChords();
}

void Helper::SetShowUp()
{
	sp = true;
	WritePots();
	WriteChords();
}

void Helper::SetThird()
{
	int nState = ((CButton*)m_dlg->GetDlgItem(IDC_CONVERT3))->GetCheck();
	if (BST_CHECKED == nState)
	{
		((CButton*)m_dlg->GetDlgItem(IDC_CONVERT3))->SetCheck(BST_UNCHECKED);
		convert = convertNOP;
	}
	chrdmod = third;
	WriteChords();
}

void Helper::SetSeventh()
{
	chrdmod = seventh;
	WriteChords();
}

void Helper::SetNinth()
{
	((CButton*)m_dlg->GetDlgItem(IDC_CONVERT1))->SetCheck(BST_UNCHECKED);
	((CButton*)m_dlg->GetDlgItem(IDC_CONVERT2))->SetCheck(BST_UNCHECKED);
	((CButton*)m_dlg->GetDlgItem(IDC_CONVERT3))->SetCheck(BST_UNCHECKED);
	convert = convertNOP;
	chrdmod = ninth;
	WriteChords();
}
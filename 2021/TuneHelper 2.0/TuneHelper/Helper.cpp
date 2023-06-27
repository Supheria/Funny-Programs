#include "pch.h"
#include "Helper.h"
#include "resource.h"


void Helper::Check()	// �����ؼ���Ϣ
{
	pos = m_dlg->m_selectMain.GetPos();	// ����λ��
	int nIndex = m_dlg->m_tunemod.GetCurSel();	// ����
	if (nIndex == 0) { tunemode = main; } else if (nIndex == 1) { tunemode = mini; } else tunemode = chrdmn;
	nIndex = m_dlg->m_chrdmod.GetCurSel();	// ��������
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

void Helper::WritePots()	// д���
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
	for (int i = 0, j[7]; i < sizeof(m_dlg->m_pots) / sizeof(m_dlg->m_pots[0]); i++)	// �����ԣ���С����д������
	{
		j[i] = Mm[tunemode][i] + pos;
		m_dlg->m_pots[i].SetWindowTextA(tunes[sp][j[i] % 12]);
	}
	CString labels[2][7] = {
		{"��", "��", "��", "��", "��", "��", "����" },
		{"��", "����", "��", "��", "��", "��", "��" }
	};
	if (main == tunemode)
	{
		for (int i = 0; i < sizeof(m_dlg->m_label) / sizeof(m_dlg->m_label[0]); i++)
		{
			m_dlg->m_label[i].SetWindowTextA(labels[0][i]);
		}
		m_dlg->m_tunelabelUP.SetWindowTextA("���");
		if (chrdmn == m_dlg->m_tunemod.GetCurSel())
			m_dlg->m_tunelabelDN.SetWindowTextA("����С��");
		else
			m_dlg->m_tunelabelDN.SetWindowTextA("С��");
	}
	else
	{

		for (int i = 0; i < sizeof(m_dlg->m_label) / sizeof(m_dlg->m_label[0]); i++)
		{
			m_dlg->m_label[i].SetWindowTextA(labels[1][i]);
		}
		if (chrdmn == tunemode)
			m_dlg->m_tunelabelUP.SetWindowTextA("����С��");
		else
			m_dlg->m_tunelabelUP.SetWindowTextA("С��");
		m_dlg->m_tunelabelDN.SetWindowTextA("���");
	}
}


void Helper::WriteChords()	// д�����
{
	CString pTunes[12];
	for (int i = 0, j = pos; i < sizeof(tunes[sp]) / sizeof(tunes[sp][0]); i++, j++)	// ������λ��Ϊ��0������������ʮ������
	{
		pTunes[i] = tunes[sp][j = j < 12 ? j : 0];
	}
	
	for (int i = 0; i < sizeof(m_dlg->m_chords) / sizeof(m_dlg->m_chords[0]); i++)	// ���ú����б�
	{
		m_dlg->m_chords[i].ResetContent();
	}
	for (int i = 0; i < sizeof(m_dlg->m_chords) / sizeof(m_dlg->m_chords[0]); i++)	// д�������ں����б�
	{
		int k = i;
		m_dlg->m_chords[i].AddString(pTunes[Mm[tunemode][k]]);	// ����
		m_dlg->m_chords[i].SetCurSel(0);
		k += 2;
		for (int j = 1; j < chrdmod; j++)
		{
			if (convert == j)	// תλ�����ڵ���
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
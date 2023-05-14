#include "pch.h"
#include "Helper.h"
#include "resource.h"


Helper::Helper(CString tune)
{
	for (int i = 0; i < sizeof(tunes) / sizeof(tunes[0]); i++)
	{
		if (tunes[i][0] == tune)
		{
			is_found = true;
			pot = i;
			break;
		}
	}
}


Helper::~Helper()
{
}


void Helper::WritePot(CTuneHelperDlg * dlg)
{
	if (is_found)
	{
		for (int i = 0; i < sizeof(dlg->m_pots) / sizeof(dlg->m_pots[0]); i++)
		{
			dlg->m_pots[i].SetWindowTextA(tunes[pot][Mm[is_mini][i]]);
		}

		for (int i = 0; i < sizeof(dlg->m_chords) / sizeof(dlg->m_chords[0]); i++)
		{
			dlg->m_chords[i].ResetContent();
		}
		for (int i = 0; i < sizeof(dlg->m_chords) / sizeof(dlg->m_chords[0]); i++)
		{
			for (int j = 0, k = i; j < 3; j++)
			{
				dlg->m_chords[i].InsertString(0, tunes[pot][Mm[is_mini][k = k < 7 ? k : k - 7]]);
				k += 2;
			}
		}
		
		//dlg->m_chords[0].AddString(tunes[pot][Mm[is_mini][4]]); dlg->m_chords[0].AddString(tunes[pot][Mm[is_mini][2]]); dlg->m_chords[0].AddString(tunes[pot][Mm[is_mini][0]]);
	}
}

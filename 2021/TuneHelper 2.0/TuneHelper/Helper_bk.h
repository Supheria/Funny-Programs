#pragma once
#ifndef HELPER_H

#include "TuneHelperDlg.h"

class Helper
{
	CString tunes[12][12] = {
		{	"C",	"bD",	"D",	"bE",	"E",	"F",	"bG",	"G",	"bA",	"A",	"bB",	"B"	},	// 0
		{	"bD",	"D",	"bE",	"E",	"F",	"bG",	"G",	"bA",	"A",	"bB",	"B",	"C"	},	// 1
		{	"D",	"bE",	"E",	"F",	"bG",	"G",	"bA",	"A",	"bB",	"B",	"C",	"bD"},	// 2
		{	"bE",	"E",	"F",	"bG",	"G",	"bA",	"A",	"bB",	"B",	"C",	"bD",	"D"	},	// 3
		{	"E",	"F",	"bG",	"G",	"bA",	"A",	"bB",	"B",	"C",	"bD",	"D",	"bE"},	// 4
		{	"F",	"bG",	"G",	"bA",	"A",	"bB",	"B",	"C",	"bD",	"D",	"bE",	"E"	},	// 5
		{	"bG",	"G",	"bA",	"A",	"bB",	"B",	"C",	"bD",	"D",	"bE",	"E",	"F"	},	// 6
		{	"G",	"bA",	"A",	"bB",	"B",	"C",	"bD",	"D",	"bE",	"E",	"F",	"bG"},	// 7
		{	"bA",	"A",	"bB",	"B",	"C",	"bD",	"D",	"bE",	"E",	"F",	"bG",	"G"	},	// 8
		{	"A",	"bB",	"B",	"C",	"bD",	"D",	"bE",	"E",	"F",	"bG",	"G",	"bA"},	// 9
		{	"bB",	"B",	"C",	"bD",	"D",	"bE",	"E",	"F",	"bG",	"G",	"bA",	"A"	},	// 10
		{	"B",	"C",	"bD",	"D",	"bE",	"E",	"F",	"bG",	"G",	"bA",	"A",	"bB"}	// 11
	};
	short pot = 0;
	int Mm[2][7] = {
		{ 0, 2, 4, 5, 7, 9, 11 },
		{ 0, 2, 3, 5, 7, 8, 10 }
	};
	bool is_mini = false;
	bool is_found = false;
public:
	Helper(CString tune);
	~Helper();
	void WritePot(CTuneHelperDlg * dlg);
	void SetToMini() { is_mini = true; }
};

#endif // !HELPER_H
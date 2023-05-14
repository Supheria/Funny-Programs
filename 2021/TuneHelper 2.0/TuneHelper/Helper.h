#pragma once
#ifndef HELPER_H

#include "TuneHelperDlg.h"

class Helper
{
public:
	enum TuneMode { main, mini, chrdmn };
	enum Convert { convertNOP = -1, convert1 = 1, convert2, convert3 };
	enum ChordMode { third = 3, seventh, ninth };
private:
	CString tunes[2][12] = {
		{ "C",	"bD",	"D",	"bE",	"E",	"F",	"bG",	"G",	"bA",	"A",	"bB",	"B" },
		{ "C",	"#C",	"D",	"#D",	"E",	"F",	"#F",	"G",	"#G",	"A",	"#A",	"B" }
	};
	short pos = 0;	// 主调位置
	int Mm[4][7] = {// 调性
		{ 0, 2, 4, 5, 7, 9, 11 },	// 大调
		{ 0, 2, 3, 5, 7, 8, 10 },	// 小调
		{ 0, 2, 3, 5, 7, 8, 11 },	// 和声小调
	};
	TuneMode tunemode = main;	// 调性
	Convert convert = convertNOP;	// 转位
	ChordMode chrdmod = third;	// 和弦类型
	bool sp = true; // ShowPattern降调/升调表示
	CTuneHelperDlg* m_dlg = nullptr;
	void Check();
	void WritePots();
	void WriteChords();
public:
	Helper() {};
	Helper(CTuneHelperDlg* dlg);
	~Helper();
	void Update();
	void SetConvertNOP();
	void SetConvert1();
	void SetConvert2();
	void SetConvert3();
	void SetModChild();
	void SetModParent();
	void SetModRelated();
	void SetShowDn();
	void SetShowUp();
	void SetThird();
	void SetSeventh();
	void SetNinth();
};

#endif // !HELPER_H
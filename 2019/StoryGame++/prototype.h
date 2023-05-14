#pragma once

#ifndef _PROTOTYPE_H_
#define _PROTOTYPE_H_

#include "pch.h"

// Initialization.cpp
BOOL CtrlHandler(DWORD fdwCtrlType);
bool Initialize();
void EndGame();
void DirIni();

// menu.cpp
bool menu();
void A(); //选择身份
void B(); //新身份
bool C(); //设置
void D(); //开发人员

//save.cpp
bool NewSave();
bool SelectSave();
void DeleteSave();

#endif
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
void A(); //ѡ�����
void B(); //�����
bool C(); //����
void D(); //������Ա

//save.cpp
bool NewSave();
bool SelectSave();
void DeleteSave();

#endif
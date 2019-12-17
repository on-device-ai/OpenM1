
// OpenM1.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// COpenM1App:
// See OpenM1.cpp for the implementation of this class
//

class COpenM1App : public CWinApp
{
public:
	COpenM1App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern COpenM1App theApp;

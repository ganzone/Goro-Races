// GoroRaces32.h : main header file for the GoroRaces32 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CGoroRaces32App:
// See GoroRaces32.cpp for the implementation of this class
//

class CGoroRaces32App : public CWinApp
{
public:
	CGoroRaces32App();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGoroRaces32App theApp;
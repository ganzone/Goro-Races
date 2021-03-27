// Goro Races Track Editor.h : main header file for the Goro Races Track Editor application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CGoroRacesTrackEditorApp:
// See Goro Races Track Editor.cpp for the implementation of this class
//

class CGoroRacesTrackEditorApp : public CWinApp
{
public:
	CGoroRacesTrackEditorApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGoroRacesTrackEditorApp theApp;
// GoroRaces32Doc.h : interface of the CGoroRaces32Doc class
//


#pragma once

#include "grGameEngine.h"


class CGoroRaces32Doc : public CDocument
{
protected: // create from serialization only
	CGoroRaces32Doc();
	DECLARE_DYNCREATE(CGoroRaces32Doc)

// Attributes
private:
	grGameEngine gameEngine;

// Operations
public:
	// Game managing functions
	void OnGameNew();
	void OnGameTogglePause();

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	virtual void PreCloseFrame(CFrameWnd *pFrame);
	virtual void OnChangedViewList();

// Implementation
public:
	virtual ~CGoroRaces32Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};
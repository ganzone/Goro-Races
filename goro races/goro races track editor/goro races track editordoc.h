// Goro Races Track EditorDoc.h : interface of the CGoroRacesTrackEditorDoc class
//


#pragma once

#include "grEngine.h"


class CGoroRacesTrackEditorDoc : public CDocument
{
protected: // create from serialization only
	CGoroRacesTrackEditorDoc();
	DECLARE_DYNCREATE(CGoroRacesTrackEditorDoc)

// Attributes
public:
	grEngine engine;
	BOOL pillsVisible;

// Operations
public:
	afx_msg void ToggleViewPills();
	afx_msg void ToggleViewPillsUpdateUI(CCmdUI *pCmdUI);

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	virtual void PreCloseFrame(CFrameWnd *pFrame);
	virtual void OnChangedViewList();

// Implementation
public:
	virtual ~CGoroRacesTrackEditorDoc() { }
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};



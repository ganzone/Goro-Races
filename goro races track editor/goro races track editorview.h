#pragma once

#include "Goro Races Track EditorDoc.h"
#include "grViewCamera.h"
#include "CarDialog.h"

class CGoroRacesTrackEditorView : public grViewCamera
{
	DECLARE_DYNCREATE(CGoroRacesTrackEditorView)

// Attributes
public:
	CGoroRacesTrackEditorDoc *Doc;		// Pointer to the document of this view
	CPoint MousePos;					// Mouse position before OnMouseMove() call
	grObject *SelectedObj;				// Current selected object
	CCarDialog *CarDialog;				// Pointer to the "Cars Properties" dialog

// Functions
public:
	void SelectObj(grObject *Obj);
	void UnSelectObj();
	grObject* PickObj(CPoint point);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnEditHumanCar();
	afx_msg void OnEditComputerCar();

// Overrides
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	void OnUpdate(CView *pSender, LPARAM lHint, CObject *pHint);
	void OnInitialUpdate();

// Constructors and destructors
public:
	CGoroRacesTrackEditorView(void);
	~CGoroRacesTrackEditorView(void) { }
};

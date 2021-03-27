// Goro Races Track EditorDoc.cpp : implementation of the CGoroRacesTrackEditorDoc class
//

#include "stdafx.h"
#include "Goro Races Track Editor.h"

#include "Goro Races Track EditorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGoroRacesTrackEditorDoc

IMPLEMENT_DYNCREATE(CGoroRacesTrackEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CGoroRacesTrackEditorDoc, CDocument)
	ON_COMMAND(ID_VIEW_PILLS, CGoroRacesTrackEditorDoc::ToggleViewPills)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PILLS, CGoroRacesTrackEditorDoc::ToggleViewPillsUpdateUI)
END_MESSAGE_MAP()


// CGoroRacesTrackEditorDoc construction/destruction

CGoroRacesTrackEditorDoc::CGoroRacesTrackEditorDoc()
{
	// Hide all pills
	for (int p=0; p<PILL_ONTRACK_NUM*4; p++)
		engine.world.Pill[p].isVisible = FALSE;

	pillsVisible = FALSE;
}


void CGoroRacesTrackEditorDoc::ToggleViewPillsUpdateUI(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(pillsVisible);
}


void CGoroRacesTrackEditorDoc::ToggleViewPills()
{
	pillsVisible = !pillsVisible;

	for (int p=0; p<PILL_ONTRACK_NUM*4; p++)
		engine.world.Pill[p].isVisible = pillsVisible;
}


BOOL CGoroRacesTrackEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// Load and run the base engine
	engine.load("");
	engine.run();

	return TRUE;
}


BOOL CGoroRacesTrackEditorDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	if (!engine.load(lpszPathName))
	{
		CString str;
		str.Format("Error: File %s is not valid", lpszPathName);
		AfxMessageBox(str, MB_OK | MB_SYSTEMMODAL | MB_ICONSTOP);
		return FALSE;
	}	

    engine.world.HumanCar.setOnTrackPos(engine.world.HumanCar.StartAngle,
										engine.world.HumanCar.StartRoad);
	engine.world.ComputerCar.setOnTrackPos(engine.world.ComputerCar.StartAngle,
										engine.world.ComputerCar.StartRoad);

	return TRUE;
}


BOOL CGoroRacesTrackEditorDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// Try to open given file
	CStdioFile fp;
	
	if (!fp.Open(lpszPathName, CFile::modeCreate | CFile::modeWrite))
	{
		CString str;
		str.Format("Error: Cannot open file %s", lpszPathName);
		AfxMessageBox(str, MB_OK | MB_SYSTEMMODAL | MB_ICONSTOP);
		return FALSE;
	}
	
	// Write world info
	engine.world.XMLWrite(fp);

	// Close file descriptor
	fp.Close();

	return TRUE;
}


void CGoroRacesTrackEditorDoc::DeleteContents()
{
	CDocument::DeleteContents();
	
	engine.unload();

	// Reset human car attributes
	engine.world.HumanCar.StartAngle = 280 * M_PI / 180;
	engine.world.HumanCar.StartRoad = TRACK_ROAD4_TRAJECTORY;
	engine.world.HumanCar.Color.r = 1;
	engine.world.HumanCar.Color.g = 0;
	engine.world.HumanCar.Color.b = 0;
	engine.world.HumanCar.HiSpeed = 0.5;
	engine.world.HumanCar.LoSpeed = 0.2;
	engine.world.HumanCar.TrajChgSpeed = 0.09;

	// Reset computer car attributes
	engine.world.ComputerCar.StartAngle = 260 * M_PI / 180;
	engine.world.ComputerCar.StartRoad = TRACK_ROAD4_TRAJECTORY;
	engine.world.ComputerCar.Color.r = 0;
	engine.world.ComputerCar.Color.g = 0;
	engine.world.ComputerCar.Color.b = 1;
	engine.world.ComputerCar.HiSpeed = 0.5;
	engine.world.ComputerCar.LoSpeed = 0.2;
	engine.world.ComputerCar.TrajChgSpeed = 0.04;

	// Reposition cars on track
	engine.world.HumanCar.setOnTrackPos(engine.world.HumanCar.StartAngle,
										engine.world.HumanCar.StartRoad);
	engine.world.ComputerCar.setOnTrackPos(engine.world.ComputerCar.StartAngle,
										   engine.world.ComputerCar.StartRoad);

	// Reset Camera position
	grViewCamera *Camera;
	if (engine.camList.size())
	{
		Camera = engine.camList.at(0);

		Camera->LookAtAngle = M_3PI_2;
		Camera->LookAtDistance = 444;
		Camera->LookAtHeight = 1000;
	}

	// Update all views
	UpdateAllViews(NULL);
}


void CGoroRacesTrackEditorDoc::PreCloseFrame(CFrameWnd *pFrame)
{
	CDocument::PreCloseFrame(pFrame);

	engine.SuspendThread();
}


void CGoroRacesTrackEditorDoc::OnChangedViewList()
{
	engine.camList.clear();

	POSITION viewPos = GetFirstViewPosition();
	while (CView *view = GetNextView(viewPos))
	{
		grViewCamera *camera = dynamic_cast<grViewCamera *>(view);
		if (camera)
		{
			camera->setId("Camera");
			camera->LookAtHeight = 1000;
			camera->LookAtDistance = 500;
			camera->LookAtPos.set(0,0,100);

			engine.camList.push_back(camera);
		}
	}
}


// CGoroRacesTrackEditorDoc diagnostics

#ifdef _DEBUG
void CGoroRacesTrackEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGoroRacesTrackEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGoroRacesTrackEditorDoc commands

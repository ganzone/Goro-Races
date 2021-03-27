// GoroRaces32Doc.cpp : implementation of the CGoroRaces32Doc class
//

#include "stdafx.h"
#include "GoroRaces32.h"

#include "GoroRaces32Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGoroRaces32Doc

IMPLEMENT_DYNCREATE(CGoroRaces32Doc, CDocument)

BEGIN_MESSAGE_MAP(CGoroRaces32Doc, CDocument)
	ON_COMMAND(ID_GAME_NEW,				CGoroRaces32Doc::OnGameNew)
	ON_COMMAND(ID_GAME_PAUSE,			CGoroRaces32Doc::OnGameTogglePause)
END_MESSAGE_MAP()


// CGoroRaces32Doc construction/destruction

CGoroRaces32Doc::CGoroRaces32Doc()
{

}

CGoroRaces32Doc::~CGoroRaces32Doc()
{

}

BOOL CGoroRaces32Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	
	gameEngine.load("");

	return TRUE;
}


BOOL CGoroRaces32Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	return gameEngine.load(lpszPathName);
}

void CGoroRaces32Doc::DeleteContents()
{
	CDocument::DeleteContents();
	
	gameEngine.unload();
}

void CGoroRaces32Doc::PreCloseFrame(CFrameWnd *pFrame)
{
	CDocument::PreCloseFrame(pFrame);

	gameEngine.SuspendThread();
}


void CGoroRaces32Doc::OnGameNew()
{
	gameEngine.setGameMode(GAME_MODE_PLAY);
}


void CGoroRaces32Doc::OnGameTogglePause()
{
	CMenu *menu = AfxGetMainWnd()->GetMenu();
	CMenu *submenu = menu->GetSubMenu(0);

	if (gameEngine.getGameMode() == GAME_MODE_PLAY)
	{
		if (gameEngine.setGameMode(GAME_MODE_PAUSE))
			submenu->CheckMenuItem(ID_GAME_PAUSE, MF_CHECKED);
	}
	else if (gameEngine.getGameMode() == GAME_MODE_PAUSE)
	{
		if (gameEngine.setGameMode(GAME_MODE_PLAY))
			submenu->CheckMenuItem(ID_GAME_PAUSE, MF_UNCHECKED);
	}
}


void CGoroRaces32Doc::OnChangedViewList()
{
	gameEngine.camList.clear();

	POSITION viewPos = GetFirstViewPosition();
	while (CView *view = GetNextView(viewPos))
	{
		grViewCamera *camera = (grViewCamera *) view;

		camera->setId("Camera");

		gameEngine.camList.push_back(camera);
	}
}


// CGoroRaces32Doc diagnostics

#ifdef _DEBUG
void CGoroRaces32Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGoroRaces32Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGoroRaces32Doc commands

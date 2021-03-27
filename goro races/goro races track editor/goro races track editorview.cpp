#include "stdafx.h"
#include "Goro Races Track EditorView.h"
#include <gl/gl.h>
#include <gl/glu.h>

// Size of selection buffer
#define SELECT_BUF_SIZE		1024


IMPLEMENT_DYNCREATE(CGoroRacesTrackEditorView, grViewCamera)

BEGIN_MESSAGE_MAP(CGoroRacesTrackEditorView, grViewCamera)
	ON_COMMAND(ID_EDIT_HUMANCAR, CGoroRacesTrackEditorView::OnEditHumanCar)
	ON_COMMAND(ID_EDIT_COMPUTERCAR, CGoroRacesTrackEditorView::OnEditComputerCar)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


void CGoroRacesTrackEditorView::OnEditHumanCar()
{
	SelectObj(&Doc->engine.world.HumanCar);
}


void CGoroRacesTrackEditorView::OnEditComputerCar()
{
	SelectObj(&Doc->engine.world.ComputerCar);
}


void CGoroRacesTrackEditorView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// Set mouse cursor
	if (nFlags & MK_LBUTTON)
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));
	else
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENS));

	// Initialize mouse position to compute mouse movement
	MousePos = point;
}


void CGoroRacesTrackEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// Set mouse cursor
	if (nFlags & MK_RBUTTON)
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));

	// Initialize mouse position to compute mouse movement
	MousePos = point;

	// Select picked object
	if (grObject *Obj = PickObj(point))
		SelectObj(Obj);
	else
		UnSelectObj();
}


void CGoroRacesTrackEditorView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	double modelMatrix[16];
	double projMatrix[16];
	int viewport[4];

	glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
	glGetIntegerv(GL_VIEWPORT, viewport);
			
	CVector win;
	gluProject(LookAtPos.x, LookAtPos.y, LookAtPos.z,
				modelMatrix, projMatrix, viewport,
				&win.x, &win.y, &win.z);

	// Find new world coordinates of pointer
	CVector obj;
	gluUnProject(point.x, viewport[3] - point.y, win.z,
				modelMatrix, projMatrix, viewport,
				&obj.x, &obj.y, &obj.z);

	LookAtPos.set(obj.x, obj.y, 100);
}


void CGoroRacesTrackEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// Set mouse cursor
	if ((nFlags & MK_RBUTTON) && !(nFlags & MK_LBUTTON))
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENS));
	else if ((nFlags & MK_LBUTTON) && (nFlags & MK_RBUTTON))
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));

	// Compute delta displacement
	CPoint deltaMove = MousePos - point;

	// Update mouse position
	MousePos = point;

	// Check if left mouse button is pressed (Selection movement)
	if (nFlags & MK_LBUTTON)
	{
		grCar *Car;
		if (Car = dynamic_cast<grCar *>(SelectedObj))
		{
			double modelMatrix[16];
			double projMatrix[16];
			int viewport[4];

			glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
			glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
			glGetIntegerv(GL_VIEWPORT, viewport);
			
			// Find window coordinates of selected car
			CVector win;
			gluProject(Car->pos.x, Car->pos.y, Car->pos.z,
					    modelMatrix, projMatrix, viewport,
						&win.x, &win.y, &win.z);

			// Find new world coordinates of pointer
			CVector obj;
			gluUnProject(point.x, viewport[3] - point.y, win.z,
						modelMatrix, projMatrix, viewport,
						&obj.x, &obj.y, &obj.z);

			// Check if pointer is among track roads
			if ((fabs(obj.x) > TRACK_ROAD4_LIMIT_UPPER) ||
				(fabs(obj.y) > TRACK_ROAD4_LIMIT_UPPER) ||
				((fabs(obj.x) < TRACK_ROAD1_LIMIT_LOWER) &&
				 (fabs(obj.y) < TRACK_ROAD1_LIMIT_LOWER)))
			   return;

			// Find new starting angle and make it >0 and <M_2PI
			Car->StartAngle = atan(obj.y/obj.x);
			if (obj.x < 0)
				Car->StartAngle += M_PI;
			Car->StartAngle = fmod(Car->StartAngle, M_2PI);
			if (Car->StartAngle < 0)
				Car->StartAngle += M_2PI;


			// Find new starting road
			if ((fabs(obj.x) > TRACK_ROAD1_LIMIT_LOWER) &&
				(fabs(obj.y) > TRACK_ROAD1_LIMIT_LOWER))
				Car->StartRoad = TRACK_STRAIGHT_LENGHT +
					fabs((fabs(obj.x) - TRACK_STRAIGHT_LENGHT) /
						  cos(atan((fabs(obj.y) - TRACK_STRAIGHT_LENGHT) /
						           (fabs(obj.x) - TRACK_STRAIGHT_LENGHT))));
			else
			if (fabs(obj.x) > TRACK_ROAD1_LIMIT_LOWER)
				Car->StartRoad = fabs(obj.x);
			else
			if (fabs(obj.y) > TRACK_ROAD1_LIMIT_LOWER)
				Car->StartRoad = fabs(obj.y);

			// Adjust trajectory to a specific road
				 if (Car->StartRoad < TRACK_ROAD2_LIMIT_LOWER)
				Car->StartRoad = TRACK_ROAD1_TRAJECTORY;
			else if (Car->StartRoad < TRACK_ROAD3_LIMIT_LOWER)
					Car->StartRoad = TRACK_ROAD2_TRAJECTORY;
			else if (Car->StartRoad < TRACK_ROAD4_LIMIT_LOWER)
				Car->StartRoad = TRACK_ROAD3_TRAJECTORY;
			else
				Car->StartRoad = TRACK_ROAD4_TRAJECTORY;

			// Update new car position
			Car->setOnTrackPos(Car->StartAngle, Car->StartRoad);

			// Update car dialog data
			CarDialog->UpdateDialogData();
		}
	}

	if (nFlags & MK_MBUTTON)
	{
		// RBUTTON + LBUTTON + UP/DOWN = Camera Distance modify
		LookAtDistance += deltaMove.y * 1.5;
		return;
	}

	// Check if right mouse button is pressed (Camera movement)
	if (nFlags & MK_RBUTTON)
	{
		// RBUTTON + LEFT/RIGHT = Camera Angle modify
		LookAtAngle += deltaMove.x * 0.005;

		if (nFlags & MK_LBUTTON)
		{
			// RBUTTON + LBUTTON + UP/DOWN = Camera Distance modify
			LookAtDistance += deltaMove.y * 1.5;
			return;
		}

		// RBUTTON + UP/DOWN = Camera Height modify
		LookAtHeight += deltaMove.y * 1.5;
		if (LookAtHeight <= 30)
			LookAtHeight = 30;
	}
}


void CGoroRacesTrackEditorView::SelectObj(grObject *Obj)
{
	ASSERT(Obj);

	// Unselect current selection
	UnSelectObj();

	// Update selection pointer
	SelectedObj = Obj;

	// If obj is a car then update car properties dialog
	if (SelectedObj->getId().Right(3) == "Car")
		CarDialog->Select(dynamic_cast<grCar *>(SelectedObj));

	// Make selection blinking
	SelectedObj->isBlinking = TRUE;
}


void CGoroRacesTrackEditorView::UnSelectObj(void)
{
	// Stop any selection blinking
	if (SelectedObj)
	{
		SelectedObj->isBlinking = FALSE;
		SelectedObj->isVisible = TRUE;
	}

	// If SelectedObj is a car then unpdate car properties dialog
	if (dynamic_cast<grCar *>(SelectedObj))
		CarDialog->UnSelect();

	// Update selection pointer
	SelectedObj = NULL;
}


grObject* CGoroRacesTrackEditorView::PickObj(CPoint point)
{
	// Set selection buffer
	static GLuint selectBuf[SELECT_BUF_SIZE];
	glSelectBuffer(SELECT_BUF_SIZE, selectBuf);

	// Set selection mode
	glRenderMode(GL_SELECT);

	// Initialize names stack
	glInitNames();
	glLoadName(-1);

	// Fetch viewport values
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	// Save current projection matrix
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	// Set picking matrix
	double pm[16];
	glGetDoublev(GL_PROJECTION_MATRIX, pm);
	glLoadIdentity();
	gluPickMatrix(point.x, viewport[3] - point.y, 1, 1, viewport);
	glMultMatrixd(pm);
	
	// Render the world without rasterization
	Doc->engine.world.draw();

	// Restore projection matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	// Restore render mode and save hits count
	int hits = glRenderMode(GL_RENDER);
	
	// Check if any object was hit
	if (hits == 0)
		return 0;

	// Find nearest objects record index
	int i=0;
	for (int h=1; h<hits; h++)
		i += selectBuf[i] + 3;

	// Find object corresponding to nearest ObjName
	switch (selectBuf[i + 3])
	{
	case OGL_NAME_HUMANCAR:		return &Doc->engine.world.HumanCar;
	case OGL_NAME_COMPUTERCAR:	return &Doc->engine.world.ComputerCar;
	default: return NULL;
	}
}


void CGoroRacesTrackEditorView::OnUpdate(CView *pSender, LPARAM lHint, CObject *pHint)
{
	// Deselect selected object
	UnSelectObj();
}


void CGoroRacesTrackEditorView::OnInitialUpdate(void)
{
	// Get document pointer
	Doc = dynamic_cast<CGoroRacesTrackEditorDoc *>(GetDocument());
	ASSERT(Doc);
}


CGoroRacesTrackEditorView::CGoroRacesTrackEditorView(void)
{
	// Initialize selected object pointer
	SelectedObj = NULL;
}
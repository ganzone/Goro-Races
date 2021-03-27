/*

File name: grView.cpp

Description:
see grView.h file for a description about this class

*/


#include "stdafx.h"
#include "grView.h"
#include <gl/gl.h>
#include <gl/glu.h>


IMPLEMENT_DYNCREATE(grView, CView)

BEGIN_MESSAGE_MAP(grView, CView)
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


BOOL const grView::setupPixelFormat(CDC *pDC)
{
	// Fill-in pixelformat descriptor structure
	static PIXELFORMATDESCRIPTOR pfd = 
	{
		sizeof(PIXELFORMATDESCRIPTOR),	// size of this pfd
			1,							// version number
			PFD_DRAW_TO_WINDOW |		// support window
			PFD_SUPPORT_OPENGL |		// support OpenGL
			PFD_DOUBLEBUFFER,			// double buffered
			PFD_TYPE_RGBA,				// RGBA type 
			24,							// 24-bit color depth 
			0, 0, 0, 0, 0, 0,			// color bits ignored
			0,							// no alpha buffer
			0,							// shift bit ignored
			0,							// no accumulation buffer
			0, 0, 0, 0,					// accum bits ignored
			32,							// 32-bit z-buffer
			0,							// no stencil buffer
			0,							// no auxiliary buffer
			PFD_MAIN_PLANE,				// main layer
			0,							// reserved
			0, 0, 0						// layer masks ignored
	 };

	// Choose and set pixel format
    int pixelformat;

	if (!(pixelformat = ChoosePixelFormat(pDC->GetSafeHdc(), &pfd)))
		return FALSE;

	if (!SetPixelFormat(pDC->GetSafeHdc(), pixelformat, &pfd))
		return FALSE;

	return TRUE;
}

#include "gr3DSObject.h"

BOOL const grView::setupOpenGL(void)
{
	// Setup OpenGL state variables
	if (!glMakeCurrent())
		return FALSE;

	glEnable(GL_DEPTH_TEST);				// Enable z-buffering
	glEnable(GL_COLOR_MATERIAL);			// Enable color material
	glClearColor(0.25, 0.25, 1.0, 0.0);		// Sky scene background
	glShadeModel(GL_SMOOTH);

	// Set scene lights
	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);    
	GLfloat glfLightAmbient[] =  {0.1f, 0.1f, 0.1f, 1.0f};
    GLfloat glfLightDiffuse[] =  {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat glfLightSpecular[] = {0.6f, 0.6f, 0.3f, 1.0f};
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, glfLightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, glfLightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, glfLightSpecular);

	// Enable arrays for 3DStudio meshes drawing
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

	gr3DSObject::DListTrack = gr3DSObject::InitDListTrack();
	gr3DSObject::DListPill = gr3DSObject::InitDListPill();
	gr3DSObject::DListCar = gr3DSObject::InitDListCar();

	return TRUE;
}


BOOL const grView::glMakeCurrent(void)
{
	// No OpenGL context available, do nothing
	if (!(m_hDC && hglrc))
		return FALSE;

	// Error during make current, generate error
	if (!wglMakeCurrent(m_hDC->GetSafeHdc(), hglrc))
	{
		AfxMessageBox("grEngine: glMakeCurrent() Error (bad thing...)");
		return FALSE;
	}

	return TRUE;
}


BOOL grView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName,
					   DWORD dwStyle, const RECT& rect, CWnd* pParentWnd,
					   UINT nID, CCreateContext* pContext)
{
	// Create a CView window
	if( ! CView::Create(lpszClassName, lpszWindowName, dwStyle,
		rect, pParentWnd, nID, pContext))
	{
		AfxMessageBox("grEngine: Cannot create a CView window");
		return FALSE;
	}

	// Create a new device context for including the OpenGL context
	m_hDC = new CClientDC(this);
	if (!m_hDC)
	{
		AfxMessageBox("grEngine: Error creating the client device context");
		return FALSE;
	}

	// Set the pixel format of the device context
	if (!setupPixelFormat(m_hDC))
	{
		AfxMessageBox("grEngine: Error during PixelFormat setup");
		return FALSE;
	}

	// Set OpenGL rendering context
	hglrc = wglCreateContext(m_hDC->GetSafeHdc());
	if(hglrc==NULL)
	{
		AfxMessageBox("gEngine: error creating OpenGL context");
		return FALSE;
	}

	// Setup OpenGL settings
	if (!setupOpenGL())
	{
		AfxMessageBox("grEngine: Error setting up OpenGL flags");
		return FALSE;
	}

	// Create a windows font
	hFont = CreateFont(14, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET,
					   OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
					   FF_DONTCARE | DEFAULT_PITCH, "Courier");
	if (!hFont)
	{
		AfxMessageBox("grEngine: Error creating Windows font");
		return FALSE;
	}

	// Assign this device context to just created font
	SelectObject(m_hDC->GetSafeHdc(), hFont);

	// Create 96 OpenGL display lists to hold bitmap font characters
	fontList = glGenLists(96);

	// Prepare for bitmap fonts use
	wglUseFontBitmaps(m_hDC->GetSafeHdc(), 32, 96, fontList);

	return TRUE;
}


BOOL grView::PreCreateWindow(CREATESTRUCT &cs)
{
	// Set window style
	cs.style &= ~WS_BORDER;
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	
	// Set window extended-style
	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	
	// Ensures style has not the CS_PARENTDC flag activated
	ASSERT(!(cs.style & CS_PARENTDC));

	// Register the new window
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
	     ::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return CView::PreCreateWindow(cs);
}


void grView::OnDestroy(void)
{
	// Delete Font display lists
	glDeleteLists(fontList, 96);

	// Destroy font object
	DeleteObject(hFont);

	// Destroy this CView window
	CView::OnDestroy();

	// Select OpenGL context
	if (glMakeCurrent())
		// Wait for last OpenGL commands completion
		glFinish();

	// Delete OpenGL context
	ASSERT(wglDeleteContext(hglrc));
	
	// Delete device context
	delete m_hDC;
}


void grView::OnSize(UINT nType, int cx, int cy)
{
	// Adjust viewport values
	glViewport(0, 0, cx, cy);
}


BOOL grView::OnEraseBkgnd(CDC *pDC)
{
	return TRUE;
}


grView::grView(void)
{
	m_hDC = 0;
	hglrc = 0;
}
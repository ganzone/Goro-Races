/*

File name grView.h

Description:
grView class represents the surface were Goro Racer Engine draws objects. It
contains a pointer to a rendering context (HDRC on win32) and to a client
device context (CDC on win32). This context can be used in a stand-alone window,
MFC apps, ecc...

*/


#ifndef _GRVIEW_H
#define _GRVIEW_H


class AFX_EXT_CLASS grView : public CView
{
	DECLARE_DYNCREATE(grView)

// Attributes
protected:
	CClientDC *m_hDC;		// Client device context
	HGLRC hglrc;			// Rendering context for OpenGL
	HFONT hFont;			// Win32 font used within OpenGL bitmap-fonts
	unsigned int fontList;	// Font display lists to hold character bitmaps

// Functions
private:
	BOOL const setupPixelFormat(CDC *pDC);	// Set needed pixel format for an OpenGL context
	BOOL const setupOpenGL(void);			// Set general OpenGL-state flags
protected:
	BOOL const glMakeCurrent(void);			// Set this OpenGL context as the current

// Constructors and destructors
public:
	grView(void);
	virtual ~grView(void) { }

// Overridden functions of CView class
private:
	BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
				const RECT& rect, CWnd* pParentWnd, UINT nID,
				CCreateContext* pContext);
	BOOL PreCreateWindow(CREATESTRUCT &cs);

// Overridden CView message handlers
	DECLARE_MESSAGE_MAP()
private:
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
protected:
	virtual afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnDraw(CDC* pDC) { };
};


#endif // _GRVIEW_H
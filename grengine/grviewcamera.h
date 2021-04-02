/*

File name: grViewCamera.h

Description:
grViewCamera class provides functions and information about the view camera of the
world. It derives a grObject, so a grCamera can have a position, a speed, ecc...

*/


#ifndef _GRVIEWCAMERA_H
#define _GRVIEWCAMERA_H

#include "grView.h"
#include "grObject.h"


class AFX_EXT_CLASS grViewCamera: public grView, public grObject
{
	DECLARE_DYNCREATE(grViewCamera)

// Attributes
public:
	CVector LookAtPos;			// look-at position
	double LookAtAngle;			// Polar angle from look-at position
	double LookAtDistance;		// Polar distance from look-at position
	double LookAtHeight;		// Height from look-at position height
	double Fov;					// Field-Of-View angle (in degrees) in y direction
	double zNear;				// z-distance to the near clipping plane
	double zFar;				// z-distance to the far clipping plane

// Functions
public:
	// Lead given object from given distance and height
	void Lead(grObject const &Obj, double const Dist = 0,
			  double const Angle = 0, double const Height = 0);
	// Follow given object from given distance
	void Follow(grObject const &Obj, double const Dist = 0,
				double const Angle = 0, double const Height = 0);

// Overloaded functions
public:
	// Modify projection matrix according to current camera data
	void onDraw(void);
	void onAnimate(DWORD deltaTime);

	DECLARE_MESSAGE_MAP()

	virtual void OnDraw(CDC *pDC);
	afx_msg virtual void OnSize(UINT nType, int cx, int cy);

// Constructors and destructors
public:
	grViewCamera(void);
	virtual ~grViewCamera(void) { }
};


#endif // _GRVIEWCAMERA_H
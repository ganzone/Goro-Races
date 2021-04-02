/*

File name: gr3DSObject.h

Description:
this class represents a 3D grObject (as defined in object.h) whose shape is
defined in a 3DStudio file.

*/


#ifndef _GR3DSOBJECT_H
#define _GR3DSOBJECT_H

// OpenGL names for selection
#define OGL_NAME_HUMANCAR			100
#define OGL_NAME_COMPUTERCAR		200


// Shapes path
#ifdef _DEBUG
#define GR_3DS_SHAPE_PATH				"../shapes"
#else
#define GR_3DS_SHAPE_PATH				"shapes"
#endif // _DEBUG

#define GR_3DS_SHAPE_TRACK_PATH			GR_3DS_SHAPE_PATH"/track.3ds"
#define GR_3DS_SHAPE_PILL_PATH			GR_3DS_SHAPE_PATH"/pill.3ds"
#define GR_3DS_SHAPE_CAR_PATH			GR_3DS_SHAPE_PATH"/car.3ds"


#include "grObject.h"
#include "l3ds.h"

class AFX_EXT_CLASS gr3DSObject :	public virtual grObject
{
// Attributes
public:
	// L3DS shapes support
	static L3DS ShapeTrack;
	static L3DS ShapePill;
	static L3DS ShapeCar;

	// Display list support
	static unsigned int DListTrack;
	static unsigned int DListPill;
	static unsigned int DListCar;

	// Functions to initialize display lists at startup
	static unsigned int InitDListTrack(void) { return InitDList(ShapeTrack); }
	static unsigned int InitDListPill(void) { return InitDList(ShapePill); }
	static unsigned int InitDListCar(void) { return InitDList(ShapeCar); }
	static unsigned int InitDList(L3DS &shape);

	// Pointer to a specific display list to use during onDraw()
	unsigned int *DList;

// Overloaded functions
protected:
	virtual void onDraw(void);

// Constructors and destructors
public:
	gr3DSObject(void) { DList = NULL; }
	virtual ~gr3DSObject(void) { }
};


#endif // _GR3DSOBJECT_H
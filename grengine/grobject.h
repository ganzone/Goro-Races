/*

File name: grObject.h

Description:
grObject class represents the minimum entity of the world that the grEngine can
manage. Every grObject mantains its position, speed, acceleration, orientation,
ecc... and provides basic functions for collisions detection, object drawing and
animating.

*/


#ifndef _GROBJECT_H
#define _GROBJECT_H

#include "vector.h"
#include "quaternion.h"
#include "grNode.h"

#include "xml.h"
using namespace vcg;

class AFX_EXT_CLASS grObject : public grNode
{
// Attributes
public:
	CVector pos;				// position
	CVector speed;				// speed
	CVector accel;				// acceleration
	CVector rot_angle;			// x/y/z-axis rotation angle
	double radius;				// collision detection radius
	BOOL isAnimating;			// animation flag (FALSE means a freezed object)
	BOOL isColliding;			// collision flag (FALSE means a no colliding object)
	BOOL isVisible;				// visibility flag
	BOOL isBlinking;			// blinking flag
	BOOL isDead;				// dead flag (object will be destroyed when TRUE)
	BOOL hasGravity;			// flag gravity force (along z-axis)

	DWORD lastBlinkTime;		// Time elapsed from last blink switching
	DWORD deltaBlinkTime;		// Time to wait between two blink switches

// Functions
public:
	// Animate the object and its children/siblings
	void animate(DWORD deltaTime);
	// Prepare the object and its children/siblings for collision detection
	void prepare(void);
	// Detect if this object and its children/siblings collides obj
	void detectCollision(grObject *obj);
	// Draw the object and its children/siblings given the camera position
	void draw(void);

// Event handlers
public:
	// Perform physics of the object
	virtual void onAnimate(DWORD deltaTime) { }
	// Perform collisions and preparations for other objects
	virtual void onPrepare(void);
	// Draw the object given the camera position
	virtual void onDraw(void) { }
	// Collide with obj
	virtual void onCollision(grObject *obj) { }

	// Save object info to given file
	virtual void XMLWrite(CStdioFile &fp) { }
	// Load object info from given file
	virtual void XMLRead(Xml &Tag) { }

// Constructors and destructors
public:
	grObject(void);
	virtual ~grObject(void);
};


#endif // _GROBJECT_H
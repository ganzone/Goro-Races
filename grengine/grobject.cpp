/*

File name: grObject.cpp

Description:
see grObject.h for a description about this class

*/


#include "stdafx.h"
#include "grObject.h"

#include <gl/gl.h>


void grObject::animate(DWORD deltaTime)
{
	// Animate this object
	if (isAnimating)
	{
		onAnimate(deltaTime);

		// Animate children
		if (hasChild())
			((grObject *) childNode)->animate(deltaTime);
	}

	// Animate siblings from left-one to right-one
	if (hasSiblings() && !isLastChild())
		((grObject *) nextNode)->animate(deltaTime);
}


void grObject::prepare(void)
{
	// Prepare this object for collision detection
	onPrepare();

	// If this object has children then prepare them
	if (hasChild())
		((grObject *) childNode)->prepare();

	// If this object has siblings then prepare them
	if (hasSiblings() && !isLastChild())
		((grObject *) nextNode)->prepare();
}


void grObject::detectCollision(grObject *obj)
{
	// Check if obj is a NULL pointer
	ASSERT(obj);

	// Check if obj is this object
	if (obj == this)
		ASSERT(FALSE);

	// Check if obj can collide
	if (!obj->isColliding)
		return;

	// Check if this object can collide
	if (isColliding)
	{
		// Check if this object's bounding sphere collides with obj's sphere
		// and if this obj is not this object
		if (((obj->pos - pos).lenght() <= (obj->radius + radius)) &&
			(obj != this))
		{
			// Treat collision between obj and this object
			onCollision(obj);

			// Test children collisions with obj
			if (hasChild())
				((grObject *) childNode)->detectCollision(obj);
		}
	}
}


void grObject::draw(void)
{
	// Check if object is blinking
	if (isBlinking)
		if (GetTickCount() - lastBlinkTime > deltaBlinkTime)
		{
			lastBlinkTime = GetTickCount();
			isVisible = !isVisible;
		}

	// Draw the object and its children if it is visibile
	if (isVisible)
	{
		// save current modelview matrix
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		{
			// Translate object to its position
			glTranslated(pos.x, pos.y, pos.z);

			// Generate rotation quaternions for x/y/z axis
			CQuaternion quat_x, quat_y, quat_z;

			quat_x.setAxisAngle(rot_angle.x, 1, 0, 0);
			quat_y.setAxisAngle(rot_angle.y, 0, 1, 0);
			quat_z.setAxisAngle(rot_angle.z, 0, 0, 1);

			// Generate rotation matrix and rotate object multipling it
			double matrix[16];
			(quat_x * quat_y * quat_z).getMatrix_4x4(matrix);
			glMultMatrixd(matrix);

			onDraw();

			// draw children
			if (hasChild())
				((grObject *) childNode)->draw();
		}
		// restore old modelview matrix
		glPopMatrix();
	}
	
	// draw siblings from left-one to right-one
	if (hasSiblings() && !isLastChild())
		((grObject *) nextNode)->draw();
}


void grObject::onPrepare(void)
{
	// Detect collisions with siblings objects
	grObject *obj = (grObject *) nextNode;

	while (obj != this)
	{
		detectCollision(obj);
		obj = (grObject *) obj->nextNode;
	}
}

grObject::grObject(void)
{
	// Set default parameters values
	rot_angle = 0;
	radius = 0;
	isAnimating = TRUE;
	isColliding = TRUE;
	isVisible = TRUE;
	isBlinking = FALSE;
	isDead = FALSE;
	hasGravity = FALSE;

	lastBlinkTime = 0;
	deltaBlinkTime = 100;
}


grObject::~grObject(void)
{

}
/*

File name: grViewCamera.cpp

Description:
see grViewCamera.h for a description about this class

*/


#include "stdafx.h"
#include "grWorld.h"
#include "grViewCamera.h"
#include <gl/gl.h>
#include <gl/glu.h>


IMPLEMENT_DYNCREATE(grViewCamera, grView)

BEGIN_MESSAGE_MAP(grViewCamera, grView)
	ON_WM_SIZE()
END_MESSAGE_MAP()


void grViewCamera::Lead(grObject const &Obj, double const Dist,
						double const Angle, double const Height)
{
	LookAtPos = Obj.pos;
	LookAtDistance = Dist;
	LookAtAngle = Angle - Obj.rot_angle.z + M_PI_2;
	LookAtHeight = Height;
}


void grViewCamera::Follow(grObject const &Obj, double const Dist,
						  double const Angle, double const Height)
{
	LookAtPos = Obj.pos;
	LookAtDistance = Dist;
	LookAtAngle = Angle - Obj.rot_angle.z + M_3PI_2;
	LookAtHeight = Height;
}


void grViewCamera::onDraw(void)
{
	// Reset projection matrix
	glMatrixMode(GL_PROJECTION);
	
	glPopMatrix();
	glPushMatrix();

	// Set looking-at position
	gluLookAt(pos.x,
			  pos.y,
			  pos.z,
			  LookAtPos.x,
			  LookAtPos.y,
			  LookAtPos.z,
			  0, 0, 1);
	
	glMatrixMode(GL_MODELVIEW);
}


void grViewCamera::onAnimate(DWORD deltaTime)
{
	// Compute camera position
	pos.x = LookAtPos.x + LookAtDistance * cos(LookAtAngle);
	pos.y = LookAtPos.y + LookAtDistance * sin(LookAtAngle);
	pos.z = LookAtPos.z + LookAtHeight;
}


void grViewCamera::OnDraw(CDC *pDC)
{
	// Select this engine context as the current OpenGL context
	ASSERT(glMakeCurrent());

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw world objects
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Check if camera is attached to any world objects tree
	grNode *root = getRoot();
	if (root != this)
	{
        grWorld *world = (grWorld *) root;

		CSingleLock world_mutex(&world->mutex, TRUE);

		// Draw world objects
		world->draw();

		world_mutex.Unlock();
	}

	// Wait for OpenGL-commands to terminate
	glFlush();

	// Swap video buffers
	SwapBuffers(m_hDC->GetSafeHdc());
}


void grViewCamera::OnSize(UINT nType, int cx, int cy)
{
	grView::OnSize(nType, cx, cy);

	if ((cx == 0) || (cy == 0))
		return;

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glLoadIdentity();

	if (cy > cx)
		gluPerspective(Fov, cy/cx, zNear, zFar);
	else
		gluPerspective(Fov, cx/cy, zNear, zFar);

	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
}


grViewCamera::grViewCamera(void)
{
	// Set default camera values
	LookAtAngle = 0;
	LookAtDistance = 0;
	LookAtHeight = 0;
	Fov = 60;
	zNear = 4;
	zFar = 5000;

	// Set some super-classes attributes
	isColliding = FALSE;
}
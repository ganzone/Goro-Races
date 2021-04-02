#include "stdafx.h"
#include "grTrack.h"
#include <gl/gl.h>

void grTrack::onDraw(void)
{
	// Draw track mesh 4 times, rotating about 90 degrees for each cycle
	gr3DSObject::onDraw();
	glRotatef(90, 0, 0, 1);
	gr3DSObject::onDraw();
	glRotatef(90, 0, 0, 1);
	gr3DSObject::onDraw();
	glRotatef(90, 0, 0, 1);
	gr3DSObject::onDraw();
}
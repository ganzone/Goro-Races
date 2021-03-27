/*

File name: gr3DSObject.cpp

Description:
see gr3DSObject.h for a description about this file

*/


#include "stdafx.h"
#include "gr3DSobject.h"
#include <gl/gl.h>


// Static objects initialization
L3DS  gr3DSObject::ShapeTrack(GR_3DS_SHAPE_TRACK_PATH);
L3DS  gr3DSObject::ShapePill(GR_3DS_SHAPE_PILL_PATH);
L3DS  gr3DSObject::ShapeCar(GR_3DS_SHAPE_CAR_PATH);

unsigned int gr3DSObject::DListTrack;
unsigned int gr3DSObject::DListPill;
unsigned int gr3DSObject::DListCar;


unsigned int gr3DSObject::InitDList(L3DS &shape)
{
	// Generate a single display list name
	unsigned int name = glGenLists(1);

	// Compile display list commands
	glNewList(name, GL_COMPILE);
	{
		// Draw shape meshes
		for (uint meshIndex=0; meshIndex < shape.GetMeshCount(); meshIndex++)
		{
			// Get current mesh
			LMesh &mesh = shape.GetMesh(meshIndex);

			// Get mesh material (NOTE: only first material of the mesh is used!)
			LMaterial &material = shape.GetMaterial(mesh.GetMaterial(0));

			LColor3 color = material.GetAmbientColor();
			float alpha = (float) 1.0 - material.GetTransparency();

			glColor4f(color.r, color.g, color.b, alpha);

			// Check if we must enable blending
			if (alpha < 1.0)
			{
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glDepthMask(GL_FALSE);
			}

			// Draw mesh triangles
			glNormalPointer(GL_FLOAT, 0, &mesh.GetNormal(0));
			glVertexPointer(4, GL_FLOAT, 0, &mesh.GetVertex(0));
			glDrawElements(GL_TRIANGLES, mesh.GetTriangleCount()*3, 
							GL_UNSIGNED_SHORT, &mesh.GetTriangle(0));

			if (alpha < 1.0)
			{
				glDisable(GL_BLEND);
				glDepthMask(GL_TRUE);
			}
		}
	}
	glEndList();

	return name;
}


void gr3DSObject::onDraw(void)
{
	ASSERT(DList);
	ASSERT(*DList);
	ASSERT(glIsList(*DList));

	glCallList(*DList);
}
#include "stdafx.h"
#include "grHumanCar.h"
#include <gl/gl.h>

void grHumanCar::onDraw(void)
{
	glPushName(OGL_NAME_HUMANCAR);
	
	grCar::onDraw();

	glPopName();
}


void grHumanCar::XMLWrite(CStdioFile &fp)
{
	fp.WriteString("\t<HumanCar>\n");

	grCar::XMLWrite(fp);
	
	fp.WriteString("\t</HumanCar>\n");
}


void grHumanCar::XMLRead(Xml &Tag)
{
	ASSERT(Tag.id == "HumanCar");

	grCar::XMLRead(Tag);
}

	
grHumanCar::grHumanCar(void)
{
	Color.r = 1;
	Color.g = 0;
	Color.b = 0;
	HiSpeed = 0.5;
	LoSpeed = 0.2;
	TrajChgSpeed = 0.09;
	StartAngle = M_3PI_2 + 0.2;
}
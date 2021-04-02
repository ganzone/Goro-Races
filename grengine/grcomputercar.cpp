#include "stdafx.h"
#include "grComputerCar.h"
#include <gl/gl.h>

void grComputerCar::onDraw(void)
{
	glPushName(OGL_NAME_COMPUTERCAR);
	
	grCar::onDraw();

	glPopName();
}


void grComputerCar::onAnimate(DWORD deltaTime)
{
	// Try to follow other car trajectory
	if (OtherCar && trk_speed)
	{
		if (OtherCar->getOnTrackTrajectory() > trk_trajectory)
			trk_trajChgSpeed = +TrajChgSpeed;

		if (OtherCar->getOnTrackTrajectory() < trk_trajectory)
			trk_trajChgSpeed = -TrajChgSpeed;

		if (fabs(OtherCar->getOnTrackTrajectory() - trk_trajectory) < 1)
			trk_trajChgSpeed = 0;
	}

	grCar::onAnimate(deltaTime);
}


void grComputerCar::XMLWrite(CStdioFile &fp)
{
	fp.WriteString("\t<ComputerCar>\n");

	grCar::XMLWrite(fp);
	
	fp.WriteString("\t</ComputerCar>\n");
}


void grComputerCar::XMLRead(Xml &Tag)
{
	ASSERT(Tag.id == "ComputerCar");

	grCar::XMLRead(Tag);
}


grComputerCar::grComputerCar(void)
{
	OtherCar = NULL;

	Color.r = 0;
	Color.g = 0;
	Color.b = 1;
	HiSpeed = 0.5;
	LoSpeed = 0.3;
	TrajChgSpeed = 0.09;
	StartAngle = M_3PI_2 - 0.2;

	// Revert forward direction of all computer cars
	trk_revdir = TRUE;
}
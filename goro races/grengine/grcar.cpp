#include "stdafx.h"
#include "grCar.h"
#include "grPill.h"		// For collision detection


void grCar::onAnimate(DWORD deltaTime)
{
	// Animate object on track
	grOnTrackObject::onAnimate(deltaTime);

	// Calculate new trajectory
    double newTraj;

	// Check if car not among walls
	if ((fabs(pos.x) >= TRACK_STRAIGHT_EMPTY_LENGHT) &&
		(fabs(pos.y) >= TRACK_STRAIGHT_EMPTY_LENGHT))
	{
		// If car is among walls then modify its trajectory to the one
		// of nearest road
		if (trk_trajectory < TRACK_ROAD1_LIMIT_UPPER)
			newTraj = TRACK_ROAD1_TRAJECTORY;
		if ((trk_trajectory >= TRACK_ROAD2_LIMIT_LOWER) &&
			(trk_trajectory <  TRACK_ROAD2_LIMIT_UPPER))
			newTraj = TRACK_ROAD2_TRAJECTORY;
		if ((trk_trajectory >= TRACK_ROAD3_LIMIT_LOWER) &&
			(trk_trajectory <  TRACK_ROAD3_LIMIT_UPPER))
			newTraj = TRACK_ROAD3_TRAJECTORY;
		if (trk_trajectory >= TRACK_ROAD4_LIMIT_LOWER)
			newTraj = TRACK_ROAD4_TRAJECTORY;
	}
	else
	{
		// If car is not among walls then calculate its new
		// trajectory depending on trajChangeSpeed value
		newTraj = trk_trajectory + (trk_trajChgSpeed * deltaTime);

		if (newTraj < TRACK_ROAD1_TRAJECTORY)
			newTraj = TRACK_ROAD1_TRAJECTORY;
		if (newTraj > TRACK_ROAD4_TRAJECTORY)
			newTraj = TRACK_ROAD4_TRAJECTORY;
	}

	// Calculate angle delta
	double deltaAngle;

	if (fabs(pos.x) < TRACK_STRAIGHT_EMPTY_LENGHT)
		deltaAngle = fabs(fabs(atan(pos.x / trk_trajectory)) -
						  fabs(atan(pos.x / newTraj)));
	else
		deltaAngle = fabs(fabs(atan(pos.y / trk_trajectory)) -
						  fabs(atan(pos.y / newTraj)));

	// Adjust new angle
	double newAngle;

	if (fmod(trk_angle, M_PI_2) < getOnTrackStraightAngle())
		deltaAngle = -deltaAngle;

	if (newTraj - trk_trajectory > 0)
		newAngle = trk_angle + deltaAngle;
	else
		newAngle = trk_angle - deltaAngle;

    // Set new track position of object
	setOnTrackPos(newAngle, newTraj);
}


void grCar::onCollision(grObject *obj)
{
	// Check if collided a pill
	if (obj->getId().Left(4) == "Pill" && isEatingPills)
	{
		obj->isDead = TRUE;
		obj->isVisible = FALSE;
		obj->isColliding = FALSE;

		EatenPills++;

		return;
	}

	// Check if collided the other car
	if (obj->getId().Right(3) == "Car")
	{
		isDead = TRUE;

		return;
	}
}


void grCar::onDraw(void)
{
	// Get "body" mesh
	LMesh *mesh = ShapeCar.FindMesh("Body");
	ASSERT(mesh);

	// Get mesh material
	LMaterial &mat = ShapeCar.GetMaterial(mesh->GetMaterial(0));

	// Set material color
	mat.SetAmbientColor(Color);
	mat.SetDiffuseColor(Color);
	mat.SetSpecularColor(Color);

	// Draw the shape
	gr3DSObject::onDraw();
}


void grCar::XMLWrite(CStdioFile &fp)
{
	CString str;

	str.AppendFormat("\t\t<Color R=\"%g\" G=\"%g\" B=\"%g\"/>\n", Color.r*255, Color.g*255, Color.b*255);
	str.AppendFormat("\t\t<LoSpeed>%g</LoSpeed>\n", LoSpeed*1000);
	str.AppendFormat("\t\t<HiSpeed>%g</HiSpeed>\n", HiSpeed*1000);
	str.AppendFormat("\t\t<TrajChgSpeed>%g</TrajChgSpeed>\n", TrajChgSpeed*1000);
	str.AppendFormat("\t\t<StartAngle>%g</StartAngle>\n", (StartAngle * 180) / M_PI);

	str.AppendFormat("\t\t<StartRoad>");
	if (StartRoad == TRACK_ROAD1_TRAJECTORY)
		str.Append("1");
	if (StartRoad == TRACK_ROAD2_TRAJECTORY)
		str.Append("2");
	if (StartRoad == TRACK_ROAD3_TRAJECTORY)
		str.Append("3");
	if (StartRoad == TRACK_ROAD4_TRAJECTORY)
		str.Append("4");
	str.AppendFormat("</StartRoad>\n");

	fp.WriteString(str);
}


void grCar::XMLRead(Xml &Tag)
{
	// ASSERT(xml.id == "Car");

	// Assign default values to attributes
	Color.r = 0;
	Color.g = 0;
	Color.b = 0;
	HiSpeed = 0;
	LoSpeed = 0;
	TrajChgSpeed = 0;
	StartAngle = 0;
	StartRoad = TRACK_ROAD4_TRAJECTORY;

	for (Xml::iterator TagIter = Tag.begin(); TagIter != Tag.end(); TagIter++)
	{
		Xml cTag = *TagIter;

			if (cTag.id == "HiSpeed")
				HiSpeed = atof(cTag.content.c_str()) * 0.001;
		else
			if (cTag.id == "LoSpeed")
				LoSpeed = atof(cTag.content.c_str()) * 0.001;
		else
			if (cTag.id == "StartAngle")
				StartAngle = (atof(cTag.content.c_str()) * M_PI) / 180;
		else
			if (cTag.id == "TrajChgSpeed")
				TrajChgSpeed = atof(cTag.content.c_str()) * 0.001;
		else
			if (cTag.id == "Color")
			{
				Color.r = (float) (atof(cTag["R"].c_str()) / 255);
				Color.g = (float) (atof(cTag["G"].c_str()) / 255);
				Color.b = (float) (atof(cTag["B"].c_str()) / 255);
			}
		else
			if (cTag.id == "StartRoad")
			{
				if (cTag.content == "1")
					StartRoad = TRACK_ROAD1_TRAJECTORY;
				if (cTag.content == "2")
					StartRoad = TRACK_ROAD2_TRAJECTORY;
				if (cTag.content == "3")
					StartRoad = TRACK_ROAD3_TRAJECTORY;
				if (cTag.content == "4")
					StartRoad = TRACK_ROAD4_TRAJECTORY;
			}
	}
}


grCar::grCar(void)
{
	// Set grObject attributes
	radius = 15;

	// Set gr3DSObject attributes
	DList = &DListCar;

    // Set grOnTrackObject attributes
	trk_trajChgSpeed = 0;
	trk_height = 15;

	// Initialize car attributes
	Color.r = 0;
	Color.g = 0;
	Color.b = 0;
	HiSpeed = 0;
	LoSpeed = 0;
	TrajChgSpeed = 0;
	StartAngle = 0;
	StartRoad = TRACK_ROAD4_TRAJECTORY;
	isEatingPills = FALSE;
	EatenPills = 0;
}
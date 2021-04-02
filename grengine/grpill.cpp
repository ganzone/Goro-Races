#include "stdafx.h"
#include "grPill.h"


double const grPill::PillOnTrackAngle[PILL_ONTRACK_NUM] = 
{
	// Road 1 (6 pills)
	0.40,
	0.55,
	0.70,
	0.85,
	1.00,
	1.15,
	// Road 2 (9 pills)
	0.35,
	0.46,
	0.57,
	0.68,
	0.79,
	0.90,
	1.01,
	1.12,
	1.23,
	// Road 3 (11 pills)
	0.30,
	0.40,
	0.50,
	0.60,
	0.70,
	0.80,
	0.90,
	1.00,
	1.10,
	1.20,
	1.30,
	// Road 4 (11 pills)
	0.30,
	0.40,
	0.50,
	0.60,
	0.70,
	0.80,
	0.90,
	1.00,
	1.10,
	1.20,
	1.30,
};

double const grPill::PillOnTrackTraj[PILL_ONTRACK_NUM] =
{
	// Road 1 (6 pills)
	TRACK_ROAD1_TRAJECTORY,
	TRACK_ROAD1_TRAJECTORY,
	TRACK_ROAD1_TRAJECTORY,
	TRACK_ROAD1_TRAJECTORY,
	TRACK_ROAD1_TRAJECTORY,
	TRACK_ROAD1_TRAJECTORY,
	// Road 2 (9 pills)
	TRACK_ROAD2_TRAJECTORY,
	TRACK_ROAD2_TRAJECTORY,
	TRACK_ROAD2_TRAJECTORY,
	TRACK_ROAD2_TRAJECTORY,
	TRACK_ROAD2_TRAJECTORY,
	TRACK_ROAD2_TRAJECTORY,
	TRACK_ROAD2_TRAJECTORY,
	TRACK_ROAD2_TRAJECTORY,
	TRACK_ROAD2_TRAJECTORY,
	// Road 3 (11 pills)
	TRACK_ROAD3_TRAJECTORY,
	TRACK_ROAD3_TRAJECTORY,
	TRACK_ROAD3_TRAJECTORY,
	TRACK_ROAD3_TRAJECTORY,
	TRACK_ROAD3_TRAJECTORY,
	TRACK_ROAD3_TRAJECTORY,
	TRACK_ROAD3_TRAJECTORY,
	TRACK_ROAD3_TRAJECTORY,
	TRACK_ROAD3_TRAJECTORY,
	TRACK_ROAD3_TRAJECTORY,
	TRACK_ROAD3_TRAJECTORY,
	// Road 4 (11 pills)
	TRACK_ROAD4_TRAJECTORY,
	TRACK_ROAD4_TRAJECTORY,
	TRACK_ROAD4_TRAJECTORY,
	TRACK_ROAD4_TRAJECTORY,
	TRACK_ROAD4_TRAJECTORY,
	TRACK_ROAD4_TRAJECTORY,
	TRACK_ROAD4_TRAJECTORY,
	TRACK_ROAD4_TRAJECTORY,
	TRACK_ROAD4_TRAJECTORY,
	TRACK_ROAD4_TRAJECTORY,
	TRACK_ROAD4_TRAJECTORY,
};


void grPill::onDraw(void)
{
	LMaterial &mat = ShapePill.GetMaterial(0);

	mat.SetAmbientColor(Color);
	mat.SetDiffuseColor(Color);
	mat.SetSpecularColor(Color);

	gr3DSObject::onDraw();
}


grPill::grPill(void)
{
	// Set grObject attributes
	isAnimating = FALSE;
	radius = 15;

	// Set gr3DSObject attributes
	DList = &DListPill;

	// Set grOnTrackObject attributes
	trk_height = 10;

	// Set pill default color to yellow
	Color.r = 1;
	Color.g = 1;
}
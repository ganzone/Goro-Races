/*

File name: grPill.h

Description:
the pill class

*/

#ifndef _GRPILL_H
#define _GRPILL_H

// Number of pills on each quarter of track
#define PILL_ONTRACK_NUM		37

#include "gr3DSObject.h"
#include "grOnTrackObject.h"


class grPill : public gr3DSObject, public grOnTrackObject
{
// Attributes
public:
	static double const PillOnTrackAngle[PILL_ONTRACK_NUM];;
	static double const PillOnTrackTraj[PILL_ONTRACK_NUM];

	LColor3 Color;

// Overrides
public:
	void onDraw(void);
	void onAnimate(DWORD deltaTime) { }
	void onPrepare(void) { }

// Constructors and destructors
public:
	grPill(void);
	~grPill(void) { }
};


#endif // _GRPILL_H
#ifndef _GRCAR_H
#define _GRCAR_H

#include "gr3DSObject.h"
#include "grOnTrackObject.h"


class grCar : public gr3DSObject, public grOnTrackObject
{
// Attributes
public:
	double trk_trajChgSpeed;	// Trajectory change speed (0 for no movement,
								// >0 for external movement, <0 for internal movement)

	LColor3 Color;				// Car body color
	double HiSpeed;				// Car HI speed on track
	double LoSpeed;				// Car Lo speed on track
	double TrajChgSpeed;		// Car trajectory change speed
	double StartAngle;			// Initial OnTrack polar angle
	double StartRoad;			// Initial OnTrack road
	int EatenPills;				// Number of eaten pills
	BOOL isEatingPills;			// TRUE if car is eating pills

// Overrides
public:
	// Change car trjectory when it is not among track walls
	virtual void onAnimate(DWORD deltaTime);
	virtual void onCollision(grObject *obj);
	void onDraw(void);

	// Save object info to given file
	virtual void XMLWrite(CStdioFile &fp);
	// Load object info from given file
	virtual void XMLRead(Xml &Tag);

// Constructors and destructors
public:
	grCar(void);
	virtual ~grCar(void) { }
};


#endif // _GRPILL_H
/*

File name: grOnTrackObject.h

Description:
this class represents an object positionated on a the track. It is referenced
with polar coordinates for easier auto/manual displacement

*/


#ifndef _GRONTRACKOBJECT_H
#define _GRONTRACKOBJECT_H

#include <math.h>
// Define some useful costants
#define M_SQRT2		(1.41421356237309504880)
#define M_PI		(3.14159265358979323846)
#define M_2PI		(M_PI * 2)
#define M_PI_2		(M_PI / 2)
#define M_PI_3		(M_PI / 3)
#define M_PI_4		(M_PI / 4)
#define M_PI_5		(M_PI / 5)
#define M_PI_6		(M_PI / 6)
#define M_3PI_2		((M_PI * 3) / 2)


// Track inclination angle (in radiants)
#define TRACK_ANGLE					((double) (M_PI_6))

// Wall width
#define TRACK_WALL_WIDTH			((double) 6.4)

// Road width
#define TRACK_ROAD_WIDTH			((double) 38.41)

// Empty space between first wall and inner track limit
#define TRACK_EMPTY_WIDTH			((double) 17.37)

// Straight lenght
#define TRACK_STRAIGHT_LENGHT		((double) 241.0)

// Straight wall lenght
#define TRACK_STRAIGHT_WALL_LENGHT	((double) 130.0)

// Straight non-wall lenght
#define TRACK_STRAIGHT_EMPTY_LENGHT (TRACK_STRAIGHT_LENGHT - TRACK_STRAIGHT_WALL_LENGHT)


// Track road identification
typedef enum
{
	TRACK_ROAD_UNDEF,		// Used when object trajectory is out of track
	TRACK_ROAD1,
	TRACK_ROAD2,
	TRACK_ROAD3,
	TRACK_ROAD4
} trackRoad_t;

// Track areas
typedef enum
{
	TRACK_AREA_UNDEF,		// Used when object trajectory is out of track
	TRACK_AREA_STRAIGHT_N,
	TRACK_AREA_STRAIGHT_S,
	TRACK_AREA_STRAIGHT_W,
	TRACK_AREA_STRAIGHT_E,
	TRACK_AREA_CURVE_NW,
	TRACK_AREA_CURVE_NE,
	TRACK_AREA_CURVE_SW,
	TRACK_AREA_CURVE_SE
} trackArea_t;

// Road trajectories distance from inner track limit
#define TRACK_ROAD1_TRAJECTORY	\
	(TRACK_STRAIGHT_LENGHT	+	\
	 TRACK_EMPTY_WIDTH		+	\
	 TRACK_WALL_WIDTH * 1	+	\
	 TRACK_ROAD_WIDTH * 0	+	\
	 TRACK_ROAD_WIDTH / 2)
#define TRACK_ROAD2_TRAJECTORY	\
	(TRACK_STRAIGHT_LENGHT	+	\
	 TRACK_EMPTY_WIDTH		+	\
	 TRACK_WALL_WIDTH * 2	+	\
	 TRACK_ROAD_WIDTH * 1	+	\
	 TRACK_ROAD_WIDTH / 2)
#define TRACK_ROAD3_TRAJECTORY	\
	(TRACK_STRAIGHT_LENGHT	+	\
	 TRACK_EMPTY_WIDTH		+	\
	 TRACK_WALL_WIDTH * 3	+	\
	 TRACK_ROAD_WIDTH * 2	+	\
	 TRACK_ROAD_WIDTH / 2)
#define TRACK_ROAD4_TRAJECTORY	\
	(TRACK_STRAIGHT_LENGHT	+	\
	 TRACK_EMPTY_WIDTH		+	\
	 TRACK_WALL_WIDTH * 4	+	\
	 TRACK_ROAD_WIDTH * 3	+	\
	 TRACK_ROAD_WIDTH / 2)

// Roads limits distances from inner track limit
#define TRACK_ROAD1_LIMIT_LOWER	\
	(TRACK_ROAD1_TRAJECTORY - (TRACK_ROAD_WIDTH / 2) - (TRACK_WALL_WIDTH / 2))
#define TRACK_ROAD1_LIMIT_UPPER	\
	(TRACK_ROAD1_TRAJECTORY + (TRACK_ROAD_WIDTH / 2) + (TRACK_WALL_WIDTH / 2))
#define TRACK_ROAD2_LIMIT_LOWER	\
	(TRACK_ROAD2_TRAJECTORY - (TRACK_ROAD_WIDTH / 2) - (TRACK_WALL_WIDTH / 2))
#define TRACK_ROAD2_LIMIT_UPPER	\
	(TRACK_ROAD2_TRAJECTORY + (TRACK_ROAD_WIDTH / 2) + (TRACK_WALL_WIDTH / 2))
#define TRACK_ROAD3_LIMIT_LOWER	\
	(TRACK_ROAD3_TRAJECTORY - (TRACK_ROAD_WIDTH / 2) - (TRACK_WALL_WIDTH / 2))
#define TRACK_ROAD3_LIMIT_UPPER	\
	(TRACK_ROAD3_TRAJECTORY + (TRACK_ROAD_WIDTH / 2) + (TRACK_WALL_WIDTH / 2))
#define TRACK_ROAD4_LIMIT_LOWER	\
	(TRACK_ROAD4_TRAJECTORY - (TRACK_ROAD_WIDTH / 2) - (TRACK_WALL_WIDTH / 2))
#define TRACK_ROAD4_LIMIT_UPPER	\
	(TRACK_ROAD4_TRAJECTORY + (TRACK_ROAD_WIDTH / 2) + (TRACK_WALL_WIDTH / 2))


#include "grObject.h"


class AFX_EXT_CLASS grOnTrackObject :	public virtual grObject
{
// Attributes
protected:
	double trk_trajectory;			// Trajectory followed on the circuit
	double trk_angle;				// Polar angle referred to center of the track
	double trk_height;				// Height from track road
public:
	double trk_speed;				// Speed
	BOOL trk_revdir;				// TRUE if object upward direction must be reversed
	
// Functions
public:
	// Return track trajectory
	double const getOnTrackTrajectory(void) const { return trk_trajectory; }
	// Return track angle
	double const getOnTrackAngle(void) const { return trk_angle; }
	// Return track height
	double const getOnTrackHeight(void) const { return trk_height; }

	// Return current object area on track
	trackArea_t const getOnTrackArea(void) const;
	// Return current object road
	trackRoad_t const getOnTrackRoad(void) const;

	// Return TRUE if object is on track
	BOOL const isOnTrack(void) const;
	// Return TRUE if object is on a straight
	BOOL const isOnTrackStraight(void) const;
	// Return TRUE if object is on a curve
	BOOL const isOnTrackCurve(void) const;

	// Put object on track at the specified height
	void setOnTrackPos(double const angle) { setOnTrackPos(angle, trk_trajectory, trk_height); }
	void setOnTrackPos(double const angle, double const trajectory) { setOnTrackPos(angle, trajectory, trk_height); }
	void setOnTrackPos(double const angle, double const trajectory, double const height);
	
	// Return the primal track angle for which object is on a straight
	double const getOnTrackStraightAngle(void) const;
	// Return the distance from the center of the track
	double const getOnTrackDistanceFromTrackCenter(void) const;
	// Return the distance from inner track limit
	double const getOnTrackDistanceFromInnerTrackLimit(void) const;

private:
	// Compute X/Y-axis coordinates corresponding to current track position
	void updateOnTrackXY(void);
	// Compute Z-axis coordinate corresponding to current track position
	void updateOnTrackZ(void);
	// Compute orientation angles values corresponding to current track position
	void updateOnTrackOrientation(void);
	// Compute new X/Y/Z coordinates corresponding to current track position and height from the track
	void updateOnTrackHeight(void);

// Overloaded functions
public:
	void onAnimate(DWORD deltaTime);

// Constructors and destructors
public:
	grOnTrackObject(void);
	virtual ~grOnTrackObject(void) { }
};


#endif // _GRONTRACKOBJECT_H
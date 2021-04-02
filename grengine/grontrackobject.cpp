#include "stdafx.h"
#include "grOnTrackObject.h"


// Make angle to be >=0 and <M_2PI
double normalize_angle(double const angle)
{
	if ((angle >= 0) && (angle < M_2PI))
		return angle;

	double n_angle = fmod(angle, M_2PI);

	if (n_angle < 0)
		n_angle += M_2PI;

	return n_angle;
}


// Convert a road to its trajectory defined value
#define ROAD_TO_TRAJECTORY(road)	\
	((road == TRACK_ROAD1)	?	TRACK_ROAD1_TRAJECTORY	:	\
	 (road == TRACK_ROAD2)	?	TRACK_ROAD2_TRAJECTORY	:	\
	 (road == TRACK_ROAD3)	?	TRACK_ROAD3_TRAJECTORY	:	\
	 (road == TRACK_ROAD4)	?	TRACK_ROAD4_TRAJECTORY	:	\
	 (ASSERT(FALSE)))

// Convert a road to its road lower limit defined value
#define ROAD_TO_LIMIT_LOWER(road)	\
	((road == TRACK_ROAD1)	?	TRACK_ROAD1_LIMIT_LOWER	:	\
	 (road == TRACK_ROAD2)	?	TRACK_ROAD2_LIMIT_LOWER	:	\
	 (road == TRACK_ROAD3)	?	TRACK_ROAD3_LIMIT_LOWER	:	\
	 (road == TRACK_ROAD4)	?	TRACK_ROAD4_LIMIT_LOWER :	\
	 (ASSERT(FALSE)))

// Convert a road to its road upper limit defined value
#define ROAD_TO_LIMIT_UPPER(road)	\
	((road == TRACK_ROAD1)	?	TRACK_ROAD1_LIMIT_UPPER	:	\
	 (road == TRACK_ROAD2)	?	TRACK_ROAD2_LIMIT_UPPER	:	\
	 (road == TRACK_ROAD3)	?	TRACK_ROAD3_LIMIT_UPPER	:	\
	 (road == TRACK_ROAD4)	?	TRACK_ROAD4_LIMIT_UPPER	:	\
	 (ASSERT(FALSE)))




double const grOnTrackObject::getOnTrackStraightAngle(void) const
{
	return normalize_angle(atan(TRACK_STRAIGHT_LENGHT / trk_trajectory));
}


trackArea_t const grOnTrackObject::getOnTrackArea(void) const
{
	// Check if obhject is on track
	if (!isOnTrack())
		return TRACK_AREA_UNDEF;

	// Find road straight angle
	double straight_angle = getOnTrackStraightAngle();

	// Determine if angle refers a straight
	if (((trk_angle < straight_angle) && (trk_angle >= 0)) ||
		((trk_angle > M_2PI-straight_angle) && (trk_angle <= M_2PI)))
		return TRACK_AREA_STRAIGHT_E;

	if ((trk_angle > M_PI_2-straight_angle) && (trk_angle < M_PI_2+straight_angle))
		return TRACK_AREA_STRAIGHT_N;

	if ((trk_angle > M_PI-straight_angle) && (trk_angle < M_PI+straight_angle))
		return TRACK_AREA_STRAIGHT_W;
    
	if ((trk_angle > M_3PI_2-straight_angle) && (trk_angle < M_3PI_2+straight_angle))
		return TRACK_AREA_STRAIGHT_S;

	// Determine if angle refers a curve
	if ((trk_angle >= straight_angle) && (trk_angle <= M_PI_2-straight_angle))
		return TRACK_AREA_CURVE_NE;

	if ((trk_angle >= M_PI_2+straight_angle) && (trk_angle <= M_PI-straight_angle))
		return TRACK_AREA_CURVE_NW;

	if ((trk_angle >= M_PI+straight_angle) && (trk_angle <= M_3PI_2-straight_angle))
		return TRACK_AREA_CURVE_SW;

	if ((trk_angle >= M_3PI_2+straight_angle) && (trk_angle <= M_2PI-straight_angle))
		return TRACK_AREA_CURVE_SE;

	// We should never reach this point
	//ASSERT(FALSE);
	return (trackArea_t) 0;
}


trackRoad_t const grOnTrackObject::getOnTrackRoad(void) const
{
	// Check if object is on track
	if (!isOnTrack())
		return TRACK_ROAD_UNDEF;

	// Check in which road is the object
	if ((trk_trajectory >= TRACK_ROAD1_LIMIT_LOWER) &&
		(trk_trajectory < TRACK_ROAD1_LIMIT_UPPER))
		return TRACK_ROAD1;
	if ((trk_trajectory >= TRACK_ROAD2_LIMIT_LOWER) &&
		(trk_trajectory < TRACK_ROAD2_LIMIT_UPPER))
		return TRACK_ROAD2;
	if ((trk_trajectory >= TRACK_ROAD3_LIMIT_LOWER) &&
		(trk_trajectory < TRACK_ROAD3_LIMIT_UPPER))
		return TRACK_ROAD3;
	if ((trk_trajectory >= TRACK_ROAD4_LIMIT_LOWER) &&
		(trk_trajectory < TRACK_ROAD4_LIMIT_UPPER))
		return TRACK_ROAD4;

	// We should never reach this point
	ASSERT(FALSE);
	return (trackRoad_t) 0;
}


BOOL const grOnTrackObject::isOnTrack(void) const
{
	// Check if trajectory is out of roads
	if ((trk_trajectory >= TRACK_ROAD1_LIMIT_LOWER) &&
		(trk_trajectory <= TRACK_ROAD4_LIMIT_UPPER))
		return TRUE;
	
	return FALSE;
}


BOOL const grOnTrackObject::isOnTrackStraight(void) const
{
	// Check if object is on track
	if (!isOnTrack())
		return FALSE;

	// Get the area which the given parameters refers
	trackArea_t area = getOnTrackArea();
	
	// Check if object is on a straight
	if ((area == TRACK_AREA_STRAIGHT_N) || (area == TRACK_AREA_STRAIGHT_S) ||
		(area == TRACK_AREA_STRAIGHT_W) || (area == TRACK_AREA_STRAIGHT_E))
		return TRUE;

	// Check if object is on a curve
	if ((area == TRACK_AREA_CURVE_NE) || (area == TRACK_AREA_CURVE_NW) ||
		(area == TRACK_AREA_CURVE_SE) || (area == TRACK_AREA_CURVE_SW))
		return FALSE;

	// We should never reach this point
	ASSERT(FALSE);
	return FALSE;
}


BOOL const grOnTrackObject::isOnTrackCurve(void) const
{
	// Check if object is on track
	if (!isOnTrack())
		return FALSE;

	// Get the area which the given parameters refers
	trackArea_t area = getOnTrackArea();
	
	// Check if object is on a curve
	if ((area == TRACK_AREA_CURVE_NE) || (area == TRACK_AREA_CURVE_NW) ||
		(area == TRACK_AREA_CURVE_SE) || (area == TRACK_AREA_CURVE_SW))
		return TRUE;

	// Check if object is on a straight
	if ((area == TRACK_AREA_STRAIGHT_N) || (area == TRACK_AREA_STRAIGHT_S) ||
		(area == TRACK_AREA_STRAIGHT_W) || (area == TRACK_AREA_STRAIGHT_E))
		return FALSE;

	// We should never reach this point
	ASSERT(FALSE);
	return FALSE;
}


void grOnTrackObject::setOnTrackPos(double const angle, double const trajectory,
									double const height)
{
	// Set given attributes
	trk_trajectory = trajectory;
	trk_angle = normalize_angle(angle);
	trk_height = height;

	// Update object position and orientation
	updateOnTrackXY();
	updateOnTrackZ();
	updateOnTrackHeight();
	updateOnTrackOrientation();
}


void grOnTrackObject::updateOnTrackXY(void)
{
	// Find distance from track center
	double dist = getOnTrackDistanceFromTrackCenter();

	pos.x = dist * cos(trk_angle);
	pos.y = dist * sin(trk_angle);
}


void grOnTrackObject::updateOnTrackZ(void)
{
	// Z-axis equals to 0 if object is not on track
	if (!isOnTrack())
		pos.z = 0;

	// Get current track area
	trackArea_t area = getOnTrackArea();

	// Find distance from inner track limit
	double cx = fabs(getOnTrackDistanceFromTrackCenter() * cos(trk_angle)) - TRACK_STRAIGHT_LENGHT;
	double cy = fabs(getOnTrackDistanceFromTrackCenter() * sin(trk_angle)) - TRACK_STRAIGHT_LENGHT;

	// If object is on a straight then use only road-dependent axis value to compute Z
	if (isOnTrackStraight())
	{
		if ((area == TRACK_AREA_STRAIGHT_N) || (area == TRACK_AREA_STRAIGHT_S))
			pos.z = fabs((cy) * tan(TRACK_ANGLE));
		else
			pos.z = fabs((cx) * tan(TRACK_ANGLE));
	}
	else
	{
		// If object is on a curve then use the distance from center of the curve
		pos.z = fabs((double) (cx / cos(atan(cy/cx))) * tan(TRACK_ANGLE));
	}
}


void grOnTrackObject::updateOnTrackHeight(void)
{
	// Calculate height component
	double xHeight = 0;
	double yHeight = 0;
	double zHeight = 0;

	// Get current track area
	trackArea_t area = getOnTrackArea();

	if (isOnTrackStraight())
	{
		switch (area)
		{
		case TRACK_AREA_STRAIGHT_N: yHeight -= trk_height * sin(TRACK_ANGLE); break;
		case TRACK_AREA_STRAIGHT_S: yHeight += trk_height * sin(TRACK_ANGLE); break;
		case TRACK_AREA_STRAIGHT_W: xHeight += trk_height * sin(TRACK_ANGLE); break;
		case TRACK_AREA_STRAIGHT_E:	xHeight -= trk_height * sin(TRACK_ANGLE); break;
		}
	}
	else
	{
		// Find distance from inner track limit
		double cx = fabs(getOnTrackDistanceFromTrackCenter() * cos(trk_angle)) - TRACK_STRAIGHT_LENGHT;
		double cy = fabs(getOnTrackDistanceFromTrackCenter() * sin(trk_angle)) - TRACK_STRAIGHT_LENGHT;

		double curve_angle = atan(cy/cx);

		switch (area)
		{
		case TRACK_AREA_CURVE_NE:
			xHeight -= fabs(trk_height * sin(TRACK_ANGLE) * cos(curve_angle));
			yHeight -= fabs(trk_height * sin(TRACK_ANGLE) * sin(curve_angle));
			break;
		case TRACK_AREA_CURVE_NW:
			xHeight += fabs(trk_height * sin(TRACK_ANGLE) * cos(curve_angle));
			yHeight -= fabs(trk_height * sin(TRACK_ANGLE) * sin(curve_angle));
			break;
		case TRACK_AREA_CURVE_SW:
			xHeight += fabs(trk_height * sin(TRACK_ANGLE) * cos(curve_angle));
			yHeight += fabs(trk_height * sin(TRACK_ANGLE) * sin(curve_angle));
			break;
		case TRACK_AREA_CURVE_SE:
			xHeight -= fabs(trk_height * sin(TRACK_ANGLE) * cos(curve_angle));
			yHeight += fabs(trk_height * sin(TRACK_ANGLE) * sin(curve_angle));
			break;
		}
	}

	// Calculate height from track component
	zHeight = trk_height * cos(TRACK_ANGLE);

	// Modify position according to found height offsets
	pos.x += xHeight;
	pos.y += yHeight;
	pos.z += zHeight;
}

void grOnTrackObject::updateOnTrackOrientation(void)
{
	// Get track Area
	trackArea_t area = getOnTrackArea();

	// Find z-axis rotation angle
	if (isOnTrackStraight())
	{
		switch (area)
		{
		case TRACK_AREA_STRAIGHT_N:	rot_angle = CVector(0, TRACK_ANGLE, -M_PI_2); break;
		case TRACK_AREA_STRAIGHT_S:	rot_angle = CVector(0, TRACK_ANGLE, M_PI_2); break;
		case TRACK_AREA_STRAIGHT_W:	rot_angle = CVector(0, TRACK_ANGLE, M_PI); break;
		case TRACK_AREA_STRAIGHT_E:	rot_angle = CVector(0, TRACK_ANGLE, 0); break;
		default: ASSERT(FALSE); // We should never reach this point
		}
	}
	else
	{
		double d = getOnTrackDistanceFromTrackCenter();
		double x = fabs(d * cos(trk_angle)) - TRACK_STRAIGHT_LENGHT;
		double y = fabs(d * sin(trk_angle)) - TRACK_STRAIGHT_LENGHT;

		switch (area)
		{
		case TRACK_AREA_CURVE_NE: rot_angle = CVector(0, TRACK_ANGLE, -(			+atan(y/x))); break;
		case TRACK_AREA_CURVE_NW: rot_angle = CVector(0, TRACK_ANGLE, -(M_PI_2	+atan(x/y))); break;
		case TRACK_AREA_CURVE_SW: rot_angle = CVector(0, TRACK_ANGLE, -(M_PI		+atan(y/x))); break;
		case TRACK_AREA_CURVE_SE: rot_angle = CVector(0, TRACK_ANGLE, -(M_3PI_2	+atan(x/y))); break;
		default: ASSERT(FALSE); // We should never reach this point
		}
	}

	// Set object upward direction
	if (trk_revdir == 1)
	{
		rot_angle.x =  rot_angle.x;
		rot_angle.y = -rot_angle.y;
		rot_angle.z =  rot_angle.z + M_PI;
	}

	// Normalize angles
	rot_angle.x = normalize_angle(rot_angle.x);
	rot_angle.y = normalize_angle(rot_angle.y);
	rot_angle.z = normalize_angle(rot_angle.z);
}


double const grOnTrackObject::getOnTrackDistanceFromTrackCenter() const
{
	// Make the angle to be >=0 and <M_PI_2
	double angle = fmod(trk_angle, M_PI_2);
	if (angle < 0)
		angle += M_PI_2;

	// Check if area references a straight or a curve
	if (isOnTrackStraight())
	{
		// Angle references a straight
		if (angle < M_PI_4)
			return fabs(trk_trajectory / cos(angle));
		else
			return fabs(trk_trajectory / sin(angle));
	}
	else
	{
		// Angle references a curve
		double trkdst = (TRACK_STRAIGHT_LENGHT * M_SQRT2) * cos(angle-M_PI_4);

		trkdst += (trk_trajectory - TRACK_STRAIGHT_LENGHT) * cos(
			asin(fabs((TRACK_STRAIGHT_LENGHT * M_SQRT2) * sin(angle-M_PI_4))
				/ (trk_trajectory - TRACK_STRAIGHT_LENGHT)));
		
        return fabs(trkdst);
	}
}


void grOnTrackObject::onAnimate(DWORD deltaTime)
{
	// Compute how much the object has moved (S = v * t)
	double displacement = trk_speed * deltaTime;

	// Check if object has not to be moved
	if (displacement == 0)
		return;

	// Get current object trajectory straight angle
	double straight_angle = getOnTrackStraightAngle();

	// Compute curve ray
	double curve_ray = trk_trajectory - TRACK_STRAIGHT_LENGHT;

	// Move the object on track for needed displacement
	while (fabs(displacement) > 0)
	{
		// Make the angle to be >=0 and <=M_PI_2
		double angle = fmod(trk_angle, M_PI_2);
		if (angle < 0)
			angle += M_PI_2;

		// Compute angle and displacement delta depending from object position
		double deltaAngle;
		double deltaDisp;

		if (isOnTrackStraight())
		{
			deltaDisp = fabs(displacement);
			deltaAngle = fabs(atan(deltaDisp/trk_trajectory));
		}
		else // !isOnTrackStraight()
		{
			deltaDisp = fabs(displacement);
			deltaAngle = deltaDisp / trk_trajectory; // not very sportive...

			if (deltaAngle < 0.00001)
				deltaAngle = 0.00001;
		}

		// Update object ontrack-angle
		if (trk_speed > 0)
		{
			displacement -= deltaDisp;
			trk_angle += deltaAngle;
		}
		else
		{
			displacement += deltaDisp;
			trk_angle -= deltaAngle;
		}
	}

	// Update object position
	setOnTrackPos(trk_angle, trk_trajectory, trk_height);
}


grOnTrackObject::grOnTrackObject(void)
{
	setOnTrackPos(0, TRACK_ROAD4_TRAJECTORY, 0);
	trk_speed = 0;
	trk_revdir = 0;
}
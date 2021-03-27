#ifndef _GRTRACK_H
#define _GRTRACK_H

#include "gr3DSObject.h"


class grTrack :	public gr3DSObject
{
// Overloaded functions
public:
	void onDraw(void);

// Constructors and destructors
public:
	grTrack(void) { DList = &DListTrack; }
	~grTrack(void) { }
};


#endif // _GRTRACK_H
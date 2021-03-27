/*

File name: grWorld.h

Description:
grWorld class defines the world that the grEngine is running, displaying and
interacting with.

*/


#ifndef _GRWORLD_H
#define _GRWORLD_H


// Include all 3DStudio objects classes
#include "grTrack.h"
#include "grPill.h"
#include "grHumanCar.h"
#include "grComputerCar.h"

// Include MFC multithreading synchronization support
#include <afxmt.h>

#include "grObject.h"


class AFX_EXT_CLASS grWorld : public grObject
{
// Attributes
private:
	// isLoaded() flag
	BOOL isLoadedFlag;

public:
	// Mutex for exclusive access to world objects
	CMutex mutex;

	// Default world objects
	grTrack Track;
	grHumanCar HumanCar;
	grComputerCar ComputerCar;
	grPill Pill[PILL_ONTRACK_NUM*4];

// Functions
public:
	// Is any world file loaded ?
	BOOL const isLoaded(void) const { return isLoadedFlag; }
	// Load a specific world file
	BOOL const load(CString const &file);
	// Unload world objects
	BOOL const unload(void);

// Overrides
public:
	// Save object info to given file
	virtual void XMLWrite(CStdioFile &fp);
	// Load object info from given file
	virtual void XMLRead(Xml &Tag);


// Constructors and destructors
public:
	grWorld(void);
	~grWorld(void);
};


#endif // _GRWORLD_H
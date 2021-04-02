/*

File name: grEngine.h

Description:
grEngine class provides a thread for every of its instances, the run/stop
engine functions, the view camera(s) and the main loop update function. You
should inherit this class and ovverride mainLoop() function to use a grEngine
instance.

*/


#ifndef _GRENGINE_H
#define _GRENGINE_H

#include "grViewCamera.h"
#include "grWorld.h"

#include <vector>
using namespace std;


class AFX_EXT_CLASS grEngine : public CWinThread
{
// Attributes
private:
	BOOL isRunningFlag;					// Engine-Is-Running flag
public:
	grWorld world;						// Root node of grEngine scene graph
	vector <grViewCamera *> camList;	// View camera(s) pointers list

// Functions
protected:
	// Make a main processing loop (objects managing, camera reposition, ecc...)
	// dependently from how application overrides this function
	virtual BOOL const mainLoop(DWORD const deltaTime) { return TRUE; }
public:
	// Is the engine running ?
	BOOL const isRunning(void) const { return isRunningFlag; }
	// Make the engine run
	void run(void) { isRunningFlag = TRUE; }
	// Make the engine stop
	void stop(void) { isRunningFlag = FALSE; }

	// Load given world file
	BOOL const load(CString const &file);
	// Unload current world
	BOOL const unload(void);

private:
	// Attach view cameras to world objects tree
	void attachViewCameras(void);
	// Detach view cameras from world objects tree
	void detachViewCameras(void);
	// Invalidate all view cameras listed in camList vector
	void invalidateViewCameras(void);

// Overloaded Functions
public:
	BOOL InitInstance(void) { return TRUE; }
	BOOL OnIdle(LONG lCount);

// Constructors and destructors
public:
	grEngine(void);
	virtual ~grEngine(void) { }
};


#endif	// _GRENGINE_H
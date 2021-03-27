/*

File name: grEngine.cpp

Description:
see grEngine.h for a description about this class

*/


#include "stdafx.h"
#include "grEngine.h"


BOOL const grEngine::load(CString const &file)
{
	// Check if any world file is already loaded
	if (world.isLoaded())
		unload();

	// Load world file
	BOOL retval = world.load(file);

	// Re-Attach view camera(s)
	attachViewCameras();

	return retval;
}


BOOL const grEngine::unload(void)
{
	// Detach view camera(s) to prevent destruction
	detachViewCameras();

	// Unload non-default world object
	BOOL retval = world.unload();

	return retval;
}


BOOL grEngine::OnIdle(LONG lCount)
{
	static DWORD deltaTime = 0;
	static DWORD lastRedrawTime = 0;
	static DWORD lastUpdateTime = GetTickCount();

	BOOL retval = TRUE;		// Used to return mainloop() return value

	// Calculate elapsed time
	deltaTime = GetTickCount() - lastUpdateTime;
	lastUpdateTime = GetTickCount();

	// Check if engine is running
	if (isRunning())
	{
		CSingleLock world_mutex(&world.mutex, TRUE);

		// Call mainLoop() user-defined function and check if app must be closed
		if (!(retval = mainLoop(deltaTime)))
			AfxGetApp()->m_pMainWnd->PostMessage(WM_CLOSE);

		// Do world objects pshysics computations
		world.animate(deltaTime);
		world.prepare();

		world_mutex.Unlock();
	}

	// Redraw all views if more than 1000/60 ticks were elapsed (60 fps)
	if (lastUpdateTime - lastRedrawTime > (1000/60))
	{
		// Skip frame if deltaTime is higher than 50 milliseconds
		if (deltaTime < 50)
			// Invalidate the context of each view camera
			invalidateViewCameras();

		// Update last-redraw time variable
		lastRedrawTime = lastUpdateTime;
	}

	return retval;
}


void grEngine::attachViewCameras(void)
{
	vector<grViewCamera *>::iterator cam_Iter;
	for (cam_Iter = camList.begin(); cam_Iter != camList.end(); cam_Iter++)
	{
		grViewCamera *cam = *cam_Iter;
		world.attach(cam);
	}
}


void grEngine::detachViewCameras(void)
{
	vector<grViewCamera *>::iterator cam_Iter;
	for (cam_Iter = camList.begin(); cam_Iter != camList.end(); cam_Iter++)
	{
		grViewCamera *cam = *cam_Iter;
		cam->detach();
	}
}


void grEngine::invalidateViewCameras(void)
{
	vector<grViewCamera *>::iterator cam_Iter;
	for (cam_Iter = camList.begin(); cam_Iter != camList.end(); cam_Iter++)
	{
		grViewCamera *cam = *cam_Iter;
		cam->Invalidate();
	}
}

grEngine::grEngine(void)
{
	// Set engine flags
	isRunningFlag = FALSE;

	CreateThread();
	SetThreadPriority(THREAD_PRIORITY_IDLE);
}
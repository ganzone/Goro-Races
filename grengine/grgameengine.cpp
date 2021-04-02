/*

File name: grGameEngine.cpp

Description:
see grGameEngine.h file for a descrition about this file

*/


#include "stdafx.h"
#include "grGameEngine.h"
#include "grCar.h"

#define DEMO_MODE_CAMERA_DISTANCE	70		// Camera distance from displayed car in demo-mode
#define DEMO_MODE_CAMERA_HEIGHT		20		// Camera height from displayed car in demo-mode

#define PLAY_MODE_CAMERA_DISTANCE	500		// Camera [X,Y] polar distance from center of the track
#define PLAY_MODE_CAMERA_ANGLE		M_3PI_2	// Camera polar angle referred to center of track
#define PLAY_MODE_CAMERA_HEIGHT		1000	// Camera height from "0" of Z-axis

#define DEMO_MODE_CAR_SPEED			0.08	// Car speed in demo mode

#define NEW_GAME_WAIT_TIME			2000	// Time to wait after new-game init to start the game


BOOL const grGameEngine::setGameMode(GameMode_t const GameMode)
{
	switch (GameMode)
	{
	case GAME_MODE_DEMO:
		InitDemoMode();
		run();
        break;
	case GAME_MODE_PLAY:
		if (this->GameMode != GAME_MODE_PAUSE)
			InitPlayMode();
		run();
		break;
	case GAME_MODE_PAUSE:
		stop();
		break;
	case GAME_MODE_EXIT:
		run();
		break;
	}

	this->GameMode = GameMode;

	return TRUE;
}


BOOL const grGameEngine::mainLoop(DWORD const deltaTime)
{
	// Check if ESC button was pressed
	if (GetAsyncKeyState(VK_ESCAPE))
		setGameMode(GAME_MODE_EXIT);

	switch (GameMode)
	{
	case GAME_MODE_DEMO:
		return LoopDemoMode(deltaTime);
	case GAME_MODE_PLAY:
		return LoopPlayMode(deltaTime);
	case GAME_MODE_PAUSE:
		return TRUE;
	case GAME_MODE_EXIT:
		return FALSE;

	default:
		return TRUE;
	}
}

BOOL const grGameEngine::InitDemoMode(void)
{
	// Initialize camera position
	InitCameraDemoMode();

	// Initialize human car attributes
	world.HumanCar.setOnTrackPos(-M_PI_6, TRACK_ROAD3_TRAJECTORY);
	world.HumanCar.trk_speed = DEMO_MODE_CAR_SPEED;
	world.HumanCar.trk_trajChgSpeed = 0;
	world.HumanCar.isColliding = FALSE;
	world.HumanCar.isVisible = TRUE;

	// Disable computer car
	world.ComputerCar.isVisible = FALSE;
	world.ComputerCar.isAnimating = FALSE;

	// Disable all pills
	for (int p=0; p<PILL_ONTRACK_NUM*4; p++)
	{
		world.Pill[p].isVisible = FALSE;
		world.Pill[p].isColliding = FALSE;
	}

	return TRUE;
}

BOOL const grGameEngine::InitPlayMode(void)
{
	// Initialize camera position
	InitCameraPlayMode();

	// Set human car attributes
	world.HumanCar.setOnTrackPos(world.HumanCar.StartAngle, world.HumanCar.StartRoad);
	world.HumanCar.trk_speed = 0;
	world.HumanCar.trk_trajChgSpeed = 0;
	world.HumanCar.isVisible = TRUE;
	world.HumanCar.isBlinking = TRUE;
	world.HumanCar.lastBlinkTime = 0;
	world.HumanCar.isAnimating = TRUE;
	world.HumanCar.isColliding = TRUE;
	world.HumanCar.isDead = FALSE;
	world.HumanCar.isEatingPills = TRUE;
	world.HumanCar.EatenPills = 0;
	
	// Set computer car attributes
	world.ComputerCar.setOnTrackPos(world.ComputerCar.StartAngle, world.ComputerCar.StartRoad);
	world.ComputerCar.trk_speed = 0;
	world.ComputerCar.trk_trajChgSpeed = 0;
	world.ComputerCar.isVisible = TRUE;
	world.ComputerCar.isAnimating = TRUE;
	world.ComputerCar.isColliding = TRUE;
	world.ComputerCar.isDead = FALSE;
	world.ComputerCar.isEatingPills = FALSE;
	world.ComputerCar.EatenPills = 0;
	world.ComputerCar.setOtherCar(world.HumanCar);

	// Enable all pills
	for (int p=0; p<PILL_ONTRACK_NUM*4; p++)
	{
		world.Pill[p].isVisible = TRUE;
		world.Pill[p].isColliding = TRUE;
		world.Pill[p].isDead = FALSE;
	}

	// Set initial time to wait before to make the cars run
	NewGameWaitTime = NEW_GAME_WAIT_TIME;

	return TRUE;
}


BOOL const grGameEngine::LoopDemoMode(DWORD const deltaTime)
{
	// Update camera position
	UpdateCameraDemoMode(deltaTime);

	// Continue looping
	return TRUE;
}


BOOL const grGameEngine::LoopPlayMode(DWORD const deltaTime)
{
	// Update camera position
	UpdateCameraPlayMode(deltaTime);

	// Wait a while before make cars to run
	if (NewGameWaitTime > 0)
	{
		NewGameWaitTime -= deltaTime;

		// Make the cars run if enough time elapsed
		if (NewGameWaitTime <= 0)
		{
			world.HumanCar.isBlinking = FALSE;
			world.HumanCar.isVisible = TRUE;
			world.HumanCar.trk_speed = world.HumanCar.LoSpeed;

			world.ComputerCar.trk_speed = -world.ComputerCar.LoSpeed;
		}

		return TRUE;
	}

	// Check if there are no more pills
	if (world.HumanCar.EatenPills == PILL_ONTRACK_NUM*4)
	{
		AfxMessageBox("You Win !", MB_OK | MB_SYSTEMMODAL | MB_ICONEXCLAMATION);
		setGameMode(GAME_MODE_DEMO);
		return TRUE;
	}

	// Check if HumanCar died
	if (world.HumanCar.isDead)
	{
		AfxMessageBox("You Lose !", MB_OK | MB_SYSTEMMODAL | MB_ICONSTOP);
		setGameMode(GAME_MODE_DEMO);
		return TRUE;
	}

	// Get current track position
	trackArea_t area = world.HumanCar.getOnTrackArea();

	// Reset HumanCar trajectory change speed
	world.HumanCar.trk_trajChgSpeed = 0;

	// Check user input
	if (GetAsyncKeyState(VK_UP))
		switch (area)
		{
		case TRACK_AREA_STRAIGHT_N: world.HumanCar.trk_trajChgSpeed = +world.HumanCar.TrajChgSpeed; break;
		case TRACK_AREA_STRAIGHT_S: world.HumanCar.trk_trajChgSpeed = -world.HumanCar.TrajChgSpeed; break;
		}
	if (GetAsyncKeyState(VK_DOWN))
		switch (area)
		{
		case TRACK_AREA_STRAIGHT_N: world.HumanCar.trk_trajChgSpeed = -world.HumanCar.TrajChgSpeed; break;
		case TRACK_AREA_STRAIGHT_S: world.HumanCar.trk_trajChgSpeed = +world.HumanCar.TrajChgSpeed; break;
		}
	if (GetAsyncKeyState(VK_LEFT))
		switch (area)
		{
		case TRACK_AREA_STRAIGHT_W: world.HumanCar.trk_trajChgSpeed = +world.HumanCar.TrajChgSpeed; break;
		case TRACK_AREA_STRAIGHT_E: world.HumanCar.trk_trajChgSpeed = -world.HumanCar.TrajChgSpeed; break;
		}
	if (GetAsyncKeyState(VK_RIGHT))
		switch (area)
		{
		case TRACK_AREA_STRAIGHT_W: world.HumanCar.trk_trajChgSpeed = -world.HumanCar.TrajChgSpeed; break;
		case TRACK_AREA_STRAIGHT_E: world.HumanCar.trk_trajChgSpeed = +world.HumanCar.TrajChgSpeed; break;
		}

	if (GetAsyncKeyState(VK_SHIFT))
		world.HumanCar.trk_speed = world.HumanCar.HiSpeed;
	else
		world.HumanCar.trk_speed = world.HumanCar.LoSpeed;

	// Continue looping
	return TRUE;
}


void grGameEngine::InitCameraDemoMode(void)
{
	// Check if a camera is available
	if (camList.size() == 0)
		return;
		
	// Get Camera pointer
	grViewCamera *Camera = camList.at(0);
}


void grGameEngine::InitCameraPlayMode(void)
{
	// Check if a camera is available
	if (camList.size() == 0)
		return;
		
	// Get Camera pointer
	grViewCamera *Camera = camList.at(0);

	// Set default playing camera position and view direction
	Camera->LookAtPos.set(0,0,0);
	Camera->LookAtAngle = PLAY_MODE_CAMERA_ANGLE;
	Camera->LookAtDistance = PLAY_MODE_CAMERA_DISTANCE;
	Camera->LookAtHeight = PLAY_MODE_CAMERA_HEIGHT;
}


void grGameEngine::UpdateCameraDemoMode(DWORD deltaTime)
{
	// Check if a camera is available
	if (camList.size() == 0)
		return;
		
	// Get Camera pointer
	grViewCamera *Camera = camList.at(0);

	Camera->Lead(world.HumanCar, DEMO_MODE_CAMERA_DISTANCE, 0, DEMO_MODE_CAMERA_HEIGHT);
}


void grGameEngine::UpdateCameraPlayMode(DWORD deltaTime)
{
	// Check if a camera is available
	if (camList.size() == 0)
		return;
		
	// Get Camera pointer
	grViewCamera *Camera = camList.at(0);
}
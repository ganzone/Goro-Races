/*

File name: grGameEngine.h

Description:
the logic of Goro Races game

*/


#ifndef _GRGAMEENGINE_H
#define _GRGAMEENGINE_H

// Available game modes
typedef enum
{
	GAME_MODE_DEMO,			// Game is in demo mode
	GAME_MODE_PLAY,			// Game is playing
	GAME_MODE_PAUSE,		// Game is paused
    GAME_MODE_EXIT			// Game must exit
} GameMode_t;


#include "grEngine.h"


class AFX_EXT_CLASS grGameEngine : public grEngine
{
// Attributes
private:
	// Game mode
	GameMode_t GameMode;
	// Time to wait before to start a new game
	int NewGameWaitTime;

// Functions
public:
	// Returns current game state
	GameMode_t const getGameMode(void) const { return GameMode; }
	// Set given game state (returns FALSE if it was not possible to set given state)
	BOOL const setGameMode(GameMode_t const GameMode);

private:
	BOOL const InitDemoMode(void);
	BOOL const InitPlayMode(void);

	BOOL const LoopDemoMode(DWORD const deltaTime);
	BOOL const LoopPlayMode(DWORD const deltaTime);

	void InitCameraDemoMode(void);
	void InitCameraPlayMode(void);

	void UpdateCameraDemoMode(DWORD deltaTime);
	void UpdateCameraPlayMode(DWORD deltaTime);

	grViewCamera *GetCamera(void) const;

// Overrides
protected:
	BOOL const mainLoop(DWORD const deltaTime);

// Constructors and destructors
public:
	grGameEngine(void) { setGameMode(GAME_MODE_DEMO); }
	~grGameEngine(void) { }
};


#endif // _GRGAMEENGINE_H
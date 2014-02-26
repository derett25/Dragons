// Class that represents the start menu of the game
// Author: Linus Esbjörnsson || a12lines
// Mail: linuse93@hotmail.com || a12lines@student.his.se
// Department of Communication and Information
// Högskolan i Skövde

#ifndef INCLUDED_GAMEMENU
#define INCLUDED_GAMEMENU

#include "GameContext.h"
#include "Camera.h"
#include "GameText.h"

class GameMenu : public GameContext {
public:
	GameMenu();
	~GameMenu();
	virtual void run();
	virtual void draw(SDL_Surface* src_surface);
	virtual bool handleEvent(SDL_Event& e, ContextContainer& queue);
	static void initialize();
	static void finalize();
private:
	void moveScreen();
	Camera mCamera;
	GameText mClickText;
};

#endif


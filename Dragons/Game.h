// Class that represents the main window
// Author: Linus Esbjörnsson || a12lines
// Mail: linuse93@hotmail.com || a12lines@student.his.se
// Department of Communication and Information
// Högskolan i Skövde

#ifndef INCLUDED_GAME
#define INCLUDED_GAME

#include "SDL.h"
#include "CustomMouse.h"
#include "GameContext.h"

class Game : public ContextContainer {
public:
	Game(const char* title, int width, int height);
	~Game();
	virtual void add(GameContext* context);
	virtual void pop();
	void run();
	static void initialize();
	static void finalize();
private:
	void draw();
	bool handleEvents();
	SDL_Window* mWindow;
	SDL_Surface* mSurface;
	CustomMouse mMouse;
	bool mRunning;
	SDL_Event event;
	GameContext::ContextQueue mContextQueue;
};

#endif


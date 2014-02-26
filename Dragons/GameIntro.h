// Class that represents the introduction screen of the game
// Author: Linus Esbjörnsson || a12lines
// Mail: linuse93@hotmail.com || a12lines@student.his.se
// Department of Communication and Information
// Högskolan i Skövde

#ifndef INCLUDED_GAMEINTRO
#define INCLUDED_GAMEINTRO

#include "GameContext.h"
#include "Camera.h"

class GameIntro : public GameContext {
public:
	GameIntro();
	~GameIntro();
	virtual void run();
	virtual void draw(SDL_Surface* src_surface);
	virtual bool handleEvent(SDL_Event& e, ContextContainer& queue);
	static void initialize();
	static void finalize();
private:
	void checkCamera();
	Camera mCamera;
};

#endif


// Protocol class of the game contexts
// Author: Linus Esbjörnsson || a12lines
// Mail: linuse93@hotmail.com || a12lines@student.his.se
// Department of Communication and Information
// Högskolan i Skövde

#ifndef INCLUDED_GAMECONTEXT
#define INCLUDED_GAMECONTEXT

#include "SDL.h"
#include <queue>
#include "ContextContainer.h"

class GameContext {
public:
	typedef std::queue<GameContext*> ContextQueue;
	virtual ~GameContext();
	virtual void run() = 0;
	virtual void draw(SDL_Surface* src_surface) = 0;
	virtual bool handleEvent(SDL_Event& e, ContextContainer& queue) = 0;
};

#endif
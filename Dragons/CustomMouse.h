// Class that represents the glove cursor
// Author: Linus Esbj�rnsson || a12lines
// Mail: linuse93@hotmail.com || a12lines@student.his.se
// Department of Communication and Information
// H�gskolan i Sk�vde

#ifndef INCLUDED_CUSTOMMOUSE
#define INCLUDED_CUSTOMMOUSE

#include "SDL.h"

class Vector2D;

class CustomMouse {
public:
	CustomMouse();
	~CustomMouse();
	void render(SDL_Surface* src_surface) const;
	bool handleEvents(SDL_Event& e);
	static void initialize();
	static void finalize();
	static Vector2D getMouseState();
private:
	int mFrame;
};

#endif
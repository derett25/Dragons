// Static class that is used for resource loading and drawing
// Author: Linus Esbjörnsson || a12lines
// Mail: linuse93@hotmail.com || a12lines@student.his.se
// Department of Communication and Information
// Högskolan i Skövde

#ifndef INCLUDED_GAMESURFACE
#define INCLUDED_GAMESURFACE

#include "SDL.h"

class Vector2D;

struct GameSurface {
	static SDL_Surface* onLoad(const char* file);
	static bool draw(SDL_Surface* src_surface, SDL_Surface* dest_surface, const Vector2D& vector);
	static bool draw(SDL_Surface* src_surface, SDL_Surface* dest_surface, const Vector2D& vector, SDL_Rect clip);
	static bool draw(SDL_Surface* src_surface, SDL_Surface* dest_surface, const Vector2D& vector, int width, int height);
	static bool drawRect(SDL_Surface* src_surface, const Vector2D& vector, int width, int height, int color);
};

#endif
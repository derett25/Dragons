// Class that represents text in the game
// Author: Linus Esbjörnsson || a12lines
// Mail: linuse93@hotmail.com || a12lines@student.his.se
// Department of Communication and Information
// Högskolan i Skövde

#ifndef INCLUDED_GAMETEXT
#define INCLUDED_GAMETEXT

#include "SDL.h"
#include "Vector2D.h"
#include "SDL_ttf.h"
#include <string>

class GameText {
public:
	GameText();
	GameText(const std::string text, int size=20, int r=0, int g=0, int b=0);
	~GameText();
	void draw(SDL_Surface* src_surface, const Vector2D& vector);
	void setText(const std::string text, int size=20, int r=0, int g=0, int b=0);
private:
	SDL_Surface* mTextSurface;
	TTF_Font* mTextFont;
};

#endif


// Class that represents a background tile in the game
// Author: Linus Esbj�rnsson || a12lines
// Mail: linuse93@hotmail.com || a12lines@student.his.se
// Department of Communication and Information
// H�gskolan i Sk�vde

#ifndef INCLUDED_GAMETILE
#define INCLUDED_GAMETILE

#include "SDL.h"
#include "Vector2D.h"

class Camera;

class GameTile {
public:
	GameTile();
	GameTile(const Vector2D& vector);
	~GameTile();
	void draw(SDL_Surface* src_surface, Camera& camera);
	Vector2D& getVector();
	static void initialize();
	static void finalize();
private:
	SDL_Rect mClip;
	Vector2D mVector;
};

#endif


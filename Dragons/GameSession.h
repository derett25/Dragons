// Class that represents the game
// Author: Linus Esbjörnsson || a12lines
// Mail: linuse93@hotmail.com || a12lines@student.his.se
// Department of Communication and Information
// Högskolan i Skövde

#ifndef INCLUDED_GAMESESSION
#define INCLUDED_GAMESESSION

#include "GameContext.h"
#include "SDL.h"
#include "GameMap.h"
#include "GameTimer.h"
#include "Camera.h"
#include "GameText.h"

class Entity;

class GameSession : public GameContext {
public:
	GameSession();
	~GameSession();
	virtual void run();
	virtual void draw(SDL_Surface* src_surface);
	virtual bool handleEvent(SDL_Event& e, ContextContainer& queue);
	static void initialize();
	static void finalize();
private:
	void checkCamera();
	void update();
	void checkPickup(Vector2D& vector);
	void checkSell(Vector2D& vector);
	void addFood();
	Entity* mEntityPicked;
	GameMap mMap;
	Camera mCamera;
	GameText mMoneyText;
	GameTimer mMoneyIncrease;
	int mMoney;
};

#endif
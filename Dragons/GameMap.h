// Class that stores all the physical objects of the game and handles them
// Author: Linus Esbjörnsson || a12lines
// Mail: linuse93@hotmail.com || a12lines@student.his.se
// Department of Communication and Information
// Högskolan i Skövde

#ifndef INCLUDED_GAMEMAP
#define INCLUDED_GAMEMAP

#include "GameTile.h"
#include "Camera.h"
#include "Defines.h"
#include "Entity.h"
#include "EntityContainer.h"

class GameMap : public EntityContainer {
public:
	typedef std::vector<Entity*> EntityVector;
	GameMap();
	~GameMap();
	virtual void add(Entity* entity);
	virtual void remove(Entity* entity);
	void update();
	void draw(SDL_Surface* src_surface, Camera& camera);
	Entity* getIntersect(Vector2D& vector);
	Vector2D getSize() const;
	static void initialize();
	static void finalize();
private:
	void generateMap();
	void renderForeground(SDL_Surface* src_surface, Camera& camera);
	void renderBackground(SDL_Surface* src_surface, Camera& camera);
	void killDeadEntities();
	void checkBoundaries();
	void checkCollision();
	bool isOverlap(Vector2D& vector0, Vector2D& vector1);
	GameTile mTiles[MAP_X][MAP_Y];
	EntityVector mEntities;
};

#endif


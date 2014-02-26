// Class that defines global behavior and complex implementation for EntityImp
// Author: Linus Esbjörnsson || a12lines
// Mail: linuse93@hotmail.com || a12lines@student.his.se
// Department of Communication and Information
// Högskolan i Skövde

#ifndef INCLUDED_ENTITY
#define INCLUDED_ENTITY

#include "EntityImp.h"

class Entity {
public:
	Entity(EntityImp* entity);
	~Entity();
	void draw(SDL_Surface* src_surface, Camera& camera);
	void update(EntityContainer& entities);
	Vector2D& getVector();
	EntityImp::Category getCategory() const;
	EntityImp::Priority getPriority() const;
	bool isAlive() const;
	bool handleEvents(EntityImp::GameEvent e);
	int getValue() const;
	int getMaxHealth() const;
	int getHealth() const;
	void setHealth(int health);
	static void initialize();
	static void finalize();
private:
	void drawHealth(SDL_Surface* src_surface, Camera& camera) const;
	EntityImp* mEntity;
	bool mPicked;
};

#endif
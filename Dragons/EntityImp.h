// Protocol class for entities
// Author: Linus Esbjörnsson || a12lines
// Mail: linuse93@hotmail.com || a12lines@student.his.se
// Department of Communication and Information
// Högskolan i Skövde

#ifndef INCLUDED_ENTITYIMP
#define INCLUDED_ENTITYIMP

#include "SDL_surface.h"
#include "Vector2D.h"
#include <vector>
#include "Camera.h"
#include "EntityContainer.h"

class EntityImp {
public:
	enum Category {
		NPC,
		CONSUMABLE,
		ITEM
	};
	enum GameEvent{
		ON_SELL,
		ON_PICKUP,
		ON_RELEASED,
		ON_EAT
	};
	enum Priority{
		FOREGROUND,
		BACKGROUND
	};
	virtual ~EntityImp();
	virtual void draw(SDL_Surface* src_surface, Camera& camera) = 0;
	virtual void update(EntityContainer& entities) = 0;
	virtual Vector2D& getVector() = 0;
	virtual Category getCategory() const = 0;
	virtual Priority getPriority() const = 0;
	virtual bool isAlive() const = 0;
	virtual bool handleEvents(GameEvent e) = 0;
	virtual int getValue() const = 0;
	virtual int getHealth() const = 0; 
	virtual int getMaxHealth() const = 0;
	virtual void setHealth(int health) = 0;
};

#endif
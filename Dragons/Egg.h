// Class that represents an egg
// Author: Linus Esbjörnsson || a12lines
// Mail: linuse93@hotmail.com || a12lines@student.his.se
// Department of Communication and Information
// Högskolan i Skövde

#ifndef INCLUDED_EGG
#define INCLUDED_EGG

#include "EntityImp.h"
#include "GameTimer.h"

class Egg : public EntityImp {
public:
	Egg(const Vector2D& vector);
	~Egg();
	virtual void draw(SDL_Surface* src_surface, Camera& camera);
	virtual void update(EntityContainer& entities);
	virtual Vector2D& getVector();
	virtual EntityImp::Category getCategory() const;
	virtual EntityImp::Priority getPriority() const;
	virtual bool isAlive() const;
	virtual bool handleEvents(EntityImp::GameEvent e);
	virtual int getValue() const;
	virtual int getHealth() const;
	virtual int getMaxHealth() const;
	virtual void setHealth(int health);
	static void initialize();
	static void finalize();
private:
	bool mIsAlive;
	Vector2D mVector;
	GameTimer mHatchDelay;
	int mMaxHealth;
	int mHealth;
};

#endif
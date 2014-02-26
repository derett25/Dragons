// Class that represents a fierce green dragon
// Author: Linus Esbjörnsson || a12lines
// Mail: linuse93@hotmail.com || a12lines@student.his.se
// Department of Communication and Information
// Högskolan i Skövde

#ifndef INCLUDED_DRAGON
#define INCLUDED_DRAGON

#include "EntityImp.h"
#include "GameTimer.h"
#include "GameText.h"
#include <string>

class Dragon : public EntityImp {
public:
	Dragon(const Vector2D& vector);
	~Dragon();
	virtual void draw(SDL_Surface* src_surface, Camera &camera);
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
	void setRandomMove();
	void move(Vector2D &direction);
	bool mIsAlive;
	Vector2D mVector;
	Vector2D mDirection;
	int mSpeed;
	int mMaxHealth;
	int mHealth;
	GameText mName;
	GameTimer mMoveDelay;
	GameTimer mHealthDecay;
	// Frame data
	int mStatus;
	int mFrame;
};

#endif


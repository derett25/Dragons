#include "Dragon.h"
#include "GameSurface.h"
#include "EntityTool.h"
#include "Defines.h"
#include "GameRand.h"
#include "Entity.h"

static const int DRAGON_NAMES_SIZE = 20;
static const int TEXT_SIZE = 16;
static const int HEALTH_BAR_WIDTH = 50;
static const int HEALTH_BAR_HEIGHT = 3;
static const std::string DRAGON_NAMES[20] = {"Sture", "Eivor", "Einar", "Claes", "Bosse", "Elof", "Sture", "Alfred", "Danny", "Viktor",
											"Kicki", "Helge", "Lasse", "Jimmy", "Karit", "Greta", "Stina", "Rollo", "Clark", "Ricky"};
static SDL_Surface* dragonImage;

enum DragonSprite {
	DRAGON_DOWN = 0,
	DRAGON_LEFT = 1,
	DRAGON_RIGHT = 2,
	DRAGON_UP = 3
};

static const int DRAGON_FRAME_COUNT = 3;
static SDL_Rect dragonClipsDown[DRAGON_FRAME_COUNT];
static SDL_Rect dragonClipsUp[DRAGON_FRAME_COUNT];
static SDL_Rect dragonClipsLeft[DRAGON_FRAME_COUNT];
static SDL_Rect dragonClipsRight[DRAGON_FRAME_COUNT];

static const int DRAGON_SELL_VALUE = 100;

Dragon::Dragon(const Vector2D& vector) :
	mIsAlive(true),
	mVector(vector),
	mDirection(Vector2D(0,0)),
	mStatus(DRAGON_DOWN),
	mSpeed(GameRand::randomNumber(1, 3)),
	mMaxHealth(GameRand::randomNumber(50, 200)),
	mHealth(mMaxHealth),
	mName(DRAGON_NAMES[GameRand::randomNumber(0, DRAGON_NAMES_SIZE - 1)], TEXT_SIZE),
	mFrame(1),
	mMoveDelay(90),
	mHealthDecay(2500) {
}


Dragon::~Dragon() {
}

void Dragon::update(EntityContainer& entities) {
	if (GameRand::randomPercentage(0.01)) {
		entities.add(EntityTool::createEgg(mVector));
	}
	if (mHealthDecay.isExpired()) {
		mHealth--;
		mHealthDecay.restartTimer();
	}
	if (mMoveDelay.isExpired()) {
		mMoveDelay.restartTimer();
		setRandomMove();
		move(mDirection);
	}
	if (mHealth == 0) {
		mIsAlive = false;
	}
}

void Dragon::draw(SDL_Surface* src_surface, Camera& camera) {
	switch (mStatus) {
		case DRAGON_DOWN:
			GameSurface::draw(dragonImage, src_surface, mVector + camera.getPosition(), dragonClipsDown[mFrame]);
			break;
		case DRAGON_LEFT:
			GameSurface::draw(dragonImage, src_surface, mVector + camera.getPosition(), dragonClipsLeft[mFrame]);
			break;
		case DRAGON_RIGHT:
			GameSurface::draw(dragonImage, src_surface, mVector + camera.getPosition(), dragonClipsRight[mFrame]);
			break;
		default:
			GameSurface::draw(dragonImage, src_surface, mVector + camera.getPosition(), dragonClipsUp[mFrame]);
			break;
	}
	mName.draw(src_surface, Vector2D(mVector.getX() - 3, mVector.getY() - 20) + camera.getPosition());
}

Vector2D& Dragon::getVector()  {
	return mVector;
}

EntityImp::Category Dragon::getCategory() const {
	return EntityImp::Category::NPC;
}

EntityImp::Priority Dragon::getPriority() const {
	return EntityImp::Priority::FOREGROUND;
}

bool Dragon::isAlive() const {
	return mIsAlive;
}

bool Dragon::handleEvents(EntityImp::GameEvent e) {
	if (e == EntityImp::GameEvent::ON_PICKUP) {
		mStatus = DRAGON_DOWN;
		mFrame = 1;
		return true;
	} else if (e == EntityImp::GameEvent::ON_SELL) {
		return true;
	} else if (e == EntityImp::GameEvent::ON_EAT) {
		return true;
	}
	return false;
}

int Dragon::getValue() const {
	return DRAGON_SELL_VALUE;
}

int Dragon::getHealth() const {
	return mHealth;
}

int Dragon::getMaxHealth() const {
	return mMaxHealth;
}

void Dragon::setHealth(int health) {
	mHealth = health;
	if (mHealth > mMaxHealth)
		mHealth = mMaxHealth;
}

void Dragon::initialize() {
	const char* DRAGON_PATH = "resources/textures/dragon.bmp";
	dragonImage = GameSurface::onLoad(DRAGON_PATH);

	for (int i = 0; i < DRAGON_FRAME_COUNT; i++) {
		dragonClipsDown[i].x = SPRITE_WIDTH * i;
		dragonClipsDown[i].y = 0;
		dragonClipsDown[i].w = SPRITE_WIDTH;
		dragonClipsDown[i].h = SPRITE_HEIGHT;

		dragonClipsLeft[i].x = SPRITE_WIDTH * i;
		dragonClipsLeft[i].y = SPRITE_HEIGHT;
		dragonClipsLeft[i].w = SPRITE_WIDTH;
		dragonClipsLeft[i].h = SPRITE_HEIGHT;

		dragonClipsRight[i].x = SPRITE_WIDTH * i;
		dragonClipsRight[i].y = SPRITE_HEIGHT * 2;
		dragonClipsRight[i].w = SPRITE_WIDTH;
		dragonClipsRight[i].h = SPRITE_HEIGHT;

		dragonClipsUp[i].x = SPRITE_WIDTH * i;
		dragonClipsUp[i].y = SPRITE_HEIGHT * 3;
		dragonClipsUp[i].w = SPRITE_WIDTH;
		dragonClipsUp[i].h = SPRITE_HEIGHT;
	}
}

void Dragon::finalize() {
	SDL_FreeSurface(dragonImage);
}

void Dragon::setRandomMove() {
	if (GameRand::randomPercentage(1)) {
		mDirection = Vector2D(0, 0);
		mFrame = 1;
	} else if (GameRand::randomPercentage(1)) {
		mDirection = Vector2D(1, 0);
	} else if (GameRand::randomPercentage(1)) {
		mDirection = Vector2D(-1, 0);
	} else if (GameRand::randomPercentage(1)) {
		mDirection = Vector2D(0, 1);
	} else if (GameRand::randomPercentage(1)) {
		mDirection = Vector2D(0, -1);
	}
}

void Dragon::move(Vector2D &direction) {
	if (direction.getX() != 0 || direction.getY() != 0) {
		if (direction.getX() < 0)
			mStatus = DRAGON_LEFT;
		else if (direction.getX() > 0)
			mStatus = DRAGON_RIGHT;
		else if (direction.getY() < 0)
			mStatus = DRAGON_UP;
		else if (direction.getY() > 0)
			mStatus = DRAGON_DOWN;

		mFrame = ++mFrame % DRAGON_FRAME_COUNT;
		mVector.setX(mVector.getX() + (mSpeed * direction.getX()));
		mVector.setY(mVector.getY() + (mSpeed * direction.getY()));
	}
}

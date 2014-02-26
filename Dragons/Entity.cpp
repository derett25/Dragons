#include "Entity.h"
#include "GameSurface.h"
#include "Defines.h"
#include "SDL_mixer.h"

static const int HEALTH_BAR_WIDTH = 50;
static const int HEALTH_BAR_HEIGHT = 3;

static Mix_Chunk* moneyEffectSound;
static Mix_Chunk* dropSound;
static Mix_Chunk* pickupSound;

Entity::Entity(EntityImp* entity) : 
	mEntity(entity),
	mPicked(false) {
}

Entity::~Entity() {
}

void Entity::update(EntityContainer& entities) {
	if (!mPicked) {
		mEntity->update(entities);
	}
}

void Entity::draw(SDL_Surface* src_surface, Camera& camera) {
	// Check if entity is inside camera view
	if ((mEntity->getVector().getX() >= camera.getPosition().getX() - SPRITE_WIDTH && mEntity->getVector().getX() <= abs(camera.getPosition().getX()) + DISPLAY_WIDTH + SPRITE_WIDTH) &&
		(mEntity->getVector().getY() >= camera.getPosition().getY() - SPRITE_HEIGHT && mEntity->getVector().getY() <= abs(camera.getPosition().getY()) + DISPLAY_HEIGHT + SPRITE_HEIGHT)) {
		mEntity->draw(src_surface, camera);
		drawHealth(src_surface, camera);
	}
}

Vector2D& Entity::getVector()  {
	return mEntity->getVector();
}

EntityImp::Category Entity::getCategory() const {
	return mEntity->getCategory();
}

EntityImp::Priority Entity::getPriority() const {
	return mEntity->getPriority();
}

bool Entity::isAlive() const {
	return mEntity->isAlive();
}

bool Entity::handleEvents(EntityImp::GameEvent e) {
	bool result = mEntity->handleEvents(e);

	if (e == EntityImp::GameEvent::ON_PICKUP) {
		Mix_PlayChannel(-1, pickupSound, 0);
		mPicked = true;
		return mPicked;
	} else if (e == EntityImp::GameEvent::ON_RELEASED) {
		Mix_PlayChannel(-1, dropSound, 0);
		mPicked = false;
		return mPicked;
	} else if (e == EntityImp::GameEvent::ON_SELL) {
		if (result) {
			Mix_PlayChannel(-1, moneyEffectSound, 0);
		}
	}
	// If entity is picked up we do not react on any event
	if (mPicked) {
		return false;
	} else {
		return result;
	}
}

int Entity::getValue() const {
	return mEntity->getValue();
}

int Entity::getMaxHealth() const {
	return mEntity->getMaxHealth();
}

int Entity::getHealth() const {
	return mEntity->getHealth();
}

void Entity::setHealth(int health) {
	mEntity->setHealth(health);
}

void Entity::initialize() {
	const char* MONEY_EFFECT_PATH = "resources/audio/moneyEffect.wav";
	const char* PICKUP_PATH = "resources/audio/pickupEffect.wav";
	const char* DROP_PATH = "resources/audio/dropEffect.wav";
	moneyEffectSound = Mix_LoadWAV(MONEY_EFFECT_PATH);
	pickupSound = Mix_LoadWAV(PICKUP_PATH);
	dropSound = Mix_LoadWAV(DROP_PATH);
}

void Entity::finalize() {
	Mix_FreeChunk(moneyEffectSound);
}

void Entity::drawHealth(SDL_Surface* src_surface, Camera& camera) const {
	Vector2D vector(mEntity->getVector().getX() - 10, mEntity->getVector().getY() + 40);

	GameSurface::drawRect(src_surface, vector + camera.getPosition(), HEALTH_BAR_WIDTH, HEALTH_BAR_HEIGHT, 0x000000); // Draw black rectangle
	if (mEntity->getHealth() <= mEntity->getMaxHealth() / 4) {
		GameSurface::drawRect(src_surface, vector + camera.getPosition(), HEALTH_BAR_WIDTH * (mEntity->getHealth() / (float)mEntity->getMaxHealth()), HEALTH_BAR_HEIGHT - 1, 0xC70C0C); // Draw red rectangle on top
	} else if (mEntity->getHealth() <= mEntity->getMaxHealth() / 2) {
		GameSurface::drawRect(src_surface, vector + camera.getPosition(), HEALTH_BAR_WIDTH * (mEntity->getHealth() / (float)mEntity->getMaxHealth()), HEALTH_BAR_HEIGHT - 1, 0xF2A922); // Draw orange rectangle on top
	} else {
		GameSurface::drawRect(src_surface, vector + camera.getPosition(), HEALTH_BAR_WIDTH * (mEntity->getHealth() / (float)mEntity->getMaxHealth()), HEALTH_BAR_HEIGHT - 1, 0x24C912); // Draw green rectangle on top
	}
}


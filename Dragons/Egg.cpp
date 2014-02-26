#include "Egg.h"
#include "EntityTool.h"
#include "GameSurface.h"
#include "SDL_mixer.h"

static SDL_Surface* eggImage;
static Mix_Chunk* eggBlopSound;

static const int EGG_SELL_VALUE = 25;
static const int EGG_HEALTH = 100;
static const int HATCH_DELAY_MS = 500;

Egg::Egg(const Vector2D& vector) :
	mIsAlive(true),
	mVector(vector),
	mHatchDelay(HATCH_DELAY_MS),
	mMaxHealth(EGG_HEALTH),
	mHealth(EGG_HEALTH) {
}


Egg::~Egg() {
}

void Egg::draw(SDL_Surface* src_surface, Camera& camera) {
	GameSurface::draw(eggImage, src_surface, mVector + camera.getPosition());
}

void Egg::update(EntityContainer& entities) {
	if (mHatchDelay.isExpired()) {
		mHealth--;
		mHatchDelay.restartTimer();
	}
	if (mHealth == 0) {
		Mix_PlayChannel(-1, eggBlopSound, 0);
		mIsAlive = false;
		entities.add(EntityTool::createDragon(mVector));
	}
}

Vector2D& Egg::getVector() {
	return mVector;
}

EntityImp::Category Egg::getCategory() const {
	return EntityImp::Category::ITEM;
}

EntityImp::Priority Egg::getPriority() const {
	return EntityImp::Priority::BACKGROUND;
}

bool Egg::isAlive() const {
	return mIsAlive;
}

bool Egg::handleEvents(EntityImp::GameEvent e) {
	if (e == EntityImp::GameEvent::ON_PICKUP) {
		return true;
	} else if (e == EntityImp::GameEvent::ON_SELL) {
		return true;
	}
	return false;
}

int Egg::getValue() const {
	return EGG_SELL_VALUE;
}

int Egg::getHealth() const {
	return mHealth;
}

int Egg::getMaxHealth() const {
	return mMaxHealth;
}

void Egg::setHealth(int health) {
	mHealth = health;
	if (mHealth > mMaxHealth)
		mHealth = mMaxHealth;
}

void Egg::initialize() {
	const char* EGG_PATH = "resources/textures/egg.bmp";
	const char* BLOP_PATH = "resources/audio/blop.wav";
	eggImage = GameSurface::onLoad(EGG_PATH);
	eggBlopSound = Mix_LoadWAV(BLOP_PATH);
}

void Egg::finalize() {
	SDL_FreeSurface(eggImage);
	Mix_FreeChunk(eggBlopSound);
}

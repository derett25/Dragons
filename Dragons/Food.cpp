#include "Food.h"
#include "Defines.h"
#include "GameSurface.h"
#include "GameRand.h"

static SDL_Surface* foodImage;
static const int FOOD_FRAME_COUNT = 4;
static SDL_Rect foodClips[FOOD_FRAME_COUNT];

static const int FOOD_HEALTH = 100;
static const int FOOD_SELL_VALUE = 75;
static const int FOOD_DECAY = 500;

Food::Food(const Vector2D& vector) :
	mIsAlive(true),
	mVector(vector),
	mRottenDecay(FOOD_DECAY),
	mMaxHealth(FOOD_HEALTH),
	mHealth(FOOD_HEALTH) {

	mClip = foodClips[GameRand::randomNumber(0, FOOD_FRAME_COUNT - 1)];
}


Food::~Food() {
}

void Food::draw(SDL_Surface* src_surface, Camera& camera) {
	GameSurface::draw(foodImage, src_surface, mVector + camera.getPosition(), mClip);
}

void Food::update(EntityContainer& entities) {
	if (mRottenDecay.isExpired()) {
		mHealth--;
		mRottenDecay.restartTimer();
	}
	if (mHealth == 0) {
		mIsAlive = false;
	}
}

Vector2D& Food::getVector() {
	return mVector;
}

EntityImp::Category Food::getCategory() const {
	return EntityImp::Category::CONSUMABLE;
}

EntityImp::Priority Food::getPriority() const {
	return EntityImp::Priority::FOREGROUND;
}

bool Food::isAlive() const {
	return mIsAlive;
}

bool Food::handleEvents(EntityImp::GameEvent e) {
	if (e == EntityImp::GameEvent::ON_PICKUP) {
		return true;
	} else if (e == EntityImp::GameEvent::ON_SELL) {
		return true;
	} else if (e == EntityImp::GameEvent::ON_EAT) {
		return true;
	}
	return false;
}

int Food::getValue() const {
	return FOOD_SELL_VALUE;
}

int Food::getMaxHealth() const {
	return mMaxHealth;
}

int Food::getHealth() const {
	return mHealth;
}

void Food::setHealth(int health) {
	mHealth = health;
	if (mHealth > mMaxHealth)
		mHealth = mMaxHealth;
}

void Food::initialize() {
	const char* FOOD_PATH = "resources/textures/food.bmp";
	foodImage = GameSurface::onLoad(FOOD_PATH);

	for (int i = 0; i < FOOD_FRAME_COUNT; i++) {
		foodClips[i].w = SPRITE_WIDTH;
		foodClips[i].h = SPRITE_HEIGHT;
		foodClips[i].y = 0;
		foodClips[i].x = i * SPRITE_WIDTH;
	}
}

void Food::finalize() {
	SDL_FreeSurface(foodImage);
}


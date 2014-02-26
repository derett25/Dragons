#include "GameMap.h"
#include "Defines.h"
#include "SDL_mixer.h"

static Mix_Chunk* chewingSound;

GameMap::GameMap() :
	mEntities() {

	generateMap();
}


GameMap::~GameMap() {
	while (!mEntities.empty()){
		delete mEntities.back();
		mEntities.pop_back();
	}
}

void GameMap::add(Entity* entity) {
	mEntities.push_back(entity);
}

void GameMap::remove(Entity* entity) {
	EntityVector entities;
	for (EntityVector::iterator it = mEntities.begin(); it != mEntities.end(); it++) {
		Entity* entity0 = *it;
		if (entity != entity0) {
			entities.push_back(entity0);
		} else {
			delete entity0;
		}
	}
	mEntities = entities;
}

void GameMap::update() {
	EntityVector entities(mEntities);
	for (EntityVector::iterator it = entities.begin(); it != entities.end(); it++) {
		Entity* entity = *it;
		entity->update(*this);
	}
	killDeadEntities();
	checkBoundaries();
	checkCollision();
}

void GameMap::draw(SDL_Surface* src_surface, Camera& camera) {
	for (int width = 0; width < MAP_X; width++) {
		for (int height = 0; height < MAP_X; height++) {
			mTiles[width][height].draw(src_surface, camera);
		}
	}
	renderBackground(src_surface, camera);
	renderForeground(src_surface, camera);
}

Entity* GameMap::getIntersect(Vector2D& vector) {
	for (EntityVector::iterator it = mEntities.begin(); it != mEntities.end(); it++) {
		Entity* entity = *it;
		if (isOverlap(entity->getVector(), vector)) {
			return entity;
		}
	}
	return NULL;
}

Vector2D GameMap::getSize() const {
	return Vector2D((MAP_X * SPRITE_WIDTH) - DISPLAY_WIDTH, (MAP_Y * SPRITE_HEIGHT) - DISPLAY_HEIGHT);
}

void GameMap::initialize() {
	const char* CHEWING_PATH = "resources/audio/chewing.wav";
	chewingSound = Mix_LoadWAV(CHEWING_PATH);
}

void GameMap::finalize() {
	Mix_FreeChunk(chewingSound);
}

void GameMap::generateMap() {
	for (int width = 0; width < MAP_X; width++) {
		for (int height = 0; height < MAP_X; height++) {
			mTiles[width][height] = GameTile(Vector2D(SPRITE_WIDTH * width, SPRITE_HEIGHT * height));
		}
	}
}

void GameMap::renderBackground(SDL_Surface* src_surface, Camera& camera) {
	for (EntityVector::iterator it = mEntities.begin(); it != mEntities.end(); it++) {
		Entity* entity = *it;
		if (entity->getPriority() == EntityImp::Priority::BACKGROUND) {
			entity->draw(src_surface, camera);
		}
	}
}

void GameMap::renderForeground(SDL_Surface* src_surface, Camera& camera) {
	for (EntityVector::iterator it = mEntities.begin(); it != mEntities.end(); it++) {
		Entity* entity = *it;
		if (entity->getPriority() == EntityImp::Priority::FOREGROUND) {
			entity->draw(src_surface, camera);
		}
	}
}

void GameMap::killDeadEntities() {
	EntityVector entities;
	for (EntityVector::iterator it = mEntities.begin(); it != mEntities.end(); it++) {
		Entity* entity = *it;
		if (entity->isAlive()) {
			entities.push_back(entity);
		}
	}
	mEntities = entities;
}

void GameMap::checkBoundaries() {
	for (EntityVector::iterator it = mEntities.begin(); it != mEntities.end(); it++) {
		Entity* entity = *it;
		if (entity->getVector().getX() < 0) {
			entity->getVector().setX(0);
		} else if (entity->getVector().getX() > getSize().getX() + DISPLAY_WIDTH - SPRITE_WIDTH) {
			entity->getVector().setX(getSize().getX() + DISPLAY_WIDTH - SPRITE_WIDTH);
		}
	
		if (entity->getVector().getY() < 0) {
			entity->getVector().setY(0);
		} else if (entity->getVector().getY() > getSize().getY() + DISPLAY_HEIGHT - SPRITE_HEIGHT) {
			entity->getVector().setY(getSize().getY() + DISPLAY_HEIGHT - SPRITE_HEIGHT);
		}
	}
}

void GameMap::checkCollision() {
	for (EntityVector::iterator i = mEntities.begin(); i != mEntities.end(); i++) {
		Entity* entity0 = *i;
		for (EntityVector::iterator j = i + 1; j != mEntities.end(); j++) {
			Entity* entity1 = *j;
			// If two entities collide with same drawing priority
			if (isOverlap(entity0->getVector(), entity1->getVector()) && entity0->getPriority() == entity1->getPriority()) {
				// If they are of different category and the second entity is a consumable object
				if (entity0->getCategory() != entity1->getCategory() && entity1->getCategory() == EntityImp::CONSUMABLE) {
					// If they both react true on the ON_EAT event
					if (entity0->handleEvents(EntityImp::GameEvent::ON_EAT) && entity1->handleEvents(EntityImp::GameEvent::ON_EAT)) {
						Mix_PlayChannel(-1, chewingSound, 0);
						entity0->setHealth(entity0->getHealth() + entity1->getHealth()); // Restore health to the first object
						entity1->setHealth(0); // Kill the consumable object
					}
				}
			}
		}
	}
}

bool GameMap::isOverlap(Vector2D& vector0, Vector2D& vector1) {
	return vector0 + SPRITE_WIDTH >= vector1 && vector0 <= vector1 + SPRITE_HEIGHT;
}

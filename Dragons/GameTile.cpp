#include "GameTile.h"
#include "GameSurface.h"
#include "GameRand.h"
#include "Camera.h"
#include "Defines.h"
#include <cmath>

static SDL_Surface* tileImage;
static const int NUMBER_OF_TILES = 5;
static SDL_Rect tileClips[NUMBER_OF_TILES];

GameTile::GameTile() :
	mVector() {
}

GameTile::GameTile(const Vector2D& vector) :
	mVector(vector) {

	if (GameRand::randomPercentage(1)) {
		mClip = tileClips[3];
	} else if(GameRand::randomPercentage(1)) {
		mClip = tileClips[4];
	} else {
		mClip = tileClips[GameRand::randomNumber(0, 2)];
	}
}


GameTile::~GameTile() {
}

void GameTile::draw(SDL_Surface* src_surface, Camera& camera) {
	if ((mVector.getX() >= camera.getPosition().getX() - SPRITE_WIDTH && mVector.getX() <= abs(camera.getPosition().getX()) + DISPLAY_WIDTH + SPRITE_WIDTH) &&
		(mVector.getY() >= camera.getPosition().getY() - SPRITE_HEIGHT && mVector.getY() <= abs(camera.getPosition().getY()) + DISPLAY_HEIGHT + SPRITE_HEIGHT)) {
		GameSurface::draw(tileImage, src_surface, Vector2D(mVector + camera.getPosition()), mClip);
	}
}

Vector2D& GameTile::getVector() {
	return mVector;
}

void GameTile::initialize() {
	const char* TILE_PATH = "resources/textures/tileSet.bmp";
	tileImage = GameSurface::onLoad(TILE_PATH);

	for (int i = 0; i < NUMBER_OF_TILES; i++) {
		tileClips[i].w = SPRITE_WIDTH;
		tileClips[i].h = SPRITE_HEIGHT;
		tileClips[i].y = 0;
		tileClips[i].x = i * SPRITE_WIDTH;
	}
}

void GameTile::finalize() {
	SDL_FreeSurface(tileImage);
}



#include "GameIntro.h"
#include "GameSurface.h"
#include "Defines.h"
#include "Vector2D.h"
#include "GameSession.h"
#include "GameMenu.h"
#include "CustomMouse.h"

static SDL_Surface* introBackground;
static const int INTRO_WIDTH = 1800;
static const int INTRO_HEIGHT = 640;

GameIntro::GameIntro() :
	mCamera() {
}


GameIntro::~GameIntro() {
}

void GameIntro::run() {
	checkCamera();
}

void GameIntro::draw(SDL_Surface* src_surface) {
	GameSurface::draw(introBackground, src_surface, mCamera.getPosition(), DISPLAY_WIDTH, DISPLAY_HEIGHT);
}

bool GameIntro::handleEvent(SDL_Event& event, ContextContainer& queue) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_RETURN) {
			queue.add(new GameSession());
			return false;
		} else if (event.key.keysym.sym == SDLK_ESCAPE) {
			queue.add(new GameMenu());
			return false;
		}
	}
	return true;
}

void GameIntro::initialize() {
	const char* INTRO_PATH = "resources/textures/introbackground.bmp";
	introBackground = GameSurface::onLoad(INTRO_PATH);
}

void GameIntro::finalize() {
	SDL_FreeSurface(introBackground);
}

void GameIntro::checkCamera() {
	Vector2D mousePos = CustomMouse::getMouseState();

	if (mousePos.getX() >= SCROLL_X_MAX) {
		mCamera.moveCamera(Vector2D(1, 0));
	} else if (mousePos.getX() <= SCROLL_X_MIN) {
		mCamera.moveCamera(Vector2D(-1, 0));
	}

	if (mousePos.getY() >= SCROLL_Y_MAX) {
		mCamera.moveCamera(Vector2D(0, 1));
	} else if (mousePos.getY() <= SCROLL_Y_MIN) {
		mCamera.moveCamera(Vector2D(0, -1));
	}

	if (mCamera.getPosition().getX() < 0) {
		mCamera.getPosition().setX(0);
	} else if (abs(mCamera.getPosition().getX()) > INTRO_WIDTH - DISPLAY_WIDTH) {
		mCamera.getPosition().setX(INTRO_WIDTH - DISPLAY_WIDTH);
	}
	
	if (mCamera.getPosition().getY() < 0) {
		mCamera.getPosition().setY(0);
	} else if (abs(mCamera.getPosition().getY()) > INTRO_HEIGHT - DISPLAY_HEIGHT) {
		mCamera.getPosition().setY(INTRO_HEIGHT - DISPLAY_HEIGHT);
	}
}
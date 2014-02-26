#include "GameSession.h"
#include "GameSurface.h"
#include "EntityTool.h"
#include "Defines.h"
#include "GameMenu.h"
#include "CustomMouse.h"
#include "GameRand.h"
#include "SDL_mixer.h"
#include "Entity.h"
#include <Windows.h>

static Mix_Music* gameMusic;

GameSession::GameSession() :
	mMap(),
	mEntityPicked(NULL),
	mMoney(100),
	mCamera(),
	mMoneyText(),
	mMoneyIncrease(1000) {

	const int NO_DRAGONS = 8;
	for (int i = 0; i < NO_DRAGONS; i++) {
		mMap.add(EntityTool::createDragon(Vector2D(GameRand::randomNumber(0, mMap.getSize().getX() + DISPLAY_WIDTH), GameRand::randomNumber(0, mMap.getSize().getY() + DISPLAY_HEIGHT))));
	}
	mMoneyText.setText("Money: " + std::to_string(mMoney), 25, 17, 73, 11);
	Mix_HaltMusic(); // Kill all other music
	Mix_PlayMusic(gameMusic, -1);
}

GameSession::~GameSession() {
}

void GameSession::run() {
	checkCamera();
	update();
	mMap.update();
}

void GameSession::draw(SDL_Surface* src_surface) {
	mMap.draw(src_surface, mCamera);
	mMoneyText.draw(src_surface, Vector2D(5, 615));
}

bool GameSession::handleEvent(SDL_Event& event, ContextContainer& queue) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			if (MessageBox(NULL, "Do you want to exit to the main menu (all progress will be lost)?", "Exit", MB_YESNO) == IDYES) {
				// Return to main menu and kill this context
				queue.add(new GameMenu());
				return false;
			}
		} else if (event.key.keysym.sym == SDLK_f) {
			addFood();
		}
	} else if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			// Check if entity exists on the click location
			checkPickup(Vector2D(event.button.x + abs(mCamera.getPosition().getX()), event.button.y + abs(mCamera.getPosition().getY())));
		}
	} else if (event.type == SDL_MOUSEBUTTONUP) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			if (mEntityPicked != NULL) {
				mEntityPicked->handleEvents(EntityImp::GameEvent::ON_RELEASED); // Send event to indicate that it is not picked up anymore
				mEntityPicked = NULL;
			}
		} else if (event.button.button == SDL_BUTTON_RIGHT) {
			checkSell(Vector2D(event.button.x + abs(mCamera.getPosition().getX()), event.button.y + abs(mCamera.getPosition().getY())));
		}
	}
	return true;
}

void GameSession::initialize() {
	const char* MUSIC_PATH = "resources/audio/gameMusic.wav";
	gameMusic = Mix_LoadMUS(MUSIC_PATH);
}

void GameSession::finalize() {
	Mix_FreeMusic(gameMusic);
}

void GameSession::checkCamera() {
	Vector2D mousePos = CustomMouse::getMouseState();

	// Set camera direction to the reverse direction, used for offset
	if (mousePos.getX() >= SCROLL_X_MAX) {
		mCamera.moveCamera(Vector2D(-1, 0));
	} else if (mousePos.getX() <= SCROLL_X_MIN) {
		mCamera.moveCamera(Vector2D(1, 0));
	}

	if (mousePos.getY() >= SCROLL_Y_MAX) {
		mCamera.moveCamera(Vector2D(0, -1));
	} else if (mousePos.getY() <= SCROLL_Y_MIN) {
		mCamera.moveCamera(Vector2D(0, 1));
	}

	// Limit camera from going too far horizontally
	if (mCamera.getPosition().getX() > 0) {
		mCamera.getPosition().setX(0);
	} else if (abs(mCamera.getPosition().getX()) > mMap.getSize().getX()) {
		mCamera.getPosition().setX(0 - mMap.getSize().getX());
	}
	
	// Limit camera from going too far vertically
	if (mCamera.getPosition().getY() > 0) {
		mCamera.getPosition().setY(0);
	} else if (abs(mCamera.getPosition().getY()) > mMap.getSize().getY()) {
		mCamera.getPosition().setY(0 - mMap.getSize().getY());
	}
}

void GameSession::update() {
	if (mMoneyIncrease.isExpired()) {
		mMoney++;
		mMoneyIncrease.restartTimer();
		mMoneyText.setText("Money: " + std::to_string(mMoney), 25, 17, 73, 11);
	}
	if (mEntityPicked != NULL) {
		Vector2D& vector = mEntityPicked->getVector();
		vector = CustomMouse::getMouseState();
		vector.setX(vector.getX() + abs(mCamera.getPosition().getX()));
		vector.setY(vector.getY() + abs(mCamera.getPosition().getY()) + 22);
	}
}

void GameSession::checkPickup(Vector2D& vector) {
	Entity* entity = mMap.getIntersect(vector);
	if (entity != NULL) {
		if (entity->handleEvents(EntityImp::GameEvent::ON_PICKUP)) {
			mEntityPicked = entity;
		}
	}
}

void GameSession::checkSell(Vector2D& vector) {
	Entity* entity = mMap.getIntersect(vector);
	if (entity != NULL) {
		if (entity->handleEvents(EntityImp::GameEvent::ON_SELL)) {
			mMoney += entity->getValue();
			mMoneyText.setText("Money: " + std::to_string(mMoney), 25, 17, 73, 11);
			mMap.remove(entity);
		}
	}
}

void GameSession::addFood() {
	// Create food on the mouse location
	Entity* food = EntityTool::createFood(Vector2D(CustomMouse::getMouseState().getX() + abs(mCamera.getPosition().getX()), CustomMouse::getMouseState().getY() + abs(mCamera.getPosition().getY())));
	if (mMoney >= food->getValue()) {
		mMap.add(food);
		mMoney -= food->getValue();
		mMoneyText.setText("Money: " + std::to_string(mMoney), 25, 17, 73, 11);
	} else {
		// Delete food if too expensive
		delete food;
	}
}

#include "Game.h"
#include "GameMenu.h"
#include "GameTimer.h"
#include "GameSurface.h"
#include "Defines.h"

static SDL_Surface* windowIcon;

Game::Game(const char* title, int width, int height) :
	mWindow(SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL)),
	mSurface(SDL_GetWindowSurface(mWindow)),
	mMouse(),
	mRunning(true),
	mContextQueue() {

	SDL_ShowCursor(0); // Hide the system cursor
	SDL_SetWindowIcon(mWindow, windowIcon);
	mContextQueue.push(new GameMenu()); // Add the game menu to the queue
}


Game::~Game() {
	while (!mContextQueue.empty()) {
		pop();
	}
	SDL_FreeSurface(mSurface);
	SDL_DestroyWindow(mWindow);
}

void Game::add(GameContext* context) {
	mContextQueue.push(context);
}

void Game::pop() {
	delete mContextQueue.front();
	mContextQueue.pop();
}

void Game::run() {
	GameTimer time(1000/FRAMES_PER_SECOND); // FPS Limiter
	while (time.restartTimer(), mRunning) {
		mContextQueue.front()->run();
		draw();
		if (!handleEvents()) { // Destroy the context if event processing failed
			pop();
		}
		while (!time.isExpired());
		if (mContextQueue.empty()) { // No more contexts to run? Quit
			mRunning = false;
		}
	}
}

void Game::initialize() {
	const char* ICON_PATH = "resources/textures/windowIcon.bmp";
	windowIcon = GameSurface::onLoad(ICON_PATH);
}

void Game::finalize() {
	SDL_FreeSurface(windowIcon);
}

void Game::draw() {
	SDL_FillRect(mSurface, NULL, 0x00000000); // Clear the screen
	mContextQueue.front()->draw(mSurface);
	mMouse.render(mSurface); // Render mouse last
	SDL_UpdateWindowSurface(mWindow);
}

bool Game::handleEvents() {
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			mRunning = false;
			return false;
		} else {
			mMouse.handleEvents(event);
			if (!mContextQueue.front()->handleEvent(event, *this)) { // For efficiency reasons
				return false;
			}
		}	
	}
	return true;
}
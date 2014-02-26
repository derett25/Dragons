#include "GameMenu.h"
#include "GameSurface.h"
#include "Defines.h"
#include "SDL_mixer.h"
#include "Vector2D.h"
#include "GameIntro.h"

static SDL_Surface* menuBackground;
static Mix_Music* menuMusic;

static const int BACKGROUND_WIDTH = 2880;
static const int TEXT_SIZE = 34;
static const int CAMERA_SCROLL_SPEED = 1;

GameMenu::GameMenu() :
	mCamera(CAMERA_SCROLL_SPEED),
	mClickText("Click to Start", TEXT_SIZE, 255, 255, 255) {

	Mix_HaltMusic();
	Mix_PlayMusic(menuMusic, -1);
}


GameMenu::~GameMenu() {
}

void GameMenu::run() {
	moveScreen();
}

void GameMenu::draw(SDL_Surface* src_surface) {
	GameSurface::draw(menuBackground, src_surface, mCamera.getPosition(), DISPLAY_WIDTH, DISPLAY_HEIGHT);
	mClickText.draw(src_surface, Vector2D(315, 50));
}

bool GameMenu::handleEvent(SDL_Event& event, ContextContainer& queue) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		queue.add(new GameIntro());
		return false;
	}
	return true;
}

void GameMenu::moveScreen() {
	mCamera.moveCamera(Vector2D(1, 0));
	// If the camera reaches the end of the picture
	if (mCamera.getPosition().getX() > (BACKGROUND_WIDTH - DISPLAY_WIDTH)) {
		mCamera.setPosition(0);
	}
}

void GameMenu::initialize() {
	const char* BACKGROUND_PATH = "resources/textures/menubackground.bmp";
	const char* MUSIC_PATH = "resources/audio/menuMusic.wav";
	menuBackground = GameSurface::onLoad(BACKGROUND_PATH);
	menuMusic = Mix_LoadMUS(MUSIC_PATH);
}

void GameMenu::finalize() {
	SDL_FreeSurface(menuBackground);
	Mix_FreeMusic(menuMusic);
}
#include "CustomMouse.h"
#include "GameSurface.h"
#include "Vector2D.h"
#include "Defines.h"

static SDL_Surface* mSurface;
static const int MOUSE_FRAME_COUNT = 2;
static SDL_Rect mouseClip[MOUSE_FRAME_COUNT];

CustomMouse::CustomMouse() :
	mFrame(0) {
}

CustomMouse::~CustomMouse() {
}

void CustomMouse::render(SDL_Surface* src_surface) const {
	GameSurface::draw(mSurface, src_surface, getMouseState(), mouseClip[mFrame]);
}

bool CustomMouse::handleEvents(SDL_Event& e) {
	if ((e.type == SDL_MOUSEBUTTONDOWN) || (e.type == SDL_MOUSEBUTTONUP)) {
		mFrame = ++mFrame % MOUSE_FRAME_COUNT; // Switch frame for the custom mouse
		return true;
	}
	return false;
}

void CustomMouse::initialize() {
	const char* CURSOR_PATH = "resources/textures/cursor.bmp";
	mSurface = GameSurface::onLoad(CURSOR_PATH);
	for (int i = 0; i < MOUSE_FRAME_COUNT; i++) {
		mouseClip[i].x = SPRITE_WIDTH * i;
		mouseClip[i].y = 0;
		mouseClip[i].w = SPRITE_WIDTH;
		mouseClip[i].h = SPRITE_HEIGHT;
	}
}

void CustomMouse::finalize() {
	SDL_FreeSurface(mSurface);
}

Vector2D CustomMouse::getMouseState() {
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	return Vector2D(mouseX, mouseY);
}

#include "GameText.h"
#include "GameSurface.h"
#include "Defines.h"

static const char* FONT_PATH = "resources/fonts/franklin.ttf";

GameText::GameText() :
	mTextFont(),
	mTextSurface() {
	// To avoid errors
	setText("Text");
}

GameText::GameText(const std::string text, int size, int r, int g, int b) :
	mTextFont(),
	mTextSurface() {
	setText(text, size, r, g, b);
}


GameText::~GameText() {
	TTF_CloseFont(mTextFont);
	SDL_FreeSurface(mTextSurface);
}

void GameText::draw(SDL_Surface* src_surface, const Vector2D& vector) {
	GameSurface::draw(mTextSurface, src_surface, vector);
}

void GameText::setText(const std::string text, int size, int r, int g, int b) {
	mTextFont = TTF_OpenFont(FONT_PATH, size);
	SDL_Color color = {r, g, b};
	mTextSurface = TTF_RenderText_Blended(mTextFont, text.c_str(), color);
}

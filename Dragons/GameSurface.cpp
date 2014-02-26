#include "GameSurface.h"
#include "Vector2D.h"

SDL_Surface* GameSurface::onLoad(const char* file) {
	SDL_Surface* surface;
	if ((surface = SDL_LoadBMP(file)) == NULL) {
		return NULL;
	}
	// Set transparency for the pink color
	SDL_SetColorKey(surface, 1, SDL_MapRGB(surface->format, 240, 0, 255));
	return surface;
}

bool GameSurface::draw(SDL_Surface* src_surface, SDL_Surface* dest_surface, const Vector2D& vector) {
	if ((src_surface == NULL) || (dest_surface == NULL)) {
		return false;
	}
	SDL_Rect posRect;
	posRect.x = vector.getX();
	posRect.y = vector.getY();

	SDL_BlitSurface(src_surface, NULL, dest_surface, &posRect);
	return true;
}

bool GameSurface::draw(SDL_Surface* src_surface, SDL_Surface* dest_surface, const Vector2D& vector, SDL_Rect clip) {
	if ((src_surface == NULL) || (dest_surface == NULL)) {
		return false;
	}
	SDL_Rect posRect;
	posRect.x = vector.getX();
	posRect.y = vector.getY();

	SDL_BlitSurface(src_surface, &clip, dest_surface, &posRect);
	return true;
}


bool GameSurface::draw(SDL_Surface* src_surface, SDL_Surface* dest_surface, const Vector2D& vector, int width, int height) {
	if ((src_surface == NULL) || (dest_surface == NULL)) {
		return false;
	}
	SDL_Rect posRect = { vector.getX(), vector.getY(), width, height };

	SDL_BlitSurface(src_surface, &posRect, dest_surface, NULL);
	return true;
}

bool GameSurface::drawRect(SDL_Surface* src_surface, const Vector2D& vector, int width, int height, int color) {
	if ((src_surface == NULL)) {
		return false;
	}
	SDL_Rect rect = { vector.getX() ,vector.getY(), width, height };
	SDL_FillRect(src_surface, &rect, color);
	return true;
}

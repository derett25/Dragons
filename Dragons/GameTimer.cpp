#include "GameTimer.h"
#include "SDL.h"

GameTimer::GameTimer() :
	mTimerLength(0),
	mEndTicks(0) {
}

GameTimer::GameTimer(long ms) :
	mTimerLength(ms) {
	restartTimer();
}


GameTimer::~GameTimer() {
}

void GameTimer::setTimer(long ms) {
	mTimerLength = ms;
	mEndTicks = SDL_GetTicks() + mTimerLength;
}

bool GameTimer::isExpired() const {
	return SDL_GetTicks() >= mEndTicks;
}

void GameTimer::restartTimer() {
	mEndTicks = SDL_GetTicks() + mTimerLength;
}

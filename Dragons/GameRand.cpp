#include "GameRand.h"
#include <cassert>

static std::mt19937 randomGenerator;
static std::random_device randomDevice;

void GameRand::initialize() {
	randomGenerator.seed(randomDevice());
}

int GameRand::randomNumber(int min, int max) {
	assert(min < max);
	RNG numbers(min, max);
	return numbers(randomGenerator);
}

bool GameRand::randomPercentage(float percent) {
	return percent*1000 >= randomNumber(0, 100000);
}

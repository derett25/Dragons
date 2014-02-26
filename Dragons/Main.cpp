#include "Game.h"
#include "GameSession.h"
#include "GameMenu.h"
#include "GameIntro.h"
#include "Dragon.h"
#include "Food.h"
#include "Egg.h"
#include "GameRand.h"
#include "SDL_mixer.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
	Mix_OpenAudio(44100 , AUDIO_S16SYS , 2, 1024);
	TTF_Init();
	GameTile::initialize();
	CustomMouse::initialize();
	Egg::initialize();
	GameRand::initialize();
	Dragon::initialize();
	Entity::initialize();
	GameSession::initialize();
	GameIntro::initialize();
	GameMenu::initialize();
	Food::initialize();
	Game::initialize();
	GameMap::initialize();
	Game* game = new Game(GAME_NAME, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	game->run();
	delete game;
	GameTile::finalize();
	Dragon::finalize();
	GameMenu::finalize();
	GameIntro::finalize();
	CustomMouse::finalize();
	Egg::finalize();
	Entity::finalize();
	Food::finalize();
	Game::finalize();
	GameSession::finalize();
	GameMap::finalize();
	Mix_CloseAudio();
	TTF_Quit();
    SDL_Quit();

    return 0;
}
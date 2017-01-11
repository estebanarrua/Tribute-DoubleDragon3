#include "Globals.h"
#include "Application.h"
#include "ModuleEntity.h"
#include "ModuleTimer.h"
#include "SDL/include/SDL.h"


ModuleTimer::ModuleTimer(CONFIG_OBJECT config) : Module(config)
{
}

ModuleTimer::~ModuleTimer()
{
}

bool ModuleTimer::Start()
{
	firtTime = SDL_GetTicks();
	return true;
}

update_status ModuleTimer::Update()
{
	unsigned int aux = SDL_GetTicks();
	if (App->entities->gameState == GAMMING) {
		if (gameTime > 0) {
			gameTime -= (aux - lastTime);
		}
		else {
			gameTime = 0;
		}
	}
	lastTime = aux;
	return UPDATE_CONTINUE;
}

bool ModuleTimer::CleanUp()
{
	return true;
}

int ModuleTimer::GetGameTime()
{
	return gameTime/1000;
}

void ModuleTimer::StartGameTime(int gameTime)
{
	this->gameTime = gameTime * 1000;
}


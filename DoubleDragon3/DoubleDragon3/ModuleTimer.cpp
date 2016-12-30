#include "Globals.h"
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
	lastTime = SDL_GetTicks();
	return UPDATE_CONTINUE;
}

bool ModuleTimer::CleanUp()
{
	return true;
}

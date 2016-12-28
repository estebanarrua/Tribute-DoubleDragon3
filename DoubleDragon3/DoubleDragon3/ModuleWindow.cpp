#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "SDL/include/SDL.h"

ModuleWindow::ModuleWindow(CONFIG_OBJECT config) : Module(config)
{
	title = CONFIG_OBJECT_STRING(config, "title");
	CONFIG_ARRAY arraySize = CONFIG_OBJECT_ARRAY(config, "screen_size");

	screenWidth = (int) (CONFIG_ARRAY_NUMBER(arraySize, 0));
	screenHeight = (int)(CONFIG_ARRAY_NUMBER(arraySize, 1));
	screenSize = (int)(CONFIG_ARRAY_NUMBER(arraySize, 2));
	fullScreen = CONFIG_OBJECT_BOOL(config, "fullscreen") != 0;
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	LOG("Init SDL window & surface");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		int width = this->screenWidth * this->screenSize;
		int height = this->screenHeight * this->screenSize;
		Uint32 flags = SDL_WINDOW_SHOWN;

		if(this->fullScreen == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if(window == nullptr)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != nullptr)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}


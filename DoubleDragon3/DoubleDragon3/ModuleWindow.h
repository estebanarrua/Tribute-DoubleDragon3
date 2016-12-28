#ifndef __MODULEWINDOW_H__
#define __MODULEWINDOW_H__

#include <string>
#include "Module.h"

struct SDL_Window;
struct SDL_Surface;

class ModuleWindow : public Module
{

public:
	//The window we'll be rendering to
	SDL_Window* window = nullptr;

	//The surface contained by the window
	SDL_Surface* screen_surface = nullptr;

	// Configuration -----------
	int screenWidth = 0;
	int screenHeight = 0;
	int screenSize = 0;
	bool fullScreen = false;
	std::string title = "";

public:

	ModuleWindow(CONFIG_OBJECT config);

	// Destructor
	virtual ~ModuleWindow();

	// Called before quitting
	bool Init();

	// Called before quitting
	bool CleanUp();

};

#endif // __MODULEWINDOW_H__
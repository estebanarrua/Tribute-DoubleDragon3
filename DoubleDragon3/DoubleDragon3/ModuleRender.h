#ifndef __MODULERENDER_H__
#define __MODULERENDER_H__

#include "Module.h"
#include "Globals.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ModuleRender : public Module
{

public:
	SDL_Renderer* renderer = nullptr;
	SDL_Rect camera;

	// Configuration -----------
	int screenWidth = 0;
	int screenHeight = 0;
	int screenSize = 0;
	bool vsync = false;
	
public:
	ModuleRender(CONFIG_OBJECT config);
	~ModuleRender();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	bool Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed = 1.0f);

};

#endif // __MODULERENDER_H__
#ifndef __MODULESCENECHINA_H__
#define __MODULESCENECHINA_H__

#include "Module.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneChina :
	public Module
{
public:
	ModuleSceneChina( bool start_enabled = true);
	~ModuleSceneChina();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect background;
	SDL_Rect tree;
};

#endif // __MODULESCENECHINA_H__



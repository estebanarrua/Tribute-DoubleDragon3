#ifndef __MODULESCENEINIT_H__
#define __MODULESCENEINIT_H__

#include "Module.h"
#include "Globals.h"
#include "Animation.h"
#include "Point.h"

struct SDL_Texture;

class ModuleSceneInit : public Module
{
public:
	SDL_Texture* segaGraphics = nullptr;
	SDL_Texture* flyingedgeGraphics = nullptr;

	Frame background;
	Animation sega;
	iPoint segaPosition;

public:

	ModuleSceneInit(CONFIG_OBJECT config, bool start_enabled = true);
	~ModuleSceneInit();

	bool Start();
	update_status Update();
	bool CleanUp();

};

#endif //__MODULESCENE_H__


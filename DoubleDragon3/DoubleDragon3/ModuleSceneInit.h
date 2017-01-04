#ifndef __MODULESCENEINIT_H__
#define __MODULESCENEINIT_H__

#include "Module.h"
#include "Globals.h"
#include "Animation.h"
#include "Point.h"

struct SDL_Texture;

enum initState {
	SEGA,
	FLYING,
	BLACK,

	TOTAL_STATES
};

class ModuleSceneInit : public Module
{
private:
	SDL_Texture* segaGraphics = nullptr;
	SDL_Texture* flyingedgeGraphics = nullptr;

	Frame flyingedge;
	Animation sega;
	iPoint segaPosition;

	initState actualState = SEGA;
	unsigned int lastTime = 0;
	unsigned int times[TOTAL_STATES];

public:

	ModuleSceneInit(CONFIG_OBJECT config, bool start_enabled = true);
	~ModuleSceneInit();

	bool Start();
	update_status Update();
	bool CleanUp();

};

#endif //__MODULESCENE_H__


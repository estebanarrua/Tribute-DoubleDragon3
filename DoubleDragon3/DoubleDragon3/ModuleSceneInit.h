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
	INIT_PAGE,

	TOTAL_STATES
};

class ModuleSceneInit : public Module
{
private:
	SDL_Texture* segaGraphics = nullptr;
	SDL_Texture* flyingedgeGraphics = nullptr;
	SDL_Texture* initPageGraphics = nullptr;

	Frame flyingedge;
	Frame background;
	Frame bigFonts;
	Frame smallFonts;
	Animation sega;
	iPoint segaPosition;
	int bigFontsPositionX;
	int starts[2];
	int startPressed = -1;

	initState actualState = SEGA;
	int backgroundMaxWith = 0;
	unsigned int backgroundTime = 0;
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


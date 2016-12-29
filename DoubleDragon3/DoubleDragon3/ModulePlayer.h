#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:

	SDL_Texture* graphics = nullptr;
	Frame idle;
	Animation forward;
	Animation backward;
	Animation up;
	Animation down;
	iPoint position;

public:
	ModulePlayer(CONFIG_OBJECT config, bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();


};

#endif // __MODULEPLAYER_H__
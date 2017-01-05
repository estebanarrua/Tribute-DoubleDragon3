#ifndef __MODULESCENECHINA_H__
#define __MODULESCENECHINA_H__

#include "Module.h"
#include "Globals.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleSceneChina : public Module
{
public:

	SDL_Texture* graphics = nullptr;
	Frame background;
	Frame tree;
	bool player[2] = { false, false };

public:
	ModuleSceneChina(CONFIG_OBJECT config, bool start_enabled = true);
	~ModuleSceneChina();

	bool Start();
	update_status Update();
	bool CleanUp();


};

#endif // __MODULESCENECHINA_H__



#ifndef __MODULEHUB_H__
#define __MODULEHUB_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleHub : public Module
{
private:
	int fontText;
	int fontNumber;
	int fontLife[2];
	Frame faces[2];
	SDL_Texture* gFaces;

public:
	ModuleHub(CONFIG_OBJECT config, bool start_enabled = true);
	~ModuleHub();

	bool Start();
	update_status Update();
	bool CleanUp();

};

#endif // __MODULEHUB_H__


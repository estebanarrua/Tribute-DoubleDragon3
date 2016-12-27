#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModuleFadeToBlack;
class ModulePlayer;
class ModuleSceneChina;

class Application
{

private:

	std::list<Module*> modules;

public:
	CONFIG_OBJECT configObj;
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleFadeToBlack* fade;
	ModulePlayer* player;
	ModuleSceneChina* scene_china;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();
};

extern Application* App;

#endif // __APPLICATION_CPP__
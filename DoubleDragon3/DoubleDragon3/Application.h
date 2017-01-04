#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleTimer;
class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModuleFadeToBlack;
class ModuleEntity;
class ModuleSceneChina;
class ModuleSceneInit;

class Application
{

private:

	std::list<Module*> modules;

public:
	CONFIG_OBJECT configObj;
	ModuleTimer* timer;
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleFadeToBlack* fade;
	ModuleEntity* entitys;
	ModuleSceneChina* scene_china;
	ModuleSceneInit* scene_init;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();
};

extern Application* App;

#endif // __APPLICATION_CPP__
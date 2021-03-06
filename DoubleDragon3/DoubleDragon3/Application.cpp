#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneChina.h"
#include "ModuleSceneInit.h"
#include "ModuleEntity.h"
#include "ModuleTimer.h"
#include "ModuleCollision.h"
#include "ModuleFonts.h"
#include "ModuleHub.h"

using namespace std;

Application::Application()
{
	//Init config
	configObj = GET_CONFIG("config.json");

	// Order matters: they will init/start/pre/update/post in this order
	modules.push_back(input = new ModuleInput(CONFIG_OBJECT_OBJECT(configObj, "input")));
	modules.push_back(window = new ModuleWindow(CONFIG_OBJECT_OBJECT(configObj, "window")));
	modules.push_back(timer = new ModuleTimer(CONFIG_OBJECT_OBJECT(configObj, "timer")));
	modules.push_back(fonts = new ModuleFonts(CONFIG_OBJECT_OBJECT(configObj, "fonts")));
	
	modules.push_back(renderer = new ModuleRender(CONFIG_OBJECT_OBJECT(configObj, "render")));
	modules.push_back(textures = new ModuleTextures(CONFIG_OBJECT_OBJECT(configObj, "textures")));
	modules.push_back(audio = new ModuleAudio(CONFIG_OBJECT_OBJECT(configObj, "audio")));

	// Game Modules
	modules.push_back(collisions = new ModuleCollision(CONFIG_OBJECT_OBJECT(configObj, "collision")));
	modules.push_back(scene_init = new ModuleSceneInit(CONFIG_OBJECT_OBJECT(configObj, "sceneInit"), true));
	modules.push_back(entities = new ModuleEntity(CONFIG_OBJECT_OBJECT(configObj, "entitys"), false));
	modules.push_back(scene_china = new ModuleSceneChina(CONFIG_OBJECT_OBJECT(configObj, "sceneChina"), false));
	modules.push_back(fade = new ModuleFadeToBlack(CONFIG_OBJECT_OBJECT(configObj, "fadeToBlack")));
	modules.push_back(hub = new ModuleHub(CONFIG_OBJECT_OBJECT(configObj, "hub"), false));
}

Application::~Application()
{
	for(list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it)
		RELEASE(*it);
}

bool Application::Init()
{
	bool ret = true;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init(); // we init everything, even if not anabled

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
	{
		if((*it)->IsEnabled() == true)
			ret = (*it)->Start();
	}

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->PreUpdate();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->Update();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->PostUpdate();

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->CleanUp();

	return ret;
}


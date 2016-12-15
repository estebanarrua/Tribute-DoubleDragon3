#include "Globals.h"
#include "Application.h"
#include "ModuleSceneChina.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"



ModuleSceneChina::ModuleSceneChina(bool start_enabled) : Module(start_enabled)
{
	background.x = 8;
	background.y = 8;
	background.w = 1104;
	background.h = 224;

	tree.x = 0;
	tree.y = 0;
	tree.w = 0;
	tree.h = 0;
}

ModuleSceneChina::~ModuleSceneChina()
{
}

bool ModuleSceneChina::Start()
{
	LOG("Loading China scene");
	graphics = App->textures->Load("Sprites/china_scene.png");

	//App->audio->PlayMusic("Music/03-in-china.ogg");

	return true;
}

update_status ModuleSceneChina::Update()
{
	App->renderer->Blit(graphics, 0, 0, &background, 1.0f);
	
	return UPDATE_CONTINUE;
}

bool ModuleSceneChina::CleanUp()
{
	LOG("Unloading China scene");
	App->textures->Unload(graphics);
	App->player->Disable();

	return false;
}

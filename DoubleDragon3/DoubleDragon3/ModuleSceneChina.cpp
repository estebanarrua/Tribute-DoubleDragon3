#include "Globals.h"
#include "Application.h"
#include "ModuleSceneChina.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleEntity.h"
#include "SDL/include/SDL.h"



ModuleSceneChina::ModuleSceneChina(CONFIG_OBJECT config, bool start_enabled) : Module(config, start_enabled)
{
	background.rect.x = 8;
	background.rect.y = 8;
	background.rect.w = 1104;
	background.rect.h = 224;
	background.flip = false;

	tree.rect.x = 1119;
	tree.rect.y = 7;
	tree.rect.w = 122;
	tree.rect.h = 225;
	tree.flip = false;
}

ModuleSceneChina::~ModuleSceneChina()
{
}

bool ModuleSceneChina::Start()
{
	LOG("Loading China scene");
	graphics = App->textures->Load("Sprites/china_scene.png");

	App->audio->PlayMusic("Music/03-in-china.ogg");

	App->entitys->Enable();

	return true;
}

update_status ModuleSceneChina::Update()
{
	App->renderer->Blit(graphics, 0, 0, &background, 1.0f);
	
	return UPDATE_CONTINUE;
}

update_status ModuleSceneChina::PostUpdate()
{
	App->renderer->Blit(graphics, 607, 0, &tree, 1.0f);

	return UPDATE_CONTINUE;
}

bool ModuleSceneChina::CleanUp()
{
	LOG("Unloading China scene");
	App->textures->Unload(graphics);

	return false;
}

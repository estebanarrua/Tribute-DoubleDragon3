#include "Globals.h"
#include "Application.h"
#include "ModuleSceneInit.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

ModuleSceneInit::ModuleSceneInit(CONFIG_OBJECT config, bool start_enabled) : Module(config, start_enabled)
{
	int segaCount = (int)CONFIG_OBJECT_NUMBER(config, "segaAnimationCount");
	CONFIG_ARRAY aSegaAnimation = CONFIG_OBJECT_ARRAY(config, "segaAnimation");
	Frame fAux;
	fAux.rect = {
		(int)CONFIG_ARRAY_NUMBER(aSegaAnimation, 0),
		(int)CONFIG_ARRAY_NUMBER(aSegaAnimation, 1),
		(int)CONFIG_ARRAY_NUMBER(aSegaAnimation, 2),
		(int)CONFIG_ARRAY_NUMBER(aSegaAnimation, 3),
	};
	fAux.flip = CONFIG_ARRAY_BOOL(aSegaAnimation, 4) != 0;
	segaPosition.x = (int)CONFIG_ARRAY_NUMBER(aSegaAnimation, 5);
	segaPosition.y = (int)CONFIG_ARRAY_NUMBER(aSegaAnimation, 6);
	for (int i = 0; i < segaCount; ++i)
	{
		Frame f = fAux;
		sega.frames.push_back(f);
		fAux.rect.y += fAux.rect.h;
	}
	sega.speed = (float)CONFIG_OBJECT_NUMBER(config, "segaAnimationSpeed");

}

ModuleSceneInit::~ModuleSceneInit()
{
	CleanUp();
}

bool ModuleSceneInit::Start()
{
	LOG("Loading Init scene");
	segaGraphics = App->textures->Load(CONFIG_OBJECT_STRING(config, "segaGraphics"));
	flyingedgeGraphics = App->textures->Load(CONFIG_OBJECT_STRING(config, "flyingedgeGraphics"));
	
	App->audio->PlayMusic(CONFIG_OBJECT_STRING(config, "music"));
	return true;
}

update_status ModuleSceneInit::Update()
{
	App->renderer->Blit(segaGraphics, segaPosition.x, segaPosition.y, &sega.GetCurrentFrame(), 1.0f);
	return UPDATE_CONTINUE;
}

bool ModuleSceneInit::CleanUp()
{
	App->textures->Unload(segaGraphics);
	App->textures->Unload(flyingedgeGraphics);
	return false;
}

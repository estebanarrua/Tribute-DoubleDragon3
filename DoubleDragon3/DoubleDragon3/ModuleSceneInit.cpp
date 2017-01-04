#include "Globals.h"
#include "Application.h"
#include "ModuleSceneInit.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleTimer.h"

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
	CONFIG_ARRAY aTimes = CONFIG_OBJECT_ARRAY(config, "times");
	for (unsigned int i = 0; i < CONFIG_ARRAY_COUNT(aTimes) && i < TOTAL_STATES; ++i) {
		times[i] = (int)CONFIG_ARRAY_NUMBER(aTimes, i);
	}
	CONFIG_ARRAY aFlying = CONFIG_OBJECT_ARRAY(config, "flyingedgeFrame");
	flyingedge.rect = {
		(int)CONFIG_ARRAY_NUMBER(aFlying, 0),
		(int)CONFIG_ARRAY_NUMBER(aFlying, 1),
		(int)CONFIG_ARRAY_NUMBER(aFlying, 2),
		(int)CONFIG_ARRAY_NUMBER(aFlying, 3),
	};
	flyingedge.flip = CONFIG_ARRAY_BOOL(aFlying, 4) != 0;
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
	lastTime = App->timer->lastTime;
	return true;
}

update_status ModuleSceneInit::Update()
{
	switch (actualState)
	{
	case SEGA:
		App->renderer->Blit(segaGraphics, segaPosition.x, segaPosition.y, &sega.GetCurrentFrame(), 1.0f);
		break;
	case FLYING:
		App->renderer->Blit(flyingedgeGraphics, 0, 0, &flyingedge, 1.0f);
		break;
	default:
		break;
	}
	if (actualState != TOTAL_STATES) {
		if (App->timer->lastTime - lastTime > times[actualState]) {
			actualState = (initState)((int)actualState + 1);
			lastTime = App->timer->lastTime;
		}
			
	}

	return UPDATE_CONTINUE;
}

bool ModuleSceneInit::CleanUp()
{
	App->textures->Unload(segaGraphics);
	App->textures->Unload(flyingedgeGraphics);
	return false;
}

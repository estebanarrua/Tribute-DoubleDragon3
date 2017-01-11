#include "Globals.h"
#include "Application.h"
#include "ModuleSceneInit.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleTimer.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneChina.h"
#include "ModuleEntity.h"

ModuleSceneInit::ModuleSceneInit(CONFIG_OBJECT config, bool start_enabled) : Module(config, start_enabled)
{
	
}

ModuleSceneInit::~ModuleSceneInit()
{
	CleanUp();
}

bool ModuleSceneInit::Start()
{
	LOG("Loading Init scene");

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
	CONFIG_ARRAY aInitPage = CONFIG_OBJECT_ARRAY(config, "initPageFrames");
	CONFIG_ARRAY aFrame = CONFIG_ARRAY_ARRAY(aInitPage, 0);
	background.rect = {
		(int)CONFIG_ARRAY_NUMBER(aFrame, 0),
		(int)CONFIG_ARRAY_NUMBER(aFrame, 1),
		(int)CONFIG_ARRAY_NUMBER(aFrame, 2),
		(int)CONFIG_ARRAY_NUMBER(aFrame, 3),
	};
	background.flip = CONFIG_ARRAY_BOOL(aFrame, 4) != 0;
	aFrame = CONFIG_ARRAY_ARRAY(aInitPage, 1);
	bigFonts.rect = {
		(int)CONFIG_ARRAY_NUMBER(aFrame, 0),
		(int)CONFIG_ARRAY_NUMBER(aFrame, 1),
		(int)CONFIG_ARRAY_NUMBER(aFrame, 2),
		(int)CONFIG_ARRAY_NUMBER(aFrame, 3),
	};
	bigFonts.flip = CONFIG_ARRAY_BOOL(aFrame, 4) != 0;
	aFrame = CONFIG_ARRAY_ARRAY(aInitPage, 2);
	smallFonts.rect = {
		(int)CONFIG_ARRAY_NUMBER(aFrame, 0),
		(int)CONFIG_ARRAY_NUMBER(aFrame, 1),
		(int)CONFIG_ARRAY_NUMBER(aFrame, 2),
		(int)CONFIG_ARRAY_NUMBER(aFrame, 3),
	};
	smallFonts.flip = CONFIG_ARRAY_BOOL(aFrame, 4) != 0;
	CONFIG_ARRAY aStart = CONFIG_OBJECT_ARRAY(config, "starts");
	starts[0] = (int)CONFIG_ARRAY_NUMBER(aStart, 0);
	starts[1] = (int)CONFIG_ARRAY_NUMBER(aStart, 1);

	segaGraphics = App->textures->Load(CONFIG_OBJECT_STRING(config, "segaGraphics"));
	flyingedgeGraphics = App->textures->Load(CONFIG_OBJECT_STRING(config, "flyingedgeGraphics"));
	initPageGraphics = App->textures->Load(CONFIG_OBJECT_STRING(config, "initPageGraphics"));
	
	App->audio->PlayMusic(CONFIG_OBJECT_STRING(config, "music"));
	lastTime = 0;
	backgroundMaxWith = background.rect.w;
	background.rect.w = App->window->screenWidth;
	bigFontsPositionX = -App->window->screenWidth;
	App->renderer->camera.x = 0;
	App->renderer->camera.y = 0;
	return true;
}

update_status ModuleSceneInit::Update()
{
	if (lastTime == 0)
		lastTime = App->timer->lastTime;
	switch (actualState)
	{
	case SEGA:
		App->renderer->Blit(segaGraphics, segaPosition.x, segaPosition.y, &sega.GetCurrentFrame(), 1.0f);
		break;
	case FLYING:
		App->renderer->Blit(flyingedgeGraphics, 0, 0, &flyingedge, 1.0f);
		if (App->input->GetKey(starts[0]) == KEY_DOWN || App->input->GetKey(starts[1]) == KEY_DOWN) {
			actualState = (initState)((int)actualState + 1);
			lastTime = App->timer->lastTime;
		}
		break;
	case INIT_PAGE:
		if (background.rect.x + App->window->screenWidth != backgroundMaxWith)
		{
			int deltaTime = (App->timer->lastTime - backgroundTime)/2;
			background.rect.x += deltaTime;
			backgroundTime = App->timer->lastTime;
			if (background.rect.x >= (backgroundMaxWith - App->window->screenWidth * 2)) 
				bigFontsPositionX += deltaTime;
			if (background.rect.x >= backgroundMaxWith - App->window->screenWidth) {
				background.rect.x = backgroundMaxWith - App->window->screenWidth;
				bigFontsPositionX = 0;
			}
		}
		App->renderer->Blit(initPageGraphics, 0, 0, &background, 1.0f);
		App->renderer->Blit(initPageGraphics, bigFontsPositionX, 0, &bigFonts, 1.0f);
		if (bigFontsPositionX == 0) {
			App->renderer->Blit(initPageGraphics, 0, bigFonts.rect.h, &smallFonts, 1.0f);
		}
		if (App->input->GetKey(starts[0]) == KEY_DOWN)
			startPressed = 0;
		if (App->input->GetKey(starts[1]) == KEY_DOWN)
			startPressed = 1;
		break;
	default:
		break;
	}
	if (actualState != INIT_PAGE) {
		if (App->timer->lastTime - lastTime > times[actualState]) {
			actualState = (initState)((int)actualState + 1);
			lastTime = App->timer->lastTime;
		}
		if (actualState == INIT_PAGE) {
			backgroundTime = lastTime;
		}
	}
	if (startPressed != -1) {

		App->entities->playerStart[startPressed] = true;
		if (!App->scene_china->Enable() || !this->Disable()) {
			return UPDATE_ERROR;
		}
		startPressed = -1;
	}
	return UPDATE_CONTINUE;
}

bool ModuleSceneInit::CleanUp()
{
	App->textures->Unload(segaGraphics);
	App->textures->Unload(flyingedgeGraphics);
	App->textures->Unload(initPageGraphics);
	actualState = INIT_PAGE;

	return true;
}

#include "Globals.h"
#include "ModuleHub.h"
#include "Application.h"
#include "ModuleFonts.h"
#include "ModuleTimer.h"
#include "ModuleEntity.h"
#include "ModuleRender.h"
#include "Player.h"

ModuleHub::ModuleHub(CONFIG_OBJECT config, bool start_enabled) :Module(config, start_enabled)
{
}

ModuleHub::~ModuleHub()
{
	CleanUp();
}

bool ModuleHub::Start()
{
	Frame frame;
	CONFIG_ARRAY aRect = CONFIG_OBJECT_ARRAY(config, "textRect"); 
	frame.rect.x = (int)(CONFIG_ARRAY_NUMBER(aRect, 0));
	frame.rect.y = (int)(CONFIG_ARRAY_NUMBER(aRect, 1));
	frame.rect.w = (int)(CONFIG_ARRAY_NUMBER(aRect, 2));
	frame.rect.h = (int)(CONFIG_ARRAY_NUMBER(aRect, 3));
	frame.flip = false;
	fontText = App->fonts->LoadTFont(frame, CONFIG_OBJECT_STRING(config, "texture"), CONFIG_OBJECT_STRING(config, "textStr"));
	frame.rect.x += frame.rect.w;
	fontNumber = App->fonts->LoadNFont(frame, CONFIG_OBJECT_STRING(config, "texture"));
	aRect = CONFIG_OBJECT_ARRAY(config, "numbP1");
	frame.rect.x = (int)(CONFIG_ARRAY_NUMBER(aRect, 0));
	frame.rect.y = (int)(CONFIG_ARRAY_NUMBER(aRect, 1));
	frame.rect.w = (int)(CONFIG_ARRAY_NUMBER(aRect, 2));
	frame.rect.h = (int)(CONFIG_ARRAY_NUMBER(aRect, 3));
	frame.flip = false;
	fontLife[0] = App->fonts->LoadNFont(frame, CONFIG_OBJECT_STRING(config, "texture"));
	aRect = CONFIG_OBJECT_ARRAY(config, "numbP2");
	frame.rect.x = (int)(CONFIG_ARRAY_NUMBER(aRect, 0));
	frame.rect.y = (int)(CONFIG_ARRAY_NUMBER(aRect, 1));
	frame.rect.w = (int)(CONFIG_ARRAY_NUMBER(aRect, 2));
	frame.rect.h = (int)(CONFIG_ARRAY_NUMBER(aRect, 3));
	frame.flip = false;
	fontLife[1] = App->fonts->LoadNFont(frame, CONFIG_OBJECT_STRING(config, "texture"));
	gFaces = App->textures->Load(CONFIG_OBJECT_STRING(config, "faces"));
	aRect = CONFIG_OBJECT_ARRAY(config, "facesRect1");
	frame.rect.x = (int)(CONFIG_ARRAY_NUMBER(aRect, 0));
	frame.rect.y = (int)(CONFIG_ARRAY_NUMBER(aRect, 1));
	frame.rect.w = (int)(CONFIG_ARRAY_NUMBER(aRect, 2));
	frame.rect.h = (int)(CONFIG_ARRAY_NUMBER(aRect, 3));
	frame.flip = false;
	faces[0] = frame;
	aRect = CONFIG_OBJECT_ARRAY(config, "facesRect2");
	frame.rect.x = (int)(CONFIG_ARRAY_NUMBER(aRect, 0));
	frame.rect.y = (int)(CONFIG_ARRAY_NUMBER(aRect, 1));
	frame.rect.w = (int)(CONFIG_ARRAY_NUMBER(aRect, 2));
	frame.rect.h = (int)(CONFIG_ARRAY_NUMBER(aRect, 3));
	frame.flip = false;
	faces[1] = frame;
	return true;
}

update_status ModuleHub::Update()
{
	App->fonts->BlitText(128, 20, fontText, "time ");
	App->fonts->BlitNumber(168, 20, fontNumber, App->timer->GetGameTime(), 3);
	App->fonts->BlitText(128, 28, fontText, "coins ");
	App->fonts->BlitNumber(176, 28, fontNumber, App->entities->coins, 2);
	if (App->entities->players[0]->IsEnabled()) {
		App->fonts->BlitNumber(30, 15, fontLife[0],App->entities->players[0]->totalLife, 3);
		App->fonts->BlitText(38, 40, fontText, "jimmy");
		App->renderer->BlitWithOutCamera(gFaces, 78, 15, &faces[0]);
	}
	else {
		App->fonts->BlitText(38, 20, fontText, "press");
		App->fonts->BlitText(38, 28, fontText, "start");
	}
	if (App->entities->players[1]->IsEnabled()) {
		App->fonts->BlitNumber(242, 15, fontLife[1], App->entities->players[1]->totalLife, 3);
		App->fonts->BlitText(242, 40, fontText, "billy");
		App->renderer->BlitWithOutCamera(gFaces, 217, 15, &faces[1]);
	}
	else {
		App->fonts->BlitText(242, 20, fontText, "press");
		App->fonts->BlitText(242, 28, fontText, "start");
	}
	return UPDATE_CONTINUE;
}

bool ModuleHub::CleanUp()
{
	App->textures->Unload(gFaces);
	return true;
}
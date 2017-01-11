#include "Globals.h"
#include "ModuleHub.h"
#include "Application.h"
#include "ModuleFonts.h"

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
	return true;
}

update_status ModuleHub::Update()
{
	return UPDATE_CONTINUE;
}

bool ModuleHub::CleanUp()
{
	return true;
}

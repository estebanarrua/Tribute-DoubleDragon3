#include "Globals.h"
#include "Animation.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleEntity.h"
#include "Player.h"
#include "SDL/include/SDL.h"

ModuleRender::ModuleRender(CONFIG_OBJECT config) : Module(config)
{
	CONFIG_ARRAY arraySize = CONFIG_OBJECT_ARRAY(config, "screen_size");

	screenWidth = (int)(CONFIG_ARRAY_NUMBER(arraySize, 0));
	screenHeight = (int)(CONFIG_ARRAY_NUMBER(arraySize, 1));
	screenSize = (int)(CONFIG_ARRAY_NUMBER(arraySize, 2));
	vsync = CONFIG_OBJECT_BOOL(config, "vsync") != 0;
	
	camera.x = camera.y = 0;
	camera.w = screenWidth * screenSize;
	camera.h = screenHeight * screenSize;
}

// Destructor
ModuleRender::~ModuleRender()
{}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if(vsync == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);
	
	if(renderer == nullptr)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

update_status ModuleRender::PreUpdate()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update()
{
	// debug camera
	int speed = 3 * screenSize;
	int xMax = 0; 
	int xMin = screenWidth;

	if (App->entitys->players[0]->IsEnabled()) {
		xMax = App->entitys->players[0]->position.x;
		xMin = App->entitys->players[0]->position.x;
	}
	if (App->entitys->players[1]->IsEnabled() && App->entitys->players[1]->position.x > xMax) {
		xMax = App->entitys->players[1]->position.x;
	}
	if (App->entitys->players[1]->IsEnabled() && App->entitys->players[1]->position.x < xMin) {
		xMin = App->entitys->players[1]->position.x;
	}

	if (camera.x + xMax*screenSize > (screenWidth / 4) * 3 * screenSize) {
		camera.x -= speed;
		if (camera.x < (-1104+screenWidth) * screenSize)
			camera.x = (-1104 + screenWidth) * screenSize;
	}
	if (camera.x + xMin*screenSize < 27*screenSize) {
		camera.x += speed;
		if (camera.x > 0)
			camera.x = 0;
	}

	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	SDL_RenderPresent(renderer);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window
	if(renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
	}

	return true;
}

// Blit to screen
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, Frame* section, float speed)
{
	bool ret = true;
	SDL_Rect rect;
	rect.x = (int)(camera.x * speed) + x * screenSize;
	rect.y = (int)(camera.y * speed) + y * screenSize;

	if(section != NULL)
	{
		rect.w = section->rect.w;
		rect.h = section->rect.h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= screenSize;
	rect.h *= screenSize;

	SDL_RendererFlip flip = section->flip? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	if (section->flip)
		rect.x -= rect.w;

	if(SDL_RenderCopyEx(renderer,texture, &section->rect, &rect, 0, NULL, flip) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

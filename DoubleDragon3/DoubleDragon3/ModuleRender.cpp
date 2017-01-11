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

	// debug camera
	int speed = 3 * screenSize;
	int xMax = 0;
	int xMin = 1104;
	if (App->entities->IsEnabled()) {
		if (App->entities->players[0]->IsEnabled()) {
			xMax = App->entities->players[0]->position.x;
			xMin = App->entities->players[0]->position.x;
		}
		if (App->entities->players[1]->IsEnabled() && App->entities->players[1]->position.x > xMax) {
			xMax = App->entities->players[1]->position.x;
		}
		if (App->entities->players[1]->IsEnabled() && App->entities->players[1]->position.x < xMin) {
			xMin = App->entities->players[1]->position.x;
		}

		if (camera.x + xMax*screenSize >(screenWidth / 4) * 3 * screenSize) {
			camera.x = ((screenWidth / 4) * 3 * screenSize) - xMax*screenSize;
			if (camera.x < (-1104 + screenWidth) * screenSize)
				camera.x = (-1104 + screenWidth) * screenSize;
		}
		if (camera.x + xMin*screenSize < 27 * screenSize) {
			camera.x = 27 * screenSize - xMin*screenSize;
			if (camera.x > 0)
				camera.x = 0;
		}
	}

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update()
{
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

bool ModuleRender::BlitWithOutCamera(SDL_Texture* texture, int x, int y, Frame* section) {
	bool ret = true;
	SDL_Rect rect;
	rect.x = x * screenSize;
	rect.y = y * screenSize;

	if (section != NULL)
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

	SDL_RendererFlip flip = section->flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	if (section->flip)
		rect.x -= rect.w;

	if (SDL_RenderCopyEx(renderer, texture, &section->rect, &rect, 0, NULL, flip) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleRender::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera)
{
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect rec(rect);
	rec.y = rec.y * 3 + 151;
	if (use_camera)
	{
		rec.x = (int)(camera.x + rect.x * screenSize);
		rec.y = (int)(camera.y + rect.y * screenSize);
		rec.w *= screenSize;
		rec.h *= screenSize;
	}

	if (SDL_RenderFillRect(renderer, &rec) != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}
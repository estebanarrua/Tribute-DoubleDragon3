#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"

ModulePlayer::ModulePlayer(CONFIG_OBJECT config, bool start_enabled) : Module(config, start_enabled)
{
	position.x = 116;
	position.y = 128;

	// idle (billy-jimmy sprite sheet)
	idle.x = 8;
	idle.y = 2;
	idle.w = 27;
	idle.h = 61;

	// walk forward animation (billy-jimmy sprite sheet)
	forward.frames.push_back({ 8, 2, 27, 61 });
	forward.frames.push_back({ 48, 1, 25, 62 });
	forward.frames.push_back({ 80, 1, 26, 61 });
	forward.frames.push_back({ 112, 0, 26, 62 });
	forward.speed = 0.2f;

	// walk backward animation (billy-jimmy sprite sheet)
	backward.frames.push_back({542, 131, 61, 87});
	backward.frames.push_back({628, 129, 59, 90});
	backward.frames.push_back({713, 128, 57, 90});
	backward.frames.push_back({797, 127, 57, 90});
	backward.frames.push_back({883, 128, 58, 91});
	backward.frames.push_back({974, 129, 57, 89});
	backward.speed = 0.1f;

	// TODO 8: setup the walk forward animation from ryu4.png
}

ModulePlayer::~ModulePlayer()
{
	// Homework : check for memory leaks
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("Sprites/billy_jimmy.png"); // arcade version

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update
update_status ModulePlayer::Update()
{
	SDL_Rect draw = idle;

	int speed = 3;

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		position.y -= speed;
		draw = forward.GetCurrentFrame();
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		position.y += speed;
		draw = forward.GetCurrentFrame();
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		position.x -= speed;
		draw = forward.GetCurrentFrame();
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		position.x += speed;
		draw = forward.GetCurrentFrame();
	}

	App->renderer->Blit(graphics, position.x, position.y, &draw, 1.0f);

	return UPDATE_CONTINUE;
}
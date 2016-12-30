#include "Player.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"


Player::Player(CONFIG_OBJECT config) : Entity(config)
{
	CONFIG_ARRAY aPosition = CONFIG_OBJECT_ARRAY(config, "position");
	position.x = (int)(CONFIG_ARRAY_NUMBER(aPosition, 0));
	position.y = (int)(CONFIG_ARRAY_NUMBER(aPosition, 1));
	CONFIG_ARRAY aMovements = CONFIG_OBJECT_ARRAY(config, "movements");
	for (unsigned int i = 0; i < CONFIG_ARRAY_COUNT(aMovements); ++i) {
		CONFIG_OBJECT oMovement = CONFIG_ARRAY_OBJECT(aMovements, i);
		CONFIG_ARRAY aAnimation = CONFIG_OBJECT_ARRAY(oMovement, "animations");
		Animation a;
		for (unsigned int j = 0; j < CONFIG_ARRAY_COUNT(aAnimation); ++j) {
			CONFIG_ARRAY aFrame = CONFIG_ARRAY_ARRAY(aAnimation, j);
			Frame f;
			f.rect = {
				(int) CONFIG_ARRAY_NUMBER(aFrame, 0),
				(int) CONFIG_ARRAY_NUMBER(aFrame, 1),
				(int) CONFIG_ARRAY_NUMBER(aFrame, 2),
				(int) CONFIG_ARRAY_NUMBER(aFrame, 3),
			};
			f.flip = CONFIG_ARRAY_BOOL(aFrame, 4) != 0;
			a.frames.push_back(f);
		}
		a.speed = (float)CONFIG_OBJECT_NUMBER(oMovement, "speed");
		movements.push_back(a);
	}
}


Player::~Player()
{
}

bool Player::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load(CONFIG_OBJECT_STRING(config, "graphics"));

	return true;
}

update_status Player::Update()
{
	Frame draw = movements[IDLE].GetCurrentFrame();

	static int speed = 3;

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		position.y -= speed;
		draw = movements[UP].GetCurrentFrame();
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		position.y += speed;
		draw = movements[WALK].GetCurrentFrame();
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		flip = true;
		position.x -= speed;
		draw = movements[WALK].GetCurrentFrame();
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		flip = false;
		position.x += speed;
		draw = movements[WALK].GetCurrentFrame();
	}

	draw.flip ^= flip;

	App->renderer->Blit(graphics, position.x, position.y, &draw, 1.0f);

	return UPDATE_CONTINUE;
}

bool Player::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

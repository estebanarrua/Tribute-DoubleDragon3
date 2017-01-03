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
	CONFIG_ARRAY aKeys = CONFIG_OBJECT_ARRAY(config, "keys");
	for (unsigned int i = 0; i < CONFIG_ARRAY_COUNT(aKeys); ++i) {
		int k = (int) CONFIG_ARRAY_NUMBER(aKeys, i);
		keys.push_back(k);
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
	eDirection jDirection = NONE; //Jump direction.
	static int speed = 3;
	static int countWalk = 0;

	switch (playerState)
	{
	case IDLE:
	case WALK:
		if (App->input->GetKey(keys[K_LEFT]) == KEY_REPEAT)
		{
			playerState = WALK;
			jDirection = LEFT;
			position.x -= speed;
			draw = movements[WALK].GetCurrentFrame();
			if (!flip)
				position.x += draw.rect.w;
			flip = true;
		}
		if (App->input->GetKey(keys[K_RIGHT]) == KEY_REPEAT)
		{
			playerState = WALK;
			jDirection = RIGHT;
			position.x += speed;
			draw = movements[WALK].GetCurrentFrame();
			if (flip)
				position.x -= draw.rect.w;
			flip = false;
		}

		if (App->input->GetKey(keys[K_UP]) == KEY_REPEAT)
		{
			playerState = WALK;
			position.y -= speed;
			draw = movements[UP].GetCurrentFrame();
		}

		if (App->input->GetKey(keys[K_DOWN]) == KEY_REPEAT)
		{
			playerState = WALK;
			position.y += speed;
			draw = movements[WALK].GetCurrentFrame();
		}

		if (App->input->GetKey(keys[K_B]) == KEY_DOWN)
		{
			draw = Jump(jDirection);
		}
		if (App->input->GetKey(keys[K_A]) == KEY_DOWN)
		{
			draw = Punch();
		}
		if (App->input->GetKey(keys[K_C]) == KEY_DOWN)
		{
			draw = Kick();
		}
		break;
	case JUMP:
	case FLY_KICK:
		if (App->input->GetKey(keys[K_C]) == KEY_DOWN)
		{
			playerState = FLY_KICK;
		}
		draw = Jump(jDirection);
		break;
	case PUNCH:
		draw = Punch();
		break;
	case KICK:
		draw = Kick();
		break;
	default:
		break;
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

Frame Player::Jump(eDirection d)
{
	const int maxCount = 7;
	static int ySpeed = -3;
	static int xSpeed = 0;
	static int yPosition = 0;
	if (playerState != JUMP && playerState != FLY_KICK) {
		playerState = JUMP;
		if(d == RIGHT)
			xSpeed = 3;
		if(d == LEFT)
			xSpeed = -3;
		yPosition = position.y;
	}
	else 
	{
		position.x += xSpeed;
		position.y += ySpeed;
		if (position.y <= yPosition + maxCount * ySpeed)
			ySpeed = 3;
		if (position.y >= yPosition)
		{
			playerState = IDLE;
			xSpeed = 0;
			ySpeed = -3;
		}
	}
	return movements[playerState].GetCurrentFrame();
}

Frame Player::Punch()
{
	static int count = 0;
	if (playerState != PUNCH) {
		playerState = PUNCH;
		count = 0;
	}
	else {
		++count;
		if (count >= 5 )
			playerState = IDLE;
	}
	return movements[PUNCH].GetCurrentFrame();
}

Frame Player::Kick()
{
	static int count = 0;
	if (playerState != KICK) {
		playerState = KICK;
		count = 0;
	}
	else {
		++count;
		if (count >= 5)
			playerState = IDLE;
	}
	return movements[KICK].GetCurrentFrame();
}

#include "Enemy.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "Player.h"


Enemy::Enemy(CONFIG_OBJECT config) : Entity(config)
{
	CONFIG_ARRAY aPosition = CONFIG_OBJECT_ARRAY(config, "position");
	position.x = (int)(CONFIG_ARRAY_NUMBER(aPosition, 0));
	position.y = (int)(CONFIG_ARRAY_NUMBER(aPosition, 1));
	zPosition = (int)(CONFIG_ARRAY_NUMBER(aPosition, 2));
	CONFIG_ARRAY aMovements = CONFIG_OBJECT_ARRAY(config, "movements");
	for (unsigned int i = 0; i < CONFIG_ARRAY_COUNT(aMovements); ++i) {
		CONFIG_OBJECT oMovement = CONFIG_ARRAY_OBJECT(aMovements, i);
		CONFIG_ARRAY aAnimation = CONFIG_OBJECT_ARRAY(oMovement, "animations");
		Animation a;
		for (unsigned int j = 0; j < CONFIG_ARRAY_COUNT(aAnimation); ++j) {
			CONFIG_ARRAY aFrame = CONFIG_ARRAY_ARRAY(aAnimation, j);
			Frame f;
			f.rect = {
				(int)CONFIG_ARRAY_NUMBER(aFrame, 0),
				(int)CONFIG_ARRAY_NUMBER(aFrame, 1),
				(int)CONFIG_ARRAY_NUMBER(aFrame, 2),
				(int)CONFIG_ARRAY_NUMBER(aFrame, 3),
			};
			f.flip = CONFIG_ARRAY_BOOL(aFrame, 4) != 0;
			a.frames.push_back(f);
		}
		a.speed = (float)CONFIG_OBJECT_NUMBER(oMovement, "speed");
		movements.push_back(a);
	}
}

Enemy::~Enemy()
{

}

bool Enemy::Start()
{
	LOG("Loading enemy");

	graphics = App->textures->Load(CONFIG_OBJECT_STRING(config, "graphics"));
	target = nullptr;

	SDL_Rect colRect = { position.x, zPosition - 1, movements[IDLE].GetCurrentFrame().rect.w, 3 };
	collider = App->collisions->AddCollider(colRect, ENEMY);
	return true;
}

update_status Enemy::Update()
{
	Frame draw = movements[E_IDLE].GetCurrentFrame();
	static int speed = 3;
	static int punch = 2;
	static int wait = 5;

	switch (enemyState)
	{
	case E_IDLE:
		if (!collider->collided) {
			enemyState = E_WALK;
		}
		else {
			if (wait == 0) {
				wait = 5;
				if (punch > 0) {
					draw = Punch();
					--punch;
				}
				else {
					draw = Kick();
					punch = 2;
				}
			}
			else {
				--wait;
			}
		}
		break;
	case E_WALK:
		if (target != nullptr) {
			if (collider->collided) {
				enemyState = E_IDLE;
			}
			else {
				if (position.x < target->position.x) {
					position.x += speed;
					if (flip)
						position.x -= draw.rect.w;
					flip = false;
					draw = movements[E_WALK].GetCurrentFrame();
				}
				if (position.x > target->position.x) {
					position.x -= speed;
					if (!flip)
						position.x += draw.rect.w;
					flip = true;
					draw = movements[E_WALK].GetCurrentFrame();
				}
				if (zPosition < target->zPosition) {
					++zPosition;
					position.y += speed;
					draw = movements[E_WALK].GetCurrentFrame();
				}
				if (zPosition > target->zPosition) {
					--zPosition;
					position.y -= speed;
					draw = movements[E_UP].GetCurrentFrame();
				}
			}
		}
		break;
	case E_PUNCH:
		draw = Punch();
		break;
	case E_KICK:
		draw = Kick();
		break;
	default:
		break;
	}

	draw.flip ^= flip;
	App->renderer->Blit(graphics, position.x, position.y, &draw, 1.0f);
	int colX = position.x;
	if (flip)
		colX -= movements[E_IDLE].GetCurrentFrame().rect.w;
	collider->SetPos(colX, zPosition - 1);

	return UPDATE_CONTINUE;
}

bool Enemy::CleanUp()
{
	LOG("Unloading enemy");

	App->textures->Unload(graphics);

	return true;
}

Frame Enemy::Punch()
{
	static int count = 0;
	static Collider* collider = nullptr;
	if (enemyState != E_PUNCH) {
		enemyState = E_PUNCH;
		count = 0;
		int xCol = 0;
		if (flip)
			xCol = position.x - movements[E_IDLE].GetCurrentFrame().rect.w - 3;
		else
			xCol = position.x + movements[E_IDLE].GetCurrentFrame().rect.w;
		collider = App->collisions->AddCollider({xCol,zPosition - 1,3,3}, E_C_PUNCH);
	}
	else {
		++count;
		if (count >= 5) {
			enemyState = E_IDLE;
			collider->to_delete = true;
			collider = nullptr;
		}
	}
	return movements[E_PUNCH].GetCurrentFrame();
}

Frame Enemy::Kick()
{
	static int count = 0;
	static Collider* collider = nullptr;
	if (enemyState != E_KICK) {
		enemyState = E_KICK;
		count = 0;
		int xCol = 0;
		if (flip)
			xCol = position.x - movements[E_IDLE].GetCurrentFrame().rect.w - 6;
		else
			xCol = position.x + movements[E_IDLE].GetCurrentFrame().rect.w;
		collider = App->collisions->AddCollider({ xCol,zPosition - 1,6,3 }, E_C_KICK);
	}
	else {
		++count;
		if (count >= 5) {
			enemyState = E_IDLE;
			collider->to_delete = true;
			collider = nullptr;
		}
			
	}
	return movements[E_KICK].GetCurrentFrame();
}
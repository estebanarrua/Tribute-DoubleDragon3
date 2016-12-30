#include "Player.h"
#include "Application.h"
#include "ModuleTextures.h"



Player::Player(CONFIG_OBJECT config) : Entity(config)
{
	CONFIG_ARRAY aPosition = CONFIG_OBJECT_ARRAY(config, "position");
	position.x = (int)(CONFIG_ARRAY_NUMBER(aPosition, 0));
	position.y = (int)(CONFIG_ARRAY_NUMBER(aPosition, 1));
	CONFIG_ARRAY aMovements = CONFIG_OBJECT_ARRAY(config, "movements");
	for (unsigned int i = 0; i < CONFIG_ARRAY_COUNT(aMovements) && i < movements.size(); ++i) {
		CONFIG_OBJECT oMovement = CONFIG_ARRAY_OBJECT(aMovements, i);
		CONFIG_ARRAY aAnimation = CONFIG_OBJECT_ARRAY(oMovement, "animations");
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
			movements[i].frames.push_back(f);
		}
		movements[i].speed = CONFIG_OBJECT_NUMBER(oMovement, "speed");
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
	return update_status();
}

bool Player::CleanUp()
{
	return false;
}

#include "Enemy.h"


Enemy::Enemy(CONFIG_OBJECT config) : Entity(config)
{
}

Enemy::~Enemy()
{
}

bool Enemy::Start()
{
	return false;
}

update_status Enemy::Update()
{
	return update_status();
}

bool Enemy::CleanUp()
{
	return false;
}

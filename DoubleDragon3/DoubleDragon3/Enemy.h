#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity.h"
#include "Animation.h"

enum eMovements
{
	IDLE,
	WALK,
	RUN,
	UP,
	JUMP,
	PUNCH,
	KICK,
	FLY_KICK,
	FLY_KNEE,
	HEADER,

	//Specials Tricks
	ROTATING_KICK,
	KEY,

	//Weapons
	NUNCHACUS,

	MOVEMENTS_COUNT
};

enum eDirection
{
	NONE,
	RIGHT,
	LEFT
};

class Enemy : public Entity
{
	//Movements
	vector<Animation> movements;
	eMovements enemyState = IDLE;

public:
	Enemy(CONFIG_OBJECT config);
	~Enemy();

	bool Start();
	update_status Update();
	bool CleanUp();
};

#endif //__ENEMY_H__

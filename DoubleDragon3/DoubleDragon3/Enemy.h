#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity.h"
#include "Animation.h"
#include "ModuleCollision.h"

enum eMovEnemy
{
	E_IDLE,
	E_WALK,
	E_UP,
	E_PUNCH,
	E_KICK,
	E_PUNCH_RECIVE,
	E_KICK_RECIVE,
	E_DEAD,

	E_MOVEMENTS_COUNT
};

class Player;

class Enemy : public Entity
{

private:
	bool imDead;

public:
	//Movements
	vector<Animation> movements;
	eMovEnemy enemyState = E_IDLE;
	Player* target;

public:
	Enemy(CONFIG_OBJECT config);
	~Enemy();

	bool Start();
	update_status Update();
	bool CleanUp();
private:
	Frame Punch();
	Frame Kick();
	Frame ReciveHit(ColliderType collision);
	Frame Dead();
	bool ReachPlayer();
	ColliderType AttackMe();
};

#endif //__ENEMY_H__

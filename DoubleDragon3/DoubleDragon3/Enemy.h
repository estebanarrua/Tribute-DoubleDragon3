#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity.h"
#include "Animation.h"

enum eMovEnemy
{
	E_IDLE,
	E_WALK,
	E_UP,
	E_PUNCH,
	E_KICK,

	E_MOVEMENTS_COUNT
};

class Player;

class Enemy : public Entity
{

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
};

#endif //__ENEMY_H__

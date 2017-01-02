#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Animation.h"

enum eMovements
{
	IDLE,
	WALK,
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

class Player :public Entity
{

private:
	//Movements
	vector<Animation> movements;

	bool isJumping = false;
	bool isHitting = false;
	
public:
	Player(CONFIG_OBJECT config);
	~Player();

	bool Start();
	update_status Update();
	bool CleanUp();

private:
	Frame Jump(eDirection d);
	Frame Punch();
	Frame Kick();
};

#endif //PLAYER


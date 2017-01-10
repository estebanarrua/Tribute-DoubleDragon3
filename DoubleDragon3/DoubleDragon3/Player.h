#ifndef __PLAYER_H__
#define __PLAYER_H__

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

enum eKeys
{
	K_UP,
	K_DOWN,
	K_RIGHT,
	K_LEFT,

	K_A,
	K_B,
	K_C,

	K_START,
	K_SELECT,

	KEYS_COUNT
};

class Player :public Entity
{

private:
	//Movements
	vector<Animation> movements;
	vector<int> keys;
	eMovements playerState = IDLE;
	
public:
	Player(CONFIG_OBJECT config);
	~Player();

	bool Start();
	update_status Update();
	bool CleanUp();

private:
	void ChangeXPosition(int diff);
	Frame Jump(eDirection d);
	Frame Punch();
	Frame Kick();
};

#endif //PLAYER


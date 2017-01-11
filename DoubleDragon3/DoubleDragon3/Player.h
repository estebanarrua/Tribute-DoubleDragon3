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
	PUNCH_RECIVE,
	KICK_RECIVE,
	DEAD,
	STAND_UP,

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
	bool imDead = false;
	bool isUntouchable = false;
	bool invisible = false;
	unsigned int timeUntouchable = 0;

public:
	Player(CONFIG_OBJECT config);
	~Player();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();

private:
	void ChangeXPosition(int diff);
	Frame Jump(eDirection d);
	Frame Punch();
	Frame Kick();
	Frame ReciveHit();
	Frame Dead();
	Frame StandUp();
};

#endif //PLAYER


#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Animation.h"

enum movements
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

class Player :public Entity
{
private:
	
	//Movements
	vector<Animation> movements;

public:
	Player(CONFIG_OBJECT config);
	~Player();

	bool Start();
	update_status Update();
	bool CleanUp();
};

#endif //PLAYER


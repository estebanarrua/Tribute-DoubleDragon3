#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Animation.h"

class Player :public Entity
{
private:
	
	Animation right;
	Animation left;
	Animation rightPunch;
	Animation leftPunch;

public:
	Player(CONFIG_OBJECT config);
	~Player();
};

#endif //PLAYER


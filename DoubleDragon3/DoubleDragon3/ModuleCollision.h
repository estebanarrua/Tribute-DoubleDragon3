#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#include<list>
#include "Module.h"

enum ColliderType
{
	PLAYER,
	ENEMY,
	P_C_PUNCH,
	E_C_PUNCH,
	P_C_KICK,
	E_C_KICK,

	MAX_COLAIDERS
};
															/*PLAYER  ENEMY  P_PUNCH  E_PUNCH  P_KICK  E_KICK  */
const bool ColliderMatrix[MAX_COLAIDERS][MAX_COLAIDERS] = { { false,  true,  false,   true,    false,  true },      //PLAYER
															{ true,   false, true,    false,   true,   false},		//ENEMY
															{ false,  true,  false,   false,   false,  false},		//P_PUNCH
															{ true,   false, false,   false,   false,  false},		//E_PUNCH
															{ false,  true,  false,   false,   false,  false},		//P_KICK
															{ true,   false, false,   false,   false,  false}};	//E_KICK
															

struct Collider
{
	SDL_Rect rect = { 0,0,0,0 };
	ColliderType type;
	bool to_delete = false;
	bool collided = false;
	ColliderType tCollided;
	
	Collider(SDL_Rect rectangle, ColliderType type) : // expand this call if you need to
		rect(rectangle), type(type), tCollided(type)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool CheckCollision(const SDL_Rect& r) const;
};

class ModuleCollision : public Module
{
private:

	std::list<Collider*> colliders;
	bool debug = false;

public:

	ModuleCollision(CONFIG_OBJECT config);
	~ModuleCollision();

	update_status PreUpdate();
	update_status Update();

	bool CleanUp();

	Collider* AddCollider(const SDL_Rect& rect, ColliderType type);
	void DebugDraw();

};

#endif // __ModuleCollision_H__
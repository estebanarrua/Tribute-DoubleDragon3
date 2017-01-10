#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#include<list>
#include "Module.h"

enum ColliderType
{
	PLAYER,
	ENEMY,
	P_HIT,
	E_HIT,

	MAX_COLAIDERS
};

const bool ColliderMatrix[MAX_COLAIDERS][MAX_COLAIDERS] = { {false,false,false,true}, {false,false,true,false}, {false,true,false,false} ,{true,false,false,false} };

struct Collider
{
	SDL_Rect rect = { 0,0,0,0 };
	ColliderType type;
	bool to_delete = false;
	bool collided = false;
	
	Collider(SDL_Rect rectangle, ColliderType type) : // expand this call if you need to
		rect(rectangle), type(type)
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
	//void DebugDraw();

};

#endif // __ModuleCollision_H__
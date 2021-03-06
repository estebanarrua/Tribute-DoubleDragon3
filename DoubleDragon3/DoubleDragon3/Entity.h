#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Globals.h"
#include "Point.h"

struct SDL_Texture;

struct Collider;

class Entity
{

private:
	bool active;
public:
	CONFIG_OBJECT config;
	iPoint position;
	int zPosition = 0;
	bool flip; 
	SDL_Texture* graphics = nullptr;
	Collider* collider = nullptr;
	int totalLife;
	int life;
	bool to_delete;
	int soundJump = 0;
	int soundHit = 0;
	int soundDead = 0;

public:
	Entity(CONFIG_OBJECT config, bool active = false, bool flip = false) : config(config), active(active), flip(flip), to_delete(false)
	{}

	virtual ~Entity()
	{}
	
	bool IsEnabled() const
	{
		return active;
	}

	bool Enable()
	{
		if (active == false)
			return active = Start();

		return true;
	}

	bool Disable()
	{
		if (active == true)
			return !(active = !CleanUp());

		return true;
	}

	virtual bool Init()
	{
		return true;
	}

	virtual bool Start()
	{
		return true;
	}

	virtual update_status PreUpdate()
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status Update()
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status PostUpdate()
	{
		return UPDATE_CONTINUE;
	}

	virtual bool CleanUp()
	{
		return true;
	}

	bool isZLower(Entity* ent) const
	{
		return zPosition <= ent->zPosition;
	}
};

#endif //ENTITY


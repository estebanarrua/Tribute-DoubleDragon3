#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Globals.h"
#include "Point.h"

struct SDL_Texture;

class Entity
{

public:
	CONFIG_OBJECT config;
	iPoint position;
	bool flip; 
	SDL_Texture* graphics = nullptr;

public:
	Entity(CONFIG_OBJECT config, bool flip = false) : config(config), flip(flip)
	{}

	virtual ~Entity()
	{}

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
};

#endif //ENTITY


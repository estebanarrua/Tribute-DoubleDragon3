#ifndef __MODULEENTITY_H__
#define __MODULEENTITY_H__

#include <list>
#include <vector>
#include "Module.h"
#include "Entity.h"

class Player;

class ModuleEntity : public Module
{
public:
	std::vector<Player*> players;
	std::list<Entity*> entities;
	bool playerStart[2] = { false, false };

public:
	ModuleEntity(CONFIG_OBJECT config, bool start_enabled = true);
	~ModuleEntity();

	bool Start();
	update_status Update();
	bool CleanUp();
};

#endif //MODULEENTITY

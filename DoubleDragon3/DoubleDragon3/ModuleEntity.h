#ifndef __MODULEENTITY_H__
#define __MODULEENTITY_H__

#include <list>
#include "Module.h"
#include "Entity.h"

class ModuleEntity : public Module
{
public:
	std::list<Entity*> entities;

public:
	ModuleEntity(CONFIG_OBJECT config, bool start_enabled = true);
	~ModuleEntity();

	bool Start();
	update_status Update();
	bool CleanUp();
};

#endif //MODULEENTITY

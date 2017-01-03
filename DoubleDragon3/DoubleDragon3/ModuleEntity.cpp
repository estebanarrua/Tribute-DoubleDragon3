#include "Globals.h"
#include "ModuleEntity.h"
#include "Player.h"

using namespace std;

ModuleEntity::ModuleEntity(CONFIG_OBJECT config, bool start_enabled) : Module(config, start_enabled)
{
	Entity* e = new Player(CONFIG_OBJECT_OBJECT(config, "player2"));
	entities.push_back(e);
}

ModuleEntity::~ModuleEntity()
{
	for (list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		RELEASE(*it);
	entities.clear();
}

bool ModuleEntity::Start()
{
	bool ret = true;

	for (list<Entity*>::iterator it = entities.begin(); it != entities.end() && ret; ++it)
		(*it)->Start();

	return ret;
}

update_status ModuleEntity::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for (list<Entity*>::iterator it = entities.begin(); it != entities.end() && ret == UPDATE_CONTINUE; ++it)
		(*it)->Update();

	return ret;
}

bool ModuleEntity::CleanUp()
{

	bool ret = true;

	for (list<Entity*>::reverse_iterator it = entities.rbegin(); it != entities.rend() && ret; ++it)
		ret = (*it)->CleanUp();

	return ret;
}

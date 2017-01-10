#include "Globals.h"
#include "ModuleEntity.h"
#include "Player.h"

using namespace std;

ModuleEntity::ModuleEntity(CONFIG_OBJECT config, bool start_enabled) : Module(config, start_enabled)
{
	Player* player1 = new Player(CONFIG_OBJECT_OBJECT(config, "player1"));
	entities.push_back((Entity*)player1);
	players.push_back(player1);
	Player* player2 = new Player(CONFIG_OBJECT_OBJECT(config, "player2"));
	entities.push_back((Entity*)player2);
	players.push_back(player2);

}

ModuleEntity::~ModuleEntity()
{
	players.clear();
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
		if((*it)->IsEnabled())
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

#include "Globals.h"
#include "ModuleEntity.h"
#include "Player.h"
#include "Enemy.h"

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
	if (playerStart[0])
		players[0]->Enable();
	if (playerStart[1])
		players[1]->Enable();

	for (list<Entity*>::iterator it = entities.begin(); it != entities.end() && ret; ++it)
		if ((*it)->IsEnabled())
			(*it)->Start();

	return ret;
}

update_status ModuleEntity::PreUpdate()
{
	entitiesZOrder.clear();
	for (list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		if ((*it)->IsEnabled())
			entitiesZOrder.push_back((*it));
	OrderByZ( 0, entitiesZOrder.size() - 1);

	return UPDATE_CONTINUE;
}



update_status ModuleEntity::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for (vector<Entity*>::iterator it = entitiesZOrder.begin(); it != entitiesZOrder.end() && ret == UPDATE_CONTINUE; ++it)
		if((*it)->IsEnabled())
			ret = (*it)->Update();

	return ret;
}

bool ModuleEntity::CleanUp()
{

	bool ret = true;

	for (list<Entity*>::reverse_iterator it = entities.rbegin(); it != entities.rend() && ret; ++it)
		ret = (*it)->CleanUp();
	entities.clear();

	return ret;
}

void ModuleEntity::OrderByZ( int pIni, int pEnd)
{
	vector<Entity*> ret;
	if (pEnd - pIni > 1)  {
		int pMiddle = (pEnd - pIni) / 2;
		pMiddle += pIni;
		OrderByZ( pIni, pMiddle);
		OrderByZ( ++pMiddle, pEnd);
		int i = pIni;
		int j = pMiddle;
		while (i < pMiddle && j < pEnd)
		{
			if (entitiesZOrder[j]->isZLower(entitiesZOrder[i])) {
				Entity* aux = entitiesZOrder[j];
				for (int k = j; k > i; --k) {
					entitiesZOrder[k] = entitiesZOrder[k - 1];
				}
				entitiesZOrder[i] = aux;
				++i;
				++j;
			}
			else {
				++i;
			}
		}
	}
	else {
		if (pEnd != pIni) {
			if (!entitiesZOrder[pIni]->isZLower(entitiesZOrder[pEnd])) {
				Entity* aux = entitiesZOrder[pIni];
				entitiesZOrder[pIni] = entitiesZOrder[pEnd];
				entitiesZOrder[pEnd] = aux;
			}
		}
	}
}




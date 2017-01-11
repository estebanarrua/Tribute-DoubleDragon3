#ifndef __MODULEENTITY_H__
#define __MODULEENTITY_H__

#include <list>
#include <vector>
#include "Module.h"
#include "Entity.h"

class Player;
class Enemy;

class ModuleEntity : public Module
{
private:
	int maxEnemies[2];
	int enemiesAlive = 0;
	
public:
	std::vector<Player*> players;
	std::list<Enemy*> enemies;
	std::list<Entity*> entities;
	std::vector<Entity*> entitiesZOrder;
	bool playerStart[2] = { false, false };

public:
	ModuleEntity(CONFIG_OBJECT config, bool start_enabled = true);
	~ModuleEntity();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();

private:
	void OrderByZ( int pIni, int pEnd);
	void GenerateEnemies();
	void LeadEnemies();
};

#endif //MODULEENTITY

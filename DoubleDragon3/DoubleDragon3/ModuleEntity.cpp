#include "Globals.h"
#include "Application.h"
#include "ModuleEntity.h"
#include "ModuleInput.h"
#include "ModuleTimer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneInit.h"
#include "ModuleSceneChina.h"
#include "ModuleHub.h"
#include "Player.h"
#include "Enemy.h"

using namespace std;

ModuleEntity::ModuleEntity(CONFIG_OBJECT config, bool start_enabled) : Module(config, start_enabled)
{
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
	CONFIG_ARRAY aMaxEnemies = CONFIG_OBJECT_ARRAY(config, "maxEnemies");
	maxEnemies[0] = (int)(CONFIG_ARRAY_NUMBER(aMaxEnemies, 0));
	maxEnemies[1] = (int)(CONFIG_ARRAY_NUMBER(aMaxEnemies, 1));
	restOfEnemies = (int)(CONFIG_ARRAY_NUMBER(aMaxEnemies, 2));

	Player* player1 = new Player(CONFIG_OBJECT_OBJECT(config, "player1"));
	entities.push_back((Entity*)player1);
	players.push_back(player1);
	Player* player2 = new Player(CONFIG_OBJECT_OBJECT(config, "player2"));
	entities.push_back((Entity*)player2);
	players.push_back(player2);
	CONFIG_ARRAY aStart = CONFIG_OBJECT_ARRAY(config, "starts");
	starts[0] = (int)CONFIG_ARRAY_NUMBER(aStart, 0);
	starts[1] = (int)CONFIG_ARRAY_NUMBER(aStart, 1);

	for (list<Entity*>::iterator it = entities.begin(); it != entities.end() && ret; ++it)
		if ((*it)->IsEnabled())
			(*it)->Start();
	if (playerStart[0])
		players[0]->Enable();
	if (playerStart[1])
		players[1]->Enable();
	App->timer->StartGameTime((int) CONFIG_OBJECT_NUMBER(config, "time"));
	coins = (int)CONFIG_OBJECT_NUMBER(config, "coins");
	gameState = GAMMING;

	return ret;
}

update_status ModuleEntity::PreUpdate()
{
	if (App->input->GetKey(starts[0]) == KEY_DOWN || App->input->GetKey(starts[1]) == KEY_DOWN) {
		switch (gameState)
		{
		case GAMMING:
			if (App->input->GetKey(starts[0]) == KEY_DOWN && !players[0]->IsEnabled() && coins>=1) {
				App->timer->StartGameTime((int)CONFIG_OBJECT_NUMBER(config, "time"));
				players[0]->Enable();
				--coins;
			}
			else if (App->input->GetKey(starts[1]) == KEY_DOWN && !players[1]->IsEnabled() && coins >= 1) {
				App->timer->StartGameTime((int)CONFIG_OBJECT_NUMBER(config, "time"));
				players[1]->Enable();
				--coins;
			}
			else {
				gameState = PAUSE;
			}
			break;
		case PAUSE:
			if (App->input->GetKey(starts[0]) == KEY_DOWN && players[0]->IsEnabled())
				gameState = GAMMING;
			else if (App->input->GetKey(starts[1]) == KEY_DOWN && players[1]->IsEnabled())
				gameState = GAMMING;
			break;
		case GAME_OVER:
		case WIN:
			this->Disable();
			App->collisions->Disable();
			App->hub->Disable();
			App->fade->FadeToBlack(App->scene_init, App->scene_china);
			break;
		default:
			break;
		}
	}

	if (gameState == GAMMING) {
		
		if ((coins == 0 && !players[0]->IsEnabled() && !players[1]->IsEnabled()) || App->timer->GetGameTime() == 0) {
			gameState = GAME_OVER;
		}
		if (enemies.size() == 0 && restOfEnemies == 0) {
			gameState = WIN;
		}

		GenerateEnemies();
		LeadEnemies();

		entitiesZOrder.clear();

		for (list<Enemy*>::iterator it = enemies.begin(); it != enemies.end();) {
			if ((*it)->to_delete == true)
			{
				it = enemies.erase(it);
			}
			else {
				++it;
			}
		}

		for (list<Entity*>::iterator it = entities.begin(); it != entities.end();)
		{
			if ((*it)->to_delete == true)
			{
				RELEASE(*it);
				it = entities.erase(it);
			}
			else {
				if ((*it)->IsEnabled()) {
					(*it)->PreUpdate();
					entitiesZOrder.push_back((*it));
				}
				++it;
			}
		}

		OrderByZ(0, entitiesZOrder.size() - 1);
	}	

	return UPDATE_CONTINUE;
}

update_status ModuleEntity::Update()
{
	update_status ret = UPDATE_CONTINUE;
	if (gameState == GAMMING) {
		for (vector<Entity*>::iterator it = entitiesZOrder.begin(); it != entitiesZOrder.end() && ret == UPDATE_CONTINUE; ++it)
			if ((*it)->IsEnabled())
				ret = (*it)->Update();
	}

	return ret;
}

update_status ModuleEntity::PostUpdate() {
	update_status ret = UPDATE_CONTINUE;
	if (gameState == GAMMING) {
		for (list<Entity*>::iterator it = entities.begin(); it != entities.end() && ret == UPDATE_CONTINUE; ++it)
			if ((*it)->IsEnabled())
				ret = (*it)->PostUpdate();
	}

	return ret;
}

bool ModuleEntity::CleanUp()
{

	bool ret = true;

	for (list<Entity*>::reverse_iterator it = entities.rbegin(); it != entities.rend() && ret; ++it)
		ret = (*it)->CleanUp();
	entities.clear();
	entitiesZOrder.clear();
	players.clear();
	enemies.clear();

	return ret;
}

void ModuleEntity::OrderByZ( int pIni, int pEnd)
{
	if (pEnd - pIni > 1)  {
		int pMiddle = (pEnd - pIni) / 2;
		pMiddle += pIni;
		OrderByZ( pIni, pMiddle);
		OrderByZ( ++pMiddle, pEnd);
		int i = pIni;
		int j = pMiddle;
		while (i < pMiddle && j <= pEnd)
		{
			if (entitiesZOrder[j]->isZLower(entitiesZOrder[i])) {
				Entity* aux = entitiesZOrder[j];
				for (int k = j; k > i; --k) {
					entitiesZOrder[k] = entitiesZOrder[k - 1];
				}
				entitiesZOrder[i] = aux;
				++i;
				++j;
				++pMiddle;
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

void ModuleEntity::GenerateEnemies()
{
	static bool right = true;
	static int count = 5;
	unsigned int max = maxEnemies[0];
	if (count > 0) {
		--count;
	}
	else {
		if (players[0]->IsEnabled() && players[1]->IsEnabled())
			max = maxEnemies[1];
		if (enemies.size() < max && restOfEnemies > 0) {
			Entity* enemy = new Enemy(CONFIG_OBJECT_OBJECT(config, "enemy1"));
			enemy->Enable();
			if (right)
				enemy->position.x = enemy->position.x + players[0]->position.x;
			else
				enemy->position.x = players[0]->position.x - enemy->position.x;
			right = !right;
			enemy->position.y = players[0]->position.y;
			enemy->zPosition = players[0]->zPosition;
			entities.push_back(enemy);
			enemies.push_back((Enemy*)enemy);
			--restOfEnemies;
		}
		count = 5;
	}
	
}

void ModuleEntity::LeadEnemies()
{
	int i = 0;
	for (list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it) 
		if ((*it)->IsEnabled()) {
			if (players[i]->IsEnabled()) {
				(*it)->target = players[i];
				i = (i + 1) % 2;
			}
			else {
				i = (i + 1) % 2;
				if (players[i]->IsEnabled()) {
					(*it)->target = players[i];
				}
			}
		}
}




#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

using namespace std;

ModuleCollision::ModuleCollision(CONFIG_OBJECT config): Module(config)
{
}

// Destructor
ModuleCollision::~ModuleCollision()
{
	CleanUp();
}

update_status ModuleCollision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end();)
	{
		if ((*it)->to_delete == true)
		{
			RELEASE(*it);
			it = colliders.erase(it);
		}
		else
			++it;
	}

	return UPDATE_CONTINUE;
}

update_status ModuleCollision::Update()
{
	for (list<Collider*>::iterator it1 = colliders.begin(); it1 != colliders.end();)
	{
		list<Collider*>::iterator it2 = it1;
		for (++it2; it2 != colliders.end();)
		{
			if (ColliderMatrix[(*it1)->type][(*it2)->type])
				if ((*it1)->CheckCollision((*it2)->rect)) 
				{
					(*it1)->collided = true;
					(*it1)->tCollided = (*it2)->type;
					(*it2)->collided = true;
					(*it2)->tCollided = (*it1)->type;
				}
				else {
					(*it1)->collided = false;
					(*it2)->collided = false;
				}
			++it2;
		}
		++it1;
	}

	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(debug == true)
		DebugDraw();

	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it) {
		if ((*it)->type == PLAYER)
			App->renderer->DrawQuad((*it)->rect, 0, 0, 255, 80, true);
		if ((*it)->type == ENEMY)
			App->renderer->DrawQuad((*it)->rect, 0, 255, 0, 80, true);
		if ((*it)->type == E_C_PUNCH || (*it)->type == E_C_KICK)
			App->renderer->DrawQuad((*it)->rect, 255, 0, 0, 80, true);
		if ((*it)->type == P_C_PUNCH || (*it)->type == P_C_KICK)
			App->renderer->DrawQuad((*it)->rect, 255, 255, 0, 80, true);
	}
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		RELEASE(*it);

	colliders.clear();

	return true;
}

Collider* ModuleCollision::AddCollider(const SDL_Rect& rect, ColliderType type)
{
	Collider* ret = new Collider(rect, type);

	colliders.push_back(ret);

	return ret;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	SDL_Rect ra = rect;
	SDL_Rect rb = r;
	if (r.w > rect.w){
		ra = r;
		rb = rect;
	}
	if ((ra.x <= rb.x) && (rb.x <= ra.x + ra.w) || (ra.x <= rb.x + rb.w) && (rb.x + rb.w <= ra.x + ra.w)) {
		ra = rect;
		rb = r;
		if (r.h >= rect.h) {
			ra = r;
			rb = rect;
			if ((ra.y - ra.h <= rb.y) && (rb.y <= ra.y) || (ra.y - ra.h <= rb.y - rb.h) && (rb.y - rb.h <= ra.y)) {
				return true;
			}
		}
	}
		

	return false;
}

#ifndef __MODULERENDER_H__
#define __MODULERENDER_H__

#include "Module.h"
#include "Globals.h"
#include "Point.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;
struct Frame;

class ModuleRender : public Module
{

public:
	SDL_Renderer* renderer = nullptr;
	SDL_Rect camera;

	// Configuration -----------
	int screenWidth = 0;
	int screenHeight = 0;
	int screenSize = 0;
	bool vsync = false;
	
public:
	ModuleRender(CONFIG_OBJECT config);
	~ModuleRender();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	bool Blit(SDL_Texture* texture, int x, int y, Frame* section, float speed = 1.0f);

	bool DrawQuad(const SDL_Rect & rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera);

};

#endif // __MODULERENDER_H__
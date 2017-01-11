#ifndef __MODULEFONTS_H__
#define __MODULEFONTS_H__

#include <string>
#include <list>
#include "ModuleTextures.h"
#include "Module.h"
#include "Animation.h"

struct TextFont
{
	Frame origin;
	int id;
	SDL_Texture* graphics;
	std::string map;

	TextFont(Frame origin, int id, SDL_Texture* graphics, std::string map):
		origin(origin), id(id), graphics(graphics), map(map)
	{}

	~TextFont()
	{
		App->textures->Unload(graphics);
	}

};

struct NumericFont
{
	Frame origin;
	int id;
	SDL_Texture* graphics;

	NumericFont(Frame origin, int id, SDL_Texture* graphics) :
		origin(origin), id(id), graphics(graphics)
	{}

	~NumericFont()
	{
		App->textures->Unload(graphics);
	}

};

class ModuleFonts :	public Module
{
private:
	std::list<TextFont*> textFonts;
	std::list<NumericFont*> nFonts;
	int sigId = 0;
public:
	ModuleFonts(CONFIG_OBJECT config);
	~ModuleFonts();

	int LoadTFont(Frame origin, const char* texture, std::string map);
	int LoadNFont(Frame origin, const char* texture);

	void BlitText(int x, int y, int f, const char * text);

	void BlitNumber(int x, int y, int f, int number, unsigned int digits);

};

#endif //__MODULEFONTS_H__



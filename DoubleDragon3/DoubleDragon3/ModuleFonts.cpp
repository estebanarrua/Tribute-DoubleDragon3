#include "Globals.h"
#include "Application.h"
#include "ModuleFonts.h"
#include "ModuleRender.h"
#include <vector>

using namespace std;

ModuleFonts::ModuleFonts(CONFIG_OBJECT config):Module(config)
{
}

ModuleFonts::~ModuleFonts()
{
}

int ModuleFonts::LoadTFont(Frame origin, const char * texture, std::string map)
{
	SDL_Texture* graphics = App->textures->Load(texture);
	TextFont* f = new TextFont(origin, sigId, graphics, map);
	textFonts.push_back(f);
	++sigId;
	return f->id;
}

int ModuleFonts::LoadNFont(Frame origin, const char * texture)
{
	SDL_Texture* graphics = App->textures->Load(texture);
	NumericFont* f = new NumericFont(origin, sigId, graphics);
	nFonts.push_back(f);
	++sigId;
	return f->id;
}

void ModuleFonts :: BlitText(int x, int y, int f, const char* text) {
	TextFont* font = nullptr;
	for (list<TextFont*>::iterator it = textFonts.begin(); it != textFonts.cend() && font == nullptr; ++it)
		if ((*it)->id == f)
			font = (*it);
	while (*text != '\0') {
		bool found = false;
		unsigned int i = 0;
		while (i < font->map.length() && !found) {
			if (*text == font->map[i]) {
				found = true;
			}
			else {
				++i;
			}
		}
			
		Frame faux = font->origin;
		faux.rect.x += (font->origin.rect.w * i);
		App->renderer->BlitWithOutCamera(font->graphics, x , y, &(faux));
		x += font->origin.rect.w;
		++text;
	}
}

void ModuleFonts::BlitNumber(int x, int y, int f, int number, unsigned int digits) {
	NumericFont* font = nullptr;
	for (list<NumericFont*>::iterator it = nFonts.begin(); it != nFonts.cend() && font == nullptr; ++it)
		if ((*it)->id == f)
			font = (*it);
	vector<int> vect;
	while (number / 10 != 0) {
		vect.push_back(number % 10);
		number = number / 10;
	}
	vect.push_back(number % 10);
	while (vect.size() < digits) {
		vect.push_back(0);
	}

	for (vector<int>::const_reverse_iterator it = vect.crbegin(); it != vect.crend(); ++it) {
		Frame faux = font->origin;
		faux.rect.x += (font->origin.rect.w * (*it));
		App->renderer->BlitWithOutCamera(font->graphics, x, y, &(faux));
		x += font->origin.rect.w;
	}
}
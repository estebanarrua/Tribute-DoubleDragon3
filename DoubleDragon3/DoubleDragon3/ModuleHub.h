#ifndef __MODULEHUB_H__
#define __MODULEHUB_H__

#include "Module.h"

class ModuleHub : public Module
{
private:
	int fontText;
	int fontLife[2];

public:
	ModuleHub(CONFIG_OBJECT config, bool start_enabled = true);
	~ModuleHub();

	bool Start();
	update_status Update();
	bool CleanUp();


};

#endif // __MODULEHUB_H__


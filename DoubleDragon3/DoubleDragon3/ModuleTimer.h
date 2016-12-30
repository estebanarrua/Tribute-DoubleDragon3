#ifndef __MODULETIMER_H__
#define __MODULETIMER_H__

#include "Module.h"

class ModuleTimer : public Module
{

private:
	unsigned int firtTime = 0;
	unsigned int lastTime = 0;

public:
	ModuleTimer(CONFIG_OBJECT config);
	~ModuleTimer();

	bool Start();
	update_status Update();
	bool CleanUp();

};

#endif //MODULETIMER
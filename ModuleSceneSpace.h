#ifndef __MODULESCENESPACE_H__
#define __MODULESCENESPACE_H__

#include "Module.h"

#define MAX_ICEBERGS 10

struct SDL_Texture;
struct SDL_Surface;

class ModuleSceneSpace : public Module
{
public:
	ModuleSceneSpace();
	~ModuleSceneSpace();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture* sprites = nullptr;
	SDL_Texture* background = nullptr;
	SDL_Texture* background0 = nullptr;
	SDL_Texture* hud = nullptr;
	SDL_Texture* stars = nullptr;

	int scroll0 = 0;
	int scroll = 0;

	int iceberg1[MAX_ICEBERGS];
};

#endif // __MODULESCENESPACE_H__
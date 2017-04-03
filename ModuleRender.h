#ifndef __ModuleRenderer_H__
#define __ModuleRenderer_H__

#include "Module.h"

struct SDL_Renderer;
struct SDL_Texture;

#define WATER_HEIGHT 38
#define WATER_TEX_HEIGHT 100

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	update_status PostUpdate();
	update_status Update();
	update_status PreUpdate();
	bool CleanUp();

	bool Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed = 1.0f, bool use_camera = true);
	bool DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera = true);
	void FullScreenEffects();

public:
	SDL_Renderer* renderer = nullptr;
	SDL_Rect camera;
	SDL_Texture* target = nullptr;
	SDL_Texture* water = nullptr;
};

#endif //__ModuleRenderer_H__
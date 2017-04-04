#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleSceneSpace.h"
#include "ModuleWindow.h"

#ifdef _WIN32
	#include "SDL/include/SDL.h"
#else
	#include "SDL.h"
#endif

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneSpace::ModuleSceneSpace()
{}

ModuleSceneSpace::~ModuleSceneSpace()
{}

// Load assets
bool ModuleSceneSpace::Start()
{
	LOG("Loading space scene");
	
	background0 = App->textures->Load("astro/background0.png");
	background = App->textures->Load("astro/background.png");
	hud = App->textures->Load("rtype/hud.png");
	water = SDL_CreateRGBSurface(0, 600, 40, SDL_GetWindowPixelFormat(App->window->window), 0, 0, 0, 0);
	twater = SDL_CreateTexture(App->render->renderer, SDL_GetWindowPixelFormat(App->window->window), SDL_TEXTUREACCESS_STREAMING, 600, 24);

	App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();
	App->enemies->Enable();

	/*
	App->audio->PlayMusic("rtype/stage1.ogg", 1.0f);
	
	// Colliders ---
	App->collision->AddCollider({0, 224, 3930, 16}, COLLIDER_WALL);
	App->collision->AddCollider({1375, 0, 111, 96}, COLLIDER_WALL);
	App->collision->AddCollider({1375, 145, 111, 96}, COLLIDER_WALL);

	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 600, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 625, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 640, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 665, 80);
	
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 735, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 750, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 775, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 790, 120);

	App->enemies->AddEnemy(ENEMY_TYPES::BROWNSHIP, 830, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNSHIP, 850, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNSHIP, 870, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNSHIP, 890, 100);

	App->enemies->AddEnemy(ENEMY_TYPES::MECH, 900, 195);
	*/
	return true;
}

// UnLoad assets
bool ModuleSceneSpace::CleanUp()
{
	LOG("Unloading space scene");

 	App->textures->Unload(background);
	App->textures->Unload(background0);
	SDL_DestroyTexture(twater);
	SDL_FreeSurface(water);

	App->enemies->Disable();
	App->collision->Disable();
	App->particles->Disable();
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneSpace::Update()
{
	// Move camera forward -----------------------------
	App->render->camera.x += 1 * SCREEN_SIZE;

	int s = 600;
	int s0 = 600 * 0.5f;
	int s1 = 600 * 2.0f;

	if (App->render->camera.x % s == 0)
		scroll += s;

	if (App->render->camera.x % s1 == 0)
		scroll0 += s;

	// Draw everything --------------------------------------
	App->render->Blit(background0, scroll0, 0, NULL, 0.5f);
	App->render->Blit(background0, scroll0 + 600, 0, NULL, 0.5f);

	App->render->Blit(background, scroll, 0, NULL);
	App->render->Blit(background, scroll + s, 0, NULL);

	//App->render->Blit(hud, 0, 240, NULL, 0.0f, false);

	// Water reflection -------------------------------------
	


	SDL_Rect screen_chunk = { 0, 600-189, 600, 40 };
	//SDL_BlitSurface(App->window->screen_surface, &screen_chunk, water, NULL);
	
	//twater = SDL_CreateTextureFromSurface(App->render->renderer, water);
	
	void* pixels = nullptr;
	int pitch = 0;
	SDL_LockTexture(twater, NULL, &pixels, &pitch);

	//if(SDL_MUSTLOCK(water))
		//SDL_LockSurface(water);
	Uint32 format;
	SDL_QueryTexture(twater, &format, NULL, NULL, NULL);
	int r = SDL_RenderReadPixels(App->render->renderer, &screen_chunk, format, pixels, pitch);
	if (r != 0)
	{
		LOG("Cannot read pixels: %s\n", SDL_GetError());
	}

	//SDL_Texture* t = SDL_CreateTextureFromSurface(App->render->renderer, water);

	//SDL_UpdateTexture(twater, NULL, pixels, pitch);
	
	//if (SDL_MUSTLOCK(water))
		//SDL_UnlockSurface(water);

	SDL_UnlockTexture(twater);
	

	//App->render->Blit(twater, 0, 0, NULL, 1.0f, false);

	//SDL_DestroyTexture(t);
	
	return UPDATE_CONTINUE;
}
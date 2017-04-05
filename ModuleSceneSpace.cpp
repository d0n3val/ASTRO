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

#ifdef WIN32
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

	App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();
	App->enemies->Enable();
	App->render->effect_water = true;

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

	App->enemies->Disable();
	App->collision->Disable();
	App->particles->Disable();
	App->player->Disable();

	App->render->effect_water = false;

	return true;
}

// Update: draw background
update_status ModuleSceneSpace::Update()
{
	// Move camera forward -----------------------------
	App->render->camera.x += 1 * SCREEN_SIZE;

	int s = 1920;
	int s0 = 1920 * 0.5f;
	int s1 = 1920 * 2.0f;

	if (App->render->camera.x % s == 0)
		scroll += s;

	if (App->render->camera.x % s1 == 0)
		scroll0 += s;

	// Draw everything --------------------------------------
	App->render->Blit(background0, scroll0, 0, NULL, 0.5f);
	App->render->Blit(background0, scroll0 + s, 0, NULL, 0.5f);

	App->render->Blit(background, scroll, 250, NULL);
	App->render->Blit(background, scroll + s, 250, NULL);

	//App->render->Blit(hud, 0, 240, NULL, 0.0f, false);

	return UPDATE_CONTINUE;
}
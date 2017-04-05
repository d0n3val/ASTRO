#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModulePlayer.h"

#include<stdio.h>

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	// idle animation (just the ship)
	idle.PushBack({7, 4, 321, 147});

	// move upwards
	up.PushBack({ 7, 327, 321, 147 });
	//up.PushBack({ 0,  0, 70, 21 });
	up.loop = false;
	up.speed = 0.1f;

	// Move down
	down.PushBack({ 7, 160, 321, 147 });
	//down.PushBack({ 0, 84, 70, 21 });
	down.loop = false;
	down.speed = 0.1f;

	// Move forward
	forward.PushBack({ 649, 4, 321, 147 });
	//forward.PushBack({ 0, 84, 70, 21 });
	forward.loop = false;
	forward.speed = 0.1f;

	// Move backwards
	backward.PushBack({ 329, 4, 321, 147 });
	//backward.PushBack({ 0, 84, 70, 21 });
	backward.loop = false;
	backward.speed = 0.1f;

	// thruster
	thruster.PushBack({ 652, 536, 87, 51 });
	//thruster.PushBack({ 0, 84, 70, 21 });
	thruster.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("astro/player_sprites.png");

	destroyed = false;
	position.x = 150;
	position.y = 120;
	score = 0;

	col = App->collision->AddCollider({position.x, position.y, 32, 16}, COLLIDER_PLAYER, this);
	font_score = App->fonts->Load("fonts/rtype_font3.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 2);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	App->collision->EraseCollider(col);
	App->fonts->UnLoad(font_score);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	bool i_bwd = App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT || App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_DOWN;
	bool i_fwd = App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT || App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_DOWN;
	bool i_up = App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT || App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_DOWN;
	bool i_down = App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT || App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_DOWN;
	bool i_shoot = App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT || App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN;

	position.x += 1; // Automatic movement

	int speed = 6;

	if(i_bwd)
	{
		if(position.x - App->render->camera.x > 0)
			position.x -= speed;

		if (current_animation != &backward)
		{
			backward.Reset();
			current_animation = &backward;
		}
	}

	if(i_fwd)
	{
		if (position.x - App->render->camera.x < SCREEN_WIDTH - 70)
		{
			position.x += speed;
			//App->render->DrawQuad({ 0, position.y+19, position.x+40, 2}, 223, 90, 182, 200);
		}

		if (current_animation != &forward)
		{
			forward.Reset();
			current_animation = &forward;
		}
	}

	if (i_down)
	{
		if (position.y - App->render->camera.y < SCREEN_HEIGHT - 160 - WATER_HEIGHT)
			position.y += speed;

		if (current_animation != &down)
		{
			down.Reset();
			current_animation = &down;
		}
	}

	if (i_up)
	{
		if (position.y - App->render->camera.y > 0)
			position.y -= speed;

		if (current_animation != &up)
		{
			up.Reset();
			current_animation = &up;
		}
	}
	
	if(i_shoot)
	{
		//App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, COLLIDER_PLAYER_SHOT);
		//score+=13;
		//App->render->DrawQuad({position.x + 68, position.y + 5, SCREEN_WIDTH, 3 }, 208, 130, 214, 200);
	}

	if(!i_up && !i_down && !i_fwd && !i_bwd && current_animation != &idle)
		current_animation = &idle;

	col->SetPos(position.x, position.y);

	// Draw everything --------------------------------------
	if(destroyed == false)
	{
		if(i_fwd)
			App->render->Blit(graphics, position.x-84, position.y, &(thruster.GetCurrentFrame()));

		App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
	}

	// Draw UI (score) --------------------------------------
	//sprintf_s(score_text, 10, "%7d", score);
	//App->fonts->Blit(58, 248, font_score, score_text);

	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if(c1 == col && destroyed == false && App->fade->IsFading() == false)
	{
		App->fade->FadeToBlack((Module*)App->scene_space, (Module*)App->scene_intro);

		App->particles->AddParticle(App->particles->explosion, position.x, position.y, COLLIDER_NONE, 150);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, COLLIDER_NONE, 220);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, COLLIDER_NONE, 670);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, COLLIDER_NONE, 480);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, COLLIDER_NONE, 350);

		destroyed = true;
	}
}
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
	int w = 300;
	int h = 142;

	// idle animation (just the ship)
	idle.PushBack({113, 51, w, h});

	// move upwards
	up.PushBack({ 113, 707, w, h });
	up.PushBack({ 113, 502, w, h });
	up.loop = false;
	up.speed = 0.1f;

	// Move down
	down.PushBack({ 689, 502, w, h });
	down.PushBack({ 689, 707, w, h });
	down.loop = false;
	down.speed = 0.1f;

	// Move forward
	forward.PushBack({ 113, 51, w, h });
	//forward.PushBack({ 0, 84, w, h });
	forward.loop = false;
	forward.speed = 0.1f;

	// Move backwards
	backward.PushBack({ 120, 888, w, h });
	//backward.PushBack({ 0, 84, w, h });
	backward.loop = false;
	backward.speed = 0.1f;

	// thruster
	thruster.PushBack({ 652, 536, 87, 51 });
	//thruster.PushBack({ 0, 84, 70, 21 });
	thruster.speed = 0.1f;

	// banking right to left
	banking.PushBack({99, 274, w, h});
	banking.PushBack({488, 270, w, h});
	banking.PushBack({809, 265, w, h});
	banking.PushBack({1077, 265, w, h});
	banking.PushBack({1474, 265, w, h});
	banking.loop = false;
	banking.speed = 0.2f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("astro/spritesheet_pixelart.png");

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

	position.x += 3; // Automatic movement

	int speed = 6;

	if(!i_up && !i_down && !i_fwd && !i_bwd && current_animation != &idle)
		current_animation = &idle;

	if(i_bwd)
	{
		if(position.x - App->render->camera.x > 0)
			position.x -= speed;

		if (facing_right == true && current_animation != &banking)
		{
			banking.Reset();
			current_animation = &banking;
			facing_right = false;
		}
		else if(banking.Finished())
			current_animation = &idle;
	}

	if(i_fwd)
	{
		if (position.x - App->render->camera.x < SCREEN_WIDTH - 70)
		{
			position.x += speed;
			//App->render->DrawQuad({ 0, position.y+19, position.x+40, 2}, 223, 90, 182, 200);
		}

		if (facing_right == false && current_animation != &banking)
		{
			banking.Reset();
			current_animation = &banking;
			facing_right = true;
		}
		else if(banking.Finished())
			current_animation = &idle;
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


	col->SetPos(position.x, position.y);

	// Draw everything --------------------------------------
	if(destroyed == false)
	{
		//if(i_fwd)
			//App->render->Blit(graphics, position.x-84, position.y, &(thruster.GetCurrentFrame()));

		if(facing_right)
			App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
		else
			App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()), 1.0f, true, true);
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
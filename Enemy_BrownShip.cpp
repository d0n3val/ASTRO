#include "Application.h"
#include "Enemy_BrownShip.h"
#include "ModuleCollision.h"
#include "Globals.h"

Enemy_BrownShip::Enemy_BrownShip(int x, int y) : Enemy(x, y)
{
	fly.PushBack({5,72,21,22});
	fly.speed = 0.2f;
	animation = &fly;

	path.PushBack({-1.0f, -0.5f}, 100);
	path.PushBack({-1.0f, 0.5f}, 80);
	path.PushBack({-1.0f, 1.0f}, 80);

	collider = App->collision->AddCollider({0, 0, 24, 24}, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
}

void Enemy_BrownShip::Move()
{
	position = original_pos + path.GetCurrentSpeed();
}

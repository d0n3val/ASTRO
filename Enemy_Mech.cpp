#include "Application.h"
#include "Enemy_Mech.h"
#include "ModuleCollision.h"
#include "Globals.h"

Enemy_Mech::Enemy_Mech(int x, int y) : Enemy(x, y)
{
	front.PushBack({5, 108, 31, 29});
	front.PushBack({4, 141, 31, 29});
	front.PushBack({38, 108, 31, 29});
	front.speed = 0.1f;

	back.PushBack({170, 108, 31, 29});
	back.PushBack({170, 141, 31, 29});
	back.PushBack({137, 108, 31, 29});
	back.speed = 0.1f;

	path.PushBack({-0.3f, 0.0f}, 150, &front);
	path.PushBack({1.2f, 0.0f}, 150, &back);

	collider = App->collision->AddCollider({0, 0, 24, 24}, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
}

void Enemy_Mech::Move()
{
	position = original_pos + path.GetCurrentSpeed(&animation);
}

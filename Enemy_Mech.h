#ifndef __ENEMY_MECH_H__
#define __ENEMY_MECH_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Mech : public Enemy
{
private:
	Path path;
	iPoint original_pos;
	Animation front,back;

public:

	Enemy_Mech(int x, int y);

	void Move();
};

#endif // __ENEMY_MECH_H__
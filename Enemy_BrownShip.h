#ifndef __ENEMY_BROWNSHIP_H__
#define __ENEMY_BROWNSHIP_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_BrownShip : public Enemy
{
private:
	Path path;
	iPoint original_pos;
	Animation fly;

public:

	Enemy_BrownShip(int x, int y);

	void Move();
};

#endif // __ENEMY_BROWNSHIP_H__
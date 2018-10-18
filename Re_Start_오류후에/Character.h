#pragma once
#include "Object_Handling.h"
#include "sprite.h"

class Character : public Object_Handling
{
public:

	int Face_Direction;
	int walk_step;
	sprite* sprite_ptr;


public:
	Character()
	{
		Face_Direction = 1;
		walk_step = 0;
		sprite_ptr = new sprite;
	}
	virtual ~Character() {}
};


#pragma once
#include "Object_Handling.h"

class Character : public Object_Handling
{
public:

	int Face_Direction;

public:
	Character()
	{
		Face_Direction = 1;
	}
	virtual ~Character() {}
};


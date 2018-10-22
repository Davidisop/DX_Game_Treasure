#pragma once
#include "Object_Handling.h"

class Gun_Bullet : public Object_Handling
{
public:
	bool frame()
	{

	}
public:

	bool Bullet_Go;

public:
	Gun_Bullet() { Bullet_Go = false; }
	virtual ~Gun_Bullet() {}
};




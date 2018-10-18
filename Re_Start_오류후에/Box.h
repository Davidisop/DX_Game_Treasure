#pragma once
#include "Object_Handling.h"

class Box : public Object_Handling
{

public:
	int Linger_Stage;

public:
	Box()
	{		Linger_Stage = 0;	}
	~Box() {}
};


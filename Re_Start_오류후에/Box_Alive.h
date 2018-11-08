#pragma once
#include "Object_Handling.h"

enum { Detection_0 = 0, Detection_1 = 1 };

class Box_Alive : public Object_Handling
{
public:

	float detection_time;
	bool  ghost_shoot_flag;
	int   state;
	bool  Bullet_G1_Bullet_Go;
	bool  Bullet_G2_Bullet_Go;
	bool  Bullet_G3_Bullet_Go;
	bool  Bullet_G4_Bullet_Go;

public:

	void attack()
	{
		if (state == Detection_1)
		{
			state = Detection_0;
			
		
				static int count_K = 1;
				if (count_K == 1) { Bullet_G1_Bullet_Go = true; }  // 씬에서 이거와 연동되서, 고스트 나간다.
				if (count_K == 2) { Bullet_G2_Bullet_Go = true; }
				if (count_K == 3) { Bullet_G3_Bullet_Go = true; }
				if (count_K == 4) { Bullet_G4_Bullet_Go = true; }
				count_K++;	
		}
	}

	void Detction_FULL()
	{
		if (state == Detection_0)
		{
			state = Detection_1;
			attack();
		}
	}

	void frame()
	{

		detection_time += g_fSecPerFrame;

		if (detection_time >= 1.5f)
		{
			detection_time = 0;
			Detction_FULL();
			
		}

	}

	Box_Alive() : state (Detection_0), detection_time(0), ghost_shoot_flag(false), Bullet_G1_Bullet_Go(false), Bullet_G2_Bullet_Go(false), Bullet_G3_Bullet_Go(false), Bullet_G4_Bullet_Go(false)
	{
		/*state = Detection_0;
		detection_time = 0;
		ghost_shoot_flag = false;
		Bullet_G1_Bullet_Go = false;
		Bullet_G2_Bullet_Go = false;
		Bullet_G3_Bullet_Go = false;
		Bullet_G4_Bullet_Go = false;*/
	}
	virtual ~Box_Alive() {}

};


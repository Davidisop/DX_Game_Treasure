#pragma once
#include "Character.h"


enum { Detection__0 = 0, Detection__1_SWORD = 1, Detection__1_GUN = 2 };

class BOSS_NPC : public Character
{
public:
	void right_walk();
	void left_walk();
	void shot();
	void sword();

public:
	bool  Bullet_Go;
	int   Gun_step;
	bool  m_Collision_down_side;
	int	  sword_step;
	int   slide_step;

public:
	int   state;
	float detection_time;

	int   shoot_flag;
	bool  Bullet_B1_Bullet_Go;
	bool  Bullet_B2_Bullet_Go;
	bool  Bullet_B3_Bullet_Go;
	bool  Bullet_B4_Bullet_Go;

	bool sword_flag;
	bool sword_left_right_go;

	float distance_direction_between_hero_boss;


public:
	BOSS_NPC() : Gun_step(0), m_Collision_down_side(0), sword_step(0), slide_step(0), detection_time(0), shoot_flag(0), Bullet_B1_Bullet_Go(0), Bullet_B2_Bullet_Go(0), Bullet_B3_Bullet_Go(0), Bullet_B4_Bullet_Go (0), sword_flag (0), sword_left_right_go(9), distance_direction_between_hero_boss(0)
	{
	/*	Gun_step = 0;
		m_Collision_down_side = false;
		sword_step = 0;
		slide_step = 0;
		detection_time = 0;

		shoot_flag = false;
		Bullet_B1_Bullet_Go = false;
		Bullet_B2_Bullet_Go = false;
		Bullet_B3_Bullet_Go = false;
		Bullet_B4_Bullet_Go = false;

		sword_flag = false;
		sword_left_right_go = false;
		distance_direction_between_hero_boss = 0;*/

	}
	virtual ~BOSS_NPC() {}

public:


	void ATTACK_SHOT()   // �̰� ���� ������.

	{

			
			if (shoot_flag == 1) { Bullet_B1_Bullet_Go = true; shot(); }  // ������ �̰ſ� �����Ǽ�, ��Ʈ ������.
			else if (shoot_flag == 2) { Bullet_B2_Bullet_Go = true; shot(); }
			else if (shoot_flag == 3) { Bullet_B3_Bullet_Go = true; shot(); }
			else if (shoot_flag == 4) { Bullet_B4_Bullet_Go = true; shot(); }
			

			static float fAddTime = 0.0f;
			fAddTime += g_fSecPerFrame;

			if (Gun_step == 1 && fAddTime > 0.3f)
			{
				Gun_step = 2; fAddTime = 0;
			}

			else if (Gun_step == 2 && fAddTime > 0.3f)
			{
				Gun_step = 3; fAddTime = 0;
			}

			else if (Gun_step == 3 && fAddTime > 0.3f)
			{
				Gun_step = 4; fAddTime = 0;
			}


	}



	void ATTACK_SWORD()  // �̰� ���� ������.
	{	
			 	
			static float fAddTime = 0.0f;
			fAddTime += g_fSecPerFrame;

			if (sword_step == 1 && fAddTime > 0.3f)
			{
				sword_step = 2; fAddTime = 0;
			}

			else if (sword_step == 2 && fAddTime > 0.3f)
			{
				sword_step = 3; fAddTime = 0;
			}

			else if (sword_step == 3 && fAddTime > 0.3f)
			{
				sword_step = 4; fAddTime = 0;
			}

			else if (sword_step == 4 && fAddTime > 0.3f)
			{
				sword_step = 5; fAddTime = 0;
			}

			else if (sword_step == 5 && fAddTime > 0.3f)
			{
				sword_step = 6; fAddTime = 0;
			}

			else if (sword_step == 6 && fAddTime > 0.3f)
			{
				sword_step = 7; fAddTime = 0;
			}


		
	}

	void Detction_FULL()
	{
		if (state == Detection__0)
		{
			if (abs(distance_direction_between_hero_boss) < 150)
			{
				state = Detection__1_SWORD;
				sword_step = 1;
				ATTACK_SWORD();
			}

			else 
			{
				state = Detection__1_GUN;
				shoot_flag++;
				Gun_step = 1;
				ATTACK_SHOT();
			}
		}
	}


	void walk_T()  // �̰� ���� �̻���. ���׶�̿� ȭ��ǥ�� �ް�����?
	{
		if (distance_direction_between_hero_boss>0)
		{
			Face_Direction = 1;
			left_walk();
		}

		else if (distance_direction_between_hero_boss<0)
		{
			Face_Direction = 2;
			right_walk();
		}
	}


	void basic_frame()
	{
			
			walk_T();

			detection_time += g_fSecPerFrame;
		
			if (detection_time >= 3.0f)
			{
				detection_time = 0;
				Detction_FULL();
			}
		
	}





};


void BOSS_NPC::left_walk()
{
	static float fAddTime = 0.0f;
	fAddTime += g_fSecPerFrame;
	
	if (fAddTime >= 0.1f)
		{
			switch (walk_step)
			{
				case 0:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 19, 0, 702, 1843);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");
					++walk_step;
				}break;
				case 1:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 19, 1, 702, 1843);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");
					++walk_step;
				}break;

				case 2:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 19, 2, 702, 1843);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");
					++walk_step;
				}break;
				case 3:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 19, 3, 702, 1843);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");
					++walk_step;
				}break;
				case 4:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 19, 4, 702, 1843);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");
					++walk_step;
				}break;

				case 5:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 19, 5, 702, 1843);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");
					++walk_step;
				}break;
				case 6:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 19, 6, 702, 1843);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");
					++walk_step;
				}break;
				case 7:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 19, 7, 702, 1843);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");
					walk_step = 0;
				}break;

			}
		
	}

	if (fAddTime >= 0.1f)
	{
		fAddTime = 0;
	}

}


void BOSS_NPC::right_walk()
{
	static float fAddTime = 0.0f;
	fAddTime += g_fSecPerFrame;
	
	if (fAddTime >= 0.1f)
	{

			switch (walk_step)
			{
				case 0:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 18, 0, 702, 1843);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");
					++walk_step;
				}break;
				case 1:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 18, 1, 702, 1843);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");
					++walk_step;
				}break;

				case 2:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 18, 2, 702, 1843);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");
					++walk_step;
				}break;
				case 3:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 18, 3, 702, 1843);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");
					++walk_step;
				}break;
				case 4:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 18, 4, 702, 1843);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");
					++walk_step;
				}break;

				case 5:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 18, 5, 702, 1843);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");
					++walk_step;
				}break;
				case 6:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 18, 6, 702, 1843);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");
					++walk_step;
				}break;
				case 7:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 18, 7, 702, 1843);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");
					walk_step = 0;
				}break;

			}
	}
	
	if (fAddTime >= 0.1f)
	{
		fAddTime = 0;
	}
}



void BOSS_NPC::shot()
{

	if (Face_Direction == 2)

	{

		switch (Gun_step)
		{
			case 1:
			{
				in_Texture_SetData_sprite_factors(sprite_ptr, 20, 0, 702, 1843);
				Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");


				++Gun_step;
			}break;

			case 2:
			{
				in_Texture_SetData_sprite_factors(sprite_ptr, 20, 1, 702, 1843);
				Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");


				++Gun_step;

			}break;

			case 3:
			{
				in_Texture_SetData_sprite_factors(sprite_ptr, 20, 2, 702, 1843);
				Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");
				++Gun_step;
			}break;

			case 4:
			{
				in_Texture_SetData_sprite_factors(sprite_ptr, 20, 3, 702, 1843);
				Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");
				Gun_step = 0; state = Detection__0;
			}break;


		}
	}

	else 
	{
		switch (Gun_step)
		{
			case 1:
			{
				in_Texture_SetData_sprite_factors(sprite_ptr, 21, 0, 702, 1843);
				Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");


				++Gun_step;
			}break;

			case 2:
			{
				in_Texture_SetData_sprite_factors(sprite_ptr, 21, 1, 702, 1843);
				Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");

				++Gun_step;
			}break;

			case 3:
			{
				in_Texture_SetData_sprite_factors(sprite_ptr, 21, 2, 702, 1843);
				Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");

				++Gun_step;
			}break;
			case 4:
			{
				in_Texture_SetData_sprite_factors(sprite_ptr, 21, 3, 702, 1843);
				Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");
				Gun_step = 0; state = Detection__0;
			}break; 

		}

	}

}




void BOSS_NPC::sword()
{


	if (Face_Direction == 2)

	{

		switch (sword_step)
		{
			case 1:
			{
				in_Texture_SetData_sprite_factors(sprite_ptr, 16, 0, 702, 1843);
				Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");


				++sword_step;
			}break;

			case 2:
			{
				in_Texture_SetData_sprite_factors(sprite_ptr, 16, 1, 702, 1843);
				Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");


				++sword_step;

			}break;

			case 3:
			{
				in_Texture_SetData_sprite_factors(sprite_ptr, 16, 2, 702, 1843);
				Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");


				++sword_step;
			}break;


			case 4:
			{
				in_Texture_SetData_sprite_factors(sprite_ptr, 16, 3, 702, 1843);
				Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");


				++sword_step;

			}break;

			case 5:
			{
				in_Texture_SetData_sprite_factors(sprite_ptr, 16, 4, 702, 1843);
				Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");
				++sword_step;
			}break;

			case 6:
			{
				in_Texture_SetData_sprite_factors(sprite_ptr, 16, 5, 702, 1843);
				Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");


				++sword_step;
			}break;

			case 7:
			{
				in_Texture_SetData_sprite_factors(sprite_ptr, 16, 6, 702, 1843);
				Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");


				++sword_step;
			}break;

			case 8:
			{
				in_Texture_SetData_sprite_factors(sprite_ptr, 16, 7, 702, 1843);
				Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");


				sword_step = 0; state = Detection__0;
			}break;


		}
	}

	else 
	{


		switch (sword_step)
		{

			case 1:
			{
				in_Texture_SetData_sprite_factors(sprite_ptr, 17, 0, 702, 1843);
				Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");

				++sword_step;
			}break;

			case 2:
			{
				in_Texture_SetData_sprite_factors(sprite_ptr, 17, 1, 702, 1843);
				Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");

				++sword_step;

			}break;

			case 3:
			{
				in_Texture_SetData_sprite_factors(sprite_ptr, 17, 2, 702, 1843);
				Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");


				++sword_step;
			}break;


			case 4:
			{
				in_Texture_SetData_sprite_factors(sprite_ptr, 17, 3, 702, 1843);
				Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");


				++sword_step;

			}break;

			case 5:
			{
				in_Texture_SetData_sprite_factors(sprite_ptr, 17, 4, 702, 1843);
				Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");


				++sword_step;
			}break;

			case 6:
			{
				in_Texture_SetData_sprite_factors(sprite_ptr, 17, 5, 702, 1843);
				Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");


				++sword_step;
			}break;

			case 7:
			{
				in_Texture_SetData_sprite_factors(sprite_ptr, 17, 6, 702, 1843);
				Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");


				++sword_step;
			}break;

			case 8:
			{
				in_Texture_SetData_sprite_factors(sprite_ptr, 17, 7, 702, 1843);
				Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");

				sword_step = 0; state = Detection__0;
			}break;

		}

	}

}
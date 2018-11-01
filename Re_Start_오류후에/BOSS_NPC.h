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

	bool  shoot_flag;
	bool  Bullet_B1_Bullet_Go;
	bool  Bullet_B2_Bullet_Go;
	bool  Bullet_B3_Bullet_Go;
	bool  Bullet_B4_Bullet_Go;

	bool sword_flag;
	bool sword_left_right_go;

	float distance_direction_between_hero_boss;

public:

	void ATTACK_SHOT()   // 이걸 씬에 빼놔야.
	{		
		if (state == Detection__1_GUN)
		{
			shoot_flag = true;   	
			if (shoot_flag == true)
			{
				static int count_K = 1;
				if (count_K == 1) { Bullet_B1_Bullet_Go = true; Gun_step = 1; shot(); }  // 씬에서 이거와 연동되서, 고스트 나간다.
				if (count_K == 2) { Bullet_B2_Bullet_Go = true; Gun_step = 1; shot(); }
				if (count_K == 3) { Bullet_B3_Bullet_Go = true; Gun_step = 1; shot(); }
				if (count_K == 4) { Bullet_B4_Bullet_Go = true; Gun_step = 1; shot(); }
				count_K++;
			}
			shoot_flag = false;
			state = Detection__0;

		/*	detection_time += g_fSecPerFrame;
			if (detection_time >1.0F)
			{	
				
				detection_time = 0.0f;
			}*/

		}
	}

	void ATTACK_SWORD()  // 이걸 씬에 빼놔야.
	{	
		if (state == Detection__1_SWORD)
		{
			 	
				static DWORD dwEventTime = 300; // 이벤트 발생 간격 을 얻습니다. < GetTickCount로는 1/1000초 단위로 할수 있기 때문에 2초입니다.
				static DWORD dw_NoUpdate_Time = GetTickCount();// 기준 시간을 얻습니다.
				DWORD dw_AutoUpdate_CurTime = GetTickCount();	//현재 시간을 얻습니다.


				if (sword_step == 1 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // 설정한 시간이 지나가면 if문을 실행합니다.
				{
					sword_step = 2;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
				}

				if (sword_step == 2 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // 설정한 시간이 지나가면 if문을 실행합니다.
				{
					sword_step = 3;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
				}

				if (sword_step == 3 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // 설정한 시간이 지나가면 if문을 실행합니다.
				{
					sword_step = 4;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
				}

				if (sword_step == 4 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // 설정한 시간이 지나가면 if문을 실행합니다.
				{
					sword_step = 5;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
				}

				if (sword_step == 5 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // 설정한 시간이 지나가면 if문을 실행합니다.
				{
					sword_step = 6;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
				}

				if (sword_step == 6 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // 설정한 시간이 지나가면 if문을 실행합니다.
				{
					sword_step = 7;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
				}	
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

			if (abs(distance_direction_between_hero_boss) >= 150)
			{
				state = Detection__1_GUN;
				ATTACK_SHOT();
			}
		}
	}


	void walk_T()  // 이게 뭔가 이상해. 동그라미와 화살표를 햇갈린듯?
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
			
		if(state== Detection__0)
		{
			walk_T();

			detection_time += g_fSecPerFrame;
		
			if (detection_time >= 3.0f)
			{
				detection_time = 0;
				Detction_FULL();
			}
		}
	}





public:
	BOSS_NPC()
	{
		Gun_step = 0;
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
		distance_direction_between_hero_boss = 0;

	}
	virtual ~BOSS_NPC() {}
};


void BOSS_NPC::left_walk()
{
	static float fAddTime = 0.0f;
	fAddTime += g_fSecPerFrame;
	{
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
	}

	if (fAddTime >= 0.1f)
	{
		fAddTime -= 0.1f;
	}

}


void BOSS_NPC::right_walk()
{
	static float fAddTime = 0.0f;
	fAddTime += g_fSecPerFrame;
	{
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
	}
	if (fAddTime >= 0.1f)
	{
		fAddTime -= 0.1f;
	}
}



void BOSS_NPC::shot()
{
	static DWORD dwEventTime = 300; // 이벤트 발생 간격 을 얻습니다. < GetTickCount로는 1/1000초 단위로 할수 있기 때문에 2초입니다.
	static DWORD dw_NoUpdate_Time = GetTickCount();// 기준 시간을 얻습니다.
	DWORD dw_AutoUpdate_CurTime = GetTickCount();	//현재 시간을 얻습니다.


	if (Gun_step == 1 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // 설정한 시간이 지나가면 if문을 실행합니다.
	{
		Gun_step = 2;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
	}

	if (Gun_step == 2 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // 설정한 시간이 지나가면 if문을 실행합니다.
	{
		Gun_step = 3;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
	}


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
				Gun_step = 0;
			}break;


		}
	}

	else if (Face_Direction == 1)
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
				Gun_step = 0;
			}break;

		}

	}

}




void BOSS_NPC::sword()
{
//
//	static DWORD dwEventTime = 300; // 이벤트 발생 간격 을 얻습니다. < GetTickCount로는 1/1000초 단위로 할수 있기 때문에 2초입니다.
//	static DWORD dw_NoUpdate_Time = GetTickCount();// 기준 시간을 얻습니다.
//	DWORD dw_AutoUpdate_CurTime = GetTickCount();	//현재 시간을 얻습니다.
//
//
//	if (sword_step == 1 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // 설정한 시간이 지나가면 if문을 실행합니다.
//	{
//		sword_step = 2;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
//	}
//
//	if (sword_step == 2 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // 설정한 시간이 지나가면 if문을 실행합니다.
//	{
//		sword_step = 3;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
//	}
//
//	if (sword_step == 3 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // 설정한 시간이 지나가면 if문을 실행합니다.
//	{
//		sword_step = 4;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
//	}
//
//	if (sword_step == 4 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // 설정한 시간이 지나가면 if문을 실행합니다.
//	{
//		sword_step = 5;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
//	}
//
//	if (sword_step == 5 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // 설정한 시간이 지나가면 if문을 실행합니다.
//	{
//		sword_step = 6;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
//	}
//
//	if (sword_step == 6 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // 설정한 시간이 지나가면 if문을 실행합니다.
//	{
//		sword_step = 7;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
//	}



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

	else if (Face_Direction == 1)
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
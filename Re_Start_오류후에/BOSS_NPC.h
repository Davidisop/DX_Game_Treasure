#pragma once
#include "Character.h"


enum { Detection_0 = 0, Detection_1_SWORD = 1, Detection_1_GUN = 2 };

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


public:

	void ATTACK_SHOT()   // �̰� ���� ������.
	{		
		if (state == Detection_1_GUN)
		{
			shoot_flag = true;   	
			if (shoot_flag == true)
			{
				static int count_K = 1;
				if (count_K == 1) { Bullet_B1_Bullet_Go = true; }  // ������ �̰ſ� �����Ǽ�, ��Ʈ ������.
				if (count_K == 2) { Bullet_B2_Bullet_Go = true; }
				if (count_K == 3) { Bullet_B3_Bullet_Go = true; }
				if (count_K == 4) { Bullet_B4_Bullet_Go = true; }
				count_K++;
			}
			shoot_flag = false;


			detection_time += g_fSecPerFrame;
			if (detection_time >1.0F)
			{	
				state = Detection_0;
				detection_time = 0.0f;
			}

		}
	}

	void ATTACK_SWORD()  // �̰� ���� ������.
	{	
		if (state == Detection_1_SWORD)
		{
			 	
			sword_flag = true;

			if (sword_flag == true)
			{
				sword_left_right_go = true;
			}
			sword_left_right_go = false;
			sword_flag = false;
			
			
			detection_time += g_fSecPerFrame;

			if (detection_time > 1.0F)
			{
				state = Detection_0;
				detection_time = 0.0f;
			}
		}
	}

	void Detction_FULL()
	{
		if (state == Detection_0)
		{
			if (�� ������ �Ÿ�, ���� �÷��׿��� ���밪< 10)
			{
				state = Detection_1_SWORD;
				ATTACK_SWORD();
			}

			if (�� ������ �Ÿ�, ���� �÷��׿��� ���밪 > 10)
			{
				state = Detection_1_GUN;
				ATTACK_SHOT();
			}
		}
	}


	void walk()  // �̰� ���� �̻���. ���׶�̿� ȭ��ǥ�� �ް�����?
	{
		if (�� ������ �Ÿ�, ���� �÷��׿��� ��ġ�� ���ʿ� ������,)
		{
			left_walk();
		}

		else if (�� ������ �Ÿ�, ���� �÷��׿��� ��ġ�� �����ʿ� ������, )
		{
			right_walk();
		}
	}


	void basic_frame()
	{
			
		if(state== Detection_0)
		{
			void walk();

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
	static DWORD dwEventTime = 300; // �̺�Ʈ �߻� ���� �� ����ϴ�. < GetTickCount�δ� 1/1000�� ������ �Ҽ� �ֱ� ������ 2���Դϴ�.
	static DWORD dw_NoUpdate_Time = GetTickCount();// ���� �ð��� ����ϴ�.
	DWORD dw_AutoUpdate_CurTime = GetTickCount();	//���� �ð��� ����ϴ�.


	if (Gun_step == 1 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // ������ �ð��� �������� if���� �����մϴ�.
	{
		Gun_step = 2;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
	}

	if (Gun_step == 2 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // ������ �ð��� �������� if���� �����մϴ�.
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
	static DWORD dwEventTime = 300; // �̺�Ʈ �߻� ���� �� ����ϴ�. < GetTickCount�δ� 1/1000�� ������ �Ҽ� �ֱ� ������ 2���Դϴ�.
	static DWORD dw_NoUpdate_Time = GetTickCount();// ���� �ð��� ����ϴ�.
	DWORD dw_AutoUpdate_CurTime = GetTickCount();	//���� �ð��� ����ϴ�.


	if (sword_step == 1 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // ������ �ð��� �������� if���� �����մϴ�.
	{
		sword_step = 2;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
	}

	if (sword_step == 2 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // ������ �ð��� �������� if���� �����մϴ�.
	{
		sword_step = 3;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
	}

	if (sword_step == 3 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // ������ �ð��� �������� if���� �����մϴ�.
	{
		sword_step = 4;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
	}

	if (sword_step == 4 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // ������ �ð��� �������� if���� �����մϴ�.
	{
		sword_step = 5;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
	}

	if (sword_step == 5 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // ������ �ð��� �������� if���� �����մϴ�.
	{
		sword_step = 6;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
	}

	if (sword_step == 6 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // ������ �ð��� �������� if���� �����մϴ�.
	{
		sword_step = 7;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
	}



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


				sword_step = 0;
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

				sword_step = 0;
			}break;

		}

	}

}
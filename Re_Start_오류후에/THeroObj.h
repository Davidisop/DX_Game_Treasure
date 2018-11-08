#pragma once
#include "Character.h"


class THeroObj : public Character
{
public:
	
	void right_walk();
	void left_walk();
	void shot();

	void sword();
	void slide();


public:

	bool  Bullet_Go;
	int   Gun_step;
	bool  Jump_Yes_No;
	bool  m_Collision_down_side;
	int	  sword_step;
	int   slide_step;
	



public:
	THeroObj() : Gun_step(0), Jump_Yes_No(false), m_Collision_down_side(false), sword_step(0), slide_step(0)
	{
		/*Gun_step = 0;
		Jump_Yes_No = false;
		m_Collision_down_side = false;
		sword_step = 0;
		slide_step = 0;*/
	}
	virtual ~THeroObj() {}
};

void THeroObj::left_walk()
{

	static float fAddTime = 0.0f;
	fAddTime += g_fSecPerFrame;


	if (Jump_Yes_No == false)
	{

		if (fAddTime >= 0.1f)
		{
			switch (walk_step)
			{
				case 0:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 0, 0, 758, 535);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Girl_Left.png");
					++walk_step;
				}break;
				case 1:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 0, 1, 758, 535);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Girl_Left.png");
					++walk_step;
				}break;

				case 2:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 0, 2, 758, 535);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Girl_Left.png");
					++walk_step;
				}break;
				case 3:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 0, 3, 758, 535);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Girl_Left.png");
					++walk_step;
				}break;
				case 4:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 0, 4, 758, 535);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Girl_Left.png");
					++walk_step;
				}break;

				case 5:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 0, 5, 758, 535);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Girl_Left.png");
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


void THeroObj::right_walk()
{

	static float fAddTime = 0.0f;
	fAddTime += g_fSecPerFrame;


	if (Jump_Yes_No == false)
	{

		if (fAddTime >= 0.1f)
		{

			switch (walk_step)
			{
				case 0:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 1, 0, 758, 535);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Girl_Right.png");
					++walk_step;
				}break;

				case 1:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 1, 1, 758, 535);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Girl_Right.png");
					++walk_step;
				}break;

				case 2:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 1, 2, 758, 535);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Girl_Right.png");
					++walk_step;
				}break;
				case 3:
				{

					in_Texture_SetData_sprite_factors(sprite_ptr, 1, 3, 758, 535);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Girl_Right.png");
					++walk_step;
				}break;
				case 4:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 1, 4, 758, 535);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Girl_Right.png");
					++walk_step;
				}break;

				case 5:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 1, 5, 758, 535);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Girl_Right.png");
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





void THeroObj::shot()
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

	if (Jump_Yes_No == false)
	{

		if (Face_Direction == 2)

		{

			switch (Gun_step)
			{
				case 1:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 3, 0, 758, 535);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Girl_Right.png");


					++Gun_step;
				}break;

				case 2:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 3, 1, 758, 535);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Girl_Right.png");


					++Gun_step;

				}break;

				case 3:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 3, 2, 758, 535);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Girl_Right.png");


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
					in_Texture_SetData_sprite_factors(sprite_ptr, 2, 0, 758, 535);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Girl_Left.png");


					++Gun_step;
				}break;

				case 2:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 2, 1, 758, 535);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Girl_Left.png");

					++Gun_step;
				}break;

				case 3:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 2, 2, 758, 535);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Girl_Left.png");

					Gun_step = 0;
				}break;

			}

		}
	}
}






void THeroObj::slide()
{
	static DWORD dwEventTime = 300; // 이벤트 발생 간격 을 얻습니다. < GetTickCount로는 1/1000초 단위로 할수 있기 때문에 2초입니다.
	static DWORD dw_NoUpdate_Time = GetTickCount();// 기준 시간을 얻습니다.
	DWORD dw_AutoUpdate_CurTime = GetTickCount();	//현재 시간을 얻습니다.


	if (slide_step == 1 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // 설정한 시간이 지나가면 if문을 실행합니다.
	{
		slide_step = 2;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
	}

	if (slide_step == 2 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // 설정한 시간이 지나가면 if문을 실행합니다.
	{
		slide_step = 3;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
	}

	if (slide_step == 3 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // 설정한 시간이 지나가면 if문을 실행합니다.
	{
		slide_step = 4;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
	}

	if (slide_step == 4 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // 설정한 시간이 지나가면 if문을 실행합니다.
	{
		slide_step = 5;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
	}


	if (Jump_Yes_No == false)
	{

		if (Face_Direction == 2)

		{

			switch (slide_step)
			{
				case 1:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 13, 0, 757, 1274);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


					++slide_step;
				}break;

				case 2:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 13, 1, 757, 1274);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


					++slide_step;

				}break;

				case 3:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 13, 2, 757, 1274);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


					++slide_step;
				}break;
				case 4:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 13, 3, 757, 1274);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


					++slide_step;
				}break;
				case 5:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 13, 4, 757, 1274);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


					slide_step = 0;
				}break;

			}
		}

		else if (Face_Direction == 1)
		{


			switch (slide_step)
			{
				case 1:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 12, 0, 757, 1274);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


					++slide_step;
				}break;

				case 2:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 12, 1, 757, 1274);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


					++slide_step;

				}break;

				case 3:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 12, 2, 757, 1274);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


					++slide_step;
				}break;
				case 4:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 12, 3, 757, 1274);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


					++slide_step;
				}break;
				case 5:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 12, 4, 757, 1274);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


					slide_step = 0;
				}break;

			}

		}
	}
}



void THeroObj::sword()
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


	if (Jump_Yes_No == false)
	{

		if (Face_Direction == 2)

		{

			switch (sword_step)
			{
				case 1:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 11, 0, 757, 1274);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


					++sword_step;
				}break;

				case 2:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 11, 1, 757, 1274);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


					++sword_step;

				}break;

				case 3:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 11, 2, 757, 1274);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


					++sword_step;
				}break;


				case 4:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 11, 3, 757, 1274);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


					++sword_step;

				}break;

				case 5:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 11, 4, 757, 1274);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


					++sword_step;
				}break;

				case 6:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 11, 5, 757, 1274);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


					++sword_step;
				}break;

				case 7:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 11, 6, 757, 1274);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


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
					in_Texture_SetData_sprite_factors(sprite_ptr, 10, 0, 757, 1274);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


					++sword_step;
				}break;

				case 2:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 10, 1, 757, 1274);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


					++sword_step;

				}break;

				case 3:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 10, 2, 757, 1274);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


					++sword_step;
				}break;


				case 4:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 10, 3, 757, 1274);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


					++sword_step;

				}break;

				case 5:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 10, 4, 757, 1274);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


					++sword_step;
				}break;

				case 6:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 10, 5, 757, 1274);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


					++sword_step;
				}break;

				case 7:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 10, 6, 757, 1274);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


					sword_step = 0;
				}break;

			}

		}
	}
}
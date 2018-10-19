#pragma once
#include "Character.h"


class THeroObj : public Character
{
public:
	//bool Frame();

//public:
//	void gravity_pre();
//	void gravity_post();
//	void excute_collision();
//
//public:
//
//	void stand();
	void right_walk();
	void left_walk();
	void shot();
	//void jump();
	
public:

	bool  Bullet_Go;
	int   Gun_step;
	float gravity_a;
	float m_fSpeed_Y;
	float m_fSpeed_JUMP;
	bool  Jump_Yes_No;
	int   jump_step;
	bool  m_Collision_down_side;

public:



public:
	THeroObj()
	{
		Gun_step = 0;
		gravity_a = 9.8;
		m_fSpeed_Y = 0;
		m_fSpeed_JUMP = -20;
		Jump_Yes_No = false;
		jump_step = 0;
		m_Collision_down_side = false;
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

//
//
//bool THeroObj::Frame()
//{
//	stand();
//	if (I_Input.Key('A')) { left_walk(); Face_Direction = 1; }
//	if (I_Input.Key('D')) { right_walk(); Face_Direction = 2; }
//	if (I_Input.Key('G')) { Gun_step = 1; }
//	shot();
//	gravity_post();
//	return true;
//}


//
//void THeroObj::gravity_pre()
//{
//	m_fSpeed_Y += gravity_a * g_fSecPerFrame * 30.0f;
//	m_pos.y += m_fSpeed_Y * g_fSecPerFrame + gravity_a * g_fSecPerFrame* g_fSecPerFrame* 30.0f / 2;
//}
//
//
//void THeroObj::gravity_post()
//{
//	if (m_pos.x == m_pos_past.x)
//	{
//		if (Jump_Yes_No == false)
//		{
//			move_Yes_No = false;
//		}
//
//		if (Jump_Yes_No == true)
//		{
//			move_Yes_No = true;
//		}
//	}
//
//	else
//	{
//		move_Yes_No = true;
//	}
//
//	m_pos_past.x = m_pos.x;
//}
//
//
//void  THeroObj::stand()
//{
//	if (move_Yes_No == false)
//	{
//		if (Face_Direction == 1)
//		{
//			Set(m_pos.x, m_pos.y, 39, 5, 56, 90);
//			Load(L"../../data/Girl_Left.bmp", L"../../data/Girl_Left_B.bmp");
//		}
//
//		else if (Face_Direction == 2)
//		{
//			Set(m_pos.x, m_pos.y, 20, 5, 60, 93);
//			Load(L"../../data/Girl_Right.bmp", L"../../data/Girl_Right_B.bmp");
//		}
//	}
//}
//
//
//void THeroObj::excute_collision()
//{
//	if (m_pos.y > 420) { m_Collision_down_side = true; }
//
//	if (m_Collision_number == 1)
//	{
//		m_fSpeed_Y = 0;
//		m_fSpeed_JUMP = 0;
//		m_pos.y = 300;
//		Jump_Yes_No = false;
//		move_Yes_No = false;
//
//		if (m_pos.x > 370 || m_pos.x < 230)
//		{
//			m_Collision_number = 0;
//		}
//	}
//
//	if (m_Collision_down_side == true)
//	{
//		m_fSpeed_Y = 0;
//		m_fSpeed_JUMP = 0;
//		m_pos.y = m_pos_past.y;
//		m_Collision_down_side = false;
//		Jump_Yes_No = false;
//	}
//
//	if (m_Collision_number == 2 && move_Yes_No == true)
//	{
//		m_pos.x += 3;
//		m_Collision_number = 0;
//	}
//
//
//	if (m_Collision_number == 3 && move_Yes_No == true)
//	{
//		m_pos.x -= 3;
//		m_Collision_number = 0;
//	}
//
//}
//
//
//



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
//
//
//void THeroObj::jump()
//{
//	switch (Jump_Yes_No)
//	{
//		case 0:
//		{
//
//		}break;
//
//		case 1:
//		{
//			m_fSpeed_JUMP = -15;
//			m_Collision_down_side = false;
//
//			m_fSpeed_JUMP += gravity_a * g_fSecPerFrame;
//			m_pos.y += m_fSpeed_JUMP * g_fSecPerFrame*50.0f + m_fSpeed_Y * g_fSecPerFrame + gravity_a * g_fSecPerFrame* 50.0f* g_fSecPerFrame* 50.0f;
//
//
//			static float fAddTime = 0.0f;
//			fAddTime += g_fSecPerFrame;
//
//
//			if (fAddTime >= 0.1f)
//			{
//				if (Face_Direction == 2)
//				{
//
//					switch (jump_step)
//					{
//						case 0:
//						{
//							Set(m_pos.x, m_pos.y, sprite_ptr->Sprite_Sturcture[5][0]);
//							Load(L"../../data/Girl_Right.bmp", L"../../data/Girl_Right_B.bmp");
//							++jump_step;
//						}break;
//
//						case 1:
//						{
//							Set(m_pos.x, m_pos.y, sprite_ptr->Sprite_Sturcture[5][1]);
//							Load(L"../../data/Girl_Right.bmp", L"../../data/Girl_Right_B.bmp");
//							++jump_step;
//						}break;
//
//						case 2:
//						{
//							Set(m_pos.x, m_pos.y, sprite_ptr->Sprite_Sturcture[5][2]);
//							Load(L"../../data/Girl_Right.bmp", L"../../data/Girl_Right_B.bmp");
//							++jump_step;
//						}break;
//						case 3:
//						{
//							Set(m_pos.x, m_pos.y, sprite_ptr->Sprite_Sturcture[5][3]);
//							Load(L"../../data/Girl_Right.bmp", L"../../data/Girl_Right_B.bmp");
//							++jump_step;
//						}break;
//						case 4:
//						{
//							Set(m_pos.x, m_pos.y, sprite_ptr->Sprite_Sturcture[5][4]);
//							Load(L"../../data/Girl_Right.bmp", L"../../data/Girl_Right_B.bmp");
//							++jump_step;
//						}break;
//
//						case 5:
//						{
//							Set(m_pos.x, m_pos.y, sprite_ptr->Sprite_Sturcture[5][5]);
//							Load(L"../../data/Girl_Right.bmp", L"../../data/Girl_Right_B.bmp");
//							++jump_step;
//						}break;
//						case 6:
//						{
//
//							Set(m_pos.x, m_pos.y, sprite_ptr->Sprite_Sturcture[5][6]);
//							Load(L"../../data/Girl_Right.bmp", L"../../data/Girl_Right_B.bmp");
//							++jump_step;
//						}break;
//						case 7:
//						{
//							Set(m_pos.x, m_pos.y, sprite_ptr->Sprite_Sturcture[5][7]);
//							Load(L"../../data/Girl_Right.bmp", L"../../data/Girl_Right_B.bmp");
//							++jump_step;
//						}break;
//
//						case 8:
//						{
//							Set(m_pos.x, m_pos.y, sprite_ptr->Sprite_Sturcture[5][8]);
//							Load(L"../../data/Girl_Right.bmp", L"../../data/Girl_Right_B.bmp");
//							jump_step = 0;
//						}break;
//
//					}
//				}
//
//				else if (Face_Direction == 1)
//				{
//
//					switch (jump_step)
//					{
//						case 0:
//						{
//							Set(m_pos.x, m_pos.y, sprite_ptr->Sprite_Sturcture[6][0]);
//							Load(L"../../data/Girl_Left.bmp", L"../../data/Girl_Left_B.bmp");
//							++jump_step;
//						}break;
//
//						case 1:
//						{
//							Set(m_pos.x, m_pos.y, sprite_ptr->Sprite_Sturcture[6][1]);
//							Load(L"../../data/Girl_Left.bmp", L"../../data/Girl_Left_B.bmp");
//							++jump_step;
//						}break;
//
//						case 2:
//						{
//							Set(m_pos.x, m_pos.y, sprite_ptr->Sprite_Sturcture[6][2]);
//							Load(L"../../data/Girl_Left.bmp", L"../../data/Girl_Left_B.bmp");
//							++jump_step;
//						}break;
//						case 3:
//						{
//
//							Set(m_pos.x, m_pos.y, sprite_ptr->Sprite_Sturcture[6][3]);
//							Load(L"../../data/Girl_Left.bmp", L"../../data/Girl_Left_B.bmp");
//							++jump_step;
//						}break;
//						case 4:
//						{
//							Set(m_pos.x, m_pos.y, sprite_ptr->Sprite_Sturcture[6][4]);
//							Load(L"../../data/Girl_Left.bmp", L"../../data/Girl_Left_B.bmp");
//							++jump_step;
//						}break;
//
//						case 5:
//						{
//							Set(m_pos.x, m_pos.y, sprite_ptr->Sprite_Sturcture[6][5]);
//							Load(L"../../data/Girl_Left.bmp", L"../../data/Girl_Left_B.bmp");
//							++jump_step;
//						}break;
//						case 6:
//						{
//
//							Set(m_pos.x, m_pos.y, sprite_ptr->Sprite_Sturcture[6][6]);
//							Load(L"../../data/Girl_Left.bmp", L"../../data/Girl_Left_B.bmp");
//							++jump_step;
//						}break;
//
//						case 7:
//						{
//							Set(m_pos.x, m_pos.y, sprite_ptr->Sprite_Sturcture[6][7]);
//							Load(L"../../data/Girl_Left.bmp", L"../../data/Girl_Left_B.bmp");
//							++jump_step;
//						}break;
//
//						case 8:
//						{
//							Set(m_pos.x, m_pos.y, sprite_ptr->Sprite_Sturcture[6][8]);
//							Load(L"../../data/Girl_Left.bmp", L"../../data/Girl_Left_B.bmp");
//							jump_step = 0;
//						}break;
//
//					}
//
//				}
//
//				if (fAddTime >= 0.1f)
//				{
//					fAddTime -= 0.1f;
//				}
//			}
//		}break;
//	}
//
//
//}

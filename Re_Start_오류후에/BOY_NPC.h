#include "Character.h"

class Boy_NPC : public Character
{
public:
	

public:
	int dead_step;
	bool walk_flag;
	int hurt_step;
	bool hurt_flag;
	bool initial_start;



	void dead();
	void hurt();

public:

	bool	walk()
	{
		static float fAddTime = 0.0f;
		fAddTime += g_fSecPerFrame;

		if (fAddTime >= 0.1f)
		{
			switch (walk_step)
			{

				case 1:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 4, 0, 753, 532);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy_B.png");
					
					walk_step++;
					
				}break;

				case 2:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 4, 1, 753, 532);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy_B.png");
					
					walk_step++;
					
				}break;

				case 3:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 4, 2, 753, 532);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy_B.png");
					
					walk_step++;
					
				}break;
				case 4:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 4, 3, 753, 532);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy_B.png");
					
					walk_step++;
					
				}break;

				case 5:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 4, 4, 753, 532);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy_B.png");
					
					walk_step++;
					
				}break;

				case 6:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 4, 5, 753, 532);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy_B.png");
					
					walk_step++;
					
				}break;
				case 7:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 4, 6, 753, 532);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy_B.png");
					
					walk_step++;
					
				}break;

				case 8:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 4, 7, 753, 532);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy_B.png");
					
					walk_step++;
					
				}break;

				case 9:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 4, 8, 753, 532);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy_B.png");
					
					walk_step++;
					
				}break;

				case 10:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 4, 9, 753, 532);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy_B.png");
					
					walk_step = 1;
				}break;
			}
			
		}

		if (fAddTime >= 0.1f)
		{
		fAddTime -= 0.1f;

		}

/*

		if (m_Collision_number == 3)
		{
			in_Texture_SetData_sprite_factors(sprite_ptr, 7, 0, 753, 532);
			Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy_B.png");
		}*/

		return true;

	}


public:
	Boy_NPC() 
	{ 
	  dead_step = 0;
	  walk_flag = 0;
	  hurt_step = 1;
	  initial_start = true;
	  hurt_flag = false;
	
	}
	virtual ~Boy_NPC() {}

};


void Boy_NPC::hurt()
{
	static DWORD dwEventTime = 400; // 이벤트 발생 간격 을 얻습니다. < GetTickCount로는 1/1000초 단위로 할수 있기 때문에 2초입니다.
	static DWORD dw_NoUpdate_Time = GetTickCount();// 기준 시간을 얻습니다.
	DWORD dw_AutoUpdate_CurTime = GetTickCount();	//현재 시간을 얻습니다.


	if (hurt_step == 1 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // 설정한 시간이 지나가면 if문을 실행합니다.
	{
		hurt_step = 2;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 400;
	}

	if (hurt_step == 2 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // 설정한 시간이 지나가면 if문을 실행합니다.
	{
		hurt_step = 3;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 400;
	}

	
	switch (hurt_step)
	{
		case 1:
		{
			in_Texture_SetData_sprite_factors(sprite_ptr, 15, 0, 757, 1274);
			Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


			++hurt_step;
		}break;

		case 2:
		{
			in_Texture_SetData_sprite_factors(sprite_ptr, 15, 1, 757, 1274);
			Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


			++hurt_step;

		}break;

		case 3:
		{
			in_Texture_SetData_sprite_factors(sprite_ptr, 15, 2, 757, 1274);
			Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


			++hurt_step;
		}break;
	}





}

void Boy_NPC::dead()
{
	static DWORD dwEventTime = 300; // 이벤트 발생 간격 을 얻습니다. < GetTickCount로는 1/1000초 단위로 할수 있기 때문에 2초입니다.
	static DWORD dw_NoUpdate_Time = GetTickCount();// 기준 시간을 얻습니다.
	DWORD dw_AutoUpdate_CurTime = GetTickCount();	//현재 시간을 얻습니다.


	if (dead_step == 1 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // 설정한 시간이 지나가면 if문을 실행합니다.
	{
		dead_step = 2;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
	}

	if (dead_step == 2 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // 설정한 시간이 지나가면 if문을 실행합니다.
	{
		dead_step = 3;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
	}

	if (dead_step == 3 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // 설정한 시간이 지나가면 if문을 실행합니다.
	{
		dead_step = 4;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
	}

	if (dead_step == 4 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // 설정한 시간이 지나가면 if문을 실행합니다.
	{
		dead_step = 5;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
	}

	if (dead_step == 5 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // 설정한 시간이 지나가면 if문을 실행합니다.
	{
		dead_step = 6;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
	}


			switch (dead_step)
			{
				case 1:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 15, 0, 757, 1274);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


					++dead_step;
				}break;

				case 2:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 15, 1, 757, 1274);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


					++dead_step;

				}break;

				case 3:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 15, 2, 757, 1274);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


					++dead_step;
				}break;
				case 4:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 15, 3, 757, 1274);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


					++dead_step;
				}break;

				case 5:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 15, 4, 757, 1274);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


					++dead_step;

				}break;

				case 6:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 15, 5, 757, 1274);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");


					dead_step = 0;
				}break;

			}
		

	
}


	//void fall()
	//{
	//	static DWORD dwEventTime = 300; // 이벤트 발생 간격 을 얻습니다. < GetTickCount로는 1/1000초 단위로 할수 있기 때문에 2초입니다.
	//	static DWORD dw_NoUpdate_Time = GetTickCount();// 기준 시간을 얻습니다.
	//	DWORD dw_AutoUpdate_CurTime = GetTickCount();	//현재 시간을 얻습니다.


	//	if (fall_step == 1 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // 설정한 시간이 지나가면 if문을 실행합니다.
	//	{
	//		fall_step = 2;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
	//	}

	//	if (fall_step == 2 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // 설정한 시간이 지나가면 if문을 실행합니다.
	//	{
	//		fall_step = 3;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
	//	}

	//	if (fall_step == 3 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // 설정한 시간이 지나가면 if문을 실행합니다.
	//	{
	//		fall_step = 4;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
	//	}

	//	if (fall_step == 4 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // 설정한 시간이 지나가면 if문을 실행합니다.
	//	{
	//		fall_step = 5;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
	//	}

	//	if (fall_step == 5 && dw_NoUpdate_Time + dwEventTime <= dw_AutoUpdate_CurTime) // 설정한 시간이 지나가면 if문을 실행합니다.
	//	{
	//		fall_step = 6;	dw_NoUpdate_Time = dw_AutoUpdate_CurTime;	dwEventTime = 200;
	//	}



	//	switch (fall_step)
	//			{
	//			case 1:
	//			{
	//				in_Texture_SetData_sprite_factors(sprite_ptr, 3, 0, 758, 535);
	//				Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Girl_Right.png");


	//				++fall_step;
	//			}break;

	//			case 2:
	//			{
	//				in_Texture_SetData_sprite_factors(sprite_ptr, 3, 1, 758, 535);
	//				Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Girl_Right.png");


	//				++fall_step;

	//			}break;

	//			case 3:
	//			{
	//				in_Texture_SetData_sprite_factors(sprite_ptr, 3, 2, 758, 535);
	//				Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Girl_Right.png");


	//				++fall_step;
	//			}break;
	//			case 4:
	//			{
	//				in_Texture_SetData_sprite_factors(sprite_ptr, 3, 2, 758, 535);
	//				Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Girl_Right.png");


	//				++fall_step;
	//			}break;
	//			case 5:
	//			{
	//				in_Texture_SetData_sprite_factors(sprite_ptr, 3, 2, 758, 535);
	//				Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Girl_Right.png");


	//				++fall_step;
	//			}break;
	//			case 6:
	//			{
	//				in_Texture_SetData_sprite_factors(sprite_ptr, 3, 2, 758, 535);
	//				Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Girl_Right.png");


	//				fall_step=0;
	//			}break;

	//	}
	//	

	

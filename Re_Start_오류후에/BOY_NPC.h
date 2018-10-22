#include "Character.h"

class Boy_NPC : public Character
{
public:
	bool	frame()
	{


		static DWORD dwEventTime_2 = 100; // 이벤트 발생 간격 을 얻습니다. < GetTickCount로는 1/1000초 단위로 할수 있기 때문에 2초입니다.
		static DWORD dwTime_2 = GetTickCount();// 기준 시간을 얻습니다.
		DWORD dwCurTime_2 = GetTickCount();	//현재 시간을 얻습니다.

		if (m_bDead == true)
		{
			if (m_Collision_number == 1) { walk_step = 1; }
			if (walk_step == 1 && dwTime_2 + dwEventTime_2 <= dwCurTime_2) { walk_step = 2;	dwTime_2 = dwCurTime_2;		dwEventTime_2 = 100; }
			if (walk_step == 2 && dwTime_2 + dwEventTime_2 <= dwCurTime_2) { walk_step = 3;	dwTime_2 = dwCurTime_2;		dwEventTime_2 = 100; }
			if (walk_step == 3 && dwTime_2 + dwEventTime_2 <= dwCurTime_2) { walk_step = 4;	dwTime_2 = dwCurTime_2;		dwEventTime_2 = 100; }
			if (walk_step == 4 && dwTime_2 + dwEventTime_2 <= dwCurTime_2) { walk_step = 5;	dwTime_2 = dwCurTime_2;		dwEventTime_2 = 100; }
			if (walk_step == 5 && dwTime_2 + dwEventTime_2 <= dwCurTime_2) { walk_step = 6;	dwTime_2 = dwCurTime_2;		dwEventTime_2 = 100; }
			if (walk_step == 6 && dwTime_2 + dwEventTime_2 <= dwCurTime_2) { walk_step = 7;	dwTime_2 = dwCurTime_2;		dwEventTime_2 = 100; }
			if (walk_step == 7 && dwTime_2 + dwEventTime_2 <= dwCurTime_2) { walk_step = 8;	dwTime_2 = dwCurTime_2;		dwEventTime_2 = 100; }
			if (walk_step == 8 && dwTime_2 + dwEventTime_2 <= dwCurTime_2) { walk_step = 9;	dwTime_2 = dwCurTime_2;		dwEventTime_2 = 100; }
			if (walk_step == 9 && dwTime_2 + dwEventTime_2 <= dwCurTime_2) { walk_step = 10;	dwTime_2 = dwCurTime_2;		dwEventTime_2 = 100; }


			switch (walk_step)
			{
				case 1:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 4, 0, 753, 532);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy_B.png");
					m_pos.x += 1 * g_fSecPerFrame*100.0f;
				}break;

				case 2:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 4, 1, 753, 532);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy_B.png");
					m_pos.x += 1 * g_fSecPerFrame*100.0f;
				}break;

				case 3:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 4, 2, 753, 532);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy_B.png");
					m_pos.x += 1 * g_fSecPerFrame*100.0f;
				}break;
				case 4:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 4, 3, 753, 532);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy_B.png");
					m_pos.x += 1 * g_fSecPerFrame*100.0f;
				}break;

				case 5:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 4, 4, 753, 532);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy_B.png");
					m_pos.x += 1 * g_fSecPerFrame*100.0f;
				}break;

				case 6:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 4, 5, 753, 532);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy_B.png");
					m_pos.x += 1 * g_fSecPerFrame*100.0f;
				}break;
				case 7:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 4, 6, 753, 532);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy_B.png");
					m_pos.x += 1 * g_fSecPerFrame*100.0f;
				}break;

				case 8:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 4, 7, 753, 532);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy_B.png");
					m_pos.x += 1 * g_fSecPerFrame*100.0f;
				}break;

				case 9:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 4, 8, 753, 532);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy_B.png");
					m_pos.x += 1 * g_fSecPerFrame*100.0f;
				}break;

				case 10:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 4, 9, 753, 532);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy_B.png");
					m_pos.x += 1 * g_fSecPerFrame*100.0f;
					dwTime_2 = dwCurTime_2;
					walk_step = 1;
				}break;
			}
		}

		if (m_Collision_number == 2)
		{
			in_Texture_SetData_sprite_factors(sprite_ptr, 7, 0, 753, 532);
			Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy_B.png");
		}

		return true;

	}



public:
	Boy_NPC() {}
	virtual ~Boy_NPC() {}
	
};

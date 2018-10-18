#include "Character.h"

class NPC : public Character
{
public:
	bool	Frame()
	{

		int iHalfX = m_rtDraw.right / 2;
		int iHalfY = m_rtDraw.bottom / 2;


		m_posDraw.x = m_pos.x - iHalfX;
		m_posDraw.y = m_pos.y - iHalfY;

		m_rtCollision.left = m_posDraw.x;
		m_rtCollision.top = m_posDraw.y;
		m_rtCollision.right = m_rtCollision.left + m_rtDraw.right;
		m_rtCollision.bottom = m_rtCollision.top + m_rtDraw.bottom;


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
					Set(m_pos.x, m_pos.y, 91, 2, 59, 84);
					Load(L"../../data/AD_Boy.bmp", L"../../data/AD_Boy_B.bmp");
					m_pos.x += 1 * g_fSecPerFrame*100.0f;

				}break;

				case 2:
				{
					Set(m_pos.x, m_pos.y, 159, 2, 64, 93);
					Load(L"../../data/AD_Boy.bmp", L"../../data/AD_Boy_B.bmp");
					m_pos.x += 1 * g_fSecPerFrame*100.0f;
				}break;

				case 3:
				{
					Set(m_pos.x, m_pos.y, 234, 2, 66, 92);
					Load(L"../../data/AD_Boy.bmp", L"../../data/AD_Boy_B.bmp");
					m_pos.x += 1 * g_fSecPerFrame*100.0f;
				}break;
				case 4:
				{
					Set(m_pos.x, m_pos.y, 304, 2, 72, 88);
					Load(L"../../data/AD_Boy.bmp", L"../../data/AD_Boy_B.bmp");
					m_pos.x += 1 * g_fSecPerFrame*100.0f;
				}break;

				case 5:
				{
					Set(m_pos.x, m_pos.y, 383, 2, 72, 92);
					Load(L"../../data/AD_Boy.bmp", L"../../data/AD_Boy_B.bmp");
					m_pos.x += 1 * g_fSecPerFrame*100.0f;
				}break;

				case 6:
				{
					Set(m_pos.x, m_pos.y, 468, 2, 62, 90);
					Load(L"../../data/AD_Boy.bmp", L"../../data/AD_Boy_B.bmp");
					m_pos.x += 1 * g_fSecPerFrame*100.0f;
				}break;
				case 7:
				{
					Set(m_pos.x, m_pos.y, 542, 2, 63, 91);
					Load(L"../../data/AD_Boy.bmp", L"../../data/AD_Boy_B.bmp");
					m_pos.x += 1 * g_fSecPerFrame*100.0f;
				}break;

				case 8:
				{
					Set(m_pos.x, m_pos.y, 614, 2, 68, 88);
					Load(L"../../data/AD_Boy.bmp", L"../../data/AD_Boy_B.bmp");
					m_pos.x += 1 * g_fSecPerFrame*100.0f;
				}break;

				case 9:
				{
					Set(m_pos.x, m_pos.y, 4, 102, 66, 80);
					Load(L"../../data/AD_Boy.bmp", L"../../data/AD_Boy_B.bmp");
					m_pos.x += 1 * g_fSecPerFrame*100.0f;
				}break;

				case 10:
				{
					Set(m_pos.x, m_pos.y, 85, 105, 63, 79);
					Load(L"../../data/AD_Boy.bmp", L"../../data/AD_Boy_B.bmp");
					m_pos.x += 1 * g_fSecPerFrame*100.0f;
					dwTime_2 = dwCurTime_2;
					walk_step = 1;
				}break;
			}
		}

		if (m_bDead == false)
		{
			Set(m_pos.x, m_pos.y, 0, 0, 70, 94);
			Load(L"../../data/AD_Boy.bmp", L"../../data/AD_Boy_B.bmp");
		}



		return true;


	}

	bool    Render()
	{

		// collision rect

		if (m_bDebugRect)
		{
			int prevMode = SetROP2(g_hOffScreenDC, R2_XORPEN);
			Rectangle(g_hOffScreenDC,
				m_rtCollision.left,
				m_rtCollision.top,
				m_rtCollision.left + m_rtDraw.right,
				m_rtCollision.top + m_rtDraw.bottom);

			SetROP2(g_hOffScreenDC, prevMode);
		}

		return true;

	}

public:
	NPC();
	virtual ~NPC();
	void Create_State(String type);
};

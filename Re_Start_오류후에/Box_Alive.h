#pragma once
#include "Object_Handling.h"
//
//
//enum { Detection_0 = 0, Detection_1 = 1 };

class Box_Alive : public Object_Handling
{

public:
//
//	float detection_time;
//	bool  ghost_shoot_flag;
//	int   state;
//	bool Bullet_F1_Bullet_Go;
//	bool Bullet_F2_Bullet_Go;
//	bool Bullet_F3_Bullet_Go;
//	bool Bullet_F4_Bullet_Go;
//
//public:
//
//
//	void frame()
//	{
//
//		if (감지중)
//		{
//
//			static float fAddTime = 0.0f;
//			fAddTime += g_fSecPerFrame;
//			
//			if (fAddTime >= 1f)
//			{
//				Detction_FULL();
//				fAddTime = 0;
//			}
//		
//		}
//
//
//		{
//
//
//
//		void Detction_FULL(void)
//		{
//			
//			else if (state == 0초 감지)
//			{
//				state = 1초 감지;
//				attack();
//			}
//		}
//
//	public:
//
//		void attack(void)
//		{
//			if (state == 1초감지)
//			{
//				state = 0초 감지;
//				고스트 샷 플래그 발동();
//
//				if (고스트 샷 플래그 발동 되면,)
//				{
//					static int count_K = 1;
//					if (count_K == 1) { Bullet_F1_Bullet_Go = true; }  // 씬에서 이거와 연동되서, 고스트 나간다.
//					if (count_K == 2) { Bullet_F2_Bullet_Go = true; }
//					if (count_K == 3) { Bullet_F3_Bullet_Go = true; }
//					if (count_K == 4) { Bullet_F4_Bullet_Go = true; }
//					count_K++;
//				}
//
//
//			}
//		}
//	}
//
//
//
//
//
//
//
//


	Box_Alive()
	{
	/*	detection_time = 0;
		ghost_shoot_flag = false;
		state = Detection_0;
		 Bullet_F1_Bullet_Go = false;
		 Bullet_F2_Bullet_Go = false;
		 Bullet_F3_Bullet_Go = false;
		 Bullet_F4_Bullet_Go = false; */
	}
	virtual ~Box_Alive() {}
	   
};


//
//
//
//static DWORD dwEventTime_2 = 13000; // 이벤트 발생 간격 을 얻습니다. < GetTickCount로는 1/1000초 단위로 할수 있기 때문에 2초입니다.
//static DWORD dwTime_2 = GetTickCount();// 기준 시간을 얻습니다.
//DWORD dwCurTime_2 = GetTickCount();	//현재 시간을 얻습니다.
//
//
//
//if (Treasure_Box.m_bDead == false)
//{
//	TSound::Get()->PlayEffect(5);
//	{ Treasure_Box.Linger_Stage = 1; }
//	if (Treasure_Box.Linger_Stage == 1 && dwTime_2 + dwEventTime_2 <= dwCurTime_2) { Treasure_Box.Linger_Stage = 2;	dwTime_2 = dwCurTime_2;		dwEventTime_2 = 5000; }
//
//	switch (Treasure_Box.Linger_Stage)
//	{
//
//		e += g_fSecPerFrame;
//
//		if (fAddTime >= 1.0f) { move_Yes_No = true; }
//		/////////////////////////////////////스위치 ON 됨////////////////////////////////////////////////////////
//
//		if (move_Yes_No == true && Much_Fire_ptr->m_Collision_number == 0)
//		{
//			Much_Fire_ptr->Set(Much_Fire_ptr->m_pos.x, Much_Fire_ptr->m_pos.y, 0, 0, 100, 92);
//			Much_Fire_ptr->Load(L"../../data/Duskull.bmp", L"../../data/Duskull_B.bmp");
//			Much_Fire_ptr->m_pos.x -= g_fSecPerFrame * 700.0f;
//
//		}
//
//
//		if (Much_Fire_ptr->m_Collision_number > 0 && switch_Yes_No == false)
//		{
//			fAddTime = 0.0f;
//			switch_Yes_No = true;
//		}
//
//
//		if (Much_Fire_ptr->m_Collision_number > 0 && switch_Yes_No == false)
//		{
//			fAddTime = 0.0f;
//			switch_Yes_No = true;
//		}
//
//
//		//////////////////////////////////////스위치 ON 됨//////////////////////////////////////////////////////////
//
//		if (switch_Yes_No == true && Much_Fire_ptr_2->m_Collision_number == 0 && fAddTime >= 1.0f)
//		{
//			Much_Fire_ptr_2->Set(Much_Fire_ptr_2->m_pos.x, Much_Fire_ptr_2->m_pos.y, 0, 0, 100, 92);
//			Much_Fire_ptr_2->Load(L"../../data/Duskull.bmp", L"../../data/Duskull_B.bmp");
//			Much_Fire_ptr_2->m_pos.x -= g_fSecPerFrame * 700.0f;
//		}
//	}
//}
//};

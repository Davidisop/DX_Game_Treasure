



static DWORD dwEventTime_2 = 13000; // �̺�Ʈ �߻� ���� �� ����ϴ�. < GetTickCount�δ� 1/1000�� ������ �Ҽ� �ֱ� ������ 2���Դϴ�.
static DWORD dwTime_2 = GetTickCount();// ���� �ð��� ����ϴ�.
DWORD dwCurTime_2 = GetTickCount();	//���� �ð��� ����ϴ�.



if (Treasure_Box.m_bDead == false)
{
	TSound::Get()->PlayEffect(5);
	{ Treasure_Box.Linger_Stage = 1; }
	if (Treasure_Box.Linger_Stage == 1 && dwTime_2 + dwEventTime_2 <= dwCurTime_2) { Treasure_Box.Linger_Stage = 2;	dwTime_2 = dwCurTime_2;		dwEventTime_2 = 5000; }

	switch (Treasure_Box.Linger_Stage)
	{

		e += g_fSecPerFrame;

		if (fAddTime >= 1.0f) { move_Yes_No = true; }
		/////////////////////////////////////����ġ ON ��////////////////////////////////////////////////////////

		if (move_Yes_No == true && Much_Fire_ptr->m_Collision_number == 0)
		{
			Much_Fire_ptr->Set(Much_Fire_ptr->m_pos.x, Much_Fire_ptr->m_pos.y, 0, 0, 100, 92);
			Much_Fire_ptr->Load(L"../../data/Duskull.bmp", L"../../data/Duskull_B.bmp");
			Much_Fire_ptr->m_pos.x -= g_fSecPerFrame * 700.0f;

		}


		if (Much_Fire_ptr->m_Collision_number > 0 && switch_Yes_No == false)
		{
			fAddTime = 0.0f;
			switch_Yes_No = true;
		}


		if (Much_Fire_ptr->m_Collision_number > 0 && switch_Yes_No == false)
		{
			fAddTime = 0.0f;
			switch_Yes_No = true;
		}


		//////////////////////////////////////����ġ ON ��//////////////////////////////////////////////////////////

		if (switch_Yes_No == true && Much_Fire_ptr_2->m_Collision_number == 0 && fAddTime >= 1.0f)
		{
			Much_Fire_ptr_2->Set(Much_Fire_ptr_2->m_pos.x, Much_Fire_ptr_2->m_pos.y, 0, 0, 100, 92);
			Much_Fire_ptr_2->Load(L"../../data/Duskull.bmp", L"../../data/Duskull_B.bmp");
			Much_Fire_ptr_2->m_pos.x -= g_fSecPerFrame * 700.0f;
		}
	}
}
};

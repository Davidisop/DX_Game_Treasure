#include "Character.h"

class Boy_NPC : public Character
{
public:
	

public:
	int dead_step;
	bool dead_flag;
	bool walk_flag;
	int hurt_step;
	bool hurt_flag;
	bool Enter_flag_1;
	bool Enter_flag_2;
	bool initial_start;
	bool Finish_start;
	



	void dead();
	void hurt();


public:
	Boy_NPC() :dead_step(0), dead_flag(false), walk_flag(0), hurt_step(1), Enter_flag_1 (false), Enter_flag_2 (false), initial_start(true), Finish_start(true), hurt_flag (false)
	{
	/*	dead_step = 0;
		dead_flag = false;
		walk_flag = 0;
		hurt_step = 1;
		Enter_flag_1 = false;
		Enter_flag_2 = false;
		initial_start = true;
		Finish_start = true;
		hurt_flag = false;*/
	}
	virtual ~Boy_NPC() {}


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
			fAddTime = 0;

		}

		return true;

	}


};


void Boy_NPC::hurt()
{


	static float fAddTime = 0.0f;
	fAddTime += g_fSecPerFrame;

	if (hurt_step == 1 && fAddTime > 0.3f)
	{
		hurt_step = 2; fAddTime = 0;
	}

	else if (hurt_step == 2 && fAddTime > 0.3f)
	{
		hurt_step = 3; fAddTime = 0;
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


	static float fAddTime = 0.0f;
	fAddTime += g_fSecPerFrame;

	if (dead_step == 1 && fAddTime > 0.3f)
	{
		dead_step = 2; fAddTime = 0;
	}

	else if (dead_step == 2 && fAddTime > 0.3f)
	{
		dead_step = 3; fAddTime = 0;
	}

	else if (dead_step == 3 && fAddTime > 0.3f)
	{
		dead_step = 4; fAddTime = 0;
	}

	else if (dead_step == 4 && fAddTime > 0.3f)
	{
		dead_step = 5; fAddTime = 0;
	}
	else if (dead_step == 5&& fAddTime > 0.3f)
	{
		dead_step = 6; fAddTime = 0;
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


					++dead_step ;
				}break;

			}
		

	
}

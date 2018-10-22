#include "Character.h"

class Boy_NPC : public Character
{
public:
	bool	frame()
	{
		static float fAddTime = 0.0f;
		fAddTime += g_fSecPerFrame;
		if (fAddTime >= 0.1f)
		{
			switch (walk_step)
			{

				case 0:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 4, 0, 753, 532);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy_B.png");
					
					walk_step++;
					
				}break;

				case 1:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 4, 1, 753, 532);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy_B.png");
					
					walk_step++;
					
				}break;

				case 2:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 4, 2, 753, 532);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy_B.png");
					
					walk_step++;
					
				}break;
				case 3:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 4, 3, 753, 532);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy_B.png");
					
					walk_step++;
					
				}break;

				case 4:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 4, 4, 753, 532);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy_B.png");
					
					walk_step++;
					
				}break;

				case 5:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 4, 5, 753, 532);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy_B.png");
					
					walk_step++;
					
				}break;
				case 6:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 4, 6, 753, 532);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy_B.png");
					
					walk_step++;
					
				}break;

				case 7:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 4, 7, 753, 532);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy_B.png");
					
					walk_step++;
					
				}break;

				case 8:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 4, 8, 753, 532);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy_B.png");
					
					walk_step++;
					
				}break;

				case 9:
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
	Boy_NPC() {}
	virtual ~Boy_NPC() {}
	
};

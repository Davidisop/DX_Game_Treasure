#pragma once
#include "Object_Handling.h"

class Gun_Bullet : public Object_Handling
{
public:
	int bullet_step;
	bool Bullet_Go;
	bool Face_Direction1_flag;
	bool Face_Direction2_flag;
	sprite* sprite_ptr;

public:
	bool frame_F()
	{
		static float fAddTime = 0.0f;
		fAddTime += g_fSecPerFrame;
		if (fAddTime >= 0.1f)
		{
			switch (bullet_step)
			{



				case 0:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 8, 0, 400, 300);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/bitmap1.png");
					bullet_step++;

				}break;

				case 1:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 8, 1, 400, 300);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/bitmap1.png");

					bullet_step++;

				}break;

				case 2:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 8, 2, 400, 300);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/bitmap1.png");

					bullet_step++;

				}break;
				case 3:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 8, 3, 400, 300);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/bitmap1.png");

					bullet_step++;

				}break;

				case 4:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 8, 4, 400, 300);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/bitmap1.png");

					bullet_step++;

				}break;

				case 5:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 8, 5, 400, 300);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/bitmap1.png");

					bullet_step++;

				}break;
				case 6:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 8, 6, 400, 300);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/bitmap1.png");

				}break;

			}

		}

		if (fAddTime >= 0.1f)
		{
			fAddTime -= 0.1f;
		}
		return true;
	}


	bool frame_C()
	{
		static float fAddTime = 0.0f;
		fAddTime += g_fSecPerFrame;
		if (fAddTime >= 0.1f)
		{
			switch (bullet_step)
			{
				case 0:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 9, 0, 400, 300);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/bitmap1.png");
					bullet_step++;

				}break;

				case 1:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 9, 1, 400, 300);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/bitmap1.png");

					bullet_step++;

				}break;

				case 2:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 9, 2, 400, 300);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/bitmap1.png");

					bullet_step++;

				}break;
				case 3:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 9, 3, 400, 300);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/bitmap1.png");

					bullet_step++;

				}break;

				case 4:
				{
					in_Texture_SetData_sprite_factors(sprite_ptr, 9, 4, 400, 300);
					Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/bitmap1.png");
					bullet_step++;

				}break;

			}

		}

		if (fAddTime >= 0.1f)
		{
			fAddTime -= 0.1f;
		}

		return true;
	}

public:
	void  in_Texture_SetData_sprite_factors(sprite* sprite_ptr_in, int a, int b, float texture_width, float texture_height)
	{
		m_VertexList[0].u = (sprite_ptr_in->Sprite_Sturcture[a][b].left) / texture_width;
		m_VertexList[0].v = (sprite_ptr_in->Sprite_Sturcture[a][b].top) / texture_height;
		m_VertexList[1].u = (sprite_ptr_in->Sprite_Sturcture[a][b].left + sprite_ptr_in->Sprite_Sturcture[a][b].right) / texture_width;
		m_VertexList[1].v = (sprite_ptr_in->Sprite_Sturcture[a][b].top) / texture_height;
		m_VertexList[2].u = (sprite_ptr_in->Sprite_Sturcture[a][b].left) / texture_width;
		m_VertexList[2].v = (sprite_ptr_in->Sprite_Sturcture[a][b].top + sprite_ptr_in->Sprite_Sturcture[a][b].bottom) / texture_height;
		m_VertexList[3].u = (sprite_ptr_in->Sprite_Sturcture[a][b].left) / texture_width;
		m_VertexList[3].v = (sprite_ptr_in->Sprite_Sturcture[a][b].top + sprite_ptr_in->Sprite_Sturcture[a][b].bottom) / texture_height;
		m_VertexList[4].u = (sprite_ptr_in->Sprite_Sturcture[a][b].left + sprite_ptr_in->Sprite_Sturcture[a][b].right) / texture_width;
		m_VertexList[4].v = (sprite_ptr_in->Sprite_Sturcture[a][b].top) / texture_height;
		m_VertexList[5].u = (sprite_ptr_in->Sprite_Sturcture[a][b].left + sprite_ptr_in->Sprite_Sturcture[a][b].right) / texture_width;
		m_VertexList[5].v = (sprite_ptr_in->Sprite_Sturcture[a][b].top + sprite_ptr_in->Sprite_Sturcture[a][b].bottom) / texture_height;
	}

public:
	Gun_Bullet() {
		Bullet_Go = false; bullet_step = 0; Face_Direction1_flag = false; Face_Direction2_flag = false;
	}
	virtual ~Gun_Bullet() {}
};

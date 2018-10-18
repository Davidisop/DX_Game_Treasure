#pragma once
#include "Object_Handling.h"


class Character : public Object_Handling
{
public:

	int Face_Direction;
	int walk_step;
	

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
	Character()
	{
		Face_Direction = 1;
		walk_step = 0;
	}
	virtual ~Character() {}
};


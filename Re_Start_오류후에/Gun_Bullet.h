#pragma once
#include "Object_Handling.h"

class Gun_Bullet : public Object_Handling
{
public:
	bool Frame()
	{
		if (m_Collision_number == 0)
		{
			basic();
		}
		return true;
	}
	bool Render()
	{

		bool Gun_Bullet::Render()
		{

			if (m_Collision_number == 0)
			{

				if (m_pMaskBitmap == NULL)
				{
					BitBlt(g_hOffScreenDC,
						m_posDraw.x, m_posDraw.y,
						m_rtDraw.right,
						m_rtDraw.bottom,
						m_pColorBitmap->m_hMemDC,
						m_rtDraw.left,
						m_rtDraw.top, SRCCOPY);
					return true;
				}

				else
				{
					BitBlt(g_hOffScreenDC,
						m_posDraw.x, m_posDraw.y,
						m_rtDraw.right,
						m_rtDraw.bottom,
						m_pMaskBitmap->m_hMemDC,
						m_rtDraw.left,
						m_rtDraw.top, SRCAND);
					BitBlt(g_hOffScreenDC,
						m_posDraw.x, m_posDraw.y,
						m_rtDraw.right,
						m_rtDraw.bottom,
						m_pColorBitmap->m_hMemDC,
						m_rtDraw.left,
						m_rtDraw.top, SRCINVERT);//XOR
					BitBlt(g_hOffScreenDC,
						m_posDraw.x, m_posDraw.y,
						m_rtDraw.right,
						m_rtDraw.bottom,
						m_pMaskBitmap->m_hMemDC,
						m_rtDraw.left,
						m_rtDraw.top, SRCINVERT);
				}

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
			}
			return true;
		}

	}
public:

	bool Bullet_Go;

public:
	Gun_Bullet();
	virtual ~Gun_Bullet();
};




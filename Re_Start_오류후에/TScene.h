#include "THeroObj.h"
#include "Background.h"
#include "Box.h"
#include "TCollision.h"
#include "Boy_NPC.h"
#include "Gun_Bullet.h"
#include "Box_Alive.h"
#include "Box.h"

enum TSceneState
{
	GAME_SCENE_LOBBY = 0,
	GAME_SCENE_PLAY = 1,
	GAME_SCENE_END = 2,
};

class TScene
{
public:
	int		m_iSceneID;
	bool	m_bNextSceneStart;

public:
	virtual bool	Init() { return true; }
	virtual bool	Frame() { return true; }
	virtual bool	Render() { return true; }
	virtual bool	Release() { return true; }

public:
	TScene() 
	{
		m_bNextSceneStart = false;
	}
	virtual ~TScene() {}
};




class TSceneLobby : public TScene
{
public:
	Background			Lobby_Background;
	

	Box					UI_BUTTON;
	
public:
	virtual bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	TSceneLobby();
	virtual ~TSceneLobby();
};

bool	TSceneLobby::Init()
{


	Lobby_Background.in_Texture_SetData_factors(0, 0, 900, 500, 900, 500);
	Lobby_Background.m_for_update_Rects.x = g_rtClient.right;	Lobby_Background.m_for_update_Rects.y = g_rtClient.bottom;
	Lobby_Background.Window_SetData_factors(0, 0, Lobby_Background.m_for_update_Rects.x, Lobby_Background.m_for_update_Rects.y); 
	Lobby_Background.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Treasure_Island.bmp");
	



	UI_BUTTON.m_for_update_Rects.x = g_rtClient.right/4;	UI_BUTTON.m_for_update_Rects.y = g_rtClient.bottom/8;
	UI_BUTTON.in_Texture_SetData_factors(0, 0, 334, 82, 334, 82);
	UI_BUTTON.Window_SetData_factors(340, 240, UI_BUTTON.m_for_update_Rects.x, UI_BUTTON.m_for_update_Rects.y); // 텍스쳐 시작점 왼위점 좌표 + 텍스쳐 가로-세로 크기.
	UI_BUTTON.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/main_start_dis.bmp");
	

	return true;
};


bool	TSceneLobby::Frame()
{

	if (340 <I_Input.m_MousePos.x && I_Input.m_MousePos.x<470 && 240<I_Input.m_MousePos.y && I_Input.m_MousePos.y<300)
	{
		UI_BUTTON.m_bDead = true;
	}


	if (UI_BUTTON.m_bDead)
	{
		UI_BUTTON.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/main_start_pus.bmp");
		
		if (I_Input.Key(VK_LBUTTON) && 340 <I_Input.m_MousePos.x && I_Input.m_MousePos.x<470 && 240<I_Input.m_MousePos.y && I_Input.m_MousePos.y<300)
		{
			UI_BUTTON.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/main_start_sel.bmp");
			m_bNextSceneStart = true;
		}
	}

	return true;
};


bool	TSceneLobby::Render()
{

	Lobby_Background.Render(g_pContext);
	UI_BUTTON.Render(g_pContext);

	return true;
};

bool	TSceneLobby::Release()
{
	return true;
};
TSceneLobby::TSceneLobby()
{
	m_iSceneID = GAME_SCENE_LOBBY;
	m_bNextSceneStart = false;
}
TSceneLobby::~TSceneLobby()
{

}
























class TSceneGame : public TScene
{
public:
	Background				Game_Background;
	THeroObj				m_Actor;      SimpleVertex          N_VertexList[6];
	Boy_NPC					m_Boy_NPC;    SimpleVertex        N_VertexList_2[6];

	Box                    UI_Bullet_1;
	Box                    UI_Bullet_2;
	Box                    UI_Bullet_3;
	Box                    UI_Bullet_4;
	Box                    UI_Bullet_5;
	Box                    UI_Bullet_6;
	Box                    UI_Bullet_7;
	Box                    UI_Bullet_8;

	Gun_Bullet            Bullet_F1; SimpleVertex        N_VertexList_F1[6];
	Gun_Bullet            Bullet_F2; SimpleVertex        N_VertexList_F2[6];
	Gun_Bullet            Bullet_F3; SimpleVertex        N_VertexList_F3[6];
	Gun_Bullet            Bullet_F4; SimpleVertex        N_VertexList_F4[6];
	Gun_Bullet            Bullet_C1; SimpleVertex        N_VertexList_C1[6];
	Gun_Bullet            Bullet_C2; SimpleVertex        N_VertexList_C2[6];
	Gun_Bullet            Bullet_C3; SimpleVertex        N_VertexList_C3[6];
	Gun_Bullet            Bullet_C4; SimpleVertex        N_VertexList_C4[6];

	Gun_Bullet            Bullet_Ghost_1; SimpleVertex        N_VertexList_G1[6];
	Gun_Bullet            Bullet_Ghost_2; SimpleVertex        N_VertexList_G2[6];
	Gun_Bullet            Bullet_Ghost_3; SimpleVertex        N_VertexList_G3[6];
	Gun_Bullet            Bullet_Ghost_4; SimpleVertex        N_VertexList_G4[6];





	Box_Alive			Box_Alive;
	Box					Treasure_Box;




public:
	virtual bool    Init();
	bool    Frame();
	bool    Render();
	bool    Release();

public:
	TSceneGame();
	virtual ~TSceneGame();
};



bool   TSceneGame::Init()
{
	Game_Background.in_Texture_SetData_factors(0, 0, 900, 500, 900, 500);
	Game_Background.m_for_update_Rects.x = g_rtClient.right;    Game_Background.m_for_update_Rects.y = g_rtClient.bottom;
	Game_Background.Window_SetData_factors(0, 0, Game_Background.m_for_update_Rects.x, Game_Background.m_for_update_Rects.y);
	Game_Background.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/background.bmp");

	Treasure_Box.in_Texture_SetData_factors(0, 0, 100, 75, 100, 75);
	Treasure_Box.m_for_update_Rects.x = g_rtClient.right / 10;    Treasure_Box.m_for_update_Rects.y = g_rtClient.bottom / 8;
	Treasure_Box.Window_SetData_factors(390, 275, Treasure_Box.m_for_update_Rects.x, Treasure_Box.m_for_update_Rects.y);
	Treasure_Box.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Treasure_Close_100_75.png");
	

	Box_Alive.in_Texture_SetData_factors(0, 0, 125, 127, 125, 127);
	Box_Alive.m_for_update_Rects.x = g_rtClient.right/7;    Box_Alive.m_for_update_Rects.y = g_rtClient.bottom / 4;
	Box_Alive.Window_SetData_factors(760, 290, Box_Alive.m_for_update_Rects.x, Box_Alive.m_for_update_Rects.y);
	Box_Alive.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Alter.png");



	UI_Bullet_1.in_Texture_SetData_factors(0, 0, 120, 40, 120, 40);
	UI_Bullet_1.m_for_update_Rects.x = g_rtClient.right / 10;    UI_Bullet_1.m_for_update_Rects.y = g_rtClient.bottom / 12;
	UI_Bullet_1.Window_SetData_factors(10, 30, UI_Bullet_1.m_for_update_Rects.x, UI_Bullet_1.m_for_update_Rects.y);
	UI_Bullet_1.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/gun_bullet_F.png");

	UI_Bullet_2.in_Texture_SetData_factors(0, 0, 120, 40, 120, 40);
	UI_Bullet_2.m_for_update_Rects.x = g_rtClient.right / 10;    UI_Bullet_2.m_for_update_Rects.y = g_rtClient.bottom / 12;
	UI_Bullet_2.Window_SetData_factors(10, 80, UI_Bullet_2.m_for_update_Rects.x, UI_Bullet_2.m_for_update_Rects.y);
	UI_Bullet_2.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/gun_bullet_F.png");

	UI_Bullet_3.in_Texture_SetData_factors(0, 0, 120, 40, 120, 40);
	UI_Bullet_3.m_for_update_Rects.x = g_rtClient.right / 10;    UI_Bullet_3.m_for_update_Rects.y = g_rtClient.bottom / 12;
	UI_Bullet_3.Window_SetData_factors(10, 130, UI_Bullet_3.m_for_update_Rects.x, UI_Bullet_3.m_for_update_Rects.y);
	UI_Bullet_3.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/gun_bullet_F.png");

	UI_Bullet_4.in_Texture_SetData_factors(0, 0, 120, 40, 120, 40);
	UI_Bullet_4.m_for_update_Rects.x = g_rtClient.right / 10;    UI_Bullet_4.m_for_update_Rects.y = g_rtClient.bottom / 12;
	UI_Bullet_4.Window_SetData_factors(10, 180, UI_Bullet_4.m_for_update_Rects.x, UI_Bullet_4.m_for_update_Rects.y);
	UI_Bullet_4.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/gun_bullet_F.png");


	UI_Bullet_5.in_Texture_SetData_factors(0, 0, 120, 40, 120, 40);
	UI_Bullet_5.m_for_update_Rects.x = g_rtClient.right / 10;    UI_Bullet_5.m_for_update_Rects.y = g_rtClient.bottom / 10;
	UI_Bullet_5.Window_SetData_factors(800, 30, UI_Bullet_5.m_for_update_Rects.x, UI_Bullet_5.m_for_update_Rects.y);
	UI_Bullet_5.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/gun_bullet_C.png");

	UI_Bullet_6.in_Texture_SetData_factors(0, 0, 120, 40, 120, 40);
	UI_Bullet_6.m_for_update_Rects.x = g_rtClient.right / 10;    UI_Bullet_6.m_for_update_Rects.y = g_rtClient.bottom / 10;
	UI_Bullet_6.Window_SetData_factors(800, 80, UI_Bullet_6.m_for_update_Rects.x, UI_Bullet_6.m_for_update_Rects.y);
	UI_Bullet_6.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/gun_bullet_C.png");

	UI_Bullet_7.in_Texture_SetData_factors(0, 0, 120, 40, 120, 40);
	UI_Bullet_7.m_for_update_Rects.x = g_rtClient.right / 10;    UI_Bullet_7.m_for_update_Rects.y = g_rtClient.bottom / 10;
	UI_Bullet_7.Window_SetData_factors(800, 130, UI_Bullet_7.m_for_update_Rects.x, UI_Bullet_7.m_for_update_Rects.y);
	UI_Bullet_7.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/gun_bullet_C.png");

	UI_Bullet_8.in_Texture_SetData_factors(0, 0, 120, 40, 120, 40);
	UI_Bullet_8.m_for_update_Rects.x = g_rtClient.right / 10;    UI_Bullet_8.m_for_update_Rects.y = g_rtClient.bottom / 10;
	UI_Bullet_8.Window_SetData_factors(800, 180, UI_Bullet_8.m_for_update_Rects.x, UI_Bullet_8.m_for_update_Rects.y);
	UI_Bullet_8.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/gun_bullet_C.png");


	
	
	Bullet_F1.in_Texture_SetData_factors(225, 141, 32, 38, 400, 300);
	Bullet_F1.m_for_update_Rects.x = g_rtClient.right / 15;    Bullet_F1.m_for_update_Rects.y = g_rtClient.bottom / 15;
	Bullet_F1.Window_SetData_factors(10, 30, Bullet_F1.m_for_update_Rects.x, Bullet_F1.m_for_update_Rects.y);
	Bullet_F1.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/bitmap1.png");

	Bullet_F2.in_Texture_SetData_factors(225, 141, 32, 38, 400, 300);
	Bullet_F2.m_for_update_Rects.x = g_rtClient.right / 15;    Bullet_F2.m_for_update_Rects.y = g_rtClient.bottom / 15;
	Bullet_F2.Window_SetData_factors(10, 80, Bullet_F2.m_for_update_Rects.x, Bullet_F2.m_for_update_Rects.y);
	Bullet_F2.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/bitmap1.png");

	Bullet_F3.in_Texture_SetData_factors(225, 141, 32, 38, 400, 300);
	Bullet_F3.m_for_update_Rects.x = g_rtClient.right / 15;    Bullet_F3.m_for_update_Rects.y = g_rtClient.bottom / 15;
	Bullet_F3.Window_SetData_factors(10, 130, Bullet_F3.m_for_update_Rects.x, Bullet_F3.m_for_update_Rects.y);
	Bullet_F3.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/bitmap1.png");

	Bullet_F4.in_Texture_SetData_factors(225, 141, 32, 38, 400, 300);
	Bullet_F4.m_for_update_Rects.x = g_rtClient.right / 15;    Bullet_F4.m_for_update_Rects.y = g_rtClient.bottom / 15;
	Bullet_F4.Window_SetData_factors(10, 180, Bullet_F4.m_for_update_Rects.x, Bullet_F4.m_for_update_Rects.y);
	Bullet_F4.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/bitmap1.png");

	Bullet_C1.in_Texture_SetData_factors(253, 61, 10, 12, 400, 300);
	Bullet_C1.m_for_update_Rects.x = g_rtClient.right / 20;    Bullet_C1.m_for_update_Rects.y = g_rtClient.bottom / 20;
	Bullet_C1.Window_SetData_factors(815, 45, Bullet_C1.m_for_update_Rects.x, Bullet_C1.m_for_update_Rects.y);
	Bullet_C1.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/bitmap1.png");

	Bullet_C2.in_Texture_SetData_factors(253, 61, 10, 12, 400, 300);
	Bullet_C2.m_for_update_Rects.x = g_rtClient.right / 20;    Bullet_C2.m_for_update_Rects.y = g_rtClient.bottom / 20;
	Bullet_C2.Window_SetData_factors(815, 95, Bullet_C2.m_for_update_Rects.x, Bullet_C2.m_for_update_Rects.y);
	Bullet_C2.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/bitmap1.png");

	Bullet_C3.in_Texture_SetData_factors(253, 61, 10, 12, 400, 300);
	Bullet_C3.m_for_update_Rects.x = g_rtClient.right / 20;    Bullet_C3.m_for_update_Rects.y = g_rtClient.bottom / 20;
	Bullet_C3.Window_SetData_factors(815, 145, Bullet_C3.m_for_update_Rects.x, Bullet_C3.m_for_update_Rects.y);
	Bullet_C3.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/bitmap1.png");

	Bullet_C4.in_Texture_SetData_factors(253, 61, 10, 12, 400, 300);
	Bullet_C4.m_for_update_Rects.x = g_rtClient.right / 20;    Bullet_C4.m_for_update_Rects.y = g_rtClient.bottom / 20;
	Bullet_C4.Window_SetData_factors(815, 195, Bullet_C4.m_for_update_Rects.x, Bullet_C4.m_for_update_Rects.y);
	Bullet_C4.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/bitmap1.png");




	Bullet_Ghost_1.in_Texture_SetData_factors(0, 0, 67, 79, 67, 79);
	Bullet_Ghost_1.m_for_update_Rects.x = g_rtClient.right / 10;    Bullet_Ghost_1.m_for_update_Rects.y = g_rtClient.bottom / 5;
	Bullet_Ghost_1.Window_SetData_factors(790, 310, Bullet_Ghost_1.m_for_update_Rects.x, Bullet_Ghost_1.m_for_update_Rects.y);
	Bullet_Ghost_1.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Duskull.png");

	Bullet_Ghost_2.in_Texture_SetData_factors(0, 0, 67, 79, 67, 79);
	Bullet_Ghost_2.m_for_update_Rects.x = g_rtClient.right / 10;    Bullet_Ghost_2.m_for_update_Rects.y = g_rtClient.bottom / 5;
	Bullet_Ghost_2.Window_SetData_factors(790, 310, Bullet_Ghost_2.m_for_update_Rects.x, Bullet_Ghost_2.m_for_update_Rects.y);
	Bullet_Ghost_2.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Duskull.png");

	Bullet_Ghost_3.in_Texture_SetData_factors(0, 0, 67, 79, 67, 79);
	Bullet_Ghost_3.m_for_update_Rects.x = g_rtClient.right / 10;    Bullet_Ghost_3.m_for_update_Rects.y = g_rtClient.bottom / 5;
	Bullet_Ghost_3.Window_SetData_factors(790, 310, Bullet_Ghost_3.m_for_update_Rects.x, Bullet_Ghost_3.m_for_update_Rects.y);
	Bullet_Ghost_3.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Duskull.png");

	Bullet_Ghost_4.in_Texture_SetData_factors(0, 0, 67, 79, 67, 79);
	Bullet_Ghost_4.m_for_update_Rects.x = g_rtClient.right / 10;    Bullet_Ghost_4.m_for_update_Rects.y = g_rtClient.bottom / 5;
	Bullet_Ghost_4.Window_SetData_factors(790, 310, Bullet_Ghost_4.m_for_update_Rects.x, Bullet_Ghost_4.m_for_update_Rects.y);
	Bullet_Ghost_4.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Duskull.png");



	m_Boy_NPC.m_for_update_Rects.x = g_rtClient.right / 9;    m_Boy_NPC.m_for_update_Rects.y = g_rtClient.bottom / 9;
	m_Boy_NPC.in_Texture_SetData_factors(91, 2, 57, 92, 753, 532);
	m_Boy_NPC.Window_SetData_factors(0, 350, m_Boy_NPC.m_for_update_Rects.x, m_Boy_NPC.m_for_update_Rects.y); // 텍스쳐 시작점 왼위점 좌표 + 텍스쳐 가로-세로 크기.
	m_Boy_NPC.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy.png");



	m_Actor.m_for_update_Rects.x = g_rtClient.right / 9;    m_Actor.m_for_update_Rects.y = g_rtClient.bottom / 9;
	m_Actor.in_Texture_SetData_factors(20, 6, 60, 93, 758, 537);
	m_Actor.Window_SetData_factors(0, 350, m_Actor.m_for_update_Rects.x, m_Actor.m_for_update_Rects.y); // 텍스쳐 시작점 왼위점 좌표 + 텍스쳐 가로-세로 크기.
	m_Actor.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Girl_Right.png");

	return true;
};

bool    TSceneGame::Frame()
{
		static float fAngle = 0.0f;

		if (I_Input.Key('A'))
		{
			m_Actor.Face_Direction = 1;
			m_Actor.left_walk();
			memcpy(N_VertexList, m_Actor.m_VertexList, sizeof(SimpleVertex) * 6);
			m_Actor.MoveX(-g_fSecPerFrame * 0.3f);
		}

		if (I_Input.Key('D'))
		{
			m_Actor.Face_Direction = 2;
			m_Actor.right_walk();
			memcpy(N_VertexList, m_Actor.m_VertexList, sizeof(SimpleVertex) * 6);
			m_Actor.MoveX(g_fSecPerFrame*0.3f);
		}

		if (I_Input.Key('W'))
		{
			m_Actor.MoveY(g_fSecPerFrame * 0.3f);
		}

		if (I_Input.Key('S'))
		{
			m_Actor.MoveY(-g_fSecPerFrame * 0.3f);
		}


		if (I_Input.Key('K') || I_Input.Key('L'))
		{
			m_Actor.Gun_step = 1;

			if (m_Actor.Face_Direction == 1) { m_Actor.MoveX(g_fSecPerFrame*0.3f); }
			else if (m_Actor.Face_Direction == 2) { m_Actor.MoveX(-g_fSecPerFrame * 0.3f); }
		}
		m_Actor.shot();     memcpy(N_VertexList, m_Actor.m_VertexList, sizeof(SimpleVertex) * 6);


		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = m_Actor.m_VertexList[iV].x;
			vertex.y = m_Actor.m_VertexList[iV].y;

			vertex.x -= m_Actor.m_vCenter.x;
			vertex.y -= m_Actor.m_vCenter.y;
			float S = sinf(fAngle);
			float C = cosf(fAngle);
			N_VertexList[iV].x = vertex.x * C + vertex.y * S;
			N_VertexList[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList[iV].x += m_Actor.m_vCenter.x;
			N_VertexList[iV].y += m_Actor.m_vCenter.y;
		}
		g_pContext->UpdateSubresource(m_Actor.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList, 0, 0);



		///////////////////////////////////////////////////////////////////////////////////////

		if (I_Input.Key(VK_LBUTTON))
		{
			m_Boy_NPC.m_bDead = true;
			m_Boy_NPC.m_Collision_number = 1;
		}

		if (m_Boy_NPC.m_bDead == true)
		{
			m_Boy_NPC.frame();
			if (m_Boy_NPC.walk_step == 0) { m_Boy_NPC.MoveX(g_fSecPerFrame*0.1f); }        if (m_Boy_NPC.walk_step == 1) { m_Boy_NPC.MoveX(g_fSecPerFrame*0.1f); }
			if (m_Boy_NPC.walk_step == 2) { m_Boy_NPC.MoveX(g_fSecPerFrame*0.1f); }        if (m_Boy_NPC.walk_step == 3) { m_Boy_NPC.MoveX(g_fSecPerFrame*0.1f); }
			if (m_Boy_NPC.walk_step == 4) { m_Boy_NPC.MoveX(g_fSecPerFrame*0.1f); }        if (m_Boy_NPC.walk_step == 5) { m_Boy_NPC.MoveX(g_fSecPerFrame*0.1f); }
			if (m_Boy_NPC.walk_step == 6) { m_Boy_NPC.MoveX(g_fSecPerFrame*0.1f); }        if (m_Boy_NPC.walk_step == 7) { m_Boy_NPC.MoveX(g_fSecPerFrame*0.1f); }
			if (m_Boy_NPC.walk_step == 8) { m_Boy_NPC.MoveX(g_fSecPerFrame*0.1f); }        if (m_Boy_NPC.walk_step == 9) { m_Boy_NPC.MoveX(g_fSecPerFrame*0.1f); }
		}
		memcpy(N_VertexList_2, m_Boy_NPC.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = m_Boy_NPC.m_VertexList[iV].x;
			vertex.y = m_Boy_NPC.m_VertexList[iV].y;
			vertex.x -= m_Boy_NPC.m_vCenter.x;
			vertex.y -= m_Boy_NPC.m_vCenter.y;
			float S = sinf(fAngle);
			float C = cosf(fAngle);
			N_VertexList_2[iV].x = vertex.x * C + vertex.y * S;
			N_VertexList_2[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_2[iV].x += m_Boy_NPC.m_vCenter.x;
			N_VertexList_2[iV].y += m_Boy_NPC.m_vCenter.y;
		}
		g_pContext->UpdateSubresource(m_Boy_NPC.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_2, 0, 0);

		////////////////////////////////////////////////////////////////////////////////////////////////////////


		if (I_Input.Key('K') == KEY_PUSH)
		{
			static int count_K = 1;
			if (count_K == 1) { Bullet_F1.Bullet_Go = true; }
			if (count_K == 2) { Bullet_F2.Bullet_Go = true; }
			if (count_K == 3) { Bullet_F3.Bullet_Go = true; }
			if (count_K == 4) { Bullet_F4.Bullet_Go = true; }
			count_K++;
		}

		if (I_Input.Key('L') == KEY_PUSH)
		{
			static int count_L = 1;
			if (count_L == 1) { Bullet_C1.Bullet_Go = true; }
			if (count_L == 2) { Bullet_C2.Bullet_Go = true; }
			if (count_L == 3) { Bullet_C3.Bullet_Go = true; }
			if (count_L == 4) { Bullet_C4.Bullet_Go = true; }
			count_L++;
		}
		//////////////////////////////////////////////////////

		if (Bullet_F1.Bullet_Go == true && m_Actor.Face_Direction==1)
		{	Bullet_F1.Bullet_Go = false; Bullet_F1.Face_Direction1_flag = true;
			Bullet_F1.m_VertexList[0].x = m_Actor.m_VertexList[0].x - 30 / 900 ; Bullet_F1.m_VertexList[0].y = m_Actor.m_VertexList[0].y - 5 / 900;
			Bullet_F1.m_VertexList[1].x = m_Actor.m_VertexList[1].x - 30 / 900 ; Bullet_F1.m_VertexList[1].y = m_Actor.m_VertexList[1].y - 5 / 900;
			Bullet_F1.m_VertexList[2].x = m_Actor.m_VertexList[2].x - 30 / 900 ; Bullet_F1.m_VertexList[2].y = m_Actor.m_VertexList[2].y - 5 / 900;
			Bullet_F1.m_VertexList[3].x = m_Actor.m_VertexList[3].x - 30 / 900 ; Bullet_F1.m_VertexList[3].y = m_Actor.m_VertexList[3].y - 5 / 900;
			Bullet_F1.m_VertexList[4].x = m_Actor.m_VertexList[4].x - 30 / 900 ; Bullet_F1.m_VertexList[4].y = m_Actor.m_VertexList[4].y - 5 / 900;
			Bullet_F1.m_VertexList[5].x = m_Actor.m_VertexList[5].x - 30 / 900 ; Bullet_F1.m_VertexList[5].y = m_Actor.m_VertexList[5].y - 5 / 900;
			Bullet_F1.m_VertexList[6].x = m_Actor.m_VertexList[6].x - 30 / 900 ; Bullet_F1.m_VertexList[6].y = m_Actor.m_VertexList[6].y - 5 / 900;}

		if (Bullet_F1.Bullet_Go == true && m_Actor.Face_Direction == 2)
		{	Bullet_F1.Bullet_Go = false; Bullet_F1.Face_Direction2_flag = true;
			Bullet_F1.m_VertexList[0].x = m_Actor.m_VertexList[0].x + 30 / 900 ; Bullet_F1.m_VertexList[0].y = m_Actor.m_VertexList[0].y + 5 / 900;
			Bullet_F1.m_VertexList[1].x = m_Actor.m_VertexList[1].x + 30 / 900 ; Bullet_F1.m_VertexList[1].y = m_Actor.m_VertexList[1].y + 5 / 900;
			Bullet_F1.m_VertexList[2].x = m_Actor.m_VertexList[2].x + 30 / 900 ; Bullet_F1.m_VertexList[2].y = m_Actor.m_VertexList[2].y + 5 / 900;
			Bullet_F1.m_VertexList[3].x = m_Actor.m_VertexList[3].x + 30 / 900 ; Bullet_F1.m_VertexList[3].y = m_Actor.m_VertexList[3].y + 5 / 900;
			Bullet_F1.m_VertexList[4].x = m_Actor.m_VertexList[4].x + 30 / 900 ; Bullet_F1.m_VertexList[4].y = m_Actor.m_VertexList[4].y + 5 / 900;
			Bullet_F1.m_VertexList[5].x = m_Actor.m_VertexList[5].x + 30 / 900 ; Bullet_F1.m_VertexList[5].y = m_Actor.m_VertexList[5].y + 5 / 900;
			Bullet_F1.m_VertexList[6].x = m_Actor.m_VertexList[6].x + 30 / 900 ; Bullet_F1.m_VertexList[6].y = m_Actor.m_VertexList[6].y + 5 / 900;}

		if(Bullet_F1.Face_Direction1_flag == true)
		{	Bullet_F1.frame_F();
			if (Bullet_F1.bullet_step == 0) { Bullet_F1.MoveX(-g_fSecPerFrame*1.0f); }        if (Bullet_F1.bullet_step == 1) { Bullet_F1.MoveX(-g_fSecPerFrame*1.0f); }
			if (Bullet_F1.bullet_step == 2) { Bullet_F1.MoveX(-g_fSecPerFrame*1.0f); }        if (Bullet_F1.bullet_step == 3) { Bullet_F1.MoveX(-g_fSecPerFrame*1.0f); }
			if (Bullet_F1.bullet_step == 4) { Bullet_F1.MoveX(-g_fSecPerFrame*1.0f); }        if (Bullet_F1.bullet_step == 5) { Bullet_F1.MoveX(-g_fSecPerFrame*1.0f); }
			if (Bullet_F1.bullet_step == 6) { Bullet_F1.MoveX(-g_fSecPerFrame*1.0f); }	}	

		if (Bullet_F1.Face_Direction2_flag == true)
		{	Bullet_F1.frame_F();
			if (Bullet_F1.bullet_step == 0) { Bullet_F1.MoveX(g_fSecPerFrame*1.0f); }        if (Bullet_F1.bullet_step == 1) { Bullet_F1.MoveX(g_fSecPerFrame*1.0f); }
			if (Bullet_F1.bullet_step == 2) { Bullet_F1.MoveX(g_fSecPerFrame*1.0f); }        if (Bullet_F1.bullet_step == 3) { Bullet_F1.MoveX(g_fSecPerFrame*1.0f); }
			if (Bullet_F1.bullet_step == 4) { Bullet_F1.MoveX(g_fSecPerFrame*1.0f); }        if (Bullet_F1.bullet_step == 5) { Bullet_F1.MoveX(g_fSecPerFrame*1.0f); }
			if (Bullet_F1.bullet_step == 6) { Bullet_F1.MoveX(g_fSecPerFrame*1.0f); }}	
		
		memcpy(N_VertexList_F1, Bullet_F1.m_VertexList, sizeof(SimpleVertex) * 6);
		for (int iV = 0; iV < 6; iV++)
		{	D3DVECTOR vertex;
			vertex.x = Bullet_F1.m_VertexList[iV].x; vertex.y = Bullet_F1.m_VertexList[iV].y;
			vertex.x -= Bullet_F1.m_vCenter.x;		 vertex.y -= Bullet_F1.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_F1[iV].x = vertex.x * C + vertex.y * S; N_VertexList_F1[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_F1[iV].x += Bullet_F1.m_vCenter.x;		 N_VertexList_F1[iV].y += Bullet_F1.m_vCenter.y;}
		g_pContext->UpdateSubresource(Bullet_F1.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_F1, 0, 0);

		///////////////////////////////////////////////////////////


		if (Bullet_F2.Bullet_Go == true && m_Actor.Face_Direction == 1)
		{
			Bullet_F2.Bullet_Go = false; Bullet_F2.Face_Direction1_flag = true;
			Bullet_F2.m_VertexList[0].x = m_Actor.m_VertexList[0].x - 30 / 900; Bullet_F2.m_VertexList[0].y = m_Actor.m_VertexList[0].y - 5 / 900;
			Bullet_F2.m_VertexList[1].x = m_Actor.m_VertexList[1].x - 30 / 900; Bullet_F2.m_VertexList[1].y = m_Actor.m_VertexList[1].y - 5 / 900;
			Bullet_F2.m_VertexList[2].x = m_Actor.m_VertexList[2].x - 30 / 900; Bullet_F2.m_VertexList[2].y = m_Actor.m_VertexList[2].y - 5 / 900;
			Bullet_F2.m_VertexList[3].x = m_Actor.m_VertexList[3].x - 30 / 900; Bullet_F2.m_VertexList[3].y = m_Actor.m_VertexList[3].y - 5 / 900;
			Bullet_F2.m_VertexList[4].x = m_Actor.m_VertexList[4].x - 30 / 900; Bullet_F2.m_VertexList[4].y = m_Actor.m_VertexList[4].y - 5 / 900;
			Bullet_F2.m_VertexList[5].x = m_Actor.m_VertexList[5].x - 30 / 900; Bullet_F2.m_VertexList[5].y = m_Actor.m_VertexList[5].y - 5 / 900;
			Bullet_F2.m_VertexList[6].x = m_Actor.m_VertexList[6].x - 30 / 900; Bullet_F2.m_VertexList[6].y = m_Actor.m_VertexList[6].y - 5 / 900;
		}

		if (Bullet_F2.Bullet_Go == true && m_Actor.Face_Direction == 2)
		{
			Bullet_F2.Bullet_Go = false; Bullet_F2.Face_Direction2_flag = true;
			Bullet_F2.m_VertexList[0].x = m_Actor.m_VertexList[0].x + 30 / 900; Bullet_F2.m_VertexList[0].y = m_Actor.m_VertexList[0].y + 5 / 900;
			Bullet_F2.m_VertexList[1].x = m_Actor.m_VertexList[1].x + 30 / 900; Bullet_F2.m_VertexList[1].y = m_Actor.m_VertexList[1].y + 5 / 900;
			Bullet_F2.m_VertexList[2].x = m_Actor.m_VertexList[2].x + 30 / 900; Bullet_F2.m_VertexList[2].y = m_Actor.m_VertexList[2].y + 5 / 900;
			Bullet_F2.m_VertexList[3].x = m_Actor.m_VertexList[3].x + 30 / 900; Bullet_F2.m_VertexList[3].y = m_Actor.m_VertexList[3].y + 5 / 900;
			Bullet_F2.m_VertexList[4].x = m_Actor.m_VertexList[4].x + 30 / 900; Bullet_F2.m_VertexList[4].y = m_Actor.m_VertexList[4].y + 5 / 900;
			Bullet_F2.m_VertexList[5].x = m_Actor.m_VertexList[5].x + 30 / 900; Bullet_F2.m_VertexList[5].y = m_Actor.m_VertexList[5].y + 5 / 900;
			Bullet_F2.m_VertexList[6].x = m_Actor.m_VertexList[6].x + 30 / 900; Bullet_F2.m_VertexList[6].y = m_Actor.m_VertexList[6].y + 5 / 900;
		}

		if (Bullet_F2.Face_Direction1_flag == true)
		{
			Bullet_F2.frame_F();
			if (Bullet_F2.bullet_step == 0) { Bullet_F2.MoveX(-g_fSecPerFrame * 1.0f); }        if (Bullet_F2.bullet_step == 1) { Bullet_F2.MoveX(-g_fSecPerFrame * 1.0f); }
			if (Bullet_F2.bullet_step == 2) { Bullet_F2.MoveX(-g_fSecPerFrame * 1.0f); }        if (Bullet_F2.bullet_step == 3) { Bullet_F2.MoveX(-g_fSecPerFrame * 1.0f); }
			if (Bullet_F2.bullet_step == 4) { Bullet_F2.MoveX(-g_fSecPerFrame * 1.0f); }        if (Bullet_F2.bullet_step == 5) { Bullet_F2.MoveX(-g_fSecPerFrame * 1.0f); }
			if (Bullet_F2.bullet_step == 6) { Bullet_F2.MoveX(-g_fSecPerFrame * 1.0f); }
		}

		if (Bullet_F2.Face_Direction2_flag == true)
		{
			Bullet_F2.frame_F();
			if (Bullet_F2.bullet_step == 0) { Bullet_F2.MoveX(g_fSecPerFrame*1.0f); }        if (Bullet_F2.bullet_step == 1) { Bullet_F2.MoveX(g_fSecPerFrame*1.0f); }
			if (Bullet_F2.bullet_step == 2) { Bullet_F2.MoveX(g_fSecPerFrame*1.0f); }        if (Bullet_F2.bullet_step == 3) { Bullet_F2.MoveX(g_fSecPerFrame*1.0f); }
			if (Bullet_F2.bullet_step == 4) { Bullet_F2.MoveX(g_fSecPerFrame*1.0f); }        if (Bullet_F2.bullet_step == 5) { Bullet_F2.MoveX(g_fSecPerFrame*1.0f); }
			if (Bullet_F2.bullet_step == 6) { Bullet_F2.MoveX(g_fSecPerFrame*1.0f); }
		}

		memcpy(N_VertexList_F2, Bullet_F2.m_VertexList, sizeof(SimpleVertex) * 6);
		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_F2.m_VertexList[iV].x; vertex.y = Bullet_F2.m_VertexList[iV].y;
			vertex.x -= Bullet_F2.m_vCenter.x;		 vertex.y -= Bullet_F2.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_F2[iV].x = vertex.x * C + vertex.y * S; N_VertexList_F2[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_F2[iV].x += Bullet_F2.m_vCenter.x;		 N_VertexList_F2[iV].y += Bullet_F2.m_vCenter.y;
		}
		g_pContext->UpdateSubresource(Bullet_F2.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_F2, 0, 0);

		///////////////////////////////////////////////////////////


		if (Bullet_F3.Bullet_Go == true && m_Actor.Face_Direction == 1)
		{
			Bullet_F3.Bullet_Go = false; Bullet_F3.Face_Direction1_flag = true;
			Bullet_F3.m_VertexList[0].x = m_Actor.m_VertexList[0].x - 30 / 900; Bullet_F3.m_VertexList[0].y = m_Actor.m_VertexList[0].y - 5 / 900;
			Bullet_F3.m_VertexList[1].x = m_Actor.m_VertexList[1].x - 30 / 900; Bullet_F3.m_VertexList[1].y = m_Actor.m_VertexList[1].y - 5 / 900;
			Bullet_F3.m_VertexList[2].x = m_Actor.m_VertexList[2].x - 30 / 900; Bullet_F3.m_VertexList[2].y = m_Actor.m_VertexList[2].y - 5 / 900;
			Bullet_F3.m_VertexList[3].x = m_Actor.m_VertexList[3].x - 30 / 900; Bullet_F3.m_VertexList[3].y = m_Actor.m_VertexList[3].y - 5 / 900;
			Bullet_F3.m_VertexList[4].x = m_Actor.m_VertexList[4].x - 30 / 900; Bullet_F3.m_VertexList[4].y = m_Actor.m_VertexList[4].y - 5 / 900;
			Bullet_F3.m_VertexList[5].x = m_Actor.m_VertexList[5].x - 30 / 900; Bullet_F3.m_VertexList[5].y = m_Actor.m_VertexList[5].y - 5 / 900;
			Bullet_F3.m_VertexList[6].x = m_Actor.m_VertexList[6].x - 30 / 900; Bullet_F3.m_VertexList[6].y = m_Actor.m_VertexList[6].y - 5 / 900;
		}

		if (Bullet_F3.Bullet_Go == true && m_Actor.Face_Direction == 2)
		{
			Bullet_F3.Bullet_Go = false; Bullet_F3.Face_Direction2_flag = true;
			Bullet_F3.m_VertexList[0].x = m_Actor.m_VertexList[0].x + 30 / 900; Bullet_F3.m_VertexList[0].y = m_Actor.m_VertexList[0].y + 5 / 900;
			Bullet_F3.m_VertexList[1].x = m_Actor.m_VertexList[1].x + 30 / 900; Bullet_F3.m_VertexList[1].y = m_Actor.m_VertexList[1].y + 5 / 900;
			Bullet_F3.m_VertexList[2].x = m_Actor.m_VertexList[2].x + 30 / 900; Bullet_F3.m_VertexList[2].y = m_Actor.m_VertexList[2].y + 5 / 900;
			Bullet_F3.m_VertexList[3].x = m_Actor.m_VertexList[3].x + 30 / 900; Bullet_F3.m_VertexList[3].y = m_Actor.m_VertexList[3].y + 5 / 900;
			Bullet_F3.m_VertexList[4].x = m_Actor.m_VertexList[4].x + 30 / 900; Bullet_F3.m_VertexList[4].y = m_Actor.m_VertexList[4].y + 5 / 900;
			Bullet_F3.m_VertexList[5].x = m_Actor.m_VertexList[5].x + 30 / 900; Bullet_F3.m_VertexList[5].y = m_Actor.m_VertexList[5].y + 5 / 900;
			Bullet_F3.m_VertexList[6].x = m_Actor.m_VertexList[6].x + 30 / 900; Bullet_F3.m_VertexList[6].y = m_Actor.m_VertexList[6].y + 5 / 900;
		}

		if (Bullet_F3.Face_Direction1_flag == true)
		{
			Bullet_F3.frame_F();
			if (Bullet_F3.bullet_step == 0) { Bullet_F3.MoveX(-g_fSecPerFrame * 1.0f); }        if (Bullet_F3.bullet_step == 1) { Bullet_F3.MoveX(-g_fSecPerFrame * 1.0f); }
			if (Bullet_F3.bullet_step == 2) { Bullet_F3.MoveX(-g_fSecPerFrame * 1.0f); }        if (Bullet_F3.bullet_step == 3) { Bullet_F3.MoveX(-g_fSecPerFrame * 1.0f); }
			if (Bullet_F3.bullet_step == 4) { Bullet_F3.MoveX(-g_fSecPerFrame * 1.0f); }        if (Bullet_F3.bullet_step == 5) { Bullet_F3.MoveX(-g_fSecPerFrame * 1.0f); }
			if (Bullet_F3.bullet_step == 6) { Bullet_F3.MoveX(-g_fSecPerFrame * 1.0f); }
		}

		if (Bullet_F3.Face_Direction2_flag == true)
		{
			Bullet_F3.frame_F();
			if (Bullet_F3.bullet_step == 0) { Bullet_F3.MoveX(g_fSecPerFrame*1.0f); }        if (Bullet_F3.bullet_step == 1) { Bullet_F3.MoveX(g_fSecPerFrame*1.0f); }
			if (Bullet_F3.bullet_step == 2) { Bullet_F3.MoveX(g_fSecPerFrame*1.0f); }        if (Bullet_F3.bullet_step == 3) { Bullet_F3.MoveX(g_fSecPerFrame*1.0f); }
			if (Bullet_F3.bullet_step == 4) { Bullet_F3.MoveX(g_fSecPerFrame*1.0f); }        if (Bullet_F3.bullet_step == 5) { Bullet_F3.MoveX(g_fSecPerFrame*1.0f); }
			if (Bullet_F3.bullet_step == 6) { Bullet_F3.MoveX(g_fSecPerFrame*1.0f); }
		}

		memcpy(N_VertexList_F3, Bullet_F3.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_F3.m_VertexList[iV].x; vertex.y = Bullet_F3.m_VertexList[iV].y;
			vertex.x -= Bullet_F3.m_vCenter.x;		 vertex.y -= Bullet_F3.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_F3[iV].x = vertex.x * C + vertex.y * S; N_VertexList_F3[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_F3[iV].x += Bullet_F3.m_vCenter.x;		 N_VertexList_F3[iV].y += Bullet_F3.m_vCenter.y;
		}
		g_pContext->UpdateSubresource(Bullet_F3.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_F3, 0, 0);
		
		////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (Bullet_F4.Bullet_Go == true && m_Actor.Face_Direction == 1)
		{
			Bullet_F4.Bullet_Go = false; Bullet_F4.Face_Direction1_flag = true;
			Bullet_F4.m_VertexList[0].x = m_Actor.m_VertexList[0].x - 30 / 900; Bullet_F4.m_VertexList[0].y = m_Actor.m_VertexList[0].y - 5 / 900;
			Bullet_F4.m_VertexList[1].x = m_Actor.m_VertexList[1].x - 30 / 900; Bullet_F4.m_VertexList[1].y = m_Actor.m_VertexList[1].y - 5 / 900;
			Bullet_F4.m_VertexList[2].x = m_Actor.m_VertexList[2].x - 30 / 900; Bullet_F4.m_VertexList[2].y = m_Actor.m_VertexList[2].y - 5 / 900;
			Bullet_F4.m_VertexList[3].x = m_Actor.m_VertexList[3].x - 30 / 900; Bullet_F4.m_VertexList[3].y = m_Actor.m_VertexList[3].y - 5 / 900;
			Bullet_F4.m_VertexList[4].x = m_Actor.m_VertexList[4].x - 30 / 900; Bullet_F4.m_VertexList[4].y = m_Actor.m_VertexList[4].y - 5 / 900;
			Bullet_F4.m_VertexList[5].x = m_Actor.m_VertexList[5].x - 30 / 900; Bullet_F4.m_VertexList[5].y = m_Actor.m_VertexList[5].y - 5 / 900;
			Bullet_F4.m_VertexList[6].x = m_Actor.m_VertexList[6].x - 30 / 900; Bullet_F4.m_VertexList[6].y = m_Actor.m_VertexList[6].y - 5 / 900;
		}

		if (Bullet_F4.Bullet_Go == true && m_Actor.Face_Direction == 2)
		{
			Bullet_F4.Bullet_Go = false; Bullet_F4.Face_Direction2_flag = true;
			Bullet_F4.m_VertexList[0].x = m_Actor.m_VertexList[0].x + 30 / 900; Bullet_F4.m_VertexList[0].y = m_Actor.m_VertexList[0].y + 5 / 900;
			Bullet_F4.m_VertexList[1].x = m_Actor.m_VertexList[1].x + 30 / 900; Bullet_F4.m_VertexList[1].y = m_Actor.m_VertexList[1].y + 5 / 900;
			Bullet_F4.m_VertexList[2].x = m_Actor.m_VertexList[2].x + 30 / 900; Bullet_F4.m_VertexList[2].y = m_Actor.m_VertexList[2].y + 5 / 900;
			Bullet_F4.m_VertexList[3].x = m_Actor.m_VertexList[3].x + 30 / 900; Bullet_F4.m_VertexList[3].y = m_Actor.m_VertexList[3].y + 5 / 900;
			Bullet_F4.m_VertexList[4].x = m_Actor.m_VertexList[4].x + 30 / 900; Bullet_F4.m_VertexList[4].y = m_Actor.m_VertexList[4].y + 5 / 900;
			Bullet_F4.m_VertexList[5].x = m_Actor.m_VertexList[5].x + 30 / 900; Bullet_F4.m_VertexList[5].y = m_Actor.m_VertexList[5].y + 5 / 900;
			Bullet_F4.m_VertexList[6].x = m_Actor.m_VertexList[6].x + 30 / 900; Bullet_F4.m_VertexList[6].y = m_Actor.m_VertexList[6].y + 5 / 900;
		}

		if (Bullet_F4.Face_Direction1_flag == true)
		{
			Bullet_F4.frame_F();
			if (Bullet_F4.bullet_step == 0) { Bullet_F4.MoveX(-g_fSecPerFrame * 1.0f); }        if (Bullet_F4.bullet_step == 1) { Bullet_F4.MoveX(-g_fSecPerFrame * 1.0f); }
			if (Bullet_F4.bullet_step == 2) { Bullet_F4.MoveX(-g_fSecPerFrame * 1.0f); }        if (Bullet_F4.bullet_step == 3) { Bullet_F4.MoveX(-g_fSecPerFrame * 1.0f); }
			if (Bullet_F4.bullet_step == 4) { Bullet_F4.MoveX(-g_fSecPerFrame * 1.0f); }        if (Bullet_F4.bullet_step == 5) { Bullet_F4.MoveX(-g_fSecPerFrame * 1.0f); }
			if (Bullet_F4.bullet_step == 6) { Bullet_F4.MoveX(-g_fSecPerFrame * 1.0f); }
		}

		if (Bullet_F4.Face_Direction2_flag == true)
		{
			Bullet_F4.frame_F();
			if (Bullet_F4.bullet_step == 0) { Bullet_F4.MoveX(g_fSecPerFrame*1.0f); }        if (Bullet_F4.bullet_step == 1) { Bullet_F4.MoveX(g_fSecPerFrame*1.0f); }
			if (Bullet_F4.bullet_step == 2) { Bullet_F4.MoveX(g_fSecPerFrame*1.0f); }        if (Bullet_F4.bullet_step == 3) { Bullet_F4.MoveX(g_fSecPerFrame*1.0f); }
			if (Bullet_F4.bullet_step == 4) { Bullet_F4.MoveX(g_fSecPerFrame*1.0f); }        if (Bullet_F4.bullet_step == 5) { Bullet_F4.MoveX(g_fSecPerFrame*1.0f); }
			if (Bullet_F4.bullet_step == 6) { Bullet_F4.MoveX(g_fSecPerFrame*1.0f); }
		}

		memcpy(N_VertexList_F4, Bullet_F4.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_F4.m_VertexList[iV].x; vertex.y = Bullet_F4.m_VertexList[iV].y;
			vertex.x -= Bullet_F4.m_vCenter.x;		 vertex.y -= Bullet_F4.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_F4[iV].x = vertex.x * C + vertex.y * S; N_VertexList_F4[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_F4[iV].x += Bullet_F4.m_vCenter.x;		 N_VertexList_F4[iV].y += Bullet_F4.m_vCenter.y;
		}
		g_pContext->UpdateSubresource(Bullet_F4.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_F4, 0, 0);

		////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (Bullet_C1.Bullet_Go == true && m_Actor.Face_Direction == 1)
		{
			Bullet_C1.Bullet_Go = false; Bullet_C1.Face_Direction1_flag = true;
			Bullet_C1.m_VertexList[0].x = m_Actor.m_VertexList[0].x - 30 / 900; Bullet_C1.m_VertexList[0].y = m_Actor.m_VertexList[0].y - 5 / 900;
			Bullet_C1.m_VertexList[1].x = m_Actor.m_VertexList[1].x - 30 / 900; Bullet_C1.m_VertexList[1].y = m_Actor.m_VertexList[1].y - 5 / 900;
			Bullet_C1.m_VertexList[2].x = m_Actor.m_VertexList[2].x - 30 / 900; Bullet_C1.m_VertexList[2].y = m_Actor.m_VertexList[2].y - 5 / 900;
			Bullet_C1.m_VertexList[3].x = m_Actor.m_VertexList[3].x - 30 / 900; Bullet_C1.m_VertexList[3].y = m_Actor.m_VertexList[3].y - 5 / 900;
			Bullet_C1.m_VertexList[4].x = m_Actor.m_VertexList[4].x - 30 / 900; Bullet_C1.m_VertexList[4].y = m_Actor.m_VertexList[4].y - 5 / 900;
			Bullet_C1.m_VertexList[5].x = m_Actor.m_VertexList[5].x - 30 / 900; Bullet_C1.m_VertexList[5].y = m_Actor.m_VertexList[5].y - 5 / 900;
			Bullet_C1.m_VertexList[6].x = m_Actor.m_VertexList[6].x - 30 / 900; Bullet_C1.m_VertexList[6].y = m_Actor.m_VertexList[6].y - 5 / 900;
		}

		if (Bullet_C1.Bullet_Go == true && m_Actor.Face_Direction == 2)
		{
			Bullet_C1.Bullet_Go = false; Bullet_C1.Face_Direction2_flag = true;
			Bullet_C1.m_VertexList[0].x = m_Actor.m_VertexList[0].x + 30 / 900; Bullet_C1.m_VertexList[0].y = m_Actor.m_VertexList[0].y + 5 / 900;
			Bullet_C1.m_VertexList[1].x = m_Actor.m_VertexList[1].x + 30 / 900; Bullet_C1.m_VertexList[1].y = m_Actor.m_VertexList[1].y + 5 / 900;
			Bullet_C1.m_VertexList[2].x = m_Actor.m_VertexList[2].x + 30 / 900; Bullet_C1.m_VertexList[2].y = m_Actor.m_VertexList[2].y + 5 / 900;
			Bullet_C1.m_VertexList[3].x = m_Actor.m_VertexList[3].x + 30 / 900; Bullet_C1.m_VertexList[3].y = m_Actor.m_VertexList[3].y + 5 / 900;
			Bullet_C1.m_VertexList[4].x = m_Actor.m_VertexList[4].x + 30 / 900; Bullet_C1.m_VertexList[4].y = m_Actor.m_VertexList[4].y + 5 / 900;
			Bullet_C1.m_VertexList[5].x = m_Actor.m_VertexList[5].x + 30 / 900; Bullet_C1.m_VertexList[5].y = m_Actor.m_VertexList[5].y + 5 / 900;
			Bullet_C1.m_VertexList[6].x = m_Actor.m_VertexList[6].x + 30 / 900; Bullet_C1.m_VertexList[6].y = m_Actor.m_VertexList[6].y + 5 / 900;
		}

		if (Bullet_C1.Face_Direction1_flag == true)
		{
			Bullet_C1.frame_C();
			if (Bullet_C1.bullet_step == 0) { Bullet_C1.MoveX(-g_fSecPerFrame * 1.0f); }        if (Bullet_C1.bullet_step == 1) { Bullet_C1.MoveX(-g_fSecPerFrame * 1.0f); }
			if (Bullet_C1.bullet_step == 2) { Bullet_C1.MoveX(-g_fSecPerFrame * 1.0f); }        if (Bullet_C1.bullet_step == 3) { Bullet_C1.MoveX(-g_fSecPerFrame * 1.0f); }
			if (Bullet_C1.bullet_step == 4) { Bullet_C1.MoveX(-g_fSecPerFrame * 1.0f); }        if (Bullet_C1.bullet_step == 5) { Bullet_C1.MoveX(-g_fSecPerFrame * 1.0f); }
			if (Bullet_C1.bullet_step == 6) { Bullet_C1.MoveX(-g_fSecPerFrame * 1.0f); }
		}

		if (Bullet_C1.Face_Direction2_flag == true)
		{
			Bullet_C1.frame_C();
			if (Bullet_C1.bullet_step == 0) { Bullet_C1.MoveX(g_fSecPerFrame*1.0f); }        if (Bullet_C1.bullet_step == 1) { Bullet_C1.MoveX(g_fSecPerFrame*1.0f); }
			if (Bullet_C1.bullet_step == 2) { Bullet_C1.MoveX(g_fSecPerFrame*1.0f); }        if (Bullet_C1.bullet_step == 3) { Bullet_C1.MoveX(g_fSecPerFrame*1.0f); }
			if (Bullet_C1.bullet_step == 4) { Bullet_C1.MoveX(g_fSecPerFrame*1.0f); }        if (Bullet_C1.bullet_step == 5) { Bullet_C1.MoveX(g_fSecPerFrame*1.0f); }
			if (Bullet_C1.bullet_step == 6) { Bullet_C1.MoveX(g_fSecPerFrame*1.0f); }
		}

		memcpy(N_VertexList_C1, Bullet_C1.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_C1.m_VertexList[iV].x; vertex.y = Bullet_C1.m_VertexList[iV].y;
			vertex.x -= Bullet_C1.m_vCenter.x;		 vertex.y -= Bullet_C1.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_C1[iV].x = vertex.x * C + vertex.y * S; N_VertexList_C1[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_C1[iV].x += Bullet_C1.m_vCenter.x;		 N_VertexList_C1[iV].y += Bullet_C1.m_vCenter.y;
		}
		g_pContext->UpdateSubresource(Bullet_C1.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_C1, 0, 0);

		////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (Bullet_C2.Bullet_Go == true && m_Actor.Face_Direction == 1)
		{
			Bullet_C2.Bullet_Go = false; Bullet_C2.Face_Direction1_flag = true;
			Bullet_C2.m_VertexList[0].x = m_Actor.m_VertexList[0].x - 30 / 900; Bullet_C2.m_VertexList[0].y = m_Actor.m_VertexList[0].y - 5 / 900;
			Bullet_C2.m_VertexList[1].x = m_Actor.m_VertexList[1].x - 30 / 900; Bullet_C2.m_VertexList[1].y = m_Actor.m_VertexList[1].y - 5 / 900;
			Bullet_C2.m_VertexList[2].x = m_Actor.m_VertexList[2].x - 30 / 900; Bullet_C2.m_VertexList[2].y = m_Actor.m_VertexList[2].y - 5 / 900;
			Bullet_C2.m_VertexList[3].x = m_Actor.m_VertexList[3].x - 30 / 900; Bullet_C2.m_VertexList[3].y = m_Actor.m_VertexList[3].y - 5 / 900;
			Bullet_C2.m_VertexList[4].x = m_Actor.m_VertexList[4].x - 30 / 900; Bullet_C2.m_VertexList[4].y = m_Actor.m_VertexList[4].y - 5 / 900;
			Bullet_C2.m_VertexList[5].x = m_Actor.m_VertexList[5].x - 30 / 900; Bullet_C2.m_VertexList[5].y = m_Actor.m_VertexList[5].y - 5 / 900;
			Bullet_C2.m_VertexList[6].x = m_Actor.m_VertexList[6].x - 30 / 900; Bullet_C2.m_VertexList[6].y = m_Actor.m_VertexList[6].y - 5 / 900;
		}

		if (Bullet_C2.Bullet_Go == true && m_Actor.Face_Direction == 2)
		{
			Bullet_C2.Bullet_Go = false; Bullet_C2.Face_Direction2_flag = true;
			Bullet_C2.m_VertexList[0].x = m_Actor.m_VertexList[0].x + 30 / 900; Bullet_C2.m_VertexList[0].y = m_Actor.m_VertexList[0].y + 5 / 900;
			Bullet_C2.m_VertexList[1].x = m_Actor.m_VertexList[1].x + 30 / 900; Bullet_C2.m_VertexList[1].y = m_Actor.m_VertexList[1].y + 5 / 900;
			Bullet_C2.m_VertexList[2].x = m_Actor.m_VertexList[2].x + 30 / 900; Bullet_C2.m_VertexList[2].y = m_Actor.m_VertexList[2].y + 5 / 900;
			Bullet_C2.m_VertexList[3].x = m_Actor.m_VertexList[3].x + 30 / 900; Bullet_C2.m_VertexList[3].y = m_Actor.m_VertexList[3].y + 5 / 900;
			Bullet_C2.m_VertexList[4].x = m_Actor.m_VertexList[4].x + 30 / 900; Bullet_C2.m_VertexList[4].y = m_Actor.m_VertexList[4].y + 5 / 900;
			Bullet_C2.m_VertexList[5].x = m_Actor.m_VertexList[5].x + 30 / 900; Bullet_C2.m_VertexList[5].y = m_Actor.m_VertexList[5].y + 5 / 900;
			Bullet_C2.m_VertexList[6].x = m_Actor.m_VertexList[6].x + 30 / 900; Bullet_C2.m_VertexList[6].y = m_Actor.m_VertexList[6].y + 5 / 900;
		}

		if (Bullet_C2.Face_Direction1_flag == true)
		{
			Bullet_C2.frame_C();
			if (Bullet_C2.bullet_step == 0) { Bullet_C2.MoveX(-g_fSecPerFrame * 1.0f); }        if (Bullet_C2.bullet_step == 1) { Bullet_C2.MoveX(-g_fSecPerFrame * 1.0f); }
			if (Bullet_C2.bullet_step == 2) { Bullet_C2.MoveX(-g_fSecPerFrame * 1.0f); }        if (Bullet_C2.bullet_step == 3) { Bullet_C2.MoveX(-g_fSecPerFrame * 1.0f); }
			if (Bullet_C2.bullet_step == 4) { Bullet_C2.MoveX(-g_fSecPerFrame * 1.0f); }        if (Bullet_C2.bullet_step == 5) { Bullet_C2.MoveX(-g_fSecPerFrame * 1.0f); }
			if (Bullet_C2.bullet_step == 6) { Bullet_C2.MoveX(-g_fSecPerFrame * 1.0f); }
		}

		if (Bullet_C2.Face_Direction2_flag == true)
		{
			Bullet_C2.frame_C();
			if (Bullet_C2.bullet_step == 0) { Bullet_C2.MoveX(g_fSecPerFrame*1.0f); }        if (Bullet_C2.bullet_step == 1) { Bullet_C2.MoveX(g_fSecPerFrame*1.0f); }
			if (Bullet_C2.bullet_step == 2) { Bullet_C2.MoveX(g_fSecPerFrame*1.0f); }        if (Bullet_C2.bullet_step == 3) { Bullet_C2.MoveX(g_fSecPerFrame*1.0f); }
			if (Bullet_C2.bullet_step == 4) { Bullet_C2.MoveX(g_fSecPerFrame*1.0f); }        if (Bullet_C2.bullet_step == 5) { Bullet_C2.MoveX(g_fSecPerFrame*1.0f); }
			if (Bullet_C2.bullet_step == 6) { Bullet_C2.MoveX(g_fSecPerFrame*1.0f); }
		}

		memcpy(N_VertexList_C2, Bullet_C2.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_C2.m_VertexList[iV].x; vertex.y = Bullet_C2.m_VertexList[iV].y;
			vertex.x -= Bullet_C2.m_vCenter.x;		 vertex.y -= Bullet_C2.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_C2[iV].x = vertex.x * C + vertex.y * S; N_VertexList_C2[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_C2[iV].x += Bullet_C2.m_vCenter.x;		 N_VertexList_C2[iV].y += Bullet_C2.m_vCenter.y;
		}
		g_pContext->UpdateSubresource(Bullet_C2.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_C2, 0, 0);




		////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (Bullet_C3.Bullet_Go == true && m_Actor.Face_Direction == 1)
		{
			Bullet_C3.Bullet_Go = false; Bullet_C3.Face_Direction1_flag = true;
			Bullet_C3.m_VertexList[0].x = m_Actor.m_VertexList[0].x - 30 / 900; Bullet_C3.m_VertexList[0].y = m_Actor.m_VertexList[0].y - 5 / 900;
			Bullet_C3.m_VertexList[1].x = m_Actor.m_VertexList[1].x - 30 / 900; Bullet_C3.m_VertexList[1].y = m_Actor.m_VertexList[1].y - 5 / 900;
			Bullet_C3.m_VertexList[2].x = m_Actor.m_VertexList[2].x - 30 / 900; Bullet_C3.m_VertexList[2].y = m_Actor.m_VertexList[2].y - 5 / 900;
			Bullet_C3.m_VertexList[3].x = m_Actor.m_VertexList[3].x - 30 / 900; Bullet_C3.m_VertexList[3].y = m_Actor.m_VertexList[3].y - 5 / 900;
			Bullet_C3.m_VertexList[4].x = m_Actor.m_VertexList[4].x - 30 / 900; Bullet_C3.m_VertexList[4].y = m_Actor.m_VertexList[4].y - 5 / 900;
			Bullet_C3.m_VertexList[5].x = m_Actor.m_VertexList[5].x - 30 / 900; Bullet_C3.m_VertexList[5].y = m_Actor.m_VertexList[5].y - 5 / 900;
			Bullet_C3.m_VertexList[6].x = m_Actor.m_VertexList[6].x - 30 / 900; Bullet_C3.m_VertexList[6].y = m_Actor.m_VertexList[6].y - 5 / 900;
		}

		if (Bullet_C3.Bullet_Go == true && m_Actor.Face_Direction == 2)
		{
			Bullet_C3.Bullet_Go = false; Bullet_C3.Face_Direction2_flag = true;
			Bullet_C3.m_VertexList[0].x = m_Actor.m_VertexList[0].x + 30 / 900; Bullet_C3.m_VertexList[0].y = m_Actor.m_VertexList[0].y + 5 / 900;
			Bullet_C3.m_VertexList[1].x = m_Actor.m_VertexList[1].x + 30 / 900; Bullet_C3.m_VertexList[1].y = m_Actor.m_VertexList[1].y + 5 / 900;
			Bullet_C3.m_VertexList[2].x = m_Actor.m_VertexList[2].x + 30 / 900; Bullet_C3.m_VertexList[2].y = m_Actor.m_VertexList[2].y + 5 / 900;
			Bullet_C3.m_VertexList[3].x = m_Actor.m_VertexList[3].x + 30 / 900; Bullet_C3.m_VertexList[3].y = m_Actor.m_VertexList[3].y + 5 / 900;
			Bullet_C3.m_VertexList[4].x = m_Actor.m_VertexList[4].x + 30 / 900; Bullet_C3.m_VertexList[4].y = m_Actor.m_VertexList[4].y + 5 / 900;
			Bullet_C3.m_VertexList[5].x = m_Actor.m_VertexList[5].x + 30 / 900; Bullet_C3.m_VertexList[5].y = m_Actor.m_VertexList[5].y + 5 / 900;
			Bullet_C3.m_VertexList[6].x = m_Actor.m_VertexList[6].x + 30 / 900; Bullet_C3.m_VertexList[6].y = m_Actor.m_VertexList[6].y + 5 / 900;
		}

		if (Bullet_C3.Face_Direction1_flag == true)
		{
			Bullet_C3.frame_C();
			if (Bullet_C3.bullet_step == 0) { Bullet_C3.MoveX(-g_fSecPerFrame * 1.0f); }        if (Bullet_C3.bullet_step == 1) { Bullet_C3.MoveX(-g_fSecPerFrame * 1.0f); }
			if (Bullet_C3.bullet_step == 2) { Bullet_C3.MoveX(-g_fSecPerFrame * 1.0f); }        if (Bullet_C3.bullet_step == 3) { Bullet_C3.MoveX(-g_fSecPerFrame * 1.0f); }
			if (Bullet_C3.bullet_step == 4) { Bullet_C3.MoveX(-g_fSecPerFrame * 1.0f); }        if (Bullet_C3.bullet_step == 5) { Bullet_C3.MoveX(-g_fSecPerFrame * 1.0f); }
			if (Bullet_C3.bullet_step == 6) { Bullet_C3.MoveX(-g_fSecPerFrame * 1.0f); }
		}

		if (Bullet_C3.Face_Direction2_flag == true)
		{
			Bullet_C3.frame_C();
			if (Bullet_C3.bullet_step == 0) { Bullet_C3.MoveX(g_fSecPerFrame*1.0f); }        if (Bullet_C3.bullet_step == 1) { Bullet_C3.MoveX(g_fSecPerFrame*1.0f); }
			if (Bullet_C3.bullet_step == 2) { Bullet_C3.MoveX(g_fSecPerFrame*1.0f); }        if (Bullet_C3.bullet_step == 3) { Bullet_C3.MoveX(g_fSecPerFrame*1.0f); }
			if (Bullet_C3.bullet_step == 4) { Bullet_C3.MoveX(g_fSecPerFrame*1.0f); }        if (Bullet_C3.bullet_step == 5) { Bullet_C3.MoveX(g_fSecPerFrame*1.0f); }
			if (Bullet_C3.bullet_step == 6) { Bullet_C3.MoveX(g_fSecPerFrame*1.0f); }
		}

		memcpy(N_VertexList_C3, Bullet_C3.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_C3.m_VertexList[iV].x; vertex.y = Bullet_C3.m_VertexList[iV].y;
			vertex.x -= Bullet_C3.m_vCenter.x;		 vertex.y -= Bullet_C3.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_C3[iV].x = vertex.x * C + vertex.y * S; N_VertexList_C3[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_C3[iV].x += Bullet_C3.m_vCenter.x;		 N_VertexList_C3[iV].y += Bullet_C3.m_vCenter.y;
		}
		g_pContext->UpdateSubresource(Bullet_C3.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_C3, 0, 0);

			////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (Bullet_C4.Bullet_Go == true && m_Actor.Face_Direction == 1)
		{
			Bullet_C4.Bullet_Go = false; Bullet_C4.Face_Direction1_flag = true;
			Bullet_C4.m_VertexList[0].x = m_Actor.m_VertexList[0].x - 30 / 900; Bullet_C4.m_VertexList[0].y = m_Actor.m_VertexList[0].y - 5 / 900;
			Bullet_C4.m_VertexList[1].x = m_Actor.m_VertexList[1].x - 30 / 900; Bullet_C4.m_VertexList[1].y = m_Actor.m_VertexList[1].y - 5 / 900;
			Bullet_C4.m_VertexList[2].x = m_Actor.m_VertexList[2].x - 30 / 900; Bullet_C4.m_VertexList[2].y = m_Actor.m_VertexList[2].y - 5 / 900;
			Bullet_C4.m_VertexList[3].x = m_Actor.m_VertexList[3].x - 30 / 900; Bullet_C4.m_VertexList[3].y = m_Actor.m_VertexList[3].y - 5 / 900;
			Bullet_C4.m_VertexList[4].x = m_Actor.m_VertexList[4].x - 30 / 900; Bullet_C4.m_VertexList[4].y = m_Actor.m_VertexList[4].y - 5 / 900;
			Bullet_C4.m_VertexList[5].x = m_Actor.m_VertexList[5].x - 30 / 900; Bullet_C4.m_VertexList[5].y = m_Actor.m_VertexList[5].y - 5 / 900;
			Bullet_C4.m_VertexList[6].x = m_Actor.m_VertexList[6].x - 30 / 900; Bullet_C4.m_VertexList[6].y = m_Actor.m_VertexList[6].y - 5 / 900;
		}

		if (Bullet_C4.Bullet_Go == true && m_Actor.Face_Direction == 2)
		{
			Bullet_C4.Bullet_Go = false; Bullet_C4.Face_Direction2_flag = true;
			Bullet_C4.m_VertexList[0].x = m_Actor.m_VertexList[0].x + 30 / 900; Bullet_C4.m_VertexList[0].y = m_Actor.m_VertexList[0].y + 5 / 900;
			Bullet_C4.m_VertexList[1].x = m_Actor.m_VertexList[1].x + 30 / 900; Bullet_C4.m_VertexList[1].y = m_Actor.m_VertexList[1].y + 5 / 900;
			Bullet_C4.m_VertexList[2].x = m_Actor.m_VertexList[2].x + 30 / 900; Bullet_C4.m_VertexList[2].y = m_Actor.m_VertexList[2].y + 5 / 900;
			Bullet_C4.m_VertexList[3].x = m_Actor.m_VertexList[3].x + 30 / 900; Bullet_C4.m_VertexList[3].y = m_Actor.m_VertexList[3].y + 5 / 900;
			Bullet_C4.m_VertexList[4].x = m_Actor.m_VertexList[4].x + 30 / 900; Bullet_C4.m_VertexList[4].y = m_Actor.m_VertexList[4].y + 5 / 900;
			Bullet_C4.m_VertexList[5].x = m_Actor.m_VertexList[5].x + 30 / 900; Bullet_C4.m_VertexList[5].y = m_Actor.m_VertexList[5].y + 5 / 900;
			Bullet_C4.m_VertexList[6].x = m_Actor.m_VertexList[6].x + 30 / 900; Bullet_C4.m_VertexList[6].y = m_Actor.m_VertexList[6].y + 5 / 900;
		}

		if (Bullet_C4.Face_Direction1_flag == true)
		{
			Bullet_C4.frame_C();
			if (Bullet_C4.bullet_step == 0) { Bullet_C4.MoveX(-g_fSecPerFrame * 1.0f); }        if (Bullet_C4.bullet_step == 1) { Bullet_C4.MoveX(-g_fSecPerFrame * 1.0f); }
			if (Bullet_C4.bullet_step == 2) { Bullet_C4.MoveX(-g_fSecPerFrame * 1.0f); }        if (Bullet_C4.bullet_step == 3) { Bullet_C4.MoveX(-g_fSecPerFrame * 1.0f); }
			if (Bullet_C4.bullet_step == 4) { Bullet_C4.MoveX(-g_fSecPerFrame * 1.0f); }        if (Bullet_C4.bullet_step == 5) { Bullet_C4.MoveX(-g_fSecPerFrame * 1.0f); }
			if (Bullet_C4.bullet_step == 6) { Bullet_C4.MoveX(-g_fSecPerFrame * 1.0f); }
		}

		if (Bullet_C4.Face_Direction2_flag == true)
		{
			Bullet_C4.frame_C();
			if (Bullet_C4.bullet_step == 0) { Bullet_C4.MoveX(g_fSecPerFrame*1.0f); }        if (Bullet_C4.bullet_step == 1) { Bullet_C4.MoveX(g_fSecPerFrame*1.0f); }
			if (Bullet_C4.bullet_step == 2) { Bullet_C4.MoveX(g_fSecPerFrame*1.0f); }        if (Bullet_C4.bullet_step == 3) { Bullet_C4.MoveX(g_fSecPerFrame*1.0f); }
			if (Bullet_C4.bullet_step == 4) { Bullet_C4.MoveX(g_fSecPerFrame*1.0f); }        if (Bullet_C4.bullet_step == 5) { Bullet_C4.MoveX(g_fSecPerFrame*1.0f); }
			if (Bullet_C4.bullet_step == 6) { Bullet_C4.MoveX(g_fSecPerFrame*1.0f); }
		}

		memcpy(N_VertexList_C4, Bullet_C4.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_C4.m_VertexList[iV].x; vertex.y = Bullet_C4.m_VertexList[iV].y;
			vertex.x -= Bullet_C4.m_vCenter.x;		 vertex.y -= Bullet_C4.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_C4[iV].x = vertex.x * C + vertex.y * S; N_VertexList_C4[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_C4[iV].x += Bullet_C4.m_vCenter.x;		 N_VertexList_C4[iV].y += Bullet_C4.m_vCenter.y;
		}
		g_pContext->UpdateSubresource(Bullet_C4.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_C4, 0, 0);


		////////////////////////////////////////////////////////////////////////////////////////////////////////
	
		if (I_Input.Key('V') == KEY_PUSH)

		{Bullet_Ghost_1.Bullet_Go = true;}

		if (Bullet_Ghost_1.Bullet_Go == true) 
		{ Bullet_Ghost_1.MoveX(-g_fSecPerFrame * 1.0f);}	

		memcpy(N_VertexList_G1, Bullet_Ghost_1.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_1.m_VertexList[iV].x; vertex.y = Bullet_Ghost_1.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_1.m_vCenter.x;		 vertex.y -= Bullet_Ghost_1.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G1[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G1[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G1[iV].x += Bullet_Ghost_1.m_vCenter.x;		 N_VertexList_G1[iV].y += Bullet_Ghost_1.m_vCenter.y;
		}	g_pContext->UpdateSubresource(Bullet_Ghost_1.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G1, 0, 0);




		////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (I_Input.Key('B') == KEY_PUSH)

		{
			Bullet_Ghost_2.Bullet_Go = true;
		}

		if (Bullet_Ghost_2.Bullet_Go == true)
		{
			Bullet_Ghost_2.MoveX(-g_fSecPerFrame * 1.0f);
		}

		memcpy(N_VertexList_G2, Bullet_Ghost_2.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_2.m_VertexList[iV].x; vertex.y = Bullet_Ghost_2.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_2.m_vCenter.x;		 vertex.y -= Bullet_Ghost_2.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G2[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G2[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G2[iV].x += Bullet_Ghost_2.m_vCenter.x; N_VertexList_G2[iV].y += Bullet_Ghost_2.m_vCenter.y;
		}	g_pContext->UpdateSubresource(Bullet_Ghost_2.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G2, 0, 0);



		////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (I_Input.Key('N') == KEY_PUSH)

		{
			Bullet_Ghost_3.Bullet_Go = true;
		}

		if (Bullet_Ghost_3.Bullet_Go == true)
		{
			Bullet_Ghost_3.MoveX(-g_fSecPerFrame * 1.0f);
		}

		memcpy(N_VertexList_G3, Bullet_Ghost_3.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_3.m_VertexList[iV].x; vertex.y = Bullet_Ghost_3.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_3.m_vCenter.x;		  vertex.y -= Bullet_Ghost_3.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G3[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G3[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G3[iV].x += Bullet_Ghost_3.m_vCenter.x; N_VertexList_G3[iV].y += Bullet_Ghost_3.m_vCenter.y;
		}	g_pContext->UpdateSubresource(Bullet_Ghost_3.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G3, 0, 0);



		////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (I_Input.Key('M') == KEY_PUSH)

		{
			Bullet_Ghost_4.Bullet_Go = true;
		}

		if (Bullet_Ghost_4.Bullet_Go == true)
		{
			Bullet_Ghost_4.MoveX(-g_fSecPerFrame * 1.0f);
		}

		memcpy(N_VertexList_G4, Bullet_Ghost_4.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_4.m_VertexList[iV].x; vertex.y = Bullet_Ghost_4.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_4.m_vCenter.x;		 vertex.y -= Bullet_Ghost_4.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G4[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G4[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G4[iV].x += Bullet_Ghost_4.m_vCenter.x; N_VertexList_G4[iV].y += Bullet_Ghost_4.m_vCenter.y;
		}	g_pContext->UpdateSubresource(Bullet_Ghost_4.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G4, 0, 0);








		return true;	
}

	bool   TSceneGame::Render()
	{
		Game_Background.Render(g_pContext);

		UI_Bullet_1.Render(g_pContext);
		UI_Bullet_2.Render(g_pContext);
		UI_Bullet_3.Render(g_pContext);
		UI_Bullet_4.Render(g_pContext);
		UI_Bullet_5.Render(g_pContext);
		UI_Bullet_6.Render(g_pContext);
		UI_Bullet_7.Render(g_pContext);
		UI_Bullet_8.Render(g_pContext);
		
		Bullet_F1.Render(g_pContext);
		Bullet_F2.Render(g_pContext);
		Bullet_F3.Render(g_pContext);
		Bullet_F4.Render(g_pContext);

		Bullet_C1.Render(g_pContext);
		Bullet_C2.Render(g_pContext);
		Bullet_C3.Render(g_pContext);
		Bullet_C4.Render(g_pContext);

		

		Box_Alive.Render(g_pContext);
		Treasure_Box.Render(g_pContext);


		Bullet_Ghost_1.Render(g_pContext);
		Bullet_Ghost_2.Render(g_pContext);
		Bullet_Ghost_3.Render(g_pContext);
		Bullet_Ghost_4.Render(g_pContext);

		m_Boy_NPC.Render(g_pContext);
		m_Actor.Render(g_pContext);
		return true;
	}


	bool    TSceneGame::Release()
	{

		return true;
	}

	TSceneGame::TSceneGame()
	{
		m_iSceneID = GAME_SCENE_PLAY;
		m_bNextSceneStart = false;
	}

	TSceneGame::~TSceneGame()
	{

	}











class TSceneEnd : public TScene
{

public:
	virtual bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:

	TSceneEnd();
	virtual ~TSceneEnd();
};




bool	TSceneEnd::Init()
{

	return true;
};
bool	TSceneEnd::Frame()
{

	return true;
};

bool	TSceneEnd::Render()
{


	return true;
};

bool	TSceneEnd::Release()
{
	return true;
};

TSceneEnd::TSceneEnd()
{
	m_iSceneID = GAME_SCENE_END;
	m_bNextSceneStart = false;
}

TSceneEnd::~TSceneEnd()
{}








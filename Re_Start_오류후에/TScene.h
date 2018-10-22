#include "THeroObj.h"
#include "Background.h"
#include "Box.h"
#include "TCollision.h"
#include "Boy_NPC.h"

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
	Background			Game_Background;
	THeroObj			m_Actor;	SimpleVertex		m_VertexList[6];
	Boy_NPC				m_Boy_NPC;	SimpleVertex		m_VertexList_2[6];

	Box					UI_Bullet_1;
	Box					UI_Bullet_2;
	Box					UI_Bullet_3;
	Box					UI_Bullet_4;
	Box					UI_Bullet_5;
	Box					UI_Bullet_6;
	Box					UI_Bullet_7;
	Box					UI_Bullet_8;

public:
	virtual bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	TSceneGame();
	virtual ~TSceneGame();
};



bool	TSceneGame::Init()
{
	Game_Background.in_Texture_SetData_factors(0, 0, 900, 500, 900, 500);
	Game_Background.m_for_update_Rects.x = g_rtClient.right;	Game_Background.m_for_update_Rects.y = g_rtClient.bottom;
	Game_Background.Window_SetData_factors(0, 0, Game_Background.m_for_update_Rects.x, Game_Background.m_for_update_Rects.y);
	Game_Background.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/background.bmp");

	UI_Bullet_1.in_Texture_SetData_factors(0, 0, 120, 40, 120, 40);
	UI_Bullet_1.m_for_update_Rects.x = g_rtClient.right/10;	UI_Bullet_1.m_for_update_Rects.y = g_rtClient.bottom/10;
	UI_Bullet_1.Window_SetData_factors(10, 30, UI_Bullet_1.m_for_update_Rects.x, UI_Bullet_1.m_for_update_Rects.y);
	UI_Bullet_1.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/gun_bullet.png");

	UI_Bullet_2.in_Texture_SetData_factors(0, 0, 120, 40, 120, 40);
	UI_Bullet_2.m_for_update_Rects.x = g_rtClient.right / 10;	UI_Bullet_2.m_for_update_Rects.y = g_rtClient.bottom / 10;
	UI_Bullet_2.Window_SetData_factors(10, 80, UI_Bullet_2.m_for_update_Rects.x, UI_Bullet_2.m_for_update_Rects.y);
	UI_Bullet_2.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/gun_bullet.png");

	UI_Bullet_3.in_Texture_SetData_factors(0, 0, 120, 40, 120, 40);
	UI_Bullet_3.m_for_update_Rects.x = g_rtClient.right / 10;	UI_Bullet_3.m_for_update_Rects.y = g_rtClient.bottom / 10;
	UI_Bullet_3.Window_SetData_factors(10, 130, UI_Bullet_3.m_for_update_Rects.x, UI_Bullet_3.m_for_update_Rects.y);
	UI_Bullet_3.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/gun_bullet.png");

	UI_Bullet_4.in_Texture_SetData_factors(0, 0, 120, 40, 120, 40);
	UI_Bullet_4.m_for_update_Rects.x = g_rtClient.right / 10;	UI_Bullet_4.m_for_update_Rects.y = g_rtClient.bottom / 10;
	UI_Bullet_4.Window_SetData_factors(10, 180, UI_Bullet_4.m_for_update_Rects.x, UI_Bullet_4.m_for_update_Rects.y);
	UI_Bullet_4.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/gun_bullet.png");


	UI_Bullet_5.in_Texture_SetData_factors(0, 0, 120, 40, 120, 40);
	UI_Bullet_5.m_for_update_Rects.x = g_rtClient.right / 10;	UI_Bullet_5.m_for_update_Rects.y = g_rtClient.bottom / 10;
	UI_Bullet_5.Window_SetData_factors(800, 30, UI_Bullet_5.m_for_update_Rects.x, UI_Bullet_5.m_for_update_Rects.y);
	UI_Bullet_5.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/gun_bullet.png");

	UI_Bullet_6.in_Texture_SetData_factors(0, 0, 120, 40, 120, 40);
	UI_Bullet_6.m_for_update_Rects.x = g_rtClient.right / 10;	UI_Bullet_6.m_for_update_Rects.y = g_rtClient.bottom / 10;
	UI_Bullet_6.Window_SetData_factors(800, 80, UI_Bullet_6.m_for_update_Rects.x, UI_Bullet_6.m_for_update_Rects.y);
	UI_Bullet_6.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/gun_bullet.png");

	UI_Bullet_7.in_Texture_SetData_factors(0, 0, 120, 40, 120, 40);
	UI_Bullet_7.m_for_update_Rects.x = g_rtClient.right / 10;	UI_Bullet_7.m_for_update_Rects.y = g_rtClient.bottom / 10;
	UI_Bullet_7.Window_SetData_factors(800, 130, UI_Bullet_7.m_for_update_Rects.x, UI_Bullet_7.m_for_update_Rects.y);
	UI_Bullet_7.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/gun_bullet.png");

	UI_Bullet_8.in_Texture_SetData_factors(0, 0, 120, 40, 120, 40);
	UI_Bullet_8.m_for_update_Rects.x = g_rtClient.right / 10;	UI_Bullet_8.m_for_update_Rects.y = g_rtClient.bottom / 10;
	UI_Bullet_8.Window_SetData_factors(800, 180, UI_Bullet_8.m_for_update_Rects.x, UI_Bullet_8.m_for_update_Rects.y);
	UI_Bullet_8.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/gun_bullet.png");


	m_Boy_NPC.m_for_update_Rects.x = g_rtClient.right / 9;	m_Boy_NPC.m_for_update_Rects.y = g_rtClient.bottom / 9;
	m_Boy_NPC.in_Texture_SetData_factors(91, 2, 57, 92, 753, 532); 
	m_Boy_NPC.Window_SetData_factors(600, 350, m_Boy_NPC.m_for_update_Rects.x, m_Boy_NPC.m_for_update_Rects.y); // 텍스쳐 시작점 왼위점 좌표 + 텍스쳐 가로-세로 크기.
	m_Boy_NPC.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy.png");
	memcpy(m_VertexList_2, m_Boy_NPC.m_VertexList, sizeof(SimpleVertex) * 6);


	m_Actor.m_for_update_Rects.x = g_rtClient.right / 9;	m_Actor.m_for_update_Rects.y = g_rtClient.bottom / 9;
	m_Actor.in_Texture_SetData_factors(20, 6, 60, 93, 758, 537);
	m_Actor.Window_SetData_factors(0, 350, m_Actor.m_for_update_Rects.x, m_Actor.m_for_update_Rects.y); // 텍스쳐 시작점 왼위점 좌표 + 텍스쳐 가로-세로 크기.
	m_Actor.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Girl_Right.png");
	memcpy(m_VertexList, m_Actor.m_VertexList, sizeof(SimpleVertex) * 6);
	return true;
};

bool	TSceneGame::Frame()
{
	static float fAngle = 0.0f;

	if (I_Input.Key('A') )
	{
		m_Actor.Face_Direction = 1;
		m_Actor.left_walk();
		memcpy(m_VertexList, m_Actor.m_VertexList, sizeof(SimpleVertex) * 6);
		m_Actor.MoveX(-g_fSecPerFrame * 0.3f);
	}

	if (I_Input.Key('D'))
	{
		m_Actor.Face_Direction = 2;
		m_Actor.right_walk();
		memcpy(m_VertexList, m_Actor.m_VertexList, sizeof(SimpleVertex) * 6);
		m_Actor.MoveX(g_fSecPerFrame*0.3f);
	}

	if (I_Input.Key('W'))
	{
		m_Actor.MoveY(g_fSecPerFrame * 0.3f);
	}

	if (I_Input.Key('S') )
	{
		m_Actor.MoveY(-g_fSecPerFrame * 0.3f);
	}


	if (I_Input.Key('G'))
	{
		m_Actor.Gun_step = 1;

		if (m_Actor.Face_Direction == 1)
		{
			m_Actor.MoveX(g_fSecPerFrame*0.3f);
		}
		else if (m_Actor.Face_Direction == 2)
		{
			m_Actor.MoveX(-g_fSecPerFrame * 0.3f);
		}
	}

	m_Actor.shot();
	memcpy(m_VertexList, m_Actor.m_VertexList, sizeof(SimpleVertex) * 6);


	for (int iV = 0; iV < 6; iV++)
	{
		D3DVECTOR vertex;
		vertex.x = m_Actor.m_VertexList[iV].x;
		vertex.y = m_Actor.m_VertexList[iV].y;

		vertex.x -= m_Actor.m_vCenter.x;
		vertex.y -= m_Actor.m_vCenter.y;
		float S = sinf(fAngle);
		float C = cosf(fAngle);
		m_VertexList[iV].x = vertex.x * C + vertex.y * S;
		m_VertexList[iV].y = vertex.x * -S + vertex.y * C;
		m_VertexList[iV].x += m_Actor.m_vCenter.x;
		m_VertexList[iV].y += m_Actor.m_vCenter.y;
	}
	g_pContext->UpdateSubresource(m_Actor.PipeLineSetup.m_pVertextBuffer, 0, NULL, m_VertexList, 0, 0);



	return true;
}

bool	TSceneGame::Render()
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

	m_Boy_NPC.Render(g_pContext);
	m_Actor.Render(g_pContext);


	return true;
}


bool	TSceneGame::Release()
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








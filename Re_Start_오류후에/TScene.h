#include "THeroObj.h"
#include "Background.h"
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
	SimpleVertex		m_VertexList[6];

	Box					UI_BUTTON;
	SimpleVertex		m_VertexList_2[6];

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

	Lobby_Background.m_for_update_Rects.x = g_rtClient.right ;	Lobby_Background.m_for_update_Rects.y = g_rtClient.bottom ;
	Lobby_Background.in_Texture_SetData_factors(0, 0, 900, 500, 900, 500);
	Lobby_Background.Window_SetData_factors(0, 0, Lobby_Background.m_for_update_Rects.x, Lobby_Background.m_for_update_Rects.y); // 텍스쳐 시작점 왼위점 좌표 + 텍스쳐 가로-세로 크기.
	Lobby_Background.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Treasure_Island.bmp");
	memcpy(m_VertexList, Lobby_Background.m_VertexList, sizeof(SimpleVertex) * 6);



	UI_BUTTON.m_for_update_Rects.x = g_rtClient.right/4;	UI_BUTTON.m_for_update_Rects.y = g_rtClient.bottom/8;
	UI_BUTTON.in_Texture_SetData_factors(0, 0, 334, 82, 334, 82);
	UI_BUTTON.Window_SetData_factors(340, 240, UI_BUTTON.m_for_update_Rects.x, UI_BUTTON.m_for_update_Rects.y); // 텍스쳐 시작점 왼위점 좌표 + 텍스쳐 가로-세로 크기.
	UI_BUTTON.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/main_start_dis.bmp");
	memcpy(m_VertexList_2, UI_BUTTON.m_VertexList, sizeof(SimpleVertex) * 6);

	return true;
};

bool	TSceneLobby::Frame()
{

	//if (I_Input.Key('0') == KEY_PUSH)
	//{
	//	UI_BUTTON.m_bDebugRect = !UI_BUTTON.m_bDebugRect;
	//}


	//if (TCollision::RectInPt(UI_BUTTON.m_rtCollision, I_Input.m_MousePos))
	//{
	//	UI_BUTTON.m_bDead = false;
	//	//TSound::Get()->PlayEffect(6);
	//}


	//if (!UI_BUTTON.m_bDead)
	//{
	//	UI_BUTTON.Set(g_rtClient.right / 2,
	//		g_rtClient.bottom / 2 + 200, 0, 0, 334, 82);
	//	UI_BUTTON.Load(L"../../data/main_start_pus.bmp");

	//	if (I_Input.Key(VK_LBUTTON) && TCollision::RectInPt(UI_BUTTON.m_rtCollision, I_Input.m_MousePos))
	//	{
	//		UI_BUTTON.Set(g_rtClient.right / 2,
	//			g_rtClient.bottom / 2 + 200, 0, 0, 334, 82);
	//		UI_BUTTON.Load(L"../../data/main_start_sel.bmp");

	//		m_bNextSceneStart = true;
	//	}
	//}
	
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
	THeroObj			m_Actor;
	SimpleVertex		m_VertexList[6];

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
	m_Actor.m_for_update_Rects.x = g_rtClient.right / 4;	m_Actor.m_for_update_Rects.y = g_rtClient.bottom / 4;
	m_Actor.in_Texture_SetData_factors(20, 6, 60, 93, 758, 537);
	m_Actor.Window_SetData_factors(0, 0, m_Actor.m_for_update_Rects.x, m_Actor.m_for_update_Rects.y); // 텍스쳐 시작점 왼위점 좌표 + 텍스쳐 가로-세로 크기.
	m_Actor.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Girl_Right.png");
	memcpy(m_VertexList, m_Actor.m_VertexList, sizeof(SimpleVertex) * 6);
	return true;
};

bool	TSceneGame::Frame()
{
	static float fAngle = 0.0f;

	if (g_Input.bLeft)
	{
		m_Actor.Face_Direction = 1;
		m_Actor.left_walk();
		memcpy(m_VertexList, m_Actor.m_VertexList, sizeof(SimpleVertex) * 6);
		m_Actor.MoveX(-g_fSecPerFrame * 0.3f);
	}

	if (g_Input.bRight)
	{
		m_Actor.Face_Direction = 2;
		m_Actor.right_walk();
		memcpy(m_VertexList, m_Actor.m_VertexList, sizeof(SimpleVertex) * 6);
		m_Actor.MoveX(g_fSecPerFrame*0.3f);
	}

	if (g_Input.bFront)
	{
		m_Actor.MoveY(g_fSecPerFrame * 0.3f);
	}

	if (g_Input.bBack)
	{
		m_Actor.MoveY(-g_fSecPerFrame * 0.3f);
	}


	if (g_Input.bAttack)
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








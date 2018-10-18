#include "Object_Handling.h"

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

	Object_Handling		m_Actor;
	SimpleVertex		m_VertexList[6];

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
	m_Actor.m_for_update_Rects.x = g_rtClient.right / 4;	m_Actor.m_for_update_Rects.y = g_rtClient.bottom / 4;
	m_Actor.in_Texture_SetData_factors(70, 164, 438, 378, 641, 542);
	m_Actor.Window_SetData_factors(0, 0, m_Actor.m_for_update_Rects.x, m_Actor.m_for_update_Rects.y);
	m_Actor.Create(g_pd3dDevice,L"HLSL.vsh",L"HLSL.psh",	L"../../data/wait.png");
	memcpy(m_VertexList, m_Actor.m_VertexList,sizeof(SimpleVertex) * 6);
	return true;
};


bool	TSceneLobby::Frame()
{
	static float fAngle = 0.0f;

	if (g_Input.bLeft)
		m_Actor.MoveX(-g_fSecPerFrame * 0.3f);
	if (g_Input.bRight)
		m_Actor.MoveX(g_fSecPerFrame*0.3f);
	if (g_Input.bFront)
		m_Actor.MoveY(g_fSecPerFrame * 0.3f);
	if (g_Input.bBack)
		m_Actor.MoveY(-g_fSecPerFrame * 0.3f);

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
	g_pContext->UpdateSubresource(	m_Actor.PipeLineSetup.m_pVertextBuffer,0, NULL, m_VertexList, 0, 0);
	return true;
	
};

bool	TSceneLobby::Render()
{
	m_Actor.Render(g_pContext);
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

	return true;
};

bool	TSceneGame::Frame()
{

	return true;
}

bool	TSceneGame::Render()
{


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








#include "TSceneLobby.h"

bool	TSceneLobby::Init()
{

	SimpleVertex vertices[] =  //SimpleVertex 배열이다.
	{
		-0.5f,  0.5f, 0.5f, 0.0f,0.0f,
		0.5f,  0.5f, 0.5f, 1.0f,0.0f,
		0.5, -0.5f, 0.5f, 1.0f,1.0f,
		-0.5f,  0.5f, 0.5f, 0.0f,0.0f,
		0.5, -0.5f, 0.5f, 1.0f,1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f,1.0f
	};

	m_Actor.Init(g_pd3dDevice, L"../../data/idle.png", vertices, 6, L"HLSL.vsh", L"HLSL.psh");

	return true;
};


bool	TSceneLobby::Frame()
{

	return true;
};

bool	TSceneLobby::Render()
{
	m_Actor.Render(g_pContext);

	return true;
};

bool	TSceneLobby::Release()
{
	m_Actor.Release();

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


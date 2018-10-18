#include "TSceneGame.h"

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

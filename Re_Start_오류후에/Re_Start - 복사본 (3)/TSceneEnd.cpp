#include "TSceneEnd.h"


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
#include "THeroObj.h"
#include "Background.h"
#include "Box.h"
#include "TCollision.h"
#include "Boy_NPC.h"
#include "Gun_Bullet.h"
#include "Box_Alive.h"
#include "Box.h"
#include "BOSS_NPC.h"
#include "xSound.h"


int end_decision;

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
	Box					Message; 
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

	sSound->Init();
	sSound->Load("../../data/00_Menu.mp3", false);
	sSound->Load("../../data/GunShot.mp3", false);

	sSound->Play(0);
		
	Message.in_Texture_SetData_factors(0, 0, 1241, 735, 1241, 735);
	Message.m_for_update_Rects.x = g_rtClient.right / 1;    Message.m_for_update_Rects.y = g_rtClient.bottom / 1;
	Message.Window_SetData_factors(0, 0, Message.m_for_update_Rects.x, Message.m_for_update_Rects.y);
	Message.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/KEYBOARD.png");




	Lobby_Background.in_Texture_SetData_factors(0, 0, 900, 500, 900, 500);
	Lobby_Background.m_for_update_Rects.x = g_rtClient.right;	Lobby_Background.m_for_update_Rects.y = g_rtClient.bottom;
	Lobby_Background.Window_SetData_factors(0, 0, Lobby_Background.m_for_update_Rects.x, Lobby_Background.m_for_update_Rects.y);
	Lobby_Background.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Treasure_Island.bmp");

	UI_BUTTON.m_for_update_Rects.x = g_rtClient.right / 4;	UI_BUTTON.m_for_update_Rects.y = g_rtClient.bottom / 8;
	UI_BUTTON.in_Texture_SetData_factors(0, 0, 334, 82, 334, 82);
	UI_BUTTON.Window_SetData_factors(340, 400, UI_BUTTON.m_for_update_Rects.x, UI_BUTTON.m_for_update_Rects.y); // 텍스쳐 시작점 왼위점 좌표 + 텍스쳐 가로-세로 크기.
	UI_BUTTON.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/main_start_dis.bmp");
	return true;
};


bool	TSceneLobby::Frame()
{
	

	static float fAddTime = 0.0f;
	fAddTime += g_fSecPerFrame;

	if (fAddTime>8.0f)
	{



		Message.in_Texture_SetData_factors(0, 0, 1241, 735, 1241, 735);
		Message.m_for_update_Rects.x = g_rtClient.right / 32;    Message.m_for_update_Rects.y = g_rtClient.bottom / 32;
		Message.Window_SetData_factors(900, 50, Message.m_for_update_Rects.x, Message.m_for_update_Rects.y);
		Message.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/KEYBOARD.png");
		
		//sSound-> PlayEffect(0);



	}


	if (340 < I_Input.m_MousePos.x && I_Input.m_MousePos.x < 470 && 420 < I_Input.m_MousePos.y && I_Input.m_MousePos.y < 470)
	{
		UI_BUTTON.m_bDead = true;
		sSound->Stop(0);
		sSound->Play(1);

	}




	if (UI_BUTTON.m_bDead)
	{
		UI_BUTTON.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/main_start_pus.bmp");

		if (I_Input.Key(VK_LBUTTON) && 340 < I_Input.m_MousePos.x && I_Input.m_MousePos.x < 500 && 420 < I_Input.m_MousePos.y && I_Input.m_MousePos.y < 470)
		{
			UI_BUTTON.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/main_start_sel.bmp");
			m_bNextSceneStart = true;
		}
	}

	sSound->Frame();

	return true;
};


bool	TSceneLobby::Render()
{


	Lobby_Background.Render(g_pContext);
	UI_BUTTON.Render(g_pContext);
	Message.Render(g_pContext);

	return true;
};

bool	TSceneLobby::Release()
{
	sSound->Release();
	
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

	float fAngle;

	int  box_alive_live_or_dead;
	bool BOX_ALIVE_FINAL_SWITCH;
	bool box_alive_Col_F1; bool box_alive_Col_C1;
	bool box_alive_Col_F2; bool box_alive_Col_C2;
	bool box_alive_Col_F3; bool box_alive_Col_C3;
	bool box_alive_Col_F4; bool box_alive_Col_C4;

	bool box_alive_Col_S1;
	bool box_alive_Col_S2;



	 

	int  Hero_live_or_dead;
	bool Hero_Col_G1;
	bool Hero_Col_G2;
	bool Hero_Col_G3;
	bool Hero_Col_G4;

	bool Hero_Col_B1;
	bool Hero_Col_B2;
	bool Hero_Col_B3;
	bool Hero_Col_B4;

	bool Hero_Col_S1;
	bool Hero_Col_S2;
	bool Hero_Col_S3;
	bool Hero_Col_S4;


	int  Robot_live_or_dead;
	bool Robot_Col_F1; bool Robot_Col_C1;
	bool Robot_Col_F2; bool Robot_Col_C2;
	bool Robot_Col_F3; bool Robot_Col_C3;
	bool Robot_Col_F4; bool Robot_Col_C4;
	
	bool Robot_Col_S1;
	bool Robot_Col_S2;
	bool Robot_Col_S3;
	bool Robot_Col_S4;


	int  NPC_live_or_dead;

	bool NPC_Col_F3; bool NPC_Col_C3;
	bool NPC_Col_F4; bool NPC_Col_C4;
	bool NPC_Col_S1; bool NPC_Col_S2;

public:

	Background				Game_Background;

	THeroObj				m_Actor;          SimpleVertex        N_VertexList[6];
	Box                     m_Actor_life_bar; SimpleVertex        N_VertexList_HLB[6];

	Boy_NPC					m_Boy_NPC;        SimpleVertex        N_VertexList_2[6];

	BOSS_NPC				Robot;		      SimpleVertex        N_VertexList_R[6];
	Box                     Robot_life_bar;   SimpleVertex        N_VertexList_RLB[6];


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


	Gun_Bullet            Bullet_B1; SimpleVertex        N_VertexList_B1[6];
	Gun_Bullet            Bullet_B2; SimpleVertex        N_VertexList_B2[6];
	Gun_Bullet            Bullet_B3; SimpleVertex        N_VertexList_B3[6];
	Gun_Bullet            Bullet_B4; SimpleVertex        N_VertexList_B4[6];


	Box_Alive			Box_Alive;			SimpleVertex        N_VertexList_BA[6];
	Box					Box_Alive_life_bar; SimpleVertex        N_VertexList_BA_LB[6];

	Box					Treasure_Box; SimpleVertex     N_VertexList_T[6];
	bool				Trasure_Box_FINAL_SWITCH;

	Box					Message;      SimpleVertex     N_VertexList_M[6];




public:
	virtual bool    Init();
	bool    Frame();
	bool    Render();
	bool    Release();
public:

	void Hero_Actions();
	void Boy_NPC_Action_including_first_messgae();
	void Boy_NPC_collision_from_hero_attack();
	void Hero_bullets_basic_Action();
	void Hero_Ghost_collision();


	void Herosword_boss_collision();
	void Herosword_ghost_collsion();
	void Herosword_box_alive_collision();

	void Tresure_Box__m_Actor_Dection_collision_and_ghost_shots();
	void Bullet_Ghost_collision();
	void Bullet_Box_Alive_collision();
	void Bullet_Boss_collision();

	
	void Boss_Canon_hero_collision();
	void Boss_sword_hero_collsion();

	void Boss_FSM();


	void Boy_NPC_collision_final_decision_including_second_message();
	void Box_Alive_collision_final_decision();
	void Boss_collision_final_decision();
	void Hero_collision_final_decision();

	void Treasure_Box_open();

	void succees_ending();

public:
	TSceneGame();
	virtual ~TSceneGame();
};



TSceneGame::TSceneGame() : fAngle(0.0f), box_alive_Col_S1(false), box_alive_Col_S2(false), box_alive_live_or_dead(0), box_alive_Col_F1(false), box_alive_Col_C1(false), box_alive_Col_F2(false), box_alive_Col_C2(false), box_alive_Col_F3(false), box_alive_Col_C3(false), box_alive_Col_F4(false), box_alive_Col_C4(false), Hero_live_or_dead(0), Hero_Col_G1(false), Hero_Col_G2(false), Hero_Col_G3(false), Hero_Col_G4(false), Hero_Col_B1(false), Hero_Col_B2 (false), Hero_Col_B3(false), Hero_Col_B4(false), Hero_Col_S1(false), Hero_Col_S2(false), Hero_Col_S3(false), Hero_Col_S4(false), Robot_live_or_dead (0), Robot_Col_F1(false), Robot_Col_C1(false), Robot_Col_F2(false), Robot_Col_C2(false), Robot_Col_F3(false), Robot_Col_C3(false), Robot_Col_F4(false), Robot_Col_C4(false), Robot_Col_S1(false), Robot_Col_S2(false), Robot_Col_S3(false), Robot_Col_S4(false), NPC_live_or_dead(0), NPC_Col_F3(false), NPC_Col_C3(false), NPC_Col_F4(false), NPC_Col_C4(false), NPC_Col_S1(false), NPC_Col_S2(false), BOX_ALIVE_FINAL_SWITCH(false), Trasure_Box_FINAL_SWITCH(false)
{
	m_iSceneID = GAME_SCENE_PLAY;
	m_bNextSceneStart = false;
	
	//fAngle = 0.0f;

	//box_alive_Col_S1 = false;
	//box_alive_Col_S2 = false;

	//box_alive_live_or_dead = 0;
	//box_alive_Col_F1 = false;   box_alive_Col_C1 = false;
	//box_alive_Col_F2 = false;   box_alive_Col_C2 = false;
	//box_alive_Col_F3 = false;   box_alive_Col_C3 = false;
	//box_alive_Col_F4 = false;   box_alive_Col_C4 = false;
	//

	//Hero_live_or_dead = 0;
	//Hero_Col_G1 = false;
	//Hero_Col_G2 = false;
	//Hero_Col_G3 = false;
	//Hero_Col_G4 = false;

	//Hero_Col_B1 = false;
	//Hero_Col_B2 = false;
	//Hero_Col_B3 = false;
	//Hero_Col_B4 = false;

	//Hero_Col_S1 = false;
	//Hero_Col_S2 = false;
	//Hero_Col_S3 = false;
	//Hero_Col_S4 = false;



	//Robot_live_or_dead = 0;

	//Robot_Col_F1 = false; Robot_Col_C1 = false;
	//Robot_Col_F2 = false; Robot_Col_C2 = false;
	//Robot_Col_F3 = false; Robot_Col_C3 = false;
	//Robot_Col_F4 = false; Robot_Col_C4 = false;

	//Robot_Col_S1 = false;
	//Robot_Col_S2 = false;
	//Robot_Col_S3 = false;
	//Robot_Col_S4 = false;


	//NPC_live_or_dead = 0;
	//NPC_Col_F3 = false;         NPC_Col_C3 = false;
	//NPC_Col_F4 = false;         NPC_Col_C4 = false;
	//NPC_Col_S1 = false;         NPC_Col_S2 = false;

	//BOX_ALIVE_FINAL_SWITCH = false;
	//Trasure_Box_FINAL_SWITCH = false;

}



bool   TSceneGame::Init()
{

	sSound->Init();

	sSound->Load("../../data/00_Menu.mp3", false);
	sSound->Load("../../data/GunShot.mp3", false);

	sSound->Play(0);



	Game_Background.in_Texture_SetData_factors(0, 0, 900, 500, 900, 500);
	Game_Background.m_for_update_Rects.x = g_rtClient.right;    Game_Background.m_for_update_Rects.y = g_rtClient.bottom;
	Game_Background.Window_SetData_factors(0, 0, Game_Background.m_for_update_Rects.x, Game_Background.m_for_update_Rects.y);
	Game_Background.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/background.bmp");

	Message.in_Texture_SetData_factors(0, 0, 1241, 735, 1241, 735);
	Message.m_for_update_Rects.x = g_rtClient.right / 30;    Message.m_for_update_Rects.y = g_rtClient.bottom / 30;
	Message.Window_SetData_factors(900, 50, Message.m_for_update_Rects.x, Message.m_for_update_Rects.y);
	Message.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Board_UI.png");


	Treasure_Box.in_Texture_SetData_factors(0, 0, 100, 75, 100, 75);
	Treasure_Box.m_for_update_Rects.x = g_rtClient.right / 11;    Treasure_Box.m_for_update_Rects.y = g_rtClient.bottom / 8;
	Treasure_Box.Window_SetData_factors(805, 255, Treasure_Box.m_for_update_Rects.x, Treasure_Box.m_for_update_Rects.y);
	Treasure_Box.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Treasure_Close_100_75.png");

	Box_Alive.in_Texture_SetData_factors(0, 0, 125, 127, 125, 127);
	Box_Alive.m_for_update_Rects.x = g_rtClient.right / 6.5;    Box_Alive.m_for_update_Rects.y = g_rtClient.bottom / 3.8;
	Box_Alive.Window_SetData_factors(630, 285, Box_Alive.m_for_update_Rects.x, Box_Alive.m_for_update_Rects.y);
	Box_Alive.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Alter.png");


	Box_Alive_life_bar.in_Texture_SetData_factors(0, 0, 299, 76, 299, 76);
	Box_Alive_life_bar.m_for_update_Rects.x = g_rtClient.right / 35;    Box_Alive_life_bar.m_for_update_Rects.y = g_rtClient.bottom / 10;
	Box_Alive_life_bar.Window_SetData_factors(900, 10, Box_Alive_life_bar.m_for_update_Rects.x, Box_Alive_life_bar.m_for_update_Rects.y);
	Box_Alive_life_bar.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Full_Bar_B.png");



	UI_Bullet_1.in_Texture_SetData_factors(0, 0, 120, 40, 120, 40);
	UI_Bullet_1.m_for_update_Rects.x = g_rtClient.right / 10;    UI_Bullet_1.m_for_update_Rects.y = g_rtClient.bottom / 12;
	UI_Bullet_1.Window_SetData_factors(10, 20, UI_Bullet_1.m_for_update_Rects.x, UI_Bullet_1.m_for_update_Rects.y);
	UI_Bullet_1.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/gun_bullet_F.png");

	UI_Bullet_2.in_Texture_SetData_factors(0, 0, 120, 40, 120, 40);
	UI_Bullet_2.m_for_update_Rects.x = g_rtClient.right / 10;    UI_Bullet_2.m_for_update_Rects.y = g_rtClient.bottom / 12;
	UI_Bullet_2.Window_SetData_factors(10, 70, UI_Bullet_2.m_for_update_Rects.x, UI_Bullet_2.m_for_update_Rects.y);
	UI_Bullet_2.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/gun_bullet_F.png");

	UI_Bullet_3.in_Texture_SetData_factors(0, 0, 120, 40, 120, 40);
	UI_Bullet_3.m_for_update_Rects.x = g_rtClient.right / 10;    UI_Bullet_3.m_for_update_Rects.y = g_rtClient.bottom / 12;
	UI_Bullet_3.Window_SetData_factors(10, 120, UI_Bullet_3.m_for_update_Rects.x, UI_Bullet_3.m_for_update_Rects.y);
	UI_Bullet_3.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/gun_bullet_F.png");

	UI_Bullet_4.in_Texture_SetData_factors(0, 0, 120, 40, 120, 40);
	UI_Bullet_4.m_for_update_Rects.x = g_rtClient.right / 10;    UI_Bullet_4.m_for_update_Rects.y = g_rtClient.bottom / 12;
	UI_Bullet_4.Window_SetData_factors(10, 170, UI_Bullet_4.m_for_update_Rects.x, UI_Bullet_4.m_for_update_Rects.y);
	UI_Bullet_4.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/gun_bullet_F.png");


	UI_Bullet_5.in_Texture_SetData_factors(0, 0, 120, 40, 120, 40);
	UI_Bullet_5.m_for_update_Rects.x = g_rtClient.right / 10;    UI_Bullet_5.m_for_update_Rects.y = g_rtClient.bottom / 10;
	UI_Bullet_5.Window_SetData_factors(800, 0, UI_Bullet_5.m_for_update_Rects.x, UI_Bullet_5.m_for_update_Rects.y);
	UI_Bullet_5.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/gun_bullet_C.png");

	UI_Bullet_6.in_Texture_SetData_factors(0, 0, 120, 40, 120, 40);
	UI_Bullet_6.m_for_update_Rects.x = g_rtClient.right / 10;    UI_Bullet_6.m_for_update_Rects.y = g_rtClient.bottom / 10;
	UI_Bullet_6.Window_SetData_factors(800, 50, UI_Bullet_6.m_for_update_Rects.x, UI_Bullet_6.m_for_update_Rects.y);
	UI_Bullet_6.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/gun_bullet_C.png");

	UI_Bullet_7.in_Texture_SetData_factors(0, 0, 120, 40, 120, 40);
	UI_Bullet_7.m_for_update_Rects.x = g_rtClient.right / 10;    UI_Bullet_7.m_for_update_Rects.y = g_rtClient.bottom / 10;
	UI_Bullet_7.Window_SetData_factors(800, 100, UI_Bullet_7.m_for_update_Rects.x, UI_Bullet_7.m_for_update_Rects.y);
	UI_Bullet_7.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/gun_bullet_C.png");

	UI_Bullet_8.in_Texture_SetData_factors(0, 0, 120, 40, 120, 40);
	UI_Bullet_8.m_for_update_Rects.x = g_rtClient.right / 10;    UI_Bullet_8.m_for_update_Rects.y = g_rtClient.bottom / 10;
	UI_Bullet_8.Window_SetData_factors(800, 150, UI_Bullet_8.m_for_update_Rects.x, UI_Bullet_8.m_for_update_Rects.y);
	UI_Bullet_8.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/gun_bullet_C.png");


	Bullet_F1.in_Texture_SetData_factors(225, 141, 32, 38, 400, 300);
	Bullet_F1.m_for_update_Rects.x = g_rtClient.right / 15;    Bullet_F1.m_for_update_Rects.y = g_rtClient.bottom / 15;
	Bullet_F1.Window_SetData_factors(10, 20, Bullet_F1.m_for_update_Rects.x, Bullet_F1.m_for_update_Rects.y);
	Bullet_F1.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/bitmap1.png");

	Bullet_F2.in_Texture_SetData_factors(225, 141, 32, 38, 400, 300);
	Bullet_F2.m_for_update_Rects.x = g_rtClient.right / 15;    Bullet_F2.m_for_update_Rects.y = g_rtClient.bottom / 15;
	Bullet_F2.Window_SetData_factors(10, 70, Bullet_F2.m_for_update_Rects.x, Bullet_F2.m_for_update_Rects.y);
	Bullet_F2.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/bitmap1.png");

	Bullet_F3.in_Texture_SetData_factors(225, 141, 32, 38, 400, 300);
	Bullet_F3.m_for_update_Rects.x = g_rtClient.right / 15;    Bullet_F3.m_for_update_Rects.y = g_rtClient.bottom / 15;
	Bullet_F3.Window_SetData_factors(10, 120, Bullet_F3.m_for_update_Rects.x, Bullet_F3.m_for_update_Rects.y);
	Bullet_F3.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/bitmap1.png");

	Bullet_F4.in_Texture_SetData_factors(225, 141, 32, 38, 400, 300);
	Bullet_F4.m_for_update_Rects.x = g_rtClient.right / 15;    Bullet_F4.m_for_update_Rects.y = g_rtClient.bottom / 15;
	Bullet_F4.Window_SetData_factors(10, 170, Bullet_F4.m_for_update_Rects.x, Bullet_F4.m_for_update_Rects.y);
	Bullet_F4.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/bitmap1.png");


	Bullet_C1.in_Texture_SetData_factors(253, 61, 12, 12, 400, 300);
	Bullet_C1.m_for_update_Rects.x = g_rtClient.right / 20;    Bullet_C1.m_for_update_Rects.y = g_rtClient.bottom / 20;
	Bullet_C1.Window_SetData_factors(815, 10, Bullet_C1.m_for_update_Rects.x, Bullet_C1.m_for_update_Rects.y);
	Bullet_C1.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/bitmap1.png");

	Bullet_C2.in_Texture_SetData_factors(253, 61, 12, 12, 400, 300);
	Bullet_C2.m_for_update_Rects.x = g_rtClient.right / 20;    Bullet_C2.m_for_update_Rects.y = g_rtClient.bottom / 20;
	Bullet_C2.Window_SetData_factors(815, 60, Bullet_C2.m_for_update_Rects.x, Bullet_C2.m_for_update_Rects.y);
	Bullet_C2.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/bitmap1.png");

	Bullet_C3.in_Texture_SetData_factors(253, 61, 12, 12, 400, 300);
	Bullet_C3.m_for_update_Rects.x = g_rtClient.right / 20;    Bullet_C3.m_for_update_Rects.y = g_rtClient.bottom / 20;
	Bullet_C3.Window_SetData_factors(815, 110, Bullet_C3.m_for_update_Rects.x, Bullet_C3.m_for_update_Rects.y);
	Bullet_C3.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/bitmap1.png");

	Bullet_C4.in_Texture_SetData_factors(253, 61, 12, 12, 400, 300);
	Bullet_C4.m_for_update_Rects.x = g_rtClient.right / 20;    Bullet_C4.m_for_update_Rects.y = g_rtClient.bottom / 20;
	Bullet_C4.Window_SetData_factors(815, 160, Bullet_C4.m_for_update_Rects.x, Bullet_C4.m_for_update_Rects.y);
	Bullet_C4.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/bitmap1.png");


	//

	Bullet_B1.in_Texture_SetData_factors(170, 761, 143, 139, 702, 1843);
	Bullet_B1.m_for_update_Rects.x = g_rtClient.right / 15;    Bullet_B1.m_for_update_Rects.y = g_rtClient.bottom / 15;
	Bullet_B1.Window_SetData_factors(-100, 30, Bullet_B1.m_for_update_Rects.x, Bullet_B1.m_for_update_Rects.y);
	Bullet_B1.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");

	Bullet_B2.in_Texture_SetData_factors(170, 761, 143, 139, 702, 1843);
	Bullet_B2.m_for_update_Rects.x = g_rtClient.right / 15;    Bullet_B2.m_for_update_Rects.y = g_rtClient.bottom / 15;
	Bullet_B2.Window_SetData_factors(-100, 80, Bullet_B2.m_for_update_Rects.x, Bullet_B2.m_for_update_Rects.y);
	Bullet_B2.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");

	Bullet_B3.in_Texture_SetData_factors(170, 761, 143, 139, 702, 1843);
	Bullet_B3.m_for_update_Rects.x = g_rtClient.right / 15;    Bullet_B3.m_for_update_Rects.y = g_rtClient.bottom / 15;
	Bullet_B3.Window_SetData_factors(-100, 130, Bullet_B3.m_for_update_Rects.x, Bullet_B3.m_for_update_Rects.y);
	Bullet_B3.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");

	Bullet_B4.in_Texture_SetData_factors(170, 761, 143, 139, 702, 1843);
	Bullet_B4.m_for_update_Rects.x = g_rtClient.right / 15;    Bullet_B4.m_for_update_Rects.y = g_rtClient.bottom / 15;
	Bullet_B4.Window_SetData_factors(-100, 180, Bullet_B4.m_for_update_Rects.x, Bullet_B4.m_for_update_Rects.y);
	Bullet_B4.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");

	//




	Bullet_Ghost_1.in_Texture_SetData_factors(0, 0, 67, 79, 67, 79);
	Bullet_Ghost_1.m_for_update_Rects.x = g_rtClient.right / 10;    Bullet_Ghost_1.m_for_update_Rects.y = g_rtClient.bottom / 5;
	Bullet_Ghost_1.Window_SetData_factors(900, 310, Bullet_Ghost_1.m_for_update_Rects.x, Bullet_Ghost_1.m_for_update_Rects.y);
	Bullet_Ghost_1.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Duskull.png");

	Bullet_Ghost_2.in_Texture_SetData_factors(0, 0, 67, 79, 67, 79);
	Bullet_Ghost_2.m_for_update_Rects.x = g_rtClient.right / 10;    Bullet_Ghost_2.m_for_update_Rects.y = g_rtClient.bottom / 5;
	Bullet_Ghost_2.Window_SetData_factors(900, 310, Bullet_Ghost_2.m_for_update_Rects.x, Bullet_Ghost_2.m_for_update_Rects.y);
	Bullet_Ghost_2.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Duskull.png");

	Bullet_Ghost_3.in_Texture_SetData_factors(0, 0, 67, 79, 67, 79);
	Bullet_Ghost_3.m_for_update_Rects.x = g_rtClient.right / 10;    Bullet_Ghost_3.m_for_update_Rects.y = g_rtClient.bottom / 5;
	Bullet_Ghost_3.Window_SetData_factors(900, 310, Bullet_Ghost_3.m_for_update_Rects.x, Bullet_Ghost_3.m_for_update_Rects.y);
	Bullet_Ghost_3.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Duskull.png");

	Bullet_Ghost_4.in_Texture_SetData_factors(0, 0, 67, 79, 67, 79);
	Bullet_Ghost_4.m_for_update_Rects.x = g_rtClient.right / 10;    Bullet_Ghost_4.m_for_update_Rects.y = g_rtClient.bottom / 5;
	Bullet_Ghost_4.Window_SetData_factors(900, 310, Bullet_Ghost_4.m_for_update_Rects.x, Bullet_Ghost_4.m_for_update_Rects.y);
	Bullet_Ghost_4.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Duskull.png");



	m_Boy_NPC.m_for_update_Rects.x = g_rtClient.right / 9;    m_Boy_NPC.m_for_update_Rects.y = g_rtClient.bottom / 5;
	m_Boy_NPC.in_Texture_SetData_factors(91, 2, 57, 92, 753, 532);
	m_Boy_NPC.Window_SetData_factors(0, 310, m_Boy_NPC.m_for_update_Rects.x, m_Boy_NPC.m_for_update_Rects.y); // 텍스쳐 시작점 왼위점 좌표 + 텍스쳐 가로-세로 크기.
	m_Boy_NPC.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy.png");



	m_Actor.m_for_update_Rects.x = g_rtClient.right / 9;    m_Actor.m_for_update_Rects.y = g_rtClient.bottom / 5;
	m_Actor.in_Texture_SetData_factors(38, 3, 60, 93, 758, 537);
	m_Actor.Window_SetData_factors(150, 310, m_Actor.m_for_update_Rects.x, m_Actor.m_for_update_Rects.y); // 텍스쳐 시작점 왼위점 좌표 + 텍스쳐 가로-세로 크기.
	m_Actor.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Girl_Left.png");



	m_Actor_life_bar.in_Texture_SetData_factors(0, 0, 299, 76, 299, 76);
	m_Actor_life_bar.m_for_update_Rects.x = g_rtClient.right / 3.5;    m_Actor_life_bar.m_for_update_Rects.y = g_rtClient.bottom / 10;
	m_Actor_life_bar.Window_SetData_factors(200, 10, m_Actor_life_bar.m_for_update_Rects.x, m_Actor_life_bar.m_for_update_Rects.y);
	m_Actor_life_bar.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Full_Bar.png");



	Robot.m_for_update_Rects.x = g_rtClient.right / 5;    Robot.m_for_update_Rects.y = g_rtClient.bottom / 2.5;
	Robot.in_Texture_SetData_factors(213, 1230, 65, 120, 702, 1843);
	Robot.Window_SetData_factors(900, 220, Robot.m_for_update_Rects.x, Robot.m_for_update_Rects.y); // 텍스쳐 시작점 왼위점 좌표 + 텍스쳐 가로-세로 크기.
	Robot.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");



	Robot_life_bar.in_Texture_SetData_factors(0, 0, 299, 76, 299, 76);
	Robot_life_bar.m_for_update_Rects.x = g_rtClient.right / 35;    Robot_life_bar.m_for_update_Rects.y = g_rtClient.bottom / 10;
	Robot_life_bar.Window_SetData_factors(900, 10, Robot_life_bar.m_for_update_Rects.x, Robot_life_bar.m_for_update_Rects.y);
	Robot_life_bar.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Full_Bar_B.png");



	return true;

};

bool    TSceneGame::Frame()
{


	if (m_Boy_NPC.Enter_flag_1 == true)
	{
		Hero_Actions();
		Hero_bullets_basic_Action();	
	}

	if (m_Boy_NPC.Enter_flag_1 == false)
	{
		Boy_NPC_Action_including_first_messgae();
	}



	if (BOX_ALIVE_FINAL_SWITCH == false)
	{
		Herosword_box_alive_collision();
		Bullet_Box_Alive_collision();
		Tresure_Box__m_Actor_Dection_collision_and_ghost_shots();
		Bullet_Ghost_collision();
		Herosword_ghost_collsion();
		Hero_Ghost_collision();
		Box_Alive_collision_final_decision();
	}

	 


	if (BOX_ALIVE_FINAL_SWITCH == true && Robot_live_or_dead < 4)
	{
		Boss_FSM();
		Bullet_Boss_collision();
		Herosword_boss_collision();
		Boss_collision_final_decision();
	}


	if (BOX_ALIVE_FINAL_SWITCH == true && Hero_live_or_dead != 4 && Robot_live_or_dead != 4)
	{
		Boss_Canon_hero_collision();
		Boss_sword_hero_collsion();
	}


	if (Robot_live_or_dead == 4 && Trasure_Box_FINAL_SWITCH == false)
	{
		Boy_NPC_collision_from_hero_attack();
		Boy_NPC_collision_final_decision_including_second_message();
		Hero_collision_final_decision();
		Treasure_Box_open();
		
	}


	if (Robot_live_or_dead != 4)
	{
		 Hero_collision_final_decision();
	}
	
	if (Trasure_Box_FINAL_SWITCH == true)
	{
		succees_ending();
	}




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

	Box_Alive_life_bar.Render(g_pContext);
	m_Actor_life_bar.Render(g_pContext);

	Bullet_Ghost_1.Render(g_pContext);
	Bullet_Ghost_2.Render(g_pContext);
	Bullet_Ghost_3.Render(g_pContext);
	Bullet_Ghost_4.Render(g_pContext);

	m_Boy_NPC.Render(g_pContext);
	m_Actor.Render(g_pContext);

	Robot.Render(g_pContext);
	Robot_life_bar.Render(g_pContext);

	Bullet_B1.Render(g_pContext);
	Bullet_B2.Render(g_pContext);
	Bullet_B3.Render(g_pContext);
	Bullet_B4.Render(g_pContext);
	
	Message.Render(g_pContext);



	return true;
}


bool    TSceneGame::Release()
{
	return true;
}

TSceneGame::~TSceneGame()
{

}

void TSceneGame::succees_ending()
{
	static float fAddTime = 0.0f;
	fAddTime += g_fSecPerFrame;

	if (fAddTime > 5.0f)
	{

		m_bNextSceneStart = true;
		end_decision = 1;
	}

}

void TSceneGame::Boss_FSM()
{
	
		Robot.distance_direction_between_hero_boss = Robot.m_pos.x - m_Actor.m_pos.x;
		Robot.basic_frame();
		Robot.ATTACK_SWORD(); Robot.sword();
		Robot.ATTACK_SHOT(); Robot.shot();
	
	
	
	
	if(Robot.state == Detection__0)
	{
		if (Robot.Face_Direction == 2 )
		{
			if (Robot.walk_step == 0) { Robot.MoveX(g_fSecPerFrame*0.1f); }
			if (Robot.walk_step == 1) { Robot.MoveX(g_fSecPerFrame*0.1f); }        if (Robot.walk_step == 2) { Robot.MoveX(g_fSecPerFrame*0.1f); }
			if (Robot.walk_step == 3) { Robot.MoveX(g_fSecPerFrame*0.1f); }        if (Robot.walk_step == 4) { Robot.MoveX(g_fSecPerFrame*0.1f); }
			if (Robot.walk_step == 5) { Robot.MoveX(g_fSecPerFrame*0.1f); }		   if (Robot.walk_step == 6) { Robot.MoveX(g_fSecPerFrame*0.1f); }
			if (Robot.walk_step == 7) { Robot.MoveX(g_fSecPerFrame*0.1f); }
		}

		if (Robot.Face_Direction == 1 )
		{
			if (Robot.walk_step == 0) { Robot.MoveX(-g_fSecPerFrame*0.1f); }
			if (Robot.walk_step == 1) { Robot.MoveX(-g_fSecPerFrame * 0.1f); }     if (Robot.walk_step == 2) { Robot.MoveX(-g_fSecPerFrame * 0.1f); }
			if (Robot.walk_step == 3) { Robot.MoveX(-g_fSecPerFrame * 0.1f); }     if (Robot.walk_step == 4) { Robot.MoveX(-g_fSecPerFrame * 0.1f); }
			if (Robot.walk_step == 5) { Robot.MoveX(-g_fSecPerFrame * 0.1f); }     if (Robot.walk_step == 6) { Robot.MoveX(-g_fSecPerFrame * 0.1f); }
			if (Robot.walk_step == 7) { Robot.MoveX(-g_fSecPerFrame * 0.1f); }
		}
	}

	memcpy(N_VertexList_R, Robot.m_VertexList, sizeof(SimpleVertex) * 6);
	//////////////////////////////////////////////////////////////////////////////////



	for (int iV = 0; iV < 6; iV++)
	{
		D3DVECTOR vertex;
		vertex.x = Robot.m_VertexList[iV].x;
		vertex.y = Robot.m_VertexList[iV].y;

		vertex.x -= Robot.m_vCenter.x;
		vertex.y -= Robot.m_vCenter.y;
		float S = sinf(fAngle);
		float C = cosf(fAngle);
		N_VertexList[iV].x = vertex.x * C + vertex.y * S;
		N_VertexList[iV].y = vertex.x * -S + vertex.y * C;
		N_VertexList[iV].x += Robot.m_vCenter.x;
		N_VertexList[iV].y += Robot.m_vCenter.y;
	}
	g_pContext->UpdateSubresource(Robot.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_R, 0, 0);




	//////////////     총알의 움직임   /////////////////////////////////////

	if (Robot.Bullet_B1_Bullet_Go == true && Robot.Face_Direction == 1)
	{
		Robot.Bullet_B1_Bullet_Go = false; Bullet_B1.Face_Direction1_flag = true;
		Bullet_B1.m_VertexList[0].x = Robot.m_VertexList[0].x - 30 / 900; Bullet_B1.m_VertexList[0].y = Robot.m_VertexList[0].y - 5 / 900;
		Bullet_B1.m_VertexList[1].x = Robot.m_VertexList[1].x - 30 / 900; Bullet_B1.m_VertexList[1].y = Robot.m_VertexList[1].y - 5 / 900;
		Bullet_B1.m_VertexList[2].x = Robot.m_VertexList[2].x - 30 / 900; Bullet_B1.m_VertexList[2].y = Robot.m_VertexList[2].y - 5 / 900;
		Bullet_B1.m_VertexList[3].x = Robot.m_VertexList[3].x - 30 / 900; Bullet_B1.m_VertexList[3].y = Robot.m_VertexList[3].y - 5 / 900;
		Bullet_B1.m_VertexList[4].x = Robot.m_VertexList[4].x - 30 / 900; Bullet_B1.m_VertexList[4].y = Robot.m_VertexList[4].y - 5 / 900;
		Bullet_B1.m_VertexList[5].x = Robot.m_VertexList[5].x - 30 / 900; Bullet_B1.m_VertexList[5].y = Robot.m_VertexList[5].y - 5 / 900;
		Bullet_B1.m_VertexList[6].x = Robot.m_VertexList[6].x - 30 / 900; Bullet_B1.m_VertexList[6].y = Robot.m_VertexList[6].y - 5 / 900;
	}

	if (Robot.Bullet_B1_Bullet_Go == true && Robot.Face_Direction == 2)
	{
		Robot.Bullet_B1_Bullet_Go = false; Bullet_B1.Face_Direction2_flag = true;
		Bullet_B1.m_VertexList[0].x = Robot.m_VertexList[0].x + 30 / 900; Bullet_B1.m_VertexList[0].y = Robot.m_VertexList[0].y + 5 / 900;
		Bullet_B1.m_VertexList[1].x = Robot.m_VertexList[1].x + 30 / 900; Bullet_B1.m_VertexList[1].y = Robot.m_VertexList[1].y + 5 / 900;
		Bullet_B1.m_VertexList[2].x = Robot.m_VertexList[2].x + 30 / 900; Bullet_B1.m_VertexList[2].y = Robot.m_VertexList[2].y + 5 / 900;
		Bullet_B1.m_VertexList[3].x = Robot.m_VertexList[3].x + 30 / 900; Bullet_B1.m_VertexList[3].y = Robot.m_VertexList[3].y + 5 / 900;
		Bullet_B1.m_VertexList[4].x = Robot.m_VertexList[4].x + 30 / 900; Bullet_B1.m_VertexList[4].y = Robot.m_VertexList[4].y + 5 / 900;
		Bullet_B1.m_VertexList[5].x = Robot.m_VertexList[5].x + 30 / 900; Bullet_B1.m_VertexList[5].y = Robot.m_VertexList[5].y + 5 / 900;
		Bullet_B1.m_VertexList[6].x = Robot.m_VertexList[6].x + 30 / 900; Bullet_B1.m_VertexList[6].y = Robot.m_VertexList[6].y + 5 / 900;
	}

	if (Bullet_B1.Face_Direction1_flag == true)
	{
		Bullet_B1.frame_B_L();
		Bullet_B1.MoveX(-g_fSecPerFrame * 1.0f);
	}

	if (Bullet_B1.Face_Direction2_flag == true)
	{
		Bullet_B1.frame_B_R();
		Bullet_B1.MoveX(g_fSecPerFrame*1.0f);
	}

	memcpy(N_VertexList_B1, Bullet_B1.m_VertexList, sizeof(SimpleVertex) * 6);
	for (int iV = 0; iV < 6; iV++)
	{
		D3DVECTOR vertex;
		vertex.x = Bullet_B1.m_VertexList[iV].x; vertex.y = Bullet_B1.m_VertexList[iV].y;
		vertex.x -= Bullet_B1.m_vCenter.x;		 vertex.y -= Bullet_B1.m_vCenter.y;
		float S = sinf(fAngle);	float C = cosf(fAngle);
		N_VertexList_B1[iV].x = vertex.x * C + vertex.y * S; N_VertexList_B1[iV].y = vertex.x * -S + vertex.y * C;
		N_VertexList_B1[iV].x += Bullet_B1.m_vCenter.x;		 N_VertexList_B1[iV].y += Bullet_B1.m_vCenter.y;
	}
	g_pContext->UpdateSubresource(Bullet_B1.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_B1, 0, 0);

	//////////////     총알의 움직임   /////////////////////////////////////

	if (Robot.Bullet_B2_Bullet_Go == true && Robot.Face_Direction == 1)
	{
		Robot.Bullet_B2_Bullet_Go  = false; Bullet_B2.Face_Direction1_flag = true;
		Bullet_B2.m_VertexList[0].x = Robot.m_VertexList[0].x - 30 / 900; Bullet_B2.m_VertexList[0].y = Robot.m_VertexList[0].y - 5 / 900;
		Bullet_B2.m_VertexList[1].x = Robot.m_VertexList[1].x - 30 / 900; Bullet_B2.m_VertexList[1].y = Robot.m_VertexList[1].y - 5 / 900;
		Bullet_B2.m_VertexList[2].x = Robot.m_VertexList[2].x - 30 / 900; Bullet_B2.m_VertexList[2].y = Robot.m_VertexList[2].y - 5 / 900;
		Bullet_B2.m_VertexList[3].x = Robot.m_VertexList[3].x - 30 / 900; Bullet_B2.m_VertexList[3].y = Robot.m_VertexList[3].y - 5 / 900;
		Bullet_B2.m_VertexList[4].x = Robot.m_VertexList[4].x - 30 / 900; Bullet_B2.m_VertexList[4].y = Robot.m_VertexList[4].y - 5 / 900;
		Bullet_B2.m_VertexList[5].x = Robot.m_VertexList[5].x - 30 / 900; Bullet_B2.m_VertexList[5].y = Robot.m_VertexList[5].y - 5 / 900;
		Bullet_B2.m_VertexList[6].x = Robot.m_VertexList[6].x - 30 / 900; Bullet_B2.m_VertexList[6].y = Robot.m_VertexList[6].y - 5 / 900;
	}

	if (Robot.Bullet_B2_Bullet_Go == true && Robot.Face_Direction == 2)
	{
		Robot.Bullet_B2_Bullet_Go = false; Bullet_B2.Face_Direction2_flag = true;
		Bullet_B2.m_VertexList[0].x = Robot.m_VertexList[0].x + 30 / 900; Bullet_B2.m_VertexList[0].y = Robot.m_VertexList[0].y + 5 / 900;
		Bullet_B2.m_VertexList[1].x = Robot.m_VertexList[1].x + 30 / 900; Bullet_B2.m_VertexList[1].y = Robot.m_VertexList[1].y + 5 / 900;
		Bullet_B2.m_VertexList[2].x = Robot.m_VertexList[2].x + 30 / 900; Bullet_B2.m_VertexList[2].y = Robot.m_VertexList[2].y + 5 / 900;
		Bullet_B2.m_VertexList[3].x = Robot.m_VertexList[3].x + 30 / 900; Bullet_B2.m_VertexList[3].y = Robot.m_VertexList[3].y + 5 / 900;
		Bullet_B2.m_VertexList[4].x = Robot.m_VertexList[4].x + 30 / 900; Bullet_B2.m_VertexList[4].y = Robot.m_VertexList[4].y + 5 / 900;
		Bullet_B2.m_VertexList[5].x = Robot.m_VertexList[5].x + 30 / 900; Bullet_B2.m_VertexList[5].y = Robot.m_VertexList[5].y + 5 / 900;
		Bullet_B2.m_VertexList[6].x = Robot.m_VertexList[6].x + 30 / 900; Bullet_B2.m_VertexList[6].y = Robot.m_VertexList[6].y + 5 / 900;
	}

	if (Bullet_B2.Face_Direction1_flag == true)
	{
		Bullet_B2.frame_B_L();
		Bullet_B2.MoveX(-g_fSecPerFrame * 1.0f);
	}

	if (Bullet_B2.Face_Direction2_flag == true)
	{
		Bullet_B2.frame_B_R();
		Bullet_B2.MoveX(g_fSecPerFrame*1.0f);
	}

	memcpy(N_VertexList_B2, Bullet_B2.m_VertexList, sizeof(SimpleVertex) * 6);
	for (int iV = 0; iV < 6; iV++)
	{
		D3DVECTOR vertex;
		vertex.x = Bullet_B2.m_VertexList[iV].x; vertex.y = Bullet_B2.m_VertexList[iV].y;
		vertex.x -= Bullet_B2.m_vCenter.x;		 vertex.y -= Bullet_B2.m_vCenter.y;
		float S = sinf(fAngle);	float C = cosf(fAngle);
		N_VertexList_B2[iV].x = vertex.x * C + vertex.y * S; N_VertexList_B2[iV].y = vertex.x * -S + vertex.y * C;
		N_VertexList_B2[iV].x += Bullet_B2.m_vCenter.x;		 N_VertexList_B2[iV].y += Bullet_B2.m_vCenter.y;
	}
	g_pContext->UpdateSubresource(Bullet_B2.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_B2, 0, 0);

	//////////////     총알의 움직임   /////////////////////////////////////


	if (Robot.Bullet_B3_Bullet_Go == true && Robot.Face_Direction == 1)
	{
		Robot.Bullet_B3_Bullet_Go = false; Bullet_B3.Face_Direction1_flag = true;
		Bullet_B3.m_VertexList[0].x = Robot.m_VertexList[0].x - 30 / 900; Bullet_B3.m_VertexList[0].y = Robot.m_VertexList[0].y - 5 / 900;
		Bullet_B3.m_VertexList[1].x = Robot.m_VertexList[1].x - 30 / 900; Bullet_B3.m_VertexList[1].y = Robot.m_VertexList[1].y - 5 / 900;
		Bullet_B3.m_VertexList[2].x = Robot.m_VertexList[2].x - 30 / 900; Bullet_B3.m_VertexList[2].y = Robot.m_VertexList[2].y - 5 / 900;
		Bullet_B3.m_VertexList[3].x = Robot.m_VertexList[3].x - 30 / 900; Bullet_B3.m_VertexList[3].y = Robot.m_VertexList[3].y - 5 / 900;
		Bullet_B3.m_VertexList[4].x = Robot.m_VertexList[4].x - 30 / 900; Bullet_B3.m_VertexList[4].y = Robot.m_VertexList[4].y - 5 / 900;
		Bullet_B3.m_VertexList[5].x = Robot.m_VertexList[5].x - 30 / 900; Bullet_B3.m_VertexList[5].y = Robot.m_VertexList[5].y - 5 / 900;
		Bullet_B3.m_VertexList[6].x = Robot.m_VertexList[6].x - 30 / 900; Bullet_B3.m_VertexList[6].y = Robot.m_VertexList[6].y - 5 / 900;
	}

	if (Robot.Bullet_B3_Bullet_Go == true && Robot.Face_Direction == 2)
	{
		Robot.Bullet_B3_Bullet_Go = false; Bullet_B3.Face_Direction2_flag = true;
		Bullet_B3.m_VertexList[0].x = Robot.m_VertexList[0].x + 30 / 900; Bullet_B3.m_VertexList[0].y = Robot.m_VertexList[0].y + 5 / 900;
		Bullet_B3.m_VertexList[1].x = Robot.m_VertexList[1].x + 30 / 900; Bullet_B3.m_VertexList[1].y = Robot.m_VertexList[1].y + 5 / 900;
		Bullet_B3.m_VertexList[2].x = Robot.m_VertexList[2].x + 30 / 900; Bullet_B3.m_VertexList[2].y = Robot.m_VertexList[2].y + 5 / 900;
		Bullet_B3.m_VertexList[3].x = Robot.m_VertexList[3].x + 30 / 900; Bullet_B3.m_VertexList[3].y = Robot.m_VertexList[3].y + 5 / 900;
		Bullet_B3.m_VertexList[4].x = Robot.m_VertexList[4].x + 30 / 900; Bullet_B3.m_VertexList[4].y = Robot.m_VertexList[4].y + 5 / 900;
		Bullet_B3.m_VertexList[5].x = Robot.m_VertexList[5].x + 30 / 900; Bullet_B3.m_VertexList[5].y = Robot.m_VertexList[5].y + 5 / 900;
		Bullet_B3.m_VertexList[6].x = Robot.m_VertexList[6].x + 30 / 900; Bullet_B3.m_VertexList[6].y = Robot.m_VertexList[6].y + 5 / 900;
	}

	if (Bullet_B3.Face_Direction1_flag == true)
	{
		Bullet_B3.frame_B_L();
		Bullet_B3.MoveX(-g_fSecPerFrame * 1.0f);
	}

	if (Bullet_B3.Face_Direction2_flag == true)
	{
		Bullet_B3.frame_B_R();
		Bullet_B3.MoveX(g_fSecPerFrame*1.0f);
	}
	memcpy(N_VertexList_B3, Bullet_B3.m_VertexList, sizeof(SimpleVertex) * 6);

	for (int iV = 0; iV < 6; iV++)
	{
		D3DVECTOR vertex;
		vertex.x = Bullet_B3.m_VertexList[iV].x; vertex.y = Bullet_B3.m_VertexList[iV].y;
		vertex.x -= Bullet_B3.m_vCenter.x;		 vertex.y -= Bullet_B3.m_vCenter.y;
		float S = sinf(fAngle);	float C = cosf(fAngle);
		N_VertexList_B3[iV].x = vertex.x * C + vertex.y * S; N_VertexList_B3[iV].y = vertex.x * -S + vertex.y * C;
		N_VertexList_B3[iV].x += Bullet_B3.m_vCenter.x;		 N_VertexList_B3[iV].y += Bullet_B3.m_vCenter.y;
	}
	g_pContext->UpdateSubresource(Bullet_B3.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_B3, 0, 0);

	//////////////     총알의 움직임   /////////////////////////////////////

	if (Robot.Bullet_B4_Bullet_Go == true && Robot.Face_Direction == 1)
	{
		Robot.Bullet_B4_Bullet_Go = false; Bullet_B4.Face_Direction1_flag = true;
		Bullet_B4.m_VertexList[0].x = Robot.m_VertexList[0].x - 30 / 900; Bullet_B4.m_VertexList[0].y = Robot.m_VertexList[0].y - 5 / 900;
		Bullet_B4.m_VertexList[1].x = Robot.m_VertexList[1].x - 30 / 900; Bullet_B4.m_VertexList[1].y = Robot.m_VertexList[1].y - 5 / 900;
		Bullet_B4.m_VertexList[2].x = Robot.m_VertexList[2].x - 30 / 900; Bullet_B4.m_VertexList[2].y = Robot.m_VertexList[2].y - 5 / 900;
		Bullet_B4.m_VertexList[3].x = Robot.m_VertexList[3].x - 30 / 900; Bullet_B4.m_VertexList[3].y = Robot.m_VertexList[3].y - 5 / 900;
		Bullet_B4.m_VertexList[4].x = Robot.m_VertexList[4].x - 30 / 900; Bullet_B4.m_VertexList[4].y = Robot.m_VertexList[4].y - 5 / 900;
		Bullet_B4.m_VertexList[5].x = Robot.m_VertexList[5].x - 30 / 900; Bullet_B4.m_VertexList[5].y = Robot.m_VertexList[5].y - 5 / 900;
		Bullet_B4.m_VertexList[6].x = Robot.m_VertexList[6].x - 30 / 900; Bullet_B4.m_VertexList[6].y = Robot.m_VertexList[6].y - 5 / 900;
	}

	if (Robot.Bullet_B4_Bullet_Go == true && Robot.Face_Direction == 2)
	{
		Robot.Bullet_B4_Bullet_Go = false; Bullet_B4.Face_Direction2_flag = true;
		Bullet_B4.m_VertexList[0].x = Robot.m_VertexList[0].x + 30 / 900; Bullet_B4.m_VertexList[0].y = Robot.m_VertexList[0].y + 5 / 900;
		Bullet_B4.m_VertexList[1].x = Robot.m_VertexList[1].x + 30 / 900; Bullet_B4.m_VertexList[1].y = Robot.m_VertexList[1].y + 5 / 900;
		Bullet_B4.m_VertexList[2].x = Robot.m_VertexList[2].x + 30 / 900; Bullet_B4.m_VertexList[2].y = Robot.m_VertexList[2].y + 5 / 900;
		Bullet_B4.m_VertexList[3].x = Robot.m_VertexList[3].x + 30 / 900; Bullet_B4.m_VertexList[3].y = Robot.m_VertexList[3].y + 5 / 900;
		Bullet_B4.m_VertexList[4].x = Robot.m_VertexList[4].x + 30 / 900; Bullet_B4.m_VertexList[4].y = Robot.m_VertexList[4].y + 5 / 900;
		Bullet_B4.m_VertexList[5].x = Robot.m_VertexList[5].x + 30 / 900; Bullet_B4.m_VertexList[5].y = Robot.m_VertexList[5].y + 5 / 900;
		Bullet_B4.m_VertexList[6].x = Robot.m_VertexList[6].x + 30 / 900; Bullet_B4.m_VertexList[6].y = Robot.m_VertexList[6].y + 5 / 900;
	}

	if (Bullet_B4.Face_Direction1_flag == true)
	{
		Bullet_B4.frame_B_L();
		Bullet_B4.MoveX(-g_fSecPerFrame * 1.0f);
	}

	if (Bullet_B4.Face_Direction2_flag == true)
	{
		Bullet_B4.frame_B_R();
		Bullet_B4.MoveX(g_fSecPerFrame*1.0f);
	}

	memcpy(N_VertexList_B4, Bullet_B4.m_VertexList, sizeof(SimpleVertex) * 6);

	for (int iV = 0; iV < 6; iV++)
	{
		D3DVECTOR vertex;
		vertex.x = Bullet_B4.m_VertexList[iV].x; vertex.y = Bullet_B4.m_VertexList[iV].y;
		vertex.x -= Bullet_B4.m_vCenter.x;		 vertex.y -= Bullet_B4.m_vCenter.y;
		float S = sinf(fAngle);	float C = cosf(fAngle);
		N_VertexList_B4[iV].x = vertex.x * C + vertex.y * S; N_VertexList_B4[iV].y = vertex.x * -S + vertex.y * C;
		N_VertexList_B4[iV].x += Bullet_B4.m_vCenter.x;		 N_VertexList_B4[iV].y += Bullet_B4.m_vCenter.y;
	}
	g_pContext->UpdateSubresource(Bullet_B4.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_B4, 0, 0);

}






void TSceneGame::Hero_Actions()
{
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


	if (I_Input.Key('I'))
	{		m_Actor.slide_step = 1;}
	if (m_Actor.Face_Direction == 2 && m_Actor.slide_step != 0)
	{	if (m_Actor.slide_step == 1) { m_Actor.MoveX(g_fSecPerFrame*0.3f); }     if (m_Actor.slide_step == 2) { m_Actor.MoveX(g_fSecPerFrame*0.3f); }
		if (m_Actor.slide_step == 3) { m_Actor.MoveX(g_fSecPerFrame*0.3f); }        if (m_Actor.slide_step == 4) { m_Actor.MoveX(g_fSecPerFrame*0.3f); }
		if (m_Actor.slide_step == 5) { m_Actor.MoveX(g_fSecPerFrame*0.3f); }	}
	   
	if (m_Actor.Face_Direction == 1 && m_Actor.slide_step != 0)
	{	if (m_Actor.slide_step == 1) { m_Actor.MoveX(-g_fSecPerFrame * 0.3f); }     if (m_Actor.slide_step == 2) { m_Actor.MoveX(-g_fSecPerFrame * 0.3f); }
		if (m_Actor.slide_step == 3) { m_Actor.MoveX(-g_fSecPerFrame * 0.3f); }     if (m_Actor.slide_step == 4) { m_Actor.MoveX(-g_fSecPerFrame * 0.3f); }
		if (m_Actor.slide_step == 5) { m_Actor.MoveX(-g_fSecPerFrame * 0.3f); }	}




	memcpy(N_VertexList, m_Actor.m_VertexList, sizeof(SimpleVertex) * 6);


	if (I_Input.Key('O'))
	{	m_Actor.sword_step = 1;}

	if (I_Input.Key('K') || I_Input.Key('L'))
	{
		m_Actor.Gun_step = 1;
		if (m_Actor.Face_Direction == 1) { m_Actor.MoveX(g_fSecPerFrame*0.3f); }
		else if (m_Actor.Face_Direction == 2) { m_Actor.MoveX(-g_fSecPerFrame * 0.3f); }
	}
	m_Actor.shot();
	m_Actor.slide();
	m_Actor.sword();
	memcpy(N_VertexList, m_Actor.m_VertexList, sizeof(SimpleVertex) * 6);

	for (int iV = 0; iV < 6; iV++)
	{	D3DVECTOR vertex;
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
}


void TSceneGame::Boy_NPC_Action_including_first_messgae()
{

	////////////////////////////////////// 시작 단계


	if (m_Boy_NPC.initial_start == true)
	{	m_Boy_NPC.initial_start = false;
		m_Boy_NPC.walk_step = 1;}

	if (m_Boy_NPC.walk_step == 1)
	{	m_Boy_NPC.walk_flag = true;}


	//////////////////////////////////////// 110m 가서 일어나는 일


	if (m_Boy_NPC.m_pos.x > 110)
	{
		m_Boy_NPC.initial_start = false;
		m_Boy_NPC.walk_step = 0;
		m_Boy_NPC.walk_flag = false;
		m_Boy_NPC.hurt_flag = true;
	}
	


	if (m_Boy_NPC.hurt_flag == true )
	{
		m_Boy_NPC.hurt();
		Message.in_Texture_SetData_factors(0, 0, 1241, 735, 1241, 735);
		Message.m_for_update_Rects.x = g_rtClient.right / 2;    Message.m_for_update_Rects.y = g_rtClient.bottom / 2;
		Message.Window_SetData_factors(200, 50, Message.m_for_update_Rects.x, Message.m_for_update_Rects.y);
		Message.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Board_UI.png");
	}

	//ENTER KEY 누르면, 원래대로 서고, 해야 한다.
	
	
		if (I_Input.Key(VK_RETURN))
		{

			m_Boy_NPC.hurt_flag = false;
			m_Boy_NPC.walk_flag = false;
			m_Boy_NPC.Enter_flag_1 = true;


			m_Boy_NPC.m_for_update_Rects.x = g_rtClient.right / 9;    m_Boy_NPC.m_for_update_Rects.y = g_rtClient.bottom / 5;
			m_Boy_NPC.in_Texture_SetData_factors(568, 327, 76, 61, 757, 1274);
			m_Boy_NPC.Window_SetData_factors(60, 310, m_Boy_NPC.m_for_update_Rects.x, m_Boy_NPC.m_for_update_Rects.y); // 텍스쳐 시작점 왼위점 좌표 + 텍스쳐 가로-세로 크기.
			m_Boy_NPC.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/woman_man_plus.png");

			
			Message.in_Texture_SetData_factors(0, 0, 1241, 735, 1241, 735);
			Message.m_for_update_Rects.x = g_rtClient.right / 100;    Message.m_for_update_Rects.y = g_rtClient.bottom / 100;
			Message.Window_SetData_factors(900, 50, Message.m_for_update_Rects.x, Message.m_for_update_Rects.y);
			Message.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Board_UI.png");
		}


	/////////////////////////////////////////////////////////////////////////   기본 걷는 동작

	if (m_Boy_NPC.walk_flag == true)
	{

		m_Boy_NPC.walk();
		if (m_Boy_NPC.walk_step == 1) { m_Boy_NPC.MoveX(g_fSecPerFrame*0.05f); }
		if (m_Boy_NPC.walk_step == 2) { m_Boy_NPC.MoveX(g_fSecPerFrame*0.05f); }        if (m_Boy_NPC.walk_step == 3) { m_Boy_NPC.MoveX(g_fSecPerFrame*0.05f); }
		if (m_Boy_NPC.walk_step == 4) { m_Boy_NPC.MoveX(g_fSecPerFrame*0.05f); }        if (m_Boy_NPC.walk_step == 5) { m_Boy_NPC.MoveX(g_fSecPerFrame*0.05f); }
		if (m_Boy_NPC.walk_step == 6) { m_Boy_NPC.MoveX(g_fSecPerFrame*0.05f); }        if (m_Boy_NPC.walk_step == 7) { m_Boy_NPC.MoveX(g_fSecPerFrame*0.05f); }
		if (m_Boy_NPC.walk_step == 8) { m_Boy_NPC.MoveX(g_fSecPerFrame*0.05f); }        if (m_Boy_NPC.walk_step == 9) { m_Boy_NPC.MoveX(g_fSecPerFrame*0.05f); }
		if (m_Boy_NPC.walk_step == 10) { m_Boy_NPC.MoveX(g_fSecPerFrame*0.05f); }
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

}


void TSceneGame::Hero_bullets_basic_Action()
{
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

	//////////////     총알의 움직임   /////////////////////////////////////

	if (Bullet_F1.Bullet_Go == true && m_Actor.Face_Direction == 1)
	{
		Bullet_F1.Bullet_Go = false; Bullet_F1.Face_Direction1_flag = true;
		Bullet_F1.m_VertexList[0].x = m_Actor.m_VertexList[0].x - 30 / 900; Bullet_F1.m_VertexList[0].y = m_Actor.m_VertexList[0].y - 5 / 900;
		Bullet_F1.m_VertexList[1].x = m_Actor.m_VertexList[1].x - 30 / 900; Bullet_F1.m_VertexList[1].y = m_Actor.m_VertexList[1].y - 5 / 900;
		Bullet_F1.m_VertexList[2].x = m_Actor.m_VertexList[2].x - 30 / 900; Bullet_F1.m_VertexList[2].y = m_Actor.m_VertexList[2].y - 5 / 900;
		Bullet_F1.m_VertexList[3].x = m_Actor.m_VertexList[3].x - 30 / 900; Bullet_F1.m_VertexList[3].y = m_Actor.m_VertexList[3].y - 5 / 900;
		Bullet_F1.m_VertexList[4].x = m_Actor.m_VertexList[4].x - 30 / 900; Bullet_F1.m_VertexList[4].y = m_Actor.m_VertexList[4].y - 5 / 900;
		Bullet_F1.m_VertexList[5].x = m_Actor.m_VertexList[5].x - 30 / 900; Bullet_F1.m_VertexList[5].y = m_Actor.m_VertexList[5].y - 5 / 900;
		Bullet_F1.m_VertexList[6].x = m_Actor.m_VertexList[6].x - 30 / 900; Bullet_F1.m_VertexList[6].y = m_Actor.m_VertexList[6].y - 5 / 900;
	}

	if (Bullet_F1.Bullet_Go == true && m_Actor.Face_Direction == 2)
	{
		Bullet_F1.Bullet_Go = false; Bullet_F1.Face_Direction2_flag = true;
		Bullet_F1.m_VertexList[0].x = m_Actor.m_VertexList[0].x + 30 / 900; Bullet_F1.m_VertexList[0].y = m_Actor.m_VertexList[0].y + 5 / 900;
		Bullet_F1.m_VertexList[1].x = m_Actor.m_VertexList[1].x + 30 / 900; Bullet_F1.m_VertexList[1].y = m_Actor.m_VertexList[1].y + 5 / 900;
		Bullet_F1.m_VertexList[2].x = m_Actor.m_VertexList[2].x + 30 / 900; Bullet_F1.m_VertexList[2].y = m_Actor.m_VertexList[2].y + 5 / 900;
		Bullet_F1.m_VertexList[3].x = m_Actor.m_VertexList[3].x + 30 / 900; Bullet_F1.m_VertexList[3].y = m_Actor.m_VertexList[3].y + 5 / 900;
		Bullet_F1.m_VertexList[4].x = m_Actor.m_VertexList[4].x + 30 / 900; Bullet_F1.m_VertexList[4].y = m_Actor.m_VertexList[4].y + 5 / 900;
		Bullet_F1.m_VertexList[5].x = m_Actor.m_VertexList[5].x + 30 / 900; Bullet_F1.m_VertexList[5].y = m_Actor.m_VertexList[5].y + 5 / 900;
		Bullet_F1.m_VertexList[6].x = m_Actor.m_VertexList[6].x + 30 / 900; Bullet_F1.m_VertexList[6].y = m_Actor.m_VertexList[6].y + 5 / 900;
	}

	if (Bullet_F1.Face_Direction1_flag == true)
	{
		Bullet_F1.frame_F();
		if (Bullet_F1.bullet_step == 0) { Bullet_F1.MoveX(-g_fSecPerFrame * 1.0f); }        if (Bullet_F1.bullet_step == 1) { Bullet_F1.MoveX(-g_fSecPerFrame * 1.0f); }
		if (Bullet_F1.bullet_step == 2) { Bullet_F1.MoveX(-g_fSecPerFrame * 1.0f); }        if (Bullet_F1.bullet_step == 3) { Bullet_F1.MoveX(-g_fSecPerFrame * 1.0f); }
		if (Bullet_F1.bullet_step == 4) { Bullet_F1.MoveX(-g_fSecPerFrame * 1.0f); }        if (Bullet_F1.bullet_step == 5) { Bullet_F1.MoveX(-g_fSecPerFrame * 1.0f); }
		if (Bullet_F1.bullet_step == 6) { Bullet_F1.MoveX(-g_fSecPerFrame * 1.0f); }
	}

	if (Bullet_F1.Face_Direction2_flag == true)
	{
		Bullet_F1.frame_F();
		if (Bullet_F1.bullet_step == 0) { Bullet_F1.MoveX(g_fSecPerFrame*1.0f); }        if (Bullet_F1.bullet_step == 1) { Bullet_F1.MoveX(g_fSecPerFrame*1.0f); }
		if (Bullet_F1.bullet_step == 2) { Bullet_F1.MoveX(g_fSecPerFrame*1.0f); }        if (Bullet_F1.bullet_step == 3) { Bullet_F1.MoveX(g_fSecPerFrame*1.0f); }
		if (Bullet_F1.bullet_step == 4) { Bullet_F1.MoveX(g_fSecPerFrame*1.0f); }        if (Bullet_F1.bullet_step == 5) { Bullet_F1.MoveX(g_fSecPerFrame*1.0f); }
		if (Bullet_F1.bullet_step == 6) { Bullet_F1.MoveX(g_fSecPerFrame*1.0f); }
	}

	memcpy(N_VertexList_F1, Bullet_F1.m_VertexList, sizeof(SimpleVertex) * 6);
	for (int iV = 0; iV < 6; iV++)
	{
		D3DVECTOR vertex;
		vertex.x = Bullet_F1.m_VertexList[iV].x; vertex.y = Bullet_F1.m_VertexList[iV].y;
		vertex.x -= Bullet_F1.m_vCenter.x;		 vertex.y -= Bullet_F1.m_vCenter.y;
		float S = sinf(fAngle);	float C = cosf(fAngle);
		N_VertexList_F1[iV].x = vertex.x * C + vertex.y * S; N_VertexList_F1[iV].y = vertex.x * -S + vertex.y * C;
		N_VertexList_F1[iV].x += Bullet_F1.m_vCenter.x;		 N_VertexList_F1[iV].y += Bullet_F1.m_vCenter.y;
	}
	g_pContext->UpdateSubresource(Bullet_F1.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_F1, 0, 0);

	//////////////     총알의 움직임   /////////////////////////////////////

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

	//////////////     총알의 움직임   /////////////////////////////////////


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

	//////////////     총알의 움직임   /////////////////////////////////////

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

	//////////////     총알의 움직임   /////////////////////////////////////

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

	//////////////     총알의 움직임   /////////////////////////////////////

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




	//////////////     총알의 움직임   /////////////////////////////////////

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


}


void TSceneGame::Tresure_Box__m_Actor_Dection_collision_and_ghost_shots()
{
	if (TCollision::SphereInSphere(m_Actor.m_rtCollision, Box_Alive.m_rtDetection))
	{
		Box_Alive.frame();
	}


	if (!TCollision::SphereInSphere(m_Actor.m_rtCollision, Box_Alive.m_rtDetection))
	{
		Box_Alive.detection_time = 0.0f;
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	
	if (Box_Alive.Bullet_G1_Bullet_Go == true)
	{
		Box_Alive.Bullet_G1_Bullet_Go = false; Bullet_Ghost_1.Face_Direction1_flag = true;
		Bullet_Ghost_1.m_VertexList[0].x =Box_Alive.m_VertexList[0].x; Bullet_Ghost_1.m_VertexList[0].y =Box_Alive.m_VertexList[0].y ;
		Bullet_Ghost_1.m_VertexList[1].x =Box_Alive.m_VertexList[1].x; Bullet_Ghost_1.m_VertexList[1].y =Box_Alive.m_VertexList[1].y ;
		Bullet_Ghost_1.m_VertexList[2].x =Box_Alive.m_VertexList[2].x; Bullet_Ghost_1.m_VertexList[2].y =Box_Alive.m_VertexList[2].y ;
		Bullet_Ghost_1.m_VertexList[3].x =Box_Alive.m_VertexList[3].x; Bullet_Ghost_1.m_VertexList[3].y =Box_Alive.m_VertexList[3].y ;
		Bullet_Ghost_1.m_VertexList[4].x =Box_Alive.m_VertexList[4].x; Bullet_Ghost_1.m_VertexList[4].y =Box_Alive.m_VertexList[4].y ;
		Bullet_Ghost_1.m_VertexList[5].x =Box_Alive.m_VertexList[5].x; Bullet_Ghost_1.m_VertexList[5].y =Box_Alive.m_VertexList[5].y ;
		Bullet_Ghost_1.m_VertexList[6].x =Box_Alive.m_VertexList[6].x; Bullet_Ghost_1.m_VertexList[6].y =Box_Alive.m_VertexList[6].y ;
	}

	if (Bullet_Ghost_1.Face_Direction1_flag == true)
	{Bullet_Ghost_1.MoveX(-g_fSecPerFrame * 1.0f);}
	memcpy(N_VertexList_G1, Bullet_Ghost_1.m_VertexList, sizeof(SimpleVertex) * 6);

	for (int iV = 0; iV < 6; iV++)
	{
		D3DVECTOR vertex;
		vertex.x = Bullet_Ghost_1.m_VertexList[iV].x; vertex.y = Bullet_Ghost_1.m_VertexList[iV].y;
		vertex.x -= Bullet_Ghost_1.m_vCenter.x;		 vertex.y -= Bullet_Ghost_1.m_vCenter.y;
		float S = sinf(fAngle);	float C = cosf(fAngle);
		N_VertexList_G1[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G1[iV].y = vertex.x * -S + vertex.y * C;
		N_VertexList_G1[iV].x += Bullet_Ghost_1.m_vCenter.x;		 N_VertexList_G1[iV].y += Bullet_Ghost_1.m_vCenter.y;
	}
	g_pContext->UpdateSubresource(Bullet_Ghost_1.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G1, 0, 0);




	////////////////////////////////////////////////////////////////////////////////////////////////////////


	if (Box_Alive.Bullet_G2_Bullet_Go == true)
	{
		Box_Alive.Bullet_G2_Bullet_Go = false; Bullet_Ghost_2.Face_Direction1_flag = true;
		Bullet_Ghost_2.m_VertexList[0].x = Box_Alive.m_VertexList[0].x; Bullet_Ghost_2.m_VertexList[0].y = Box_Alive.m_VertexList[0].y;
		Bullet_Ghost_2.m_VertexList[1].x = Box_Alive.m_VertexList[1].x; Bullet_Ghost_2.m_VertexList[1].y = Box_Alive.m_VertexList[1].y;
		Bullet_Ghost_2.m_VertexList[2].x = Box_Alive.m_VertexList[2].x; Bullet_Ghost_2.m_VertexList[2].y = Box_Alive.m_VertexList[2].y;
		Bullet_Ghost_2.m_VertexList[3].x = Box_Alive.m_VertexList[3].x; Bullet_Ghost_2.m_VertexList[3].y = Box_Alive.m_VertexList[3].y;
		Bullet_Ghost_2.m_VertexList[4].x = Box_Alive.m_VertexList[4].x; Bullet_Ghost_2.m_VertexList[4].y = Box_Alive.m_VertexList[4].y;
		Bullet_Ghost_2.m_VertexList[5].x = Box_Alive.m_VertexList[5].x; Bullet_Ghost_2.m_VertexList[5].y = Box_Alive.m_VertexList[5].y;
		Bullet_Ghost_2.m_VertexList[6].x = Box_Alive.m_VertexList[6].x; Bullet_Ghost_2.m_VertexList[6].y = Box_Alive.m_VertexList[6].y;
	}

	if (Bullet_Ghost_2.Face_Direction1_flag == true)
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
		N_VertexList_G2[iV].x += Bullet_Ghost_2.m_vCenter.x;		 N_VertexList_G2[iV].y += Bullet_Ghost_2.m_vCenter.y;
	}
	g_pContext->UpdateSubresource(Bullet_Ghost_2.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G2, 0, 0);






	////////////////////////////////////////////////////////////////////////////////////////////////////////


	if (Box_Alive.Bullet_G3_Bullet_Go == true)
	{
		Box_Alive.Bullet_G3_Bullet_Go = false; Bullet_Ghost_3.Face_Direction1_flag = true;
		Bullet_Ghost_3.m_VertexList[0].x = Box_Alive.m_VertexList[0].x; Bullet_Ghost_3.m_VertexList[0].y = Box_Alive.m_VertexList[0].y;
		Bullet_Ghost_3.m_VertexList[1].x = Box_Alive.m_VertexList[1].x; Bullet_Ghost_3.m_VertexList[1].y = Box_Alive.m_VertexList[1].y;
		Bullet_Ghost_3.m_VertexList[2].x = Box_Alive.m_VertexList[2].x; Bullet_Ghost_3.m_VertexList[2].y = Box_Alive.m_VertexList[2].y;
		Bullet_Ghost_3.m_VertexList[3].x = Box_Alive.m_VertexList[3].x; Bullet_Ghost_3.m_VertexList[3].y = Box_Alive.m_VertexList[3].y;
		Bullet_Ghost_3.m_VertexList[4].x = Box_Alive.m_VertexList[4].x; Bullet_Ghost_3.m_VertexList[4].y = Box_Alive.m_VertexList[4].y;
		Bullet_Ghost_3.m_VertexList[5].x = Box_Alive.m_VertexList[5].x; Bullet_Ghost_3.m_VertexList[5].y = Box_Alive.m_VertexList[5].y;
		Bullet_Ghost_3.m_VertexList[6].x = Box_Alive.m_VertexList[6].x; Bullet_Ghost_3.m_VertexList[6].y = Box_Alive.m_VertexList[6].y;
	}

	if (Bullet_Ghost_3.Face_Direction1_flag == true)
	{
		Bullet_Ghost_3.MoveX(-g_fSecPerFrame * 1.0f);
	}
	memcpy(N_VertexList_G3, Bullet_Ghost_3.m_VertexList, sizeof(SimpleVertex) * 6);

	for (int iV = 0; iV < 6; iV++)
	{
		D3DVECTOR vertex;
		vertex.x = Bullet_Ghost_3.m_VertexList[iV].x; vertex.y = Bullet_Ghost_3.m_VertexList[iV].y;
		vertex.x -= Bullet_Ghost_3.m_vCenter.x;		 vertex.y -= Bullet_Ghost_3.m_vCenter.y;
		float S = sinf(fAngle);	float C = cosf(fAngle);
		N_VertexList_G3[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G3[iV].y = vertex.x * -S + vertex.y * C;
		N_VertexList_G3[iV].x += Bullet_Ghost_3.m_vCenter.x;		 N_VertexList_G3[iV].y += Bullet_Ghost_3.m_vCenter.y;
	}
	g_pContext->UpdateSubresource(Bullet_Ghost_3.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G3, 0, 0);

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (Box_Alive.Bullet_G4_Bullet_Go == true)
	{
		Box_Alive.Bullet_G4_Bullet_Go = false; Bullet_Ghost_4.Face_Direction1_flag = true;
		Bullet_Ghost_4.m_VertexList[0].x = Box_Alive.m_VertexList[0].x; Bullet_Ghost_4.m_VertexList[0].y = Box_Alive.m_VertexList[0].y;
		Bullet_Ghost_4.m_VertexList[1].x = Box_Alive.m_VertexList[1].x; Bullet_Ghost_4.m_VertexList[1].y = Box_Alive.m_VertexList[1].y;
		Bullet_Ghost_4.m_VertexList[2].x = Box_Alive.m_VertexList[2].x; Bullet_Ghost_4.m_VertexList[2].y = Box_Alive.m_VertexList[2].y;
		Bullet_Ghost_4.m_VertexList[3].x = Box_Alive.m_VertexList[3].x; Bullet_Ghost_4.m_VertexList[3].y = Box_Alive.m_VertexList[3].y;
		Bullet_Ghost_4.m_VertexList[4].x = Box_Alive.m_VertexList[4].x; Bullet_Ghost_4.m_VertexList[4].y = Box_Alive.m_VertexList[4].y;
		Bullet_Ghost_4.m_VertexList[5].x = Box_Alive.m_VertexList[5].x; Bullet_Ghost_4.m_VertexList[5].y = Box_Alive.m_VertexList[5].y;
		Bullet_Ghost_4.m_VertexList[6].x = Box_Alive.m_VertexList[6].x; Bullet_Ghost_4.m_VertexList[6].y = Box_Alive.m_VertexList[6].y;
	}

	if (Bullet_Ghost_4.Face_Direction1_flag == true)
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
		N_VertexList_G4[iV].x += Bullet_Ghost_4.m_vCenter.x;		 N_VertexList_G4[iV].y += Bullet_Ghost_4.m_vCenter.y;
	}
	g_pContext->UpdateSubresource(Bullet_Ghost_4.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G4, 0, 0);
}


void TSceneGame::Boss_collision_final_decision()
{
	
	Robot_live_or_dead = Robot_Col_F1 + Robot_Col_C1 +	Robot_Col_F2 + Robot_Col_C2 +	Robot_Col_F3 + Robot_Col_C3 +	Robot_Col_F4 + Robot_Col_C4+Robot_Col_S1 + Robot_Col_S2 + Robot_Col_S3 + Robot_Col_S4;

	if (Robot_live_or_dead== 1)
	{
		Robot_life_bar.in_Texture_SetData_factors(0, 0, 299, 76, 299, 76);
		Robot_life_bar.m_for_update_Rects.x = g_rtClient.right / 3;    Robot_life_bar.m_for_update_Rects.y = g_rtClient.bottom / 8;
		Robot_life_bar.Window_SetData_factors(400, 5, Robot_life_bar.m_for_update_Rects.x, Robot_life_bar.m_for_update_Rects.y);
		Robot_life_bar.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/3_4_Bar_B.png");
	}

	if (Robot_live_or_dead == 2)
	{
		Robot_life_bar.in_Texture_SetData_factors(0, 0, 299, 76, 299, 76);
		Robot_life_bar.m_for_update_Rects.x = g_rtClient.right / 3;    Robot_life_bar.m_for_update_Rects.y = g_rtClient.bottom / 8;
		Robot_life_bar.Window_SetData_factors(400, 5, Robot_life_bar.m_for_update_Rects.x, Robot_life_bar.m_for_update_Rects.y);
		Robot_life_bar.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/2_4_Bar_B.png");
	}

	if (Robot_live_or_dead == 3)
	{
		Robot_life_bar.in_Texture_SetData_factors(0, 0, 299, 76, 299, 76);
		Robot_life_bar.m_for_update_Rects.x = g_rtClient.right / 3;    Robot_life_bar.m_for_update_Rects.y = g_rtClient.bottom / 8;
		Robot_life_bar.Window_SetData_factors(400, 5, Robot_life_bar.m_for_update_Rects.x, Robot_life_bar.m_for_update_Rects.y);
		Robot_life_bar.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/1_4_Bar_B.png");
	}


	if (Robot_live_or_dead	== 4)
	{
		Robot_life_bar.in_Texture_SetData_factors(0, 0, 299, 76, 299, 76);
		Robot_life_bar.m_for_update_Rects.x = g_rtClient.right / 30;    Robot_life_bar.m_for_update_Rects.y = g_rtClient.bottom / 30;
		Robot_life_bar.Window_SetData_factors(1000, 10, Robot_life_bar.m_for_update_Rects.x, Robot_life_bar.m_for_update_Rects.y);
		Robot_life_bar.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/0_Bar_B.png");


		Bullet_B1.in_Texture_SetData_factors(170, 761, 143, 139, 702, 1843);
		Bullet_B1.m_for_update_Rects.x = g_rtClient.right / 30;    Bullet_B1.m_for_update_Rects.y = g_rtClient.bottom / 30;
		Bullet_B1.Window_SetData_factors(-100, 30, Bullet_B1.m_for_update_Rects.x, Bullet_B1.m_for_update_Rects.y);
		Bullet_B1.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");

		Bullet_B2.in_Texture_SetData_factors(170, 761, 143, 139, 702, 1843);
		Bullet_B2.m_for_update_Rects.x = g_rtClient.right / 30;    Bullet_B2.m_for_update_Rects.y = g_rtClient.bottom / 30;
		Bullet_B2.Window_SetData_factors(-100, 80, Bullet_B2.m_for_update_Rects.x, Bullet_B2.m_for_update_Rects.y);
		Bullet_B2.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");

		Bullet_B3.in_Texture_SetData_factors(170, 761, 143, 139, 702, 1843);
		Bullet_B3.m_for_update_Rects.x = g_rtClient.right / 30;    Bullet_B3.m_for_update_Rects.y = g_rtClient.bottom / 30;
		Bullet_B3.Window_SetData_factors(-100, 130, Bullet_B3.m_for_update_Rects.x, Bullet_B3.m_for_update_Rects.y);
		Bullet_B3.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");

		Bullet_B4.in_Texture_SetData_factors(170, 761, 143, 139, 702, 1843);
		Bullet_B4.m_for_update_Rects.x = g_rtClient.right / 30;    Bullet_B4.m_for_update_Rects.y = g_rtClient.bottom / 30;
		Bullet_B4.Window_SetData_factors(-100, 180, Bullet_B4.m_for_update_Rects.x, Bullet_B4.m_for_update_Rects.y);
		Bullet_B4.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/robot.png");


		Robot.m_VertexList[0].x = 3.115f; Robot.m_VertexList[0].y = 3.115f;
		Robot.m_VertexList[1].x = 3.115f; Robot.m_VertexList[1].y = 3.115f;
		Robot.m_VertexList[2].x = 3.115f; Robot.m_VertexList[2].y = 3.115f;
		Robot.m_VertexList[3].x = 3.115f; Robot.m_VertexList[3].y = 3.115f;
		Robot.m_VertexList[4].x = 3.115f; Robot.m_VertexList[4].y = 3.115f;
		Robot.m_VertexList[5].x = 3.115f; Robot.m_VertexList[5].y = 3.115f;
		Robot.m_VertexList[6].x = 3.115f; Robot.m_VertexList[6].y = 3.115f;

		memcpy(N_VertexList_BA, Robot.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Robot.m_VertexList[iV].x; vertex.y = Robot.m_VertexList[iV].y;
			vertex.x -= Robot.m_vCenter.x;		 vertex.y -= Robot.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_BA[iV].x = vertex.x * C + vertex.y * S; N_VertexList_BA[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_BA[iV].x += Robot.m_vCenter.x;		 N_VertexList_BA[iV].y += Robot.m_vCenter.y;
		}
		g_pContext->UpdateSubresource(Robot.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_BA, 0, 0);
	}
}

void TSceneGame::Boy_NPC_collision_from_hero_attack()
{
	//////////////// Hero sword attack과  Boy_NPC 충돌

	if (I_Input.Key('O') == KEY_PUSH && TCollision::SphereInSphere(m_Actor.m_rtCollision, m_Boy_NPC.m_rtCollision) && NPC_live_or_dead == 0)
	{
		NPC_Col_S1 = true;
	}

	if (I_Input.Key('O') == KEY_PUSH && TCollision::SphereInSphere(m_Actor.m_rtCollision, m_Boy_NPC.m_rtCollision) && NPC_live_or_dead == 1)
	{
		NPC_Col_S2 = true; 
	}

	/////////////////////////////////// Bullet_F3과  Boy_NPC 충돌

	if (TCollision::SphereInSphere(Bullet_F3.m_rtCollision, m_Boy_NPC.m_rtCollision))
	{
		Bullet_F3.m_VertexList[0].x = 2.5f; Bullet_F3.m_VertexList[0].y = 2.5f;
		Bullet_F3.m_VertexList[1].x = 2.5f; Bullet_F3.m_VertexList[1].y = 2.5f;
		Bullet_F3.m_VertexList[2].x = 2.5f; Bullet_F3.m_VertexList[2].y = 2.5f;
		Bullet_F3.m_VertexList[3].x = 2.5f; Bullet_F3.m_VertexList[3].y = 2.5f;
		Bullet_F3.m_VertexList[4].x = 2.5f; Bullet_F3.m_VertexList[4].y = 2.5f;
		Bullet_F3.m_VertexList[5].x = 2.5f; Bullet_F3.m_VertexList[5].y = 2.5f;
		Bullet_F3.m_VertexList[6].x = 2.5f; Bullet_F3.m_VertexList[6].y = 2.5f;

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

		NPC_Col_F3 = true;
	}


	/////////////////////////////////// Bullet_F4과  Box_Alive 충돌

	if (TCollision::SphereInSphere(Bullet_F4.m_rtCollision, m_Boy_NPC.m_rtCollision))
	{
		Bullet_F4.m_VertexList[0].x = 2.5f; Bullet_F4.m_VertexList[0].y = 2.5f;
		Bullet_F4.m_VertexList[1].x = 2.5f; Bullet_F4.m_VertexList[1].y = 2.5f;
		Bullet_F4.m_VertexList[2].x = 2.5f; Bullet_F4.m_VertexList[2].y = 2.5f;
		Bullet_F4.m_VertexList[3].x = 2.5f; Bullet_F4.m_VertexList[3].y = 2.5f;
		Bullet_F4.m_VertexList[4].x = 2.5f; Bullet_F4.m_VertexList[4].y = 2.5f;
		Bullet_F4.m_VertexList[5].x = 2.5f; Bullet_F4.m_VertexList[5].y = 2.5f;
		Bullet_F4.m_VertexList[6].x = 2.5f; Bullet_F4.m_VertexList[6].y = 2.5f;

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

		NPC_Col_F4 = true;
	}



	/////////////////////////////////// Bullet_C3과  Boy_NPC 충돌

	if (TCollision::SphereInSphere(Bullet_C3.m_rtCollision, m_Boy_NPC.m_rtCollision))
	{
		Bullet_C3.m_VertexList[0].x = 2.5f; Bullet_C3.m_VertexList[0].y = 2.5f;
		Bullet_C3.m_VertexList[1].x = 2.5f; Bullet_C3.m_VertexList[1].y = 2.5f;
		Bullet_C3.m_VertexList[2].x = 2.5f; Bullet_C3.m_VertexList[2].y = 2.5f;
		Bullet_C3.m_VertexList[3].x = 2.5f; Bullet_C3.m_VertexList[3].y = 2.5f;
		Bullet_C3.m_VertexList[4].x = 2.5f; Bullet_C3.m_VertexList[4].y = 2.5f;
		Bullet_C3.m_VertexList[5].x = 2.5f; Bullet_C3.m_VertexList[5].y = 2.5f;
		Bullet_C3.m_VertexList[6].x = 2.5f; Bullet_C3.m_VertexList[6].y = 2.5f;

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

		NPC_Col_C3 = true;
	}


	/////////////////////////////////// Bullet_C4과  Box_Alive 충돌

	if (TCollision::SphereInSphere(Bullet_C4.m_rtCollision, m_Boy_NPC.m_rtCollision))
	{
		Bullet_C4.m_VertexList[0].x = 2.5f; Bullet_C4.m_VertexList[0].y = 2.5f;
		Bullet_C4.m_VertexList[1].x = 2.5f; Bullet_C4.m_VertexList[1].y = 2.5f;
		Bullet_C4.m_VertexList[2].x = 2.5f; Bullet_C4.m_VertexList[2].y = 2.5f;
		Bullet_C4.m_VertexList[3].x = 2.5f; Bullet_C4.m_VertexList[3].y = 2.5f;
		Bullet_C4.m_VertexList[4].x = 2.5f; Bullet_C4.m_VertexList[4].y = 2.5f;
		Bullet_C4.m_VertexList[5].x = 2.5f; Bullet_C4.m_VertexList[5].y = 2.5f;
		Bullet_C4.m_VertexList[6].x = 2.5f; Bullet_C4.m_VertexList[6].y = 2.5f;

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

		NPC_Col_C4 = true;
	}
}


void TSceneGame::Herosword_box_alive_collision()
{

	//////////////// Hero sword attack과  Box_Alive 충돌

	if (m_Actor.sword_step==2 && TCollision::SphereInSphere(m_Actor.m_rtCollision, Box_Alive.m_rtCollision) && box_alive_live_or_dead == 0)
	{
		box_alive_Col_S1 = true;
	}

	if (m_Actor.sword_step == 2 && TCollision::SphereInSphere(m_Actor.m_rtCollision, Robot.m_rtCollision) && box_alive_live_or_dead == 1)
	{
		box_alive_Col_S2 = true;
	}
	
}

void TSceneGame::Boss_sword_hero_collsion()
{
	//////////////// Robot sword attack과  Hero 충돌

	
	if (Robot.sword_step == 3  && TCollision::SphereInSphere(m_Actor.m_rtCollision, Robot.m_rtCollision) && Hero_live_or_dead == 0)
	{
		Hero_Col_S1 = true;
	}

	if (Robot.sword_step == 3 && TCollision::SphereInSphere(m_Actor.m_rtCollision, Robot.m_rtCollision) && Hero_live_or_dead == 1)
	{
		Hero_Col_S2 = true;
	}

	if (Robot.sword_step == 3 && TCollision::SphereInSphere(m_Actor.m_rtCollision, Robot.m_rtCollision) && Hero_live_or_dead == 2)
	{
		Hero_Col_S3 = true;
	}

	if (Robot.sword_step == 3 && TCollision::SphereInSphere(m_Actor.m_rtCollision, Robot.m_rtCollision) && Hero_live_or_dead == 3)
	{
		Hero_Col_S4 = true;
	}


}


void TSceneGame::Herosword_boss_collision()
{

	//////////////// Hero sword attack과  Robot 충돌

	
	if (I_Input.Key('O') == KEY_PUSH && TCollision::SphereInSphere(m_Actor.m_rtCollision, Robot.m_rtCollision) && Robot_live_or_dead == 0)
	{
		Robot_Col_S1 = true;
	}

	if (I_Input.Key('O') == KEY_PUSH && TCollision::SphereInSphere(m_Actor.m_rtCollision, Robot.m_rtCollision) && Robot_live_or_dead == 1)
	{
		Robot_Col_S2 = true;
	}

	if (I_Input.Key('O') == KEY_PUSH && TCollision::SphereInSphere(m_Actor.m_rtCollision, Robot.m_rtCollision) && Robot_live_or_dead == 2)
	{
		Robot_Col_S3 = true;
	}

	if (I_Input.Key('O') == KEY_PUSH && TCollision::SphereInSphere(m_Actor.m_rtCollision, Robot.m_rtCollision) && Robot_live_or_dead == 3)
	{
		Robot_Col_S4 = true;
	}
}

void TSceneGame::Boss_Canon_hero_collision()
{

	//////////////// Bullet_B1과  m_Actor 충돌
	if (TCollision::SphereInSphere(Bullet_B1.m_rtCollision, m_Actor.m_rtCollision))
	{

		Bullet_B1.m_VertexList[0].x = 2.321f; Bullet_B1.m_VertexList[0].y = 2.321f;
		Bullet_B1.m_VertexList[1].x = 2.321f; Bullet_B1.m_VertexList[1].y = 2.321f;
		Bullet_B1.m_VertexList[2].x = 2.321f; Bullet_B1.m_VertexList[2].y = 2.321f;
		Bullet_B1.m_VertexList[3].x = 2.321f; Bullet_B1.m_VertexList[3].y = 2.321f;
		Bullet_B1.m_VertexList[4].x = 2.321f; Bullet_B1.m_VertexList[4].y = 2.321f;
		Bullet_B1.m_VertexList[5].x = 2.321f; Bullet_B1.m_VertexList[5].y = 2.321f;
		Bullet_B1.m_VertexList[6].x = 2.321f; Bullet_B1.m_VertexList[6].y = 2.321f;

		memcpy(N_VertexList_B1, Bullet_B1.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_B1.m_VertexList[iV].x; vertex.y = Bullet_B1.m_VertexList[iV].y;
			vertex.x -= Bullet_B1.m_vCenter.x;		 vertex.y -= Bullet_B1.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_B1[iV].x = vertex.x * C + vertex.y * S; N_VertexList_B1[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_B1[iV].x += Bullet_B1.m_vCenter.x;		 N_VertexList_B1[iV].y += Bullet_B1.m_vCenter.y;
		}
		g_pContext->UpdateSubresource(Bullet_B1.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_B1, 0, 0);

		Hero_Col_B1 = true;
	}


	//////////////// Bullet_B2과  m_Actor 충돌

	if (TCollision::SphereInSphere(Bullet_B2.m_rtCollision, m_Actor.m_rtCollision))
	{
		Bullet_B2.m_VertexList[0].x = 5.521f; Bullet_B2.m_VertexList[0].y = 5.521f;
		Bullet_B2.m_VertexList[1].x = 5.521f; Bullet_B2.m_VertexList[1].y = 5.521f;
		Bullet_B2.m_VertexList[2].x = 5.521f; Bullet_B2.m_VertexList[2].y = 5.521f;
		Bullet_B2.m_VertexList[3].x = 5.521f; Bullet_B2.m_VertexList[3].y = 5.521f;
		Bullet_B2.m_VertexList[4].x = 5.521f; Bullet_B2.m_VertexList[4].y = 5.521f;
		Bullet_B2.m_VertexList[5].x = 5.521f; Bullet_B2.m_VertexList[5].y = 5.521f;
		Bullet_B2.m_VertexList[6].x = 5.521f; Bullet_B2.m_VertexList[6].y = 5.521f;

		memcpy(N_VertexList_B2, Bullet_B2.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_B2.m_VertexList[iV].x; vertex.y = Bullet_B2.m_VertexList[iV].y;
			vertex.x -= Bullet_B2.m_vCenter.x;		 vertex.y -= Bullet_B2.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_B2[iV].x = vertex.x * C + vertex.y * S; N_VertexList_B2[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_B2[iV].x += Bullet_B2.m_vCenter.x;		 N_VertexList_B2[iV].y += Bullet_B2.m_vCenter.y;
		}
		g_pContext->UpdateSubresource(Bullet_B2.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_B2, 0, 0);

		Hero_Col_B2 = true;
	}

	

	/////////////////////////////////// Bullet_B3과  m_Actor 충돌

	if (TCollision::SphereInSphere(Bullet_B3.m_rtCollision, m_Actor.m_rtCollision))
	{
		Bullet_B3.m_VertexList[0].x = 4.555f; Bullet_B3.m_VertexList[0].y = 4.555f;
		Bullet_B3.m_VertexList[1].x = 4.555f; Bullet_B3.m_VertexList[1].y = 4.555f;
		Bullet_B3.m_VertexList[2].x = 4.555f; Bullet_B3.m_VertexList[2].y = 4.555f;
		Bullet_B3.m_VertexList[3].x = 4.555f; Bullet_B3.m_VertexList[3].y = 4.555f;
		Bullet_B3.m_VertexList[4].x = 4.555f; Bullet_B3.m_VertexList[4].y = 4.555f;
		Bullet_B3.m_VertexList[5].x = 4.555f; Bullet_B3.m_VertexList[5].y = 4.555f;
		Bullet_B3.m_VertexList[6].x = 4.555f; Bullet_B3.m_VertexList[6].y = 4.555f;

		memcpy(N_VertexList_B3, Bullet_B3.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_B3.m_VertexList[iV].x; vertex.y = Bullet_B3.m_VertexList[iV].y;
			vertex.x -= Bullet_B3.m_vCenter.x;		 vertex.y -= Bullet_B3.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_B3[iV].x = vertex.x * C + vertex.y * S; N_VertexList_B3[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_B3[iV].x += Bullet_B3.m_vCenter.x;		 N_VertexList_B3[iV].y += Bullet_B3.m_vCenter.y;
		}
		g_pContext->UpdateSubresource(Bullet_B3.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_B3, 0, 0);

		Hero_Col_B3 = true;
	}


	/////////////////////////////////// Bullet_B4과  m_Actor 충돌

	if (TCollision::SphereInSphere(Bullet_B4.m_rtCollision, m_Actor.m_rtCollision))
	{
		Bullet_B4.m_VertexList[0].x = 6.523f; Bullet_B4.m_VertexList[0].y = 6.523f;
		Bullet_B4.m_VertexList[1].x = 6.523f; Bullet_B4.m_VertexList[1].y = 6.523f;
		Bullet_B4.m_VertexList[2].x = 6.523f; Bullet_B4.m_VertexList[2].y = 6.523f;
		Bullet_B4.m_VertexList[3].x = 6.523f; Bullet_B4.m_VertexList[3].y = 6.523f;
		Bullet_B4.m_VertexList[4].x = 6.523f; Bullet_B4.m_VertexList[4].y = 6.523f;
		Bullet_B4.m_VertexList[5].x = 6.523f; Bullet_B4.m_VertexList[5].y = 6.523f;
		Bullet_B4.m_VertexList[6].x = 6.523f; Bullet_B4.m_VertexList[6].y = 6.523f;

		memcpy(N_VertexList_B4, Bullet_B4.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_B4.m_VertexList[iV].x; vertex.y = Bullet_B4.m_VertexList[iV].y;
			vertex.x -= Bullet_B4.m_vCenter.x;		 vertex.y -= Bullet_B4.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_B4[iV].x = vertex.x * C + vertex.y * S; N_VertexList_B4[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_B4[iV].x += Bullet_B4.m_vCenter.x;		 N_VertexList_B4[iV].y += Bullet_B4.m_vCenter.y;
		}
		g_pContext->UpdateSubresource(Bullet_B4.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_B4, 0, 0);

		Hero_Col_B4 = true;
	
	}


}


void TSceneGame::Bullet_Boss_collision()
{
	//////////////// Bullet_F1과  Robot 충돌
	if (TCollision::SphereInSphere(Bullet_F1.m_rtCollision, Robot.m_rtCollision))
	{

		Bullet_F1.m_VertexList[0].x = 2.542f; Bullet_F1.m_VertexList[0].y = 2.542f;
		Bullet_F1.m_VertexList[1].x = 2.542f; Bullet_F1.m_VertexList[1].y = 2.542f;
		Bullet_F1.m_VertexList[2].x = 2.542f; Bullet_F1.m_VertexList[2].y = 2.542f;
		Bullet_F1.m_VertexList[3].x = 2.542f; Bullet_F1.m_VertexList[3].y = 2.542f;
		Bullet_F1.m_VertexList[4].x = 2.542f; Bullet_F1.m_VertexList[4].y = 2.542f;
		Bullet_F1.m_VertexList[5].x = 2.542f; Bullet_F1.m_VertexList[5].y = 2.542f;
		Bullet_F1.m_VertexList[6].x = 2.542f; Bullet_F1.m_VertexList[6].y = 2.542f;

		memcpy(N_VertexList_F1, Bullet_F1.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_F1.m_VertexList[iV].x; vertex.y = Bullet_F1.m_VertexList[iV].y;
			vertex.x -= Bullet_F1.m_vCenter.x;		 vertex.y -= Bullet_F1.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_F1[iV].x = vertex.x * C + vertex.y * S; N_VertexList_F1[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_F1[iV].x += Bullet_F1.m_vCenter.x;		 N_VertexList_F1[iV].y += Bullet_F1.m_vCenter.y;
		}
		g_pContext->UpdateSubresource(Bullet_F1.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_F1, 0, 0);

		Robot_Col_F1 = true;
	}


	//////////////// Bullet_F2과  Robot 충돌

	if (TCollision::SphereInSphere(Bullet_F2.m_rtCollision, Robot.m_rtCollision))
	{
		Bullet_F2.m_VertexList[0].x = 2.723f; Bullet_F2.m_VertexList[0].y = 2.723f;
		Bullet_F2.m_VertexList[1].x = 2.723f; Bullet_F2.m_VertexList[1].y = 2.723f;
		Bullet_F2.m_VertexList[2].x = 2.723f; Bullet_F2.m_VertexList[2].y = 2.723f;
		Bullet_F2.m_VertexList[3].x = 2.723f; Bullet_F2.m_VertexList[3].y = 2.723f;
		Bullet_F2.m_VertexList[4].x = 2.723f; Bullet_F2.m_VertexList[4].y = 2.723f;
		Bullet_F2.m_VertexList[5].x = 2.723f; Bullet_F2.m_VertexList[5].y = 2.723f;
		Bullet_F2.m_VertexList[6].x = 2.723f; Bullet_F2.m_VertexList[6].y = 2.723f;

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

		Robot_Col_F2 = true;
	}

	/////////////////////////////////// Bullet_F3과  Robot 충돌

	if (TCollision::SphereInSphere(Bullet_F3.m_rtCollision, Robot.m_rtCollision))
	{
		Bullet_F3.m_VertexList[0].x = 4.211f; Bullet_F3.m_VertexList[0].y = 4.211f;
		Bullet_F3.m_VertexList[1].x = 4.211f; Bullet_F3.m_VertexList[1].y = 4.211f;
		Bullet_F3.m_VertexList[2].x = 4.211f; Bullet_F3.m_VertexList[2].y = 4.211f;
		Bullet_F3.m_VertexList[3].x = 4.211f; Bullet_F3.m_VertexList[3].y = 4.211f;
		Bullet_F3.m_VertexList[4].x = 4.211f; Bullet_F3.m_VertexList[4].y = 4.211f;
		Bullet_F3.m_VertexList[5].x = 4.211f; Bullet_F3.m_VertexList[5].y = 4.211f;
		Bullet_F3.m_VertexList[6].x = 4.211f; Bullet_F3.m_VertexList[6].y = 4.211f;

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

		Robot_Col_F3 = true;
	}


	/////////////////////////////////// Bullet_F4과  Robot 충돌

	if (TCollision::SphereInSphere(Bullet_F4.m_rtCollision, Robot.m_rtCollision))
	{
		Bullet_F4.m_VertexList[0].x = 5.044f; Bullet_F4.m_VertexList[0].y = 5.044f;
		Bullet_F4.m_VertexList[1].x = 5.044f; Bullet_F4.m_VertexList[1].y = 5.044f;
		Bullet_F4.m_VertexList[2].x = 5.044f; Bullet_F4.m_VertexList[2].y = 5.044f;
		Bullet_F4.m_VertexList[3].x = 5.044f; Bullet_F4.m_VertexList[3].y = 5.044f;
		Bullet_F4.m_VertexList[4].x = 5.044f; Bullet_F4.m_VertexList[4].y = 5.044f;
		Bullet_F4.m_VertexList[5].x = 5.044f; Bullet_F4.m_VertexList[5].y = 5.044f;
		Bullet_F4.m_VertexList[6].x = 5.044f; Bullet_F4.m_VertexList[6].y = 5.044f;

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

		Robot_Col_F4 = true;

	}


	//////////////// Bullet_C1과  Robot 충돌

	if (TCollision::SphereInSphere(Bullet_C1.m_rtCollision, Robot.m_rtCollision))
	{

		Bullet_C1.m_VertexList[0].x = 5.372f; Bullet_C1.m_VertexList[0].y = 5.372f;
		Bullet_C1.m_VertexList[1].x = 5.372f; Bullet_C1.m_VertexList[1].y = 5.372f;
		Bullet_C1.m_VertexList[2].x = 5.372f; Bullet_C1.m_VertexList[2].y = 5.372f;
		Bullet_C1.m_VertexList[3].x = 5.372f; Bullet_C1.m_VertexList[3].y = 5.372f;
		Bullet_C1.m_VertexList[4].x = 5.372f; Bullet_C1.m_VertexList[4].y = 5.372f;
		Bullet_C1.m_VertexList[5].x = 5.372f; Bullet_C1.m_VertexList[5].y = 5.372f;
		Bullet_C1.m_VertexList[6].x = 5.372f; Bullet_C1.m_VertexList[6].y = 5.372f;

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

		Robot_Col_C1 = true;
	}


	//////////////// Bullet_C2과  Robot 충돌

	if (TCollision::SphereInSphere(Bullet_C2.m_rtCollision, Robot.m_rtCollision))
	{
		Bullet_C2.m_VertexList[0].x = 6.231f; Bullet_C2.m_VertexList[0].y = 6.231f;
		Bullet_C2.m_VertexList[1].x = 6.231f; Bullet_C2.m_VertexList[1].y = 6.231f;
		Bullet_C2.m_VertexList[2].x = 6.231f; Bullet_C2.m_VertexList[2].y = 6.231f;
		Bullet_C2.m_VertexList[3].x = 6.231f; Bullet_C2.m_VertexList[3].y = 6.231f;
		Bullet_C2.m_VertexList[4].x = 6.231f; Bullet_C2.m_VertexList[4].y = 6.231f;
		Bullet_C2.m_VertexList[5].x = 6.231f; Bullet_C2.m_VertexList[5].y = 6.231f;
		Bullet_C2.m_VertexList[6].x = 6.231f; Bullet_C2.m_VertexList[6].y = 6.231f;

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

		Robot_Col_C2 = true;
	}



	/////////////////////////////////// Bullet_C3과  Robot 충돌

	if (TCollision::SphereInSphere(Bullet_C3.m_rtCollision, Robot.m_rtCollision))
	{
		Bullet_C3.m_VertexList[0].x = 5.223f; Bullet_C3.m_VertexList[0].y = 5.223f;
		Bullet_C3.m_VertexList[1].x = 5.223f; Bullet_C3.m_VertexList[1].y = 5.223f;
		Bullet_C3.m_VertexList[2].x = 5.223f; Bullet_C3.m_VertexList[2].y = 5.223f;
		Bullet_C3.m_VertexList[3].x = 5.223f; Bullet_C3.m_VertexList[3].y = 5.223f;
		Bullet_C3.m_VertexList[4].x = 5.223f; Bullet_C3.m_VertexList[4].y = 5.223f;
		Bullet_C3.m_VertexList[5].x = 5.223f; Bullet_C3.m_VertexList[5].y = 5.223f;
		Bullet_C3.m_VertexList[6].x = 5.223f; Bullet_C3.m_VertexList[6].y = 5.223f;

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

		Robot_Col_C3 = true;
	}



	/////////////////////////////////// Bullet_C4과  Robot 충돌

	if (TCollision::SphereInSphere(Bullet_C4.m_rtCollision, Robot.m_rtCollision))
	{
		Bullet_C4.m_VertexList[0].x = 4.079f; Bullet_C4.m_VertexList[0].y = 4.079f;
		Bullet_C4.m_VertexList[1].x = 4.079f; Bullet_C4.m_VertexList[1].y = 4.079f;
		Bullet_C4.m_VertexList[2].x = 4.079f; Bullet_C4.m_VertexList[2].y = 4.079f;
		Bullet_C4.m_VertexList[3].x = 4.079f; Bullet_C4.m_VertexList[3].y = 4.079f;
		Bullet_C4.m_VertexList[4].x = 4.079f; Bullet_C4.m_VertexList[4].y = 4.079f;
		Bullet_C4.m_VertexList[5].x = 4.079f; Bullet_C4.m_VertexList[5].y = 4.079f;
		Bullet_C4.m_VertexList[6].x = 4.079f; Bullet_C4.m_VertexList[6].y = 4.079f;

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

		Robot_Col_C4 = true;
	}


}

void TSceneGame::Treasure_Box_open()
{
	if (TCollision::SphereInSphere(m_Boy_NPC.m_rtCollision, Treasure_Box.m_rtCollision))
	{
		Treasure_Box.in_Texture_SetData_factors(0, 0, 100, 75, 100, 75);
		Treasure_Box.m_for_update_Rects.x = g_rtClient.right / 11;    Treasure_Box.m_for_update_Rects.y = g_rtClient.bottom / 8;
		Treasure_Box.Window_SetData_factors(805, 255, Treasure_Box.m_for_update_Rects.x, Treasure_Box.m_for_update_Rects.y);
		Treasure_Box.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Treasure_Open_100_85.png");


		m_Boy_NPC.dead_flag = false;
		m_Boy_NPC.walk_flag = false;
		m_Boy_NPC.walk_step = false;
		m_Boy_NPC.hurt_flag = false;
	



	  memcpy(N_VertexList_BA, Box_Alive.m_VertexList, sizeof(SimpleVertex) * 6);

	 for (int iV = 0; iV < 6; iV++)
   	{
		D3DVECTOR vertex;
		vertex.x = Box_Alive.m_VertexList[iV].x; vertex.y = Box_Alive.m_VertexList[iV].y;
		vertex.x -= Box_Alive.m_vCenter.x;		 vertex.y -= Box_Alive.m_vCenter.y;
		float S = sinf(fAngle);	float C = cosf(fAngle);
		N_VertexList_BA[iV].x = vertex.x * C + vertex.y * S; N_VertexList_BA[iV].y = vertex.x * -S + vertex.y * C;
		N_VertexList_BA[iV].x += Box_Alive.m_vCenter.x;		 N_VertexList_BA[iV].y += Box_Alive.m_vCenter.y;
	}
	   g_pContext->UpdateSubresource(Box_Alive.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_BA, 0, 0);



		Trasure_Box_FINAL_SWITCH = true;
	}

}




void TSceneGame::Boy_NPC_collision_final_decision_including_second_message()
{


	////////////////////////////////////// 시작 단계


	if (m_Boy_NPC.Finish_start == true)
	{
		m_Boy_NPC.Finish_start = false;
		m_Boy_NPC.m_for_update_Rects.x = g_rtClient.right / 9;    m_Boy_NPC.m_for_update_Rects.y = g_rtClient.bottom / 5;
		m_Boy_NPC.in_Texture_SetData_factors(91, 2, 57, 92, 753, 532);
		//m_Boy_NPC.Window_SetData_factors(0, 310, m_Boy_NPC.m_for_update_Rects.x, m_Boy_NPC.m_for_update_Rects.y); // 텍스쳐 시작점 왼위점 좌표 + 텍스쳐 가로-세로 크기.
		m_Boy_NPC.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/AD_Boy.png");
		m_Boy_NPC.walk_step = 1;
	}


	if (m_Boy_NPC.walk_step == 1)
	{
		m_Boy_NPC.walk_flag = true;
	}


	//////////////////////////////////////// hero가 npc를 공격 충돌 & 충돌 되고 일어나는 일

	if(NPC_live_or_dead<2)
	{
	NPC_live_or_dead = NPC_Col_F3 + NPC_Col_C3 + NPC_Col_F4 + NPC_Col_C4 + NPC_Col_S1 + NPC_Col_S2;
	}

	if (NPC_live_or_dead == 1 && m_Boy_NPC.Enter_flag_2==false)
	{
		m_Boy_NPC.Finish_start = false;
		m_Boy_NPC.walk_step = 0;
		m_Boy_NPC.walk_flag = false;
		m_Boy_NPC.hurt_flag = true;

	}


	if (m_Boy_NPC.hurt_flag == true&& m_Boy_NPC.Enter_flag_2 == false)
	{
		m_Boy_NPC.hurt();
		Message.in_Texture_SetData_factors(0, 0, 1241, 735, 1241, 735);
		Message.m_for_update_Rects.x = g_rtClient.right / 2;    Message.m_for_update_Rects.y = g_rtClient.bottom / 2;
		Message.Window_SetData_factors(200, 50, Message.m_for_update_Rects.x, Message.m_for_update_Rects.y);
		Message.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Board_UI_2.png");
	}


	//////////////ENTER KEY 누르면, 원래대로 서고, 해야 한다.

	if (I_Input.Key(VK_RETURN))
	{
		m_Boy_NPC.Enter_flag_2 = true;
		m_Boy_NPC.hurt_flag = false;
	
			m_Boy_NPC.walk_step = 1;
			m_Boy_NPC.walk_flag = true;


		Message.in_Texture_SetData_factors(0, 0, 1241, 735, 1241, 735);
		Message.m_for_update_Rects.x = g_rtClient.right / 100;    Message.m_for_update_Rects.y = g_rtClient.bottom / 100;
		Message.Window_SetData_factors(900, 50, Message.m_for_update_Rects.x, Message.m_for_update_Rects.y);
		Message.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Board_UI.png");
	}


	/////////////////////////////////////////////////////////////////////////   기본 걷는 동작

	if (m_Boy_NPC.walk_flag == true)
	{
		m_Boy_NPC.walk();
		if (m_Boy_NPC.walk_step == 1) { m_Boy_NPC.MoveX(g_fSecPerFrame*0.05f); }
		if (m_Boy_NPC.walk_step == 2) { m_Boy_NPC.MoveX(g_fSecPerFrame*0.05f); }        if (m_Boy_NPC.walk_step == 3) { m_Boy_NPC.MoveX(g_fSecPerFrame*0.05f); }
		if (m_Boy_NPC.walk_step == 4) { m_Boy_NPC.MoveX(g_fSecPerFrame*0.05f); }        if (m_Boy_NPC.walk_step == 5) { m_Boy_NPC.MoveX(g_fSecPerFrame*0.05f); }
		if (m_Boy_NPC.walk_step == 6) { m_Boy_NPC.MoveX(g_fSecPerFrame*0.05f); }        if (m_Boy_NPC.walk_step == 7) { m_Boy_NPC.MoveX(g_fSecPerFrame*0.05f); }
		if (m_Boy_NPC.walk_step == 8) { m_Boy_NPC.MoveX(g_fSecPerFrame*0.05f); }        if (m_Boy_NPC.walk_step == 9) { m_Boy_NPC.MoveX(g_fSecPerFrame*0.05f); }
		if (m_Boy_NPC.walk_step == 10) { m_Boy_NPC.MoveX(g_fSecPerFrame*0.05f); }
	}

	////////////////////////////////////////////////////////////////////  NPC Frame 반영


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


	////////////////////////////////////////////////////////////////////////////////////////////



	if (NPC_live_or_dead == 2)
	{
		++NPC_live_or_dead;

			m_Boy_NPC.dead_flag = true;
			m_Boy_NPC.walk_flag = false;
			m_Boy_NPC.hurt_flag = false;		
	}
	
	if (m_Boy_NPC.dead_flag == true)
	{
		m_Boy_NPC.dead_flag = false;
		m_Boy_NPC.dead_step = 1;
	}
	

	if (NPC_live_or_dead == 3)
	{
		static float fAddTime = 0.0f;
		fAddTime += g_fSecPerFrame;

		if (fAddTime > 10.0f)
		{
			m_bNextSceneStart = true;
			end_decision = 2;
		}
	}
	
	m_Boy_NPC.dead();

	memcpy(N_VertexList_BA, Box_Alive.m_VertexList, sizeof(SimpleVertex) * 6);

	for (int iV = 0; iV < 6; iV++)
	{
		D3DVECTOR vertex;
		vertex.x = Box_Alive.m_VertexList[iV].x; vertex.y = Box_Alive.m_VertexList[iV].y;
		vertex.x -= Box_Alive.m_vCenter.x;		 vertex.y -= Box_Alive.m_vCenter.y;
		float S = sinf(fAngle);	float C = cosf(fAngle);
		N_VertexList_BA[iV].x = vertex.x * C + vertex.y * S; N_VertexList_BA[iV].y = vertex.x * -S + vertex.y * C;
		N_VertexList_BA[iV].x += Box_Alive.m_vCenter.x;		 N_VertexList_BA[iV].y += Box_Alive.m_vCenter.y;
	}
	g_pContext->UpdateSubresource(Box_Alive.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_BA, 0, 0);

}



void TSceneGame::Box_Alive_collision_final_decision()
{


	box_alive_live_or_dead = box_alive_Col_F1 + box_alive_Col_C1 + box_alive_Col_F2 + box_alive_Col_C2 + box_alive_Col_F3 + box_alive_Col_C3 + box_alive_Col_F4 + box_alive_Col_C4
		+ box_alive_Col_S1 + box_alive_Col_S2;


	if (box_alive_live_or_dead == 1)

	{

		Box_Alive_life_bar.in_Texture_SetData_factors(0, 0, 299, 76, 299, 76);
		Box_Alive_life_bar.m_for_update_Rects.x = g_rtClient.right / 3.5;    Box_Alive_life_bar.m_for_update_Rects.y = g_rtClient.bottom / 10;
		Box_Alive_life_bar.Window_SetData_factors(400, 10, Box_Alive_life_bar.m_for_update_Rects.x, Box_Alive_life_bar.m_for_update_Rects.y);
		Box_Alive_life_bar.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/3_4_Bar_A.png");

	}


	if (box_alive_live_or_dead == 2)

	{
		Box_Alive_life_bar.in_Texture_SetData_factors(0, 0, 299, 76, 299, 76);
		Box_Alive_life_bar.m_for_update_Rects.x = g_rtClient.right / 3.5;    Box_Alive_life_bar.m_for_update_Rects.y = g_rtClient.bottom / 10;
		Box_Alive_life_bar.Window_SetData_factors(400, 10, Box_Alive_life_bar.m_for_update_Rects.x, Box_Alive_life_bar.m_for_update_Rects.y);
		Box_Alive_life_bar.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/2_4_Bar_A.png");

	}

	if (box_alive_live_or_dead == 3)

	{
		Box_Alive_life_bar.in_Texture_SetData_factors(0, 0, 299, 76, 299, 76);
		Box_Alive_life_bar.m_for_update_Rects.x = g_rtClient.right / 3.5;    Box_Alive_life_bar.m_for_update_Rects.y = g_rtClient.bottom / 10;
		Box_Alive_life_bar.Window_SetData_factors(400, 10, Box_Alive_life_bar.m_for_update_Rects.x, Box_Alive_life_bar.m_for_update_Rects.y);
		Box_Alive_life_bar.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/1_4_Bar_A.png");

	}




	if (box_alive_live_or_dead == 4)
	{
		Box_Alive.m_VertexList[0].x = 3.2125f; Box_Alive.m_VertexList[0].y = 3.2125f;
		Box_Alive.m_VertexList[1].x = 3.2125f; Box_Alive.m_VertexList[1].y = 3.2125f;
		Box_Alive.m_VertexList[2].x = 3.2125f; Box_Alive.m_VertexList[2].y = 3.2125f;
		Box_Alive.m_VertexList[3].x = 3.2125f; Box_Alive.m_VertexList[3].y = 3.2125f;
		Box_Alive.m_VertexList[4].x = 3.2125f; Box_Alive.m_VertexList[4].y = 3.2125f;
		Box_Alive.m_VertexList[5].x = 3.2125f; Box_Alive.m_VertexList[5].y = 3.2125f;
		Box_Alive.m_VertexList[6].x = 3.2125f; Box_Alive.m_VertexList[6].y = 3.2125f;

		memcpy(N_VertexList_BA, Box_Alive.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Box_Alive.m_VertexList[iV].x; vertex.y = Box_Alive.m_VertexList[iV].y;
			vertex.x -= Box_Alive.m_vCenter.x;		 vertex.y -= Box_Alive.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_BA[iV].x = vertex.x * C + vertex.y * S; N_VertexList_BA[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_BA[iV].x += Box_Alive.m_vCenter.x;		 N_VertexList_BA[iV].y += Box_Alive.m_vCenter.y;
		}
		g_pContext->UpdateSubresource(Box_Alive.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_BA, 0, 0);




		Box_Alive_life_bar.m_VertexList[0].x = 3.446f; Box_Alive_life_bar.m_VertexList[0].y = 3.446f;
		Box_Alive_life_bar.m_VertexList[1].x = 3.446f; Box_Alive_life_bar.m_VertexList[1].y = 3.446f;
		Box_Alive_life_bar.m_VertexList[2].x = 3.446f; Box_Alive_life_bar.m_VertexList[2].y = 3.446f;
		Box_Alive_life_bar.m_VertexList[3].x = 3.446f; Box_Alive_life_bar.m_VertexList[3].y = 3.446f;
		Box_Alive_life_bar.m_VertexList[4].x = 3.446f; Box_Alive_life_bar.m_VertexList[4].y = 3.446f;
		Box_Alive_life_bar.m_VertexList[5].x = 3.446f; Box_Alive_life_bar.m_VertexList[5].y = 3.446f;
		Box_Alive_life_bar.m_VertexList[6].x = 3.446f; Box_Alive_life_bar.m_VertexList[6].y = 3.446f;

		memcpy(N_VertexList_BA_LB, Box_Alive_life_bar.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Box_Alive_life_bar.m_VertexList[iV].x; vertex.y = Box_Alive_life_bar.m_VertexList[iV].y;
			vertex.x -= Box_Alive_life_bar.m_vCenter.x;		 vertex.y -= Box_Alive_life_bar.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_BA_LB[iV].x = vertex.x * C + vertex.y * S; N_VertexList_BA_LB[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_BA_LB[iV].x += Box_Alive_life_bar.m_vCenter.x;		 N_VertexList_BA_LB[iV].y += Box_Alive_life_bar.m_vCenter.y;
		}
		g_pContext->UpdateSubresource(Box_Alive_life_bar.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_BA_LB, 0, 0);

	
		BOX_ALIVE_FINAL_SWITCH = true;

	}


}



void TSceneGame::Bullet_Box_Alive_collision()
{
	//////////////// Bullet_F1과  Box_Alive 충돌
	if (TCollision::SphereInSphere(Bullet_F1.m_rtCollision, Box_Alive.m_rtCollision))
	{	
		Bullet_F1.m_VertexList[0].x = 2.265f; Bullet_F1.m_VertexList[0].y = 2.265f;
		Bullet_F1.m_VertexList[1].x = 2.265f; Bullet_F1.m_VertexList[1].y = 2.265f;
		Bullet_F1.m_VertexList[2].x = 2.265f; Bullet_F1.m_VertexList[2].y = 2.265f;
		Bullet_F1.m_VertexList[3].x = 2.265f; Bullet_F1.m_VertexList[3].y = 2.265f;
		Bullet_F1.m_VertexList[4].x = 2.265f; Bullet_F1.m_VertexList[4].y = 2.265f;
		Bullet_F1.m_VertexList[5].x = 2.265f; Bullet_F1.m_VertexList[5].y = 2.265f;
		Bullet_F1.m_VertexList[6].x = 2.265f; Bullet_F1.m_VertexList[6].y = 2.265f;

		memcpy(N_VertexList_F1, Bullet_F1.m_VertexList, sizeof(SimpleVertex) * 6);
	
		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_F1.m_VertexList[iV].x; vertex.y = Bullet_F1.m_VertexList[iV].y;
			vertex.x -= Bullet_F1.m_vCenter.x;		 vertex.y -= Bullet_F1.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_F1[iV].x = vertex.x * C + vertex.y * S; N_VertexList_F1[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_F1[iV].x += Bullet_F1.m_vCenter.x;		 N_VertexList_F1[iV].y += Bullet_F1.m_vCenter.y;
		}
		g_pContext->UpdateSubresource(Bullet_F1.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_F1, 0, 0);
		
		box_alive_Col_F1 = true; 
	}


	//////////////// Bullet_F2과  Box_Alive 충돌

	if (TCollision::SphereInSphere(Bullet_F2.m_rtCollision, Box_Alive.m_rtCollision))
	{
		Bullet_F2.m_VertexList[0].x = 2.463f; Bullet_F2.m_VertexList[0].y = 2.463f;
		Bullet_F2.m_VertexList[1].x = 2.463f; Bullet_F2.m_VertexList[1].y = 2.463f;
		Bullet_F2.m_VertexList[2].x = 2.463f; Bullet_F2.m_VertexList[2].y = 2.463f;
		Bullet_F2.m_VertexList[3].x = 2.463f; Bullet_F2.m_VertexList[3].y = 2.463f;
		Bullet_F2.m_VertexList[4].x = 2.463f; Bullet_F2.m_VertexList[4].y = 2.463f;
		Bullet_F2.m_VertexList[5].x = 2.463f; Bullet_F2.m_VertexList[5].y = 2.463f;
		Bullet_F2.m_VertexList[6].x = 2.463f; Bullet_F2.m_VertexList[6].y = 2.463f;

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
	
		box_alive_Col_F2 = true;
	}

	/////////////////////////////////// Bullet_F3과  Box_Alive 충돌

	if (TCollision::SphereInSphere(Bullet_F3.m_rtCollision, Box_Alive.m_rtCollision))
	{
		Bullet_F3.m_VertexList[0].x = 4.266f; Bullet_F3.m_VertexList[0].y = 4.266f;
		Bullet_F3.m_VertexList[1].x = 4.266f; Bullet_F3.m_VertexList[1].y = 4.266f;
		Bullet_F3.m_VertexList[2].x = 4.266f; Bullet_F3.m_VertexList[2].y = 4.266f;
		Bullet_F3.m_VertexList[3].x = 4.266f; Bullet_F3.m_VertexList[3].y = 4.266f;
		Bullet_F3.m_VertexList[4].x = 4.266f; Bullet_F3.m_VertexList[4].y = 4.266f;
		Bullet_F3.m_VertexList[5].x = 4.266f; Bullet_F3.m_VertexList[5].y = 4.266f;
		Bullet_F3.m_VertexList[6].x = 4.266f; Bullet_F3.m_VertexList[6].y = 4.266f;

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
	
		box_alive_Col_F3 = true;
	}


	/////////////////////////////////// Bullet_F4과  Box_Alive 충돌

	if (TCollision::SphereInSphere(Bullet_F4.m_rtCollision, Box_Alive.m_rtCollision))
	{
		Bullet_F4.m_VertexList[0].x = 3.771f; Bullet_F4.m_VertexList[0].y = 3.771f;
		Bullet_F4.m_VertexList[1].x = 3.771f; Bullet_F4.m_VertexList[1].y = 3.771f;
		Bullet_F4.m_VertexList[2].x = 3.771f; Bullet_F4.m_VertexList[2].y = 3.771f;
		Bullet_F4.m_VertexList[3].x = 3.771f; Bullet_F4.m_VertexList[3].y = 3.771f;
		Bullet_F4.m_VertexList[4].x = 3.771f; Bullet_F4.m_VertexList[4].y = 3.771f;
		Bullet_F4.m_VertexList[5].x = 3.771f; Bullet_F4.m_VertexList[5].y = 3.771f;
		Bullet_F4.m_VertexList[6].x = 3.771f; Bullet_F4.m_VertexList[6].y = 3.771f;

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

		box_alive_Col_F4 = true;
	}
	




	//////////////// Bullet_C1과  Box_Alive 충돌

	if (TCollision::SphereInSphere(Bullet_C1.m_rtCollision, Box_Alive.m_rtCollision))
	{

		Bullet_C1.m_VertexList[0].x = 3.276f; Bullet_C1.m_VertexList[0].y = 3.276f;
		Bullet_C1.m_VertexList[1].x = 3.276f; Bullet_C1.m_VertexList[1].y = 3.276f;
		Bullet_C1.m_VertexList[2].x = 3.276f; Bullet_C1.m_VertexList[2].y = 3.276f;
		Bullet_C1.m_VertexList[3].x = 3.276f; Bullet_C1.m_VertexList[3].y = 3.276f;
		Bullet_C1.m_VertexList[4].x = 3.276f; Bullet_C1.m_VertexList[4].y = 3.276f;
		Bullet_C1.m_VertexList[5].x = 3.276f; Bullet_C1.m_VertexList[5].y = 3.276f;
		Bullet_C1.m_VertexList[6].x = 3.276f; Bullet_C1.m_VertexList[6].y = 3.276f;

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
	
		box_alive_Col_C1 = true;
	}




	//////////////// Bullet_C2과  Box_Alive 충돌

	if (TCollision::SphereInSphere(Bullet_C2.m_rtCollision, Box_Alive.m_rtCollision))
	{
		Bullet_C2.m_VertexList[0].x = 3.834f; Bullet_C2.m_VertexList[0].y = 3.834f;
		Bullet_C2.m_VertexList[1].x = 3.834f; Bullet_C2.m_VertexList[1].y = 3.834f;
		Bullet_C2.m_VertexList[2].x = 3.834f; Bullet_C2.m_VertexList[2].y = 3.834f;
		Bullet_C2.m_VertexList[3].x = 3.834f; Bullet_C2.m_VertexList[3].y = 3.834f;
		Bullet_C2.m_VertexList[4].x = 3.834f; Bullet_C2.m_VertexList[4].y = 3.834f;
		Bullet_C2.m_VertexList[5].x = 3.834f; Bullet_C2.m_VertexList[5].y = 3.834f;
		Bullet_C2.m_VertexList[6].x = 3.834f; Bullet_C2.m_VertexList[6].y = 3.834f;

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
	
		box_alive_Col_C2 = true;
	}				   



	/////////////////////////////////// Bullet_C3과  Box_Alive 충돌

	if (TCollision::SphereInSphere(Bullet_C3.m_rtCollision, Box_Alive.m_rtCollision))
	{
		Bullet_C3.m_VertexList[0].x = 2.636f; Bullet_C3.m_VertexList[0].y = 2.636f;
		Bullet_C3.m_VertexList[1].x = 2.636f; Bullet_C3.m_VertexList[1].y = 2.636f;
		Bullet_C3.m_VertexList[2].x = 2.636f; Bullet_C3.m_VertexList[2].y = 2.636f;
		Bullet_C3.m_VertexList[3].x = 2.636f; Bullet_C3.m_VertexList[3].y = 2.636f;
		Bullet_C3.m_VertexList[4].x = 2.636f; Bullet_C3.m_VertexList[4].y = 2.636f;
		Bullet_C3.m_VertexList[5].x = 2.636f; Bullet_C3.m_VertexList[5].y = 2.636f;
		Bullet_C3.m_VertexList[6].x = 2.636f; Bullet_C3.m_VertexList[6].y = 2.636f;

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
	
		box_alive_Col_C3 = true;
	}				   




	/////////////////////////////////// Bullet_C4과  Box_Alive 충돌

	if (TCollision::SphereInSphere(Bullet_C4.m_rtCollision, Box_Alive.m_rtCollision))
	{
		Bullet_C4.m_VertexList[0].x = 4.7816f; Bullet_C4.m_VertexList[0].y = 4.7816f;
		Bullet_C4.m_VertexList[1].x = 4.7816f; Bullet_C4.m_VertexList[1].y = 4.7816f;
		Bullet_C4.m_VertexList[2].x = 4.7816f; Bullet_C4.m_VertexList[2].y = 4.7816f;
		Bullet_C4.m_VertexList[3].x = 4.7816f; Bullet_C4.m_VertexList[3].y = 4.7816f;
		Bullet_C4.m_VertexList[4].x = 4.7816f; Bullet_C4.m_VertexList[4].y = 4.7816f;
		Bullet_C4.m_VertexList[5].x = 4.7816f; Bullet_C4.m_VertexList[5].y = 4.7816f;
		Bullet_C4.m_VertexList[6].x = 4.7816f; Bullet_C4.m_VertexList[6].y = 4.7816f;

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
	
		box_alive_Col_C4 = true;
	}				   





}


void TSceneGame::Hero_Ghost_collision()
{


	 
	if (TCollision::SphereInSphere(m_Actor.m_rtCollision, Bullet_Ghost_1.m_rtCollision))
	{	Hero_Col_G1 = true;	}

	if (TCollision::SphereInSphere(m_Actor.m_rtCollision, Bullet_Ghost_2.m_rtCollision))
	{	Hero_Col_G2 = true;	}

	if (TCollision::SphereInSphere(m_Actor.m_rtCollision, Bullet_Ghost_3.m_rtCollision))
	{	Hero_Col_G3 = true;	}

	if (TCollision::SphereInSphere(m_Actor.m_rtCollision, Bullet_Ghost_4.m_rtCollision))
	{	Hero_Col_G4 = true;}
	

	
}



void TSceneGame::Hero_collision_final_decision()
{

	Hero_live_or_dead = Hero_Col_G1 + Hero_Col_G2 + Hero_Col_G3 + Hero_Col_G4 + Hero_Col_B1 + Hero_Col_B2 + Hero_Col_B3 + Hero_Col_B4 +	Hero_Col_S1 + Hero_Col_S2 + Hero_Col_S3 + Hero_Col_S4;





	if (Hero_live_or_dead == 1)
	{
		m_Actor_life_bar.in_Texture_SetData_factors(0, 0, 299, 76, 299, 76);
		m_Actor_life_bar.m_for_update_Rects.x = g_rtClient.right / 3.5;    m_Actor_life_bar.m_for_update_Rects.y = g_rtClient.bottom / 10;
		m_Actor_life_bar.Window_SetData_factors(200, 10, m_Actor_life_bar.m_for_update_Rects.x, m_Actor_life_bar.m_for_update_Rects.y);
		m_Actor_life_bar.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/3_4_Bar.png");
	}



	/////////////////////////////////////////////////////////

	if (Hero_live_or_dead == 2)
	{
		m_Actor_life_bar.in_Texture_SetData_factors(0, 0, 299, 76, 299, 76);
		m_Actor_life_bar.m_for_update_Rects.x = g_rtClient.right / 3.5;    m_Actor_life_bar.m_for_update_Rects.y = g_rtClient.bottom / 10;
		m_Actor_life_bar.Window_SetData_factors(200, 10, m_Actor_life_bar.m_for_update_Rects.x, m_Actor_life_bar.m_for_update_Rects.y);
		m_Actor_life_bar.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/2_4_Bar.png");
	}

	///////////////////////////////////////////////////////

	if (Hero_live_or_dead == 3)
	{
		m_Actor_life_bar.in_Texture_SetData_factors(0, 0, 299, 76, 299, 76);
		m_Actor_life_bar.m_for_update_Rects.x = g_rtClient.right / 3.5;    m_Actor_life_bar.m_for_update_Rects.y = g_rtClient.bottom / 10;
		m_Actor_life_bar.Window_SetData_factors(200, 10, m_Actor_life_bar.m_for_update_Rects.x, m_Actor_life_bar.m_for_update_Rects.y);
		m_Actor_life_bar.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/1_4_Bar.png");
	}


	/////////////////////////////////////////////////

	if (Hero_live_or_dead == 4)
	{
		m_Actor_life_bar.in_Texture_SetData_factors(0, 0, 299, 76, 299, 76);
		m_Actor_life_bar.m_for_update_Rects.x = g_rtClient.right / 3.5;    m_Actor_life_bar.m_for_update_Rects.y = g_rtClient.bottom / 10;
		m_Actor_life_bar.Window_SetData_factors(200, 10, m_Actor_life_bar.m_for_update_Rects.x, m_Actor_life_bar.m_for_update_Rects.y);
		m_Actor_life_bar.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/0_Bar.png");
		m_bNextSceneStart = true;

		end_decision = 2;
		
	}
	///////////////////////////////////////////////////

	memcpy(N_VertexList_HLB, m_Actor_life_bar.m_VertexList, sizeof(SimpleVertex) * 6);

	for (int iV = 0; iV < 6; iV++)
	{
		D3DVECTOR vertex;
		vertex.x = m_Actor_life_bar.m_VertexList[iV].x; vertex.y = m_Actor_life_bar.m_VertexList[iV].y;
		vertex.x -= m_Actor_life_bar.m_vCenter.x;		 vertex.y -= m_Actor_life_bar.m_vCenter.y;
		float S = sinf(fAngle);	float C = cosf(fAngle);
		N_VertexList_HLB[iV].x = vertex.x * C + vertex.y * S; N_VertexList_HLB[iV].y = vertex.x * -S + vertex.y * C;
		N_VertexList_HLB[iV].x += m_Actor_life_bar.m_vCenter.x;		 N_VertexList_HLB[iV].y += m_Actor_life_bar.m_vCenter.y;
	}
	g_pContext->UpdateSubresource(m_Actor_life_bar.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_HLB, 0, 0);
}


void TSceneGame::Herosword_ghost_collsion()
{
	if (I_Input.Key('O')  && TCollision::SphereInSphere(m_Actor.m_rtCollision, Bullet_Ghost_1.m_rtCollision))
	{
		Bullet_Ghost_1.m_VertexList[0].x = 2.333f; Bullet_Ghost_1.m_VertexList[0].y = 2.333f;
		Bullet_Ghost_1.m_VertexList[1].x = 2.333f; Bullet_Ghost_1.m_VertexList[1].y = 2.333f;
		Bullet_Ghost_1.m_VertexList[2].x = 2.333f; Bullet_Ghost_1.m_VertexList[2].y = 2.333f;
		Bullet_Ghost_1.m_VertexList[3].x = 2.333f; Bullet_Ghost_1.m_VertexList[3].y = 2.333f;
		Bullet_Ghost_1.m_VertexList[4].x = 2.333f; Bullet_Ghost_1.m_VertexList[4].y = 2.333f;
		Bullet_Ghost_1.m_VertexList[5].x = 2.333f; Bullet_Ghost_1.m_VertexList[5].y = 2.333f;
		Bullet_Ghost_1.m_VertexList[6].x = 2.333f; Bullet_Ghost_1.m_VertexList[6].y = 2.333f;
	
		memcpy(N_VertexList_G1, Bullet_Ghost_1.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_1.m_VertexList[iV].x; vertex.y = Bullet_Ghost_1.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_1.m_vCenter.x;		 vertex.y -= Bullet_Ghost_1.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G1[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G1[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G1[iV].x += Bullet_Ghost_1.m_vCenter.x; N_VertexList_G1[iV].y += Bullet_Ghost_1.m_vCenter.y;
		}

		g_pContext->UpdateSubresource(Bullet_Ghost_1.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G1, 0, 0);
	}

	/////////////////////////////////////////////////////

	if (I_Input.Key('O')&& TCollision::SphereInSphere(m_Actor.m_rtCollision, Bullet_Ghost_2.m_rtCollision))
	{
		Bullet_Ghost_2.m_VertexList[0].x = 2.244f; Bullet_Ghost_2.m_VertexList[0].y = 2.244f;
		Bullet_Ghost_2.m_VertexList[1].x = 2.244f; Bullet_Ghost_2.m_VertexList[1].y = 2.244f;
		Bullet_Ghost_2.m_VertexList[2].x = 2.244f; Bullet_Ghost_2.m_VertexList[2].y = 2.244f;
		Bullet_Ghost_2.m_VertexList[3].x = 2.244f; Bullet_Ghost_2.m_VertexList[3].y = 2.244f;
		Bullet_Ghost_2.m_VertexList[4].x = 2.244f; Bullet_Ghost_2.m_VertexList[4].y = 2.244f;
		Bullet_Ghost_2.m_VertexList[5].x = 2.244f; Bullet_Ghost_2.m_VertexList[5].y = 2.244f;
		Bullet_Ghost_2.m_VertexList[6].x = 2.244f; Bullet_Ghost_2.m_VertexList[6].y = 2.244f;

		memcpy(N_VertexList_G2, Bullet_Ghost_2.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_2.m_VertexList[iV].x; vertex.y = Bullet_Ghost_2.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_2.m_vCenter.x;		 vertex.y -= Bullet_Ghost_2.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G2[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G2[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G2[iV].x += Bullet_Ghost_2.m_vCenter.x; N_VertexList_G2[iV].y += Bullet_Ghost_2.m_vCenter.y;
		}

		g_pContext->UpdateSubresource(Bullet_Ghost_2.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G2, 0, 0);
	}

	///////////////////////////////////////////////////////////

	if (I_Input.Key('O') && TCollision::SphereInSphere(m_Actor.m_rtCollision, Bullet_Ghost_3.m_rtCollision))
	{
		Bullet_Ghost_3.m_VertexList[0].x = 2.377f; Bullet_Ghost_3.m_VertexList[0].y = 2.377f;
		Bullet_Ghost_3.m_VertexList[1].x = 2.377f; Bullet_Ghost_3.m_VertexList[1].y = 2.377f;
		Bullet_Ghost_3.m_VertexList[2].x = 2.377f; Bullet_Ghost_3.m_VertexList[2].y = 2.377f;
		Bullet_Ghost_3.m_VertexList[3].x = 2.377f; Bullet_Ghost_3.m_VertexList[3].y = 2.377f;
		Bullet_Ghost_3.m_VertexList[4].x = 2.377f; Bullet_Ghost_3.m_VertexList[4].y = 2.377f;
		Bullet_Ghost_3.m_VertexList[5].x = 2.377f; Bullet_Ghost_3.m_VertexList[5].y = 2.377f;
		Bullet_Ghost_3.m_VertexList[6].x = 2.377f; Bullet_Ghost_3.m_VertexList[6].y = 2.377f;

		memcpy(N_VertexList_G3, Bullet_Ghost_3.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_3.m_VertexList[iV].x; vertex.y = Bullet_Ghost_3.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_3.m_vCenter.x;		 vertex.y -= Bullet_Ghost_3.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G3[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G3[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G3[iV].x += Bullet_Ghost_3.m_vCenter.x; N_VertexList_G3[iV].y += Bullet_Ghost_3.m_vCenter.y;
		}

		g_pContext->UpdateSubresource(Bullet_Ghost_3.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G3, 0, 0);
	}

	/////////////////////////////////////////////////////////////

	if (I_Input.Key('O') && TCollision::SphereInSphere(m_Actor.m_rtCollision, Bullet_Ghost_4.m_rtCollision))
	{
		Bullet_Ghost_4.m_VertexList[0].x = 2.996f; Bullet_Ghost_4.m_VertexList[0].y = 2.996f;
		Bullet_Ghost_4.m_VertexList[1].x = 2.996f; Bullet_Ghost_4.m_VertexList[1].y = 2.996f;
		Bullet_Ghost_4.m_VertexList[2].x = 2.996f; Bullet_Ghost_4.m_VertexList[2].y = 2.996f;
		Bullet_Ghost_4.m_VertexList[3].x = 2.996f; Bullet_Ghost_4.m_VertexList[3].y = 2.996f;
		Bullet_Ghost_4.m_VertexList[4].x = 2.996f; Bullet_Ghost_4.m_VertexList[4].y = 2.996f;
		Bullet_Ghost_4.m_VertexList[5].x = 2.996f; Bullet_Ghost_4.m_VertexList[5].y = 2.996f;
		Bullet_Ghost_4.m_VertexList[6].x = 2.996f; Bullet_Ghost_4.m_VertexList[6].y = 2.996f;

		memcpy(N_VertexList_G4, Bullet_Ghost_4.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_4.m_VertexList[iV].x; vertex.y = Bullet_Ghost_4.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_4.m_vCenter.x;		 vertex.y -= Bullet_Ghost_4.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G4[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G4[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G4[iV].x += Bullet_Ghost_4.m_vCenter.x; N_VertexList_G4[iV].y += Bullet_Ghost_4.m_vCenter.y;
		}

		g_pContext->UpdateSubresource(Bullet_Ghost_4.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G4, 0, 0);
	}
	/////////////////////////////////////////////////////////////////////
}






void TSceneGame::Bullet_Ghost_collision()
{

	if (TCollision::SphereInSphere(Bullet_F1.m_rtCollision, Bullet_Ghost_1.m_rtCollision))
	{
		Bullet_F1.m_VertexList[0].x = 5.441f; Bullet_F1.m_VertexList[0].y = 5.441f;
		Bullet_F1.m_VertexList[1].x = 5.441f; Bullet_F1.m_VertexList[1].y = 5.441f;
		Bullet_F1.m_VertexList[2].x = 5.441f; Bullet_F1.m_VertexList[2].y = 5.441f;
		Bullet_F1.m_VertexList[3].x = 5.441f; Bullet_F1.m_VertexList[3].y = 5.441f;
		Bullet_F1.m_VertexList[4].x = 5.441f; Bullet_F1.m_VertexList[4].y = 5.441f;
		Bullet_F1.m_VertexList[5].x = 5.441f; Bullet_F1.m_VertexList[5].y = 5.441f;
		Bullet_F1.m_VertexList[6].x = 5.441f; Bullet_F1.m_VertexList[6].y = 5.441f;

		Bullet_Ghost_1.m_VertexList[0].x = 5.002f; Bullet_Ghost_1.m_VertexList[0].y = 5.002f;
		Bullet_Ghost_1.m_VertexList[1].x = 5.002f; Bullet_Ghost_1.m_VertexList[1].y = 5.002f;
		Bullet_Ghost_1.m_VertexList[2].x = 5.002f; Bullet_Ghost_1.m_VertexList[2].y = 5.002f;
		Bullet_Ghost_1.m_VertexList[3].x = 5.002f; Bullet_Ghost_1.m_VertexList[3].y = 5.002f;
		Bullet_Ghost_1.m_VertexList[4].x = 5.002f; Bullet_Ghost_1.m_VertexList[4].y = 5.002f;
		Bullet_Ghost_1.m_VertexList[5].x = 5.002f; Bullet_Ghost_1.m_VertexList[5].y = 5.002f;
		Bullet_Ghost_1.m_VertexList[6].x = 5.002f; Bullet_Ghost_1.m_VertexList[6].y = 5.002f;


		memcpy(N_VertexList_F1, Bullet_F1.m_VertexList, sizeof(SimpleVertex) * 6);
		memcpy(N_VertexList_G1, Bullet_Ghost_1.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_F1.m_VertexList[iV].x; vertex.y = Bullet_F1.m_VertexList[iV].y;
			vertex.x -= Bullet_F1.m_vCenter.x;		 vertex.y -= Bullet_F1.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_F1[iV].x = vertex.x * C + vertex.y * S; N_VertexList_F1[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_F1[iV].x += Bullet_F1.m_vCenter.x;		 N_VertexList_F1[iV].y += Bullet_F1.m_vCenter.y;
		}

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_1.m_VertexList[iV].x; vertex.y = Bullet_Ghost_1.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_1.m_vCenter.x;		 vertex.y -= Bullet_Ghost_1.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G1[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G1[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G1[iV].x += Bullet_Ghost_1.m_vCenter.x; N_VertexList_G1[iV].y += Bullet_Ghost_1.m_vCenter.y;
		}


		g_pContext->UpdateSubresource(Bullet_F1.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_F1, 0, 0);
		g_pContext->UpdateSubresource(Bullet_Ghost_1.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G1, 0, 0);
	}


	if (TCollision::SphereInSphere(Bullet_F1.m_rtCollision, Bullet_Ghost_2.m_rtDetection))
	{
		Bullet_F1.m_VertexList[0].x = 4.889f; Bullet_F1.m_VertexList[0].y = 4.889f;
		Bullet_F1.m_VertexList[1].x = 4.889f; Bullet_F1.m_VertexList[1].y = 4.889f;
		Bullet_F1.m_VertexList[2].x = 4.889f; Bullet_F1.m_VertexList[2].y = 4.889f;
		Bullet_F1.m_VertexList[3].x = 4.889f; Bullet_F1.m_VertexList[3].y = 4.889f;
		Bullet_F1.m_VertexList[4].x = 4.889f; Bullet_F1.m_VertexList[4].y = 4.889f;
		Bullet_F1.m_VertexList[5].x = 4.889f; Bullet_F1.m_VertexList[5].y = 4.889f;
		Bullet_F1.m_VertexList[6].x = 4.889f; Bullet_F1.m_VertexList[6].y = 4.889f;

		Bullet_Ghost_2.m_VertexList[0].x = 3.449f; Bullet_Ghost_2.m_VertexList[0].y = 3.449f;
		Bullet_Ghost_2.m_VertexList[1].x = 3.449f; Bullet_Ghost_2.m_VertexList[1].y = 3.449f;
		Bullet_Ghost_2.m_VertexList[2].x = 3.449f; Bullet_Ghost_2.m_VertexList[2].y = 3.449f;
		Bullet_Ghost_2.m_VertexList[3].x = 3.449f; Bullet_Ghost_2.m_VertexList[3].y = 3.449f;
		Bullet_Ghost_2.m_VertexList[4].x = 3.449f; Bullet_Ghost_2.m_VertexList[4].y = 3.449f;
		Bullet_Ghost_2.m_VertexList[5].x = 3.449f; Bullet_Ghost_2.m_VertexList[5].y = 3.449f;
		Bullet_Ghost_2.m_VertexList[6].x = 3.449f; Bullet_Ghost_2.m_VertexList[6].y = 3.449f;


		memcpy(N_VertexList_F1, Bullet_F1.m_VertexList, sizeof(SimpleVertex) * 6);
		memcpy(N_VertexList_G2, Bullet_Ghost_2.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_F1.m_VertexList[iV].x; vertex.y = Bullet_F1.m_VertexList[iV].y;
			vertex.x -= Bullet_F1.m_vCenter.x;		 vertex.y -= Bullet_F1.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_F1[iV].x = vertex.x * C + vertex.y * S; N_VertexList_F1[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_F1[iV].x += Bullet_F1.m_vCenter.x;		 N_VertexList_F1[iV].y += Bullet_F1.m_vCenter.y;
		}

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_2.m_VertexList[iV].x; vertex.y = Bullet_Ghost_2.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_2.m_vCenter.x;		 vertex.y -= Bullet_Ghost_2.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G2[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G2[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G2[iV].x += Bullet_Ghost_2.m_vCenter.x; N_VertexList_G2[iV].y += Bullet_Ghost_2.m_vCenter.y;
		}


		g_pContext->UpdateSubresource(Bullet_F1.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_F1, 0, 0);
		g_pContext->UpdateSubresource(Bullet_Ghost_2.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G2, 0, 0);
	}

	if (TCollision::SphereInSphere(Bullet_F1.m_rtCollision, Bullet_Ghost_3.m_rtDetection))
	{

		Bullet_F1.m_VertexList[0].x = 3.368f; Bullet_F1.m_VertexList[0].y = 3.368f;
		Bullet_F1.m_VertexList[1].x = 3.368f; Bullet_F1.m_VertexList[1].y = 3.368f;
		Bullet_F1.m_VertexList[2].x = 3.368f; Bullet_F1.m_VertexList[2].y = 3.368f;
		Bullet_F1.m_VertexList[3].x = 3.368f; Bullet_F1.m_VertexList[3].y = 3.368f;
		Bullet_F1.m_VertexList[4].x = 3.368f; Bullet_F1.m_VertexList[4].y = 3.368f;
		Bullet_F1.m_VertexList[5].x = 3.368f; Bullet_F1.m_VertexList[5].y = 3.368f;
		Bullet_F1.m_VertexList[6].x = 3.368f; Bullet_F1.m_VertexList[6].y = 3.368f;

		Bullet_Ghost_3.m_VertexList[0].x = 3.241f; Bullet_Ghost_3.m_VertexList[0].y = 3.241f;
		Bullet_Ghost_3.m_VertexList[1].x = 3.241f; Bullet_Ghost_3.m_VertexList[1].y = 3.241f;
		Bullet_Ghost_3.m_VertexList[2].x = 3.241f; Bullet_Ghost_3.m_VertexList[2].y = 3.241f;
		Bullet_Ghost_3.m_VertexList[3].x = 3.241f; Bullet_Ghost_3.m_VertexList[3].y = 3.241f;
		Bullet_Ghost_3.m_VertexList[4].x = 3.241f; Bullet_Ghost_3.m_VertexList[4].y = 3.241f;
		Bullet_Ghost_3.m_VertexList[5].x = 3.241f; Bullet_Ghost_3.m_VertexList[5].y = 3.241f;
		Bullet_Ghost_3.m_VertexList[6].x = 3.241f; Bullet_Ghost_3.m_VertexList[6].y = 3.241f;


		memcpy(N_VertexList_F1, Bullet_F1.m_VertexList, sizeof(SimpleVertex) * 6);
		memcpy(N_VertexList_G3, Bullet_Ghost_3.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_F1.m_VertexList[iV].x; vertex.y = Bullet_F1.m_VertexList[iV].y;
			vertex.x -= Bullet_F1.m_vCenter.x;		 vertex.y -= Bullet_F1.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_F1[iV].x = vertex.x * C + vertex.y * S; N_VertexList_F1[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_F1[iV].x += Bullet_F1.m_vCenter.x;		 N_VertexList_F1[iV].y += Bullet_F1.m_vCenter.y;
		}

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_3.m_VertexList[iV].x; vertex.y = Bullet_Ghost_3.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_3.m_vCenter.x;		 vertex.y -= Bullet_Ghost_3.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G3[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G3[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G3[iV].x += Bullet_Ghost_3.m_vCenter.x; N_VertexList_G3[iV].y += Bullet_Ghost_3.m_vCenter.y;
		}


		g_pContext->UpdateSubresource(Bullet_F1.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_F1, 0, 0);
		g_pContext->UpdateSubresource(Bullet_Ghost_3.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G3, 0, 0);

	}


	if (TCollision::SphereInSphere(Bullet_F1.m_rtCollision, Bullet_Ghost_4.m_rtDetection))
	{
		Bullet_F1.m_VertexList[0].x = 3.282f; Bullet_F1.m_VertexList[0].y = 3.282f;
		Bullet_F1.m_VertexList[1].x = 3.282f; Bullet_F1.m_VertexList[1].y = 3.282f;
		Bullet_F1.m_VertexList[2].x = 3.282f; Bullet_F1.m_VertexList[2].y = 3.282f;
		Bullet_F1.m_VertexList[3].x = 3.282f; Bullet_F1.m_VertexList[3].y = 3.282f;
		Bullet_F1.m_VertexList[4].x = 3.282f; Bullet_F1.m_VertexList[4].y = 3.282f;
		Bullet_F1.m_VertexList[5].x = 3.282f; Bullet_F1.m_VertexList[5].y = 3.282f;
		Bullet_F1.m_VertexList[6].x = 3.282f; Bullet_F1.m_VertexList[6].y = 3.282f;

		Bullet_Ghost_4.m_VertexList[0].x = 3.299f; Bullet_Ghost_4.m_VertexList[0].y = 3.299f;
		Bullet_Ghost_4.m_VertexList[1].x = 3.299f; Bullet_Ghost_4.m_VertexList[1].y = 3.299f;
		Bullet_Ghost_4.m_VertexList[2].x = 3.299f; Bullet_Ghost_4.m_VertexList[2].y = 3.299f;
		Bullet_Ghost_4.m_VertexList[3].x = 3.299f; Bullet_Ghost_4.m_VertexList[3].y = 3.299f;
		Bullet_Ghost_4.m_VertexList[4].x = 3.299f; Bullet_Ghost_4.m_VertexList[4].y = 3.299f;
		Bullet_Ghost_4.m_VertexList[5].x = 3.299f; Bullet_Ghost_4.m_VertexList[5].y = 3.299f;
		Bullet_Ghost_4.m_VertexList[6].x = 3.299f; Bullet_Ghost_4.m_VertexList[6].y = 3.299f;


		memcpy(N_VertexList_F1, Bullet_F1.m_VertexList, sizeof(SimpleVertex) * 6);
		memcpy(N_VertexList_G4, Bullet_Ghost_4.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_F1.m_VertexList[iV].x; vertex.y = Bullet_F1.m_VertexList[iV].y;
			vertex.x -= Bullet_F1.m_vCenter.x;		 vertex.y -= Bullet_F1.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_F1[iV].x = vertex.x * C + vertex.y * S; N_VertexList_F1[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_F1[iV].x += Bullet_F1.m_vCenter.x;		 N_VertexList_F1[iV].y += Bullet_F1.m_vCenter.y;
		}

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_4.m_VertexList[iV].x; vertex.y = Bullet_Ghost_4.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_4.m_vCenter.x;		 vertex.y -= Bullet_Ghost_4.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G4[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G4[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G4[iV].x += Bullet_Ghost_4.m_vCenter.x; N_VertexList_G4[iV].y += Bullet_Ghost_4.m_vCenter.y;
		}


		g_pContext->UpdateSubresource(Bullet_F1.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_F1, 0, 0);
		g_pContext->UpdateSubresource(Bullet_Ghost_4.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G4, 0, 0);
	}


	if (TCollision::SphereInSphere(Bullet_F2.m_rtCollision, Bullet_Ghost_1.m_rtCollision))
	{
		Bullet_F2.m_VertexList[0].x = 3.333f; Bullet_F2.m_VertexList[0].y = 3.333f;
		Bullet_F2.m_VertexList[1].x = 3.333f; Bullet_F2.m_VertexList[1].y = 3.333f;
		Bullet_F2.m_VertexList[2].x = 3.333f; Bullet_F2.m_VertexList[2].y = 3.333f;
		Bullet_F2.m_VertexList[3].x = 3.333f; Bullet_F2.m_VertexList[3].y = 3.333f;
		Bullet_F2.m_VertexList[4].x = 3.333f; Bullet_F2.m_VertexList[4].y = 3.333f;
		Bullet_F2.m_VertexList[5].x = 3.333f; Bullet_F2.m_VertexList[5].y = 3.333f;
		Bullet_F2.m_VertexList[6].x = 3.333f; Bullet_F2.m_VertexList[6].y = 3.333f;

		Bullet_Ghost_1.m_VertexList[0].x = 3.538f; Bullet_Ghost_1.m_VertexList[0].y = 3.538f;
		Bullet_Ghost_1.m_VertexList[1].x = 3.538f; Bullet_Ghost_1.m_VertexList[1].y = 3.538f;
		Bullet_Ghost_1.m_VertexList[2].x = 3.538f; Bullet_Ghost_1.m_VertexList[2].y = 3.538f;
		Bullet_Ghost_1.m_VertexList[3].x = 3.538f; Bullet_Ghost_1.m_VertexList[3].y = 3.538f;
		Bullet_Ghost_1.m_VertexList[4].x = 3.538f; Bullet_Ghost_1.m_VertexList[4].y = 3.538f;
		Bullet_Ghost_1.m_VertexList[5].x = 3.538f; Bullet_Ghost_1.m_VertexList[5].y = 3.538f;
		Bullet_Ghost_1.m_VertexList[6].x = 3.338f; Bullet_Ghost_1.m_VertexList[6].y = 3.538f;


		memcpy(N_VertexList_F2, Bullet_F2.m_VertexList, sizeof(SimpleVertex) * 6);
		memcpy(N_VertexList_G1, Bullet_Ghost_1.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_F2.m_VertexList[iV].x; vertex.y = Bullet_F2.m_VertexList[iV].y;
			vertex.x -= Bullet_F2.m_vCenter.x;		 vertex.y -= Bullet_F2.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_F2[iV].x = vertex.x * C + vertex.y * S; N_VertexList_F2[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_F2[iV].x += Bullet_F2.m_vCenter.x;		 N_VertexList_F2[iV].y += Bullet_F2.m_vCenter.y;
		}

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_1.m_VertexList[iV].x; vertex.y = Bullet_Ghost_1.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_1.m_vCenter.x;		 vertex.y -= Bullet_Ghost_1.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G1[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G1[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G1[iV].x += Bullet_Ghost_1.m_vCenter.x; N_VertexList_G1[iV].y += Bullet_Ghost_1.m_vCenter.y;
		}


		g_pContext->UpdateSubresource(Bullet_F2.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_F2, 0, 0);
		g_pContext->UpdateSubresource(Bullet_Ghost_1.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G1, 0, 0);
	}


	if (TCollision::SphereInSphere(Bullet_F2.m_rtCollision, Bullet_Ghost_2.m_rtDetection))
	{
		Bullet_F2.m_VertexList[0].x = 3.378f; Bullet_F2.m_VertexList[0].y = 3.378f;
		Bullet_F2.m_VertexList[1].x = 3.378f; Bullet_F2.m_VertexList[1].y = 3.378f;
		Bullet_F2.m_VertexList[2].x = 3.378f; Bullet_F2.m_VertexList[2].y = 3.378f;
		Bullet_F2.m_VertexList[3].x = 3.378f; Bullet_F2.m_VertexList[3].y = 3.378f;
		Bullet_F2.m_VertexList[4].x = 3.378f; Bullet_F2.m_VertexList[4].y = 3.378f;
		Bullet_F2.m_VertexList[5].x = 3.378f; Bullet_F2.m_VertexList[5].y = 3.378f;
		Bullet_F2.m_VertexList[6].x = 3.378f; Bullet_F2.m_VertexList[6].y = 3.378f;

		Bullet_Ghost_2.m_VertexList[0].x = 8.772f; Bullet_Ghost_2.m_VertexList[0].y = 8.772f;
		Bullet_Ghost_2.m_VertexList[1].x = 8.772f; Bullet_Ghost_2.m_VertexList[1].y = 8.772f;
		Bullet_Ghost_2.m_VertexList[2].x = 8.772f; Bullet_Ghost_2.m_VertexList[2].y = 8.772f;
		Bullet_Ghost_2.m_VertexList[3].x = 8.772f; Bullet_Ghost_2.m_VertexList[3].y = 8.772f;
		Bullet_Ghost_2.m_VertexList[4].x = 8.772f; Bullet_Ghost_2.m_VertexList[4].y = 8.772f;
		Bullet_Ghost_2.m_VertexList[5].x = 8.772f; Bullet_Ghost_2.m_VertexList[5].y = 8.772f;
		Bullet_Ghost_2.m_VertexList[6].x = 8.772f; Bullet_Ghost_2.m_VertexList[6].y = 8.772f;


		memcpy(N_VertexList_F2, Bullet_F2.m_VertexList, sizeof(SimpleVertex) * 6);
		memcpy(N_VertexList_G2, Bullet_Ghost_2.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_F2.m_VertexList[iV].x; vertex.y = Bullet_F2.m_VertexList[iV].y;
			vertex.x -= Bullet_F2.m_vCenter.x;		 vertex.y -= Bullet_F2.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_F2[iV].x = vertex.x * C + vertex.y * S; N_VertexList_F2[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_F2[iV].x += Bullet_F2.m_vCenter.x;		 N_VertexList_F2[iV].y += Bullet_F2.m_vCenter.y;
		}

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_2.m_VertexList[iV].x; vertex.y = Bullet_Ghost_2.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_2.m_vCenter.x;		 vertex.y -= Bullet_Ghost_2.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G2[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G2[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G2[iV].x += Bullet_Ghost_2.m_vCenter.x; N_VertexList_G2[iV].y += Bullet_Ghost_2.m_vCenter.y;
		}


		g_pContext->UpdateSubresource(Bullet_F2.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_F2, 0, 0);
		g_pContext->UpdateSubresource(Bullet_Ghost_2.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G2, 0, 0);
	}

	if (TCollision::SphereInSphere(Bullet_F2.m_rtCollision, Bullet_Ghost_3.m_rtDetection))
	{

		Bullet_F2.m_VertexList[0].x = 3.426f; Bullet_F2.m_VertexList[0].y = 3.426f;
		Bullet_F2.m_VertexList[1].x = 3.426f; Bullet_F2.m_VertexList[1].y = 3.426f;
		Bullet_F2.m_VertexList[2].x = 3.426f; Bullet_F2.m_VertexList[2].y = 3.426f;
		Bullet_F2.m_VertexList[3].x = 3.426f; Bullet_F2.m_VertexList[3].y = 3.426f;
		Bullet_F2.m_VertexList[4].x = 3.426f; Bullet_F2.m_VertexList[4].y = 3.426f;
		Bullet_F2.m_VertexList[5].x = 3.426f; Bullet_F2.m_VertexList[5].y = 3.426f;
		Bullet_F2.m_VertexList[6].x = 3.426f; Bullet_F2.m_VertexList[6].y = 3.426f;

		Bullet_Ghost_3.m_VertexList[0].x = 3.434f; Bullet_Ghost_3.m_VertexList[0].y = 3.434f;
		Bullet_Ghost_3.m_VertexList[1].x = 3.434f; Bullet_Ghost_3.m_VertexList[1].y = 3.434f;
		Bullet_Ghost_3.m_VertexList[2].x = 3.434f; Bullet_Ghost_3.m_VertexList[2].y = 3.434f;
		Bullet_Ghost_3.m_VertexList[3].x = 3.434f; Bullet_Ghost_3.m_VertexList[3].y = 3.434f;
		Bullet_Ghost_3.m_VertexList[4].x = 3.434f; Bullet_Ghost_3.m_VertexList[4].y = 3.434f;
		Bullet_Ghost_3.m_VertexList[5].x = 3.434f; Bullet_Ghost_3.m_VertexList[5].y = 3.434f;
		Bullet_Ghost_3.m_VertexList[6].x = 3.434f; Bullet_Ghost_3.m_VertexList[6].y = 3.434f;


		memcpy(N_VertexList_F2, Bullet_F2.m_VertexList, sizeof(SimpleVertex) * 6);
		memcpy(N_VertexList_G3, Bullet_Ghost_3.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_F2.m_VertexList[iV].x; vertex.y = Bullet_F2.m_VertexList[iV].y;
			vertex.x -= Bullet_F2.m_vCenter.x;		 vertex.y -= Bullet_F2.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_F2[iV].x = vertex.x * C + vertex.y * S; N_VertexList_F2[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_F2[iV].x += Bullet_F2.m_vCenter.x;		 N_VertexList_F2[iV].y += Bullet_F2.m_vCenter.y;
		}

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_3.m_VertexList[iV].x; vertex.y = Bullet_Ghost_3.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_3.m_vCenter.x;		 vertex.y -= Bullet_Ghost_3.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G3[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G3[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G3[iV].x += Bullet_Ghost_3.m_vCenter.x; N_VertexList_G3[iV].y += Bullet_Ghost_3.m_vCenter.y;
		}


		g_pContext->UpdateSubresource(Bullet_F2.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_F2, 0, 0);
		g_pContext->UpdateSubresource(Bullet_Ghost_3.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G3, 0, 0);

	}

	if (TCollision::SphereInSphere(Bullet_F2.m_rtCollision, Bullet_Ghost_4.m_rtDetection))
	{
		Bullet_F2.m_VertexList[0].x = 4.2936f; Bullet_F2.m_VertexList[0].y = 4.2936f;
		Bullet_F2.m_VertexList[1].x = 4.2936f; Bullet_F2.m_VertexList[1].y = 4.2936f;
		Bullet_F2.m_VertexList[2].x = 4.2936f; Bullet_F2.m_VertexList[2].y = 4.2936f;
		Bullet_F2.m_VertexList[3].x = 4.2936f; Bullet_F2.m_VertexList[3].y = 4.2936f;
		Bullet_F2.m_VertexList[4].x = 4.2936f; Bullet_F2.m_VertexList[4].y = 4.2936f;
		Bullet_F2.m_VertexList[5].x = 4.2936f; Bullet_F2.m_VertexList[5].y = 4.2936f;
		Bullet_F2.m_VertexList[6].x = 4.2936f; Bullet_F2.m_VertexList[6].y = 4.2936f;

		Bullet_Ghost_4.m_VertexList[0].x = 4.741f; Bullet_Ghost_4.m_VertexList[0].y = 4.741f;
		Bullet_Ghost_4.m_VertexList[1].x = 4.741f; Bullet_Ghost_4.m_VertexList[1].y = 4.741f;
		Bullet_Ghost_4.m_VertexList[2].x = 4.741f; Bullet_Ghost_4.m_VertexList[2].y = 4.741f;
		Bullet_Ghost_4.m_VertexList[3].x = 4.741f; Bullet_Ghost_4.m_VertexList[3].y = 4.741f;
		Bullet_Ghost_4.m_VertexList[4].x = 4.741f; Bullet_Ghost_4.m_VertexList[4].y = 4.741f;
		Bullet_Ghost_4.m_VertexList[5].x = 4.741f; Bullet_Ghost_4.m_VertexList[5].y = 4.741f;
		Bullet_Ghost_4.m_VertexList[6].x = 4.741f; Bullet_Ghost_4.m_VertexList[6].y = 4.741f;


		memcpy(N_VertexList_F2, Bullet_F2.m_VertexList, sizeof(SimpleVertex) * 6);
		memcpy(N_VertexList_G4, Bullet_Ghost_4.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_F2.m_VertexList[iV].x; vertex.y = Bullet_F2.m_VertexList[iV].y;
			vertex.x -= Bullet_F2.m_vCenter.x;		 vertex.y -= Bullet_F2.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_F2[iV].x = vertex.x * C + vertex.y * S; N_VertexList_F2[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_F2[iV].x += Bullet_F2.m_vCenter.x;		 N_VertexList_F2[iV].y += Bullet_F2.m_vCenter.y;
		}

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_4.m_VertexList[iV].x; vertex.y = Bullet_Ghost_4.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_4.m_vCenter.x;		 vertex.y -= Bullet_Ghost_4.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G4[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G4[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G4[iV].x += Bullet_Ghost_4.m_vCenter.x; N_VertexList_G4[iV].y += Bullet_Ghost_4.m_vCenter.y;
		}


		g_pContext->UpdateSubresource(Bullet_F2.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_F2, 0, 0);
		g_pContext->UpdateSubresource(Bullet_Ghost_4.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G4, 0, 0);

	}


	//

	if (TCollision::SphereInSphere(Bullet_F3.m_rtCollision, Bullet_Ghost_1.m_rtCollision))
	{
		Bullet_F3.m_VertexList[0].x = 3.125f; Bullet_F3.m_VertexList[0].y = 3.125f;
		Bullet_F3.m_VertexList[1].x = 3.125f; Bullet_F3.m_VertexList[1].y = 3.125f;
		Bullet_F3.m_VertexList[2].x = 3.125f; Bullet_F3.m_VertexList[2].y = 3.125f;
		Bullet_F3.m_VertexList[3].x = 3.125f; Bullet_F3.m_VertexList[3].y = 3.125f;
		Bullet_F3.m_VertexList[4].x = 3.125f; Bullet_F3.m_VertexList[4].y = 3.125f;
		Bullet_F3.m_VertexList[5].x = 3.125f; Bullet_F3.m_VertexList[5].y = 3.125f;
		Bullet_F3.m_VertexList[6].x = 3.125f; Bullet_F3.m_VertexList[6].y = 3.125f;

		Bullet_Ghost_1.m_VertexList[0].x = 4.301f; Bullet_Ghost_1.m_VertexList[0].y = 4.301f;
		Bullet_Ghost_1.m_VertexList[1].x = 4.301f; Bullet_Ghost_1.m_VertexList[1].y = 4.301f;
		Bullet_Ghost_1.m_VertexList[2].x = 4.301f; Bullet_Ghost_1.m_VertexList[2].y = 4.301f;
		Bullet_Ghost_1.m_VertexList[3].x = 4.301f; Bullet_Ghost_1.m_VertexList[3].y = 4.301f;
		Bullet_Ghost_1.m_VertexList[4].x = 4.301f; Bullet_Ghost_1.m_VertexList[4].y = 4.301f;
		Bullet_Ghost_1.m_VertexList[5].x = 4.301f; Bullet_Ghost_1.m_VertexList[5].y = 4.301f;
		Bullet_Ghost_1.m_VertexList[6].x = 4.301f; Bullet_Ghost_1.m_VertexList[6].y = 4.301f;


		memcpy(N_VertexList_F3, Bullet_F3.m_VertexList, sizeof(SimpleVertex) * 6);
		memcpy(N_VertexList_G1, Bullet_Ghost_1.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_F3.m_VertexList[iV].x; vertex.y = Bullet_F3.m_VertexList[iV].y;
			vertex.x -= Bullet_F3.m_vCenter.x;		 vertex.y -= Bullet_F3.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_F3[iV].x = vertex.x * C + vertex.y * S; N_VertexList_F3[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_F3[iV].x += Bullet_F3.m_vCenter.x;		 N_VertexList_F3[iV].y += Bullet_F3.m_vCenter.y;
		}

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_1.m_VertexList[iV].x; vertex.y = Bullet_Ghost_1.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_1.m_vCenter.x;		 vertex.y -= Bullet_Ghost_1.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G1[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G1[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G1[iV].x += Bullet_Ghost_1.m_vCenter.x; N_VertexList_G1[iV].y += Bullet_Ghost_1.m_vCenter.y;
		}


		g_pContext->UpdateSubresource(Bullet_F3.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_F3, 0, 0);
		g_pContext->UpdateSubresource(Bullet_Ghost_1.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G1, 0, 0);
	}


	if (TCollision::SphereInSphere(Bullet_F3.m_rtCollision, Bullet_Ghost_2.m_rtDetection))
	{
		Bullet_F3.m_VertexList[0].x = 3.713f; Bullet_F3.m_VertexList[0].y = 3.713f;
		Bullet_F3.m_VertexList[1].x = 3.713f; Bullet_F3.m_VertexList[1].y = 3.713f;
		Bullet_F3.m_VertexList[2].x = 3.713f; Bullet_F3.m_VertexList[2].y = 3.713f;
		Bullet_F3.m_VertexList[3].x = 3.713f; Bullet_F3.m_VertexList[3].y = 3.713f;
		Bullet_F3.m_VertexList[4].x = 3.713f; Bullet_F3.m_VertexList[4].y = 3.713f;
		Bullet_F3.m_VertexList[5].x = 3.713f; Bullet_F3.m_VertexList[5].y = 3.713f;
		Bullet_F3.m_VertexList[6].x = 3.713f; Bullet_F3.m_VertexList[6].y = 3.713f;

		Bullet_Ghost_2.m_VertexList[0].x = 3.444f; Bullet_Ghost_2.m_VertexList[0].y = 3.444f;
		Bullet_Ghost_2.m_VertexList[1].x = 3.444f; Bullet_Ghost_2.m_VertexList[1].y = 3.444f;
		Bullet_Ghost_2.m_VertexList[2].x = 3.444f; Bullet_Ghost_2.m_VertexList[2].y = 3.444f;
		Bullet_Ghost_2.m_VertexList[3].x = 3.444f; Bullet_Ghost_2.m_VertexList[3].y = 3.444f;
		Bullet_Ghost_2.m_VertexList[4].x = 3.444f; Bullet_Ghost_2.m_VertexList[4].y = 3.444f;
		Bullet_Ghost_2.m_VertexList[5].x = 3.444f; Bullet_Ghost_2.m_VertexList[5].y = 3.444f;
		Bullet_Ghost_2.m_VertexList[6].x = 3.444f; Bullet_Ghost_2.m_VertexList[6].y = 3.444f;


		memcpy(N_VertexList_F3, Bullet_F3.m_VertexList, sizeof(SimpleVertex) * 6);
		memcpy(N_VertexList_G2, Bullet_Ghost_2.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_F3.m_VertexList[iV].x; vertex.y = Bullet_F3.m_VertexList[iV].y;
			vertex.x -= Bullet_F3.m_vCenter.x;		 vertex.y -= Bullet_F3.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_F3[iV].x = vertex.x * C + vertex.y * S; N_VertexList_F3[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_F3[iV].x += Bullet_F3.m_vCenter.x;		 N_VertexList_F3[iV].y += Bullet_F3.m_vCenter.y;
		}

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_2.m_VertexList[iV].x; vertex.y = Bullet_Ghost_2.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_2.m_vCenter.x;		 vertex.y -= Bullet_Ghost_2.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G2[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G2[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G2[iV].x += Bullet_Ghost_2.m_vCenter.x; N_VertexList_G2[iV].y += Bullet_Ghost_2.m_vCenter.y;
		}


		g_pContext->UpdateSubresource(Bullet_F3.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_F3, 0, 0);
		g_pContext->UpdateSubresource(Bullet_Ghost_2.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G2, 0, 0);
	}

	if (TCollision::SphereInSphere(Bullet_F3.m_rtCollision, Bullet_Ghost_3.m_rtDetection))
	{
		Bullet_F3.m_VertexList[0].x = 3.305f; Bullet_F3.m_VertexList[0].y = 3.305f;
		Bullet_F3.m_VertexList[1].x = 3.305f; Bullet_F3.m_VertexList[1].y = 3.305f;
		Bullet_F3.m_VertexList[2].x = 3.305f; Bullet_F3.m_VertexList[2].y = 3.305f;
		Bullet_F3.m_VertexList[3].x = 3.305f; Bullet_F3.m_VertexList[3].y = 3.305f;
		Bullet_F3.m_VertexList[4].x = 3.305f; Bullet_F3.m_VertexList[4].y = 3.305f;
		Bullet_F3.m_VertexList[5].x = 3.305f; Bullet_F3.m_VertexList[5].y = 3.305f;
		Bullet_F3.m_VertexList[6].x = 3.305f; Bullet_F3.m_VertexList[6].y = 3.305f;

		Bullet_Ghost_3.m_VertexList[0].x = 3.106f; Bullet_Ghost_3.m_VertexList[0].y = 3.106f;
		Bullet_Ghost_3.m_VertexList[1].x = 3.106f; Bullet_Ghost_3.m_VertexList[1].y = 3.106f;
		Bullet_Ghost_3.m_VertexList[2].x = 3.106f; Bullet_Ghost_3.m_VertexList[2].y = 3.106f;
		Bullet_Ghost_3.m_VertexList[3].x = 3.106f; Bullet_Ghost_3.m_VertexList[3].y = 3.106f;
		Bullet_Ghost_3.m_VertexList[4].x = 3.106f; Bullet_Ghost_3.m_VertexList[4].y = 3.106f;
		Bullet_Ghost_3.m_VertexList[5].x = 3.106f; Bullet_Ghost_3.m_VertexList[5].y = 3.106f;
		Bullet_Ghost_3.m_VertexList[6].x = 3.106f; Bullet_Ghost_3.m_VertexList[6].y = 3.106f;


		memcpy(N_VertexList_F3, Bullet_F3.m_VertexList, sizeof(SimpleVertex) * 6);
		memcpy(N_VertexList_G3, Bullet_Ghost_3.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_F3.m_VertexList[iV].x; vertex.y = Bullet_F3.m_VertexList[iV].y;
			vertex.x -= Bullet_F3.m_vCenter.x;		 vertex.y -= Bullet_F3.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_F3[iV].x = vertex.x * C + vertex.y * S; N_VertexList_F3[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_F3[iV].x += Bullet_F3.m_vCenter.x;		 N_VertexList_F3[iV].y += Bullet_F3.m_vCenter.y;
		}

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_3.m_VertexList[iV].x; vertex.y = Bullet_Ghost_3.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_3.m_vCenter.x;		 vertex.y -= Bullet_Ghost_3.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G3[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G3[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G3[iV].x += Bullet_Ghost_3.m_vCenter.x; N_VertexList_G3[iV].y += Bullet_Ghost_3.m_vCenter.y;
		}


		g_pContext->UpdateSubresource(Bullet_F3.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_F3, 0, 0);
		g_pContext->UpdateSubresource(Bullet_Ghost_3.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G3, 0, 0);
	}

	if (TCollision::SphereInSphere(Bullet_F3.m_rtCollision, Bullet_Ghost_4.m_rtDetection))
	{
		Bullet_F3.m_VertexList[0].x = 4.467f; Bullet_F3.m_VertexList[0].y = 4.467f;
		Bullet_F3.m_VertexList[1].x = 4.467f; Bullet_F3.m_VertexList[1].y = 4.467f;
		Bullet_F3.m_VertexList[2].x = 4.467f; Bullet_F3.m_VertexList[2].y = 4.467f;
		Bullet_F3.m_VertexList[3].x = 4.467f; Bullet_F3.m_VertexList[3].y = 4.467f;
		Bullet_F3.m_VertexList[4].x = 4.467f; Bullet_F3.m_VertexList[4].y = 4.467f;
		Bullet_F3.m_VertexList[5].x = 4.467f; Bullet_F3.m_VertexList[5].y = 4.467f;
		Bullet_F3.m_VertexList[6].x = 4.467f; Bullet_F3.m_VertexList[6].y = 4.467f;

		Bullet_Ghost_4.m_VertexList[0].x = 4.675f; Bullet_Ghost_4.m_VertexList[0].y = 4.675f;
		Bullet_Ghost_4.m_VertexList[1].x = 4.675f; Bullet_Ghost_4.m_VertexList[1].y = 4.675f;
		Bullet_Ghost_4.m_VertexList[2].x = 4.675f; Bullet_Ghost_4.m_VertexList[2].y = 4.675f;
		Bullet_Ghost_4.m_VertexList[3].x = 4.675f; Bullet_Ghost_4.m_VertexList[3].y = 4.675f;
		Bullet_Ghost_4.m_VertexList[4].x = 4.675f; Bullet_Ghost_4.m_VertexList[4].y = 4.675f;
		Bullet_Ghost_4.m_VertexList[5].x = 4.675f; Bullet_Ghost_4.m_VertexList[5].y = 4.675f;
		Bullet_Ghost_4.m_VertexList[6].x = 4.675f; Bullet_Ghost_4.m_VertexList[6].y = 4.675f;


		memcpy(N_VertexList_F3, Bullet_F3.m_VertexList, sizeof(SimpleVertex) * 6);
		memcpy(N_VertexList_G4, Bullet_Ghost_4.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_F3.m_VertexList[iV].x; vertex.y = Bullet_F3.m_VertexList[iV].y;
			vertex.x -= Bullet_F3.m_vCenter.x;		 vertex.y -= Bullet_F3.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_F3[iV].x = vertex.x * C + vertex.y * S; N_VertexList_F3[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_F3[iV].x += Bullet_F3.m_vCenter.x;		 N_VertexList_F3[iV].y += Bullet_F3.m_vCenter.y;
		}

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_4.m_VertexList[iV].x; vertex.y = Bullet_Ghost_4.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_4.m_vCenter.x;		 vertex.y -= Bullet_Ghost_4.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G4[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G4[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G4[iV].x += Bullet_Ghost_4.m_vCenter.x; N_VertexList_G4[iV].y += Bullet_Ghost_4.m_vCenter.y;
		}


		g_pContext->UpdateSubresource(Bullet_F3.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_F3, 0, 0);
		g_pContext->UpdateSubresource(Bullet_Ghost_4.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G4, 0, 0);
	}

	//


	if (TCollision::SphereInSphere(Bullet_F4.m_rtCollision, Bullet_Ghost_1.m_rtCollision))
	{
		Bullet_F4.m_VertexList[0].x = 4.322f; Bullet_F4.m_VertexList[0].y = 4.322f;
		Bullet_F4.m_VertexList[1].x = 4.322f; Bullet_F4.m_VertexList[1].y = 4.322f;
		Bullet_F4.m_VertexList[2].x = 4.322f; Bullet_F4.m_VertexList[2].y = 4.322f;
		Bullet_F4.m_VertexList[3].x = 4.322f; Bullet_F4.m_VertexList[3].y = 4.322f;
		Bullet_F4.m_VertexList[4].x = 4.322f; Bullet_F4.m_VertexList[4].y = 4.322f;
		Bullet_F4.m_VertexList[5].x = 4.322f; Bullet_F4.m_VertexList[5].y = 4.322f;
		Bullet_F4.m_VertexList[6].x = 4.322f; Bullet_F4.m_VertexList[6].y = 4.322f;

		Bullet_Ghost_1.m_VertexList[0].x = 3.204f; Bullet_Ghost_1.m_VertexList[0].y = 3.204f;
		Bullet_Ghost_1.m_VertexList[1].x = 3.204f; Bullet_Ghost_1.m_VertexList[1].y = 3.204f;
		Bullet_Ghost_1.m_VertexList[2].x = 3.204f; Bullet_Ghost_1.m_VertexList[2].y = 3.204f;
		Bullet_Ghost_1.m_VertexList[3].x = 3.204f; Bullet_Ghost_1.m_VertexList[3].y = 3.204f;
		Bullet_Ghost_1.m_VertexList[4].x = 3.204f; Bullet_Ghost_1.m_VertexList[4].y = 3.204f;
		Bullet_Ghost_1.m_VertexList[5].x = 3.204f; Bullet_Ghost_1.m_VertexList[5].y = 3.204f;
		Bullet_Ghost_1.m_VertexList[6].x = 3.204f; Bullet_Ghost_1.m_VertexList[6].y = 3.204f;


		memcpy(N_VertexList_F4, Bullet_F4.m_VertexList, sizeof(SimpleVertex) * 6);
		memcpy(N_VertexList_G1, Bullet_Ghost_1.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_F4.m_VertexList[iV].x; vertex.y = Bullet_F4.m_VertexList[iV].y;
			vertex.x -= Bullet_F4.m_vCenter.x;		 vertex.y -= Bullet_F4.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_F4[iV].x = vertex.x * C + vertex.y * S; N_VertexList_F4[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_F4[iV].x += Bullet_F4.m_vCenter.x;		 N_VertexList_F4[iV].y += Bullet_F4.m_vCenter.y;
		}

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_1.m_VertexList[iV].x; vertex.y = Bullet_Ghost_1.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_1.m_vCenter.x;		 vertex.y -= Bullet_Ghost_1.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G1[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G1[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G1[iV].x += Bullet_Ghost_1.m_vCenter.x; N_VertexList_G1[iV].y += Bullet_Ghost_1.m_vCenter.y;
		}


		g_pContext->UpdateSubresource(Bullet_F4.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_F4, 0, 0);
		g_pContext->UpdateSubresource(Bullet_Ghost_1.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G1, 0, 0);
	}


	if (TCollision::SphereInSphere(Bullet_F4.m_rtCollision, Bullet_Ghost_2.m_rtDetection))
	{
		Bullet_F4.m_VertexList[0].x = 3.765f; Bullet_F4.m_VertexList[0].y = 3.765f;
		Bullet_F4.m_VertexList[1].x = 3.765f; Bullet_F4.m_VertexList[1].y = 3.765f;
		Bullet_F4.m_VertexList[2].x = 3.765f; Bullet_F4.m_VertexList[2].y = 3.765f;
		Bullet_F4.m_VertexList[3].x = 3.765f; Bullet_F4.m_VertexList[3].y = 3.765f;
		Bullet_F4.m_VertexList[4].x = 3.765f; Bullet_F4.m_VertexList[4].y = 3.765f;
		Bullet_F4.m_VertexList[5].x = 3.765f; Bullet_F4.m_VertexList[5].y = 3.765f;
		Bullet_F4.m_VertexList[6].x = 3.765f; Bullet_F4.m_VertexList[6].y = 3.765f;

		Bullet_Ghost_2.m_VertexList[0].x = 3.1275f; Bullet_Ghost_2.m_VertexList[0].y = 3.1275f;
		Bullet_Ghost_2.m_VertexList[1].x = 3.1275f; Bullet_Ghost_2.m_VertexList[1].y = 3.1275f;
		Bullet_Ghost_2.m_VertexList[2].x = 3.1275f; Bullet_Ghost_2.m_VertexList[2].y = 3.1275f;
		Bullet_Ghost_2.m_VertexList[3].x = 3.1275f; Bullet_Ghost_2.m_VertexList[3].y = 3.1275f;
		Bullet_Ghost_2.m_VertexList[4].x = 3.1275f; Bullet_Ghost_2.m_VertexList[4].y = 3.1275f;
		Bullet_Ghost_2.m_VertexList[5].x = 3.1275f; Bullet_Ghost_2.m_VertexList[5].y = 3.1275f;
		Bullet_Ghost_2.m_VertexList[6].x = 3.1275f; Bullet_Ghost_2.m_VertexList[6].y = 3.1275f;


		memcpy(N_VertexList_F4, Bullet_F4.m_VertexList, sizeof(SimpleVertex) * 6);
		memcpy(N_VertexList_G2, Bullet_Ghost_2.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_F4.m_VertexList[iV].x; vertex.y = Bullet_F4.m_VertexList[iV].y;
			vertex.x -= Bullet_F4.m_vCenter.x;		 vertex.y -= Bullet_F4.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_F4[iV].x = vertex.x * C + vertex.y * S; N_VertexList_F4[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_F4[iV].x += Bullet_F4.m_vCenter.x;		 N_VertexList_F4[iV].y += Bullet_F4.m_vCenter.y;
		}

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_2.m_VertexList[iV].x; vertex.y = Bullet_Ghost_2.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_2.m_vCenter.x;		 vertex.y -= Bullet_Ghost_2.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G2[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G2[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G2[iV].x += Bullet_Ghost_2.m_vCenter.x; N_VertexList_G2[iV].y += Bullet_Ghost_2.m_vCenter.y;
		}


		g_pContext->UpdateSubresource(Bullet_F4.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_F4, 0, 0);
		g_pContext->UpdateSubresource(Bullet_Ghost_2.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G2, 0, 0);
	}

	if (TCollision::SphereInSphere(Bullet_F4.m_rtCollision, Bullet_Ghost_3.m_rtDetection))
	{
		Bullet_F4.m_VertexList[0].x = 3.812f; Bullet_F4.m_VertexList[0].y = 3.812f;
		Bullet_F4.m_VertexList[1].x = 3.812f; Bullet_F4.m_VertexList[1].y = 3.812f;
		Bullet_F4.m_VertexList[2].x = 3.812f; Bullet_F4.m_VertexList[2].y = 3.812f;
		Bullet_F4.m_VertexList[3].x = 3.812f; Bullet_F4.m_VertexList[3].y = 3.812f;
		Bullet_F4.m_VertexList[4].x = 3.812f; Bullet_F4.m_VertexList[4].y = 3.812f;
		Bullet_F4.m_VertexList[5].x = 3.812f; Bullet_F4.m_VertexList[5].y = 3.812f;
		Bullet_F4.m_VertexList[6].x = 3.812f; Bullet_F4.m_VertexList[6].y = 3.812f;

		Bullet_Ghost_3.m_VertexList[0].x = 2.828f; Bullet_Ghost_3.m_VertexList[0].y = 2.828f;
		Bullet_Ghost_3.m_VertexList[1].x = 2.828f; Bullet_Ghost_3.m_VertexList[1].y = 2.828f;
		Bullet_Ghost_3.m_VertexList[2].x = 2.828f; Bullet_Ghost_3.m_VertexList[2].y = 2.828f;
		Bullet_Ghost_3.m_VertexList[3].x = 2.828f; Bullet_Ghost_3.m_VertexList[3].y = 2.828f;
		Bullet_Ghost_3.m_VertexList[4].x = 2.828f; Bullet_Ghost_3.m_VertexList[4].y = 2.828f;
		Bullet_Ghost_3.m_VertexList[5].x = 2.828f; Bullet_Ghost_3.m_VertexList[5].y = 2.828f;
		Bullet_Ghost_3.m_VertexList[6].x = 2.828f; Bullet_Ghost_3.m_VertexList[6].y = 2.828f;


		memcpy(N_VertexList_F4, Bullet_F4.m_VertexList, sizeof(SimpleVertex) * 6);
		memcpy(N_VertexList_G3, Bullet_Ghost_3.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_F4.m_VertexList[iV].x; vertex.y = Bullet_F4.m_VertexList[iV].y;
			vertex.x -= Bullet_F4.m_vCenter.x;		 vertex.y -= Bullet_F4.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_F4[iV].x = vertex.x * C + vertex.y * S; N_VertexList_F4[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_F4[iV].x += Bullet_F4.m_vCenter.x;		 N_VertexList_F4[iV].y += Bullet_F4.m_vCenter.y;
		}

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_3.m_VertexList[iV].x; vertex.y = Bullet_Ghost_3.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_3.m_vCenter.x;		 vertex.y -= Bullet_Ghost_3.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G3[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G3[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G3[iV].x += Bullet_Ghost_3.m_vCenter.x; N_VertexList_G3[iV].y += Bullet_Ghost_3.m_vCenter.y;
		}


		g_pContext->UpdateSubresource(Bullet_F4.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_F4, 0, 0);
		g_pContext->UpdateSubresource(Bullet_Ghost_3.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G3, 0, 0);
	}

	if (TCollision::SphereInSphere(Bullet_F4.m_rtCollision, Bullet_Ghost_4.m_rtDetection))
	{
		Bullet_F4.m_VertexList[0].x = 6.306f; Bullet_F4.m_VertexList[0].y = 6.306f;
		Bullet_F4.m_VertexList[1].x = 6.306f; Bullet_F4.m_VertexList[1].y = 6.306f;
		Bullet_F4.m_VertexList[2].x = 6.306f; Bullet_F4.m_VertexList[2].y = 6.306f;
		Bullet_F4.m_VertexList[3].x = 6.306f; Bullet_F4.m_VertexList[3].y = 6.306f;
		Bullet_F4.m_VertexList[4].x = 6.306f; Bullet_F4.m_VertexList[4].y = 6.306f;
		Bullet_F4.m_VertexList[5].x = 6.306f; Bullet_F4.m_VertexList[5].y = 6.306f;
		Bullet_F4.m_VertexList[6].x = 6.306f; Bullet_F4.m_VertexList[6].y = 6.306f;

		Bullet_Ghost_4.m_VertexList[0].x = 3.741f; Bullet_Ghost_4.m_VertexList[0].y = 3.741f;
		Bullet_Ghost_4.m_VertexList[1].x = 3.741f; Bullet_Ghost_4.m_VertexList[1].y = 3.741f;
		Bullet_Ghost_4.m_VertexList[2].x = 3.741f; Bullet_Ghost_4.m_VertexList[2].y = 3.741f;
		Bullet_Ghost_4.m_VertexList[3].x = 3.741f; Bullet_Ghost_4.m_VertexList[3].y = 3.741f;
		Bullet_Ghost_4.m_VertexList[4].x = 3.741f; Bullet_Ghost_4.m_VertexList[4].y = 3.741f;
		Bullet_Ghost_4.m_VertexList[5].x = 3.741f; Bullet_Ghost_4.m_VertexList[5].y = 3.741f;
		Bullet_Ghost_4.m_VertexList[6].x = 3.741f; Bullet_Ghost_4.m_VertexList[6].y = 3.741f;


		memcpy(N_VertexList_F4, Bullet_F4.m_VertexList, sizeof(SimpleVertex) * 6);
		memcpy(N_VertexList_G4, Bullet_Ghost_4.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_F4.m_VertexList[iV].x; vertex.y = Bullet_F4.m_VertexList[iV].y;
			vertex.x -= Bullet_F4.m_vCenter.x;		 vertex.y -= Bullet_F4.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_F4[iV].x = vertex.x * C + vertex.y * S; N_VertexList_F4[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_F4[iV].x += Bullet_F4.m_vCenter.x;		 N_VertexList_F4[iV].y += Bullet_F4.m_vCenter.y;
		}

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_4.m_VertexList[iV].x; vertex.y = Bullet_Ghost_4.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_4.m_vCenter.x;		 vertex.y -= Bullet_Ghost_4.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G4[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G4[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G4[iV].x += Bullet_Ghost_4.m_vCenter.x; N_VertexList_G4[iV].y += Bullet_Ghost_4.m_vCenter.y;
		}


		g_pContext->UpdateSubresource(Bullet_F4.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_F4, 0, 0);
		g_pContext->UpdateSubresource(Bullet_Ghost_4.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G4, 0, 0);
	}



	if (TCollision::SphereInSphere(Bullet_C1.m_rtCollision, Bullet_Ghost_1.m_rtCollision))
	{

		Bullet_C1.m_VertexList[0].x = 4.115f; Bullet_C1.m_VertexList[0].y = 4.115f;
		Bullet_C1.m_VertexList[1].x = 4.115f; Bullet_C1.m_VertexList[1].y = 4.115f;
		Bullet_C1.m_VertexList[2].x = 4.115f; Bullet_C1.m_VertexList[2].y = 4.115f;
		Bullet_C1.m_VertexList[3].x = 4.115f; Bullet_C1.m_VertexList[3].y = 4.115f;
		Bullet_C1.m_VertexList[4].x = 4.115f; Bullet_C1.m_VertexList[4].y = 4.115f;
		Bullet_C1.m_VertexList[5].x = 4.115f; Bullet_C1.m_VertexList[5].y = 4.115f;
		Bullet_C1.m_VertexList[6].x = 4.115f; Bullet_C1.m_VertexList[6].y = 4.115f;

		Bullet_Ghost_1.m_VertexList[0].x = 4.802f; Bullet_Ghost_1.m_VertexList[0].y = 4.802f;
		Bullet_Ghost_1.m_VertexList[1].x = 4.802f; Bullet_Ghost_1.m_VertexList[1].y = 4.802f;
		Bullet_Ghost_1.m_VertexList[2].x = 4.802f; Bullet_Ghost_1.m_VertexList[2].y = 4.802f;
		Bullet_Ghost_1.m_VertexList[3].x = 4.802f; Bullet_Ghost_1.m_VertexList[3].y = 4.802f;
		Bullet_Ghost_1.m_VertexList[4].x = 4.802f; Bullet_Ghost_1.m_VertexList[4].y = 4.802f;
		Bullet_Ghost_1.m_VertexList[5].x = 4.802f; Bullet_Ghost_1.m_VertexList[5].y = 4.802f;
		Bullet_Ghost_1.m_VertexList[6].x = 4.802f; Bullet_Ghost_1.m_VertexList[6].y = 4.802f;


		memcpy(N_VertexList_C1, Bullet_C1.m_VertexList, sizeof(SimpleVertex) * 6);
		memcpy(N_VertexList_G1, Bullet_Ghost_1.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_C1.m_VertexList[iV].x; vertex.y = Bullet_C1.m_VertexList[iV].y;
			vertex.x -= Bullet_C1.m_vCenter.x;		 vertex.y -= Bullet_C1.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_C1[iV].x = vertex.x * C + vertex.y * S; N_VertexList_C1[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_C1[iV].x += Bullet_C1.m_vCenter.x;		 N_VertexList_C1[iV].y += Bullet_C1.m_vCenter.y;
		}

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_1.m_VertexList[iV].x; vertex.y = Bullet_Ghost_1.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_1.m_vCenter.x;		 vertex.y -= Bullet_Ghost_1.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G1[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G1[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G1[iV].x += Bullet_Ghost_1.m_vCenter.x; N_VertexList_G1[iV].y += Bullet_Ghost_1.m_vCenter.y;
		}


		g_pContext->UpdateSubresource(Bullet_C1.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_C1, 0, 0);
		g_pContext->UpdateSubresource(Bullet_Ghost_1.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G1, 0, 0);
	}


	if (TCollision::SphereInSphere(Bullet_C1.m_rtCollision, Bullet_Ghost_2.m_rtDetection))
	{
		Bullet_C1.m_VertexList[0].x = 2.344f; Bullet_C1.m_VertexList[0].y = 2.344f;
		Bullet_C1.m_VertexList[1].x = 2.344f; Bullet_C1.m_VertexList[1].y = 2.344f;
		Bullet_C1.m_VertexList[2].x = 2.344f; Bullet_C1.m_VertexList[2].y = 2.344f;
		Bullet_C1.m_VertexList[3].x = 2.344f; Bullet_C1.m_VertexList[3].y = 2.344f;
		Bullet_C1.m_VertexList[4].x = 2.344f; Bullet_C1.m_VertexList[4].y = 2.344f;
		Bullet_C1.m_VertexList[5].x = 2.344f; Bullet_C1.m_VertexList[5].y = 2.344f;
		Bullet_C1.m_VertexList[6].x = 2.344f; Bullet_C1.m_VertexList[6].y = 2.344f;

		Bullet_Ghost_2.m_VertexList[0].x = 4.101f; Bullet_Ghost_2.m_VertexList[0].y = 4.101f;
		Bullet_Ghost_2.m_VertexList[1].x = 4.101f; Bullet_Ghost_2.m_VertexList[1].y = 4.101f;
		Bullet_Ghost_2.m_VertexList[2].x = 4.101f; Bullet_Ghost_2.m_VertexList[2].y = 4.101f;
		Bullet_Ghost_2.m_VertexList[3].x = 4.101f; Bullet_Ghost_2.m_VertexList[3].y = 4.101f;
		Bullet_Ghost_2.m_VertexList[4].x = 4.101f; Bullet_Ghost_2.m_VertexList[4].y = 4.101f;
		Bullet_Ghost_2.m_VertexList[5].x = 4.101f; Bullet_Ghost_2.m_VertexList[5].y = 4.101f;
		Bullet_Ghost_2.m_VertexList[6].x = 4.101f; Bullet_Ghost_2.m_VertexList[6].y = 4.101f;


		memcpy(N_VertexList_C1, Bullet_C1.m_VertexList, sizeof(SimpleVertex) * 6);
		memcpy(N_VertexList_G2, Bullet_Ghost_2.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_C1.m_VertexList[iV].x; vertex.y = Bullet_C1.m_VertexList[iV].y;
			vertex.x -= Bullet_C1.m_vCenter.x;		 vertex.y -= Bullet_C1.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_C1[iV].x = vertex.x * C + vertex.y * S; N_VertexList_C1[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_C1[iV].x += Bullet_C1.m_vCenter.x;		 N_VertexList_C1[iV].y += Bullet_C1.m_vCenter.y;
		}

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_2.m_VertexList[iV].x; vertex.y = Bullet_Ghost_2.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_2.m_vCenter.x;		 vertex.y -= Bullet_Ghost_2.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G2[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G2[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G2[iV].x += Bullet_Ghost_2.m_vCenter.x; N_VertexList_G2[iV].y += Bullet_Ghost_2.m_vCenter.y;
		}


		g_pContext->UpdateSubresource(Bullet_C1.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_C1, 0, 0);
		g_pContext->UpdateSubresource(Bullet_Ghost_2.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G2, 0, 0);
	}

	if (TCollision::SphereInSphere(Bullet_C1.m_rtCollision, Bullet_Ghost_3.m_rtDetection))
	{

		Bullet_C1.m_VertexList[0].x = 4.785f; Bullet_C1.m_VertexList[0].y = 4.785f;
		Bullet_C1.m_VertexList[1].x = 4.785f; Bullet_C1.m_VertexList[1].y = 4.785f;
		Bullet_C1.m_VertexList[2].x = 4.785f; Bullet_C1.m_VertexList[2].y = 4.785f;
		Bullet_C1.m_VertexList[3].x = 4.785f; Bullet_C1.m_VertexList[3].y = 4.785f;
		Bullet_C1.m_VertexList[4].x = 4.785f; Bullet_C1.m_VertexList[4].y = 4.785f;
		Bullet_C1.m_VertexList[5].x = 4.785f; Bullet_C1.m_VertexList[5].y = 4.785f;
		Bullet_C1.m_VertexList[6].x = 4.785f; Bullet_C1.m_VertexList[6].y = 4.785f;

		Bullet_Ghost_3.m_VertexList[0].x = 5.405f; Bullet_Ghost_3.m_VertexList[0].y = 5.405f;
		Bullet_Ghost_3.m_VertexList[1].x = 5.405f; Bullet_Ghost_3.m_VertexList[1].y = 5.405f;
		Bullet_Ghost_3.m_VertexList[2].x = 5.405f; Bullet_Ghost_3.m_VertexList[2].y = 5.405f;
		Bullet_Ghost_3.m_VertexList[3].x = 5.405f; Bullet_Ghost_3.m_VertexList[3].y = 5.405f;
		Bullet_Ghost_3.m_VertexList[4].x = 5.405f; Bullet_Ghost_3.m_VertexList[4].y = 5.405f;
		Bullet_Ghost_3.m_VertexList[5].x = 5.405f; Bullet_Ghost_3.m_VertexList[5].y = 5.405f;
		Bullet_Ghost_3.m_VertexList[6].x = 5.405f; Bullet_Ghost_3.m_VertexList[6].y = 5.405f;


		memcpy(N_VertexList_C1, Bullet_C1.m_VertexList, sizeof(SimpleVertex) * 6);
		memcpy(N_VertexList_G3, Bullet_Ghost_3.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_C1.m_VertexList[iV].x; vertex.y = Bullet_C1.m_VertexList[iV].y;
			vertex.x -= Bullet_C1.m_vCenter.x;		 vertex.y -= Bullet_C1.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_C1[iV].x = vertex.x * C + vertex.y * S; N_VertexList_C1[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_C1[iV].x += Bullet_C1.m_vCenter.x;		 N_VertexList_C1[iV].y += Bullet_C1.m_vCenter.y;
		}

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_3.m_VertexList[iV].x; vertex.y = Bullet_Ghost_3.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_3.m_vCenter.x;		 vertex.y -= Bullet_Ghost_3.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G3[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G3[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G3[iV].x += Bullet_Ghost_3.m_vCenter.x; N_VertexList_G3[iV].y += Bullet_Ghost_3.m_vCenter.y;
		}


		g_pContext->UpdateSubresource(Bullet_C1.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_C1, 0, 0);
		g_pContext->UpdateSubresource(Bullet_Ghost_3.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G3, 0, 0);

	}


	if (TCollision::SphereInSphere(Bullet_C1.m_rtCollision, Bullet_Ghost_4.m_rtDetection))
	{
		Bullet_C1.m_VertexList[0].x = 4.1127f; Bullet_C1.m_VertexList[0].y = 4.1127f;
		Bullet_C1.m_VertexList[1].x = 4.1127f; Bullet_C1.m_VertexList[1].y = 4.1127f;
		Bullet_C1.m_VertexList[2].x = 4.1127f; Bullet_C1.m_VertexList[2].y = 4.1127f;
		Bullet_C1.m_VertexList[3].x = 4.1127f; Bullet_C1.m_VertexList[3].y = 4.1127f;
		Bullet_C1.m_VertexList[4].x = 4.1127f; Bullet_C1.m_VertexList[4].y = 4.1127f;
		Bullet_C1.m_VertexList[5].x = 4.1127f; Bullet_C1.m_VertexList[5].y = 4.1127f;
		Bullet_C1.m_VertexList[6].x = 4.1127f; Bullet_C1.m_VertexList[6].y = 4.1127f;

		Bullet_Ghost_4.m_VertexList[0].x = 4.8074f; Bullet_Ghost_4.m_VertexList[0].y = 4.8074f;
		Bullet_Ghost_4.m_VertexList[1].x = 4.8074f; Bullet_Ghost_4.m_VertexList[1].y = 4.8074f;
		Bullet_Ghost_4.m_VertexList[2].x = 4.8074f; Bullet_Ghost_4.m_VertexList[2].y = 4.8074f;
		Bullet_Ghost_4.m_VertexList[3].x = 4.8074f; Bullet_Ghost_4.m_VertexList[3].y = 4.8074f;
		Bullet_Ghost_4.m_VertexList[4].x = 4.8074f; Bullet_Ghost_4.m_VertexList[4].y = 4.8074f;
		Bullet_Ghost_4.m_VertexList[5].x = 4.8074f; Bullet_Ghost_4.m_VertexList[5].y = 4.8074f;
		Bullet_Ghost_4.m_VertexList[6].x = 4.8074f; Bullet_Ghost_4.m_VertexList[6].y = 4.8074f;


		memcpy(N_VertexList_C1, Bullet_C1.m_VertexList, sizeof(SimpleVertex) * 6);
		memcpy(N_VertexList_G4, Bullet_Ghost_4.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_C1.m_VertexList[iV].x; vertex.y = Bullet_C1.m_VertexList[iV].y;
			vertex.x -= Bullet_C1.m_vCenter.x;		 vertex.y -= Bullet_C1.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_C1[iV].x = vertex.x * C + vertex.y * S; N_VertexList_C1[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_C1[iV].x += Bullet_C1.m_vCenter.x;		 N_VertexList_C1[iV].y += Bullet_C1.m_vCenter.y;
		}

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_4.m_VertexList[iV].x; vertex.y = Bullet_Ghost_4.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_4.m_vCenter.x;		 vertex.y -= Bullet_Ghost_4.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G4[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G4[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G4[iV].x += Bullet_Ghost_4.m_vCenter.x; N_VertexList_G4[iV].y += Bullet_Ghost_4.m_vCenter.y;
		}


		g_pContext->UpdateSubresource(Bullet_C1.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_C1, 0, 0);
		g_pContext->UpdateSubresource(Bullet_Ghost_4.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G4, 0, 0);
	}



	if (TCollision::SphereInSphere(Bullet_C2.m_rtCollision, Bullet_Ghost_1.m_rtCollision))
	{

		Bullet_C2.m_VertexList[0].x = 4.202f; Bullet_C2.m_VertexList[0].y = 4.202f;
		Bullet_C2.m_VertexList[1].x = 4.202f; Bullet_C2.m_VertexList[1].y = 4.202f;
		Bullet_C2.m_VertexList[2].x = 4.202f; Bullet_C2.m_VertexList[2].y = 4.202f;
		Bullet_C2.m_VertexList[3].x = 4.202f; Bullet_C2.m_VertexList[3].y = 4.202f;
		Bullet_C2.m_VertexList[4].x = 4.202f; Bullet_C2.m_VertexList[4].y = 4.202f;
		Bullet_C2.m_VertexList[5].x = 4.202f; Bullet_C2.m_VertexList[5].y = 4.202f;
		Bullet_C2.m_VertexList[6].x = 4.202f; Bullet_C2.m_VertexList[6].y = 4.202f;

		Bullet_Ghost_1.m_VertexList[0].x = 4.712f; Bullet_Ghost_1.m_VertexList[0].y = 4.712f;
		Bullet_Ghost_1.m_VertexList[1].x = 4.712f; Bullet_Ghost_1.m_VertexList[1].y = 4.712f;
		Bullet_Ghost_1.m_VertexList[2].x = 4.712f; Bullet_Ghost_1.m_VertexList[2].y = 4.712f;
		Bullet_Ghost_1.m_VertexList[3].x = 4.712f; Bullet_Ghost_1.m_VertexList[3].y = 4.712f;
		Bullet_Ghost_1.m_VertexList[4].x = 4.712f; Bullet_Ghost_1.m_VertexList[4].y = 4.712f;
		Bullet_Ghost_1.m_VertexList[5].x = 4.712f; Bullet_Ghost_1.m_VertexList[5].y = 4.712f;
		Bullet_Ghost_1.m_VertexList[6].x = 4.712f; Bullet_Ghost_1.m_VertexList[6].y = 4.712f;


		memcpy(N_VertexList_C2, Bullet_C2.m_VertexList, sizeof(SimpleVertex) * 6);
		memcpy(N_VertexList_G1, Bullet_Ghost_1.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_C2.m_VertexList[iV].x; vertex.y = Bullet_C2.m_VertexList[iV].y;
			vertex.x -= Bullet_C2.m_vCenter.x;		 vertex.y -= Bullet_C2.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_C2[iV].x = vertex.x * C + vertex.y * S; N_VertexList_C2[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_C2[iV].x += Bullet_C2.m_vCenter.x;		 N_VertexList_C2[iV].y += Bullet_C2.m_vCenter.y;
		}

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_1.m_VertexList[iV].x; vertex.y = Bullet_Ghost_1.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_1.m_vCenter.x;		 vertex.y -= Bullet_Ghost_1.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G1[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G1[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G1[iV].x += Bullet_Ghost_1.m_vCenter.x; N_VertexList_G1[iV].y += Bullet_Ghost_1.m_vCenter.y;
		}


		g_pContext->UpdateSubresource(Bullet_C2.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_C2, 0, 0);
		g_pContext->UpdateSubresource(Bullet_Ghost_1.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G1, 0, 0);
	}


	if (TCollision::SphereInSphere(Bullet_C2.m_rtCollision, Bullet_Ghost_2.m_rtDetection))
	{
		Bullet_C2.m_VertexList[0].x = 2.335f; Bullet_C2.m_VertexList[0].y = 2.335f;
		Bullet_C2.m_VertexList[1].x = 2.335f; Bullet_C2.m_VertexList[1].y = 2.335f;
		Bullet_C2.m_VertexList[2].x = 2.335f; Bullet_C2.m_VertexList[2].y = 2.335f;
		Bullet_C2.m_VertexList[3].x = 2.335f; Bullet_C2.m_VertexList[3].y = 2.335f;
		Bullet_C2.m_VertexList[4].x = 2.335f; Bullet_C2.m_VertexList[4].y = 2.335f;
		Bullet_C2.m_VertexList[5].x = 2.335f; Bullet_C2.m_VertexList[5].y = 2.335f;
		Bullet_C2.m_VertexList[6].x = 2.335f; Bullet_C2.m_VertexList[6].y = 2.335f;

		Bullet_Ghost_2.m_VertexList[0].x = 5.032f; Bullet_Ghost_2.m_VertexList[0].y =5.032f;
		Bullet_Ghost_2.m_VertexList[1].x = 5.032f; Bullet_Ghost_2.m_VertexList[1].y =5.032f;
		Bullet_Ghost_2.m_VertexList[2].x = 5.032f; Bullet_Ghost_2.m_VertexList[2].y =5.032f;
		Bullet_Ghost_2.m_VertexList[3].x = 5.032f; Bullet_Ghost_2.m_VertexList[3].y =5.032f;
		Bullet_Ghost_2.m_VertexList[4].x = 5.032f; Bullet_Ghost_2.m_VertexList[4].y =5.032f;
		Bullet_Ghost_2.m_VertexList[5].x = 5.032f; Bullet_Ghost_2.m_VertexList[5].y =5.032f;
		Bullet_Ghost_2.m_VertexList[6].x = 5.032f; Bullet_Ghost_2.m_VertexList[6].y =5.032f;


		memcpy(N_VertexList_C2, Bullet_C2.m_VertexList, sizeof(SimpleVertex) * 6);
		memcpy(N_VertexList_G2, Bullet_Ghost_2.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_C2.m_VertexList[iV].x; vertex.y = Bullet_C2.m_VertexList[iV].y;
			vertex.x -= Bullet_C2.m_vCenter.x;		 vertex.y -= Bullet_C2.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_C2[iV].x = vertex.x * C + vertex.y * S; N_VertexList_C2[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_C2[iV].x += Bullet_C2.m_vCenter.x;		 N_VertexList_C2[iV].y += Bullet_C2.m_vCenter.y;
		}

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_2.m_VertexList[iV].x; vertex.y = Bullet_Ghost_2.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_2.m_vCenter.x;		 vertex.y -= Bullet_Ghost_2.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G2[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G2[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G2[iV].x += Bullet_Ghost_2.m_vCenter.x; N_VertexList_G2[iV].y += Bullet_Ghost_2.m_vCenter.y;
		}


		g_pContext->UpdateSubresource(Bullet_C2.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_C2, 0, 0);
		g_pContext->UpdateSubresource(Bullet_Ghost_2.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G2, 0, 0);
	}

	if (TCollision::SphereInSphere(Bullet_C2.m_rtCollision, Bullet_Ghost_3.m_rtDetection))
	{

		Bullet_C2.m_VertexList[0].x = 3.833f; Bullet_C2.m_VertexList[0].y = 3.833f;
		Bullet_C2.m_VertexList[1].x = 3.833f; Bullet_C2.m_VertexList[1].y = 3.833f;
		Bullet_C2.m_VertexList[2].x = 3.833f; Bullet_C2.m_VertexList[2].y = 3.833f;
		Bullet_C2.m_VertexList[3].x = 3.833f; Bullet_C2.m_VertexList[3].y = 3.833f;
		Bullet_C2.m_VertexList[4].x = 3.833f; Bullet_C2.m_VertexList[4].y = 3.833f;
		Bullet_C2.m_VertexList[5].x = 3.833f; Bullet_C2.m_VertexList[5].y = 3.833f;
		Bullet_C2.m_VertexList[6].x = 3.833f; Bullet_C2.m_VertexList[6].y = 3.833f;

		Bullet_Ghost_3.m_VertexList[0].x = 4.162f; Bullet_Ghost_3.m_VertexList[0].y = 4.162f;
		Bullet_Ghost_3.m_VertexList[1].x = 4.162f; Bullet_Ghost_3.m_VertexList[1].y = 4.162f;
		Bullet_Ghost_3.m_VertexList[2].x = 4.162f; Bullet_Ghost_3.m_VertexList[2].y = 4.162f;
		Bullet_Ghost_3.m_VertexList[3].x = 4.162f; Bullet_Ghost_3.m_VertexList[3].y = 4.162f;
		Bullet_Ghost_3.m_VertexList[4].x = 4.162f; Bullet_Ghost_3.m_VertexList[4].y = 4.162f;
		Bullet_Ghost_3.m_VertexList[5].x = 4.162f; Bullet_Ghost_3.m_VertexList[5].y = 4.162f;
		Bullet_Ghost_3.m_VertexList[6].x = 4.162f; Bullet_Ghost_3.m_VertexList[6].y = 4.162f;


		memcpy(N_VertexList_C2, Bullet_C2.m_VertexList, sizeof(SimpleVertex) * 6);
		memcpy(N_VertexList_G3, Bullet_Ghost_3.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_C2.m_VertexList[iV].x; vertex.y = Bullet_C2.m_VertexList[iV].y;
			vertex.x -= Bullet_C2.m_vCenter.x;		 vertex.y -= Bullet_C2.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_C2[iV].x = vertex.x * C + vertex.y * S; N_VertexList_C2[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_C2[iV].x += Bullet_C2.m_vCenter.x;		 N_VertexList_C2[iV].y += Bullet_C2.m_vCenter.y;
		}

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_3.m_VertexList[iV].x; vertex.y = Bullet_Ghost_3.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_3.m_vCenter.x;		 vertex.y -= Bullet_Ghost_3.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G3[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G3[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G3[iV].x += Bullet_Ghost_3.m_vCenter.x; N_VertexList_G3[iV].y += Bullet_Ghost_3.m_vCenter.y;
		}


		g_pContext->UpdateSubresource(Bullet_C2.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_C2, 0, 0);
		g_pContext->UpdateSubresource(Bullet_Ghost_3.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G3, 0, 0);
	}


	if (TCollision::SphereInSphere(Bullet_C2.m_rtCollision, Bullet_Ghost_4.m_rtDetection))
	{
		Bullet_C2.m_VertexList[0].x = 3.033f; Bullet_C2.m_VertexList[0].y = 3.033f;
		Bullet_C2.m_VertexList[1].x = 3.033f; Bullet_C2.m_VertexList[1].y = 3.033f;
		Bullet_C2.m_VertexList[2].x = 3.033f; Bullet_C2.m_VertexList[2].y = 3.033f;
		Bullet_C2.m_VertexList[3].x = 3.033f; Bullet_C2.m_VertexList[3].y = 3.033f;
		Bullet_C2.m_VertexList[4].x = 3.033f; Bullet_C2.m_VertexList[4].y = 3.033f;
		Bullet_C2.m_VertexList[5].x = 3.033f; Bullet_C2.m_VertexList[5].y = 3.033f;
		Bullet_C2.m_VertexList[6].x = 3.033f; Bullet_C2.m_VertexList[6].y = 3.033f;

		Bullet_Ghost_4.m_VertexList[0].x = 2.768f; Bullet_Ghost_4.m_VertexList[0].y = 2.768f;
		Bullet_Ghost_4.m_VertexList[1].x = 2.768f; Bullet_Ghost_4.m_VertexList[1].y = 2.768f;
		Bullet_Ghost_4.m_VertexList[2].x = 2.768f; Bullet_Ghost_4.m_VertexList[2].y = 2.768f;
		Bullet_Ghost_4.m_VertexList[3].x = 2.768f; Bullet_Ghost_4.m_VertexList[3].y = 2.768f;
		Bullet_Ghost_4.m_VertexList[4].x = 2.768f; Bullet_Ghost_4.m_VertexList[4].y = 2.768f;
		Bullet_Ghost_4.m_VertexList[5].x = 2.768f; Bullet_Ghost_4.m_VertexList[5].y = 2.768f;
		Bullet_Ghost_4.m_VertexList[6].x = 2.768f; Bullet_Ghost_4.m_VertexList[6].y = 2.768f;


		memcpy(N_VertexList_C2, Bullet_C2.m_VertexList, sizeof(SimpleVertex) * 6);
		memcpy(N_VertexList_G4, Bullet_Ghost_4.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_C2.m_VertexList[iV].x; vertex.y = Bullet_C2.m_VertexList[iV].y;
			vertex.x -= Bullet_C2.m_vCenter.x;		 vertex.y -= Bullet_C2.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_C2[iV].x = vertex.x * C + vertex.y * S; N_VertexList_C2[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_C2[iV].x += Bullet_C2.m_vCenter.x;		 N_VertexList_C2[iV].y += Bullet_C2.m_vCenter.y;
		}

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_4.m_VertexList[iV].x; vertex.y = Bullet_Ghost_4.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_4.m_vCenter.x;		 vertex.y -= Bullet_Ghost_4.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G4[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G4[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G4[iV].x += Bullet_Ghost_4.m_vCenter.x; N_VertexList_G4[iV].y += Bullet_Ghost_4.m_vCenter.y;
		}


		g_pContext->UpdateSubresource(Bullet_C2.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_C2, 0, 0);
		g_pContext->UpdateSubresource(Bullet_Ghost_4.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G4, 0, 0);
	}




	if (TCollision::SphereInSphere(Bullet_C3.m_rtCollision, Bullet_Ghost_1.m_rtCollision))
	{

		Bullet_C3.m_VertexList[0].x = 3.609f; Bullet_C3.m_VertexList[0].y = 3.609f;
		Bullet_C3.m_VertexList[1].x = 3.609f; Bullet_C3.m_VertexList[1].y = 3.609f;
		Bullet_C3.m_VertexList[2].x = 3.609f; Bullet_C3.m_VertexList[2].y = 3.609f;
		Bullet_C3.m_VertexList[3].x = 3.609f; Bullet_C3.m_VertexList[3].y = 3.609f;
		Bullet_C3.m_VertexList[4].x = 3.609f; Bullet_C3.m_VertexList[4].y = 3.609f;
		Bullet_C3.m_VertexList[5].x = 3.609f; Bullet_C3.m_VertexList[5].y = 3.609f;
		Bullet_C3.m_VertexList[6].x = 3.609f; Bullet_C3.m_VertexList[6].y = 3.609f;

		Bullet_Ghost_1.m_VertexList[0].x = 3.907f; Bullet_Ghost_1.m_VertexList[0].y = 3.907f;
		Bullet_Ghost_1.m_VertexList[1].x = 3.907f; Bullet_Ghost_1.m_VertexList[1].y = 3.907f;
		Bullet_Ghost_1.m_VertexList[2].x = 3.907f; Bullet_Ghost_1.m_VertexList[2].y = 3.907f;
		Bullet_Ghost_1.m_VertexList[3].x = 3.907f; Bullet_Ghost_1.m_VertexList[3].y = 3.907f;
		Bullet_Ghost_1.m_VertexList[4].x = 3.907f; Bullet_Ghost_1.m_VertexList[4].y = 3.907f;
		Bullet_Ghost_1.m_VertexList[5].x = 3.907f; Bullet_Ghost_1.m_VertexList[5].y = 3.907f;
		Bullet_Ghost_1.m_VertexList[6].x = 3.907f; Bullet_Ghost_1.m_VertexList[6].y = 3.907f;


		memcpy(N_VertexList_C3, Bullet_C3.m_VertexList, sizeof(SimpleVertex) * 6);
		memcpy(N_VertexList_G1, Bullet_Ghost_1.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_C3.m_VertexList[iV].x; vertex.y = Bullet_C3.m_VertexList[iV].y;
			vertex.x -= Bullet_C3.m_vCenter.x;		 vertex.y -= Bullet_C3.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_C3[iV].x = vertex.x * C + vertex.y * S; N_VertexList_C3[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_C3[iV].x += Bullet_C3.m_vCenter.x;		 N_VertexList_C3[iV].y += Bullet_C3.m_vCenter.y;
		}

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_1.m_VertexList[iV].x; vertex.y = Bullet_Ghost_1.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_1.m_vCenter.x;		 vertex.y -= Bullet_Ghost_1.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G1[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G1[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G1[iV].x += Bullet_Ghost_1.m_vCenter.x; N_VertexList_G1[iV].y += Bullet_Ghost_1.m_vCenter.y;
		}


		g_pContext->UpdateSubresource(Bullet_C3.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_C3, 0, 0);
		g_pContext->UpdateSubresource(Bullet_Ghost_1.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G1, 0, 0);
	}


	if (TCollision::SphereInSphere(Bullet_C3.m_rtCollision, Bullet_Ghost_2.m_rtDetection))
	{
		Bullet_C3.m_VertexList[0].x = 4.4005f; Bullet_C3.m_VertexList[0].y = 4.4005f;
		Bullet_C3.m_VertexList[1].x = 4.4005f; Bullet_C3.m_VertexList[1].y = 4.4005f;
		Bullet_C3.m_VertexList[2].x = 4.4005f; Bullet_C3.m_VertexList[2].y = 4.4005f;
		Bullet_C3.m_VertexList[3].x = 4.4005f; Bullet_C3.m_VertexList[3].y = 4.4005f;
		Bullet_C3.m_VertexList[4].x = 4.4005f; Bullet_C3.m_VertexList[4].y = 4.4005f;
		Bullet_C3.m_VertexList[5].x = 4.4005f; Bullet_C3.m_VertexList[5].y = 4.4005f;
		Bullet_C3.m_VertexList[6].x = 4.4005f; Bullet_C3.m_VertexList[6].y = 4.4005f;

		Bullet_Ghost_2.m_VertexList[0].x = 6.1135f; Bullet_Ghost_2.m_VertexList[0].y = 6.1135f;
		Bullet_Ghost_2.m_VertexList[1].x = 6.1135f; Bullet_Ghost_2.m_VertexList[1].y = 6.1135f;
		Bullet_Ghost_2.m_VertexList[2].x = 6.1135f; Bullet_Ghost_2.m_VertexList[2].y = 6.1135f;
		Bullet_Ghost_2.m_VertexList[3].x = 6.1135f; Bullet_Ghost_2.m_VertexList[3].y = 6.1135f;
		Bullet_Ghost_2.m_VertexList[4].x = 6.1135f; Bullet_Ghost_2.m_VertexList[4].y = 6.1135f;
		Bullet_Ghost_2.m_VertexList[5].x = 6.1135f; Bullet_Ghost_2.m_VertexList[5].y = 6.1135f;
		Bullet_Ghost_2.m_VertexList[6].x = 6.1135f; Bullet_Ghost_2.m_VertexList[6].y = 6.1135f;


		memcpy(N_VertexList_C3, Bullet_C3.m_VertexList, sizeof(SimpleVertex) * 6);
		memcpy(N_VertexList_G2, Bullet_Ghost_2.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_C3.m_VertexList[iV].x; vertex.y = Bullet_C3.m_VertexList[iV].y;
			vertex.x -= Bullet_C3.m_vCenter.x;		 vertex.y -= Bullet_C3.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_C3[iV].x = vertex.x * C + vertex.y * S; N_VertexList_C3[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_C3[iV].x += Bullet_C3.m_vCenter.x;		 N_VertexList_C3[iV].y += Bullet_C3.m_vCenter.y;
		}

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_2.m_VertexList[iV].x; vertex.y = Bullet_Ghost_2.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_2.m_vCenter.x;		 vertex.y -= Bullet_Ghost_2.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G2[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G2[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G2[iV].x += Bullet_Ghost_2.m_vCenter.x; N_VertexList_G2[iV].y += Bullet_Ghost_2.m_vCenter.y;
		}


		g_pContext->UpdateSubresource(Bullet_C3.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_C3, 0, 0);
		g_pContext->UpdateSubresource(Bullet_Ghost_2.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G2, 0, 0);
	}

	if (TCollision::SphereInSphere(Bullet_C3.m_rtCollision, Bullet_Ghost_3.m_rtDetection))
	{

		Bullet_C3.m_VertexList[0].x = 4.922f; Bullet_C3.m_VertexList[0].y = 4.922f;
		Bullet_C3.m_VertexList[1].x = 4.922f; Bullet_C3.m_VertexList[1].y = 4.922f;
		Bullet_C3.m_VertexList[2].x = 4.922f; Bullet_C3.m_VertexList[2].y = 4.922f;
		Bullet_C3.m_VertexList[3].x = 4.922f; Bullet_C3.m_VertexList[3].y = 4.922f;
		Bullet_C3.m_VertexList[4].x = 4.922f; Bullet_C3.m_VertexList[4].y = 4.922f;
		Bullet_C3.m_VertexList[5].x = 4.922f; Bullet_C3.m_VertexList[5].y = 4.922f;
		Bullet_C3.m_VertexList[6].x = 4.922f; Bullet_C3.m_VertexList[6].y = 4.922f;

		Bullet_Ghost_3.m_VertexList[0].x = 4.0063f; Bullet_Ghost_3.m_VertexList[0].y =4.0063f;
		Bullet_Ghost_3.m_VertexList[1].x = 4.0063f; Bullet_Ghost_3.m_VertexList[1].y =4.0063f;
		Bullet_Ghost_3.m_VertexList[2].x = 4.0063f; Bullet_Ghost_3.m_VertexList[2].y =4.0063f;
		Bullet_Ghost_3.m_VertexList[3].x = 4.0063f; Bullet_Ghost_3.m_VertexList[3].y =4.0063f;
		Bullet_Ghost_3.m_VertexList[4].x = 4.0063f; Bullet_Ghost_3.m_VertexList[4].y =4.0063f;
		Bullet_Ghost_3.m_VertexList[5].x = 4.0063f; Bullet_Ghost_3.m_VertexList[5].y =4.0063f;
		Bullet_Ghost_3.m_VertexList[6].x = 4.0063f; Bullet_Ghost_3.m_VertexList[6].y =4.0063f;


		memcpy(N_VertexList_C3, Bullet_C3.m_VertexList, sizeof(SimpleVertex) * 6);
		memcpy(N_VertexList_G3, Bullet_Ghost_3.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_C3.m_VertexList[iV].x; vertex.y = Bullet_C3.m_VertexList[iV].y;
			vertex.x -= Bullet_C3.m_vCenter.x;		 vertex.y -= Bullet_C3.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_C3[iV].x = vertex.x * C + vertex.y * S; N_VertexList_C3[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_C3[iV].x += Bullet_C3.m_vCenter.x;		 N_VertexList_C3[iV].y += Bullet_C3.m_vCenter.y;
		}

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_3.m_VertexList[iV].x; vertex.y = Bullet_Ghost_3.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_3.m_vCenter.x;		 vertex.y -= Bullet_Ghost_3.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G3[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G3[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G3[iV].x += Bullet_Ghost_3.m_vCenter.x; N_VertexList_G3[iV].y += Bullet_Ghost_3.m_vCenter.y;
		}


		g_pContext->UpdateSubresource(Bullet_C3.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_C3, 0, 0);
		g_pContext->UpdateSubresource(Bullet_Ghost_3.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G3, 0, 0);

	}


	if (TCollision::SphereInSphere(Bullet_C3.m_rtCollision, Bullet_Ghost_4.m_rtDetection))
	{
		Bullet_C3.m_VertexList[0].x = 4.5009f; Bullet_C3.m_VertexList[0].y = 4.5009f;
		Bullet_C3.m_VertexList[1].x = 4.5009f; Bullet_C3.m_VertexList[1].y = 4.5009f;
		Bullet_C3.m_VertexList[2].x = 4.5009f; Bullet_C3.m_VertexList[2].y = 4.5009f;
		Bullet_C3.m_VertexList[3].x = 4.5009f; Bullet_C3.m_VertexList[3].y = 4.5009f;
		Bullet_C3.m_VertexList[4].x = 4.5009f; Bullet_C3.m_VertexList[4].y = 4.5009f;
		Bullet_C3.m_VertexList[5].x = 4.5009f; Bullet_C3.m_VertexList[5].y = 4.5009f;
		Bullet_C3.m_VertexList[6].x = 4.5009f; Bullet_C3.m_VertexList[6].y = 4.5009f;

		Bullet_Ghost_4.m_VertexList[0].x = 4.7112f; Bullet_Ghost_4.m_VertexList[0].y = 4.7112f;
		Bullet_Ghost_4.m_VertexList[1].x = 4.7112f; Bullet_Ghost_4.m_VertexList[1].y = 4.7112f;
		Bullet_Ghost_4.m_VertexList[2].x = 4.7112f; Bullet_Ghost_4.m_VertexList[2].y = 4.7112f;
		Bullet_Ghost_4.m_VertexList[3].x = 4.7112f; Bullet_Ghost_4.m_VertexList[3].y = 4.7112f;
		Bullet_Ghost_4.m_VertexList[4].x = 4.7112f; Bullet_Ghost_4.m_VertexList[4].y = 4.7112f;
		Bullet_Ghost_4.m_VertexList[5].x = 4.7112f; Bullet_Ghost_4.m_VertexList[5].y = 4.7112f;
		Bullet_Ghost_4.m_VertexList[6].x = 4.7112f; Bullet_Ghost_4.m_VertexList[6].y = 4.7112f;


		memcpy(N_VertexList_C3, Bullet_C3.m_VertexList, sizeof(SimpleVertex) * 6);
		memcpy(N_VertexList_G4, Bullet_Ghost_4.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_C3.m_VertexList[iV].x; vertex.y = Bullet_C3.m_VertexList[iV].y;
			vertex.x -= Bullet_C3.m_vCenter.x;		 vertex.y -= Bullet_C3.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_C3[iV].x = vertex.x * C + vertex.y * S; N_VertexList_C3[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_C3[iV].x += Bullet_C3.m_vCenter.x;		 N_VertexList_C3[iV].y += Bullet_C3.m_vCenter.y;
		}

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_4.m_VertexList[iV].x; vertex.y = Bullet_Ghost_4.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_4.m_vCenter.x;		 vertex.y -= Bullet_Ghost_4.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G4[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G4[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G4[iV].x += Bullet_Ghost_4.m_vCenter.x; N_VertexList_G4[iV].y += Bullet_Ghost_4.m_vCenter.y;
		}


		g_pContext->UpdateSubresource(Bullet_C3.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_C3, 0, 0);
		g_pContext->UpdateSubresource(Bullet_Ghost_4.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G4, 0, 0);
	}




	if (TCollision::SphereInSphere(Bullet_C4.m_rtCollision, Bullet_Ghost_1.m_rtCollision))
	{

		Bullet_C4.m_VertexList[0].x = 3.257f; Bullet_C4.m_VertexList[0].y = 3.257f;
		Bullet_C4.m_VertexList[1].x = 3.257f; Bullet_C4.m_VertexList[1].y = 3.257f;
		Bullet_C4.m_VertexList[2].x = 3.257f; Bullet_C4.m_VertexList[2].y = 3.257f;
		Bullet_C4.m_VertexList[3].x = 3.257f; Bullet_C4.m_VertexList[3].y = 3.257f;
		Bullet_C4.m_VertexList[4].x = 3.257f; Bullet_C4.m_VertexList[4].y = 3.257f;
		Bullet_C4.m_VertexList[5].x = 3.257f; Bullet_C4.m_VertexList[5].y = 3.257f;
		Bullet_C4.m_VertexList[6].x = 3.257f; Bullet_C4.m_VertexList[6].y = 3.257f;

		Bullet_Ghost_1.m_VertexList[0].x = 3.074f; Bullet_Ghost_1.m_VertexList[0].y = 3.074f;
		Bullet_Ghost_1.m_VertexList[1].x = 3.074f; Bullet_Ghost_1.m_VertexList[1].y = 3.074f;
		Bullet_Ghost_1.m_VertexList[2].x = 3.074f; Bullet_Ghost_1.m_VertexList[2].y = 3.074f;
		Bullet_Ghost_1.m_VertexList[3].x = 3.074f; Bullet_Ghost_1.m_VertexList[3].y = 3.074f;
		Bullet_Ghost_1.m_VertexList[4].x = 3.074f; Bullet_Ghost_1.m_VertexList[4].y = 3.074f;
		Bullet_Ghost_1.m_VertexList[5].x = 3.074f; Bullet_Ghost_1.m_VertexList[5].y = 3.074f;
		Bullet_Ghost_1.m_VertexList[6].x = 3.074f; Bullet_Ghost_1.m_VertexList[6].y = 3.074f;


		memcpy(N_VertexList_C4, Bullet_C4.m_VertexList, sizeof(SimpleVertex) * 6);
		memcpy(N_VertexList_G1, Bullet_Ghost_1.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_C4.m_VertexList[iV].x; vertex.y = Bullet_C4.m_VertexList[iV].y;
			vertex.x -= Bullet_C4.m_vCenter.x;		 vertex.y -= Bullet_C4.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_C4[iV].x = vertex.x * C + vertex.y * S; N_VertexList_C4[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_C4[iV].x += Bullet_C4.m_vCenter.x;		 N_VertexList_C4[iV].y += Bullet_C4.m_vCenter.y;
		}

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_1.m_VertexList[iV].x; vertex.y = Bullet_Ghost_1.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_1.m_vCenter.x;		 vertex.y -= Bullet_Ghost_1.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G1[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G1[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G1[iV].x += Bullet_Ghost_1.m_vCenter.x; N_VertexList_G1[iV].y += Bullet_Ghost_1.m_vCenter.y;
		}


		g_pContext->UpdateSubresource(Bullet_C4.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_C4, 0, 0);
		g_pContext->UpdateSubresource(Bullet_Ghost_1.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G1, 0, 0);
	}



	if (TCollision::SphereInSphere(Bullet_C4.m_rtCollision, Bullet_Ghost_2.m_rtDetection))
	{
		Bullet_C4.m_VertexList[0].x = 4.333f; Bullet_C4.m_VertexList[0].y = 4.333f;
		Bullet_C4.m_VertexList[1].x = 4.333f; Bullet_C4.m_VertexList[1].y = 4.333f;
		Bullet_C4.m_VertexList[2].x = 4.333f; Bullet_C4.m_VertexList[2].y = 4.333f;
		Bullet_C4.m_VertexList[3].x = 4.333f; Bullet_C4.m_VertexList[3].y = 4.333f;
		Bullet_C4.m_VertexList[4].x = 4.333f; Bullet_C4.m_VertexList[4].y = 4.333f;
		Bullet_C4.m_VertexList[5].x = 4.333f; Bullet_C4.m_VertexList[5].y = 4.333f;
		Bullet_C4.m_VertexList[6].x = 4.333f; Bullet_C4.m_VertexList[6].y = 4.333f;

		Bullet_Ghost_2.m_VertexList[0].x = 4.1012f; Bullet_Ghost_2.m_VertexList[0].y = 4.1012f;
		Bullet_Ghost_2.m_VertexList[1].x = 4.1012f; Bullet_Ghost_2.m_VertexList[1].y = 4.1012f;
		Bullet_Ghost_2.m_VertexList[2].x = 4.1012f; Bullet_Ghost_2.m_VertexList[2].y = 4.1012f;
		Bullet_Ghost_2.m_VertexList[3].x = 4.1012f; Bullet_Ghost_2.m_VertexList[3].y = 4.1012f;
		Bullet_Ghost_2.m_VertexList[4].x = 4.1012f; Bullet_Ghost_2.m_VertexList[4].y = 4.1012f;
		Bullet_Ghost_2.m_VertexList[5].x = 4.1012f; Bullet_Ghost_2.m_VertexList[5].y = 4.1012f;
		Bullet_Ghost_2.m_VertexList[6].x = 4.1012f; Bullet_Ghost_2.m_VertexList[6].y = 4.1012f;


		memcpy(N_VertexList_C4, Bullet_C4.m_VertexList, sizeof(SimpleVertex) * 6);
		memcpy(N_VertexList_G2, Bullet_Ghost_2.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_C4.m_VertexList[iV].x; vertex.y = Bullet_C4.m_VertexList[iV].y;
			vertex.x -= Bullet_C4.m_vCenter.x;		 vertex.y -= Bullet_C4.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_C4[iV].x = vertex.x * C + vertex.y * S; N_VertexList_C4[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_C4[iV].x += Bullet_C4.m_vCenter.x;		 N_VertexList_C4[iV].y += Bullet_C4.m_vCenter.y;
		}

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_2.m_VertexList[iV].x; vertex.y = Bullet_Ghost_2.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_2.m_vCenter.x;		 vertex.y -= Bullet_Ghost_2.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G2[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G2[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G2[iV].x += Bullet_Ghost_2.m_vCenter.x; N_VertexList_G2[iV].y += Bullet_Ghost_2.m_vCenter.y;
		}


		g_pContext->UpdateSubresource(Bullet_C4.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_C4, 0, 0);
		g_pContext->UpdateSubresource(Bullet_Ghost_2.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G2, 0, 0);
	}




	if (TCollision::SphereInSphere(Bullet_C4.m_rtCollision, Bullet_Ghost_3.m_rtDetection))
	{
		Bullet_C4.m_VertexList[0].x = 2.2021f; Bullet_C4.m_VertexList[0].y = 2.2021f;
		Bullet_C4.m_VertexList[1].x = 2.2021f; Bullet_C4.m_VertexList[1].y = 2.2021f;
		Bullet_C4.m_VertexList[2].x = 2.2021f; Bullet_C4.m_VertexList[2].y = 2.2021f;
		Bullet_C4.m_VertexList[3].x = 2.2021f; Bullet_C4.m_VertexList[3].y = 2.2021f;
		Bullet_C4.m_VertexList[4].x = 2.2021f; Bullet_C4.m_VertexList[4].y = 2.2021f;
		Bullet_C4.m_VertexList[5].x = 2.2021f; Bullet_C4.m_VertexList[5].y = 2.2021f;
		Bullet_C4.m_VertexList[6].x = 2.2021f; Bullet_C4.m_VertexList[6].y = 2.2021f;

		Bullet_Ghost_3.m_VertexList[0].x = 2.843f; Bullet_Ghost_3.m_VertexList[0].y = 2.843f;
		Bullet_Ghost_3.m_VertexList[1].x = 2.843f; Bullet_Ghost_3.m_VertexList[1].y = 2.843f;
		Bullet_Ghost_3.m_VertexList[2].x = 2.843f; Bullet_Ghost_3.m_VertexList[2].y = 2.843f;
		Bullet_Ghost_3.m_VertexList[3].x = 2.843f; Bullet_Ghost_3.m_VertexList[3].y = 2.843f;
		Bullet_Ghost_3.m_VertexList[4].x = 2.843f; Bullet_Ghost_3.m_VertexList[4].y = 2.843f;
		Bullet_Ghost_3.m_VertexList[5].x = 2.843f; Bullet_Ghost_3.m_VertexList[5].y = 2.843f;
		Bullet_Ghost_3.m_VertexList[6].x = 2.843f; Bullet_Ghost_3.m_VertexList[6].y = 2.843f;


		memcpy(N_VertexList_C4, Bullet_C4.m_VertexList, sizeof(SimpleVertex) * 6);
		memcpy(N_VertexList_G3, Bullet_Ghost_3.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_C4.m_VertexList[iV].x; vertex.y = Bullet_C4.m_VertexList[iV].y;
			vertex.x -= Bullet_C4.m_vCenter.x;		 vertex.y -= Bullet_C4.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_C4[iV].x = vertex.x * C + vertex.y * S; N_VertexList_C4[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_C4[iV].x += Bullet_C4.m_vCenter.x;		 N_VertexList_C4[iV].y += Bullet_C4.m_vCenter.y;
		}

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_3.m_VertexList[iV].x; vertex.y = Bullet_Ghost_3.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_3.m_vCenter.x;		 vertex.y -= Bullet_Ghost_3.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G3[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G3[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G3[iV].x += Bullet_Ghost_3.m_vCenter.x; N_VertexList_G3[iV].y += Bullet_Ghost_3.m_vCenter.y;
		}


		g_pContext->UpdateSubresource(Bullet_C4.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_C4, 0, 0);
		g_pContext->UpdateSubresource(Bullet_Ghost_3.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G3, 0, 0);
	}




	if (TCollision::SphereInSphere(Bullet_C4.m_rtCollision, Bullet_Ghost_4.m_rtDetection))
	{
		Bullet_C4.m_VertexList[0].x = 3.0785f; Bullet_C4.m_VertexList[0].y = 3.0785f;
		Bullet_C4.m_VertexList[1].x = 3.0785f; Bullet_C4.m_VertexList[1].y = 3.0785f;
		Bullet_C4.m_VertexList[2].x = 3.0785f; Bullet_C4.m_VertexList[2].y = 3.0785f;
		Bullet_C4.m_VertexList[3].x = 3.0785f; Bullet_C4.m_VertexList[3].y = 3.0785f;
		Bullet_C4.m_VertexList[4].x = 3.0785f; Bullet_C4.m_VertexList[4].y = 3.0785f;
		Bullet_C4.m_VertexList[5].x = 3.0785f; Bullet_C4.m_VertexList[5].y = 3.0785f;
		Bullet_C4.m_VertexList[6].x = 3.0785f; Bullet_C4.m_VertexList[6].y = 3.0785f;

		Bullet_Ghost_4.m_VertexList[0].x = 4.055f; Bullet_Ghost_4.m_VertexList[0].y = 4.55f;
		Bullet_Ghost_4.m_VertexList[1].x = 4.055f; Bullet_Ghost_4.m_VertexList[1].y = 4.55f;
		Bullet_Ghost_4.m_VertexList[2].x = 4.055f; Bullet_Ghost_4.m_VertexList[2].y = 4.55f;
		Bullet_Ghost_4.m_VertexList[3].x = 4.055f; Bullet_Ghost_4.m_VertexList[3].y = 4.55f;
		Bullet_Ghost_4.m_VertexList[4].x = 4.055f; Bullet_Ghost_4.m_VertexList[4].y = 4.55f;
		Bullet_Ghost_4.m_VertexList[5].x = 4.055f; Bullet_Ghost_4.m_VertexList[5].y = 4.55f;
		Bullet_Ghost_4.m_VertexList[6].x = 4.055f; Bullet_Ghost_4.m_VertexList[6].y = 4.55f;


		memcpy(N_VertexList_C4, Bullet_C4.m_VertexList, sizeof(SimpleVertex) * 6);
		memcpy(N_VertexList_G4, Bullet_Ghost_4.m_VertexList, sizeof(SimpleVertex) * 6);

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_C4.m_VertexList[iV].x; vertex.y = Bullet_C4.m_VertexList[iV].y;
			vertex.x -= Bullet_C4.m_vCenter.x;		 vertex.y -= Bullet_C4.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_C4[iV].x = vertex.x * C + vertex.y * S; N_VertexList_C4[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_C4[iV].x += Bullet_C4.m_vCenter.x;		 N_VertexList_C4[iV].y += Bullet_C4.m_vCenter.y;
		}

		for (int iV = 0; iV < 6; iV++)
		{
			D3DVECTOR vertex;
			vertex.x = Bullet_Ghost_4.m_VertexList[iV].x; vertex.y = Bullet_Ghost_4.m_VertexList[iV].y;
			vertex.x -= Bullet_Ghost_4.m_vCenter.x;		 vertex.y -= Bullet_Ghost_4.m_vCenter.y;
			float S = sinf(fAngle);	float C = cosf(fAngle);
			N_VertexList_G4[iV].x = vertex.x * C + vertex.y * S; N_VertexList_G4[iV].y = vertex.x * -S + vertex.y * C;
			N_VertexList_G4[iV].x += Bullet_Ghost_4.m_vCenter.x; N_VertexList_G4[iV].y += Bullet_Ghost_4.m_vCenter.y;
		}


		g_pContext->UpdateSubresource(Bullet_C4.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_C4, 0, 0);
		g_pContext->UpdateSubresource(Bullet_Ghost_4.PipeLineSetup.m_pVertextBuffer, 0, NULL, N_VertexList_G4, 0, 0);
	}



}



class TSceneEnd : public TScene
{

public:
	Background			Ending_Background_success;
	Background			Ending_Background_failure;
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


	Ending_Background_success.in_Texture_SetData_factors(0, 0, 900, 500, 900, 500);
	Ending_Background_success.m_for_update_Rects.x = g_rtClient.right;	Ending_Background_success.m_for_update_Rects.y = g_rtClient.bottom;
	Ending_Background_success.Window_SetData_factors(900, 0, Ending_Background_success.m_for_update_Rects.x, Ending_Background_success.m_for_update_Rects.y);
	Ending_Background_success.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/ending_1.jpg");


	Ending_Background_failure.in_Texture_SetData_factors(0, 0, 900, 500, 900, 500);
	Ending_Background_failure.m_for_update_Rects.x = g_rtClient.right;	Ending_Background_failure.m_for_update_Rects.y = g_rtClient.bottom;
	Ending_Background_failure.Window_SetData_factors(900, 0, Ending_Background_failure.m_for_update_Rects.x, Ending_Background_failure.m_for_update_Rects.y);
	Ending_Background_failure.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/Treasure_Island.bmp");


	return true;
};
bool	TSceneEnd::Frame()
{

	if (end_decision ==1)
	{
		Ending_Background_success.in_Texture_SetData_factors(0, 0, 900, 500, 900, 500);
		Ending_Background_success.m_for_update_Rects.x = g_rtClient.right;	Ending_Background_success.m_for_update_Rects.y = g_rtClient.bottom;
		Ending_Background_success.Window_SetData_factors(0, 0, Ending_Background_success.m_for_update_Rects.x, Ending_Background_success.m_for_update_Rects.y);
		Ending_Background_success.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/ending_1.jpg");
	}

	if (end_decision ==2)
	{
		Ending_Background_failure.in_Texture_SetData_factors(0, 0, 900, 500, 900, 500);
		Ending_Background_failure.m_for_update_Rects.x = g_rtClient.right;	Ending_Background_failure.m_for_update_Rects.y = g_rtClient.bottom;
		Ending_Background_failure.Window_SetData_factors(0, 0, Ending_Background_failure.m_for_update_Rects.x, Ending_Background_failure.m_for_update_Rects.y);
		Ending_Background_failure.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/ending_2.jpg");
	}



	return true;
};

bool	TSceneEnd::Render()
{
	Ending_Background_success.Render(g_pContext);
	Ending_Background_failure.Render(g_pContext);

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


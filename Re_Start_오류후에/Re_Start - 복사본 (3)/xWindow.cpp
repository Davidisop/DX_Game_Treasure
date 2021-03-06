#pragma once
#define DIRECTINPUT_VERSION 0x0800

#include <windows.h>
#include <assert.h>
#include <tchar.h>

#include <iostream>
#include <map>
#include <string>
#include <list>
#include <vector>
#include <d3dx11.h>
#include <dxgi.h>
#include <dinput.h>

#include "D3Dcompiler.h"		//D3DCOMPILE_DEBUG
#include <math.h>
using namespace std;

//프로젝트 속성에서 추가 종속성에 넣을걸 코드로 넣을수 있다.
//#pragma comment(lib, "xCoreLib.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment( lib, "dinput8.lib")
#pragma comment( lib, "dxguid.lib")
#pragma comment( lib, "d3dx11.lib")

#pragma warning (disable : 4005)

typedef std::basic_string <char>	C_STR;	//multi-byte
typedef std::basic_string <wchar_t>	W_STR;	//unicode byte
typedef std::basic_string <TCHAR>	T_STR;	//프로젝트속성이 멀티바이트이면 멀티바이트, 유니코드이면 유니코드로 바뀜.

											//string a;		//multi-byte
											//wstring b;	//unicode byte

#define GAMESTART int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPWSTR lpCmdLine, int nCmdShow) {
											//
											////L#s ==> L"" s는 문자열이므로 #을 붙인다. 유니코드라서 L을 붙인다.
											//#define GAMERUN(s) xWindow win; win.SetWindow(hInstance, L#s, 600, 800); win.Run();
											//
#define GAME_END }


											//L#s ==> L"" s는 문자열이므로 #을 붙인다. 유니코드라서 L을 붙인다.

#define GAMERUN(s, w, h) int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR lpCmdLine, int nCmdShow) { Sample win; win.SetWindow(hInst, L#s, w, h); win.Run(); }


extern HWND			g_hWnd;
extern HINSTANCE	g_hInstance;
extern float		g_fSecPerFrame;
extern RECT			g_rtClient;
extern float		g_fGameTimer;
extern float		g_fSecPerFrame;
extern HDC			g_hOffScreenDC;
extern ID3D11Device*g_pd3dDevice;
extern ID3D11DeviceContext*	g_pContext;


typedef struct _D3DVECTOR
{
	float x;
	float y;
	float z;
} D3DVECTOR;


struct tPoint
{
	float x, y;
};

struct TGameInput
{
	BOOL bUp;
	BOOL bDown;
	BOOL bLeft;
	BOOL bRight;
	BOOL bAttack;
	BOOL bJump;
};


extern TGameInput g_Input;

typedef std::vector<RECT>  Picture_RECT;
typedef std::vector<Picture_RECT> Select_Animation_Vector;




//추가 포함 디렉토리에 해당파일을 또 추가하면
//../../include; 경로를 추가해서 또 include하면
//컴파일러 오류 C2953
//'TSingleton': 클래스 템플릿이 이미 정의되었습니다. 에러 발생.
// 라이브러리는 추가포함 디렉토리를 추가하지 않는다.
template<class T> class TSingleton
{
public:
	static T& GetInstance()
	{
		static T theSingleInstance;
		return theSingleInstance;
	}
};

#ifndef V_RETURN
#define V_RETURN(x) { hr = (x); if( FAILED(hr) ) {return hr;} }
#endif

#ifndef V
#define V(x) { hr = (x);}
#endif                                                                                                                                                                                                                                                                                                 ;
	//wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.hIconSm = LoadIcon(NULL, IDI_HAND);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;



	if (RegisterClassEx(&wc) == FALSE)
	{
		assert(RegisterClassEx(&wc) != FALSE);
		return false;
	}

	//클라이언트 영역 수정(클라이언트 영역을 정확하게, (800, 600)으로 수정한다)
	RECT rt{ 0,0, iWidth, iHeight };
	AdjustWindowRect(&rt, m_dwStyle, FALSE);

	//윈도우 생성(등록된 클래스를 사용해서)
	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW,
		L"MyWindow", pTitleName, m_dwStyle,
		0, 0, rt.right - rt.left, rt.bottom - rt.top, NULL, NULL, m_hInstance, NULL);

	if (m_hWnd == NULL)
	{
		assert(m_hWnd != NULL);
		return false;
	}

	g_hWnd = m_hWnd;

	GetWindowRect(m_hWnd, &m_rtWindow);
	GetClientRect(m_hWnd, &m_rtClient);
	g_rtClient = m_rtClient;

	CenterWindow();

	ShowWindow(m_hWnd, SW_SHOW);
	return true;
}
void xWindow::Set(DWORD dwStyle)
{
	m_dwStyle = dwStyle;
}

void xWindow::CenterWindow()
{
	assert(m_hWnd != NULL);

	int iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	int iScreenHeigth = GetSystemMetrics(SM_CYFULLSCREEN);

	int x = (iScreenWidth - (m_rtWindow.right - m_rtWindow.left)) / 2;
	int y = (iScreenHeigth - (m_rtWindow.bottom - m_rtWindow.top)) / 2;

	TCHAR	csBuffer[256];
	_stprintf_s(csBuffer, L"m_hWnd = %p, iScreenWidth  = %d, iScreenHeigth = %d, x = %d, y = %d, windowWidth = %d, windowHeight = %d\n",
		m_hWnd, iScreenWidth, iScreenHeigth, x, y, (m_rtWindow.right - m_rtWindow.left), (m_rtWindow.bottom - m_rtWindow.top));

	OutputDebugString(csBuffer);
	MoveWindow(m_hWnd, x, y, m_rtWindow.right, m_rtWindow.bottom, true);
}
bool xWindow::Run()
{
	if (!GameInit())
		return false;

	//GetMessage(&msg, NULL, 0, 0)
	//메세지큐에서 메세지가 1개이상 있을 경우 1개를 가져옴.
	//PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)
	//메세지큐에서 메세지 있으면 메세지 반환, 없으면 false를 반환.
	MSG msg;		// WM_QUIT
	ZeroMemory(&msg, sizeof(MSG));

	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
			{
				break;
			}
			MsgEvent(msg);
		}
		else
		{
			GameRun();
			Sleep(1);
		}
	}

	return GameRelease();
}

bool xWindow::GameInit()
{
	TDevice::Init();
	return true;
}

bool xWindow::GameRun()
{
	return true;
}

bool xWindow::GameRelease()
{
	return true;
}
xWindow::xWindow()
{
	g_pWindow = this;
	m_dwStyle = WS_OVERLAPPEDWINDOW;
}


xWindow::~xWindow()
{
}


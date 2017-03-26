#include "stdafx.h"

float CPlatForm::mouse_x = 0;
float CPlatForm::mouse_y = 0;
bool CPlatForm::lbutton_press = false;
long CPlatForm::PlayTime = 0;
HWND CPlatForm::avi_hw = NULL;
CPlatForm *CPlatForm::Instance = NULL;

void CPlatForm::initD3D()
{
	pD3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;//FALSE为全屏
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;//窗口刷新速度
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	// Create the D3DDevice
	pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pd3dDevice);
	//D3DXCreateSprite(pd3dDevice, &pSprite);//将精灵指针与D3D设备关联

	//AddFontResource(L"font/CHICSA__.TTF");
	AddFontResource(L"font/华康采风体.TTF");
	AddFontResource(L"font/CHICSA__.TTF");
	AddFontResource(L"font/简行楷.ttf");

	D3DXCreateFont(pd3dDevice, 20, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"DFTsaiW3-B5", &pFont);
	

	D3DXCreateFont(pd3dDevice, 40, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"迷你简行楷", &pFont_big);


	D3DXCreateLine(pd3dDevice, &g_pLine);//设置线条参数
	g_pLine->SetWidth(3.f);
	g_pLine->SetAntialias(TRUE);

	

}

LRESULT CPlatForm::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	switch (message)
	{
	case WM_CREATE:
		avi_hw = MCIWndCreate(hWnd, 0, MCIWNDF_SHOWALL | MCIWNDF_NOMENU | MCIWNDF_NOPLAYBAR | MCIWNDF_NOTIFYMODE, NULL);
		SetWindowPos(avi_hw, HWND_TOP, 0, -1, 0, 0, SWP_SHOWWINDOW);
		MCIWndOpen(avi_hw, L"other/127076386.h264_1.wmv", 0);
		PlayTime = MCIWndGetLength(avi_hw)/1000;
		MCIWndPlay(avi_hw);
		break;
	case WM_MOUSEMOVE:
		mouse_x = float(LOWORD(lParam));
		mouse_y = float(HIWORD(lParam));
		break;
	case WM_LBUTTONDOWN:
		lbutton_press = true;
		break;;

	case WM_LBUTTONUP:
		lbutton_press = false;
		break;;
	case WM_DESTROY:
		//CPlayer::Get_Instance()->~CPlayer();
		PostQuitMessage(0);
		break;
		//鼠标右键DEBUG开关
	case WM_RBUTTONDOWN:
		
		break;
	case IDM_EXIT:
		//DestroyWindow(hWnd);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void CPlatForm::run()
{
	HACCEL hAccelTable = LoadAccelerators(NULL, MAKEINTRESOURCE(IDC_MY));

	LARGE_INTEGER nFreq;
	QueryPerformanceFrequency(&nFreq);
	LARGE_INTEGER nAnimationInterval;
	nAnimationInterval.QuadPart = (LONGLONG)(1.0 / FPS * nFreq.QuadPart);

	LARGE_INTEGER nLast;
	LARGE_INTEGER nNow;
	QueryPerformanceCounter(&nLast);

	MSG msg;

	memset(&msg, 0, sizeof(MSG));
	while (msg.message != WM_QUIT)
	{
		if (!PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			QueryPerformanceCounter(&nNow);

			if (nNow.QuadPart - nLast.QuadPart > nAnimationInterval.QuadPart)
			{
				nLast.QuadPart = nNow.QuadPart;

				play_temp_time++;
				if (PlayTime - play_temp_time / FPS < 0 && !avi_end)
				{
					MCIWndClose(avi_hw);
					DestroyWindow(avi_hw);
					avi_end = true;
				}
				if (avi_end)
				{
					Render();
				}

			}
			else
			{
				Sleep(0);
			}
			continue;
		}

		if (!hAccelTable || !TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

void CPlatForm::displayFPS()
{
	float fps = getFPS();
	char temp[30];
	sprintf_s(temp, "FPS  %.2f", fps);
	RECT rc = { 20,200,960,250 };
	pFont->DrawTextA(NULL, temp, -1, &rc, DT_LEFT | DT_TOP, D3DCOLOR_RGBA(255, 0, 255, 255));

	/*static float temp_time = 0;
	temp_time++;
	char game_time[30];
	sprintf_s(game_time, "Time %.2f", temp_time/ FPS);
	RECT rc1 = { 800,30,960,80 };
	pFont->DrawTextA(NULL, game_time, -1, &rc1, DT_LEFT | DT_TOP, D3DCOLOR_RGBA(255, 0, 255, 255));*/
}

void CPlatForm::Render()
{
	// 清空后台缓冲区
	pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	if (SUCCEEDED(pd3dDevice->BeginScene())) //开始在后台缓冲区绘制图形
	{
	
		
		CObj_management::Getinstance()->update();
		CGame::Get_instance()->update();
	
		

		//displayFPS();//显示FPS
		pd3dDevice->EndScene(); //结束在后台缓冲区渲染图形
	}
	//将在后台缓冲区绘制的图形提交到前台缓冲区显示
	pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

float CPlatForm::updateTime()
{
	static float previousTime = timeGetTime() / 1000.0f;
	float currentTime = timeGetTime() / 1000.0f;
	float elapsedTime = currentTime - previousTime;
	previousTime = currentTime;
	return elapsedTime;
}

float CPlatForm::getFPS()
{
	static float timeNow = GetTickCount() / 1000.0f;
	static DWORD dwRenderedFrame = 0;

	float tFrame = GetTickCount() / 1000.0f - timeNow;
	timeNow += tFrame;

	static float fps = 0;
	if (fmodf(timeNow, 1) < tFrame)
	{
		fps = dwRenderedFrame + fmodf(timeNow, 1) / tFrame; //计算FPS
		dwRenderedFrame = 0;
	}
	dwRenderedFrame++;

	return fps;
}

CPlatForm * CPlatForm::Getinstance()
{
	if (!Instance)
		Instance = new CPlatForm;
	return Instance;
}

CPlatForm::CPlatForm()
{
	LoadStringW(NULL, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(NULL, IDC_MY, szWindowClass, MAX_LOADSTRING);//IDC_MY
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= 0;
	wcex.hIcon			= LoadIcon(0, MAKEINTRESOURCE(IDI_MY));
	wcex.hCursor		= LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName	= NULL;//MAKEINTRESOURCEW(IDC_MY);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassExW(&wcex);

	int nX = GetSystemMetrics(SM_CXFRAME) * 4;
	int nY = GetSystemMetrics(SM_CYFRAME) * 4 + GetSystemMetrics(SM_CYCAPTION);

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, WIN_X + nX, WIN_Y + nY, nullptr, nullptr, 0, nullptr);

	ShowWindow(hWnd, true);
	UpdateWindow(hWnd);
	
	initD3D();

	game_Pause = false;
}

CPlatForm::~CPlatForm()
{
	//if (pSprite)
		//pSprite->Release();
	if (pFont)
		pFont->Release();
	if (pd3dDevice)
		pd3dDevice->Release();
	if (pD3d)
		pD3d->Release();
	

}

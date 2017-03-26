#include "stdafx.h"



void CHP_rect::Release()
{
	g_pLine_M->Release();
	g_pLine_S->Release();
}

void CHP_rect::set_hp(float _hp, float _x, float _y)
{
	hp = _hp;
	x = _x;
	y = _y;

	if (x < 29)
		return;

	
	if (hp >= 0.f)
	{
		if (buffer_hp > hp)
		{
			buffer_hp -= 0.002f;
		}
		D3DXVECTOR2 HPRECT3[5];
		HPRECT3[0] = D3DXVECTOR2(x - 29, y - 128);
		HPRECT3[1] = D3DXVECTOR2(x - 29 + 29 * 2 * buffer_hp, y - 128);
		HPRECT3[2] = D3DXVECTOR2(x - 29 + 29 * 2 * buffer_hp, y - 127);
		HPRECT3[3] = D3DXVECTOR2(x - 28, y - 127);
		HPRECT3[4] = D3DXVECTOR2(x - 28, y - 128);
		g_pLine_M->Draw(HPRECT3, 5, D3DCOLOR_XRGB(255, 255, 100));


		D3DXVECTOR2 HPRECT2[5];
		HPRECT2[0] = D3DXVECTOR2(x - 29, y - 128);
		HPRECT2[1] = D3DXVECTOR2(x - 29 + 29 * 2 * hp, y - 128);
		HPRECT2[2] = D3DXVECTOR2(x - 29 + 29 * 2 * hp, y - 127);
		HPRECT2[3] = D3DXVECTOR2(x - 28, y - 127);
		HPRECT2[4] = D3DXVECTOR2(x - 28, y - 128);
		g_pLine_M->Draw(HPRECT2, 5, D3DCOLOR_XRGB(R, G, B));
	}

	


	//血条空框RECT
	D3DXVECTOR2 HPRECT[5];
	HPRECT[0] = D3DXVECTOR2(x - 30, y - 130);
	HPRECT[1] = D3DXVECTOR2(x + 30, y - 130);
	HPRECT[2] = D3DXVECTOR2(x + 30, y - 125);
	HPRECT[3] = D3DXVECTOR2(x - 30, y - 125);
	HPRECT[4] = D3DXVECTOR2(x - 30, y - 130);
	g_pLine_S->Draw(HPRECT, 5, D3DCOLOR_XRGB(0, 0, 0));
}

CHP_rect::CHP_rect()
{
	D3DXCreateLine(CPlatForm::Getinstance()->Get_pd3dDevice(), &g_pLine_M);//设置线条参数
	g_pLine_M->SetWidth(3.f);
	g_pLine_M->SetAntialias(true);

	D3DXCreateLine(CPlatForm::Getinstance()->Get_pd3dDevice(), &g_pLine_S);//设置线条参数
	g_pLine_S->SetWidth(2.f);
	g_pLine_S->SetAntialias(true);
	hp = 1.f;
	buffer_hp = hp;
}


CHP_rect::~CHP_rect()
{
}

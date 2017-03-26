#include "stdafx.h"



void CUI_img::show()
{
	color = D3DXCOLOR(R, G, B, A);

	pSprite->Begin(D3DXSPRITE_ALPHABLEND); //批处理
	pSprite->Draw(
		pD3DTexture, 				// 一个精灵纹理的实例
		&img_rect,						// 我们将要渲染的图片部分所在的矩形区域, NULL表示我们将要渲染整副图片
		&anchor, 	//指定精灵的锚点, NULL表示点(0,0,0)为精灵的中心,当前图片上的坐标，图片的宽度和长度/2
		NULL,//&Show_Pos, 	//在窗口显示坐标,如果使用矩阵，这个位置为原点, NULL表示精灵的位置是点(0,0,0)
		D3DXCOLOR(R, G, B, A)); 	//图片的颜色和alpha值被此值修正

	pSprite->End(); ////通知精灵设备我们的图片渲染完成了,
}

void CUI_img::update()
{
	/*static int time = 0;
	time++;
	if (time == 200)
	{
		set_del(true);
	}*/
}

CUI_img::CUI_img(LPCWSTR img)
	:CPicture(img)
{
	anchor = D3DXVECTOR3(0, 0, 0);
	CObj_management::Getinstance()->add(this);
}


CUI_img::~CUI_img()
{
	
}

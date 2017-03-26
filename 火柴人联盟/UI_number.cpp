#include "stdafx.h"



void CUI_number::update()
{
}

void CUI_number::show()
{
	int temp = 0;
	int num = score;
	while (num > 0)
	{
		int j = num;
		num /= 10;
		int one = j - num * 10;
		number[temp++] = one;
	}

	//记录原始坐标
	D3DXVECTOR2 lastpos = D3DXVECTOR2(x, y);

	for (int a = temp - 1; a >= 0; a--)
	{

		RECT show_rect = { number[a] * one_x,0,(number[a] + 1) * one_x,one_y };

		x += one_x;
		set_pos(x, y);

		pSprite->Begin(D3DXSPRITE_ALPHABLEND); //批处理
		pSprite->Draw(
			pD3DTexture, 				// 一个精灵纹理的实例
			&show_rect,//&IMG_RECT,						// 我们将要渲染的图片部分所在的矩形区域, NULL表示我们将要渲染整副图片
			NULL, 	//指定精灵的锚点, NULL表示点(0,0,0)为精灵的中心,当前图片上的坐标，图片的宽度和长度/2
			NULL,//&Show_Pos, 	//在窗口显示坐标,如果使用矩阵，这个位置为原点, NULL表示精灵的位置是点(0,0,0)
			color); 	//图片的颜色和alpha值被此值修正

		pSprite->End(); ////通知精灵设备我们的图片渲染完成了,

	}
	//还原坐标
	x = lastpos.x;
	y = lastpos.y;
}

//void CUI_number::Release()
//{
//}

CUI_number::CUI_number(LPCTSTR img, float _x, float _y)
	:CPicture(img)
{
	id = ui_number;
	sort = -3;
	x = _x;
	y = _y;
	one_x = get_img_x() / 10;
	one_y = get_img_y();

	CObj_management::Getinstance()->add(this);
}


CUI_number::~CUI_number()
{
}

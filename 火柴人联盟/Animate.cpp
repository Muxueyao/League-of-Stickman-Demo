#include "stdafx.h"



void CAnimate::update()
{
	
	int SHOW_X = start_num % x_num;
	int SHOW_Y = (float)start_num / x_num + 0.9;

	if (SHOW_X == 0)
		SHOW_X = x_num;

	img_rect = { long(SHOW_X - 1)*one_x,long(SHOW_Y - 1)*one_y,
		(long)SHOW_X*one_x,(long)SHOW_Y*one_y };

	S_TIME--;
	if (S_TIME <= 0)
	{
		start_num++;
		S_TIME = Speed_Time;
	}
	if (start_num > end_num)
	{
		//set_del(true);
		start_num = _start;
		is_end = true;
	}
	else
	{
		is_end = false;
	}
}

void CAnimate::show()
{
	pSprite->Begin(D3DXSPRITE_ALPHABLEND); //批处理
	pSprite->Draw(
		pD3DTexture, 				// 一个精灵纹理的实例
		&img_rect,						// 我们将要渲染的图片部分所在的矩形区域, NULL表示我们将要渲染整副图片
		&anchor, 	//指定精灵的锚点, NULL表示点(0,0,0)为精灵的中心,当前图片上的坐标，图片的宽度和长度/2
		NULL,//&Show_Pos, 	//在窗口显示坐标,如果使用矩阵，这个位置为原点, NULL表示精灵的位置是点(0,0,0)
		D3DXCOLOR(R,G,B,A)); 	//图片的颜色和alpha值被此值修正

	pSprite->End(); ////通知精灵设备我们的图片渲染完成了,
}

CAnimate::CAnimate(LPCWSTR imgname, int all_x, int all_y, int start_num, int end_num)
	:CPicture(imgname)
{
	img_rect = { 0,0,0,0 };
	dir = false;
	all_num = all_x*all_y;
	x_num = all_x;
	y_num = all_y;
	this->start_num = start_num;
	this->end_num = end_num;
	_start = start_num;

	one_x = img_width / all_x;
	one_y = img_height / all_y;

	Speed_Time = 20;//每一桢动画间隔时间
	S_TIME = Speed_Time;
	loop = false;
	is_end = false;
	anchor = D3DXVECTOR3(one_x / 2, one_y / 2, 0);

	CObj_management::Getinstance()->add(this);
}

CAnimate::~CAnimate()
{
}

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
	pSprite->Begin(D3DXSPRITE_ALPHABLEND); //������
	pSprite->Draw(
		pD3DTexture, 				// һ�����������ʵ��
		&img_rect,						// ���ǽ�Ҫ��Ⱦ��ͼƬ�������ڵľ�������, NULL��ʾ���ǽ�Ҫ��Ⱦ����ͼƬ
		&anchor, 	//ָ�������ê��, NULL��ʾ��(0,0,0)Ϊ���������,��ǰͼƬ�ϵ����꣬ͼƬ�Ŀ�Ⱥͳ���/2
		NULL,//&Show_Pos, 	//�ڴ�����ʾ����,���ʹ�þ������λ��Ϊԭ��, NULL��ʾ�����λ���ǵ�(0,0,0)
		D3DXCOLOR(R,G,B,A)); 	//ͼƬ����ɫ��alphaֵ����ֵ����

	pSprite->End(); ////֪ͨ�����豸���ǵ�ͼƬ��Ⱦ�����,
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

	Speed_Time = 20;//ÿһ�嶯�����ʱ��
	S_TIME = Speed_Time;
	loop = false;
	is_end = false;
	anchor = D3DXVECTOR3(one_x / 2, one_y / 2, 0);

	CObj_management::Getinstance()->add(this);
}

CAnimate::~CAnimate()
{
}

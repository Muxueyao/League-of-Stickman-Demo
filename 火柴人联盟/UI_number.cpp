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

	//��¼ԭʼ����
	D3DXVECTOR2 lastpos = D3DXVECTOR2(x, y);

	for (int a = temp - 1; a >= 0; a--)
	{

		RECT show_rect = { number[a] * one_x,0,(number[a] + 1) * one_x,one_y };

		x += one_x;
		set_pos(x, y);

		pSprite->Begin(D3DXSPRITE_ALPHABLEND); //������
		pSprite->Draw(
			pD3DTexture, 				// һ�����������ʵ��
			&show_rect,//&IMG_RECT,						// ���ǽ�Ҫ��Ⱦ��ͼƬ�������ڵľ�������, NULL��ʾ���ǽ�Ҫ��Ⱦ����ͼƬ
			NULL, 	//ָ�������ê��, NULL��ʾ��(0,0,0)Ϊ���������,��ǰͼƬ�ϵ����꣬ͼƬ�Ŀ�Ⱥͳ���/2
			NULL,//&Show_Pos, 	//�ڴ�����ʾ����,���ʹ�þ������λ��Ϊԭ��, NULL��ʾ�����λ���ǵ�(0,0,0)
			color); 	//ͼƬ����ɫ��alphaֵ����ֵ����

		pSprite->End(); ////֪ͨ�����豸���ǵ�ͼƬ��Ⱦ�����,

	}
	//��ԭ����
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

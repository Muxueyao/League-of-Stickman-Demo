#include "stdafx.h"



void CUI_img::show()
{
	color = D3DXCOLOR(R, G, B, A);

	pSprite->Begin(D3DXSPRITE_ALPHABLEND); //������
	pSprite->Draw(
		pD3DTexture, 				// һ�����������ʵ��
		&img_rect,						// ���ǽ�Ҫ��Ⱦ��ͼƬ�������ڵľ�������, NULL��ʾ���ǽ�Ҫ��Ⱦ����ͼƬ
		&anchor, 	//ָ�������ê��, NULL��ʾ��(0,0,0)Ϊ���������,��ǰͼƬ�ϵ����꣬ͼƬ�Ŀ�Ⱥͳ���/2
		NULL,//&Show_Pos, 	//�ڴ�����ʾ����,���ʹ�þ������λ��Ϊԭ��, NULL��ʾ�����λ���ǵ�(0,0,0)
		D3DXCOLOR(R, G, B, A)); 	//ͼƬ����ɫ��alphaֵ����ֵ����

	pSprite->End(); ////֪ͨ�����豸���ǵ�ͼƬ��Ⱦ�����,
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

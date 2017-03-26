#include "stdafx.h"



void CPicture::set_matrix()
{
	D3DXMatrixScaling(&scale_matrix, scale.x, scale.y, 1);
	D3DXMatrixRotationZ(&angle_matrix, angle);//��ת
	D3DXMatrixTranslation(&pos_matrix, x, y, 0);//ƽ��

	matrix = scale_matrix*angle_matrix*pos_matrix;

	if (dir)
	{
		matrix._11 *= 1;
	}
	else
	{
		matrix._11 *= -1;
	}
	
	pSprite->SetTransform(&matrix);//���任����д�뾫��
}

void CPicture::Release()
{
	if (pD3DTexture)
		pD3DTexture->Release();
	if (pSprite)
		pSprite->Release();
}

void CPicture::set_pos(float x, float y)
{
	this->x = x;
	this->y = y;
	set_matrix();
}

void CPicture::set_angle(float angle)
{
	this->angle = angle;
	set_matrix();
}

void CPicture::set_scale(float _scale)
{
	scale.x = _scale;
	scale.y = _scale;
	set_matrix();
}

CPicture::CPicture(LPCWSTR imgname)
{

	D3DXCreateSprite(CPlatForm::Getinstance()->Get_pd3dDevice(), &pSprite);//������ָ����D3D�豸����

	img_name = imgname;

	D3DXIMAGE_INFO imageInfo; 	//��¼����ͼƬ����Ϣ��ͼƬ�������Ϣ
	D3DXCreateTextureFromFileEx(
		CPlatForm::Getinstance()->Get_pd3dDevice(), 		//D3D�豸����
		imgname, 	// ����ͼƬ�ĵ�ַ
		D3DX_DEFAULT, 		// ͼƬ�Ŀ�, 
		D3DX_DEFAULT, 		// ͼƬ�ĸ�
		1,			// ͼƬ��miplevels���༶���������ֱ��ʻ�仯
		0,			/*�趨��������ʹ�÷������������������0,D3DUSAGE_RENDERTARGET��
					D3DUSAGE_DYNAMIC��һ���õ���0��Ҳ����ʹ�� D3DUSAGE_DYNAMIC��
					�������Զ�̬�ı������е����ݡ����������Ҫ��̬�Ըı䣬�Ͳ���Ҫ�趨��
					������ΪD3DUSAGE_DYNAMIC��*/
		D3DFMT_UNKNOWN, 	//����ĸ�ʽ
		D3DPOOL_DEFAULT, 	/*������ι�����Щ����D3DPOOL_DEFAULT,D3DPOOL_MANAGED��
							һ��ʹ��D3DPOOL_MANAGED*/
		D3DX_FILTER_NONE, 	//ͼ�����صĹ��˷�ʽ
		D3DX_FILTER_NONE, 	//MIP�����ع��˷�ʽ
		D3DXCOLOR(0, 0, 0, 0), 	// �ؼ���ɫֵ, �������ͼƬ����Ĺؼ���ɫֵ����Ϊ͸��ɫ//Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE); 
		&imageInfo, 		//��¼����ͼƬ����Ϣ�����Ե����ǰͼƬ�Ŀ��
		NULL,			 //��¼�����ɫ�����Ϣ
		&pD3DTexture); 		// ������������ͼƬ���������ʵ��

	img_width = imageInfo.Width;
	img_height = imageInfo.Height;

	R = 1;
	G = 1;
	B = 1;
	A = 1;

	img_rect = { 0,0,img_width,img_height };

	color = D3DXCOLOR(R, G, B, A);
	sort = 0;

	scale = D3DXVECTOR2(1,1);
	angle = 0;
	x = 0;
	y = 0;
	dir = true;
	anchor = D3DXVECTOR3(img_width / 2, img_height / 2, 0);
}


CPicture::~CPicture()
{
	
}

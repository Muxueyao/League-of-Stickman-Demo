#include "stdafx.h"



void CPicture::set_matrix()
{
	D3DXMatrixScaling(&scale_matrix, scale.x, scale.y, 1);
	D3DXMatrixRotationZ(&angle_matrix, angle);//旋转
	D3DXMatrixTranslation(&pos_matrix, x, y, 0);//平移

	matrix = scale_matrix*angle_matrix*pos_matrix;

	if (dir)
	{
		matrix._11 *= 1;
	}
	else
	{
		matrix._11 *= -1;
	}
	
	pSprite->SetTransform(&matrix);//将变换矩阵写入精灵
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

	D3DXCreateSprite(CPlatForm::Getinstance()->Get_pd3dDevice(), &pSprite);//将精灵指针与D3D设备关联

	img_name = imgname;

	D3DXIMAGE_INFO imageInfo; 	//记录载入图片的信息，图片长宽等信息
	D3DXCreateTextureFromFileEx(
		CPlatForm::Getinstance()->Get_pd3dDevice(), 		//D3D设备对象
		imgname, 	// 载入图片的地址
		D3DX_DEFAULT, 		// 图片的宽, 
		D3DX_DEFAULT, 		// 图片的高
		1,			// 图片的miplevels，多级渐进纹理，分辨率会变化
		0,			/*设定这个纹理的使用方法，这个参数可以是0,D3DUSAGE_RENDERTARGET和
					D3DUSAGE_DYNAMIC。一般用的是0，也可以使用 D3DUSAGE_DYNAMIC，
					这样可以动态改变纹理中的数据。如果纹理不需要动态性改变，就不需要设定这
					个参数为D3DUSAGE_DYNAMIC。*/
		D3DFMT_UNKNOWN, 	//纹理的格式
		D3DPOOL_DEFAULT, 	/*这是如何管理这些纹理D3DPOOL_DEFAULT,D3DPOOL_MANAGED，
							一般使用D3DPOOL_MANAGED*/
		D3DX_FILTER_NONE, 	//图像像素的过滤方式
		D3DX_FILTER_NONE, 	//MIP的像素过滤方式
		D3DXCOLOR(0, 0, 0, 0), 	// 关键颜色值, 将载入的图片里面的关键颜色值设置为透明色//Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE); 
		&imageInfo, 		//记录载入图片的信息，可以点出当前图片的宽高
		NULL,			 //记录载入调色板的信息
		&pD3DTexture); 		// 用来储存载入图片的纹理对象实例

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

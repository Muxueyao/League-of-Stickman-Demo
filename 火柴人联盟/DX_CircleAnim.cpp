#include "stdafx.h"


DX_CircleAnim::DX_CircleAnim(LPDIRECT3DDEVICE9 m_pd3dDevice, int dstX, int dstY, float radius, LPCWSTR strFilename)
{
	setTotalTimer(10);
	color = 0xffffffff;
	this->m_pd3dDevice = m_pd3dDevice;
	//D3DXCreateTextureFromFile(m_pd3dDevice, strFilename, &m_pTextures);
	//m_pd3dDevice = PlatForm::getInstance()->getDevice();
	D3DXIMAGE_INFO imageInfo; 	//记录载入图片的信息，图片长宽等信息
	D3DXCreateTextureFromFileEx(
		m_pd3dDevice, 		//D3D设备对象
		strFilename, 	// 载入图片的地址
		D3DX_DEFAULT, 		// 图片的宽, 
		D3DX_DEFAULT, 		// 图片的高
		1,			// 图片的miplevels，多级渐进纹理，分辨率会变化
		0,			/*设定这个纹理的使用方法，这个参数可以是0,D3DUSAGE_RENDERTARGET和
					D3DUSAGE_DYNAMIC。一般用的是0，也可以使用 D3DUSAGE_DYNAMIC，
					这样可以动态改变纹理中的数据。如果纹理不需要动态性改变，就不需要设定这
					个参数为D3DUSAGE_DYNAMIC。*/
		D3DFMT_UNKNOWN, 	//纹理的格式
		D3DPOOL_MANAGED, 	/*这是如何管理这些纹理D3DPOOL_DEFAULT,D3DPOOL_MANAGED，
							一般使用D3DPOOL_MANAGED*/
		D3DX_FILTER_NONE, 	//图像像素的过滤方式
		D3DX_FILTER_NONE, 	//MIP的像素过滤方式
		D3DXCOLOR(0, 0, 0, 0), 	// 关键颜色值, 将载入的图片里面的关键颜色值设置为透明色//Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE); 
		&imageInfo, 		//记录载入图片的信息，可以点出当前图片的宽高
		NULL,			 //记录载入调色板的信息
		&m_pTextures); 		// 用来储存载入图片的纹理对象实例

	verticePerRad = 1.0f / radius;

	verticeNum = (DWORD)(2 * D3DX_PI / verticePerRad) + 2;

	m_pd3dDevice->CreateVertexBuffer(verticeNum * sizeof(CUSTOMVERTEX_RHW),
		D3DUSAGE_WRITEONLY, CUSTOMVERTEX_RHW::FVF_Flags, D3DPOOL_MANAGED, &m_pVertexBuffer, NULL);

	CUSTOMVERTEX_RHW *pVertices;
	m_pVertexBuffer->Lock(0, verticeNum * sizeof(CUSTOMVERTEX_RHW), (void **)&pVertices, 0);
	pVertices[0].tu = 0.5f;
	pVertices[0].tv = 0.5f;
	pVertices[0].color = color;
	pVertices[0].x = (float)dstX;
	pVertices[0].y = (float)dstY;
	pVertices[0].z = 0.0f;
	pVertices[0].rhw = 1.0f;
	for (DWORD i = 1;i<verticeNum;i++)
	{
		float beta = (i - 1)*verticePerRad;
		pVertices[i].tu = 0.5f*(sin(beta) + 1.0f);
		pVertices[i].tv = 0.5f*(1.0f - cos(beta));

		pVertices[i].color = color;
		pVertices[i].x = radius*sin(beta) + dstX;
		pVertices[i].y = dstY - radius*cos(beta);
		pVertices[i].z = 0.0f;
		pVertices[i].rhw = 1.0f;
	}

	m_pVertexBuffer->Unlock();
}

void DX_CircleAnim::setTotalTimer(float timer)
{
	totalTimer = timer;
}

void DX_CircleAnim::play()
{
	isPlaying = true;
	curTimer = 0;
	curVertice = 0;
}

void DX_CircleAnim::stop()
{
	isPlaying = false;
}

bool DX_CircleAnim::getstate()
{
	if (curVertice <= 0)
		return true;
	return false;
}

void DX_CircleAnim::update(float durTime)
{
	if (isPlaying == true)
	{
		curTimer += durTime;
		curVertice = (1.0 - curTimer / totalTimer)*(verticeNum - 2);
		if (curVertice>verticeNum - 2)
		{
			curVertice = verticeNum - 2;
			stop();
		}
	}
	m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	if (m_pTextures != NULL)
	{
		m_pd3dDevice->SetTexture(0, m_pTextures);

		m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

		m_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		m_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		m_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	}
	else
	{
		m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);

		m_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		m_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	}
	m_pd3dDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(CUSTOMVERTEX_RHW));
	m_pd3dDevice->SetFVF(CUSTOMVERTEX_RHW::FVF_Flags);
	if (curVertice <= 0)
		curVertice = 0;
	m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, curVertice);

	m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

}

DX_CircleAnim::~DX_CircleAnim()
{
}

#include "StdAfx.h"
#include "SpriteX.h"

vector<SpriteX*>SpriteX::spxManager;

SpriteX::SpriteX(LPDIRECT3DDEVICE9 pd3dDevice,char *spxName,LPDIRECT3DTEXTURE9 image)
{
	m_pd3dDevice=pd3dDevice;

	initData();
	loadSpx(spxName, image);
}

SpriteX::SpriteX(LPDIRECT3DDEVICE9 pd3dDevice,char *spxName,LPDIRECT3DTEXTURE9 tiles[])
{
	m_pd3dDevice=pd3dDevice;

	initData();
	loadSpx(spxName, image);
	this->tiles = tiles;
	this->tileMode = true;
}

SpriteX::SpriteX(LPDIRECT3DDEVICE9 pd3dDevice,char* spxName, char* imageName)
{
	m_pd3dDevice=pd3dDevice;
	tiles = NULL;
	initData();

	strcpy(this->spxName,spxName);
	strcpy(this->imageName,imageName);

	bool data = false;
	bool image = false;

	for (int i = 0; i < spxManager.size(); ++i) 
	{
		if (data && image) 
			break;

		SpriteX *spx = spxManager.at(i);
		if (!data && strcmp(spx->spxName,spxName)==0)
		{
			data = true;
			this->actionData = spx->actionData;
			this->actionCount = spx->actionCount; //action count
			this->frameData = spx->frameData; //frame data
			this->frameCount = spx->frameCount; //frame count
			this->tileData = spx->tileData; //tile data
			this->tileCount = spx->tileCount; //tile count
			this->tiles = spx->tiles;
			this->tileUseCounter = spx->tileUseCounter;
			this->tileMode = spx->tileMode;
			strcpy(this->spxFileName,spx->spxFileName);
			strcpy(this->spxFileExt,spx->spxFileExt);
			this->delay = spx->delay;
		}

		if (!image && strcmp(spx->imageName,imageName)==0) 
		{
			image = true;
			if (tileMode) 
			{
				//this->image = spx->image;
				strcpy(this->spxFileName,spx->spxFileName);
				strcpy(this->spxFileExt,spx->spxFileExt);
				this->tiles = spx->tiles;
				this->tileUseCounter = spx->tileUseCounter;
			}
			else
			{

				this->image = spx->image;
			}
		}
	}

	if (image == false || data == false) 
	{
		addSpxToManage(this);
	}

	if (!data) 
	{
		loadSpx(spxName, NULL);
	}

	if (!image)
	{
		if (tileMode)
		{
			char ch;
			int len=0;
			while ((ch=*(imageName+len))!='\0')
			{
				len++;
				if (ch=='.')
				{
					strcpy(spxFileExt,strchr(imageName,'.'));
					strncpy(spxFileName,imageName,len-1);
					spxFileName[len]='\0';
					break;
				}
			}
			if (strlen(spxFileExt)==0)
			{
				strcpy(spxFileName,imageName);
				strcpy(spxFileExt,"");
			}

			tiles = new LPDIRECT3DTEXTURE9[tileCount];
			tileUseCounter = new int[tileCount];

			memset(tiles,0,sizeof(LPDIRECT3DTEXTURE9)*tileCount);
			memset(tileUseCounter,0,sizeof(int)*tileCount);
		}
		else
		{
			LPDIRECT3DTEXTURE9 spximg = NULL;
			try
			{
				if (FAILED(createImage(imageName,spximg)))
				{
					throw "can't load spx image\n";
				}
			}
			catch (char* ex)
			{
				MessageBoxA(0,ex,"错误",0);
			}
			loadSpx(spxName, spximg);
		}
	}
}

SpriteX::SpriteX(SpriteX &spx)
{
	m_pd3dDevice=spx.m_pd3dDevice;
	initData();

	//init vars
	int i, length;
	actionCount = spx.actionCount;
	frameCount = spx.frameCount;
	tileCount = spx.tileCount;
	actionData = new short*[actionCount];
	frameData = new short*[frameCount];
	tileData = new short*[tileCount];
	//copy action
	for (i = 0; i < actionCount; i++)
	{
		length = spx.actionData[i][0];
		actionData[i] = new short[length];
		memcpy(actionData[i],spx.actionData[i],sizeof(short)*length);
	}
	//copy frame
	for (i = 0; i < frameCount; i++)
	{
		length = spx.frameData[i][0];
		frameData[i] = new short[length];
		memcpy(frameData[i],spx.frameData[i],sizeof(short)*length);
	}
	//copy tile
	for (i = 0; i < tileCount; i++)
	{
		length = 4;
		tileData[i] = new short[length];
		memcpy(tileData[i],spx.tileData[i],sizeof(short)*length);
	}
	//copy data
	actionIndex = spx.actionIndex;
	sequenceIndex = spx.sequenceIndex;
	image = spx.image;
	x = spx.x;
	y = spx.y;
	visible = spx.visible;
	lastTime = spx.lastTime;
	firstUpdate = spx.firstUpdate;
	disableUpdate = spx.disableUpdate;
}

void SpriteX::initData()
{
	x=0;
	y=0;
	flipX=1;
	flipY=1;
	scaleX=1;
	scaleY=1;
	rotation=0;
	originOffsetX=0;
	originOffsetY=0;
	delay=0;
	actionIndex=0; //默认动作0
	sequenceIndex=0; //默认帧索引0
	firstUpdate=false;
	disableUpdate=false;
	tileMode=false;
	isLoop=true;
	memset(spxFileExt,0,255);
	memset(spxFileName,0,255);

	for(int i = 0 ; i < 4 ; i++ )
	{
		m_Vertex2D[i].x = 0.0f;
		m_Vertex2D[i].y = 0.0f;
		m_Vertex2D[i].z = 0.0f;
		m_Vertex2D[i].rhw = 1.0f;
		m_Vertex2D[i].color = 0xffffffff;//argb
		m_Vertex2D[i].tu = 0;
		m_Vertex2D[i].tv = 0;
	}

	m_pd3dDevice->CreateVertexBuffer(4*sizeof(CUSTOMVERTEX_RHW),
		D3DUSAGE_WRITEONLY,CUSTOMVERTEX_RHW::FVF_Flags,D3DPOOL_MANAGED,&m_pVertexBuffer,NULL);

	m_rectangle=new DXRectangle(m_pd3dDevice);
	m_circle=new DXCircle(m_pd3dDevice);
	m_polygon=new DXPolygon(m_pd3dDevice);
	m_text=new DXText(m_pd3dDevice);
}

HRESULT SpriteX::createImage(char *imageName,OUT LPDIRECT3DTEXTURE9 &spximg)
{
	D3DXIMAGE_INFO imageInfo; //记录载入图片的信息
	HRESULT hr = D3DXCreateTextureFromFileExA(
		m_pd3dDevice, //D3D设备对象
		imageName, // 载入图片的地址
		D3DX_DEFAULT, // 图片的宽, 
		D3DX_DEFAULT, // 图片的高
		1,			// 图片的miplevels，多级渐进纹理，分辨率会变化
		0,			/*设定这个纹理的使用方法，这个参数可以是0,D3DUSAGE_RENDERTARGET和
					D3DUSAGE_DYNAMIC。一般用的是0，也可以使用 D3DUSAGE_DYNAMIC，
					这样可以动态改变纹理中的数据。如果纹理不需要动态性改变，就不需要设定这
					个参数为D3DUSAGE_DYNAMIC。*/
		D3DFMT_UNKNOWN, //纹理的格式
		D3DPOOL_MANAGED, /*这是如何管理这些纹理D3DPOOL_DEFAULT,D3DPOOL_MANAGED，
						一般使用D3DPOOL_MANAGED*/
		D3DX_FILTER_NONE, //图像像素的过滤方式
		D3DX_FILTER_NONE, //MIP的像素过滤方式
		D3DXCOLOR(0,0,0,0), // 关键颜色值, 将载入的图片里面的关键颜色值设置为透明色//Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE); 
		&imageInfo,			//记录载入图片的信息
		NULL,			//记录载入调色板的信息
		&spximg);	// 用来储存载入图片的纹理对象实例

		return hr;
}

DWORD SpriteX::randomColor()
{
	char r,g,b;
	do 
	{
		r=rand()%2;
		g=rand()%2;
		b=rand()%2;

	} while (r==0 && g==0 && b==0);
	
	return D3DXCOLOR(r,g,b,1);
}

void SpriteX::enableUpdate(bool enable)
{
	if (disableUpdate && enable) {
		lastTime = timeGetTime();
	}
	disableUpdate = !enable;
}

bool SpriteX::isEnableUpdate()
{
	return !disableUpdate;
}

void SpriteX::update()
{
	if (!isEnableUpdate())
		return;

	DWORD time=timeGetTime();

	if (isDelay())
	{
		if (!firstUpdate)
		{
			firstUpdate = true;
			this->lastTime = time;
		}
		int dms = getDelayTime();
		if ( (time - this->lastTime) >= dms)
		{
			nextFrame();
			this->lastTime = time;
		}
	}
	else
	{
		if (!firstUpdate)
		{
			firstUpdate = true;
			this->lastTime = time;
		}
		int dms = delay;
		if ( (time - this->lastTime) >= dms)
		{
			nextFrame();
			this->lastTime = time;
		}
	}
}

void SpriteX::drawImage(LPDIRECT3DTEXTURE9 image,int x_src,int y_src,int wid_src,int hei_src,
						int transform,int x_dest,int y_dest,int wid_dest,int hei_dest)
{
	m_Vertex2D[0].x = x_dest-originOffsetX;
	m_Vertex2D[0].y = y_dest-originOffsetY;
	m_Vertex2D[1].x = x_dest+wid_dest-originOffsetX;
	m_Vertex2D[1].y = y_dest-originOffsetY;
	m_Vertex2D[2].x = x_dest-originOffsetX;
	m_Vertex2D[2].y = y_dest+hei_dest-originOffsetY;
	m_Vertex2D[3].x = x_dest+wid_dest-originOffsetX;
	m_Vertex2D[3].y = y_dest+hei_dest-originOffsetY;


	switch (transform)
	{
	case TRANS_NONE:
		m_Vertex2D[0].tu = (float)x_src/getImageWidth(image);
		m_Vertex2D[0].tv = (float)y_src/getImageHeight(image);

		m_Vertex2D[1].tu = (float)(x_src+wid_src)/getImageWidth(image);
		m_Vertex2D[1].tv = (float)y_src/getImageHeight(image);
		
		m_Vertex2D[2].tu = (float)x_src/getImageWidth(image);
		m_Vertex2D[2].tv = (float)(y_src+hei_src)/getImageHeight(image);

		m_Vertex2D[3].tu = (float)(x_src+wid_src)/getImageWidth(image);
		m_Vertex2D[3].tv = (float)(y_src+hei_src)/getImageHeight(image);
		break;
	case TRANS_ROT90:
		m_Vertex2D[0].tu = (float)x_src/getImageWidth(image);
		m_Vertex2D[0].tv = (float)(y_src+hei_src)/getImageHeight(image);

		m_Vertex2D[1].tu = (float)x_src/getImageWidth(image);
		m_Vertex2D[1].tv = (float)y_src/getImageHeight(image);

		m_Vertex2D[2].tu = (float)(x_src+wid_src)/getImageWidth(image);
		m_Vertex2D[2].tv = (float)(y_src+hei_src)/getImageHeight(image);

		m_Vertex2D[3].tu = (float)(x_src+wid_src)/getImageWidth(image);
		m_Vertex2D[3].tv = (float)y_src/getImageHeight(image);
		break;
	case TRANS_ROT180:
		m_Vertex2D[0].tu = (float)(x_src+wid_src)/getImageWidth(image);
		m_Vertex2D[0].tv = (float)(y_src+hei_src)/getImageHeight(image);

		m_Vertex2D[1].tu = (float)x_src/getImageWidth(image);
		m_Vertex2D[1].tv = (float)(y_src+hei_src)/getImageHeight(image);

		m_Vertex2D[2].tu = (float)(x_src+wid_src)/getImageWidth(image);
		m_Vertex2D[2].tv = (float)y_src/getImageHeight(image);

		m_Vertex2D[3].tu = (float)x_src/getImageWidth(image);
		m_Vertex2D[3].tv = (float)y_src/getImageHeight(image);
		break;
	case TRANS_ROT270:
		m_Vertex2D[0].tu = (float)(x_src+wid_src)/getImageWidth(image);
		m_Vertex2D[0].tv = (float)y_src/getImageHeight(image);

		m_Vertex2D[1].tu = (float)(x_src+wid_src)/getImageWidth(image);
		m_Vertex2D[1].tv = (float)(y_src+hei_src)/getImageHeight(image);

		m_Vertex2D[2].tu = (float)x_src/getImageWidth(image);
		m_Vertex2D[2].tv = (float)y_src/getImageHeight(image);

		m_Vertex2D[3].tu = (float)x_src/getImageWidth(image);
		m_Vertex2D[3].tv = (float)(y_src+hei_src)/getImageHeight(image);
		break;
	case TRANS_MIRROR:
		m_Vertex2D[0].tu = (float)(x_src+wid_src)/getImageWidth(image);
		m_Vertex2D[0].tv = (float)y_src/getImageHeight(image);

		m_Vertex2D[1].tu = (float)x_src/getImageWidth(image);
		m_Vertex2D[1].tv = (float)y_src/getImageHeight(image);

		m_Vertex2D[2].tu = (float)(x_src+wid_src)/getImageWidth(image);
		m_Vertex2D[2].tv = (float)(y_src+hei_src)/getImageHeight(image);

		m_Vertex2D[3].tu = (float)x_src/getImageWidth(image);
		m_Vertex2D[3].tv = (float)(y_src+hei_src)/getImageHeight(image);
		break;
	case TRANS_MIRROR_ROT90:
		m_Vertex2D[0].tu = (float)(x_src+wid_src)/getImageWidth(image);
		m_Vertex2D[0].tv = (float)(y_src+hei_src)/getImageHeight(image);

		m_Vertex2D[1].tu = (float)(x_src+wid_src)/getImageWidth(image);
		m_Vertex2D[1].tv = (float)y_src/getImageHeight(image);

		m_Vertex2D[2].tu = (float)x_src/getImageWidth(image);
		m_Vertex2D[2].tv = (float)(y_src+hei_src)/getImageHeight(image);

		m_Vertex2D[3].tu = (float)x_src/getImageWidth(image);
		m_Vertex2D[3].tv = (float)y_src/getImageHeight(image);
		break;
	case TRANS_MIRROR_ROT180:
		m_Vertex2D[0].tu = (float)x_src/getImageWidth(image);
		m_Vertex2D[0].tv = (float)(y_src+hei_src)/getImageHeight(image);

		m_Vertex2D[1].tu = (float)(x_src+wid_src)/getImageWidth(image);
		m_Vertex2D[1].tv = (float)(y_src+hei_src)/getImageHeight(image);

		m_Vertex2D[2].tu = (float)x_src/getImageWidth(image);
		m_Vertex2D[2].tv = (float)y_src/getImageHeight(image);

		m_Vertex2D[3].tu = (float)(x_src+wid_src)/getImageWidth(image);
		m_Vertex2D[3].tv = (float)y_src/getImageHeight(image);
		break;
	case TRANS_MIRROR_ROT270:
		m_Vertex2D[0].tu = (float)x_src/getImageWidth(image);
		m_Vertex2D[0].tv = (float)y_src/getImageHeight(image);

		m_Vertex2D[1].tu = (float)x_src/getImageWidth(image);
		m_Vertex2D[1].tv = (float)(y_src+hei_src)/getImageHeight(image);

		m_Vertex2D[2].tu = (float)(x_src+wid_src)/getImageWidth(image);
		m_Vertex2D[2].tv = (float)y_src/getImageHeight(image);

		m_Vertex2D[3].tu = (float)(x_src+wid_src)/getImageWidth(image);
		m_Vertex2D[3].tv = (float)(y_src+hei_src)/getImageHeight(image);
		break;
	}

	D3DXMATRIX worldMat=getWorldTransform();
	
	for (int i=0;i<4;i++)
	{
		D3DXVECTOR2 point=getWorldTransformPoint(D3DXVECTOR2(m_Vertex2D[i].x,m_Vertex2D[i].y),worldMat);
		m_Vertex2D[i].x=point.x;
		m_Vertex2D[i].y=point.y;
	}


	CUSTOMVERTEX_RHW *pVertices;
	m_pVertexBuffer->Lock(0,4*sizeof(CUSTOMVERTEX_RHW),(void **)&pVertices,0);
	memcpy(pVertices,m_Vertex2D,4*sizeof(CUSTOMVERTEX_RHW));
	m_pVertexBuffer->Unlock();

	m_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	m_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
	m_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);

	m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );
	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );

	m_pd3dDevice->SetTexture(0,image);
	m_pd3dDevice->SetStreamSource(0,m_pVertexBuffer,0,sizeof(CUSTOMVERTEX_RHW));
	m_pd3dDevice->SetFVF(CUSTOMVERTEX_RHW::FVF_Flags);
	m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

	m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	
}

void SpriteX::draw()
{
	if (m_pd3dDevice==NULL)
		return;
	
	if (visible) 
	{
		int tileIndex; //tile index
		int dx; //tile dest x
		int dy; //tile dest y
		int dw; //tile dest wid
		int dh; //tile dest hei
		int transform; //tile transform
		int tx; //tile x
		int ty; //tile y
		int tw; //tile width
		int th; //tile height
		
		int actionTransform = getActionTransform();
		if (actionTransform == TRANS_NONE)
		{
			int frameIndex = getSequenceFrame();
			int tileCount = frameData[frameIndex][FRAME_TILE_COUNT_BIT];
			int offset = FRAME_HEADER_SIZE; //tile data offset
			for (int i = 0; i < tileCount; i++)
			{
				if (tileMode)
				{
					tileIndex = frameData[frameIndex][0 + offset];
					dx = frameData[frameIndex][1 + offset];
					dy = frameData[frameIndex][2 + offset];
					transform = frameData[frameIndex][3 + offset];
					tx = 0;
					ty = 0;
					tw = getImageWidth(tiles[tileIndex]);
					th = getImageHeight(tiles[tileIndex]);

					if ((transform & INVERTED_AXES) != 0)
					{
						dw = th;
						dh = tw;
					}
					else
					{
						dw = tw;
						dh = th;
					}
					drawImage(tiles[tileIndex],tx,ty,tw,th,transform,dx,dy,dw,dh);
				}
				else
				{
					tileIndex = frameData[frameIndex][0 + offset];
					dx = frameData[frameIndex][1 + offset];
					dy = frameData[frameIndex][2 + offset];
					transform = frameData[frameIndex][3 + offset];
					tx = tileData[tileIndex][0];
					ty = tileData[tileIndex][1];
					tw = tileData[tileIndex][2];
					th = tileData[tileIndex][3];

					if ( (transform & INVERTED_AXES) != 0)
					{
						dw = th;
						dh = tw;
					}
					else
					{
						dw = tw;
						dh = th;
					}
					drawImage(image,tx,ty,tw,th,transform,dx,dy,dw,dh);
				}
				offset += 4;
			}
		}
		else
		{
			//render transform action,动作变形以坐标原点变换
			int cx;
			int cy;
			int frameIndex = getSequenceFrame();
			int tileCount = frameData[frameIndex][FRAME_TILE_COUNT_BIT];
			int offset = FRAME_HEADER_SIZE; //tile data offset
			for (int i = 0; i < tileCount; i++)
			{
				if (tileMode)
				{
					tileIndex = frameData[frameIndex][0 + offset];
					dx = frameData[frameIndex][1 + offset];
					dy = frameData[frameIndex][2 + offset];
					transform = frameData[frameIndex][3 + offset];
					tx = 0;
					ty = 0;
					tw = getImageWidth(tiles[tileIndex]);
					th = getImageHeight(tiles[tileIndex]);

					if ( (transform & INVERTED_AXES) != 0) 
					{
						dw = th;
						dh = tw;
					}
					else 
					{
						dw = tw;
						dh = th;
					}

					cx = - dx;
					cy = - dy;
					//finally transform
					transform = TRANSFORM_TABLE[transform][actionTransform];
					//adjust coordinate
					switch (actionTransform) 
					{
					case TRANS_NONE:
						//null
						break;
					case TRANS_ROT90:
						dx = - (dh - cy);
						dy = - cx;
						break;
					case TRANS_ROT180:
						dx = - (dw - cx);
						dy = - (dh - cy);
						break;
					case TRANS_ROT270:
						dx = - cy;
						dy = - (dw - cx);
						break;
					case TRANS_MIRROR:
						dx = - (dw - cx);
						break;
					case TRANS_MIRROR_ROT90:
						dx = - (dh - cy);
						dy = - (dw - cx);
						break;
					case TRANS_MIRROR_ROT180:
						dy = - (dh - cy);
						break;
					case TRANS_MIRROR_ROT270:
						dx = - cy;
						dy = - cx;
						break;
					}

					if ( (transform & INVERTED_AXES) != 0) 
					{
						dw = th;
						dh = tw;
					}
					else 
					{
						dw = tw;
						dh = th;
					}

					drawImage(tiles[tileIndex],tx,ty,tw,th,transform,dx,dy,dw,dh);
				}
				else
				{
					tileIndex = frameData[frameIndex][0 + offset];
					dx = frameData[frameIndex][1 + offset];
					dy = frameData[frameIndex][2 + offset];
					transform = frameData[frameIndex][3 + offset];
					tx = tileData[tileIndex][0];
					ty = tileData[tileIndex][1];
					tw = tileData[tileIndex][2];
					th = tileData[tileIndex][3];

					if ( (transform & INVERTED_AXES) != 0) 
					{
						dw = th;
						dh = tw;
					}
					else 
					{
						dw = tw;
						dh = th;
					}

					cx = - dx;
					cy = - dy;
					//finally transform
					transform = TRANSFORM_TABLE[transform][actionTransform];
					//adjust coordinate
					switch (actionTransform) 
					{
					case TRANS_NONE:
						//null
						break;
					case TRANS_ROT90:
						dx = - (dh - cy);
						dy = - cx;
						break;
					case TRANS_ROT180:
						dx = - (dw - cx);
						dy = - (dh - cy);
						break;
					case TRANS_ROT270:
						dx = - cy;
						dy = - (dw - cx);
						break;
					case TRANS_MIRROR:
						dx = - (dw - cx);
						break;
					case TRANS_MIRROR_ROT90:
						dx = - (dh - cy);
						dy = - (dw - cx);
						break;
					case TRANS_MIRROR_ROT180:
						dy = - (dh - cy);
						break;
					case TRANS_MIRROR_ROT270:
						dx = - cy;
						dy = - cx;
						break;
					}

					if ( (transform & INVERTED_AXES) != 0) 
					{
						dw = th;
						dh = tw;
					}
					else 
					{
						dw = tw;
						dh = th;
					}

					drawImage(image,tx,ty,tw,th,transform,dx,dy,dw,dh);
				}
				offset += 4;
			}
		}
	}
}

void SpriteX::debugDraw()
{
	int frameIndex = getSequenceFrame();

	if(m_drawArray.find(frameIndex)==m_drawArray.end())
	{
		vector<DrawParam> drawObjs;
		{
			DrawParam param;
			param.tyle=DrawParam::TYLE::s_rect;
			param.frameIndex=frameIndex;
			param.color=0xffffffff;
			drawObjs.push_back(param);
		}
		
		for (int i=0;i<getReferencePointCount();i++)
		{
			DrawParam param;
			param.tyle=DrawParam::TYLE::s_refPoint;
			param.frameIndex=frameIndex;
			param.index=i;
			param.color=randomColor();
			char str[255];
			sprintf(str,"%d",i+1);
			strcpy(param.str,str);
			drawObjs.push_back(param);
		}

		for (int i=0;i<getCollidesCount();i++)
		{
			DrawParam param;
			param.tyle=DrawParam::TYLE::s_obb;
			param.frameIndex=frameIndex;
			param.index=i;
			param.color=randomColor();
			char str[255];
			sprintf(str,"%d",i);
			strcpy(param.str,str);
			drawObjs.push_back(param);
		}

		m_drawArray.insert(make_pair(frameIndex,drawObjs));
	}

	map<int,vector<DrawParam>>::iterator map_iter=m_drawArray.find(frameIndex);
	if (map_iter!=m_drawArray.end())
	{
		vector<DrawParam> &drawObjs=(*map_iter).second;
		vector<DrawParam>::iterator vector_iter;
		for (vector_iter=drawObjs.begin();vector_iter!=drawObjs.end();vector_iter++)
		{
			DrawParam &param=(*vector_iter);
			//绘制帧的位置大小
			if (param.tyle==DrawParam::TYLE::s_rect)
			{
				RECT frameRect=getFrameRect();
				param.points[0]=D3DXVECTOR2(frameRect.left,frameRect.top);
				param.points[1]=D3DXVECTOR2(frameRect.right,frameRect.top);
				param.points[2]=D3DXVECTOR2(frameRect.right,frameRect.bottom);
				param.points[3]=D3DXVECTOR2(frameRect.left,frameRect.bottom);

				m_rectangle->draw(false,param.points[0],D3DXVECTOR2(param.points[1].x-param.points[0].x,
					param.points[2].y-param.points[0].y),param.color);
			}
			//绘制帧的碰撞区
			if (param.tyle==DrawParam::TYLE::s_obb)
			{
				VSObb obb=getCollidesObb(param.index);
				//VSAabb aabb=getCollidesAabb(i);
				VSAabb aabb;
				aabb.Construct(obb);

				//obb
				D3DXVECTOR2 vcA0, vcA1;
				vcA0 = obb.vcA0 * obb.fA0;//x轴
				vcA1 = obb.vcA1 * obb.fA1;//y轴
				param.points[0]=-vcA1-vcA0+obb.vcCenter;
				param.points[1]=-vcA1+vcA0+obb.vcCenter;
				param.points[2]=vcA1+vcA0+obb.vcCenter;
				param.points[3]=vcA1-vcA0+obb.vcCenter;
				param.orignal=obb.vcCenter;

				m_rectangle->draw(false,aabb.vcMin,D3DXVECTOR2(aabb.vcMax.x-aabb.vcMin.x,aabb.vcMax.y-aabb.vcMin.y),0xffff0000);
				m_polygon->draw(true,param.points,4,0x5000ff00);
				m_text->draw(true,param.str,param.orignal,param.color);
			}
			//绘制帧的参考点
			if (param.tyle==DrawParam::TYLE::s_refPoint)
			{
				param.orignal=getReferencePoint(param.index);

				m_circle->draw(false,param.orignal,16,360,param.color);
				m_rectangle->draw(false,D3DXVECTOR2(param.orignal.x-2,param.orignal.y-2),D3DXVECTOR2(4,4));
				m_text->draw(false,param.str,D3DXVECTOR2(param.orignal.x-2,param.orignal.y-15),param.color);
			}
		}
	}
}

void SpriteX::loadSpx(char* spxName, LPDIRECT3DTEXTURE9 image)
{
	try
	{
		FILE *fp;
		fp=fopen(spxName,"rb");

		int header;
		int sequenceLength;
		int collisionCount;
		int referencePointCount;
		int i, j, offset, length;
		byte delay;
		int frameTileCount;
		byte version;
		byte byteSequence;

		//check spx format
		fread(&header,sizeof(int),1,fp);
		if (header != SPX_HEADER) 
		{
			throw "invalid SpriteX format\n";
		}
		else
		{
			fread(&version,sizeof(byte),1,fp);
			//sprite file and sprite class no matching
			if (version != SPX_VERSION)
			{
				throw "version no matching\n";
			}
			//byte sequence check
			fread(&byteSequence,sizeof(byte),1,fp);
			if ( (byteSequence & 1) != SPX_BYTE_SEQUENCE_C)
			{
				throw "byte sequence error\n";
			}

			//add
			if ( (byteSequence & 2) != 0)
				tileMode = true;

			//read tile
			fread(&tileCount,sizeof(int),1,fp);
			if (tileMode == false) 
			{
				tileData = new short*[tileCount];
				for (i = 0; i < tileCount; i++) {
					tileData[i]=new short[4];
					/************************************************************************/
					/*struct
					...
					array[0] tile x
					array[1] tile y
					array[2] tile width
					array[3] tile height
					...*/
					/************************************************************************/
					fread(&tileData[i][0],sizeof(short),1,fp);
					fread(&tileData[i][1],sizeof(short),1,fp);
					fread(&tileData[i][2],sizeof(short),1,fp);
					fread(&tileData[i][3],sizeof(short),1,fp);
				}
			}

			//read frame
			fread(&frameCount,sizeof(int),1,fp);
			frameData = new short*[frameCount];
			for (i = 0; i < frameCount; i++) 
			{
				fread(&frameTileCount,sizeof(int),1,fp);
				fread(&collisionCount,sizeof(int),1,fp);
				fread(&referencePointCount,sizeof(int),1,fp);
				length = FRAME_HEADER_SIZE + frameTileCount * 4 +
						collisionCount * 4 + referencePointCount * 2;
				frameData[i]=new short[length];
				/************************************************************************/
				/*struct
				array[0] data length
				array[1] tile count
				arrat[2] collision count
				arrat[3] reference count
				arrat[4] frame width
				arrat[5] frame height
				...
				array[6] tile index
				array[7] tile x
				array[8] tile y
				array[9] tile transform
				...
				array[10] collision x
				array[11] collision y
				array[12] collision width
				array[13] collision height
				...
				array[14] reference point x
				array[15] reference point y
				...*/
				/************************************************************************/
				frameData[i][0] = (short)length;
				frameData[i][FRAME_TILE_COUNT_BIT] = (short)frameTileCount;
				frameData[i][FRAME_COLLISION_COUNT_BIT] = (short)collisionCount;
				frameData[i][FRAME_REFERENCE_POINT_COUNT_BIT] =(short)referencePointCount;
				fread(&frameData[i][FRAME_TOP_POS_BIT],sizeof(short),1,fp);//frame top pos
				fread(&frameData[i][FRAME_BOTTOM_POS_BIT],sizeof(short),1,fp);//frame bottom pos
				fread(&frameData[i][FRAME_LEFT_POS_BIT],sizeof(short),1,fp);//frame left pos
				fread(&frameData[i][FRAME_RIGHT_POS_BIT],sizeof(short),1,fp);//frame right pos

				offset = FRAME_HEADER_SIZE;
				
				//read frame tile
				for (j = 0; j < frameTileCount; j++)
				{
					fread(&frameData[i][0 + offset],sizeof(short),1,fp);//tile index
					fread(&frameData[i][1 + offset],sizeof(short),1,fp);//tile x
					fread(&frameData[i][2 + offset],sizeof(short),1,fp);//tile y
					fread(&frameData[i][3 + offset],sizeof(short),1,fp);//tile transform
					offset += 4;
				}

				//read collision
				for (j = 0; j < collisionCount; j++)
				{
					fread(&frameData[i][0 + offset],sizeof(short),1,fp);//collision x
					fread(&frameData[i][1 + offset],sizeof(short),1,fp);//collision y
					fread(&frameData[i][2 + offset],sizeof(short),1,fp);//collision width
					fread(&frameData[i][3 + offset],sizeof(short),1,fp);//collision height
					offset += 4;
				}

				//reference point
				for (j = 0; j < referencePointCount; j++)
				{
					fread(&frameData[i][0 + offset],sizeof(short),1,fp);//reference point x
					fread(&frameData[i][1 + offset],sizeof(short),1,fp);//reference point y
					offset += 2;
				}
			}

			//read action
			fread(&actionCount,sizeof(int),1,fp);
			actionData = new short*[actionCount];
			for (i = 0; i < actionCount; i++)
			{
				fread(&sequenceLength,sizeof(int),1,fp);
				fread(&delay,sizeof(byte),1,fp);
				if (delay == 1) 
					length = ACTION_HEADER_SIZE + sequenceLength * 2;
				else
					length = ACTION_HEADER_SIZE + sequenceLength;
				actionData[i] = new short[length];
				/************************************************************************/
				/*struct
				array[0] data length
				array[1] sequence count
				array[2] action delay
				array[3] action transform
				...
				array[4] action sequences
				#array[5] delay time
				...*/
				/************************************************************************/
				actionData[i][0] = (short)length; //data length for c copy array
				actionData[i][ACTION_SEQUENCE_LENGTH_BIT] = (short)sequenceLength; //sequence count
				actionData[i][ACTION_SEQUENCE_DELAY_BIT] = delay; //action delay
				fread(&actionData[i][ACTION_TRANSFORM_BIT],sizeof(int),1,fp);//action transform
				
				offset = ACTION_HEADER_SIZE;
				if (delay == 1) 
				{
					for (j = 0; j < sequenceLength; j++)
					{
						//read sequence
						fread(&actionData[i][offset],sizeof(short),1,fp);
						//read delay time
						fread(&actionData[i][offset + 1],sizeof(short),1,fp);
						offset += 2;
					}
				}
				else
				{
					for (j = 0; j < sequenceLength; j++)
					{
						//read sequence
						fread(&actionData[i][offset],sizeof(short),1,fp);
						offset += 1;
					}
				}
			}
		}

		//set image
		setImage(image);

		//load complete
		visible = true;

		//data.close();
		fclose(fp);
		
	}
	catch (char *ex)
	{
		MessageBoxA(0,ex,"错误",0);
	}
}

void SpriteX::initAction(int nAction)
{
	if (!tileMode)
		return;
	
	int *tileUse = new int[tileCount];
	memset(tileUse,0,sizeof(int)*tileCount);
	int sequenceLength = actionData[nAction][ACTION_SEQUENCE_LENGTH_BIT];
	int isDelay = actionData[nAction][ACTION_SEQUENCE_DELAY_BIT];
	int actionDataOffset = ACTION_HEADER_SIZE;
	if (isDelay == 1)
	{
		for (int i = 0; i < sequenceLength; ++i)
		{
			int frame = actionData[nAction][actionDataOffset];
			int frameTileCount = frameData[frame][FRAME_TILE_COUNT_BIT];
			int frameDataOffset = FRAME_HEADER_SIZE;
			int tile;
			for (int j = 0; j < frameTileCount; ++j)
			{
				tile = frameData[frame][frameDataOffset];
				frameDataOffset += 4;
				tileUse[tile] = 1;
			}
			actionDataOffset += 2;
		}
	}
	else
	{
		for (int i = 0; i < sequenceLength; ++i)
		{
			int frame = actionData[nAction][actionDataOffset];
			int frameTileCount = frameData[frame][FRAME_TILE_COUNT_BIT];
			int frameDataOffset = FRAME_HEADER_SIZE;
			int tile;
			for (int j = 0; j < frameTileCount; ++j)
			{
				tile = frameData[frame][frameDataOffset];
				frameDataOffset += 4;
				tileUse[tile] = 1;
			}
			++actionDataOffset;
		}
	}

	char fullName[255];
	for (int i = 0; i < tileCount; i++)
	{
		if (tileUse[i] == 1)
		{
			if (tiles[i] == NULL)
			{
				sprintf(fullName,"%s%d%s",spxFileName,i,spxFileExt);
				LPDIRECT3DTEXTURE9 spximg = NULL;
				try
				{
					if (FAILED(createImage(fullName,spximg)))
					{
						throw "can't load spx image\n";
					}
				}
				catch (char* ex)
				{
					MessageBoxA(0,ex,"错误",0);
				}
				tiles[i] = spximg;
			}
			++tileUseCounter[i];
		}
	}

	delete []tileUse;
}

void SpriteX::releaseAction(int nAction)
{
	if (!tileMode)
		return;
	
	int *tileUse = new int[tileCount];
	int sequenceLength = actionData[nAction][ACTION_SEQUENCE_LENGTH_BIT];
	int isDelay = actionData[nAction][ACTION_SEQUENCE_DELAY_BIT];
	int actionDataOffset = ACTION_HEADER_SIZE;
	if (isDelay == 1)
	{
		for (int i = 0; i < sequenceLength; ++i)
		{
			int frame = actionData[nAction][actionDataOffset];
			int frameTileCount = frameData[frame][FRAME_TILE_COUNT_BIT];
			int frameDataOffset = FRAME_HEADER_SIZE;
			int tile;
			for (int j = 0; j < frameTileCount; ++j)
			{
				tile = frameData[frame][frameDataOffset];
				frameDataOffset += 4;
				tileUse[tile] = 1;
			}
			actionDataOffset += 2;
		}
	}
	else
	{
		for (int i = 0; i < sequenceLength; ++i)
		{
			int frame = actionData[nAction][actionDataOffset];
			int frameTileCount = frameData[frame][FRAME_TILE_COUNT_BIT];
			int frameDataOffset = FRAME_HEADER_SIZE;
			int tile;
			for (int j = 0; j < frameTileCount; ++j)
			{
				tile = frameData[frame][frameDataOffset];
				frameDataOffset += 4;
				tileUse[tile] = 1;
			}
			++actionDataOffset;
		}
	}

	for (int i = 0; i < tileCount; i++)
	{
		if (tileUse[i] == 1)
		{
			if (tiles[i] != NULL)
			{
				--tileUseCounter[i];
				if (tileUseCounter[i] <= 0)
				{
					tiles[i] = NULL;
				}
			}
		}
	}

	delete []tileUse;
}

void SpriteX::initAllAction()
{
	if (!tileMode)
		return;

	char fullName[255];
	for (int i = 0; i < tileCount; i++)
	{
		if (tiles[i] == NULL)
		{
			sprintf(fullName,"%s%d%s",spxFileName,i,spxFileExt);
			LPDIRECT3DTEXTURE9 spximg = NULL;
			try
			{
				if (FAILED(createImage(fullName,spximg)))
				{
					throw "can't load spx image\n";
				}
			}
			catch (char* ex)
			{
				MessageBoxA(0,ex,"错误",0);
			}
			tiles[i] = spximg;
		}
		tileUseCounter[i] = 1;
	}
}

void SpriteX::releaseAllAction()
{
	if (!tileMode)
		return;

	for (int i = 0; i < tileCount; i++)
	{
		tiles[i] = NULL;
		tileUseCounter[i] = 0;
	}
}


void SpriteX::setAction(int actionIndex, bool loop)
{
	if (actionIndex == this->actionIndex)
	{
		setLoop(loop);
		return;
	}
	if (actionIndex < 0 || actionIndex >= actionCount)
	{
		throw "Index Out Of Bounds";
	}
	else
	{
		this->actionIndex =actionIndex;
		this->sequenceIndex =0;
		this->firstUpdate =false;
		setLoop(loop);
	}
}

int SpriteX::getAction()
{
	return actionIndex;
}

int SpriteX::getActionCount()
{
	return actionCount;
}

int SpriteX::getSequenceFrame(int sequenceIndex)
{
	if (isDelay())
		return actionData[actionIndex][ACTION_HEADER_SIZE + sequenceIndex * 2];
	else
		return actionData[actionIndex][ACTION_HEADER_SIZE + sequenceIndex];
}

int SpriteX::getSequenceFrame()
{
	if (isDelay())
		return actionData[actionIndex][ACTION_HEADER_SIZE + this->sequenceIndex * 2];
	else
		return actionData[actionIndex][ACTION_HEADER_SIZE + this->sequenceIndex];
}

int SpriteX::getSequenceLength()
{
	return actionData[actionIndex][ACTION_SEQUENCE_LENGTH_BIT];
}

void SpriteX::setFrame(int sequenceIndex)
{
	if (sequenceIndex < 0 || sequenceIndex >= getSequenceLength())
		return;
	else
	{
		this->sequenceIndex = sequenceIndex;
		this->firstUpdate = false;
	}
}

int SpriteX::getFrame()
{
	return sequenceIndex;
}

void SpriteX::nextFrame()
{
	if (isLoop)
	{
		sequenceIndex =(sequenceIndex + 1) % getSequenceLength();
		firstUpdate =false;
		loopFinished =false;
	}
	else
	{
		if (sequenceIndex < getSequenceLength() - 1)
		{
			sequenceIndex++;
			loopFinished =false;
		}
		else
		{
			loopFinished =true;
		}
	}
}

void SpriteX::prevFrame()
{
	if (sequenceIndex == 0)
	{
		sequenceIndex = getSequenceLength() - 1;
	}
	else
	{
		sequenceIndex--;
	}
	firstUpdate = false;
}


RECT SpriteX::getFrameRect(int frameIndex)
{
	int top=frameData[frameIndex][FRAME_TOP_POS_BIT];
	int bottom=frameData[frameIndex][FRAME_BOTTOM_POS_BIT];
	int left=frameData[frameIndex][FRAME_LEFT_POS_BIT];
	int right=frameData[frameIndex][FRAME_RIGHT_POS_BIT];

	RECT rect;
	SetRect(&rect,left,top,right,bottom);
	int width=rect.right-rect.left;
	int height=rect.bottom-rect.top;

	int cx = - rect.left;
	int cy = - rect.top;

	int actionTransform = getActionTransform();
	//adjust coordinate
	switch (actionTransform) 
	{
	case TRANS_NONE:
		//null
		break;
	case TRANS_ROT90:
		rect.left = - (height - cy);
		rect.top = - cx;
		break;
	case TRANS_ROT180:
		rect.left = - (width - cx);
		rect.top = - (height - cy);
		break;
	case TRANS_ROT270:
		rect.left = - cy;
		rect.top = - (width - cx);
		break;
	case TRANS_MIRROR:
		rect.left = - (width - cx);
		break;
	case TRANS_MIRROR_ROT90:
		rect.left = - (height - cy);
		rect.top = - (width - cx);
		break;
	case TRANS_MIRROR_ROT180:
		rect.top = - (height - cy);
		break;
	case TRANS_MIRROR_ROT270:
		rect.left = - cy;
		rect.top = - cx;
		break;
	}

	if ( (actionTransform & INVERTED_AXES) != 0) 
	{
		rect.right=rect.left+height;
		rect.bottom=rect.top+width;
	}
	else 
	{
		rect.right=rect.left+width;
		rect.bottom=rect.top+height;
	}

	D3DXMATRIX mat=getWorldTransform();
	VSAabb aabb;
	aabb.Set(D3DXVECTOR2(rect.left,rect.top),D3DXVECTOR2(rect.right,rect.bottom));
	aabb.Construct(aabb,mat);

	SetRect(&rect,aabb.vcMin.x+0.5f,aabb.vcMin.y+0.5f,aabb.vcMax.x+0.5f,aabb.vcMax.y+0.5f);

	return rect;
}

int SpriteX::getFrameWidth(int frameIndex)
{
	RECT rect=getFrameRect(frameIndex);
	return rect.right-rect.left;
}

int SpriteX::getFrameHeight(int frameIndex)
{
	RECT rect=getFrameRect(frameIndex);
	return rect.bottom-rect.top;
}

RECT SpriteX::getFrameRect()
{
	int frameIndex = getSequenceFrame();
	return getFrameRect(frameIndex);
}

int SpriteX::getFrameWidth()
{
	int frameIndex = getSequenceFrame();
	return getFrameWidth(frameIndex);
}
int SpriteX::getFrameHeight()
{
	int frameIndex = getSequenceFrame();
	return getFrameHeight(frameIndex);
}


void SpriteX::setDelay(int delay)
{
	this->delay = delay;
}

int SpriteX::getDelay()
{
	return this->delay;
}

bool SpriteX::isDelay()
{
	if (actionData[actionIndex][ACTION_SEQUENCE_DELAY_BIT] == 1)
		return true;
	else
		return false;
}

int SpriteX::getDelayTime()
{
	return actionData[actionIndex][ACTION_HEADER_SIZE + sequenceIndex * 2 + 1];
}


D3DXVECTOR2 SpriteX::getReferencePoint(int frameIndex,int index)
{
	if (frameIndex < 0 && frameIndex >= frameCount)
		throw "Array Index OutOf Bound";

	int frameTileCount = frameData[frameIndex][FRAME_TILE_COUNT_BIT];
	int frameCollisionCount = frameData[frameIndex][FRAME_COLLISION_COUNT_BIT];
	int offset = FRAME_HEADER_SIZE + frameTileCount * 4 + frameCollisionCount * 4 + index * 2;
	int refX = frameData[frameIndex][offset];
	int refY = frameData[frameIndex][offset + 1];

	D3DXVECTOR2 refPoint=D3DXVECTOR2(refX,refY);
	refPoint=getActionTransformPoint(refPoint,getActionTransform());
	refPoint=getWorldTransformPoint(refPoint,getWorldTransform());
	return refPoint;
}

int SpriteX::getReferencePointCount(int frameIndex)
{
	if (frameIndex < 0 && frameIndex >= frameCount)
		throw "Array Index OutOf Bound";

	int frameReferencePointCount = frameData[frameIndex][FRAME_REFERENCE_POINT_COUNT_BIT];
	return frameReferencePointCount;
}

D3DXVECTOR2 SpriteX::getReferencePoint(int index)
{
	int frameIndex = getSequenceFrame();
	return getReferencePoint(frameIndex,index);
}

int SpriteX::getReferencePointCount()
{
	int frameIndex = getSequenceFrame();
	return getReferencePointCount(frameIndex);
}


int SpriteX::getActionTransform()
{
	return actionData[actionIndex][ACTION_TRANSFORM_BIT];
}

D3DXMATRIX SpriteX::getWorldTransform()
{
	D3DXMATRIX flipMatrix;
	D3DXMATRIX scaleMatrix; 
	D3DXMATRIX rotateMatrix;
	D3DXMATRIX transMatrix;
	D3DXMATRIX matMatrix;

	//翻转图片
	D3DXMatrixIdentity(&flipMatrix);
	flipMatrix._11=flipX;
	flipMatrix._22=flipY;
	//放缩图片
	D3DXMatrixScaling(&scaleMatrix, scaleX, scaleY, 1);
	//旋转图片
	D3DXMatrixRotationZ(&rotateMatrix,rotation*D3DX_PI/180.0f);
	// 平移图片到我们的指定位置
	D3DXMatrixTranslation(&transMatrix, x, y, 0);
	// 生成图片大小位置转换的矩阵
	matMatrix = flipMatrix*scaleMatrix*rotateMatrix*transMatrix;


	//局部坐标系
	/*D3DXVECTOR3 local_oxy=D3DXVECTOR3(0,0,0);
	D3DXVECTOR3 local_dir_x=D3DXVECTOR3(1,0,0);
	D3DXVECTOR3 local_dir_y=D3DXVECTOR3(0,1,0);
	D3DXVECTOR3 local_dir_z=D3DXVECTOR3(0,0,1);

	D3DXVec3TransformCoord(&local_oxy,&local_oxy,&matMatrix);
	D3DXVec3TransformNormal(&local_dir_x,&local_dir_x,&matMatrix);
	D3DXVec3TransformNormal(&local_dir_y,&local_dir_y,&matMatrix);
	D3DXVec3TransformNormal(&local_dir_z,&local_dir_z,&matMatrix);

	D3DXMATRIX local_mat;
	local_mat._11=local_dir_x.x;local_mat._12=local_dir_x.y;local_mat._13=local_dir_x.z;local_mat._14=0;
	local_mat._21=local_dir_y.x;local_mat._22=local_dir_y.y;local_mat._23=local_dir_y.z;local_mat._24=0;
	local_mat._31=local_dir_z.x;local_mat._32=local_dir_z.y;local_mat._33=local_dir_z.z;local_mat._34=0;
	local_mat._41=local_oxy.x;  local_mat._42=local_oxy.y;  local_mat._43=local_oxy.z;  local_mat._44=1;*/

	return matMatrix;
}

D3DXVECTOR2 SpriteX::getActionTransformPoint(D3DXVECTOR2 point, int transform)
{
	D3DXVECTOR2 transPoint;
	switch (transform)
	{
		case TRANS_NONE:
			transPoint.x=point.x;
			transPoint.y=point.y;
			break;
		case TRANS_ROT90:
			transPoint.x=-point.y;
			transPoint.y=point.x;
			break;
		case TRANS_ROT180:
			transPoint.x=-point.x;
			transPoint.y=-point.y;
			break;
		case TRANS_ROT270:
			transPoint.x=point.y;
			transPoint.y=-point.x;
			break;
		case TRANS_MIRROR:
			transPoint.x=-point.x;
			transPoint.y=point.y;
			break;
		case TRANS_MIRROR_ROT90:
			transPoint.x=-point.y;
			transPoint.y=-point.x;
			break;
		case TRANS_MIRROR_ROT180:
			transPoint.x=point.x;
			transPoint.y=-point.y;
			break;
		case TRANS_MIRROR_ROT270:
			transPoint.x=point.y;
			transPoint.y=point.x;
			break;
	}
	return transPoint;
}

D3DXVECTOR2 SpriteX::getWorldTransformPoint(D3DXVECTOR2 point, D3DXMATRIX &worldMat)
{
	D3DXVec2TransformCoord(&point,&point,&worldMat);
	return point;
}


VSAabb SpriteX::getCollidesAabb(int frameIndex, int index)
{
	VSObb obb=getCollidesObb(frameIndex,index);
	VSAabb aabb;
	aabb.Construct(obb);
	return aabb;
}

VSObb SpriteX::getCollidesObb(int frameIndex, int index)
{
	if (index < 0 || index >= frameData[frameIndex][FRAME_COLLISION_COUNT_BIT])
		throw "Array Index OutOf Bounds";

	RECT rect;
	int offset = FRAME_HEADER_SIZE + frameData[frameIndex][FRAME_TILE_COUNT_BIT] * 4 + index * 4;
	rect.left=frameData[frameIndex][offset+0];
	rect.top=frameData[frameIndex][offset+1];
	rect.right=rect.left+frameData[frameIndex][offset+2];
	rect.bottom=rect.top+frameData[frameIndex][offset+3];

	int width=rect.right-rect.left;
	int height=rect.bottom-rect.top;

	int cx = - rect.left;
	int cy = - rect.top;

	int actionTransform = getActionTransform();
	//adjust coordinate
	switch (actionTransform) 
	{
	case TRANS_NONE:
		//null
		break;
	case TRANS_ROT90:
		rect.left = - (height - cy);
		rect.top = - cx;
		break;
	case TRANS_ROT180:
		rect.left = - (width - cx);
		rect.top = - (height - cy);
		break;
	case TRANS_ROT270:
		rect.left = - cy;
		rect.top = - (width - cx);
		break;
	case TRANS_MIRROR:
		rect.left = - (width - cx);
		break;
	case TRANS_MIRROR_ROT90:
		rect.left = - (height - cy);
		rect.top = - (width - cx);
		break;
	case TRANS_MIRROR_ROT180:
		rect.top = - (height - cy);
		break;
	case TRANS_MIRROR_ROT270:
		rect.left = - cy;
		rect.top = - cx;
		break;
	}

	if ( (actionTransform & INVERTED_AXES) != 0) 
	{
		rect.right=rect.left+height;
		rect.bottom=rect.top+width;
	}
	else 
	{
		rect.right=rect.left+width;
		rect.bottom=rect.top+height;
	}

	D3DXMATRIX mat=getWorldTransform();
	VSObb obb;
	obb.Set(D3DXVECTOR2((rect.left+rect.right)/2.0,(rect.top+rect.bottom)/2.0),
		D3DXVECTOR2(1,0),D3DXVECTOR2(0,1),D3DXVECTOR2((rect.right-rect.left)/2.0,(rect.bottom-rect.top)/2.0));
	obb.Construct(obb,mat);

	return obb;
}

int SpriteX::getCollidesCount(int frameIndex)
{
	return frameData[frameIndex][FRAME_COLLISION_COUNT_BIT];
}

VSAabb SpriteX::getCollidesAabb(int index)
{
	int frameIndex = getSequenceFrame();
	return getCollidesAabb(frameIndex,index);
}

VSObb SpriteX::getCollidesObb(int index)
{
	int frameIndex = getSequenceFrame();
	return getCollidesObb(frameIndex,index);
}

int SpriteX::getCollidesCount()
{
	int frameIndex = getSequenceFrame();
	return getCollidesCount(frameIndex);
}

bool SpriteX::collidesWith(float dest_x,float dest_y,int thisColIndex,int type)
{
	if (!this->visible)
		return false;
	
	if (this->getCollidesCount() == 0)
		return false;

	if (type==COLLISION_AABB)
	{
		VSAabb thisAabb=this->getCollidesAabb(thisColIndex);
		if (thisAabb.Intersects(D3DXVECTOR2(dest_x,dest_y)))
		{
			return true;
		}
		return false;
	}
	else if (type==COLLISION_OBB)
	{
		VSObb thisObb=this->getCollidesObb(thisColIndex);
		if (thisObb.Intersects(D3DXVECTOR2(dest_x,dest_y)))
		{
			return true;
		}
		return false;
	}
}

bool SpriteX::collidesWith(RECT destRect,int thisColIndex,int type)
{
	if (!this->visible)
		return false;

	if (this->getCollidesCount() == 0)
		return false;

	if (type==COLLISION_AABB)
	{
		VSAabb thisAabb=this->getCollidesAabb(thisColIndex);
		VSAabb destAabb;
		destAabb.Set(D3DXVECTOR2(destRect.left,destRect.top),D3DXVECTOR2(destRect.right,destRect.bottom));
		if (thisAabb.Intersects(destAabb))
		{
			return true;
		}
		return false;
	}
	else if (type==COLLISION_OBB)
	{
		VSObb thisObb=this->getCollidesObb(thisColIndex);
		VSObb destObb;
		destObb.Set(D3DXVECTOR2((destRect.left+destRect.right)/2.0,(destRect.top+destRect.bottom)/2.0),
			D3DXVECTOR2(1,0),D3DXVECTOR2(0,1),D3DXVECTOR2((destRect.right-destRect.left)/2.0,(destRect.bottom-destRect.top)/2.0));
		if (thisObb.Intersects(destObb))
		{
			return true;
		}
		return false;
	}
}

bool SpriteX::collidesWith(D3DXVECTOR2 destPoints[4],int thisColIndex,int type)
{
	if (!this->visible)
		return false;

	if (this->getCollidesCount() == 0)
		return false;

	D3DXVECTOR2 center=D3DXVECTOR2(0,0);
	for (int i=0;i<4;i++)
	{
		center.x+=destPoints[i].x;
		center.y+=destPoints[i].y;
	}
	center/=4;

	D3DXVECTOR2 dirX=destPoints[1]-destPoints[0];
	D3DXVECTOR2 dirY=destPoints[3]-destPoints[0];

	float halfWid=D3DXVec2Length(&dirX)/2.0;
	float halfHei=D3DXVec2Length(&dirY)/2.0;

	D3DXVec2Normalize(&dirX,&dirX);
	D3DXVec2Normalize(&dirY,&dirY);

	if (type==COLLISION_AABB)
	{
		VSAabb thisAabb=this->getCollidesAabb(thisColIndex);
		VSObb thisObb;
		thisObb.Construct(thisAabb);
		VSObb destObb;
		destObb.Set(center,dirX,dirY,D3DXVECTOR2(halfWid,halfHei));
		if (thisObb.Intersects(destObb))
		{
			return true;
		}
		return false;
	}
	else if (type==COLLISION_OBB)
	{
		VSObb thisObb=this->getCollidesObb(thisColIndex);
		VSObb destObb;
		destObb.Set(center,dirX,dirY,D3DXVECTOR2(halfWid,halfHei));
		if (thisObb.Intersects(destObb))
		{
			return true;
		}
		return false;
	}
}

bool SpriteX::collidesWith(SpriteX *spx,int spxColIndex,int thisColIndex,int type)
{
	if (!spx->visible || !this->visible)
		return false;
	
	if (this->getCollidesCount() == 0 || spx->getCollidesCount() == 0)
		return false;
	
	if (type==COLLISION_AABB)
	{
		VSAabb thisAabb=this->getCollidesAabb(thisColIndex);
		VSAabb spxAabb=spx->getCollidesAabb(spxColIndex);
		if (thisAabb.Intersects(spxAabb))
		{
			return true;
		}
		return false;
	}
	else if (type==COLLISION_OBB)
	{
		VSObb thisObb=this->getCollidesObb(thisColIndex);
		VSObb spxObb=spx->getCollidesObb(spxColIndex);
		if (thisObb.Intersects(spxObb))
		{
			return true;
		}
		return false;
	}
}

bool SpriteX::collidesWith(ID3DXSprite *sp,RECT &pSrcRect,D3DXVECTOR2 &pCenter,D3DXVECTOR2 &pPosition,int thisColIndex,int type)
{
	if (!this->visible)
		return false;

	if (this->getCollidesCount() == 0)
		return false;

	D3DXMATRIX mat;
	sp->GetTransform(&mat);

	if (D3DXMatrixIsIdentity(&mat))
	{
		int width=pSrcRect.right-pSrcRect.left;
		int height=pSrcRect.bottom-pSrcRect.top;
		RECT rect;
		rect.left=pPosition.x-pCenter.x+0.5;
		rect.right=rect.left+width+0.5;
		rect.top=pPosition.y-pCenter.y+0.5;
		rect.bottom=rect.top+height+0.5;

		if (collidesWith(rect,thisColIndex,type))
		{
			return true;
		}
		return false;
	}
	else
	{
		int width=pSrcRect.right-pSrcRect.left;
		int height=pSrcRect.bottom-pSrcRect.top;
		D3DXVECTOR2 points[4];
		points[0]=D3DXVECTOR2(pPosition.x-pCenter.x,pPosition.y-pCenter.y);
		points[1]=D3DXVECTOR2(pPosition.x+(width-pCenter.x),pPosition.y-pCenter.y);
		points[2]=D3DXVECTOR2(pPosition.x+(width-pCenter.x),pPosition.y+(height-pCenter.y));
		points[3]=D3DXVECTOR2(pPosition.x-pCenter.x,pPosition.y+(height-pCenter.y));

		D3DXVec2TransformCoord(&points[0],&points[0],&mat);
		D3DXVec2TransformCoord(&points[1],&points[1],&mat);
		D3DXVec2TransformCoord(&points[2],&points[2],&mat);
		D3DXVec2TransformCoord(&points[3],&points[3],&mat);
		
		if (collidesWith(points,thisColIndex,type))
		{
			return true;
		}
		return false;
	}
}


void SpriteX::removeAllSpx()
{
	vector<SpriteX*>::iterator iter;
	for (iter=spxManager.begin();iter!=spxManager.end();iter++)
	{
		delete (*iter);
	}
	spxManager.clear();
}

void SpriteX::addSpxToManage(SpriteX *spx)
{
	spxManager.push_back(spx);
}


SpriteX::~SpriteX(void)
{
	this;
	for (int i = 0; i < actionCount; i++)
	{
		delete[]actionData[i];
	}
	delete[]actionData;

	for (int i = 0; i < frameCount; i++)
	{
		delete[]frameData[i];
	}
	delete[]frameData;


// 	for (int i = 0; i < tileCount; i++)
// 	{
// 		if (tiles != NULL)
// 		{
// 			if (tiles[i] != NULL)
// 				tiles[i]->Release();
// 		}
// 
// 		delete[]tileData[i];
// 	}
// 
// 	if (tiles != NULL)
// 		delete[]tiles;
// 
// 
// 
// 	 delete[]tileData;
// 	 delete[]tileUseCounter;


	
	m_pVertexBuffer->Release();
	image->Release();

	map<int,vector<DrawParam>>::iterator iter;
	for (iter=m_drawArray.begin();iter!=m_drawArray.end();iter++)
		(*iter).second.clear();
	m_drawArray.clear();

	delete m_rectangle;
	delete m_circle;
	delete m_polygon;
	delete m_text;
}


/************************************************************************/
/* 数学函数                                                             */
/************************************************************************/
/************************************************************************/
/* AABB类                                                               */
/************************************************************************/
void VSAabb::Set(const D3DXVECTOR2 &_vcMin, const D3DXVECTOR2 &_vcMax)
{
	vcMin = _vcMin;
	vcMax = _vcMax;
	vcCenter = (vcMax + vcMin) / 2.0f;
}

void VSAabb::Construct(const VSAabb &pAABB,const D3DXMATRIX &m)
{
	D3DXVECTOR2 transVecPos[4];
	transVecPos[0]=pAABB.vcMin;
	transVecPos[1]=D3DXVECTOR2(pAABB.vcMax.x,pAABB.vcMin.y);
	transVecPos[2]=pAABB.vcMax;
	transVecPos[3]=D3DXVECTOR2(pAABB.vcMin.x,pAABB.vcMax.y);

	D3DXVec2TransformCoord(&transVecPos[0],&transVecPos[0],&m);
	D3DXVec2TransformCoord(&transVecPos[1],&transVecPos[1],&m);
	D3DXVec2TransformCoord(&transVecPos[2],&transVecPos[2],&m);
	D3DXVec2TransformCoord(&transVecPos[3],&transVecPos[3],&m);


	D3DXVECTOR2 Min = transVecPos[0];
	D3DXVECTOR2 Max = transVecPos[0];

	for(int i=0;i<4;i++)
	{
		if(Max.x < transVecPos[i].x)
			Max.x = transVecPos[i].x;

		if(Max.y < transVecPos[i].y)
			Max.y = transVecPos[i].y;

		if(Min.x > transVecPos[i].x)
			Min.x = transVecPos[i].x;

		if(Min.y > transVecPos[i].y)
			Min.y = transVecPos[i].y;
	}
	this->vcMin.x = Min.x;
	this->vcMin.y = Min.y;

	this->vcMax.x = Max.x;
	this->vcMax.y = Max.y;

	this->vcCenter.x = (Max.x + Min.x)/2;
	this->vcCenter.y = (Max.y + Min.y)/2;
}

void VSAabb::Construct(const VSObb &pObb) 
{
	D3DXVECTOR2 vcA0, vcA1;

	vcA0 = pObb.vcA0 * pObb.fA0;//x轴
	vcA1 = pObb.vcA1 * pObb.fA1;//y轴

	D3DXVECTOR2 vcPos[4];
	vcPos[0]=-vcA1-vcA0;
	vcPos[1]=-vcA1+vcA0;
	vcPos[2]=vcA1+vcA0;
	vcPos[3]=vcA1-vcA0;

	D3DXVECTOR2 Min = vcPos[0];
	D3DXVECTOR2 Max = vcPos[0];

	for(int i=0;i<4;i++)
	{
		if(Max.x < vcPos[i].x)
			Max.x = vcPos[i].x;

		if(Max.y < vcPos[i].y)
			Max.y = vcPos[i].y;

		if(Min.x > vcPos[i].x)
			Min.x = vcPos[i].x;

		if(Min.y > vcPos[i].y)
			Min.y = vcPos[i].y;
	}

	this->vcMax=Max+pObb.vcCenter;
	this->vcMin=Min+pObb.vcCenter;
}

bool VSAabb::Intersects(const D3DXVECTOR2 &vc0) 
{
	if ( vc0.x > vcMax.x ) return false;
	if ( vc0.y > vcMax.y ) return false;
	if ( vc0.x < vcMin.x ) return false;
	if ( vc0.y < vcMin.y ) return false;
	return true;
}

bool VSAabb::Intersects(const VSAabb &aabb) 
{
	if ((vcMin.x > aabb.vcMax.x) || (aabb.vcMin.x > vcMax.x))
		return false;
	if ((vcMin.y > aabb.vcMax.y) || (aabb.vcMin.y > vcMax.y))
		return false;
	return true;
}

/************************************************************************/
/* OBB类                                                                */
/************************************************************************/
void VSObb::Set(const D3DXVECTOR2 &_center,const D3DXVECTOR2 &_dirX,const D3DXVECTOR2 &_dirY,D3DXVECTOR2 &_halfSize)
{
	vcCenter=_center;
	vcA0=_dirX;
	vcA1=_dirY;
	fA0=_halfSize.x;
	fA1=_halfSize.y;
}

void VSObb::Construct(const VSAabb &pAABB)
{
	D3DXVECTOR2 vMax=pAABB.vcMax;
	D3DXVECTOR2 vMin=pAABB.vcMin;

	//分别对应x,y,z轴
	this->fA0=(vMax.x-vMin.x)/2;
	this->fA1=(vMax.y-vMin.y)/2;
	this->vcA0=D3DXVECTOR2(1.0f,0.0f);
	this->vcA1=D3DXVECTOR2(0.0f,1.0f);
	this->vcCenter.x=(vMax.x+vMin.x)/2;
	this->vcCenter.y=(vMax.y+vMin.y)/2;
}

void VSObb::Construct(const VSObb &obb,const D3DXMATRIX &m)
{
	D3DXMATRIX mat = m;

	// 旋转中心点和2个方向轴
	D3DXVec2TransformCoord(&this->vcCenter,&obb.vcCenter,&mat);
	D3DXVec2TransformNormal(&this->vcA0,&(obb.vcA0*obb.fA0),&mat);
	D3DXVec2TransformNormal(&this->vcA1,&(obb.vcA1*obb.fA1),&mat);

	this->fA0=D3DXVec2Length(&this->vcA0);
	this->fA1=D3DXVec2Length(&this->vcA1);

	//将轴方向单位化
	D3DXVec2Normalize(&this->vcA0,&this->vcA0);
	D3DXVec2Normalize(&this->vcA1,&this->vcA1);
}

bool VSObb::Intersects(const D3DXVECTOR2 &vc0)
{
	D3DXVECTOR2 vcA0, vcA1;

	vcA0 = this->vcA0 * this->fA0;//x轴
	vcA1 = this->vcA1 * this->fA1;//y轴

	D3DXVECTOR2 vcPos[4];
	vcPos[0]=-vcA1-vcA0+vcCenter;
	vcPos[1]=-vcA1+vcA0+vcCenter;
	vcPos[2]=vcA1+vcA0+vcCenter;
	vcPos[3]=vcA1-vcA0+vcCenter;

	int i, j;
	bool c=false;
	for (i = 0, j = 4-1; i < 4; j = i++) {
		if ( ((vcPos[i].y>vc0.y) != (vcPos[j].y>vc0.y)) &&
			(vc0.x < (vcPos[j].x-vcPos[i].x) * (vc0.y-vcPos[i].y) / (vcPos[j].y-vcPos[i].y) + vcPos[i].x))
			c = !c;
	}
	return c;
}

bool VSObb::Intersects(const VSObb &Obb)
{
	float T[2];

	D3DXVECTOR2 vcD = Obb.vcCenter - this->vcCenter;

	float matM[2][2];
	float ra,rb,t;

	//obb的a0,a1投影到this的a0轴上
	matM[0][0] = D3DXVec2Dot(&this->vcA0,&Obb.vcA0);
	matM[0][1] = D3DXVec2Dot(&this->vcA0,&Obb.vcA1);
	ra   = this->fA0;
	rb   = Obb.fA0 * fabs(matM[0][0]) + 
		Obb.fA1 * fabs(matM[0][1]);
	T[0] = D3DXVec2Dot(&vcD,&this->vcA0);
	t    = fabs(T[0]);
	if(t > (ra + rb) ) 
		return false;

	//obb的a0,a1投影到this的a1轴上
	matM[1][0] = D3DXVec2Dot(&this->vcA1,&Obb.vcA0);
	matM[1][1] = D3DXVec2Dot(&this->vcA1,&Obb.vcA1);
	ra   = this->fA1;
	rb   = Obb.fA0 * fabs(matM[1][0]) + 
		Obb.fA1 * fabs(matM[1][1]);
	T[1] = D3DXVec2Dot(&vcD,&this->vcA1);
	t    = fabs(T[1]);
	if(t > (ra + rb) ) 
		return false;

	//this的a0,a1投影到obb的a0轴上
	ra = this->fA0 * fabs(matM[0][0]) + 
		this->fA1 * fabs(matM[1][0]);
	rb = Obb.fA0;
	t = fabs( T[0]*matM[0][0] + T[1]*matM[1][0] );
	if(t > (ra + rb) )
		return false;

	//this的a0,a1投影到obb的a1轴上
	ra = this->fA0 * fabs(matM[0][1]) + 
		this->fA1 * fabs(matM[1][1]);
	rb = Obb.fA1;
	t = fabs( T[0]*matM[0][1] + T[1]*matM[1][1] );
	if(t > (ra + rb) )
		return false;

	return true;
}

/************************************************************************/
/* 绘图函数                                                             */
/************************************************************************/
/************************************************************************/
/* 点                                                                   */
/************************************************************************/
DXPoint::DXPoint(LPDIRECT3DDEVICE9 pd3dDevice):DXShape(pd3dDevice)
{
	m_pd3dDevice->CreateVertexBuffer(sizeof(CUSTOMVERTEX_RHW),
		D3DUSAGE_WRITEONLY,CUSTOMVERTEX_RHW::FVF_Flags,D3DPOOL_MANAGED,&m_pVertexBuffer,NULL);

}
void DXPoint::draw(D3DXVECTOR2 point,float size,DWORD color)
{
	CUSTOMVERTEX_RHW *pVertices;
	m_pVertexBuffer->Lock(0,sizeof(CUSTOMVERTEX_RHW),(void **)&pVertices,0);
	pVertices[0].x=point.x;
	pVertices[0].y=point.y;
	pVertices[0].z=0.0f;
	pVertices[0].rhw=1.0f;
	pVertices[0].color=color;
	m_pVertexBuffer->Unlock();

	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1 );
	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_DIFFUSE );

	m_pd3dDevice->SetRenderState( D3DRS_POINTSIZE,FtoDW(size));

	m_pd3dDevice->SetStreamSource(0,m_pVertexBuffer,0,sizeof(CUSTOMVERTEX_RHW));
	m_pd3dDevice->SetFVF(CUSTOMVERTEX_RHW::FVF_Flags);
	m_pd3dDevice->DrawPrimitive(D3DPT_POINTLIST,0,1);
}

/************************************************************************/
/* 直线                                                                 */
/************************************************************************/
DXLine::DXLine(LPDIRECT3DDEVICE9 pd3dDevice):DXShape(pd3dDevice)
{
	m_pd3dDevice->CreateVertexBuffer(2*sizeof(CUSTOMVERTEX_RHW),
		D3DUSAGE_WRITEONLY,CUSTOMVERTEX_RHW::FVF_Flags,D3DPOOL_MANAGED,&m_pVertexBuffer,NULL);
}
void DXLine::draw(D3DXVECTOR2 startPoint,D3DXVECTOR2 endPoint,DWORD color)
{
	CUSTOMVERTEX_RHW *pVertices;
	m_pVertexBuffer->Lock(0,2*sizeof(CUSTOMVERTEX_RHW),(void **)&pVertices,0);
	pVertices[0].x=startPoint.x;
	pVertices[0].y=startPoint.y;
	pVertices[0].z=0.0f;
	pVertices[0].rhw=1.0f;
	pVertices[0].color=color;

	pVertices[1].x=endPoint.x;
	pVertices[1].y=endPoint.y;
	pVertices[1].z=0.0f;
	pVertices[1].rhw=1.0f;
	pVertices[1].color=color;
	m_pVertexBuffer->Unlock();

	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1 );
	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_DIFFUSE );

	m_pd3dDevice->SetStreamSource(0,m_pVertexBuffer,0,sizeof(CUSTOMVERTEX_RHW));
	m_pd3dDevice->SetFVF(CUSTOMVERTEX_RHW::FVF_Flags);
	m_pd3dDevice->DrawPrimitive(D3DPT_LINELIST,0,1);
}

/************************************************************************/
/* 射线                                                                 */
/************************************************************************/
DXArrowLine::DXArrowLine(LPDIRECT3DDEVICE9 pd3dDevice):DXShape(pd3dDevice)
{
	m_pd3dDevice->CreateVertexBuffer(6*sizeof(CUSTOMVERTEX_RHW),
		D3DUSAGE_WRITEONLY,CUSTOMVERTEX_RHW::FVF_Flags,D3DPOOL_MANAGED,&m_pVertexBuffer,NULL);
}
void DXArrowLine::draw(D3DXVECTOR2 startPoint,D3DXVECTOR2 endPoint,DWORD color)
{
	D3DXVECTOR2 ds=endPoint-startPoint;
	float da=0;
	if (ds.x==0)
	{
		if (ds.y<0)
			da=D3DX_PI/2;
		else if (ds.y>0)
			da=D3DX_PI/2*3;
		else
			da=0;
	}
	else if (ds.x>0)
	{
		if (ds.y<=0)
			da=-atan(ds.y/ds.x);
		else
			da=D3DX_PI*2-atan(ds.y/ds.x);
	}
	else
	{
		da=D3DX_PI-atan(ds.y/ds.x);
	}

	float upAng=da+D3DX_PI-D3DX_PI/180*30;
	float downAng=da+D3DX_PI+D3DX_PI/180*30;


	CUSTOMVERTEX_RHW *pVertices;
	m_pVertexBuffer->Lock(0,6*sizeof(CUSTOMVERTEX_RHW),(void **)&pVertices,0);
	pVertices[0].x=startPoint.x;
	pVertices[0].y=startPoint.y;
	pVertices[0].z=0.5f;
	pVertices[0].rhw=1.0f;
	pVertices[0].color=color;

	pVertices[1].x=endPoint.x;
	pVertices[1].y=endPoint.y;
	pVertices[1].z=0.5f;
	pVertices[1].rhw=1.0f;
	pVertices[1].color=color;

	pVertices[2].x=endPoint.x;
	pVertices[2].y=endPoint.y;
	pVertices[2].z=0.5f;
	pVertices[2].rhw=1.0f;
	pVertices[2].color=color;

	pVertices[3].x=endPoint.x+cos(upAng)*15;
	pVertices[3].y=endPoint.y-sin(upAng)*15;
	pVertices[3].z=0.5f;
	pVertices[3].rhw=1.0f;
	pVertices[3].color=color;

	pVertices[4].x=endPoint.x;
	pVertices[4].y=endPoint.y;
	pVertices[4].z=0.5f;
	pVertices[4].rhw=1.0f;
	pVertices[4].color=color;

	pVertices[5].x=endPoint.x+cos(downAng)*15;
	pVertices[5].y=endPoint.y-sin(downAng)*15;
	pVertices[5].z=0.5f;
	pVertices[5].rhw=1.0f;
	pVertices[5].color=color;


	m_pVertexBuffer->Unlock();

	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1 );
	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_DIFFUSE );

	m_pd3dDevice->SetStreamSource(0,m_pVertexBuffer,0,sizeof(CUSTOMVERTEX_RHW));
	m_pd3dDevice->SetFVF(CUSTOMVERTEX_RHW::FVF_Flags);
	m_pd3dDevice->DrawPrimitive(D3DPT_LINELIST,0,3);
}

/************************************************************************/
/* 矩形                                                                 */
/************************************************************************/
DXRectangle::DXRectangle(LPDIRECT3DDEVICE9 pd3dDevice):DXShape(pd3dDevice)
{
	m_pd3dDevice->CreateVertexBuffer(5*sizeof(CUSTOMVERTEX_RHW),
		D3DUSAGE_WRITEONLY,CUSTOMVERTEX_RHW::FVF_Flags,D3DPOOL_MANAGED,&m_pVertexBuffer,NULL);
}
void DXRectangle::draw(bool isFill,D3DXVECTOR2 point,D3DXVECTOR2 size,DWORD color)
{
	if (isFill==true)
	{
		CUSTOMVERTEX_RHW *pVertices;
		m_pVertexBuffer->Lock(0,4*sizeof(CUSTOMVERTEX_RHW),(void **)&pVertices,0);
		pVertices[0].x=point.x;
		pVertices[0].y=point.y;
		pVertices[0].z=0.0f;
		pVertices[0].rhw=1.0f;
		pVertices[0].color=color;

		pVertices[1].x=point.x+size.x;
		pVertices[1].y=point.y;
		pVertices[1].z=0.0f;
		pVertices[1].rhw=1.0f;
		pVertices[1].color=color;

		pVertices[2].x=point.x;
		pVertices[2].y=point.y+size.y;
		pVertices[2].z=0.0f;
		pVertices[2].rhw=1.0f;
		pVertices[2].color=color;

		pVertices[3].x=point.x+size.x;
		pVertices[3].y=point.y+size.y;
		pVertices[3].z=0.0f;
		pVertices[3].rhw=1.0f;
		pVertices[3].color=color;

		m_pVertexBuffer->Unlock();

		m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1 );
		m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_DIFFUSE );

		m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1 );
		m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE );

		m_pd3dDevice->SetStreamSource(0,m_pVertexBuffer,0,sizeof(CUSTOMVERTEX_RHW));
		m_pd3dDevice->SetFVF(CUSTOMVERTEX_RHW::FVF_Flags);
		m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

		m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
	}
	else
	{
		CUSTOMVERTEX_RHW *pVertices;
		m_pVertexBuffer->Lock(0,5*sizeof(CUSTOMVERTEX_RHW),(void **)&pVertices,0);
		pVertices[0].x=point.x;
		pVertices[0].y=point.y;
		pVertices[0].z=0.0f;
		pVertices[0].rhw=1.0f;
		pVertices[0].color=color;

		pVertices[1].x=point.x+size.x;
		pVertices[1].y=point.y;
		pVertices[1].z=0.0f;
		pVertices[1].rhw=1.0f;
		pVertices[1].color=color;

		pVertices[2].x=point.x+size.x;
		pVertices[2].y=point.y+size.y;
		pVertices[2].z=0.0f;
		pVertices[2].rhw=1.0f;
		pVertices[2].color=color;

		pVertices[3].x=point.x;
		pVertices[3].y=point.y+size.y;
		pVertices[3].z=0.0f;
		pVertices[3].rhw=1.0f;
		pVertices[3].color=color;

		pVertices[4].x=point.x;
		pVertices[4].y=point.y;
		pVertices[4].z=0.0f;
		pVertices[4].rhw=1.0f;
		pVertices[4].color=color;

		m_pVertexBuffer->Unlock();

		m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1 );
		m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_DIFFUSE );

		m_pd3dDevice->SetStreamSource(0,m_pVertexBuffer,0,sizeof(CUSTOMVERTEX_RHW));
		m_pd3dDevice->SetFVF(CUSTOMVERTEX_RHW::FVF_Flags);
		m_pd3dDevice->DrawPrimitive(D3DPT_LINESTRIP,0,4);
	}
}

/************************************************************************/
/* 圆                                                                   */
/************************************************************************/
DXCircle::DXCircle(LPDIRECT3DDEVICE9 pd3dDevice):DXShape(pd3dDevice)
{
	DWORD vecNum=360/perAngle+2;
	m_pd3dDevice->CreateVertexBuffer(vecNum*sizeof(CUSTOMVERTEX_RHW),
		D3DUSAGE_WRITEONLY,CUSTOMVERTEX_RHW::FVF_Flags,D3DPOOL_MANAGED,&m_pVertexBuffer,NULL);
}
void DXCircle::draw(bool isFill,D3DXVECTOR2 point,float radius,int arc,DWORD color)
{
	if (isFill==true)
	{
		DWORD vecNum=360/perAngle+2;
		CUSTOMVERTEX_RHW *pVertices;
		m_pVertexBuffer->Lock(0,vecNum*sizeof(CUSTOMVERTEX_RHW),(void **)&pVertices,0);

		pVertices[0].x=point.x;
		pVertices[0].y=point.y;
		pVertices[0].z=0.0f;
		pVertices[0].rhw=1.0f;
		pVertices[0].color=color;

		for (DWORD i=1;i<vecNum;i++)
		{
			float beta=(i-1)*perAngle*D3DX_PI/180;
			pVertices[i].x=point.x+radius*sin(beta);
			pVertices[i].y=point.y-radius*cos(beta);
			pVertices[i].z=0.0f;
			pVertices[i].rhw=1.0f;
			pVertices[i].color=color;
		}

		m_pVertexBuffer->Unlock();

		m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1 );
		m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_DIFFUSE );

		m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1 );
		m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE );

		m_pd3dDevice->SetStreamSource(0,m_pVertexBuffer,0,sizeof(CUSTOMVERTEX_RHW));
		m_pd3dDevice->SetFVF(CUSTOMVERTEX_RHW::FVF_Flags);
		m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLEFAN,0,arc/perAngle);

		m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
	}
	else
	{
		DWORD vecNum=360/perAngle+1;
		CUSTOMVERTEX_RHW *pVertices;
		m_pVertexBuffer->Lock(0,vecNum*sizeof(CUSTOMVERTEX_RHW),(void **)&pVertices,0);

		for (DWORD i=0;i<vecNum;i++)
		{
			float beta=i*perAngle*D3DX_PI/180;
			pVertices[i].x=point.x+radius*sin(beta);
			pVertices[i].y=point.y-radius*cos(beta);
			pVertices[i].z=0.0f;
			pVertices[i].rhw=1.0f;
			pVertices[i].color=color;
		}

		m_pVertexBuffer->Unlock();

		m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1 );
		m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_DIFFUSE );

		m_pd3dDevice->SetStreamSource(0,m_pVertexBuffer,0,sizeof(CUSTOMVERTEX_RHW));
		m_pd3dDevice->SetFVF(CUSTOMVERTEX_RHW::FVF_Flags);
		m_pd3dDevice->DrawPrimitive(D3DPT_LINESTRIP,0,arc/perAngle);
	}

}

/************************************************************************/
/* 多边形                                                               */
/************************************************************************/
DXPolygon::DXPolygon(LPDIRECT3DDEVICE9 pd3dDevice):DXShape(pd3dDevice)
{
	m_pd3dDevice->CreateVertexBuffer(MaxVertexNums*sizeof(CUSTOMVERTEX_RHW),
		D3DUSAGE_WRITEONLY,CUSTOMVERTEX_RHW::FVF_Flags,D3DPOOL_MANAGED,&m_pVertexBuffer,NULL);
}

void DXPolygon::draw(bool isFill,D3DXVECTOR2 points[],int pointNum,DWORD color)
{
	
	if (isFill==true)
	{
		CUSTOMVERTEX_RHW *pVertices;
		m_pVertexBuffer->Lock(0,(pointNum+2)*sizeof(CUSTOMVERTEX_RHW),(void **)&pVertices,0);

		D3DXVECTOR2 center=D3DXVECTOR2(0,0);
		for (int j=0;j<pointNum;j++)
		{
			center+=points[j];
		}
		center/=pointNum;

		pVertices[0].x=center.x;
		pVertices[0].y=center.y;
		pVertices[0].z=0.0f;
		pVertices[0].rhw=1.0f;
		pVertices[0].color=color;

		for (int i=1;i<pointNum+2-1;i++)
		{
			pVertices[i].x=points[i-1].x;
			pVertices[i].y=points[i-1].y;
			pVertices[i].z=0.0f;
			pVertices[i].rhw=1.0f;
			pVertices[i].color=color;
		}

		pVertices[pointNum+2-1].x=points[0].x;
		pVertices[pointNum+2-1].y=points[0].y;
		pVertices[pointNum+2-1].z=0.0f;
		pVertices[pointNum+2-1].rhw=1.0f;
		pVertices[pointNum+2-1].color=color;

		m_pVertexBuffer->Unlock();

		m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1 );
		m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_DIFFUSE );

		m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1 );
		m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE );

		m_pd3dDevice->SetStreamSource(0,m_pVertexBuffer,0,sizeof(CUSTOMVERTEX_RHW));
		m_pd3dDevice->SetFVF(CUSTOMVERTEX_RHW::FVF_Flags);
		m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLEFAN,0,pointNum);

		m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
	}
	else
	{
		CUSTOMVERTEX_RHW *pVertices;
		m_pVertexBuffer->Lock(0,(pointNum+1)*sizeof(CUSTOMVERTEX_RHW),(void **)&pVertices,0);
		for (int i=0;i<pointNum;i++)
		{
			pVertices[i].x=points[i].x;
			pVertices[i].y=points[i].y;
			pVertices[i].z=0.0f;
			pVertices[i].rhw=1.0f;
			pVertices[i].color=color;

		}
		pVertices[pointNum]=pVertices[0];

		m_pVertexBuffer->Unlock();

		m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1 );
		m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_DIFFUSE );

		m_pd3dDevice->SetStreamSource(0,m_pVertexBuffer,0,sizeof(CUSTOMVERTEX_RHW));
		m_pd3dDevice->SetFVF(CUSTOMVERTEX_RHW::FVF_Flags);
		m_pd3dDevice->DrawPrimitive(D3DPT_LINESTRIP,0,pointNum);
	}
}
/************************************************************************/
/* 文字                                                                 */
/************************************************************************/
DXText::DXText(LPDIRECT3DDEVICE9 pd3dDevice):m_rectangle(pd3dDevice)
{
	m_pd3dDevice=pd3dDevice;
	D3DXCreateSprite(m_pd3dDevice,&m_sprite);
	D3DXCreateFontA( m_pd3dDevice, 15, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		"黑体", &m_font );

}

void DXText::draw(bool isFill,char *string,D3DXVECTOR2 point,DWORD fontcolor,DWORD backcolor)
{
	int len=0;
	char *ch=string;
	while (*ch++!='\0')
	{
		len++;
	}

	TEXTMETRICA textMet;
	m_font->GetTextMetricsA(&textMet);

	RECT rect;
	SetRect(&rect,point.x,point.y,point.x+len*textMet.tmAveCharWidth,point.y+textMet.tmHeight);

	if (isFill)
	{
		m_rectangle.draw(true,D3DXVECTOR2(rect.left,rect.top),
			D3DXVECTOR2(rect.right-rect.left,rect.bottom-rect.top),backcolor);
	}

	m_sprite->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE );
	m_font->DrawTextA( m_sprite, string, -1, &rect, DT_LEFT|DT_TOP, fontcolor);
	m_sprite->End();

}
#pragma once
#include <d3dx9.h>
#include <mmsystem.h>
#include <vector>
#include <map>
using namespace std;

//sprite file header
const int SPX_HEADER = 0x58525053; //SPRX
//sprite class version
const int SPX_VERSION = 34; //3.3
//byte sequence
const int SPX_BYTE_SEQUENCE_JAVA = 1;
const int SPX_BYTE_SEQUENCE_C = 0;

//sprite transform type
enum SPX_Transform
{
	TRANS_NONE = 0,
	TRANS_ROT90 = 5,
	TRANS_ROT180 = 3,
	TRANS_ROT270 = 6,
	TRANS_MIRROR = 2,
	TRANS_MIRROR_ROT90 = 7,
	TRANS_MIRROR_ROT180 = 1,
	TRANS_MIRROR_ROT270 = 4,
};

//rotate bit
enum SPX_Rotate
{
	ANTICLOCKWISE_90 = 0,
	DEASIL_90 = 1,
	HORIZONTAL = 2,
	VERTICAL = 3,
};

//sprite direction
enum SPX_Direction
{
	DIRECTION_NONE = 0,
	DIRECTION_UP = 1,
	DIRECTION_DOWN = 2,
	DIRECTION_LEFT = 3,
	DIRECTION_RIGHT = 4,
};

//frame attrib
const int FRAME_HEADER_SIZE = 8;

//frame data bit
enum SPX_FRAME
{
	FRAME_TILE_COUNT_BIT = 1,
	FRAME_COLLISION_COUNT_BIT = 2,
	FRAME_REFERENCE_POINT_COUNT_BIT = 3,
	FRAME_TOP_POS_BIT = 4,
	FRAME_BOTTOM_POS_BIT = 5,
	FRAME_LEFT_POS_BIT = 6,
	FRAME_RIGHT_POS_BIT = 7,
};

//action attrib
const int ACTION_HEADER_SIZE = 4;

//action data bit
enum SPX_ACTION
{
	ACTION_SEQUENCE_LENGTH_BIT = 1,
	ACTION_SEQUENCE_DELAY_BIT = 2,
	ACTION_TRANSFORM_BIT = 3,
};

//collision type
enum SPX_COLLISION
{
	COLLISION_AABB = 1,
	COLLISION_OBB = 2,
};

const int INVERTED_AXES = 0x4;

//transfrom table
const int TRANSFORM_TABLE[8][8]=
{
	{
		TRANS_NONE,
		TRANS_MIRROR_ROT180,
		TRANS_MIRROR, TRANS_ROT180,
		TRANS_MIRROR_ROT270,
		TRANS_ROT90, TRANS_ROT270,
		TRANS_MIRROR_ROT90
	}, 
	{
		TRANS_MIRROR_ROT180,
		TRANS_NONE, TRANS_ROT180,
		TRANS_MIRROR, TRANS_ROT90,
		TRANS_MIRROR_ROT270,
		TRANS_MIRROR_ROT90,
		TRANS_ROT270
	}, 
	{
		TRANS_MIRROR, TRANS_ROT180,
		TRANS_NONE,
		TRANS_MIRROR_ROT180,
		TRANS_ROT270,
		TRANS_MIRROR_ROT90,
		TRANS_MIRROR_ROT270,
		TRANS_ROT90
	}, 
	{
		TRANS_ROT180, TRANS_MIRROR,
		TRANS_MIRROR_ROT180,
		TRANS_NONE,
		TRANS_MIRROR_ROT90,
		TRANS_ROT270, TRANS_ROT90,
		TRANS_MIRROR_ROT270
	}, 
	{
		TRANS_MIRROR_ROT270,
		TRANS_ROT270, TRANS_ROT90,
		TRANS_MIRROR_ROT90,
		TRANS_NONE, TRANS_MIRROR,
		TRANS_MIRROR_ROT180,
		TRANS_ROT180
	}, 
	{
		TRANS_ROT90,
		TRANS_MIRROR_ROT90,
		TRANS_MIRROR_ROT270,
		TRANS_ROT270,
		TRANS_MIRROR_ROT180,
		TRANS_ROT180, TRANS_NONE,
		TRANS_MIRROR
	}, 
	{
		TRANS_ROT270,
		TRANS_MIRROR_ROT270,
		TRANS_MIRROR_ROT90,
		TRANS_ROT90,
		TRANS_MIRROR, TRANS_NONE,
		TRANS_ROT180,
		TRANS_MIRROR_ROT180
	}, 
	{
		TRANS_MIRROR_ROT90,
		TRANS_ROT90, TRANS_ROT270,
		TRANS_MIRROR_ROT270,
		TRANS_ROT180,
		TRANS_MIRROR_ROT180,
		TRANS_MIRROR, TRANS_NONE
	}
};

//rotate table
const int ROTATE_TABLE[8][4]=
{
	{
		TRANS_ROT270, TRANS_ROT90,
		TRANS_MIRROR,
		TRANS_MIRROR_ROT180
	}, 
	{
		TRANS_MIRROR_ROT90,
		TRANS_MIRROR_ROT270,
		TRANS_ROT180, TRANS_NONE
	}, 
	{
		TRANS_MIRROR_ROT270,
		TRANS_MIRROR_ROT90, TRANS_NONE,
		TRANS_ROT180
	}, 
	{
		TRANS_ROT90, TRANS_ROT270,
		TRANS_MIRROR_ROT180,
		TRANS_MIRROR
	}, 
	{
		TRANS_MIRROR_ROT180,
		TRANS_MIRROR, TRANS_ROT90,
		TRANS_ROT270
	}, 
	{
		TRANS_NONE, TRANS_ROT180,
		TRANS_MIRROR_ROT270,
		TRANS_MIRROR_ROT90
	}, 
	{
		TRANS_ROT180, TRANS_NONE,
		TRANS_MIRROR_ROT90,
		TRANS_MIRROR_ROT270
	}, 
	{
		TRANS_MIRROR,
		TRANS_MIRROR_ROT180,
		TRANS_ROT270, TRANS_ROT90
	}
};

class DXRectangle;
class DXCircle;
class DXPolygon;
class DXText;

class VSAabb;
class VSObb;

class SpriteX
{
private:
	LPDIRECT3DDEVICE9 m_pd3dDevice;
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;

	struct CUSTOMVERTEX_RHW
	{
		FLOAT x, y, z,rhw;      // The untransformed, 3D position for the vertex
		DWORD color;        // The vertex color
		FLOAT tu,tv;
		enum FVF
		{
			FVF_Flags =D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1
		};
	};

	CUSTOMVERTEX_RHW	m_Vertex2D[4];

	char spxName[255];
	char imageName[255];

	short** actionData; //action data
	int actionCount; //action count

	short** frameData; //frame data
	int frameCount; //frame count

	LPDIRECT3DTEXTURE9 *tiles; //tile image
	short** tileData; //tile data
	int* tileUseCounter;
	int tileCount; //tile count

	int actionIndex; //current action
	int sequenceIndex; //current action sequence

	LPDIRECT3DTEXTURE9 image;//whole sprite image

	bool tileMode;

	char spxFileName[255];
	char spxFileExt[255];

	int delay;

	bool visible; //sprite visible
	DWORD lastTime; //last update sequence time
	bool firstUpdate; //frist update sequence
	bool disableUpdate; //disable update sequence

	bool isLoop;
	bool loopFinished;

	//transform
	float x; //sprite x position
	float y; //sprite y position

	//flip
	int flipX;
	int flipY;

	//scale
	float scaleX;
	float scaleY;

	//rotation(单位:角度)
	float rotation;

	//origin offset position
	int originOffsetX;
	int originOffsetY;

	static vector<SpriteX*> spxManager;

	//绘图
	struct DrawParam
	{
		enum TYLE
		{
			s_rect,
			s_obb,
			s_refPoint,
		}tyle;
		int frameIndex;
		int index;
		DWORD color;
		char str[255];
		D3DXVECTOR2 orignal; //中心点
		D3DXVECTOR2 points[4];
	};
	map<int,vector<DrawParam>> m_drawArray;
	DXRectangle *m_rectangle;
	DXCircle *m_circle;
	DXPolygon *m_polygon;
	DXText *m_text;
private:
	void initData();
	DWORD randomColor();
	HRESULT createImage(char *imageName,OUT LPDIRECT3DTEXTURE9 &spximg);
	void loadSpx(char* spxName, LPDIRECT3DTEXTURE9 image);
	void drawImage(LPDIRECT3DTEXTURE9 image,int x_src,int y_src,int wid_src,int hei_src,
				int transform,int x_dest,int y_dest,int wid_dest,int hei_dest);
public:
	static void removeAllSpx();
	static void addSpxToManage(SpriteX *spx);

	SpriteX(LPDIRECT3DDEVICE9 pd3dDevice,char *spxName,LPDIRECT3DTEXTURE9 image);
	SpriteX(LPDIRECT3DDEVICE9 pd3dDevice,char *spxName,LPDIRECT3DTEXTURE9 tiles[]);
	SpriteX(LPDIRECT3DDEVICE9 pd3dDevice,char *spxName, char* imageName);
	SpriteX(SpriteX &spx);
	
	/************************************************************************/
	/* Action																*/
	void initAction(int nAction);
	void releaseAction(int nAction);
	void initAllAction();
	void releaseAllAction();
	//用户调用
	void setAction(int actionIndex, bool loop=true);
	int getAction();
	int getActionCount();
	/************************************************************************/

	/************************************************************************/
	/* SequenceFrame，spriteX编辑器中动画序列                               */
	int getSequenceFrame(int sequenceIndex);
	int getSequenceFrame();
	int getSequenceLength();
	/************************************************************************/

	/************************************************************************/
	/* Frame，游戏中的动画帧												*/
	void setFrame(int sequenceIndex);
	int getFrame();
	void nextFrame();
	void prevFrame();
	//获取指定帧的位置大小
	RECT getFrameRect(int frameIndex);
	int getFrameWidth(int frameIndex);
	int getFrameHeight(int frameIndex);
	//获取当前帧的位置大小
	RECT getFrameRect();
	int getFrameWidth();
	int getFrameHeight();
	/************************************************************************/

	/************************************************************************/
	/* ReferencePoint                                                       */
	//获取指定帧的参考点
	D3DXVECTOR2 getReferencePoint(int frameIndex,int index);
	int getReferencePointCount(int frameIndex);
	//获取当前帧的参考点
	D3DXVECTOR2 getReferencePoint(int index);
	int getReferencePointCount();
	/************************************************************************/

	/************************************************************************/
	/* Transform                                                            */
	//获取动作序列变化矩阵
	int getActionTransform();
	//获取世界变化矩阵
	D3DXMATRIX getWorldTransform();
	//获取动作序列矩阵变化后的点
	D3DXVECTOR2 getActionTransformPoint(D3DXVECTOR2 point, int transform);
	//获取世界矩阵变化后的点
	D3DXVECTOR2 getWorldTransformPoint(D3DXVECTOR2 point, D3DXMATRIX &worldMat);
	/************************************************************************/

	/************************************************************************/
	/* Collides                                                             */
	//获取指定帧的碰撞区
	VSAabb getCollidesAabb(int frameIndex, int index);
	VSObb getCollidesObb(int frameIndex, int index);
	int getCollidesCount(int frameIndex);
	//获取当前帧的碰撞区
	VSAabb getCollidesAabb(int index);
	VSObb getCollidesObb(int index);
	int getCollidesCount();
	//碰撞
	bool collidesWith(float dest_x,float dest_y,int thisColIndex,int type);
	bool collidesWith(RECT destRect,int thisColIndex,int type);
	//4个点以顺时针排列
	bool collidesWith(D3DXVECTOR2 destPoints[4],int thisColIndex,int type);
	bool collidesWith(SpriteX *spx,int spxColIndex,int thisColIndex,int type);
	bool collidesWith(ID3DXSprite *sp,RECT &pSrcRect,D3DXVECTOR2 &pCenter,D3DXVECTOR2 &pPosition,int thisColIndex,int type);
	/************************************************************************/

	/************************************************************************/
	/* Delay                                                                */
	//用户自定义
	void setDelay(int delay);
	int getDelay();
	//从spriteX编辑器中读取
	bool isDelay();
	int getDelayTime();
	/************************************************************************/

	/************************************************************************/
	/* Update																*/
	void enableUpdate(bool enable);
	bool isEnableUpdate();
	void update();
	/************************************************************************/

	/************************************************************************/
	/* Draw                                                                     */
	void draw();
	void debugDraw();
	/************************************************************************/
	
	~SpriteX(void);
public:
	/////////////////////////////////////////////////////////////////////////
	char* getSpxName(){return spxName;}
	char* getImageName(){return imageName;}
	/////////////////////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////////////////////
	void setImage(LPDIRECT3DTEXTURE9 image){this->image = image;}
	LPDIRECT3DTEXTURE9 getImage(){return this->image;}
	LPDIRECT3DTEXTURE9 getImage(int index){return this->tiles[index];}
	int getImageWidth(LPDIRECT3DTEXTURE9 image)
	{
		D3DSURFACE_DESC	desc;
		image->GetLevelDesc(0,&desc);
		return desc.Width;
	}
	int getImageHeight(LPDIRECT3DTEXTURE9 image)
	{
		D3DSURFACE_DESC	desc;
		image->GetLevelDesc(0,&desc);
		return desc.Height;
	}
	/////////////////////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////////////////////
	void setX(float fx){this->x=fx;}
	int getX(){return this->x;}
	void setY(float fy){this->y=fy;}
	int getY(){return this->y;}
	void setPosition(float fx, float fy){this->x=fx;this->y=fy;}
	void move(float dx, float dy){x+=dx;y+=dy;}
	/////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////
	bool isFlipX(void){return flipX==-1;}
	void setFlipX(bool bFlipX){bFlipX==true?flipX=-1:flipX=1;}
	bool isFlipY(void){return flipY==-1;}
	void setFlipY(bool bFlipY){bFlipY==true?flipY=-1:flipY=1;}
	/////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////
	void setScale(float fScale){this->scaleX=this->scaleY=fScale;}
	void setScaleX(float fScaleX){this->scaleX=fScaleX;}
	void setScaleY(float fScaleY){this->scaleY=fScaleY;}
	/////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////
	//参数:角度
	void setRotation(float fRotation){this->rotation=fRotation;}
	/////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////
	void setAnchorPoint(int ox,int oy){originOffsetX=ox,originOffsetY=oy;}
	/////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////
	//参数:Range[0,1],待定
	void setZOrder(float zOrder)
	{
		for (int i=0;i<4;i++)
			m_Vertex2D[i].z=1.0f-zOrder;
	}
	/////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////
	void setColor(byte r, byte g, byte b)
	{
		//argb
		byte a=m_Vertex2D[0].color>>24;
		DWORD dwColor = D3DCOLOR_ARGB(a,r,g,b);
		for (int i=0;i<4;i++)
			m_Vertex2D[i].color=dwColor;
	}
	void setOpacity(byte opacity)
	{
		//argb
		DWORD dwColor = m_Vertex2D[0].color&0x00ffffff;
		dwColor=dwColor^(opacity<<24);
		for (int i=0;i<4;i++)
			m_Vertex2D[i].color=dwColor;
	}
	/////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////
	void setVisible(bool visible){this->visible=visible;}
	bool isVisible(){return this->visible;}
	/////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////
	void setLoop(bool loop){this->isLoop=loop;this->loopFinished=false;}
	bool getLoop(){return this->isLoop;}
	/////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////
	bool isPlayOver(int actionIndex)
	{
		if (this->actionIndex==actionIndex)
		{
			if (sequenceIndex >= getSequenceLength() - 1)
			{
				return true;
			}
		}
		return false;
	}
	/////////////////////////////////////////////////////////////////////////
	
};

/************************************************************************/
/* 数学函数                                                             */
/************************************************************************/
//AABB类
class VSAabb
{
public:
	D3DXVECTOR2	vcMin, vcMax; // 最大,最小边界
	D3DXVECTOR2	vcCenter;     // 中心
	//通过最大点，最小获取AABB
	void Set(const D3DXVECTOR2 &_vcMin, const D3DXVECTOR2 &_vcMax);
	//以AABB通过矩阵得到新的AABB(是否进行扩大)
	void Construct(const VSAabb &pAABB,const D3DXMATRIX &m);
	//从OBB构造AABB
	void Construct(const VSObb &pObb);
	//判断一点是否在AABB里
	bool Intersects(const D3DXVECTOR2 &vc0);
	//测试AABB与AABB相交
	bool Intersects(const VSAabb &aabb);
};

//OBB类
class VSObb
{
public:
	//分别对应x轴，y轴
	float		fA0,   fA1; // 2个半轴的长度
	D3DXVECTOR2	vcA0, vcA1; // 2个轴(单位向量),以LOACA坐标为轴
	D3DXVECTOR2	vcCenter;         // 中心点
	//通过中心点和轴构建OBB
	void Set(const D3DXVECTOR2 &_center,const D3DXVECTOR2 &_dirX,const D3DXVECTOR2 &_dirY,D3DXVECTOR2 &_halfSize);
	//从AABB构造OBB
	void Construct(const VSAabb &pAABB);
	//用给定的OBB和变换矩阵来构造OBB
	void Construct(const VSObb &obb,const D3DXMATRIX &m);
	//判断一点是否在OBB里
	bool Intersects(const D3DXVECTOR2 &vc0);
	//测试OBB与OBB相交
	bool Intersects(const VSObb &Obb);
};


/************************************************************************/
/* 绘图函数                                                             */
/************************************************************************/
class DXShape
{
protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
	LPDIRECT3DDEVICE9 m_pd3dDevice;
	struct CUSTOMVERTEX_RHW
	{
		FLOAT x, y, z,rhw;      // The untransformed, 3D position for the vertex
		DWORD color;        // The vertex color
		enum FVF
		{
			FVF_Flags =D3DFVF_XYZRHW|D3DFVF_DIFFUSE
		};
	};
public:
	DXShape(LPDIRECT3DDEVICE9 pd3dDevice){m_pd3dDevice=pd3dDevice;}
	inline DWORD FtoDW( FLOAT f ) { return *((DWORD*)&f); }
public:
	~DXShape(void){m_pVertexBuffer->Release();}
};

class DXPoint:public DXShape
{
public:
	DXPoint(LPDIRECT3DDEVICE9 pd3dDevice);
	void draw(D3DXVECTOR2 point,float size,DWORD color=0xff000000);
	~DXPoint(){}
};

class DXLine:public DXShape
{
public:
	DXLine(LPDIRECT3DDEVICE9 pd3dDevice);
	void draw(D3DXVECTOR2 startPoint,D3DXVECTOR2 endPoint,DWORD color=0xff000000);
	~DXLine(){}
};

class DXArrowLine:public DXShape
{
public:
	DXArrowLine(LPDIRECT3DDEVICE9 pd3dDevice);
	void draw(D3DXVECTOR2 startPoint,D3DXVECTOR2 endPoint,DWORD color=0xff000000);
	~DXArrowLine(){}
};

class DXRectangle:public DXShape
{
public:
	DXRectangle(LPDIRECT3DDEVICE9 pd3dDevice);
	void draw(bool isFill,D3DXVECTOR2 point,D3DXVECTOR2 size,DWORD color=0xff000000);
public:
	~DXRectangle(){}
};

class DXCircle:public DXShape
{
#define perAngle 5
public:
	DXCircle(LPDIRECT3DDEVICE9 pd3dDevice);
	void draw(bool isFill,D3DXVECTOR2 point,float radius,int arc=360,DWORD color=0xff000000);
public:
	~DXCircle(){}
};

class DXPolygon:public DXShape
{
#define MaxVertexNums 16
public:
	DXPolygon(LPDIRECT3DDEVICE9 pd3dDevice);
	void draw(bool isFill,D3DXVECTOR2 points[],int pointNum,DWORD color=0xff000000);
public:
	~DXPolygon(){}
};

class DXText
{
private:
	LPDIRECT3DDEVICE9 m_pd3dDevice;
	LPD3DXFONT m_font;
	LPD3DXSPRITE m_sprite;
	DXRectangle m_rectangle;
public:
	DXText(LPDIRECT3DDEVICE9 pd3dDevice);
	void draw(bool isFill,char *string,D3DXVECTOR2 point,DWORD fontcolor=0xffffffff,DWORD backcolor=0xff000000);
public:
	~DXText(){m_font->Release();m_sprite->Release();}
};

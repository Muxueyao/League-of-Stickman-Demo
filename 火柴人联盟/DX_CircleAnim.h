#pragma once

class DX_CircleAnim
{
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
	LPDIRECT3DTEXTURE9 m_pTextures;
	LPDIRECT3DDEVICE9 m_pd3dDevice;
	struct CUSTOMVERTEX_RHW
	{
		FLOAT x, y, z, rhw;      // The untransformed, 3D position for the vertex
		DWORD color;        // The vertex color
		FLOAT tu, tv;
		enum FVF
		{
			FVF_Flags = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1
		};
	};
	DWORD color;
	DWORD verticeNum;		//所有顶点
	float verticePerRad;    //每个顶点对应的弧度
	float totalTimer;
	float curTimer;
	bool isPlaying;
	float curVertice;
public:				
	//(精灵指针,显示X坐标，显示Y坐标，显示半径，图片路径)
	DX_CircleAnim(LPDIRECT3DDEVICE9 m_pd3dDevice, int dstX, int dstY, float radius, LPCWSTR strFilename);
	void setTotalTimer(float timer);//冷却时间
	//开始
	void play();
	//停止
	void stop();
	//冷却完毕返回真,
	bool getstate();
	//执行逻辑，带入参数为每一桢的时间，通常为0.01f
	void update(float durTime);
	~DX_CircleAnim(void);
};
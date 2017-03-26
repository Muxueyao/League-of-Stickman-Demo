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
	DWORD verticeNum;		//���ж���
	float verticePerRad;    //ÿ�������Ӧ�Ļ���
	float totalTimer;
	float curTimer;
	bool isPlaying;
	float curVertice;
public:				
	//(����ָ��,��ʾX���꣬��ʾY���꣬��ʾ�뾶��ͼƬ·��)
	DX_CircleAnim(LPDIRECT3DDEVICE9 m_pd3dDevice, int dstX, int dstY, float radius, LPCWSTR strFilename);
	void setTotalTimer(float timer);//��ȴʱ��
	//��ʼ
	void play();
	//ֹͣ
	void stop();
	//��ȴ��Ϸ�����,
	bool getstate();
	//ִ���߼����������Ϊÿһ���ʱ�䣬ͨ��Ϊ0.01f
	void update(float durTime);
	~DX_CircleAnim(void);
};
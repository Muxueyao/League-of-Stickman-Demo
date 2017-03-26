#pragma once
/** @defgroup EXAMPLES ���������
*  @author  �Է�
*  @version 1.0
*  @date    2006-11-9
*  @{
*/
class CPicture
	:public CObj
{
	/** @name ͼƬ����
	*  @{
	*/
public:
	/** �����豸 */
	LPD3DXSPRITE		pSprite;
	/** �ϲ����� */
	D3DXMATRIX matrix;
	/** ��ת���� */
	D3DXMATRIX angle_matrix;
	/** ƽ�ƾ��� */
	D3DXMATRIX pos_matrix;
	/** ���ž��� */
	D3DXMATRIX scale_matrix;
	/** ��ʾ���� */
	float x, y;
	/** ���Ų��� */
	D3DXVECTOR2 scale;
	/** ��ת���� */
	float angle;
	/** ��ת״̬ */
	bool dir;
	/** ͼƬ��� */
	int img_width;
	/** ͼƬ�߶� */
	int img_height;
	/** ��ʾ��Χ */
	RECT img_rect;
	/** ͼƬê�� */
	D3DXVECTOR3 anchor;
	/** ��ʾ��ɫ */
	D3DXCOLOR color;
	float R, G, B, A;

public:
	/** ͼƬ·�� */
	LPCWSTR img_name;
	/** ͼƬ���� */
	LPDIRECT3DTEXTURE9 pD3DTexture;
	/** ��Ⱦ���� */
	void show()=0;
	/** �߼����� */
	void update()=0;
	/** ���þ��� */
	void set_matrix();
	/** �������� */
	void Release();
	/** ������ʾRECT */
	void set_rect(float left, float top, float right, float bottum) { img_rect = { (long)left,(long)top,(long)right,(long)bottum }; }
	/** ������ʾ���� */
	void set_pos(float x, float y);
	/** ������ת���� */
	void set_angle(float angle);
	/** �������Ŵ�С */
	void set_scale(float _scale);
	/** ���õ�����˳�� */
	void set_sort(int sort) { this->sort = sort; }
	/** ����alphaֵ */
	void set_alpha(float A) { this->A = A/255; }
	/** ������ʾ��ɫ */
	void set_color(float R, float G, float B) { this->R = R/255;this->G = G/255;this->B = B/255;}
	/** ����ê�� */
	void set_anchor(D3DXVECTOR3 anchor) { this->anchor = anchor; }
	/** ��ȡͼƬ��� */
	int get_img_x() { return img_width; }
	/** ��ȡͼƬ�߶� */
	int get_img_y() { return img_height; }
	/** ����ͼ��ת */
	void set_dir(bool dir) { this->dir = dir; set_matrix(); }
	/** ��ȡ��ǰê�� */
	D3DXVECTOR3 get_anchor() { return anchor; }
	/** ���캯�� */
	CPicture(LPCWSTR imgname);
	/** �������� */
	~CPicture();
};

/** @}*/ // ͼƬ����
/** @}*/ // ���������
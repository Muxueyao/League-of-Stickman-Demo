#pragma once
/** @defgroup EXAMPLES 火柴人联盟
*  @author  赵飞
*  @version 1.0
*  @date    2006-11-9
*  @{
*/
class CPicture
	:public CObj
{
	/** @name 图片基类
	*  @{
	*/
public:
	/** 精灵设备 */
	LPD3DXSPRITE		pSprite;
	/** 合并矩阵 */
	D3DXMATRIX matrix;
	/** 旋转矩阵 */
	D3DXMATRIX angle_matrix;
	/** 平移矩阵 */
	D3DXMATRIX pos_matrix;
	/** 缩放矩阵 */
	D3DXMATRIX scale_matrix;
	/** 显示坐标 */
	float x, y;
	/** 缩放参数 */
	D3DXVECTOR2 scale;
	/** 旋转参数 */
	float angle;
	/** 翻转状态 */
	bool dir;
	/** 图片宽度 */
	int img_width;
	/** 图片高度 */
	int img_height;
	/** 显示范围 */
	RECT img_rect;
	/** 图片锚点 */
	D3DXVECTOR3 anchor;
	/** 显示颜色 */
	D3DXCOLOR color;
	float R, G, B, A;

public:
	/** 图片路径 */
	LPCWSTR img_name;
	/** 图片纹理 */
	LPDIRECT3DTEXTURE9 pD3DTexture;
	/** 渲染函数 */
	void show()=0;
	/** 逻辑函数 */
	void update()=0;
	/** 设置矩阵 */
	void set_matrix();
	/** 析构对象 */
	void Release();
	/** 设置显示RECT */
	void set_rect(float left, float top, float right, float bottum) { img_rect = { (long)left,(long)top,(long)right,(long)bottum }; }
	/** 设置显示坐标 */
	void set_pos(float x, float y);
	/** 设置旋转弧度 */
	void set_angle(float angle);
	/** 设置缩放大小 */
	void set_scale(float _scale);
	/** 设置迭代器顺序 */
	void set_sort(int sort) { this->sort = sort; }
	/** 设置alpha值 */
	void set_alpha(float A) { this->A = A/255; }
	/** 设置显示颜色 */
	void set_color(float R, float G, float B) { this->R = R/255;this->G = G/255;this->B = B/255;}
	/** 设置锚点 */
	void set_anchor(D3DXVECTOR3 anchor) { this->anchor = anchor; }
	/** 获取图片宽度 */
	int get_img_x() { return img_width; }
	/** 获取图片高度 */
	int get_img_y() { return img_height; }
	/** 设置图像翻转 */
	void set_dir(bool dir) { this->dir = dir; set_matrix(); }
	/** 获取当前锚点 */
	D3DXVECTOR3 get_anchor() { return anchor; }
	/** 构造函数 */
	CPicture(LPCWSTR imgname);
	/** 析构函数 */
	~CPicture();
};

/** @}*/ // 图片基类
/** @}*/ // 火柴人联盟
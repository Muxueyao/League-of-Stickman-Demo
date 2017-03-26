#pragma once
/** @defgroup EXAMPLES 火柴人联盟
*  @author  赵飞
*  @version 1.0
*  @date    2006-11-9
*  @{
*/

class CDie_Effect
	:public CObj
{
	/** @name 人物死亡效果
	*  @{
	*/

	/** 枚举常量_图块弹起次数 */
	enum drop_time
	{
		one,	  /**< 第一次弹起 */
		two,	  /**< 第二次弹起 */
		three,	  /**< 第三次弹起 */

	}i1_drop, i2_drop, i3_drop, i4_drop, i5_drop, i6_drop, i7_drop, i8_drop, i9_drop, i10_drop;

	/** 弹起次数完毕后隐藏开关,十张图片全部为true后删除对象 */
	bool i1s, i2s, i3s, i4s, i5s, i6s, i7s, i8s, i9s, i10s;
	/** 显示坐标 */
	float x,y;
	/** 旋转角度 */
	float angle;
	/** X坐标,Y坐标,Y速度,X速度,Y的偏移速度 */
	float i1_x, i1_y, i1_offset_y, i1_offset_x, i1_y_speed;
	/** X坐标,Y坐标,Y速度,X速度,Y的偏移速度 */
	float i2_x, i2_y, i2_offset_y, i2_offset_x, i2_y_speed;
	/** X坐标,Y坐标,Y速度,X速度,Y的偏移速度 */
	float i3_x, i3_y, i3_offset_y, i3_offset_x, i3_y_speed;
	/** X坐标,Y坐标,Y速度,X速度,Y的偏移速度 */
	float i4_x, i4_y, i4_offset_y, i4_offset_x, i4_y_speed;
	/** X坐标,Y坐标,Y速度,X速度,Y的偏移速度 */
	float i5_x, i5_y, i5_offset_y, i5_offset_x, i5_y_speed;
	/** X坐标,Y坐标,Y速度,X速度,Y的偏移速度 */
	float i6_x, i6_y, i6_offset_y, i6_offset_x, i6_y_speed;
	/** X坐标,Y坐标,Y速度,X速度,Y的偏移速度 */
	float i7_x, i7_y, i7_offset_y, i7_offset_x, i7_y_speed;
	/** X坐标,Y坐标,Y速度,X速度,Y的偏移速度 */
	float i8_x, i8_y, i8_offset_y, i8_offset_x, i8_y_speed;
	/** X坐标,Y坐标,Y速度,X速度,Y的偏移速度 */
	float i9_x, i9_y, i9_offset_y, i9_offset_x, i9_y_speed;
	/** X坐标,Y坐标,Y速度,X速度,Y的偏移速度 */
	float i10_x, i10_y, i10_offset_y, i10_offset_x, i10_y_speed;
	/** 飘移X速度 */
	float offset_x;

	/** 图块1对象 */
	CUI_img *i1;
	/** 图块2对象 */
	CUI_img *i2;
	/** 图块3对象 */
	CUI_img *i3;
	/** 图块4对象 */
	CUI_img *i4;
	/** 图块5对象 */
	CUI_img *i5;
	/** 图块6对象 */
	CUI_img *i6;
	/** 图块7对象 */
	CUI_img *i7;
	/** 图块8对象 */
	CUI_img *i8;
	/** 图块9对象 */
	CUI_img *i9;
	/** 图块10对象 */
	CUI_img *i10;
public:
	/** 逻辑函数 */
	void update();
	/** 渲染函数 */
	void show();
	/** 析构对象指针 */
	void Release();
	/** 构造函数
	*  @param file float x, float y 显示坐标
	*  @param file  LPCWSTR img1,img2...... 图块纹理
	*/
	CDie_Effect(float x, float y, LPCWSTR img1, LPCWSTR img2, LPCWSTR img3, LPCWSTR img4,
		LPCWSTR img5, LPCWSTR img6, LPCWSTR img7, LPCWSTR img8, LPCWSTR img9, LPCWSTR img10);
	/** 析构函数 */
	~CDie_Effect();
};

/** @}*/ // 人物死亡效果
/** @}*/ // 火柴人联盟
#pragma once

/** @defgroup EXAMPLES 火柴人联盟
*  @author  赵飞
*  @version 1.0
*  @date    2006-11-9
*  @{
*/
class CMoney_drop
	:public CObj
{
	/** @name 金币掉落
	*  @{
	*/

	/** 金币1图片对象 */
	CUI_img *jb1;
	/** 金币2图片对象 */
	CUI_img *jb2;
	/** 金币3图片对象 */
	CUI_img *jb3;
	/** 金币1坐标与偏移值 */
	float jb1_x, x1_speed;
	float jb1_y, y1_speed;
	/** 金币2坐标与偏移值 */
	float jb2_x, x2_speed;
	float jb2_y, y2_speed;
	/** 金币3坐标与偏移值 */
	float jb3_x, x3_speed;
	float jb3_y, y3_speed;
	/** 偏移数值 */
	float speed;
	/** 金币碰撞开关 */
	bool j1, j2, j3;
	/** 金币掉落音频 */
	CAudio4Bass		dropcoin;
	/** 拾取金币音频 */
	CAudio4Bass		money_Audio;
	/** 金币弹落次数 */
	enum jb_time
	{
		one,	 /**< 一次 */
		two,	 /**< 两次 */
		three,	 /**< 三次 */
		four,	 /**< 四次 */
	}jb1_time, jb2_time, jb3_time;
public:
	/** 渲染函数 */
	void show();
	/** 逻辑函数 */
	void update();
	/** 析构成员对象 */
	void Release();
	/** 构造函数
	*  @param file  float x, float y 显示坐标
	*/
	CMoney_drop(float x, float y);
	/** 析构函数 */
	~CMoney_drop();
};
/** @}*/ // 金币掉落
/** @}*/ // 火柴人联盟

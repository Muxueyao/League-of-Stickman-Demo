#pragma once

/** @defgroup EXAMPLES 火柴人联盟
*  @author  赵飞
*  @version 1.0
*  @date    2006-11-9
*  @{
*/

/** @name 按钮显示2
*  @{
*/
class CUI_button_2
	:public CObj
{
	/** 两张图片之间切换时间 */
	float show_time, buffer_time;
	/** 图片对象1 */
	CUI_img *img_1;
	/** 图片对象2 */
	CUI_img *img_2;
public:
	/** 析构图片1与图片2 */
	void Release();
	/** 逻辑 */
	void update();
	/** 渲染函数 */
	void show();
	/** 构造函数
	*  @param file LPCWSTR img1 图像1地址
	*  @param file LPCWSTR img2 图像2地址
	*  @param file float x		显示坐标
	*  @param file float y		显示坐标
	*  @param file float time	两张图片切换时间
	*/
	CUI_button_2(LPCWSTR img1,LPCWSTR img2,float x,float y,float time);
	/** 析构函数 */
	~CUI_button_2();
};
/** @}*/ // 按钮显示2

/** @}*/ // 火柴人联盟

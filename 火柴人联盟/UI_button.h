#pragma once
/** @defgroup EXAMPLES 火柴人联盟
*  @author  赵飞
*  @version 1.0
*  @date    2006-11-9
*  @{
*/
class CUI_button
	//:public CObj
{
	/** @name UI按钮类
	*  @{
	*/
	/** 鼠标移入图片 */
	CUI_img *mousein;
	/** 鼠标移出图片 */
	CUI_img *mouseout;
	/** 显示开关 */
	bool is_show;
	/** X坐标 */
	int x;
	/** Y坐标 */
	int y;
	/** 图片宽度 */
	int img_x;
	/** 图片高度 */
	int img_y;
	/** 点击按钮状态 */
	bool is_end;
	
public:
	/** 构造函数
	*  @param file LPCWSTR in 鼠标移入地址
	*  @param file LPCWSTR in 鼠标移出地址
	*  @param file float x	显示X坐标
	*  @param file float y	显示Y坐标
	*/
	CUI_button(LPCWSTR in,LPCWSTR out,float x,float y);
	/** 析构包含对象指针 */
	void Release();
	/** 逻辑函数 */
	void update();
	/** 获取鼠标点击状态 */
	bool get_state() { return is_end; }
	/** 设置显示状态 */
	void set_show(bool show);
	/** 获取显示 */
	bool get_show() { return is_show; }
	/** 析构函数 */
	~CUI_button();
};
/** @}*/ // UI按钮类
/** @}*/ // 火柴人联盟


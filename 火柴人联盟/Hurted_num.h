#pragma once
/** @defgroup EXAMPLES 火柴人联盟
*  @author  赵飞
*  @version 1.0
*  @date    2006-11-9
*  @{
*/
class CHurted_num
	:public CObj
{
	/** @name 图片数值显示
	*  @{
	*/
	/** 数字图片对象 */
	CUI_number *number;
	/** 其他效果图片对象 */
	CUI_img *img2;
	/** 显示的数值 */
	int num;
	/** 显示时间_后删除对象 */
	int show_time;
	/** 显示坐标 */
	float x, y;
public:
	/** 逻辑函数 */
	void update();
	/** 渲染函数 */
	void show();
	/** 析构指针对象 */
	void Release();
	/** 构造函数1 
	*  @param file LPCWSTR img_name 数值图片地址
	*  @param file int num 要显示的数值
	*  @param file float x,float y 显示的坐标
	*  @param file LPCWSTR img2 其他效果图片地址
	*/
	CHurted_num(LPCWSTR img_name,int num,float x,float y,LPCWSTR img2);
	/** 构造函数2
	*  @param file LPCWSTR img_name 数值图片地址
	*  @param file int num 要显示的数值
	*  @param file float x,float y 显示的坐标
	*/
	CHurted_num(LPCWSTR img_name, int num, float x, float y);
	/** 析构函数 */
	~CHurted_num();
};

/** @}*/ // 图片数值显示
/** @}*/ // 火柴人联盟
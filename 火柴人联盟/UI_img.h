#pragma once

/** @defgroup EXAMPLES 火柴人联盟
*  @author  赵飞
*  @version 1.0
*  @date    2006-11-9
*  @{
*/

/** @name 基础图片类
*  @{
*/
class CUI_img
	:public CPicture
{
public:
	/** 渲染函数 */
	void show();
	/** 逻辑函数 */
	void update();
	/** 游戏暂停开关
	*  @param file LPCWSTR img 图片地址
	*/
	CUI_img(LPCWSTR img);
	/** 析构函数 */
	~CUI_img();
};
/** @}*/ // 基础图片类
/** @}*/ // 火柴人联盟


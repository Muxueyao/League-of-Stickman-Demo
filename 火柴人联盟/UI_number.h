#pragma once
/** @defgroup EXAMPLES 火柴人联盟
*  @author  赵飞
*  @version 1.0
*  @date    2006-11-9
*  @{
*/
class CUI_number
	:public CPicture
{
	/** @name 数值显示
	*  @{
	*/
	/** 要显示的分数 */
	int score;
	/** 单帧图片宽度 */
	int one_x;
	/** 单帧图片高度 */
	int one_y;
	/** 取传入数值每位数,最多八位 */
	int number[8];

public:
	/** 逻辑函数 */
	void update();
	/** 渲染函数 */
	void show();
	/** 设置分数 */
	void set_score(int _score) { score = _score; }
	/** 构造函数
	*  @param file LPCTSTR img	图片地址
	*  @param file float _x		显示坐标
	*  @param file float _y		显示坐标
	*/
	CUI_number(LPCTSTR img,float _x,float _y);
	/** 析构函数 */
	~CUI_number();
};

/** @}*/ // 数值显示
/** @}*/ // 火柴人联盟
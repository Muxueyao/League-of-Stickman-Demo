#pragma once
/** @defgroup EXAMPLES 火柴人联盟
*  @author  赵飞
*  @version 1.0
*  @date    2006-11-9
*  @{
*/
class CHP_rect
{
/** @name 血条显示
*  @{
*/
	/** 大号线条 */
	LPD3DXLINE  g_pLine_M;
	/** 小号线条 */
	LPD3DXLINE  g_pLine_S;
	/** 显示颜色 */
	BYTE R, G, B;
	/** 显示坐标 */
	float x, y;
	/** 血条百分比 */
	float hp;
	/** 缓冲百分比 */
	float buffer_hp;
public:
	/** 成员析构 */
	void Release();
	/** 设置血量 
	*  @param file float _hp	血量百分比
	*  @param file float _x		显示坐标
	*  @param file float _y		显示坐标
	*/
	void set_hp(float _hp, float _x, float _y);
	/** 设置显示颜色
	*/
	void set_color(BYTE _R, BYTE _G, BYTE _B) { R = _R; G = _G; B = _B; }
	/** 构造函数
	*/
	CHP_rect();
	/** 析构函数
	*/
	~CHP_rect();
};

/** @}*/ // 血条显示
/** @}*/ // 火柴人联盟
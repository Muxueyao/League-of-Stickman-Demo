#pragma once
/** @defgroup EXAMPLES 火柴人联盟
*  @author  赵飞
*  @version 1.0
*  @date    2006-11-9
*  @{
*/
class CAnimate
	:public CPicture
{
	/** @name 动画类
	*  @{
	*/
	/** 当前桢 */
	int start_num;
	/** 开始桢 */
	int _start;
	/** 结束桢 */
	int end_num;
	/** 图片横向数量 */
	int x_num;
	/** 图片竖向数量 */
	int y_num;
	/** 单位宽度 */
	int one_x;
	/** 单位高度 */
	int one_y;
	/** 是否循环播放 */
	bool loop;
	/** 是否播放完毕 */
	bool is_end;
	/** 动画总桢数 */
	int all_num;
	/** 控制每桢动画快慢 */
	int Speed_Time;
	/** 控制每桢动画快慢_临时 */
	int S_TIME;
public:
	/** 动画播放完毕返回true */
	bool get_end() { return is_end; }
	/** 动画逻辑 */
	void update();
	/** 动画渲染 */
	void show();
	/** 构造函数
	*  @param file LPCWSTR imgname	图片地址
	*  @param file int all_x		横向帧数
	*  @param file int all_y		竖向帧数
	*  @param file int start_num	开始帧
	*  @param file int end_num		结束帧
	*/
	CAnimate(LPCWSTR imgname, int all_x, int all_y, int start_num, int end_num);
	/** 析构函数 */
	~CAnimate();
};

/** @}*/ // 动画类
/** @}*/ // 火柴人联盟
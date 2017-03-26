#pragma once

/** @defgroup EXAMPLES 火柴人联盟
*  @author  赵飞
*  @version 1.0
*  @date    2006-11-9
*  @{
*/
class Cmap
{
	/** @name 地图类
	*  @{
	*/
	/** 单例对象 */
	static Cmap *instance;
	/** 偏移坐标 */
	int offset_x, offset_y;
	/** 世界坐标 */
	int map_x, map_y;
	/** 限制当前最大地图长宽,锁定地图时用到 */
	int now_x, now_y;
	/** 地图振动状态 */
	bool is_snake;
	/** 地图振动时Y坐标的偏移值 */
	int snake;
	/** 地图图片对象 */
	CUI_img *map_img;
public:
	/** 获取单例对象 */
	static Cmap* Getinstance();
	/** 获取地图宽度 */
	int get_map_x() { return map_x; }
	/** 获取地图高度 */
	int get_map_y() { return map_y; }
	/** 获取地图宽度偏移 */
	int get_offset_x() { return offset_x; }
	/** 获取地图高度偏移 */
	int get_offset_y() { return offset_y; }
	/** 获取振动时的偏移值 */
	int get_snake() { return snake; }
	/** 设置地图振动 */
	void set_snake(bool _snake) { is_snake = _snake; }
	/** 逻辑函数 */
	void update();
	/** 重置地图状态 */
	void reset() { map_x = 1500; }
	/** 锁定地图 */
	void set_lock_scene(int _scene);
	/** 设置地图偏移值 */
	void set_offset(int x, int y) { offset_x = x;offset_y = y; }
	/** 构造函数 */
	Cmap();
	/** 析构函数 */
	~Cmap();
};

/** @}*/ // 地图类
/** @}*/ // 火柴人联盟
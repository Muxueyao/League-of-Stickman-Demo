#pragma once

/** @defgroup EXAMPLES 火柴人联盟
*  @author  赵飞
*  @version 1.0
*  @date    2006-11-9
*  @{
*/

/** @name 平台宏定义
*  @{
*/
/** 定义最大字符串个数 */
#define MAX_LOADSTRING	100
/** FPS限制 */
#define FPS				60
/** @}*/ // 平台宏定义
class CPlatForm
{
	/** @name 平台参数
	*  @{
	*/

	/** 开始界面AVI播放状态 */
	bool avi_end = false;
	/** 计算当前AVI播放时间的变量 */
	int play_temp_time = 0;
	/** AVI视频播放句柄 */
	static HWND avi_hw;
	/** AVI视频总长度 秒 */
	static long PlayTime;
	/** 窗口标题 */
	WCHAR				szTitle[MAX_LOADSTRING];
	/** 窗口副标题 */
	WCHAR				szWindowClass[MAX_LOADSTRING];
	/** 平台类单例对象 */
	static CPlatForm	*Instance;
	/** 窗口句柄 */
	HWND				hWnd;
	/** 3D设备 */
	LPDIRECT3D9			pD3d;
	/** 3D显示设备 */
	LPDIRECT3DDEVICE9	pd3dDevice;
	/** 线条绘制对象 */
	LPD3DXLINE			g_pLine;
	/** 文字绘制对象 */
	LPD3DXFONT			pFont;
	/** 文字绘制对象 */
	LPD3DXFONT			pFont_big;
	/** FPS显示开关 */
	bool				DisplayFPS = true;
	/** 游戏暂停开关 */
	bool				game_Pause;
	/** 鼠标当前x坐标 */
	static float		mouse_x;
	/** 鼠标当前y坐标 */
	static float		mouse_y;
	/** 鼠标左键状态 */
	static bool			lbutton_press;
	/** 初始化3D调备
	*/
	void				initD3D();
	/** 消息函数
	*/
	static				LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	/** FPS显示
	*/
	void				displayFPS();
	/** 图像绘制
	*/
	void				Render();
	/** 获取当前FPS值
	*/
	float				getFPS();
	
public:
	/** 游戏函数运行
	*/
	void run();
	/** 设置游戏暂停继续
	*  @param file pause = true 暂停 pause = false 继续
	*/
	void set_pause(bool _pause) { game_Pause = _pause; }
	/** 获取游戏暂停继续状态
	*  @return 返回游戏当前状态
	*/
	bool get_pause() { return game_Pause; }
	/** 获取窗口句柄
	*  @return 返回窗口句柄
	*/
	HWND Get_hwnd() { return hWnd; }
	/** 平台类单例函数
	*  @return 返回单例对象
	*/
	static CPlatForm *Getinstance();
	/** 获取3D设备
	*  @return 返回3D设备对象
	*/
	LPDIRECT3D9 Get_pD3d() { return pD3d; }
	/** 获取3D显示设备
	*  @return 返回3D显示设备
	*/
	LPDIRECT3DDEVICE9	Get_pd3dDevice() { return pd3dDevice; }
	/** 获取鼠标坐标
	*  @return 鼠标X坐标
	*/
	float get_mouse_x() { return mouse_x; }
	/** 获取鼠标坐标
	*  @return 返回鼠标Y坐标
	*/
	float get_mouse_y() { return mouse_y; }
	/** 获取鼠标左键状态
	*  @return 返回鼠标左键状态
	*  - true	鼠标左键按下
	*  - false	鼠标左键弹起

	*/
	bool get_lbutton_press() { return lbutton_press; }
	/** 获取桢时间
	*  @return 返回每一桢的时间值
	*/
	float updateTime();
	/** 获取文字对象
	*  @return 返回文字对象
	*/
	LPD3DXFONT get_p_font() { return pFont; }
	/** 获取文字对象
	*  @return 返回文字对象
	*/
	LPD3DXFONT get_p_font_big() { return pFont_big; }
	/** 类构造函数
	*/
	CPlatForm();
	/** 类析构函数
	*/
	~CPlatForm();

	/** @}*/ // 平台参数
	/** @}*/ // 火柴人联盟
};


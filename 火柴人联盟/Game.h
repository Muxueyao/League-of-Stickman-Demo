#pragma once
/** @defgroup EXAMPLES 火柴人联盟
*  @author  赵飞
*  @version 1.0
*  @date    2006-11-9
*  @{
*/
class CGame
{
	/** @name 游戏逻辑
	*  @{
	*/
	/** 单例对象 */
	static CGame *instance;
	/** 登陆开关 */
	bool is_login;
	/** 加载开关 */
	bool is_load;
	/** 主界面开关 */
	bool is_mainscene;
	/** 新手界面开关 */
	bool is_new_state;
	/** 游戏开始开关 */
	bool is_gamescene;
	/** 游戏开始 */
	bool game_start;
	/** 胜利开关 */
	bool is_win;
	/** 失败开关 */
	bool is_lose;
	/** 重新开始游戏开关 */
	bool restart;


	/** 登陆界面 */
	CLogin *login;
	/** 加载界面 */
	CLoading *loading;
	/** 主界面 */
	CMain_scene *main_scene;
	/** 新手教学 */
	CNew_hand_state *new_hand_state;
	/** 游戏开始界面 */
	CGame_start *start;
	/** 胜利界面 */
	CUI_img *win_scene;
	/** 失败界面 */
	CUI_img *lose_scene;
	/** 重新开始游戏按钮 */
	CUI_button *game_restart;
	/** 退出游戏按钮 */
	CUI_button *game_exit;
public:
	/** 获取单例对象 */
	static CGame *Get_instance();
	/** 运行游戏逻辑 */
	void update();
	/** 构造函数 */
	CGame();
	/** 析构函数 */
	~CGame();
};
/** @}*/ // 游戏逻辑
 /** @}*/ // 火柴人联盟

#pragma once
/** @defgroup EXAMPLES 火柴人联盟
*  @author  赵飞
*  @version 1.0
*  @date    2006-11-9
*  @{
*/

class CPlayer
{
	/** @name 玩家类
	*  @{
	*/
	/** 动画精灵 */
	SpriteX *spx;
	/** 世界坐标 */
	float x, y;
	/** 窗口坐标 */
	float show_x, show_y;
	/** 血条对象 */
	CHP_rect hp_rect;
	/** 当前血量 */
	float now_hp;
	/** 所有血量 */
	float all_hp;
	/** 缓冲血量 */
	float buffer_hp;
	/** 翻转状态 */
	bool dir;
	/** 镜头偏移值 */
	int camera_x;
	/** 镜头静止状态 */
	bool camera_stand;
	/** 镜头状态 */
	bool is_camera;
	/** 时间临时变量 */
	int m_time = 150;
	int m_speed = 20;
	/** 玩家金币 */
	int money;
	/** 玩家钻石 */
	int zuansi;
	/** 技能A图标 */
	CUI_img *a_img;
	/** 技能A当前动作 */
	int a_act;
	/** 技能A冷却图标 */
	DX_CircleAnim *a_load;
	/** 技能Q图标 */
	CUI_img *q_img;
	/** 技能Q冷却图标 */
	DX_CircleAnim *q_load;
	/** 技能W图标 */
	CUI_img *w_img;
	/** 技能W冷却图标 */
	DX_CircleAnim *w_load;
	/** 技能E图标 */
	CUI_img *e_img;
	/** 技能E冷却图标 */
	DX_CircleAnim *e_load;
	/** 技能R图标 */
	CUI_img *r_img;
	/** 技能R冷却图标 */
	DX_CircleAnim *r_load;
	/** 技能CD时间 */
	float Q_CD, W_CD, E_CD, R_CD, A_CD;
	/** 技能冷却剩余时间 */
	float  Q_time, W_time, E_time, R_time, A_time;
	/** 字体对象1 */
	LPD3DXFONT pFont_big;
	/** 字体对象2 */
	LPD3DXFONT pFont_small;
	/** 连击数 */
	int hits;
	/** 连击数缓冲 */
	int hits_buffer;
	/** 连击数清0时间 */
	int hits_time;
	/** 连击背景图片 */
	CUI_img *hits_battle;
	/** 人物受伤状态 */
	bool is_hurted;
	/** 受伤时间等待 */
	int hurted_time;
	/** 受伤时间等待 */
	int hurted_num;
	/** 受伤红色图片 */
	CUI_img *hurted_img;
	/** 声明人物动作 */
	enum PLAYER_ACT;
	/** 设置人物动作 */
	void set_state(PLAYER_ACT act);
	/** 设置动作移动 */
	void set_move();
	/** 玩家单例对象 */
	static CPlayer *Instance;
	/** 死亡状态 */
	bool is_death;
	/** 移动速度 */
	int move_speed;
	/** 连击数显示 */
	void hits_show();
	/** 血条显示开关 */
	bool hp_show;
	/** 技能伤害值 */
	int A1_hurted,A2_hurted,A3_hurted,A4_hurted,A5_hurted,Q_hurted,W_hurted,E_hurted,R_hurted;
public:

	/** 枚举常量_人物动作 */
	enum PLAYER_ACT
	{
		Stand,	  /**< 站立 */
		Walk,	  /**< 行走 */
		A1,		  /**< 技能 */
		A2,		  /**< 技能 */
		A3,		  /**< 技能 */
		A4,		  /**< 技能 */
		A5,		  /**< 技能 */
		Q,		  /**< 技能 */
		W,		  /**< 技能 */
		E,		  /**< 技能 */
		E2,		  /**< 技能 */
		E3,		  /**< 技能 */
		R,		  /**< 技能 */
		DIE,	  /**< 死亡 */
		hurted,	  /**< 受伤 */
	}player_act;
	/** 获取当前钻石数量 */
	int get_zuansi() { return zuansi; }
	/** 获取技能伤害值 */
	int get_q_hurted() { return Q_hurted; }
	/** 获取技能伤害值 */
	int get_w_hurted() { return W_hurted; }
	/** 获取技能伤害值 */
	int get_e_hurted() { return E_hurted; }
	/** 获取技能伤害值 */
	int get_r_hurted() { return R_hurted; }
	/** 获取技能伤害值 */
	int get_a1_hurted() { return A1_hurted; }
	/** 获取技能伤害值 */
	int get_a2_hurted() { return A2_hurted; }
	/** 获取技能伤害值 */
	int get_a3_hurted() { return A3_hurted; }
	/** 获取技能伤害值 */
	int get_a4_hurted() { return A4_hurted; }
	/** 获取技能伤害值 */
	int get_a5_hurted() { return A5_hurted; }
	/** 设置镜头移动
	*  @param file float m_x 镜头移动数值
	*/
	void set_camera(float m_x);
	/** 设置连击数 */
	void set_hits() { hits++;hits_time = 80; }
	/** 获取当前人物动作 */
	PLAYER_ACT get_act() { return player_act; }
	/** 获取动作精灵 */
	SpriteX *Get_spx() { return spx; }
	/** 获取窗口坐标 */
	int get_show_x() { return show_x; }
	/** 获取窗口坐标 */
	int get_show_y() { return show_y; }
	/** 获取世界坐标 */
	int get_x() { return x; }
	/** 获取世界坐标 */
	int get_y() { return y; }
	/** 获取单例对象 */
	static CPlayer *Get_Instance();
	/** 获取金币数值 */
	int get_money() { return money; }
	/** 获取血量值 */
	int get_hp() { return buffer_hp; }
	/** 获取镜头静止状态 */
	bool get_camera_stand() { return camera_stand; }
	/** 逻辑函数 */
	void update();
	/** 渲染函数 */
	void show();
	/** 各项参数恢复初始值 */
	void reset();
	/** 设置血条显示状态 */
	void set_hp_show(bool hp_show) { this->hp_show = hp_show; }
	/** 获取镜头状态 */
	bool get_is_camera() { return is_camera; }
	/** 获取死亡状态 */
	bool get_death() { return is_death; }
	/** 设置伤害数值 */
	void set_hurted(int hurted_num);
	/** 设置伤害击飞 */
	void set_hurted_fly(bool _dir, int hurted_num);
	/** 设置金币 */
	void set_money(int _money) { money += _money;new CHurted_num(L"img/num_yellow.png", _money, x , y - 150,L"img/num_coin.png");}
	/** 构造函数 */
	CPlayer();
	/** 析构函数 */
	~CPlayer();
};

/** @}*/ // 玩家类
/** @}*/ // 火柴人联盟
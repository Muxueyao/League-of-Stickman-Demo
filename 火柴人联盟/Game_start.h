#pragma once
class CGame_start
{
	CUI_img *BackScene;
	CAnimate *m_money;
	CAnimate *m_hp;

	CUI_number *money_number;
	CUI_number *hp_number;

	bool is_camera = false;

	//控制鼠标点击速度
	int press_time;
	CUI_button *pause;
	CUI_button *go;

	enum game_state
	{
		a_0,
		a_1,
		a_2,

		b_0,
		b_1,
		b_2,

		c_0,
		c_1,
		c_2,

		camera,

		boss,
	}_state;

	bool is_stateover;
	bool is_instate;
	int show_time;

	CNpc3 *state_a[4];
	CNpc2 *state_b[8];
	CNpc1 *state_c[8];

	CNpc1 *boss_1[2];
	CNpc2 *boss_2[2];
	CNpc3 *boss_3[2];
	CBoss *boss_boss;

	int boss_showtime;

	int gogo_time;
	SpriteX *gogo;
	bool Game_state;
	void set_go(int go_time) { gogo_time = go_time; }
public:
	void stop_audio();
	bool get_state() { return Game_state; }
	void update();
	void Release();
	void set_score(int money, int hp);
	CGame_start();
	~CGame_start();
};


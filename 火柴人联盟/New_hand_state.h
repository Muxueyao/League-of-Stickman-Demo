#pragma once
class CNew_hand_state
{
	float x, y;
	CUI_img *back_scene;
	
	int press_time;

	CUI_button *exit;

	CUI_button_2 *button_left;
	CUI_button_2 *button_right;
	CUI_button_2 *button_a;
	CUI_button_2 *button_q;
	CUI_button_2 *button_w;
	CUI_button_2 *button_e;
	CUI_button_2 *button_r;
	CUI_img *a_img;
	CUI_img *q_img;
	CUI_img *w_img;
	CUI_img *e_img;
	CUI_img *r_img;
	CNpc3 *test;
	//CUI_button_2 *select;
	bool is_over;
	int a_press_time;
	bool is_r_dir;
	bool is_l_dir;
	bool is_dir;
	bool welcome;
	bool is_a_press;
	bool is_q_press;
	bool is_w_press;
	bool is_e_press;
	bool is_r_press;
	bool is_npc_show;
	bool all_over;
	bool new_hand_state;

public:
	bool get_state() { return all_over; }
	void update();
	void Release();
	CNew_hand_state();
	~CNew_hand_state();
};


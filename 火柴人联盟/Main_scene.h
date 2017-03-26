#pragma once
class CMain_scene
{
	CUI_img *img;
	CUI_img *img2;
	float img2_angle;
	float angle_speed;
	float angle_speed_temp;
	CUI_button *start;
	CUI_img *player1;
	CUI_img *player2;

	CUI_button *bag;
	CUI_button *equip;
	CUI_button *buy;

	CUI_img *money;
	CUI_number *num_money;
	CUI_img *zuansi;
	CUI_number *num_zuansi;
	int sleep_time;
	bool button_press;
	bool is_end;
public:
	void update();
	void Release();
	bool get_state() { return is_end; }
	CMain_scene();
	~CMain_scene();
};


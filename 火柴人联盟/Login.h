#pragma once
class CLogin
{
	bool is_end;
	CUI_img *img;
	CUI_button *button;
	//CUI_button *button2;
	float x, y;
	bool button_press;
	float alpha;
	
public:
	void update();
	void Release();
	bool get_state() { return is_end; }
	CLogin();
	~CLogin();
};


#pragma once
class CLoading
{
	bool is_end;
	CUI_img *img;
	CAnimate *animate;
public:
	void update();
	void Release();
	bool get_state() { return is_end; }
	CLoading();
	~CLoading();
};


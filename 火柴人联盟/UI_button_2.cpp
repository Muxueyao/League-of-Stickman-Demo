#include "stdafx.h"



void CUI_button_2::Release()
{
	img_1->set_del(true);
	img_2->set_del(true);
}

void CUI_button_2::update()
{
	buffer_time--;
	if (buffer_time < 0)
	{
		buffer_time = show_time;
	}
	if (buffer_time > show_time / 2)
	{
		img_1->set_show(false);
		img_2->set_show(true);
	}
	else
	{
		img_1->set_show(true);
		img_2->set_show(false);
	}
}

void CUI_button_2::show()
{
}

CUI_button_2::CUI_button_2(LPCWSTR img1, LPCWSTR img2, float x, float y, float time)
{
	show_time = time;
	buffer_time = show_time;
	img_1 = new CUI_img(img1);
	img_1->set_sort(-5);
	img_1->set_pos(x, y);
	img_1->set_show(false);

	img_2 = new CUI_img(img2);
	img_2->set_sort(-5);
	img_2->set_pos(x, y);
	img_2->set_show(false);

	CObj_management::Getinstance()->add(this);

}


CUI_button_2::~CUI_button_2()
{
}

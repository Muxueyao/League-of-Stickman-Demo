#include "stdafx.h"



void CHurted_num::update()
{
	y-=2;
	number->set_pos(x, y);
	if (show_time > 0)
	{
		show_time--;
		number->set_score(num);
	}
	else
	{
		set_del(true);
	}

	if (img2!=NULL)
	{
		img2->set_pos(x-30, y);
	}
}

void CHurted_num::show()
{
}

void CHurted_num::Release()
{
	number->set_del(true);
	if (img2!=NULL)
	{
		img2->set_del(true);
	}
	
}

CHurted_num::CHurted_num(LPCWSTR img_name, int num, float _x, float _y ,LPCWSTR img_Name)
{
	id = Hurted_num;
	this->x = _x + Cmap::Getinstance()->get_offset_x();
	this->y = _y + Cmap::Getinstance()->get_offset_y();
	number = new CUI_number(img_name,x,y);
	number->set_sort(-5);
	number->set_pos(x, y);
	this->num = num;
	show_time = 20;
	img2 = new CUI_img(img_Name);
	img2->set_pos(x - 30, y);
	img2->set_sort(-5);
	CObj_management::Getinstance()->add(this);
}

CHurted_num::CHurted_num(LPCWSTR img_name, int num, float _x, float _y)
{
	id = Hurted_num;
	this->x = _x + Cmap::Getinstance()->get_offset_x();
	this->y = _y + Cmap::Getinstance()->get_offset_y();
	number = new CUI_number(img_name, x, y);
	number->set_sort(-5);
	number->set_pos(x, y);
	this->num = num;
	show_time = 20;
	img2 = NULL;
	CObj_management::Getinstance()->add(this);
}


CHurted_num::~CHurted_num()
{
}

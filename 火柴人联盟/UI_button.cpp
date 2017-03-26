#include "stdafx.h"



CUI_button::CUI_button(LPCWSTR in, LPCWSTR out,float x,float y)
{
	
	mousein = new CUI_img(in);
	mouseout = new CUI_img(out);
	mousein->set_anchor(D3DXVECTOR3(mousein->get_img_x() / 2, mousein->get_img_y() / 2, 0));
	mouseout->set_anchor(D3DXVECTOR3(mouseout->get_img_x() / 2, mouseout->get_img_y() / 2, 0));
	img_x = mousein->get_img_x();
	img_y = mousein->get_img_y();
	mousein->set_pos(x, y);
	mousein->set_sort(-3);
	mouseout->set_pos(x, y);
	mouseout->set_sort(-3);
	this->x = x;
	this->y = y;
	is_end = false;

	mousein->set_show(false);
	mouseout->set_show(false);
}

void CUI_button::Release()
{
	mousein->set_del(true);
	mouseout->set_del(true);
}

void CUI_button::update()
{
	is_end = false;

	RECT m_rect = { x - mouseout->get_anchor().x,y - mouseout->get_anchor().y,
		 x + img_x - mouseout->get_anchor().x,y + img_y - mouseout->get_anchor().y };
	int mouse_x = CPlatForm::Getinstance()->get_mouse_x();
	int mouse_y = CPlatForm::Getinstance()->get_mouse_y();
	bool is_lbutton = CPlatForm::Getinstance()->get_lbutton_press();
	if (mouse_x > m_rect.left&&mouse_x<m_rect.right
		&&mouse_y>m_rect.top&&mouse_y < m_rect.bottom)
	{
		mousein->set_show(true);
		mouseout->set_show(false);
		if (is_lbutton)
		{
			is_end = true;
			CAudio_management::Get_instance()->UI_press_audio_play();
		}
	}
	else
	{
		mousein->set_show(false);
		mouseout->set_show(true);
	}
}



void CUI_button::set_show(bool show)
{
	is_show = show;
	if (is_show)
	{
		mousein->set_show(true);
		mouseout->set_show(true);
	}
	else
	{
		mousein->set_show(false);
		mouseout->set_show(false);
	}
}

CUI_button::~CUI_button()
{
}

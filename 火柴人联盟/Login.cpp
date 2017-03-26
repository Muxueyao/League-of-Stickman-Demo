#include "stdafx.h"



void CLogin::update()
{
	if (is_end)
	{
		return;
	}
	alpha += 5;
	if (alpha > 255)
	{
		alpha = 255;
		button->set_show(true);
		
	}
	img->set_alpha(alpha);
	if (button_press)
	{
		CAudio_management::Get_instance()->main_audio_stop();
		button->set_show(false);
		x -= 20;
		alpha -= 10;
		if (alpha <= 0)
		{
			alpha = 0;
		}
		img->set_alpha(alpha);
		img->set_pos(x, y);
		if (x < -img->get_img_x())
		{
			
			is_end = true;
			//Release();
		}
		return;
	}
		
	if (button == NULL)
	{
		button = new CUI_button(L"img/bthm_ksan_2.png", L"img/bthm_ksan_1.png", 500, 460);
	
		button->set_show(false);

	}
	else
	{
		if (button->get_show())
		{
			button->update();
		}
		
		
	}
	
	if (button->get_state())
	{
		button_press = true;
		//Release();
	}
}


void CLogin::Release()
{
	img->set_del(true);
	button->Release();

	//main_audio.Release();
}

CLogin::CLogin()
{
	x = y = 0;
	button_press = false;
	is_end = false;
	alpha = 0;
	img = new CUI_img(L"img/login.png");
	img->set_alpha(alpha);
	button = NULL;
	

	
	CAudio_management::Get_instance()->main_audio_play();
}


CLogin::~CLogin()
{
}

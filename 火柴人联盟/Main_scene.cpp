#include "stdafx.h"



void CMain_scene::update()
{
	start->update();
	bag->update();
	equip->update();
	buy->update();

	num_money->set_score(CPlayer::Get_Instance()->get_money());
	num_zuansi->set_score(CPlayer::Get_Instance()->get_zuansi());

	if (img2_angle >= 50)
	{
		angle_speed -= angle_speed_temp;

	}	
	if (img2_angle <= -50)
	{
		angle_speed += angle_speed_temp;
	
	}
		
	img2_angle += angle_speed;
	
	
	img2->set_angle(img2_angle/180*D3DX_PI);



	if (start->get_state())
	{
		player2->set_show(true);
		player1->set_show(false);
		button_press = true;
	}
	if (button_press)
	{
		sleep_time--;
		if (sleep_time<=0)
		{
			is_end = true;
		}
	}
}

void CMain_scene::Release()
{
	player1->set_del(true);
	player2->set_del(true);
	img->set_del(true);
	img2->set_del(true);

	start->Release();
	delete start;
	start = NULL;
	bag->Release();
	delete bag;
	bag = NULL;
	equip->Release();
	delete equip;
	equip = NULL;
	buy->Release();
	delete buy;
	buy = NULL;

	money->set_del(true);
	//delete money;
	//money = NULL;
	zuansi->set_del(true);
	//delete zuansi;
	//zuansi = NULL;
	num_money->set_del(true);
	//delete num_money;
	//num_money = NULL;
	num_zuansi->set_del(true);
	//delete num_zuansi;
	//num_zuansi = NULL;
}

CMain_scene::CMain_scene()
{
	angle_speed = 1.f;
	angle_speed_temp = 0.03f;
	img2_angle = 0;
	sleep_time = 50;
	is_end = false;
	button_press = false;

	money = new CUI_img(L"img/battleEnd_coin.png");
	money->set_pos(25, 440);
	money->set_sort(-10);
	num_money = new CUI_number(L"img/num_yellow.png", 45, 448);
	num_money->set_sort(-10);

	zuansi = new CUI_img(L"img/battleEnd_diamond.png");
	zuansi->set_sort(-10);
	zuansi->set_pos(25, 480);
	num_zuansi = new CUI_number(L"img/num_blue.png", 45, 488);
	num_zuansi->set_sort(-10);

	img = new CUI_img(L"img/backscene.png");
	img->set_sort(-3);

	img2 = new CUI_img(L"img/arena.png");
	img2->set_anchor(D3DXVECTOR3(img2->get_img_x() / 2, 0, 0));
	img2->set_pos(510, 0);
	img2->set_sort(-3);

	start = new CUI_button(L"img/bottom_open1.png", L"img/bottom_open.png", 510, 400);
	player1 = new CUI_img(L"img/1009_a.png");
	player1->set_pos(440, 150);
	player1->set_sort(-3);
	player2 = new CUI_img(L"img/1009_b.png");
	player2->set_pos(440, 150);
	player2->set_show(false);
	player2->set_sort(-3);

	bag = new CUI_button(L"img/menu_pack1.png", L"img/menu_pack.png", 760, 500);
	equip = new CUI_button(L"img/menu_equip1.png", L"img/menu_equip.png", 830, 500);
	buy = new CUI_button(L"img/menu_money1.png", L"img/menu_money.png", 900, 500);
}


CMain_scene::~CMain_scene()
{
}

#include "stdafx.h"



void CNpc::set_hurted(float hurted_num)
{
	if (hurted_time <= 0)
	{
		new CHurted_num(L"img/num_monsterhit.png", hurted_num, x - 30, y - 150);
		now_hp -= hurted_num;
		if (now_hp <= 0)
		{
			now_hp = 0;
		}
		is_hurted = true;
		hurted_time = 10;
		
	}	
	
}

CNpc::CNpc()
{
	hurted_spx = new SpriteX(CPlatForm::Getinstance()->Get_pd3dDevice(), "other/npc/hurted.sprite", "other/npc/effect_role.png");
	hurted_spx->setAction(0,true);
	hurted_spx->setScale(2.f);
	hurted_spx->setDelay(10);
	hurted_spx->setColor(255, 0, 0);

	hurted_time = 0;
	is_hurted = false;
	num_once = 0;
	hp_rect.set_color(255, 0, 0);
	is_del = false;
	dir = true;
	all_hp = 10000+rand()%10000;
	now_hp = all_hp;
	x = 800;y = 365;
	show_x = x;show_y = y;

	/*Hurted_img = new CUI_img(L"img/button_x.png");
	Hurted_img->set_pos(x, y);
	Hurted_img->set_show(false);
	Hurted_img->set_sort(-10);*/
}


CNpc::~CNpc()
{
}

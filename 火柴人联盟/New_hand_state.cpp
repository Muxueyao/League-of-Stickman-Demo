#include "stdafx.h"



void CNew_hand_state::update()
{
	back_scene->set_pos(x, y + Cmap::Getinstance()->get_snake());
	press_time--;
	if (press_time>=0 && welcome )
	{
	
		RECT rc = { 330,40,950,550 };
		CPlatForm::Getinstance()->get_p_font_big()->DrawTextA(NULL, "欢迎来到新手教学", -1,
			&rc, DT_LEFT | DT_TOP, D3DCOLOR_RGBA(0, 255, 0, 150));
		if (press_time==0)
		{
			welcome = false;
			is_dir = true;
			press_time = 100;
	
		}
	}
	else if (is_dir&& press_time <= 0)
	{
		if (button_left == NULL&&button_right == NULL)
		{
			button_left = new CUI_button_2(L"img/keys_left_.png", L"img/keys_left.png", 350, 100, 40);
			button_right = new CUI_button_2(L"img/keys_right_.png", L"img/keys_right.png", 530, 100, 40);
		}
		RECT rc = { 300,40,950,550 };
		CPlatForm::Getinstance()->get_p_font_big()->DrawTextA(NULL, "左右方向键控制人物移动", -1,
			&rc, DT_LEFT | DT_TOP, D3DCOLOR_RGBA(0, 255, 0, 150));

		if (GetAsyncKeyState(VK_LEFT)&0x8000)
		{
			is_l_dir = true;
		}
		if (GetAsyncKeyState(VK_RIGHT)&0x8000)
		{
			is_r_dir = true;
		}
		if (is_r_dir&&is_l_dir)
		{
			is_a_press = true;
			is_dir = false;
			press_time = 100;
			button_left->set_del(true);
			button_right->set_del(true);
			button_left = NULL;
			button_right = NULL;
			
		}

	}

	else if (is_a_press && press_time <=0)
	{
		a_img->set_alpha(255);
		if (button_a == NULL)
		{
			button_a = new CUI_button_2(L"img/keys_a_.png", L"img/keys_a.png", 440, 100, 40);
		}
		RECT rc = { 300,40,950,550 };
		if (a_press_time == 0)
		{
			CPlatForm::Getinstance()->get_p_font_big()->DrawTextA(NULL, "       按 A 键  普通攻击", -1,
				&rc, DT_LEFT | DT_TOP, D3DCOLOR_RGBA(0, 255, 0, 150));
		}
		if (a_press_time == 1)
		{
			CPlatForm::Getinstance()->get_p_font_big()->DrawTextA(NULL, "再次按 A 键  释放二段普攻", -1,
				&rc, DT_LEFT | DT_TOP, D3DCOLOR_RGBA(0, 255, 0, 150));
		}
		if (a_press_time == 2)
		{
			CPlatForm::Getinstance()->get_p_font_big()->DrawTextA(NULL, "再次按 A 键  释放三段普攻", -1,
				&rc, DT_LEFT | DT_TOP, D3DCOLOR_RGBA(0, 255, 0, 150));
		}
		if (a_press_time == 3)
		{
			CPlatForm::Getinstance()->get_p_font_big()->DrawTextA(NULL, "再次按 A 键  释放四段普攻", -1,
				&rc, DT_LEFT | DT_TOP, D3DCOLOR_RGBA(0, 255, 0, 150));
		}
		if (a_press_time == 4)
		{
			CPlatForm::Getinstance()->get_p_font_big()->DrawTextA(NULL, "再次按 A 键  释放五段普攻", -1,
				&rc, DT_LEFT | DT_TOP, D3DCOLOR_RGBA(0, 255, 0, 150));
		}
		
		if (GetAsyncKeyState('A') & 0x8000)
		{
			a_press_time++;
			press_time = 50;
			if (a_press_time==5)
			{
				is_a_press = false;
				is_q_press = true;
				button_a->set_del(true);
				button_a = NULL;
				
			}
			
		}
	}
	else if (is_q_press && press_time <= 0)
	{
		q_img->set_alpha(255);
		if (button_q == NULL)
		{
			button_q = new CUI_button_2(L"img/keys_q_.png", L"img/keys_q.png", 440, 100, 40);
		}
		RECT rc = { 360,40,950,550 };
		CPlatForm::Getinstance()->get_p_font_big()->DrawTextA(NULL, "按 Q 键  释放技能", -1,
			&rc, DT_LEFT | DT_TOP, D3DCOLOR_RGBA(0, 255, 0, 150));
		if (GetAsyncKeyState('Q')&0x8000)
		{
			is_q_press = false;
			is_w_press = true;
			press_time = 100;
			button_q->set_del(true);
			button_q = NULL;
		}
	}
	else if (is_w_press && press_time <= 0)
	{
		w_img->set_alpha(255);
		if (button_w == NULL)
		{
			button_w = new CUI_button_2(L"img/keys_w_.png", L"img/keys_w.png", 440, 100, 40);
		}
		RECT rc = { 360,40,950,550 };
		CPlatForm::Getinstance()->get_p_font_big()->DrawTextA(NULL, "按 W 键  释放技能", -1,
			&rc, DT_LEFT | DT_TOP, D3DCOLOR_RGBA(0, 255, 0, 150));
		if (GetAsyncKeyState('W')&0x8000)
		{
			is_w_press = false;
			is_e_press = true;
			button_w->set_del(true);
			button_w = NULL;
			press_time = 100;
			
		}
	}
	else if (is_e_press && press_time <= 0)
	{
		e_img->set_alpha(255);
		if (button_e == NULL)
		{
			button_e = new CUI_button_2(L"img/keys_e_.png", L"img/keys_e.png", 440, 100, 40);
		}
		RECT rc = { 360,40,950,550 };
		CPlatForm::Getinstance()->get_p_font_big()->DrawTextA(NULL, "按 E 键  释放技能", -1,
			&rc, DT_LEFT | DT_TOP, D3DCOLOR_RGBA(0, 255, 0, 150));
		if (GetAsyncKeyState('E') & 0x8000)
		{
			is_e_press = false;
			is_r_press = true;
			press_time = 100;
			button_e->set_del(true);
			button_e = NULL;
			
		}
	}
	else if (is_r_press && press_time <= 0)
	{
		r_img->set_alpha(255);
		if (button_r == NULL)
		{
			button_r = new CUI_button_2(L"img/keys_r_.png", L"img/keys_r.png", 440, 100, 40);
		}
		RECT rc = { 360,40,950,550 };
		CPlatForm::Getinstance()->get_p_font_big()->DrawTextA(NULL, "按 R 键  释放大招", -1,
			&rc, DT_LEFT | DT_TOP, D3DCOLOR_RGBA(0, 255, 0, 150));
		if (GetAsyncKeyState('R')&0x8000)
		{
			is_r_press = false;
			press_time = 100;
			is_over = true;
			button_r->set_del(true);
			button_r = NULL;
		}
	}
	else if (is_over && press_time <= 0)
	{
		is_over = false;
		if (test == NULL)
		{
			test = new CNpc3;
			test->set_pos(600, 365);
			is_npc_show = true;
			press_time = 100;
		}
	}
	else if (is_npc_show)
	{
		if (press_time>=0)
		{
		
			RECT rc = { 360,40,950,550 };
			CPlatForm::Getinstance()->get_p_font_big()->DrawTextA(NULL, "使用技能击杀小兵", -1,
				&rc, DT_LEFT | DT_TOP, D3DCOLOR_RGBA(0, 255, 0, 150));
		}
		CNpc_Management::Get_instance()->update();
		if (CNpc_Management::Get_instance()->get_list_size()==0)
		{
			RECT rc = { 280,40,950,550 };
			CPlatForm::Getinstance()->get_p_font_big()->DrawTextA(NULL, "击杀小兵后能获得金币奖励!", -1,
				&rc, DT_LEFT | DT_TOP, D3DCOLOR_RGBA(0, 255, 0, 150));
			if (CObj_management::Getinstance()->get_class_obj_num(CObj::moneydrop)==0)
			{
				is_npc_show = false;
				press_time = 200;
				new_hand_state = true;
			}
			
		}
	}
	else
	{
		if (new_hand_state)
		{
			if (press_time >= 0)
			{
				RECT rc = { 200,100,950,550 };
				CPlatForm::Getinstance()->get_p_font_big()->DrawTextA(NULL, "你已完成新手教学，现在进入实战吧!", -1,
					&rc, DT_LEFT | DT_TOP, D3DCOLOR_RGBA(0, 255, 0, 150));
			}
			else
			{
				all_over = true;
				CAudio_management::Get_instance()->main_audio_stop();
			}

		}

	
	}

	exit->update();
	if (exit->get_state())
	{
		all_over = true;
		CAudio_management::Get_instance()->main_audio_stop();
	}

}

void CNew_hand_state::Release()
{
	back_scene->set_del(true);
	a_img->set_del(true);
	q_img->set_del(true);
	w_img->set_del(true);
	e_img->set_del(true);
	r_img->set_del(true);
	exit->Release();
	delete exit;
	exit = NULL;
	back_scene->set_del(true);
	if (button_left)
	{
		button_left->set_del(true);
	}
	if (button_right)
	{
		button_right->set_del(true);
	}
	if (button_a)
	{
		button_a->set_del(true);
	}
	if (button_q)
	{
		button_q->set_del(true);

	}
	if (button_w)
	{
		button_w->set_del(true);
	}
	if (button_e)
	{
		button_e->set_del(true);
	}
	if (button_r)
	{
		button_r->set_del(true);
	}

}

CNew_hand_state::CNew_hand_state()
{
	button_left = NULL;
	button_right = NULL;
	button_a = NULL;
	button_q = NULL;
	button_w = NULL;
	button_e = NULL;
	button_r = NULL;
	
	exit = new CUI_button(L"img/ui_queren_you.png", L"img/ui_js_you.png", 900, 40);
	//select = new CUI_button_2(L"img/arrow_down.png", L"img/arrow_down.png", 800, 400,20);
	CAudio_management::Get_instance()->main_audio_play();
	x = 0;
	y = -30;
	back_scene = new CUI_img(L"img/m_scene.png");
	back_scene->set_pos(x, y);
	back_scene->set_sort(-2);
	test = NULL;

	is_over = false;
	new_hand_state = false;
	welcome = true;
	is_r_dir = false;
	is_l_dir = false;
	all_over = false;
	is_dir = false;
	is_a_press = false;
	is_q_press = false;
	is_w_press = false;
	is_e_press = false;
	is_r_press = false;
	is_npc_show = false;
	press_time = 200;
	a_press_time = 0;

	a_img = new CUI_img(L"img/A.png");
	a_img->set_pos(780, 450);
	a_img->set_sort(-21);
	a_img->set_scale(0.6f);
	a_img->set_alpha(50);
	q_img = new CUI_img(L"img/Q.png");
	q_img->set_pos(700, 460);
	q_img->set_sort(-21);
	q_img->set_alpha(50);
	w_img = new CUI_img(L"img/W.png");
	w_img->set_pos(720, 380);
	w_img->set_sort(-21);
	w_img->set_alpha(50);
	e_img = new CUI_img(L"img/E.png");
	e_img->set_pos(805, 365);
	e_img->set_sort(-21);
	e_img->set_alpha(50);
	r_img = new CUI_img(L"img/R.png");
	r_img->set_pos(880, 420);
	r_img->set_sort(-21);
	r_img->set_alpha(50);
}


CNew_hand_state::~CNew_hand_state()
{
}

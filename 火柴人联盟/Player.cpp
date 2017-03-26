#include "stdafx.h"

CPlayer *CPlayer::Instance = NULL;
void CPlayer::set_state(PLAYER_ACT act)
{
	player_act = act;
	bool isLoop = false;
	switch (player_act)
	{
	case Stand:
		isLoop = true;
		spx->setDelay(150);
		break;
	case Walk:
		isLoop = true;
		spx->setDelay(20);
		break;
	case A1:
		isLoop = false;
		spx->setDelay(20);
		break;
	case A2:
		isLoop = false;
		spx->setDelay(20);
		break;
	case A3:
		isLoop = false;
		spx->setDelay(40);
		break;

	case A4:
		isLoop = false;
		spx->setDelay(40);
		break;

	case A5:
		isLoop = false;
		spx->setDelay(30);
		break;
	case Q:
		isLoop = false;
		spx->setDelay(50);
		break;
	case W:
		isLoop = false;
		spx->setDelay(30);
		break;
	case E:
		isLoop = false;
		spx->setDelay(50);
		break;
	case E2:
		isLoop = false;
		spx->setDelay(50);
		break;
	case E3:
		isLoop = false;
		spx->setDelay(50);
		break;
	case R:
		isLoop = false;
		spx->setDelay(20);
		break;
	case hurted:
		isLoop = false;
		spx->setDelay(100);
		break;
	case DIE:
		isLoop = false;
		spx->setDelay(100);
		break;
	}
	spx->setAction(player_act, isLoop);
}

void CPlayer::set_move()
{
	bool spx_end = spx->isPlayOver(player_act);

	switch (player_act)
	{
	case CPlayer::Stand:
		break;
	case CPlayer::Walk:
		if (dir)
			x += move_speed;
		else
			x -= move_speed;
		break;
	case CPlayer::A1:
		break;
	case CPlayer::A2:
		break;
	case CPlayer::A3:
		break;
	case CPlayer::A4:
		break;
	case CPlayer::A5:
		if (dir)
			x +=3;
		else
			x -=3;
		Cmap::Getinstance()->set_snake(true);
		break;
	case CPlayer::Q:
		Cmap::Getinstance()->set_snake(true);
		break;
	case CPlayer::W:
		if (dir)
			x += 2;
		else
			x -= 2;
		if (spx_end)
		{
			Cmap::Getinstance()->set_snake(true);
		}
		break;
	case CPlayer::E:
		//if (spx_end)
		//{
		//	if (dir)
		//		x += 200;
		//	else
		//		x -= 200;
		//}
		break;
	case CPlayer::E2:
		if (!spx_end)
		{
			if (dir)
				x += 12;
			else
				x -= 12;
			break;
		}
	case CPlayer::R:
		break;
	case CPlayer::DIE:
		break;
	case CPlayer::hurted:
		if (dir)
			x -= 1.f;
		else
			x += 1.f;
		break;
	default:
		break;
	}

}

void CPlayer::hits_show()
{
	hits_time--;
	if (!hits || hits_time <= 0)
	{
		hits_buffer = hits = 0;
		hits_battle->set_show(false);
		hits_time = 0;
		return;
	}


	hits_battle->set_show(true);
	char temp[30];
	sprintf_s(temp, "%d hits", hits);

	if (hits_buffer == hits)
	{
		RECT rc = { 800,100,950,150 };
		pFont_small->DrawTextA(NULL,
			temp, -1, &rc, DT_LEFT | DT_TOP, D3DCOLOR_RGBA(255, 0, 0, 255));
	}
	else
	{

		RECT rc1 = { 770,90,950,150 };
		pFont_big->DrawTextA(NULL,
			temp, -1, &rc1, DT_LEFT | DT_TOP, D3DCOLOR_RGBA(255, 0, 0, 255));
		hits_buffer = hits;
	}

}

void CPlayer::set_camera(float m_x)
{
	is_camera = true;
	camera_x += m_speed;
	if (camera_x >= m_x)
	{
		//static int m_time = 150;
		m_time--;
		if (m_time>0)
		{
			m_speed = 0;
			camera_stand = true;
		}
		else
		{
			m_speed = -20;
			camera_stand = false;

		}
	}

	if (camera_x <= 0)
	{
		m_speed = 20;
		is_camera = false;
		camera_x = 0;
		m_time = 150;
	}
}

CPlayer * CPlayer::Get_Instance()
{
	if (!Instance)
		Instance = new CPlayer;
	return Instance;
}

void CPlayer::update()
{
	
	if (is_death)
	{
		return;
	}
	if (!is_death&&now_hp <= 0)
	{
		buffer_hp = 0;
		now_hp = 0;
		hurted_img->set_show(false);
		is_death = true;
		hits_battle->set_show(false);
		CAudio_management::Get_instance()->player_die_Audio_play();
		new CDie_Effect( x, y, L"other/player/1.png", L"other/player/2.png", L"other/player/3.png", L"other/player/4.png",
			L"other/player/5.png", L"other/player/6.png", L"other/player/7.png", L"other/player/8.png",
			L"other/player/9.png", L"other/player/10.png");
		return;
	}


	

	bool spx_end = spx->isPlayOver(player_act);

	if (player_act == E && spx_end )
	{
		set_state(E2);
	}
	
	//if (player_act == E2 && spx_end)
	//{
	//	//set_state(E3);
	//}
	
	set_move();
	if (GetAsyncKeyState(VK_LEFT) & 0x8000 && player_act == Stand && show_x >= 10
		|| GetAsyncKeyState(VK_LEFT) & 0x8000 && player_act == Walk && show_x >= 10
		|| GetAsyncKeyState(VK_LEFT) & 0x8000 && player_act == R && show_x >= 10)
	{
		switch (player_act)
		{
		case Stand:set_state(Walk); break;
		case Walk:dir = false; break;
		case R:
			bool R_over = spx->isPlayOver(R);
			x -= move_speed;
			if (R_over)
				set_state(Walk);
			break;
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && player_act == Stand && show_x <= WIN_X
		|| GetAsyncKeyState(VK_RIGHT) & 0x8000 && player_act == Walk && show_x <= WIN_X
		|| GetAsyncKeyState(VK_RIGHT) & 0x8000 && player_act == R && show_x <= WIN_X)
	{
		switch (player_act)
		{
		case Stand:set_state(Walk); break;
		case Walk:dir = true; break;
		case R:
			bool R_over = spx->isPlayOver(R);
			x += move_speed;
			if (R_over)
				set_state(Walk);
			break;
		}
	}

	else if (GetAsyncKeyState('A') & 0x8000 && player_act== Stand )
	{
		if (a_load->getstate())
		{
			switch (a_act)
			{
			case 0:set_state(A1);
				CAudio_management::Get_instance()->player_a1_Audio_play();
				break;
			case 1:set_state(A2);
				CAudio_management::Get_instance()->player_a2_Audio_play();
				break;
			case 2:set_state(A3);
				CAudio_management::Get_instance()->player_a3_Audio_play();
				break;
			case 3:set_state(A4);
				CAudio_management::Get_instance()->player_a4_Audio_play();
				break;
			case 4:set_state(A5);
				CAudio_management::Get_instance()->player_a5_Audio_play();
				break;
			}
			a_act++;
			if (a_act > 4)
				a_act = 0;
			a_load->play();
			A_time = 0.f;
		}
	}
	else if (GetAsyncKeyState('Q') & 0x8000 && player_act == Stand)
	{
		if (q_load->getstate())
		{
			set_state(Q);
			Q_time = 0.f;
			q_load->play();
			CAudio_management::Get_instance()->player_Q_Audio_play();
		}
	}
	else if (GetAsyncKeyState('W') & 0x8000 && player_act == Stand)
	{
		if (w_load->getstate())
		{
			set_state(W);
			w_load->play();
			W_time = 0.f;
			CAudio_management::Get_instance()->player_W_Audio_play();
		}
	}
	else if (GetAsyncKeyState('E') & 0x8000 && player_act == Stand)
	{
		if (e_load->getstate())
		{
			set_state(E);
			e_load->play();
			E_time = 0.f;
			CAudio_management::Get_instance()->player_E_Audio_play();
		}
	}
	else if (GetAsyncKeyState('R') & 0x8000 && player_act == Stand)
	{
		if (r_load->getstate())
		{
			set_state(R);
			R_time = 0.f;
			r_load->play();
			CAudio_management::Get_instance()->player_R_Audio_play();
		}
	}
	else
	{
		if (spx->isPlayOver(player_act))
		{
			set_state(Stand);
		}
	}

	if (is_hurted)
	{
		hurted_time = 5;
		new CHurted_num(L"img/num_herohit.png", hurted_num, x - 30, y - 150);
		is_hurted = false;
	}

	if (hurted_time > 0)
	{
		hurted_time--;
		hurted_img->set_show(true);
	}
	
	else
	{
		hurted_img->set_show(false);
	}

	if (buffer_hp > now_hp)
	{
		buffer_hp -= 99;
		if (buffer_hp < now_hp)
		{
			buffer_hp = now_hp;
		}
	}

	

	int max_x = (Cmap::Getinstance()->get_map_x() - WIN_X);
	int min_x = min(x - WIN_X / 2, max_x);
	int temp_x = max(0, min_x);
	


	int max_y = (Cmap::Getinstance()->get_map_y() - WIN_Y);
	int min_y = min(y - WIN_Y / 2, max_y);
	int temp_y = max(0, min_y);




	if (is_camera)
	{
		x = 3000;
		set_state(Stand);
	}

	show_x = x + Cmap::Getinstance()->get_offset_x();//最终显示的坐标
	show_y = y - Cmap::Getinstance()->get_offset_y();

	Cmap::Getinstance()->set_offset(-temp_x - camera_x, -temp_y);
	Cmap::Getinstance()->update();


	if (x<=10)
	{
		x = 10;
	}
	else if (x >= Cmap::Getinstance()->get_map_x() - 10)
	{
		x = Cmap::Getinstance()->get_map_x() - 10;
	}
	if (hp_show && player_act!=E2)
	{
		hp_rect.set_color(0, 255, 0);
		hp_rect.set_hp(now_hp / all_hp, show_x, show_y);
	}
}
	

void CPlayer::show()
{
	float temptime = CPlatForm::Getinstance()->updateTime();

	a_load->update(temptime);
	q_load->update(temptime);
	w_load->update(temptime);
	e_load->update(temptime);
	r_load->update(temptime);

	A_time++;
	if (A_CD - A_time / FPS >= 0)
	{
		char a_time[30];
		sprintf_s(a_time, " %.1f", A_CD - A_time / FPS);
		RECT rc = { 795,480,950,640 };
		CPlatForm::Getinstance()->get_p_font()->DrawTextA(NULL, a_time, -1,
			&rc, DT_LEFT | DT_TOP, D3DCOLOR_RGBA(255, 255, 255, 150));
	}
	Q_time++;
	if (Q_CD - Q_time / FPS >= 0)
	{
		char q_time[30];
		sprintf_s(q_time, " %.1f", Q_CD - Q_time / FPS);
		RECT rc = { 713,490,950,550 };
		CPlatForm::Getinstance()->get_p_font()->DrawTextA(NULL, q_time, -1,
			&rc, DT_LEFT | DT_TOP, D3DCOLOR_RGBA(255, 255, 255, 150));
	}
	W_time++;
	if (W_CD - W_time / FPS >= 0)
	{
		char w_time[30];
		sprintf_s(w_time, " %.1f", W_CD - W_time / FPS);
		RECT rc = { 733,410,950,550 };
		CPlatForm::Getinstance()->get_p_font()->DrawTextA(NULL, w_time, -1,
			&rc, DT_LEFT | DT_TOP, D3DCOLOR_RGBA(255, 255, 255, 150));
	}
	E_time++;
	if (E_CD - E_time / FPS >= 0)
	{
		char e_time[30];
		sprintf_s(e_time, " %.1f", E_CD - E_time / FPS);
		RECT rc = { 818,395,950,550 };
		CPlatForm::Getinstance()->get_p_font()->DrawTextA(NULL, e_time, -1,
			&rc, DT_LEFT | DT_TOP, D3DCOLOR_RGBA(255, 255, 255, 150));
	}
	R_time++;
	if (R_CD - R_time / FPS >= 0)
	{
		char r_time[30];
		sprintf_s(r_time, " %.1f", R_CD - R_time / FPS);
		RECT rc = { 893,450,950,500 };
		CPlatForm::Getinstance()->get_p_font()->DrawTextA(NULL, r_time, -1,
			&rc, DT_LEFT | DT_TOP, D3DCOLOR_RGBA(255, 255, 255, 150));
	}
	

	hits_show();
	spx->setPosition(show_x, show_y + Cmap::Getinstance()->get_snake());
	spx->setFlipX(dir ? false : true);
	spx->update();
	spx->draw();
}

void CPlayer::reset()
{
	hp_show = true;
	is_death = false;
	x = 100;//X坐标
	y = 365;//Y坐标365
	camera_x = 0;
	show_x = x;
	show_y = y;
	hurted_num = 0;
	dir = true;//翻转
	buffer_hp = now_hp = all_hp;
	player_act = Stand;//动作序号
	spx->setAction(player_act);//设置动作
	spx->setDelay(150);
	is_camera = false;
	camera_stand = false;


}

void CPlayer::set_hurted(int hurted_num)
{
	now_hp -= hurted_num;
	if (hurted_time <= 0)
	{
		is_hurted = true;
		this->hurted_num = hurted_num;
	}
	
}

void CPlayer::set_hurted_fly(bool _dir, int hurted_num)
{
	CAudio_management::Get_instance()->player_R_Audio_stop();
	if (_dir)
	{
		dir = true;
	}
	else
	{
		dir = false;
	}
	now_hp -= hurted_num; 
	set_state(hurted);
	if (hurted_time <= 0)
	{
		is_hurted = true;
		this->hurted_num = hurted_num;
	}
	
	
}

CPlayer::CPlayer()
{
	Q_time = W_time = E_time = R_time = A_time = 0.f;
	TiXmlDocument *Document = new TiXmlDocument;
	Document->LoadFile("Xml/player.xml");
	TiXmlElement *Root_Element = Document->RootElement();
	TiXmlElement *FirstChild_Element = Root_Element->FirstChildElement();

	//string c = FirstChild_Element->Attribute("class");

	TiXmlElement *Text = FirstChild_Element->FirstChildElement();
	show_x = x = atoi(Text->Attribute("pos.x"));
	show_y = y = atoi(Text->Attribute("pos.y"));
	move_speed = atoi(Text->FirstChildElement("move_speed")->GetText());
	money = atoi(Text->FirstChildElement("Money")->GetText());
	zuansi= atoi(Text->FirstChildElement("zuansi")->GetText());
	buffer_hp = now_hp = all_hp = atoi(Text->FirstChildElement("HP")->GetText());
	A1_hurted = atoi(Text->FirstChildElement("A1")->GetText());
	A2_hurted = atoi(Text->FirstChildElement("A2")->GetText());
	A3_hurted = atoi(Text->FirstChildElement("A3")->GetText());
	A4_hurted = atoi(Text->FirstChildElement("A4")->GetText());
	A5_hurted = atoi(Text->FirstChildElement("A5")->GetText());
	Q_hurted = atoi(Text->FirstChildElement("Q")->GetText());
	W_hurted = atoi(Text->FirstChildElement("W")->GetText());
	E_hurted = atoi(Text->FirstChildElement("E")->GetText());
	R_hurted = atoi(Text->FirstChildElement("R")->GetText());
	camera_x = atoi(Text->FirstChildElement("camera_x")->GetText());
	hp_show = (bool)atoi(Text->FirstChildElement("hp_show")->GetText());
	dir = (bool)atoi(Text->FirstChildElement("dir")->GetText());
	is_death = (bool)atoi(Text->FirstChildElement("is_death")->GetText());
	Q_CD = (float)atoi(Text->FirstChildElement("Q_CD")->GetText());
	W_CD = (float)atoi(Text->FirstChildElement("W_CD")->GetText());
	E_CD = (float)atoi(Text->FirstChildElement("E_CD")->GetText());
	R_CD = (float)atoi(Text->FirstChildElement("R_CD")->GetText());
	A_CD = (float)atoi(Text->FirstChildElement("A_CD")->GetText());

	A_CD = 0.5f;
	char *player_sprite = new char[strlen(Text->FirstChildElement("player_sprite")->GetText()) + 1];
	strcpy(player_sprite, Text->FirstChildElement("player_sprite")->GetText());
	char *player_png = new char[strlen(Text->FirstChildElement("player_sprite")->GetText()) + 1];
	strcpy(player_png, Text->FirstChildElement("player_png")->GetText());
	spx = new SpriteX(CPlatForm::Getinstance()->Get_pd3dDevice(), player_sprite, player_png);
	delete player_sprite, player_png;
	player_png = player_sprite = NULL;

	Document->Clear();
	delete Document;
	Document = NULL;
	//A_CD = 0.5f;
	player_act = Stand;//动作序号
	spx->setAction(player_act);//设置动作
	spx->setDelay(150);
	is_camera = false;
	camera_stand = false;

	hurted_num = 0;
	is_hurted = false;
	hurted_time = 0;
	hurted_img = new CUI_img(L"img/hurted.png");
	hurted_img->set_pos(0, 0);
	hurted_img->set_show(false);
	hurted_img->set_sort(-7);


	

	D3DXCreateFont(CPlatForm::Getinstance()->Get_pd3dDevice(), 30, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"ChickenScratch AOE", &pFont_small);//设置字体属性 楷体_GB2312

	D3DXCreateFont(CPlatForm::Getinstance()->Get_pd3dDevice(), 50, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"ChickenScratch AOE", &pFont_big);
	
	hits = 0;
	hits_buffer = hits;
	hits_battle = new CUI_img(L"img/black_title.png");
	hits_battle->set_pos(770, 90);
	hits_battle->set_show(false);
	hits_battle->set_sort(-4);
	hits_time = 200;



	a_act = 0;
	a_img = new CUI_img(L"img/A.png");
	a_img->set_pos(780, 450);
	a_img->set_sort(-1);
	a_img->set_scale(0.6f);
	a_load = new DX_CircleAnim(CPlatForm::Getinstance()->Get_pd3dDevice(), 824, 490, 44, L"img/button_circle.png");
	a_load->setTotalTimer(A_CD);//冷却时间
	a_load->play();

	q_img = new CUI_img(L"img/Q.png");
	q_img->set_pos(700, 460);
	q_img->set_sort(-1);
	q_load = new DX_CircleAnim(CPlatForm::Getinstance()->Get_pd3dDevice(), 738, 499, 38, L"img/button_circle.png");
	q_load->setTotalTimer(Q_CD);//冷却时间
	q_load->play();

	w_img = new CUI_img(L"img/W.png");
	w_img->set_pos(720, 380);
	w_img->set_sort(-1);
	w_load = new DX_CircleAnim(CPlatForm::Getinstance()->Get_pd3dDevice(), 758, 419, 38, L"img/button_circle.png");
	w_load->setTotalTimer(W_CD);//冷却时间
	w_load->play();
	
	e_img = new CUI_img(L"img/E.png");
	e_img->set_pos(805, 365);
	e_img->set_sort(-1);
	e_load = new DX_CircleAnim(CPlatForm::Getinstance()->Get_pd3dDevice(), 843, 404, 38, L"img/button_circle.png");
	e_load->setTotalTimer(E_CD);//冷却时间
	e_load->play();

	r_img = new CUI_img(L"img/R.png");
	r_img->set_pos(880, 420);
	r_img->set_sort(-1);
	r_load = new DX_CircleAnim(CPlatForm::Getinstance()->Get_pd3dDevice(), 918, 459, 38, L"img/button_circle.png");
	r_load->setTotalTimer(R_CD);//冷却时间
	r_load->play();

}


CPlayer::~CPlayer()
{
	
}

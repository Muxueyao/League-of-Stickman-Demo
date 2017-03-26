#include "stdafx.h"



void CBoss::set_move()
{
	bool act_over = spx->isPlayOver(bossact);
	switch (bossact)
	{
	case CBoss::stand:

		break;
	case CBoss::move:

		if (dir)
			x -= move_speed;
		else
			x += move_speed;
		break;
	case CBoss::a1:
		if (CPlayer::Get_Instance()->Get_spx()->collidesWith(spx, 1, 0, COLLISION_AABB))
		{
			CPlayer::Get_Instance()->set_hurted(rand() % a1_hurted);
		}
		break;
	case CBoss::a2:
		if (CPlayer::Get_Instance()->Get_spx()->collidesWith(spx, 1, 0, COLLISION_AABB))
		{
			CPlayer::Get_Instance()->set_hurted(rand() % a2_hurted);
		}
		break;
	case CBoss::a3:
		if (CPlayer::Get_Instance()->Get_spx()->collidesWith(spx, 1, 0, COLLISION_AABB))
		{
			CPlayer::Get_Instance()->set_hurted(rand() % a3_hurted);
		}
		break;
	case CBoss::a4:
		if (CPlayer::Get_Instance()->Get_spx()->collidesWith(spx, 1, 0, COLLISION_AABB))
		{
			CPlayer::Get_Instance()->set_hurted(rand() % a4_hurted);
		}
		break;
	case CBoss::a5:
		if (CPlayer::Get_Instance()->Get_spx()->collidesWith(spx, 1, 0, COLLISION_AABB))
		{
			CPlayer::Get_Instance()->set_hurted(rand() % a5_hurted);
		}
		break;
	case CBoss::q1:
		if (CPlayer::Get_Instance()->Get_spx()->collidesWith(spx, 1, 0, COLLISION_AABB))
		{
			CPlayer::Get_Instance()->set_hurted(rand() % q1_hurted);
		}
		break;
	case CBoss::q2:
		if (Q_dir)
		{
			Q_x -= 15;
		}
		else
		{
			Q_x += 15;
		}
		Q_spx->setFlipX(Q_dir);
		Q_spx->update();
		Q_spx->draw();
		
		Q_spx->setPosition(Q_x + Cmap::Getinstance()->get_offset_x(), Q_y + 10);
		if (CPlayer::Get_Instance()->Get_spx()->collidesWith(Q_spx, 0, 0, COLLISION_AABB))
		{
			CPlayer::Get_Instance()->set_hurted_fly(dir,rand() % q2_hurted);
		}

		break;
	case CBoss::w1:
		if (CPlayer::Get_Instance()->Get_spx()->collidesWith(spx, 1, 0, COLLISION_AABB))
		{
			CPlayer::Get_Instance()->set_hurted(rand() % w1_hurted);
		}
		break;
	case CBoss::w2:
		if (CPlayer::Get_Instance()->Get_spx()->collidesWith(spx, 1, 0, COLLISION_AABB))
		{
			CPlayer::Get_Instance()->set_hurted(rand() % w2_hurted);
		}
		break;
	case CBoss::w3:
		if (CPlayer::Get_Instance()->Get_spx()->collidesWith(spx, 1, 0, COLLISION_AABB))
		{
			CPlayer::Get_Instance()->set_hurted(rand() % w3_hurted);
		}
		break;
	case CBoss::w4:
		if (CPlayer::Get_Instance()->Get_spx()->collidesWith(spx, 1, 0, COLLISION_AABB))
		{
			CPlayer::Get_Instance()->set_hurted(rand() % w4_hurted);
		}
		break;
	case CBoss::w5:
		if (CPlayer::Get_Instance()->Get_spx()->collidesWith(spx, 1, 0, COLLISION_AABB))
		{
			CPlayer::Get_Instance()->set_hurted(rand() % w5_hurted);
		}
		break;
	case CBoss::w6:
		if (CPlayer::Get_Instance()->Get_spx()->collidesWith(spx, 1, 0, COLLISION_AABB))
		{
			CPlayer::Get_Instance()->set_hurted(rand() % w6_hurted);
		}
		break;
	case CBoss::e:
		if (CPlayer::Get_Instance()->Get_spx()->collidesWith(spx, 1, 0, COLLISION_AABB))
		{
			CPlayer::Get_Instance()->set_hurted(rand() % e_hurted);
		}
		break;
	case CBoss::r1:
		if (CPlayer::Get_Instance()->Get_spx()->collidesWith(spx, 1, 0, COLLISION_AABB))
		{
			CPlayer::Get_Instance()->set_hurted(rand() % r1_hurted);
		}
		break;
	case CBoss::r2:
		if (CPlayer::Get_Instance()->Get_spx()->collidesWith(spx, 1, 0, COLLISION_AABB))
		{
			CPlayer::Get_Instance()->set_hurted(rand() % r2_hurted);
		}
		break;
	case CBoss::r3:
		if (CPlayer::Get_Instance()->Get_spx()->collidesWith(spx, 1, 0, COLLISION_AABB))
		{
			CPlayer::Get_Instance()->set_hurted(rand() % r3_hurted);
		}
		break;
	case CBoss::r4:
		if (CPlayer::Get_Instance()->Get_spx()->collidesWith(spx, 1, 0, COLLISION_AABB))
		{
			CPlayer::Get_Instance()->set_hurted(rand() % r4_hurted);
		}
		break;
	case CBoss::r5:
		if (CPlayer::Get_Instance()->Get_spx()->collidesWith(spx, 1, 0, COLLISION_AABB))
		{
			CPlayer::Get_Instance()->set_hurted(rand() % r5_hurted);
		}
		break;
	case CBoss::r6:
		if (CPlayer::Get_Instance()->Get_spx()->collidesWith(spx, 1, 0, COLLISION_AABB))
		{
			CPlayer::Get_Instance()->set_hurted_fly(dir, rand() % r6_hurted + r6_hurted);
		}
		Cmap::Getinstance()->set_snake(true);
		break;
	case CBoss::hurted:
		break;
	}
	if (num_once == 0)
	{
		npcout_Audio.ChannelPlay(0, true);
		num_once++;
	}
}

void CBoss::set_state(BOSSACT _act)
{
	bossact = _act;
	bool act_over = spx->isPlayOver(bossact);

	bool isLoop = false;
	switch (bossact)
	{
	case stand:
		isLoop = true;
		spx->setDelay(20);
		break;
	case move:
		isLoop = true;
		spx->setDelay(30);
		break;
	case a1:
		isLoop = false;
		spx->setDelay(50);
		break;
	case a2:
		isLoop = false;
		spx->setDelay(50);
		break;
	case a3:
		isLoop = false;
		spx->setDelay(50);
		break;
	case a4:
		isLoop = false;
		spx->setDelay(50);
		break;
	case a5:
		isLoop = false;
		spx->setDelay(50);
		break;
	case q1:
		isLoop = false;
		spx->setDelay(50);
		break;
	case q2:
		isLoop = false;
		spx->setDelay(50);
		break;
	case w1:
		isLoop = false;
		spx->setDelay(50);
		break;
	case w2:
		isLoop = false;
		spx->setDelay(50);
		break;
	case w3:
		isLoop = false;
		spx->setDelay(50);
		break;
	case w4:
		isLoop = false;
		spx->setDelay(50);
		break;
	case w5:
		isLoop = false;
		spx->setDelay(50);
		break;
	case w6:
		isLoop = false;
		spx->setDelay(50);
		break;
	case e:
		isLoop = false;
		spx->setDelay(50);
		break;
	case r1:
		isLoop = false;
		spx->setDelay(50);
		break;
	case r2:
		isLoop = false;
		spx->setDelay(50);
		break;
	case r3:
		isLoop = false;
		spx->setDelay(50);
		break;
	case r4:
		isLoop = false;
		spx->setDelay(50);
		break;
	case r5:
		isLoop = false;
		spx->setDelay(50);
		break;
	case r6:
		isLoop = false;
		spx->setDelay(50);
		break;
	case hurted:
		isLoop = false;
		spx->setDelay(50);
		break;
	}
	spx->setAction(bossact, isLoop);
}

void CBoss::update()
{
	if (now_hp <= 0 && num_once == 1)
	{
		new CMoney_drop(x, y);
			
		new CDie_Effect(x, y, L"other/npc/boss/1.png", L"other/npc/boss/2.png", L"other/npc/boss/3.png", L"other/npc/boss/4.png",
				L"other/npc/boss/5.png", L"other/npc/boss/6.png", L"other/npc/boss/7.png", L"other/npc/boss/8.png",
				L"other/npc/boss/9.png", L"other/npc/boss/10.png");
		die_Audio.ChannelPlay(0, true);
		set_del(true);
		num_once++;
	}

	set_move();

	bool act_over = spx->isPlayOver(bossact);

	show_x = x + Cmap::Getinstance()->get_offset_x();
	show_y = y + Cmap::Getinstance()->get_offset_y() + Cmap::Getinstance()->get_snake();

	//玩家与BOSS坐标判断朝向
	if (CPlayer::Get_Instance()->get_show_x() < show_x)
	{
		dir = true;
	}
	else
	{
		dir = false;
	}
	//与玩家间距触发攻击
	if (abs(CPlayer::Get_Instance()->get_show_x() - show_x) <= 300 && bossact != stand
		|| bossact == w1 || bossact == w2 || bossact == w3 || bossact == w4 || bossact == w5
		|| bossact == r1 || bossact == r2 || bossact == r3 || bossact == r4 || bossact == r5)
	{
		if (act_over)
		{
			switch (act_num)
			{
			case 1:set_state(a1);A1_Audio.ChannelPlay(0, true);break;
			case 2:set_state(a2);A2_Audio.ChannelPlay(0, true);break;
			case 3:set_state(a3);A3_Audio.ChannelPlay(0, true);break;
			case 4:set_state(a4);A4_Audio.ChannelPlay(0, true);break;
			case 5:set_state(a5);A5_Audio.ChannelPlay(0, true);break;

			case 6:set_state(q1);Q1_Audio.ChannelPlay(0, true);break;
			case 7:set_state(q2);
				Q_dir = dir;
				Q_x = x;
				Q_y = y;
				Q_spx->setAction(1, true);
				Q_spx->setDelay(50);
				Q2_Audio.ChannelPlay(0, true);break;

			case 8:set_state(w1);W1_Audio.ChannelPlay(0, true);break;
			case 9:set_state(w2);W2_Audio.ChannelPlay(0, true);break;
			case 10:set_state(w3);W3_Audio.ChannelPlay(0, true);break;
			case 11:set_state(w4);W4_Audio.ChannelPlay(0, true);break;
			case 12:set_state(w5);W5_Audio.ChannelPlay(0, true);break;
			case 13:set_state(w6);W6_Audio.ChannelPlay(0, true);break;

			case 14:set_state(e);
				if (dir)
					x -= 200;
				else
				{
					x += 200;
				}
				E_Audio.ChannelPlay(0, true);break;

			case 15:set_state(r1);
				R_Audio.ChannelPlay(0, true);
				R1_Audio.ChannelPlay(0, true);
				break;
			case 16:set_state(r2);R2_Audio.ChannelPlay(0, true);break;
			case 17:set_state(r3);R3_Audio.ChannelPlay(0, true);break;
			case 18:set_state(r4);R4_Audio.ChannelPlay(0, true);break;
			case 19:set_state(r5);R5_Audio.ChannelPlay(0, true);break;
			case 20:set_state(r6);R6_Audio.ChannelPlay(0, true);
				if (dir)
					x -= 150;
				else
				{
					x += 150;
				}
				break;
			default:
				act_num = 0;break;
			}
			++act_num;
		}
	}
	else
	{
		if (act_over)
			set_state(move);
	}


	Head_hp_rect2->set_rect(0, 0, Head_hp_rect2->get_img_x()*now_hp/all_hp, Head_hp_rect2->get_img_y());
	if (buffer_hp>now_hp)
	{
		buffer_hp -= 60;
		if (buffer_hp<now_hp)
		{
			buffer_hp = now_hp;
		}
	}
	Head_hp_buffer_rect->set_rect(0, 0, Head_hp_buffer_rect->get_img_x()*buffer_hp / all_hp, Head_hp_buffer_rect->get_img_y());


	
}

void CBoss::show()
{
	RECT rc1 = { 85,25,400,100 };
	CPlatForm::Getinstance()->get_p_font()->DrawTextA(NULL, "BOSS", -1, &rc1, DT_LEFT | DT_TOP, D3DCOLOR_RGBA(0, 255, 255, 255));

	char temp_hp[30];
	sprintf_s(temp_hp, "%.0f/%.0f", now_hp, all_hp);
	RECT rc = { 180,56,400,100 };
	CPlatForm::Getinstance()->get_p_font()->DrawTextA(NULL, temp_hp, -1, &rc, DT_LEFT | DT_TOP, D3DCOLOR_RGBA(0, 255, 0, 150));
	//hp_rect.set_hp(now_hp / all_hp, show_x, show_y-50);
	spx->setFlipX(dir);
	spx->update();
	spx->draw();
	spx->setPosition(show_x, show_y);
	if (hurted_time > 0)
	{
		hurted_spx->setPosition(show_x, show_y);
		hurted_spx->setFlipX(dir);
		hurted_spx->update();
		hurted_spx->draw();
		hurted_time--;
	}
}

void CBoss::Release()
{
	Head_img->set_del(true);
	Head_hp_rect->set_del(true);
	Head_hp_rect2->set_del(true);
	Head_hp_buffer_rect->set_del(true);
}

CBoss::CBoss()
{

	TiXmlDocument *Document = new TiXmlDocument;
	Document->LoadFile("Xml/boss.xml");
	TiXmlElement *Root_Element = Document->RootElement();
	TiXmlElement *FirstChild_Element = Root_Element->FirstChildElement();

	TiXmlElement *Text = FirstChild_Element->FirstChildElement();
	show_x = x = atoi(Text->Attribute("pos.x"));
	show_y = y = atoi(Text->Attribute("pos.y"));
	move_speed = atoi(Text->FirstChildElement("move_speed")->GetText());
	buffer_hp = now_hp = all_hp = atoi(Text->FirstChildElement("HP")->GetText());
	a1_hurted = atoi(Text->FirstChildElement("a1_hurted")->GetText());
	a2_hurted = atoi(Text->FirstChildElement("a2_hurted")->GetText());
	a3_hurted = atoi(Text->FirstChildElement("a3_hurted")->GetText());
	a4_hurted = atoi(Text->FirstChildElement("a4_hurted")->GetText());
	a5_hurted = atoi(Text->FirstChildElement("a5_hurted")->GetText());
	q1_hurted = atoi(Text->FirstChildElement("q1_hurted")->GetText());
	q2_hurted = atoi(Text->FirstChildElement("q2_hurted")->GetText());
	w1_hurted = atoi(Text->FirstChildElement("w1_hurted")->GetText());
	w2_hurted = atoi(Text->FirstChildElement("w2_hurted")->GetText());
	w3_hurted = atoi(Text->FirstChildElement("w3_hurted")->GetText());
	w4_hurted = atoi(Text->FirstChildElement("w4_hurted")->GetText());
	w5_hurted = atoi(Text->FirstChildElement("w5_hurted")->GetText());
	w6_hurted = atoi(Text->FirstChildElement("w6_hurted")->GetText());
	e_hurted = atoi(Text->FirstChildElement("e_hurted")->GetText());
	r1_hurted = atoi(Text->FirstChildElement("r1_hurted")->GetText());
	r2_hurted = atoi(Text->FirstChildElement("r2_hurted")->GetText());
	r3_hurted = atoi(Text->FirstChildElement("r3_hurted")->GetText());
	r4_hurted = atoi(Text->FirstChildElement("r4_hurted")->GetText());
	r5_hurted = atoi(Text->FirstChildElement("r5_hurted")->GetText());
	r6_hurted = atoi(Text->FirstChildElement("r6_hurted")->GetText());


	spx = new SpriteX(CPlatForm::Getinstance()->Get_pd3dDevice(), "other/npc/boss/boss.sprite", "other/npc/boss/1011_role.png");

	dir = true;//翻转
	bossact = Show;
	spx->setAction(bossact);
	spx->setDelay(20);

	Q_spx = new SpriteX(CPlatForm::Getinstance()->Get_pd3dDevice(), "other/npc/boss/Yasuo_Q.sprite", "other/npc/boss/1011_Q3_effup.png");
	Q_spx->setAction(0);
	Q_spx->setDelay(0);
	Q_spx->setScale(2);
	Q_x = Q_y = 0;
	Q_dir = dir;

	//buffer_hp = now_hp = all_hp = 100000;
	int m_MusicIndex;//临时变量，配置音频

	npcout_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = npcout_Audio.LoadFile("audio/monsterout/monsterout.mp3", BASS_MUSIC_MONO);
	npcout_Audio.ChannelBytes2Seconds(m_MusicIndex, npcout_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	die_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = die_Audio.LoadFile("audio/monster/boss/die.mp3", BASS_MUSIC_MONO);
	die_Audio.ChannelBytes2Seconds(m_MusicIndex, die_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	A1_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = A1_Audio.LoadFile("audio/monster/boss/a1.mp3", BASS_MUSIC_MONO);
	A1_Audio.ChannelBytes2Seconds(m_MusicIndex, A1_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	A2_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = A2_Audio.LoadFile("audio/monster/boss/a2.mp3", BASS_MUSIC_MONO);
	A2_Audio.ChannelBytes2Seconds(m_MusicIndex, A2_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	A3_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = A3_Audio.LoadFile("audio/monster/boss/a3.mp3", BASS_MUSIC_MONO);
	A3_Audio.ChannelBytes2Seconds(m_MusicIndex, A3_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	A4_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = A4_Audio.LoadFile("audio/monster/boss/a4.mp3", BASS_MUSIC_MONO);
	A4_Audio.ChannelBytes2Seconds(m_MusicIndex, A4_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	A5_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = A5_Audio.LoadFile("audio/monster/boss/a5.mp3", BASS_MUSIC_MONO);
	A5_Audio.ChannelBytes2Seconds(m_MusicIndex, A5_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	Q1_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = Q1_Audio.LoadFile("audio/monster/boss/q1.mp3", BASS_MUSIC_MONO);
	Q1_Audio.ChannelBytes2Seconds(m_MusicIndex, Q1_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	Q2_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = Q2_Audio.LoadFile("audio/monster/boss/q2.mp3", BASS_MUSIC_MONO);
	Q2_Audio.ChannelBytes2Seconds(m_MusicIndex, Q2_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	W1_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = W1_Audio.LoadFile("audio/monster/boss/w1.mp3", BASS_MUSIC_MONO);
	W1_Audio.ChannelBytes2Seconds(m_MusicIndex, W1_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	W2_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = W2_Audio.LoadFile("audio/monster/boss/w2.mp3", BASS_MUSIC_MONO);
	W2_Audio.ChannelBytes2Seconds(m_MusicIndex, W2_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));


	W3_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = W3_Audio.LoadFile("audio/monster/boss/w3.mp3", BASS_MUSIC_MONO);
	W3_Audio.ChannelBytes2Seconds(m_MusicIndex, W3_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	W4_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = W4_Audio.LoadFile("audio/monster/boss/w4.mp3", BASS_MUSIC_MONO);
	W4_Audio.ChannelBytes2Seconds(m_MusicIndex, W4_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	W5_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = W5_Audio.LoadFile("audio/monster/boss/w5.mp3", BASS_MUSIC_MONO);
	W5_Audio.ChannelBytes2Seconds(m_MusicIndex, W5_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	W6_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = W6_Audio.LoadFile("audio/monster/boss/w6.mp3", BASS_MUSIC_MONO);
	W6_Audio.ChannelBytes2Seconds(m_MusicIndex, W6_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));


	E_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = E_Audio.LoadFile("audio/monster/boss/e1.mp3", BASS_MUSIC_MONO);
	E_Audio.ChannelBytes2Seconds(m_MusicIndex, E_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	R_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = R_Audio.LoadFile("audio/monster/boss/r1.mp3", BASS_MUSIC_MONO);
	R_Audio.ChannelBytes2Seconds(m_MusicIndex, R_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	R1_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = R1_Audio.LoadFile("audio/monster/boss/r2.mp3", BASS_MUSIC_MONO);
	R1_Audio.ChannelBytes2Seconds(m_MusicIndex, R1_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	R2_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = R2_Audio.LoadFile("audio/monster/boss/r3.mp3", BASS_MUSIC_MONO);
	R2_Audio.ChannelBytes2Seconds(m_MusicIndex, R2_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	R3_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = R3_Audio.LoadFile("audio/monster/boss/r4.mp3", BASS_MUSIC_MONO);
	R3_Audio.ChannelBytes2Seconds(m_MusicIndex, R3_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	R4_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = R4_Audio.LoadFile("audio/monster/boss/r5.mp3", BASS_MUSIC_MONO);
	R4_Audio.ChannelBytes2Seconds(m_MusicIndex, R4_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	R5_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = R5_Audio.LoadFile("audio/monster/boss/r6.mp3", BASS_MUSIC_MONO);
	R5_Audio.ChannelBytes2Seconds(m_MusicIndex, R5_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	R6_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = R6_Audio.LoadFile("audio/monster/boss/r7.mp3", BASS_MUSIC_MONO);
	R6_Audio.ChannelBytes2Seconds(m_MusicIndex, R6_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	
	Head_img = new CUI_img(L"other/npc/boss/7.png");
	Head_img->set_scale(2.f);
	Head_img->set_pos(10, 10);
	Head_img->set_sort(-5);
	Head_hp_rect = new CUI_img(L"img/UI_hp.png");
	Head_hp_rect->set_pos(45, 53);
	Head_hp_rect->set_sort(-5);
	Head_hp_rect2 = new CUI_img(L"img/UI_rect.png");
	Head_hp_rect2->set_pos(48, 56);
	Head_hp_rect2->set_sort(-4);
	Head_hp_rect2->set_color(255, 0, 0);

	Head_hp_buffer_rect = new CUI_img(L"img/UI_rect.png");
	Head_hp_buffer_rect->set_pos(48, 56);
	Head_hp_buffer_rect->set_sort(-3);
	

	

	CNpc_Management::Get_instance()->add(this);
}


CBoss::~CBoss()
{
}

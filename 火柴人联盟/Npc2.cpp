#include "stdafx.h"



void CNpc2::set_state(ACT _act)
{
	act = _act;

	bool act_over = spx->isPlayOver(act);

	bool isLoop = false;
	switch (act)
	{
	case move:
		isLoop = true;
		spx->setDelay(40);
		break;
	case atk1:
		isLoop = true;
		spx->setDelay(200);
		break;
	case atk2:
		isLoop = false;
		spx->setDelay(200);
		break;
	case hurted_fly:
		isLoop = false;
		spx->setDelay(100);
		break;
	case hurted:
		isLoop = false;
		spx->setDelay(100);
		break;
	case die:
		isLoop = false;
		spx->setDelay(150);
		break;
	case Show:
		isLoop = false;
		spx->setDelay(100);
		break;
	}
	spx->setAction(act, isLoop);
}

void CNpc2::update()
{
	if (now_hp <= 0 && num_once == 1)
	{
		
		new CDie_Effect(x, y, L"other/npc/npc2/1.png", L"other/npc/npc2/2.png", L"other/npc/npc2/3.png", L"other/npc/npc2/4.png",
			L"other/npc/npc2/5.png", L"other/npc/npc2/6.png", L"other/npc/npc2/7.png", L"other/npc/npc2/8.png",
			L"other/npc/npc2/9.png", L"other/npc/npc2/10.png");
		npc2_die_Audio.ChannelPlay(0, true);
		new CMoney_drop(x, y);
		set_del(true);
		num_once++;
	}
	
	if (is_hurted)
	{
		if (CPlayer::Get_Instance()->get_act() == CPlayer::Get_Instance()->Q
			|| CPlayer::Get_Instance()->get_act() == CPlayer::Get_Instance()->A5)
		{
			set_state(hurted_fly);
		}
		else
		{
			set_state(hurted);
		}
		is_hurted = false;
		npc2_Atk1_Audio.ChannelStop(0);
		npc2_Atk2_Audio.ChannelStop(0);
	}

	bool act_over = spx->isPlayOver(act);

	set_move();

	show_x = x + Cmap::Getinstance()->get_offset_x();
	show_y = y + Cmap::Getinstance()->get_offset_y();

	if (show_x > CPlayer::Get_Instance()->get_show_x())
		dir = true;
	if (show_x < CPlayer::Get_Instance()->get_show_x())
		dir = false;

	if (show_x > CPlayer::Get_Instance()->get_show_x() + to_player_x && act_over)
	{
		set_state(move);
	}
	else if (show_x < CPlayer::Get_Instance()->get_show_x() - to_player_x && act_over)
	{
		set_state(move);
	}
	else
	{
		if (act_over)
		{
			if (a_act==0)
			{
				set_state(atk1);
				npc2_Atk1_Audio.ChannelPlay(0, true);
			}

			else if(a_act==1)
			{
				set_state(atk2);
				npc2_Atk2_Audio.ChannelPlay(0, true);
			}
			a_act++;
			if (a_act == 2)
			{
				a_act = 0;
			}
		}
		
	}
	



	if (act == atk1)
	{
		if (CPlayer::Get_Instance()->Get_spx()->collidesWith(get_spx(), 1, 0, COLLISION_AABB))
		{
			CPlayer::Get_Instance()->set_hurted(rand() % 500);
		}
	}
	if (act == atk2)
	{
		if (CPlayer::Get_Instance()->Get_spx()->collidesWith(get_spx(), 1, 0, COLLISION_AABB))
		{
			CPlayer::Get_Instance()->set_hurted_fly(dir, rand() % 500);
		}
	}
}

void CNpc2::show()
{
	spx->setFlipX(dir);
	spx->update();
	spx->draw();
	if (hurted_time > 0)
	{
		hurted_spx->setPosition(show_x, show_y);
		hurted_spx->setFlipX(dir);
		hurted_spx->update();
		hurted_spx->draw();
		hurted_time--;
	}
	hp_rect.set_hp(now_hp / all_hp, show_x, show_y);
	spx->setPosition(show_x, show_y + Cmap::Getinstance()->get_snake());
}

void CNpc2::set_move()
{
	bool act_over = spx->isPlayOver(act);
	if (act == move)
	{
		if (dir)
			x-=2;
		else
			x+=2;

	}

	if (act == hurted_fly)
	{
		if (dir)
			x += 1;
		else
			x -= 1;
	}
	//出场音效
	if (num_once == 0)
	{
		npc2_out_Audio.ChannelPlay(0, true);
		num_once++;
	}



}

void CNpc2::Release()
{
	//delete spx;
	//spx = NULL;
}

CNpc2::CNpc2()
{
	int m_MusicIndex;
	/*char *npc2_out = new char[strlen(Text->FirstChildElement("npc2_out")->GetText()) + 1];
	strcpy(npc2_out, Text->FirstChildElement("npc2_out")->GetText());*/
	npc2_out_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = npc2_out_Audio.LoadFile("audio/monsterout/monsterout.mp3", BASS_MUSIC_MONO);
	npc2_out_Audio.ChannelBytes2Seconds(m_MusicIndex, npc2_out_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	/*char *npc2_die = new char[strlen(Text->FirstChildElement("npc2_die")->GetText()) + 1];
	strcpy(npc2_die, Text->FirstChildElement("npc2_die")->GetText());*/
	npc2_die_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = npc2_die_Audio.LoadFile("audio/monster/2/die.mp3", BASS_MUSIC_MONO);
	npc2_die_Audio.ChannelBytes2Seconds(m_MusicIndex, npc2_die_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	//char *npc2_atk1 = new char[strlen(Text->FirstChildElement("npc2_atk1")->GetText()) + 1];
	//strcpy(npc2_atk1, Text->FirstChildElement("npc2_atk1")->GetText());
	npc2_Atk1_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = npc2_Atk1_Audio.LoadFile("audio/monster/2/Q1.mp3", BASS_MUSIC_MONO);
	npc2_Atk1_Audio.ChannelBytes2Seconds(m_MusicIndex, npc2_Atk1_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	/*char *npc2_atk2 = new char[strlen(Text->FirstChildElement("npc2_atk2")->GetText()) + 1];
	strcpy(npc2_atk2, Text->FirstChildElement("npc2_atk2")->GetText());*/
	npc2_Atk2_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = npc2_Atk2_Audio.LoadFile("audio/monster/2/W1.mp3", BASS_MUSIC_MONO);
	npc2_Atk2_Audio.ChannelBytes2Seconds(m_MusicIndex, npc2_Atk2_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));


	to_player_x = 0 + rand() % 100;

	spx = new SpriteX(CPlatForm::Getinstance()->Get_pd3dDevice(), "other/npc/npc2/npc2.sprite", "other/npc/npc2/2_1.png");

	dir = true;//翻转
	a_act = 0;
	//hp_rect.set_color(255, 0, 0);
	
	act = Show;
	spx->setAction(act);
	spx->setDelay(50);

	CNpc_Management::Get_instance()->add(this);
}


CNpc2::~CNpc2()
{
}

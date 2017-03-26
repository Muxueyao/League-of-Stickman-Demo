#include "stdafx.h"



void CNpc1::set_state(NPCACT _act)
{
	act = _act;
	bool act_over = spx->isPlayOver(act);

	bool isLoop = false;
	switch (act)
	{
	case move:
		isLoop = true;
		spx->setDelay(20);
		break;
	case atk1:
		isLoop = true;
		spx->setDelay(150);
		break;
	case hurted:
		isLoop = false;
		spx->setDelay(150);
		break;
	case hurted_fly:
		isLoop = false;
		spx->setDelay(100);
		break;
	case die:
		isLoop = false;
		spx->setDelay(100);
		break;
	case Show:
		isLoop = false;
		spx->setDelay(100);
	}
	spx->setAction(act, isLoop);
}

void CNpc1::set_move()
{
	bool act_over = spx->isPlayOver(act);
	if (act == move)
	{
		if (dir)
			x -= 2;
		else
			x += 2;
	}
	if (act == hurted_fly)
	{
		if (dir)
			x += 1;
		else
			x -= 1;
		//spx->setColor(255, 0, 0);
	}

	//出场音效
	if (num_once == 0)
	{
		npc1_out_Audio.ChannelPlay(0, true);
		num_once++;
	}

}

void CNpc1::update()
{

	if (now_hp <= 0 && num_once == 1)
	{
		new CDie_Effect(x, y, L"other/npc/npc1/1.png", L"other/npc/npc1/2.png", L"other/npc/npc1/3.png", L"other/npc/npc1/4.png",
			L"other/npc/npc1/5.png", L"other/npc/npc1/6.png", L"other/npc/npc1/7.png", L"other/npc/npc1/8.png",
			L"other/npc/npc1/9.png", L"other/npc/npc1/10.png");
		npc1_die_Audio.ChannelPlay(0, true);
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
		npc1_Atk1_Audio.ChannelStop(0);
		is_hurted = false;
	}

	bool act_over = spx->isPlayOver(act);
	set_move();

	show_x = x + Cmap::Getinstance()->get_offset_x();
	show_y = y + Cmap::Getinstance()->get_offset_y();


	if (show_x > CPlayer::Get_Instance()->get_show_x())
		dir = true;
	if (show_x < CPlayer::Get_Instance()->get_show_x())
		dir = false;

	if (show_x > CPlayer::Get_Instance()->get_show_x() + to_player_x && act_over
		|| show_x < CPlayer::Get_Instance()->get_show_x() - to_player_x && act_over)
	{
		set_state(move);
	}

	else
	{
		if (act_over)
		{
			set_state(atk1);
			npc1_Atk1_Audio.ChannelPlay(0,true);
		}
	}

	if (act == atk1)
	{
		if (CPlayer::Get_Instance()->Get_spx()->collidesWith(get_spx(), 1, 0, COLLISION_AABB))
		{
			CPlayer::Get_Instance()->set_hurted(rand() % 500);
		}
	}
}

void CNpc1::show()
{
	hp_rect.set_hp(now_hp / all_hp, show_x, show_y);
	spx->setFlipX(dir);
	spx->update();
	spx->draw();
	spx->setPosition(show_x, show_y + Cmap::Getinstance()->get_snake());
	if (hurted_time > 0)
	{
		hurted_spx->setPosition(show_x, show_y);
		hurted_spx->setFlipX(dir);
		hurted_spx->update();
		hurted_spx->draw();
		hurted_time--;
	}
}

void CNpc1::Release()
{
}

CNpc1::CNpc1()
{
	int m_MusicIndex;
	/*TiXmlDocument *Document = new TiXmlDocument;
	Document->LoadFile("Xml/audio.xml");
	TiXmlElement *Root_Element = Document->RootElement();
	TiXmlElement *FirstChild_Element = Root_Element->FirstChildElement();
	TiXmlElement *Text = FirstChild_Element->FirstChildElement();*/

	/*char *npc1_out = new char[strlen(Text->FirstChildElement("npc1_out")->GetText()) + 1];
	strcpy(npc1_out, Text->FirstChildElement("npc1_out")->GetText());*/
	npc1_out_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = npc1_out_Audio.LoadFile("audio/monsterout/monsterout.mp3", BASS_MUSIC_MONO);
	npc1_out_Audio.ChannelBytes2Seconds(m_MusicIndex, npc1_out_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	/*char *npc1_die = new char[strlen(Text->FirstChildElement("npc1_die")->GetText()) + 1];
	strcpy(npc1_die, Text->FirstChildElement("npc1_die")->GetText());*/
	npc1_die_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = npc1_die_Audio.LoadFile("audio/monster/1/die.mp3", BASS_MUSIC_MONO);
	npc1_die_Audio.ChannelBytes2Seconds(m_MusicIndex, npc1_die_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	/*char *npc1_atk = new char[strlen(Text->FirstChildElement("npc1_atk")->GetText()) + 1];
	strcpy(npc1_atk, Text->FirstChildElement("npc1_atk")->GetText());*/
	npc1_Atk1_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = npc1_Atk1_Audio.LoadFile("audio/monster/1/A1.mp3", BASS_MUSIC_MONO);
	npc1_Atk1_Audio.ChannelBytes2Seconds(m_MusicIndex, npc1_Atk1_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));



	to_player_x = 0 + rand() % 100;

	spx = new SpriteX(CPlatForm::Getinstance()->Get_pd3dDevice(), "other/npc/npc1/npc1.sprite", "other/npc/npc1/1_1.png");

	dir = true;//翻转

	act = Show;
	spx->setAction(act);
	spx->setDelay(50);
	CNpc_Management::Get_instance()->add(this);
}


CNpc1::~CNpc1()
{
}

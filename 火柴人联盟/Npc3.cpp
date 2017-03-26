#include "stdafx.h"



void CNpc3::set_state(ACT _act)
{
	bool act_over = spx->isPlayOver(act);

	if (!act_over || act == die)
		return;
	this->act = _act;
	bool isLoop = false;
	switch (act)
	{
	case move:
		isLoop = true;
		spx->setDelay(40);
		break;
	case atk:
		isLoop = false;
		spx->setDelay(50);

		break;
	case stand:
		isLoop = true;
		spx->setDelay(100);
		break;
	case die:
		isLoop = false;
		spx->setDelay(100);
		break;
	case Show:
		isLoop = false;
		spx->setDelay(100);
		break;
	}
	spx->setAction(act, isLoop);
}

void CNpc3::set_move()
{
	bool act_over = spx->isPlayOver(act);
	switch (act)
	{
	case move:
		if (dir)
		{
			x -= 2;
		}
		else
		{
			x += 2;
		}
		break;
	case atk:
		
		break;
	case Show:
		if (num_once == 0)
		{
			npc3_out_Audio.ChannelPlay(0, true);
			num_once++;
		}
	case die:

		break;
		/*case show:
		npcout_Audio.ChannelPlay(0, true);
		break;*/
	}
}

void CNpc3::update()
{
	
	if (now_hp <= 0 && num_once == 1)
	{
		npc3_die_Audio.ChannelPlay(0, true);
		new CDie_Effect(x, y, L"other/npc/npc3/1.png", L"other/npc/npc3/2.png", L"other/npc/npc3/3.png", L"other/npc/npc3/4.png",
			L"other/npc/npc3/5.png", L"other/npc/npc3/6.png", L"other/npc/npc3/7.png", L"other/npc/npc3/8.png",
			L"other/npc/npc3/9.png", L"other/npc/npc3/10.png");
		new CMoney_drop(x, y);
		set_del(true);
		num_once++;
	}
	if (is_hurted)
	{
		
		is_hurted = false;
	}
	bool act_over = spx->isPlayOver(act);
	
	set_move();

	show_x = x + Cmap::Getinstance()->get_offset_x();
	show_y = y + Cmap::Getinstance()->get_offset_y();

	if (show_x > CPlayer::Get_Instance()->get_show_x())
	{
		dir = true;

	}
	else
	{
		dir = false;
	}


	if (show_x > CPlayer::Get_Instance()->get_show_x() + to_player_x && act_over
		|| show_x < CPlayer::Get_Instance()->get_show_x() - to_player_x && act_over)
	{
		set_state(move);
	}
	else
	{
		if (act_over)
		{
			fire_time--;
			if (fire_time == 0 )
			{
				set_state(atk);
				bullet_dir = dir;
				bullet_show = true;
				if (dir)
				{
					bullet_x = x - 80;
					bullet_y = y - 15;
				}
				else
				{
					bullet_x = x + 80;
					bullet_y = y - 15;
				}
				npc3_fire_Audio.ChannelPlay(0, true);
				b_act = fire;
				bullet_spx->setAction(fire);

				fire_time = fire_time_temp;
			}
			else
			{
				set_state(stand);
			}
				
		}
	}


	bullet_spx->setVisible(bullet_show);

	if (bullet_show)
	{
		if (b_act == fire)
		{
			if (bullet_dir)
			{
				bullet_x -= 10;
			}
			else
			{
				bullet_x += 10;
			}
		}
		if (b_act == boom)
		{
			bool bulletact_over = bullet_spx->isPlayOver(b_act);
			if (bulletact_over)
			{
				bullet_show = false;
				bullet_x = 0;
				bullet_y = 0;
			}
		}

	}


	if (CPlayer::Get_Instance()->Get_spx()->collidesWith(bullet_spx, 1, 0, COLLISION_AABB))
	{
		npc3_boom_Audio.ChannelPlay(0, true);
		b_act = boom;
		bullet_spx->setAction(b_act);
		int temp_sum = rand() % 4;
		if (!temp_sum)
		{
			CPlayer::Get_Instance()->set_hurted_fly(dir,rand() % 1000);
		}
		else
		{
			CPlayer::Get_Instance()->set_hurted(rand() % 500);
		}
		
	}
	

}

void CNpc3::Release()
{
	//Hurted_img->set_del(true);
	
	//delete spx;
	//spx = NULL;

	//delete bullet_spx;
	//bullet_spx = NULL;
}

void CNpc3::show()
{
	float bulletshow_x = bullet_x + Cmap::Getinstance()->get_offset_x();
	float bulletshow_y = bullet_y + Cmap::Getinstance()->get_offset_y();


	bullet_spx->setFlipX(dir);
	bullet_spx->update();
	bullet_spx->draw();
	bullet_spx->setPosition(bulletshow_x, bulletshow_y + Cmap::Getinstance()->get_snake());
	
	spx->setFlipX(dir);
	spx->update();
	spx->draw();

	if (hurted_time > 0)
	{
		hurted_spx->setPosition(show_x, show_y);
		hurted_spx->setFlipX(dir);
		hurted_spx->update();
		hurted_spx->draw();
		/*Hurted_img->set_show(true);
		Hurted_img->set_pos(show_x-10, show_y-130);*/
		hurted_time--;

	}
	else
	{
		//Hurted_img->set_show(false);
	}
	spx->setPosition(show_x, show_y + Cmap::Getinstance()->get_snake());

	hp_rect.set_hp(now_hp / all_hp, show_x, show_y + Cmap::Getinstance()->get_snake());
}

CNpc3::CNpc3()
{
	int m_MusicIndex;
	/*char *npc3_out = new char[strlen(Text->FirstChildElement("npc3_out")->GetText()) + 1];
	strcpy(npc3_out, Text->FirstChildElement("npc3_out")->GetText());*/
	npc3_out_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = npc3_out_Audio.LoadFile("audio/monsterout/monsterout.mp3", BASS_MUSIC_MONO);
	npc3_out_Audio.ChannelBytes2Seconds(m_MusicIndex, npc3_out_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	/*char *npc3_die = new char[strlen(Text->FirstChildElement("npc3_die")->GetText()) + 1];
	strcpy(npc3_die, Text->FirstChildElement("npc3_die")->GetText());*/
	npc3_die_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = npc3_die_Audio.LoadFile("audio/monster/3/die.mp3", BASS_MUSIC_MONO);
	npc3_die_Audio.ChannelBytes2Seconds(m_MusicIndex, npc3_die_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	/*char *npc3_fire = new char[strlen(Text->FirstChildElement("npc3_fire")->GetText()) + 1];
	strcpy(npc3_fire, Text->FirstChildElement("npc3_fire")->GetText());*/
	npc3_fire_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = npc3_fire_Audio.LoadFile("audio/monster/3/A.mp3", BASS_MUSIC_MONO);
	npc3_fire_Audio.ChannelBytes2Seconds(m_MusicIndex, npc3_fire_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	/*char *npc3_boom = new char[strlen(Text->FirstChildElement("npc3_boom")->GetText()) + 1];
	strcpy(npc3_boom, Text->FirstChildElement("npc3_boom")->GetText());*/
	npc3_boom_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = npc3_boom_Audio.LoadFile("audio/monster/3/boom.mp3", BASS_MUSIC_MONO);
	npc3_boom_Audio.ChannelBytes2Seconds(m_MusicIndex, npc3_boom_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	to_player_x = 300 + rand() % 200;
	spx = new SpriteX(CPlatForm::Getinstance()->Get_pd3dDevice(),"other/npc/npc3/npc_car.sprite", "other/npc/npc3/npc3.png");
	dir = true;
	act = Show;
	spx->setAction(act);
	spx->setDelay(50);
	bullet_show = false;
	bullet_spx = new SpriteX(CPlatForm::Getinstance()->Get_pd3dDevice(), "other/npc/npc3/fire.sprite", "other/npc/npc3/bullet.png");
	b_act = fire;
	bullet_spx->setAction(b_act);
	bullet_spx->setDelay(50);
	bullet_spx->setVisible(bullet_show);
	bullet_x = 0;
	bullet_y = 0;
	bullet_dir = true;

	fire_time = 40;
	fire_time_temp = fire_time;


	CNpc_Management::Get_instance()->add(this);
}


CNpc3::~CNpc3()
{
}

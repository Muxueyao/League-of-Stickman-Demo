#include "stdafx.h"



void CMoney_drop::show()
{

}

void CMoney_drop::update()
{
	jb1_y -= y1_speed;
	y1_speed -= speed;
	jb1_x -= x1_speed;

	if (jb1_y > 365)
	{
		jb1_y = 365;
		if (jb1_time == one)
		{
			y1_speed = 10;
			jb1_time = two;
			money_Audio.ChannelPlay(0, true);
		}
		else if (jb1_time == two)
		{
			y1_speed = 5;
			jb1_time = three;
			money_Audio.ChannelPlay(0, true);
		}
		else if (jb1_time == three)
		{
			jb1_time = four;
			y1_speed = 0;
			x1_speed = 0;
			money_Audio.ChannelPlay(0, true);
		}

	}
	jb2_y -= y2_speed;
	y2_speed -= speed;
	jb2_x += x2_speed;
	if (jb2_y > 365)
	{
		jb2_y = 365;
		if (jb2_time == one)
		{
			y2_speed = 10;
			jb2_time = two;
			money_Audio.ChannelPlay(0, true);
		}
		else if (jb2_time == two)
		{
			y2_speed = 5;
			jb2_time = three;
			money_Audio.ChannelPlay(0, true);
		}
		else if (jb2_time == three)
		{
			jb2_time = four;
			y2_speed = 0;
			x2_speed = 0;
			money_Audio.ChannelPlay(0, true);
		}

	}

	jb3_y -= y3_speed;
	y3_speed -= speed;
	jb3_x += x3_speed;
	if (jb3_y > 365)
	{
		jb3_y = 365;
		if (jb3_time == one)
		{
			y3_speed = 10;
			jb3_time = two;
			money_Audio.ChannelPlay(0, true);
		}
		else if (jb3_time == two)
		{
			y3_speed = 5;
			jb3_time = three;
			money_Audio.ChannelPlay(0, true);
		}
		else if (jb3_time == three)
		{
			jb3_time = four;
			y3_speed = 0;
			x3_speed = 0;
			money_Audio.ChannelPlay(0, true);
		}

	}


	int player_x = CPlayer::Get_Instance()->get_show_x();
	int offset_x = Cmap::Getinstance()->get_offset_x();
	int snake_y = Cmap::Getinstance()->get_snake();
	if (j1)
	{

		jb1->set_pos(offset_x + jb1_x, jb1_y + snake_y);

		if (abs(player_x - (offset_x + jb1_x)) <= 10 && jb1_y > 300)
		{
			dropcoin.ChannelPlay(0, true);
			jb1->set_show(false);
			CPlayer::Get_Instance()->set_money(1);
			//new CUI_number(L"img/num_doublehit/png",CPlayer::Get_Instance()->get_show_x(),CPlayer::Get_Instance()->get_show_y());

			j1 = false;
		}
	}

	if (j2)
	{
	
		jb2->set_pos(offset_x + jb2_x, jb2_y + snake_y);

		if (abs(player_x - (offset_x + jb2_x)) <= 10 && jb2_y>300)
		{
			dropcoin.ChannelPlay(0, true);
			jb2->set_show(false);
			CPlayer::Get_Instance()->set_money(5);
			//new CUI_number(L"img/num_doublehit/png", CPlayer::Get_Instance()->get_show_x(), CPlayer::Get_Instance()->get_show_y());
			j2 = false;
		}
	}

	if (j3)
	{
		jb3->set_pos(offset_x + jb3_x, jb3_y + snake_y);

		if (abs(player_x - (offset_x + jb3_x)) <= 10 && jb3_y>300)
		{
			dropcoin.ChannelPlay(0, true);
			jb3->set_show(false);
			CPlayer::Get_Instance()->set_money(10);
			//new CUI_number(L"img/num_doublehit/png", CPlayer::Get_Instance()->get_show_x(), CPlayer::Get_Instance()->get_show_y());
			j3 = false;

		}
	}

	if (!j1 && !j2 && !j3)
	{
		set_del(true);
	}
}

void CMoney_drop::Release()
{
	//dropcoin.Release();
	//money1_Audio.Release();
	//money2_Audio.Release();
	//money3_Audio.Release();
	jb1->set_del(true);
	jb2->set_del(true);
	jb3->set_del(true);
}

CMoney_drop::CMoney_drop(float x, float y)
{
	id = moneydrop;
	int m_MusicIndex;//ÁÙÊ±±äÁ¿£¬ÅäÖÃÒôÆµ

	dropcoin.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = dropcoin.LoadFile("audio/ui/4.mp3", BASS_MUSIC_MONO);
	dropcoin.ChannelBytes2Seconds(m_MusicIndex, dropcoin.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	money_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = money_Audio.LoadFile("audio/ui/6043.mp3", BASS_MUSIC_MONO);
	money_Audio.ChannelBytes2Seconds(m_MusicIndex, money_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));


	j1 = j2 = j3 = true;
	jb1_x = jb2_x = jb3_x = x;
	jb1_y = jb2_y = jb3_y = y;


	x1_speed = x3_speed = 1.0f;
	x2_speed = 0.f;
	y1_speed = y2_speed = y3_speed = 15.0f;

	speed = 0.5f;

	jb1_time = one;
	jb2_time = one;
	jb3_time = one;


	jb1 = new CUI_img(L"img/map_coin_1.png");
	jb1->set_anchor(D3DXVECTOR3(jb1->get_img_x() / 2, jb1->get_img_y(), 0));
	jb1->set_pos(x, y);
	jb1->set_sort(-3);
	jb2 = new CUI_img(L"img/map_coin_2.png");
	jb2->set_anchor(D3DXVECTOR3(jb2->get_img_x() / 2, jb2->get_img_y(), 0));
	jb2->set_pos(x, y);
	jb2->set_sort(-3);
	jb3 = new CUI_img(L"img/map_coin_3.png");
	jb3->set_anchor(D3DXVECTOR3(jb3->get_img_x() / 2, jb3->get_img_y(), 0));
	jb3->set_pos(x, y);
	jb3->set_sort(-3);

	CObj_management::Getinstance()->add(this);
}


CMoney_drop::~CMoney_drop()
{
}

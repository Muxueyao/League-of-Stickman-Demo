#pragma once
class CNpc3
	:public CNpc
{
	SpriteX *bullet_spx;
	bool bullet_show;
	float bullet_x;
	float bullet_y;
	bool bullet_dir;
	

	int fire_time;
	int fire_time_temp;
	enum bullet_act
	{
		fire,
		boom,
	}b_act;
	enum ACT
	{
		move,
		atk,
		die,
		stand,
		Show,
	}act;

	CAudio4Bass		npc3_out_Audio;
	CAudio4Bass		npc3_die_Audio;
	CAudio4Bass		npc3_fire_Audio;
	CAudio4Bass		npc3_boom_Audio;
public:
	void set_state(ACT _act);
	void set_move();
	void update();
	void Release();
	void show();
	CNpc3();
	~CNpc3();
};


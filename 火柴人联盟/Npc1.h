#pragma once
class CNpc1
	:public CNpc
{
	CAudio4Bass		npc1_out_Audio;
	CAudio4Bass		npc1_die_Audio;
	CAudio4Bass		npc1_Atk1_Audio;
	enum NPCACT
	{
		move,
		atk1,
		atk2,
		hurted_fly,
		die,
		Show,
		hurted,
	}act;
	void set_state(NPCACT _act);
	void set_move();
public:
	void update();
	void show();
	void Release();
	CNpc1();
	~CNpc1();
};


#pragma once
class CNpc2
	:public CNpc
{

	CAudio4Bass		npc2_out_Audio;
	CAudio4Bass		npc2_die_Audio;
	CAudio4Bass		npc2_Atk1_Audio;
	CAudio4Bass		npc2_Atk2_Audio;
	enum ACT
	{
		move,
		atk1,
		atk2,
		hurted_fly,
		die,
		Show,
		hurted,
	}act;
	int a_act;
public:
	void set_state(ACT _act);
	void update();
	void show();
	void set_move();
	void Release();
	CNpc2();
	~CNpc2();
};


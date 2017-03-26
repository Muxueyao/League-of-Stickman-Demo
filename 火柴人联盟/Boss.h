#pragma once
class CBoss
	:public CNpc
{
	CAudio4Bass		A1_Audio;
	CAudio4Bass		A2_Audio;
	CAudio4Bass		A3_Audio;
	CAudio4Bass		A4_Audio;
	CAudio4Bass		A5_Audio;


	CAudio4Bass		Q1_Audio;
	CAudio4Bass		Q2_Audio;


	CAudio4Bass		W1_Audio;
	CAudio4Bass		W2_Audio;
	CAudio4Bass		W3_Audio;
	CAudio4Bass		W4_Audio;
	CAudio4Bass		W5_Audio;
	CAudio4Bass		W6_Audio;

	CAudio4Bass		E_Audio;

	CAudio4Bass		R_Audio;
	CAudio4Bass		R1_Audio;
	CAudio4Bass		R2_Audio;
	CAudio4Bass		R3_Audio;
	CAudio4Bass		R4_Audio;
	CAudio4Bass		R5_Audio;
	CAudio4Bass		R6_Audio;

	CAudio4Bass		npcout_Audio;
	CAudio4Bass		die_Audio;

	int a1_hurted;
	int a2_hurted;
	int a3_hurted;
	int a4_hurted;
	int a5_hurted;
	int q1_hurted;
	int q2_hurted;
	int w1_hurted;
	int w2_hurted;
	int w3_hurted;
	int w4_hurted;
	int w5_hurted;
	int w6_hurted;
	int e_hurted;
	int r1_hurted;
	int r2_hurted;
	int r3_hurted;
	int r4_hurted;
	int r5_hurted;
	int r6_hurted;

	float move_speed;

	CUI_img *Head_img;
	CUI_img *Head_hp_rect;
	CUI_img *Head_hp_rect2;
	CUI_img *Head_hp_buffer_rect;

	float buffer_hp;

	SpriteX *Q_spx;

	float Q_x, Q_y;
	bool Q_dir;
	int act_num;
	enum BOSSACT
	{
		stand,
		move,
		a1,
		a2,
		a3,
		a4,
		a5,
		q1,
		q2,
		w1,
		w2,
		w3,
		w4,
		w5,
		w6,
		e,
		r1,
		r2,
		r3,
		r4,
		r5,
		r6,
		Show,
		hurted,
		die,

	}bossact;
	void set_move();
	void set_state(BOSSACT _act);
public:

	void update();
	void show();
	void Release();
	CBoss();
	~CBoss();
};


#pragma once
class CNpc
{
	
	bool is_del;
public:
	SpriteX *hurted_spx;
	//CUI_img *Hurted_img;
	//������Ҽ�Ĺ�������
	int to_player_x;
	float x, y;
	float show_x, show_y;
	float all_hp, now_hp;
	bool dir;
	bool is_hurted;
	//�������˶���
	int hurted_time;
	//���Ƴ������������߼�ִ��һ��,1Ϊ������2Ϊ����
	int num_once;
	CHP_rect hp_rect;
	SpriteX *spx;
	bool get_del() { return is_del; }
	void set_pos(float _x, float _y) { x = _x;y = _y; }
	void set_del(bool del) { is_del = del; }
	virtual void Release() = 0;
	virtual void update() = 0;
	virtual void show() = 0;
	SpriteX *get_spx() { return spx; }
	void set_hurted(float hurted_num); 
	CNpc();
	~CNpc();
};


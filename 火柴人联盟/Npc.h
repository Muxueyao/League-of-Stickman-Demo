#pragma once
class CNpc
{
	
	bool is_del;
public:
	SpriteX *hurted_spx;
	//CUI_img *Hurted_img;
	//距离玩家间的攻击距离
	int to_player_x;
	float x, y;
	float show_x, show_y;
	float all_hp, now_hp;
	bool dir;
	bool is_hurted;
	//控制受伤动画
	int hurted_time;
	//控制出场，死亡等逻辑执行一次,1为出场，2为死亡
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


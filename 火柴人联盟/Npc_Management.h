#pragma once
class CNpc_Management
{
	static CNpc_Management*Instance;
	list<CNpc*>Npc_list;
	enum PLAYER_ACT
	{
		Stand,
		Walk,
		A1,
		A2,
		A3,
		A4,
		A5,
		Q,
		W,
		E,
		E2,
		E3,
		R,
		DIE,
		hurted,
	};
	CAudio4Bass		npchurted_Audio;
public:
	static CNpc_Management *Get_instance();
	void add(CNpc *Obj);
	void update();
	void Release();
	int get_list_size() { return Npc_list.size(); }
	CNpc_Management();
	~CNpc_Management();
};


#pragma once
/** @defgroup EXAMPLES ���������
*  @author  �Է�
*  @version 1.0
*  @date    2006-11-9
*  @{
*/

class CPlayer
{
	/** @name �����
	*  @{
	*/
	/** �������� */
	SpriteX *spx;
	/** �������� */
	float x, y;
	/** �������� */
	float show_x, show_y;
	/** Ѫ������ */
	CHP_rect hp_rect;
	/** ��ǰѪ�� */
	float now_hp;
	/** ����Ѫ�� */
	float all_hp;
	/** ����Ѫ�� */
	float buffer_hp;
	/** ��ת״̬ */
	bool dir;
	/** ��ͷƫ��ֵ */
	int camera_x;
	/** ��ͷ��ֹ״̬ */
	bool camera_stand;
	/** ��ͷ״̬ */
	bool is_camera;
	/** ʱ����ʱ���� */
	int m_time = 150;
	int m_speed = 20;
	/** ��ҽ�� */
	int money;
	/** �����ʯ */
	int zuansi;
	/** ����Aͼ�� */
	CUI_img *a_img;
	/** ����A��ǰ���� */
	int a_act;
	/** ����A��ȴͼ�� */
	DX_CircleAnim *a_load;
	/** ����Qͼ�� */
	CUI_img *q_img;
	/** ����Q��ȴͼ�� */
	DX_CircleAnim *q_load;
	/** ����Wͼ�� */
	CUI_img *w_img;
	/** ����W��ȴͼ�� */
	DX_CircleAnim *w_load;
	/** ����Eͼ�� */
	CUI_img *e_img;
	/** ����E��ȴͼ�� */
	DX_CircleAnim *e_load;
	/** ����Rͼ�� */
	CUI_img *r_img;
	/** ����R��ȴͼ�� */
	DX_CircleAnim *r_load;
	/** ����CDʱ�� */
	float Q_CD, W_CD, E_CD, R_CD, A_CD;
	/** ������ȴʣ��ʱ�� */
	float  Q_time, W_time, E_time, R_time, A_time;
	/** �������1 */
	LPD3DXFONT pFont_big;
	/** �������2 */
	LPD3DXFONT pFont_small;
	/** ������ */
	int hits;
	/** ���������� */
	int hits_buffer;
	/** ��������0ʱ�� */
	int hits_time;
	/** ��������ͼƬ */
	CUI_img *hits_battle;
	/** ��������״̬ */
	bool is_hurted;
	/** ����ʱ��ȴ� */
	int hurted_time;
	/** ����ʱ��ȴ� */
	int hurted_num;
	/** ���˺�ɫͼƬ */
	CUI_img *hurted_img;
	/** �������ﶯ�� */
	enum PLAYER_ACT;
	/** �������ﶯ�� */
	void set_state(PLAYER_ACT act);
	/** ���ö����ƶ� */
	void set_move();
	/** ��ҵ������� */
	static CPlayer *Instance;
	/** ����״̬ */
	bool is_death;
	/** �ƶ��ٶ� */
	int move_speed;
	/** ��������ʾ */
	void hits_show();
	/** Ѫ����ʾ���� */
	bool hp_show;
	/** �����˺�ֵ */
	int A1_hurted,A2_hurted,A3_hurted,A4_hurted,A5_hurted,Q_hurted,W_hurted,E_hurted,R_hurted;
public:

	/** ö�ٳ���_���ﶯ�� */
	enum PLAYER_ACT
	{
		Stand,	  /**< վ�� */
		Walk,	  /**< ���� */
		A1,		  /**< ���� */
		A2,		  /**< ���� */
		A3,		  /**< ���� */
		A4,		  /**< ���� */
		A5,		  /**< ���� */
		Q,		  /**< ���� */
		W,		  /**< ���� */
		E,		  /**< ���� */
		E2,		  /**< ���� */
		E3,		  /**< ���� */
		R,		  /**< ���� */
		DIE,	  /**< ���� */
		hurted,	  /**< ���� */
	}player_act;
	/** ��ȡ��ǰ��ʯ���� */
	int get_zuansi() { return zuansi; }
	/** ��ȡ�����˺�ֵ */
	int get_q_hurted() { return Q_hurted; }
	/** ��ȡ�����˺�ֵ */
	int get_w_hurted() { return W_hurted; }
	/** ��ȡ�����˺�ֵ */
	int get_e_hurted() { return E_hurted; }
	/** ��ȡ�����˺�ֵ */
	int get_r_hurted() { return R_hurted; }
	/** ��ȡ�����˺�ֵ */
	int get_a1_hurted() { return A1_hurted; }
	/** ��ȡ�����˺�ֵ */
	int get_a2_hurted() { return A2_hurted; }
	/** ��ȡ�����˺�ֵ */
	int get_a3_hurted() { return A3_hurted; }
	/** ��ȡ�����˺�ֵ */
	int get_a4_hurted() { return A4_hurted; }
	/** ��ȡ�����˺�ֵ */
	int get_a5_hurted() { return A5_hurted; }
	/** ���þ�ͷ�ƶ�
	*  @param file float m_x ��ͷ�ƶ���ֵ
	*/
	void set_camera(float m_x);
	/** ���������� */
	void set_hits() { hits++;hits_time = 80; }
	/** ��ȡ��ǰ���ﶯ�� */
	PLAYER_ACT get_act() { return player_act; }
	/** ��ȡ�������� */
	SpriteX *Get_spx() { return spx; }
	/** ��ȡ�������� */
	int get_show_x() { return show_x; }
	/** ��ȡ�������� */
	int get_show_y() { return show_y; }
	/** ��ȡ�������� */
	int get_x() { return x; }
	/** ��ȡ�������� */
	int get_y() { return y; }
	/** ��ȡ�������� */
	static CPlayer *Get_Instance();
	/** ��ȡ�����ֵ */
	int get_money() { return money; }
	/** ��ȡѪ��ֵ */
	int get_hp() { return buffer_hp; }
	/** ��ȡ��ͷ��ֹ״̬ */
	bool get_camera_stand() { return camera_stand; }
	/** �߼����� */
	void update();
	/** ��Ⱦ���� */
	void show();
	/** ��������ָ���ʼֵ */
	void reset();
	/** ����Ѫ����ʾ״̬ */
	void set_hp_show(bool hp_show) { this->hp_show = hp_show; }
	/** ��ȡ��ͷ״̬ */
	bool get_is_camera() { return is_camera; }
	/** ��ȡ����״̬ */
	bool get_death() { return is_death; }
	/** �����˺���ֵ */
	void set_hurted(int hurted_num);
	/** �����˺����� */
	void set_hurted_fly(bool _dir, int hurted_num);
	/** ���ý�� */
	void set_money(int _money) { money += _money;new CHurted_num(L"img/num_yellow.png", _money, x , y - 150,L"img/num_coin.png");}
	/** ���캯�� */
	CPlayer();
	/** �������� */
	~CPlayer();
};

/** @}*/ // �����
/** @}*/ // ���������
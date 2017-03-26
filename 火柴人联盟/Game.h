#pragma once
/** @defgroup EXAMPLES ���������
*  @author  �Է�
*  @version 1.0
*  @date    2006-11-9
*  @{
*/
class CGame
{
	/** @name ��Ϸ�߼�
	*  @{
	*/
	/** �������� */
	static CGame *instance;
	/** ��½���� */
	bool is_login;
	/** ���ؿ��� */
	bool is_load;
	/** �����濪�� */
	bool is_mainscene;
	/** ���ֽ��濪�� */
	bool is_new_state;
	/** ��Ϸ��ʼ���� */
	bool is_gamescene;
	/** ��Ϸ��ʼ */
	bool game_start;
	/** ʤ������ */
	bool is_win;
	/** ʧ�ܿ��� */
	bool is_lose;
	/** ���¿�ʼ��Ϸ���� */
	bool restart;


	/** ��½���� */
	CLogin *login;
	/** ���ؽ��� */
	CLoading *loading;
	/** ������ */
	CMain_scene *main_scene;
	/** ���ֽ�ѧ */
	CNew_hand_state *new_hand_state;
	/** ��Ϸ��ʼ���� */
	CGame_start *start;
	/** ʤ������ */
	CUI_img *win_scene;
	/** ʧ�ܽ��� */
	CUI_img *lose_scene;
	/** ���¿�ʼ��Ϸ��ť */
	CUI_button *game_restart;
	/** �˳���Ϸ��ť */
	CUI_button *game_exit;
public:
	/** ��ȡ�������� */
	static CGame *Get_instance();
	/** ������Ϸ�߼� */
	void update();
	/** ���캯�� */
	CGame();
	/** �������� */
	~CGame();
};
/** @}*/ // ��Ϸ�߼�
 /** @}*/ // ���������

#pragma once

/** @defgroup EXAMPLES ���������
*  @author  �Է�
*  @version 1.0
*  @date    2006-11-9
*  @{
*/
class Cmap
{
	/** @name ��ͼ��
	*  @{
	*/
	/** �������� */
	static Cmap *instance;
	/** ƫ������ */
	int offset_x, offset_y;
	/** �������� */
	int map_x, map_y;
	/** ���Ƶ�ǰ����ͼ����,������ͼʱ�õ� */
	int now_x, now_y;
	/** ��ͼ��״̬ */
	bool is_snake;
	/** ��ͼ��ʱY�����ƫ��ֵ */
	int snake;
	/** ��ͼͼƬ���� */
	CUI_img *map_img;
public:
	/** ��ȡ�������� */
	static Cmap* Getinstance();
	/** ��ȡ��ͼ��� */
	int get_map_x() { return map_x; }
	/** ��ȡ��ͼ�߶� */
	int get_map_y() { return map_y; }
	/** ��ȡ��ͼ���ƫ�� */
	int get_offset_x() { return offset_x; }
	/** ��ȡ��ͼ�߶�ƫ�� */
	int get_offset_y() { return offset_y; }
	/** ��ȡ��ʱ��ƫ��ֵ */
	int get_snake() { return snake; }
	/** ���õ�ͼ�� */
	void set_snake(bool _snake) { is_snake = _snake; }
	/** �߼����� */
	void update();
	/** ���õ�ͼ״̬ */
	void reset() { map_x = 1500; }
	/** ������ͼ */
	void set_lock_scene(int _scene);
	/** ���õ�ͼƫ��ֵ */
	void set_offset(int x, int y) { offset_x = x;offset_y = y; }
	/** ���캯�� */
	Cmap();
	/** �������� */
	~Cmap();
};

/** @}*/ // ��ͼ��
/** @}*/ // ���������
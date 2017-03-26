#pragma once
/** @defgroup EXAMPLES ���������
*  @author  �Է�
*  @version 1.0
*  @date    2006-11-9
*  @{
*/
class CAnimate
	:public CPicture
{
	/** @name ������
	*  @{
	*/
	/** ��ǰ�� */
	int start_num;
	/** ��ʼ�� */
	int _start;
	/** ������ */
	int end_num;
	/** ͼƬ�������� */
	int x_num;
	/** ͼƬ�������� */
	int y_num;
	/** ��λ��� */
	int one_x;
	/** ��λ�߶� */
	int one_y;
	/** �Ƿ�ѭ������ */
	bool loop;
	/** �Ƿ񲥷���� */
	bool is_end;
	/** ���������� */
	int all_num;
	/** ����ÿ�嶯������ */
	int Speed_Time;
	/** ����ÿ�嶯������_��ʱ */
	int S_TIME;
public:
	/** ����������Ϸ���true */
	bool get_end() { return is_end; }
	/** �����߼� */
	void update();
	/** ������Ⱦ */
	void show();
	/** ���캯��
	*  @param file LPCWSTR imgname	ͼƬ��ַ
	*  @param file int all_x		����֡��
	*  @param file int all_y		����֡��
	*  @param file int start_num	��ʼ֡
	*  @param file int end_num		����֡
	*/
	CAnimate(LPCWSTR imgname, int all_x, int all_y, int start_num, int end_num);
	/** �������� */
	~CAnimate();
};

/** @}*/ // ������
/** @}*/ // ���������
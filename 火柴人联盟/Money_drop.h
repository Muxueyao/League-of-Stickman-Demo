#pragma once

/** @defgroup EXAMPLES ���������
*  @author  �Է�
*  @version 1.0
*  @date    2006-11-9
*  @{
*/
class CMoney_drop
	:public CObj
{
	/** @name ��ҵ���
	*  @{
	*/

	/** ���1ͼƬ���� */
	CUI_img *jb1;
	/** ���2ͼƬ���� */
	CUI_img *jb2;
	/** ���3ͼƬ���� */
	CUI_img *jb3;
	/** ���1������ƫ��ֵ */
	float jb1_x, x1_speed;
	float jb1_y, y1_speed;
	/** ���2������ƫ��ֵ */
	float jb2_x, x2_speed;
	float jb2_y, y2_speed;
	/** ���3������ƫ��ֵ */
	float jb3_x, x3_speed;
	float jb3_y, y3_speed;
	/** ƫ����ֵ */
	float speed;
	/** �����ײ���� */
	bool j1, j2, j3;
	/** ��ҵ�����Ƶ */
	CAudio4Bass		dropcoin;
	/** ʰȡ�����Ƶ */
	CAudio4Bass		money_Audio;
	/** ��ҵ������ */
	enum jb_time
	{
		one,	 /**< һ�� */
		two,	 /**< ���� */
		three,	 /**< ���� */
		four,	 /**< �Ĵ� */
	}jb1_time, jb2_time, jb3_time;
public:
	/** ��Ⱦ���� */
	void show();
	/** �߼����� */
	void update();
	/** ������Ա���� */
	void Release();
	/** ���캯��
	*  @param file  float x, float y ��ʾ����
	*/
	CMoney_drop(float x, float y);
	/** �������� */
	~CMoney_drop();
};
/** @}*/ // ��ҵ���
/** @}*/ // ���������

#pragma once
/** @defgroup EXAMPLES ���������
*  @author  �Է�
*  @version 1.0
*  @date    2006-11-9
*  @{
*/
class CUI_number
	:public CPicture
{
	/** @name ��ֵ��ʾ
	*  @{
	*/
	/** Ҫ��ʾ�ķ��� */
	int score;
	/** ��֡ͼƬ��� */
	int one_x;
	/** ��֡ͼƬ�߶� */
	int one_y;
	/** ȡ������ֵÿλ��,����λ */
	int number[8];

public:
	/** �߼����� */
	void update();
	/** ��Ⱦ���� */
	void show();
	/** ���÷��� */
	void set_score(int _score) { score = _score; }
	/** ���캯��
	*  @param file LPCTSTR img	ͼƬ��ַ
	*  @param file float _x		��ʾ����
	*  @param file float _y		��ʾ����
	*/
	CUI_number(LPCTSTR img,float _x,float _y);
	/** �������� */
	~CUI_number();
};

/** @}*/ // ��ֵ��ʾ
/** @}*/ // ���������
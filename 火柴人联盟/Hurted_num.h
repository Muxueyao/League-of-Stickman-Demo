#pragma once
/** @defgroup EXAMPLES ���������
*  @author  �Է�
*  @version 1.0
*  @date    2006-11-9
*  @{
*/
class CHurted_num
	:public CObj
{
	/** @name ͼƬ��ֵ��ʾ
	*  @{
	*/
	/** ����ͼƬ���� */
	CUI_number *number;
	/** ����Ч��ͼƬ���� */
	CUI_img *img2;
	/** ��ʾ����ֵ */
	int num;
	/** ��ʾʱ��_��ɾ������ */
	int show_time;
	/** ��ʾ���� */
	float x, y;
public:
	/** �߼����� */
	void update();
	/** ��Ⱦ���� */
	void show();
	/** ����ָ����� */
	void Release();
	/** ���캯��1 
	*  @param file LPCWSTR img_name ��ֵͼƬ��ַ
	*  @param file int num Ҫ��ʾ����ֵ
	*  @param file float x,float y ��ʾ������
	*  @param file LPCWSTR img2 ����Ч��ͼƬ��ַ
	*/
	CHurted_num(LPCWSTR img_name,int num,float x,float y,LPCWSTR img2);
	/** ���캯��2
	*  @param file LPCWSTR img_name ��ֵͼƬ��ַ
	*  @param file int num Ҫ��ʾ����ֵ
	*  @param file float x,float y ��ʾ������
	*/
	CHurted_num(LPCWSTR img_name, int num, float x, float y);
	/** �������� */
	~CHurted_num();
};

/** @}*/ // ͼƬ��ֵ��ʾ
/** @}*/ // ���������
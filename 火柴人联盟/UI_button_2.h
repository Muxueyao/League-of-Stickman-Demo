#pragma once

/** @defgroup EXAMPLES ���������
*  @author  �Է�
*  @version 1.0
*  @date    2006-11-9
*  @{
*/

/** @name ��ť��ʾ2
*  @{
*/
class CUI_button_2
	:public CObj
{
	/** ����ͼƬ֮���л�ʱ�� */
	float show_time, buffer_time;
	/** ͼƬ����1 */
	CUI_img *img_1;
	/** ͼƬ����2 */
	CUI_img *img_2;
public:
	/** ����ͼƬ1��ͼƬ2 */
	void Release();
	/** �߼� */
	void update();
	/** ��Ⱦ���� */
	void show();
	/** ���캯��
	*  @param file LPCWSTR img1 ͼ��1��ַ
	*  @param file LPCWSTR img2 ͼ��2��ַ
	*  @param file float x		��ʾ����
	*  @param file float y		��ʾ����
	*  @param file float time	����ͼƬ�л�ʱ��
	*/
	CUI_button_2(LPCWSTR img1,LPCWSTR img2,float x,float y,float time);
	/** �������� */
	~CUI_button_2();
};
/** @}*/ // ��ť��ʾ2

/** @}*/ // ���������

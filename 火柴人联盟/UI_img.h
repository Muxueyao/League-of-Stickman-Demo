#pragma once

/** @defgroup EXAMPLES ���������
*  @author  �Է�
*  @version 1.0
*  @date    2006-11-9
*  @{
*/

/** @name ����ͼƬ��
*  @{
*/
class CUI_img
	:public CPicture
{
public:
	/** ��Ⱦ���� */
	void show();
	/** �߼����� */
	void update();
	/** ��Ϸ��ͣ����
	*  @param file LPCWSTR img ͼƬ��ַ
	*/
	CUI_img(LPCWSTR img);
	/** �������� */
	~CUI_img();
};
/** @}*/ // ����ͼƬ��
/** @}*/ // ���������


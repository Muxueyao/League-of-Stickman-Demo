#pragma once
/** @defgroup EXAMPLES ���������
*  @author  �Է�
*  @version 1.0
*  @date    2006-11-9
*  @{
*/
class CUI_button
	//:public CObj
{
	/** @name UI��ť��
	*  @{
	*/
	/** �������ͼƬ */
	CUI_img *mousein;
	/** ����Ƴ�ͼƬ */
	CUI_img *mouseout;
	/** ��ʾ���� */
	bool is_show;
	/** X���� */
	int x;
	/** Y���� */
	int y;
	/** ͼƬ��� */
	int img_x;
	/** ͼƬ�߶� */
	int img_y;
	/** �����ť״̬ */
	bool is_end;
	
public:
	/** ���캯��
	*  @param file LPCWSTR in ��������ַ
	*  @param file LPCWSTR in ����Ƴ���ַ
	*  @param file float x	��ʾX����
	*  @param file float y	��ʾY����
	*/
	CUI_button(LPCWSTR in,LPCWSTR out,float x,float y);
	/** ������������ָ�� */
	void Release();
	/** �߼����� */
	void update();
	/** ��ȡ�����״̬ */
	bool get_state() { return is_end; }
	/** ������ʾ״̬ */
	void set_show(bool show);
	/** ��ȡ��ʾ */
	bool get_show() { return is_show; }
	/** �������� */
	~CUI_button();
};
/** @}*/ // UI��ť��
/** @}*/ // ���������


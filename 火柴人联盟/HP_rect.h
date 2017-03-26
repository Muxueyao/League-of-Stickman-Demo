#pragma once
/** @defgroup EXAMPLES ���������
*  @author  �Է�
*  @version 1.0
*  @date    2006-11-9
*  @{
*/
class CHP_rect
{
/** @name Ѫ����ʾ
*  @{
*/
	/** ������� */
	LPD3DXLINE  g_pLine_M;
	/** С������ */
	LPD3DXLINE  g_pLine_S;
	/** ��ʾ��ɫ */
	BYTE R, G, B;
	/** ��ʾ���� */
	float x, y;
	/** Ѫ���ٷֱ� */
	float hp;
	/** ����ٷֱ� */
	float buffer_hp;
public:
	/** ��Ա���� */
	void Release();
	/** ����Ѫ�� 
	*  @param file float _hp	Ѫ���ٷֱ�
	*  @param file float _x		��ʾ����
	*  @param file float _y		��ʾ����
	*/
	void set_hp(float _hp, float _x, float _y);
	/** ������ʾ��ɫ
	*/
	void set_color(BYTE _R, BYTE _G, BYTE _B) { R = _R; G = _G; B = _B; }
	/** ���캯��
	*/
	CHP_rect();
	/** ��������
	*/
	~CHP_rect();
};

/** @}*/ // Ѫ����ʾ
/** @}*/ // ���������
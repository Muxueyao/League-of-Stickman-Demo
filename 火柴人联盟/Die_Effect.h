#pragma once
/** @defgroup EXAMPLES ���������
*  @author  �Է�
*  @version 1.0
*  @date    2006-11-9
*  @{
*/

class CDie_Effect
	:public CObj
{
	/** @name ��������Ч��
	*  @{
	*/

	/** ö�ٳ���_ͼ�鵯����� */
	enum drop_time
	{
		one,	  /**< ��һ�ε��� */
		two,	  /**< �ڶ��ε��� */
		three,	  /**< �����ε��� */

	}i1_drop, i2_drop, i3_drop, i4_drop, i5_drop, i6_drop, i7_drop, i8_drop, i9_drop, i10_drop;

	/** ���������Ϻ����ؿ���,ʮ��ͼƬȫ��Ϊtrue��ɾ������ */
	bool i1s, i2s, i3s, i4s, i5s, i6s, i7s, i8s, i9s, i10s;
	/** ��ʾ���� */
	float x,y;
	/** ��ת�Ƕ� */
	float angle;
	/** X����,Y����,Y�ٶ�,X�ٶ�,Y��ƫ���ٶ� */
	float i1_x, i1_y, i1_offset_y, i1_offset_x, i1_y_speed;
	/** X����,Y����,Y�ٶ�,X�ٶ�,Y��ƫ���ٶ� */
	float i2_x, i2_y, i2_offset_y, i2_offset_x, i2_y_speed;
	/** X����,Y����,Y�ٶ�,X�ٶ�,Y��ƫ���ٶ� */
	float i3_x, i3_y, i3_offset_y, i3_offset_x, i3_y_speed;
	/** X����,Y����,Y�ٶ�,X�ٶ�,Y��ƫ���ٶ� */
	float i4_x, i4_y, i4_offset_y, i4_offset_x, i4_y_speed;
	/** X����,Y����,Y�ٶ�,X�ٶ�,Y��ƫ���ٶ� */
	float i5_x, i5_y, i5_offset_y, i5_offset_x, i5_y_speed;
	/** X����,Y����,Y�ٶ�,X�ٶ�,Y��ƫ���ٶ� */
	float i6_x, i6_y, i6_offset_y, i6_offset_x, i6_y_speed;
	/** X����,Y����,Y�ٶ�,X�ٶ�,Y��ƫ���ٶ� */
	float i7_x, i7_y, i7_offset_y, i7_offset_x, i7_y_speed;
	/** X����,Y����,Y�ٶ�,X�ٶ�,Y��ƫ���ٶ� */
	float i8_x, i8_y, i8_offset_y, i8_offset_x, i8_y_speed;
	/** X����,Y����,Y�ٶ�,X�ٶ�,Y��ƫ���ٶ� */
	float i9_x, i9_y, i9_offset_y, i9_offset_x, i9_y_speed;
	/** X����,Y����,Y�ٶ�,X�ٶ�,Y��ƫ���ٶ� */
	float i10_x, i10_y, i10_offset_y, i10_offset_x, i10_y_speed;
	/** Ʈ��X�ٶ� */
	float offset_x;

	/** ͼ��1���� */
	CUI_img *i1;
	/** ͼ��2���� */
	CUI_img *i2;
	/** ͼ��3���� */
	CUI_img *i3;
	/** ͼ��4���� */
	CUI_img *i4;
	/** ͼ��5���� */
	CUI_img *i5;
	/** ͼ��6���� */
	CUI_img *i6;
	/** ͼ��7���� */
	CUI_img *i7;
	/** ͼ��8���� */
	CUI_img *i8;
	/** ͼ��9���� */
	CUI_img *i9;
	/** ͼ��10���� */
	CUI_img *i10;
public:
	/** �߼����� */
	void update();
	/** ��Ⱦ���� */
	void show();
	/** ��������ָ�� */
	void Release();
	/** ���캯��
	*  @param file float x, float y ��ʾ����
	*  @param file  LPCWSTR img1,img2...... ͼ������
	*/
	CDie_Effect(float x, float y, LPCWSTR img1, LPCWSTR img2, LPCWSTR img3, LPCWSTR img4,
		LPCWSTR img5, LPCWSTR img6, LPCWSTR img7, LPCWSTR img8, LPCWSTR img9, LPCWSTR img10);
	/** �������� */
	~CDie_Effect();
};

/** @}*/ // ��������Ч��
/** @}*/ // ���������
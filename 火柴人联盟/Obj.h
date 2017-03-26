#pragma once
/** @defgroup EXAMPLES ���������
*  @author  �Է�
*  @version 1.0
*  @date    2006-11-9
*  @{
*/
class CObj
{
	/** @name �������
	*  @{
	*/
	/** ɾ������_��obj_management��ɾ�� */
	bool is_del;
	/** �Ƿ���ʾ_��obj_management����Ⱦ */
	bool is_show;

public:
	/** ö�ٳ���_���� */
	enum class_id
	{
		nul,		/**< �� */
		img,		/**< img���� */
		ui_number,	/**< ui_number���� */
		moneydrop,	/**< moneydrop���� */
		Hurted_num,	/**< Hurted_num���� */
		Die_Effect,	/**< Die_Effect���� */
	}id;
	/** ����������_����sortֵ��С */
	int sort;
	/** ��ȡ��ǰ������ֵ */
	int get_sort() { return sort; }
	/** ���ö����Ƿ���ʾ
	*  @param file show = true ��ʾ show = false ����
	*/
	void set_show(bool show) { is_show = show; }
	/** ����ɾ������
	*  @param file del = true ɾ��
	*/
	void set_del(bool del) { is_del = del; }
	/** ��ȡ�����Ƿ�ɾ��_����������е���
	*  @return ����ɾ��״̬
	*/
	bool get_del() { return is_del; }
	/** ��ȡ������ʾ״̬
	*  @return ������ʾ״̬
	*/
	bool get_show() { return is_show; }
	/** ������Ⱦ_�麯��*/
	virtual void show()=0;
	/** �����߼�_�麯��*/
	virtual void update()=0;
	/** ������������_�麯��*/
	virtual void Release() = 0;
	/** ���캯��*/
	CObj();
	/** ��������*/
	~CObj();
	/** @}*/ // �������

};

/** @}*/ // ���������
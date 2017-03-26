#pragma once
/** @defgroup EXAMPLES ���������
*  @author  �Է�
*  @version 1.0
*  @date    2006-11-9
*  @{
*/
/** @name �������
*  @{
*/
class CObj_management
{
	/** ���ж������� */
	list<CObj*>obj_list;
	/** ��������൥�� */
	static CObj_management *instance;
public:
	/** @name ����������
	*  @{
	*/
	class sort
	{
	public:
		bool operator()(CObj*, CObj*);
	};
	/** @}*/ // ����������

	/** ��ȡ��������
	*  @return ���ص�������
	*/
	static CObj_management *Getinstance();
	/** ��Ӷ�������
	*  @param file CObj *Obj�������
	*/
	void add(CObj *Obj);
	/** �������ж����߼�����Ⱦ���� */
	void update();
	/** ��ȡ�����������
	*  @return �����������
	*/
	int get_class_obj_num(CObj::class_id classid);
	/** ɾ���ض������ж����Ա
	*  @param file CObj::class_id classid ����ɾ�������ID 
	*  - �������е�ö��ֵ
	*/
	void clean_class(CObj::class_id classid);
	/** ���캯�� */
	CObj_management();
	/** �������� */
	~CObj_management();
};

/** @}*/ // �������
/** @}*/ // ���������
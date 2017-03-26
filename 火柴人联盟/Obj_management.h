#pragma once
/** @defgroup EXAMPLES 火柴人联盟
*  @author  赵飞
*  @version 1.0
*  @date    2006-11-9
*  @{
*/
/** @name 对象管理
*  @{
*/
class CObj_management
{
	/** 所有对象链表 */
	list<CObj*>obj_list;
	/** 对象管理类单例 */
	static CObj_management *instance;
public:
	/** @name 对象层次排序
	*  @{
	*/
	class sort
	{
	public:
		bool operator()(CObj*, CObj*);
	};
	/** @}*/ // 对象层次排序

	/** 获取单例对象
	*  @return 返回单例对象
	*/
	static CObj_management *Getinstance();
	/** 添加对象到链表
	*  @param file CObj *Obj传入对象
	*/
	void add(CObj *Obj);
	/** 调用所有对象逻辑与渲染函数 */
	void update();
	/** 获取链表对象数量
	*  @return 链表对象数量
	*/
	int get_class_obj_num(CObj::class_id classid);
	/** 删除特定类所有对象成员
	*  @param file CObj::class_id classid 传入删除对象的ID 
	*  - 对象类中的枚举值
	*/
	void clean_class(CObj::class_id classid);
	/** 构造函数 */
	CObj_management();
	/** 析构函数 */
	~CObj_management();
};

/** @}*/ // 对象管理
/** @}*/ // 火柴人联盟
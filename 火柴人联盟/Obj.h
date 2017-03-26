#pragma once
/** @defgroup EXAMPLES 火柴人联盟
*  @author  赵飞
*  @version 1.0
*  @date    2006-11-9
*  @{
*/
class CObj
{
	/** @name 对象基类
	*  @{
	*/
	/** 删除对象_在obj_management中删除 */
	bool is_del;
	/** 是否显示_在obj_management中渲染 */
	bool is_show;

public:
	/** 枚举常量_类名 */
	enum class_id
	{
		nul,		/**< 空 */
		img,		/**< img类名 */
		ui_number,	/**< ui_number类名 */
		moneydrop,	/**< moneydrop类名 */
		Hurted_num,	/**< Hurted_num类名 */
		Die_Effect,	/**< Die_Effect类名 */
	}id;
	/** 迭代器排序_根据sort值大小 */
	int sort;
	/** 获取当前排序数值 */
	int get_sort() { return sort; }
	/** 设置对象是否显示
	*  @param file show = true 显示 show = false 隐藏
	*/
	void set_show(bool show) { is_show = show; }
	/** 设置删除对象
	*  @param file del = true 删除
	*/
	void set_del(bool del) { is_del = del; }
	/** 获取对象是否删除_对象管理类中调用
	*  @return 对象删除状态
	*/
	bool get_del() { return is_del; }
	/** 获取对象显示状态
	*  @return 对象显示状态
	*/
	bool get_show() { return is_show; }
	/** 对象渲染_虚函数*/
	virtual void show()=0;
	/** 对象逻辑_虚函数*/
	virtual void update()=0;
	/** 对象内容析构_虚函数*/
	virtual void Release() = 0;
	/** 构造函数*/
	CObj();
	/** 析构函数*/
	~CObj();
	/** @}*/ // 对象基类

};

/** @}*/ // 火柴人联盟
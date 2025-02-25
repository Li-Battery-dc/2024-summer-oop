/*************************************************************************
【文件名】                 Store.hpp
【功能模块和目的】         建立程序运行期间的Store类
【开发者及日期】           刘东琛 2024.8.12
【更改记录】               （若修改过则必需注明）
*************************************************************************/
#ifndef Store_hpp
#define Store_hpp

#include "../3D_Element/Model.hpp"
#include <vector>

using std::vector;

/*************************************************************************
【类名】             Store
【功能】             作为程序运行期间储存model的类
【接口说明】         
	Store()
	默认构造函数。

	Store(const Store& Source)
	拷贝构造函数，用于复制另一个 Store 对象的所有属性。

	virtual ~Store()
	虚析构函数，保证派生类正确释放资源。

	Store& operator=(const Store& Source)
	赋值运算符，用于复制另一个 Store 对象的所有属性。

	bool AddModel(const Model& MyModel)
	向 Store 中添加一个模型。

	bool RemoveModel(const Model& MyModel)
	通过指定模型来移除一个模型。

	bool RemoveModel(unsigned int index)
	通过索引来移除模型。

	bool RemoveModel(const std::string& ModelName)
	通过模型名称来移除模型。

	Model& GetModel(unsigned int index) const
	通过索引获取 Store 中的模型引用。

	Model& GetModel(const std::string& ModelName) const
	通过模型名称获取 Store 中的模型引用。

	size_t Size() const
	获取 Store 中模型的数量。

【开发者及日期】     刘东琛 2024.8.12
【更改记录】         （若修改过则必需注明）
*************************************************************************/
class Store {
public:
	//显示给出一些基本函数方便后续添改
	//显式地给出构造函数
	Store();
	//显式地给出拷贝构造函数
	Store(const Store& Source);
	//显式地给出析构函数
	virtual ~Store();
	//显式地给出赋值运算符
	Store& operator=(const Store& Source);

	//向Store中添加模型
	bool AddModel(const Model& MyModel);

	//通过指定要移除的模型来移除一个模型
	bool RemoveModel(const Model& MyModel);
	//通过下标来移除模型
	bool RemoveModel(unsigned int index);
	//通过模型名来移除模型
	bool RemoveModel(const std::string& ModelName);
	//通过下标获取store中的模型引用
	Model& GetModel(unsigned int index) const;
	//通过模型名获取store中的模型引用
	Model& GetModel(const std::string& ModelName) const;

	//size的getter
	size_t Size() const { return m_ModelPtrs.size(); }
private:
	vector<shared_ptr<Model>> m_ModelPtrs;
};

#endif 

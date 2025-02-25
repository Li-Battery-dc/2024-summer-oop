/*************************************************************************
【文件名】                 Store.cpp
【功能模块和目的】         实现程序运行期间的Store类
【开发者及日期】           刘东琛 2024.8.12
【更改记录】               （若修改过则必需注明）
*************************************************************************/
#include "Store.hpp"
#include <exception>
#include <algorithm>

/*************************************************************************
【函数名称】       Store
【函数功能】       Store默认构造函数
【参数】           无
【返回值】         无
【开发者及日期】   刘东琛 2024.8.12
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Store::Store() {

}

/*************************************************************************
【函数名称】       Store
【函数功能】       Store默认复制构造函数
【参数】           参与复制的另一个元素
【返回值】         无
【开发者及日期】   刘东琛 2024.8.12
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Store::Store(const Store& Source) {
	m_ModelPtrs = Source.m_ModelPtrs;
}

/*************************************************************************
【函数名称】       Store
【函数功能】       Store默认析构函数
【参数】           无
【返回值】         无
【开发者及日期】   刘东琛 2024.8.12
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Store::~Store() {

}

/*************************************************************************
【函数名称】       operator=
【函数功能】       Store赋值运算符
【参数】           参与赋值的另一个元素
【返回值】         Store&
【开发者及日期】   刘东琛 2024.8.12
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Store& Store::operator=(const Store& Source) {
	return *this;
}

/*************************************************************************
【函数名称】       AddModel
【函数功能】       向Store中添加一个新的Model
【参数】           需要添加的Model
【返回值】         bool 表示添加成功
【开发者及日期】   刘东琛 2024.8.12
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Store::AddModel(const Model& MyModel) {
	//查找store中有没有相同名字的model
	auto it = find_if(m_ModelPtrs.begin(), m_ModelPtrs.end(), 
		[&MyModel](const std::shared_ptr<Model>& ptr) {
			return ptr->ModelName == MyModel.ModelName;
		});
	//仅添加非重名的model，便于通过model名称查找
	if (it == m_ModelPtrs.end()) { 
		std::shared_ptr<Model> NewModel = std::make_shared<Model>(MyModel);
		m_ModelPtrs.push_back(NewModel);
		return true;
	}
	else {
		throw std::exception("can not add a model with a name same as another model");
	}
}

/*************************************************************************
【函数名称】       RemoveModel
【函数功能】       在Store中删除一个指定的model
【参数】           需要删除的Model
【返回值】         bool 表示删除成功
【开发者及日期】   刘东琛 2024.8.12
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Store::RemoveModel(const Model& MyModel) {
	auto it = find_if(m_ModelPtrs.begin(), m_ModelPtrs.end(), 
		[&MyModel](const std::shared_ptr<Model>& ptr) {
			return *ptr == MyModel;	
		});	//使用lamda表达式表示对象的比较，而不是直接比较指针的值
	if (it != m_ModelPtrs.end()) {
		m_ModelPtrs.erase(it);
		return true;
	}
	return false;
}

/*************************************************************************
【函数名称】       RemoveModel
【函数功能】       在Store中删除一个指定下标的model
【参数】           需要删除的Model的下标
【返回值】         bool 表示删除成功
【开发者及日期】   刘东琛 2024.8.12
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Store::RemoveModel(unsigned int index) {
	if (index >= 0 && index < m_ModelPtrs.size()) {
		m_ModelPtrs.erase(m_ModelPtrs.begin() + index);
		return true;
	}
	else {
		throw std::exception("the index of model is out of range");
	}
}

/*************************************************************************
【函数名称】       RemoveModel
【函数功能】       在Store中删除一个指定名字的model
【参数】           需要删除的Model的模型名
【返回值】         bool 表示删除成功
【开发者及日期】   刘东琛 2024.8.12
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Store::RemoveModel(const std::string& ModelName){
	auto it = find_if(m_ModelPtrs.begin(), m_ModelPtrs.end(),
		[&ModelName](const std::shared_ptr<Model>& ptr) {
			return ptr->ModelName == ModelName;	
		});
	if (it != m_ModelPtrs.end()) {
		m_ModelPtrs.erase(it);
		return true;
	}
	else {
		throw std::exception("The Store has no member with the given name");
	}
}

/*************************************************************************
【函数名称】       GetModel
【函数功能】       获取Store中指定下标的Model
【参数】           需要获取的Model的下标
【返回值】         Model& 获取的Model的引用 
【开发者及日期】   刘东琛 2024.8.12
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Model& Store::GetModel(unsigned int index) const {
	if (index >= 0 && index < m_ModelPtrs.size()) {
		return *m_ModelPtrs[index];
	}
	else {
		throw std::exception("the index of model is out of range");
	}
}

/*************************************************************************
【函数名称】       GetModel
【函数功能】       获取Store中指定名字的Model
【参数】           需要获取的Model的模型名
【返回值】         Model& 获取的Model的引用 
【开发者及日期】   刘东琛 2024.8.12
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Model& Store::GetModel(const std::string& ModelName) const {
	auto it = find_if(m_ModelPtrs.begin(), m_ModelPtrs.end(),
		[&ModelName](const std::shared_ptr<Model>& ptr) {
			return ptr->ModelName == ModelName;	
		});
	if (it != m_ModelPtrs.end()) {
		return *(*it);
	}
	else {
		throw std::exception("The Store has no member with the given name");
	}
}
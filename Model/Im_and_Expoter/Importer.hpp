/*************************************************************************
【文件名】                 Importer.hpp
【功能模块和目的】         导入类基类的声明
【开发者及日期】           刘东琛 2024.8.11
【更改记录】               （若修改过则必需注明）
*************************************************************************/
#ifndef Impoter_hpp
#define Impoter_hpp

#include "../3D_Element/Model.hpp"

#include<string>

/*************************************************************************
【类名】             Importer
【功能】             作为导入类的基类
【接口说明】         
    Importer()
    默认构造函数。

    Importer(const Importer& Source)
    拷贝构造函数，用于复制另一个导入器的所有属性。

    Importer& operator=(const Importer& Source)
    赋值运算符，用于复制另一个导入器的所有属性。

    virtual ~Importer()
    虚析构函数，保证派生类正确释放资源。

    virtual Model Import(const std::string& FileName) const = 0
    纯虚函数，用于从指定文件名的文件中导入三维模型。必须在派生类中实现。

【开发者及日期】     刘东琛 2024.8.11
【更改记录】         （若修改过则必需注明）
*************************************************************************/
class Importer {
public:
    Importer();
    Importer(const Importer& Source);
    Importer& operator=(const Importer& Source);
    virtual ~Importer();
    //拥有一个纯虚的导入函数
    virtual Model Import(const std::string& FileName) const = 0;
};
#endif
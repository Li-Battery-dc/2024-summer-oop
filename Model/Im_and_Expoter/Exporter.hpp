/*************************************************************************
【文件名】                 Exporter.hpp
【功能模块和目的】         导出类基类的声明
【开发者及日期】           刘东琛 2024.8.11
【更改记录】               （若修改过则必需注明）
*************************************************************************/

#ifndef Expoter_hpp
#define Expoter_hpp

#include "../3D_Element/Model.hpp"
#include <string>

/*************************************************************************
【类名】             Exporter
【功能】             作为导出类的基类
【接口说明】         （必需）
    Exporter()
    默认构造函数。

    Exporter(const Exporter& Source)
    拷贝构造函数，用于复制另一个导出器的所有属性。

    virtual ~Exporter()
    虚析构函数，保证派生类正确释放资源。

    Exporter& operator=(const Exporter& Source)
    赋值运算符，用于复制另一个导出器的所有属性。

    virtual bool Export(const Model& MyModel, const std::string& FileName) = 0
    纯虚函数，用于导出三维模型到指定文件名的文件。必须在派生类中实现。
    
【开发者及日期】     刘东琛 2024.8.11
【更改记录】         （若修改过则必需注明）
*************************************************************************/
class Exporter{
public:
    Exporter();
    Exporter(const Exporter& Source);
    virtual ~Exporter();
    Exporter& operator=(const Exporter& Source);
    //拥有一个纯虚函数
    virtual bool Export(const Model& MyModel, const std::string& FileName) = 0;
};
#endif
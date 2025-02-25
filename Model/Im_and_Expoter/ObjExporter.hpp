/*************************************************************************
【文件名】                 ObjExporter.hpp
【功能模块和目的】         Obj导出类的声明
【开发者及日期】           刘东琛 2024.8.11
【更改记录】               （若修改过则必需注明）
*************************************************************************/
#ifndef ObjExporter_hpp
#define ObjExporter_hpp

#include "Exporter.hpp"
#include <string>

using std::string;

/*************************************************************************
【类名】             ObjExporter
【功能】             Obj文件的导出类
【接口说明】         
    ObjExporter()
    默认构造函数。

    ObjExporter(const ObjExporter& Source)
    拷贝构造函数，用于复制另一个 ObjExporter 对象的所有属性。

    virtual ~ObjExporter()
    虚析构函数，保证派生类正确释放资源。

    ObjExporter& operator=(const ObjExporter& Source)
    赋值运算符，用于复制另一个 ObjExporter 对象的所有属性。

    bool Export(const Model& MyModel, const string& FileName) override
    实现从 Model 类型对象导出到 .obj 文件的功能。此函数覆盖了基类 Exporter 中的纯虚函数。

【开发者及日期】     刘东琛 2024.8.11
【更改记录】         （若修改过则必需注明）
*************************************************************************/
class ObjExporter : public Exporter {
public:
    ObjExporter();
    ObjExporter(const ObjExporter& Source);
    virtual ~ObjExporter();
    ObjExporter& operator=(const ObjExporter& Source);
    //重写满足obj文件要求的导出功能
    bool Export(const Model& MyModel, const string& FileName) override;
};

#endif 

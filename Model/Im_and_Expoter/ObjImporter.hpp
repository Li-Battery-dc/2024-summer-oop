/*************************************************************************
【文件名】                 ObjImporter.hpp
【功能模块和目的】         obj导入类的声明
【开发者及日期】           刘东琛 2024.8.11
【更改记录】               （若修改过则必需注明）
*************************************************************************/
#ifndef ObjImporter_hpp
#define ObjImporter_hpp

#include "Importer.hpp"
#include <string>

using std::string;

/*************************************************************************
【类名】             ObjImporter
【功能】             obj导入类的说明
【接口说明】         
    ObjImporter()
    默认构造函数。

    ~ObjImporter()
    析构函数，保证资源的正确释放。

    ObjImporter(const ObjImporter& Source)
    拷贝构造函数，用于复制另一个 ObjImporter 对象的所有属性。

    ObjImporter& operator=(const ObjImporter& Source)
    赋值运算符，用于复制另一个 ObjImporter 对象的所有属性。

    Model Import(const string& FileName) const override
    实现从 .obj 文件格式中导入三维模型的功能。此函数覆盖了基类 Importer 中的纯虚函数。
    
【开发者及日期】     刘东琛 2024.8.11
【更改记录】         （若修改过则必需注明）
*************************************************************************/
class ObjImporter : public Importer {
public:
    ObjImporter();
    ~ObjImporter();
    ObjImporter(const ObjImporter& Source);
    ObjImporter& operator=(const ObjImporter& Source);
    //重写导入方法
    Model Import(const string& FileName) const override;
};
#endif
/*************************************************************************
【文件名】                 Controller.hpp
【功能模块和目的】         控制台类及其所用枚举类的声明
【开发者及日期】           刘东琛 2024.8.12
【更改记录】               （若修改过则必需注明）
*************************************************************************/
#ifndef Controller_hpp
#define Controller_hpp

#include <string>
#include "../Viewer/Response.hpp"
#include "../Model/3D_Element/Model.hpp"
#include "../Model/Store/Store.hpp"

using std::string;

/*************************************************************************
【类名】             Controller
【功能】             控制台类接受Viewer信息并对model进行操作
【接口说明】         
    static Controller& GetInstance()
    静态成员函数，用于获取 Controller 类的唯一实例。

    Response AutolySave(char choice)
    自动保存模型。

    Response ImportModel(const string& FileName)
    导入模型到 Store 中。

    Response ExportModel(unsigned int index, const string& FileName)
    通过索引导出模型到文件。

    Response ExportModel(const string& ModelName, const string& FileName)
    通过模型名称导出模型到文件。

    Response CreateNewModel(const string& name)
    创建一个新的模型并添加到 Store 中。

    Response ChangeName(unsigned int ModelIndex, const string& NewName)
    改变指定索引模型的名称。

    Response AddFaceByPoints(unsigned int ModelIndex, const vector<string>& PointString)
    通过点的字符串表示添加面到指定索引的模型。

    Response RemoveFace(unsigned int ModelIndex, int number)
    从指定索引的模型中移除面。

    Response ShowAllFace(unsigned int ModelIndex) const
    显示指定索引模型的所有面。

    Response ShowFace(unsigned int ModelIndex, int number) const
    显示指定索引模型中指定编号的面。

    Response ChangePointOfFace(unsigned int ModelIndex, int number, const string& PointName, const string& NewPointString)
    改变指定索引模型中指定编号面的指定点。

    Response AddLineByPoints(unsigned int ModelIndex, const vector<string>& PointString)
    通过点的字符串表示添加线到指定索引的模型。

    Response RemoveLine(unsigned int ModelIndex, int number)
    从指定索引的模型中移除线。

    Response ShowAllLine(unsigned int ModelIndex) const
    显示指定索引模型的所有线。

    Response ShowLine(unsigned int ModelIndex, int number) const
    显示指定索引模型中指定编号的线。

    Response ChangePointOfLine(unsigned int ModelIndex, int number, const string& PointName, const string& NewPointString)
    改变指定索引模型中指定编号线的指定点。

    Response DisPlaySatatics(unsigned int ModelIndex) const
    显示指定索引模型的统计信息。

    unsigned int FindModel(const string& ModelName) const
    通过模型名称找到其在 Store 中的索引。

【开发者及日期】     刘东琛 2024.8.12
【更改记录】         （若修改过则必需注明）
*************************************************************************/
class Controller{
public:
    //使用静态函数调用私有的构造函数创建静态对象作为单例
    static Controller& GetInstance();
   //自动保存
   Response AutolySave(char chooice);
    //相关操作函数
    //导入模型
    Response ImportModel(const string& FileName);
    //导出模型
    Response ExportModel(unsigned int index, const string& FileName);
    Response ExportModel(const string& ModelName, const string& FileName);
    //创建一个新的模型
    Response CreateNewModel(const string& name);
    
    //通过VIewer调用的一系列操作函数
    Response ChangeName(unsigned int ModelIndex, const string& NewName);
    Response AddFaceByPoints(unsigned int ModelIndex, const vector<string>& PointString);
    Response RemoveFace(unsigned int ModelIndex, int number);
    Response ShowAllFace(unsigned int ModelIndex) const;
    Response ShowFace(unsigned int ModelIndex, int number) const;
    Response ChangePointOfFace(unsigned int ModelIndex, int number, const string& PointName, const string& NewPointString);

    Response AddLineByPoints(unsigned int ModelIndex, const vector<string> PointString);
    Response RemoveLine(unsigned int ModelIndex, int number);
    Response ShowAllLine(unsigned int ModelIndex) const;
    Response ShowLine(unsigned int ModelIndex, int number) const;
    Response ChangePointOfLine(unsigned int ModelIndex, int number, const string& PointName, const string& NewPointString);

    Response DisPlaySatatics(unsigned int ModelIndex) const;

    //通过模型名获得其下标，便于通过模型名访问
    unsigned int FindModel(const string& ModelName) const;

private:
    //数据成员为model的仓库
    Store ModelStore;
    //将构造与析构函数设为私有，保证单例化设计
    Controller();
    virtual ~Controller();
    //删除赋值运算符和拷贝构造函数以保证单例化
    Controller(const Controller& Source) = delete;
    Controller& operator=(const Controller& Source) = delete;
};
#endif
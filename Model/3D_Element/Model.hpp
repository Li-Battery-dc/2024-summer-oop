/*************************************************************************
【文件名】                 MOodel.hpp
【功能模块和目的】         实现一个三维模型类
【开发者及日期】           刘东琛 2024.8.1
【更改记录】               （若修改过则必需注明）
*************************************************************************/
#ifndef Model_hpp
#define Model_hpp

#include "Line.hpp"
#include "Face.hpp"
#include "Point.hpp"
#include <memory>
#include <string>


using std::vector;
using std::shared_ptr;
using std::string;

/*************************************************************************
【类名】             Model
【功能】             通过整合点线面实现三维模型
【接口说明】         
    Model(const string& name = "Standard Model")
    默认构造函数，构造一个模型，模型名默认为 "Standard Model"。

    Model(const Model& Source)
    拷贝构造函数，用于复制另一个模型的所有属性。

    virtual ~Model()
    虚析构函数，保证派生类正确释放资源。

    Model& operator=(const Model& Source)
    赋值运算符，用于复制另一个模型的所有属性。

    bool operator==(const Model& AModel)
    判断两个模型是否相等。

    void ShowAllFace() const
    显示模型中所有面的信息。

    void ShowFace(int number) const
    显示模型中指定编号的面的信息。

    bool AddFace(const Point3D& pA, const Point3D& pB, const Point3D& pC)
    通过指定三个顶点向模型中添加一个新的面。

    bool RemoveFace(int number)
    移除模型中指定编号的面。

    bool ChangeFace(int number, const string& p_name, const Point3D& newPoint)
    更改模型中指定编号的面的指定点。

    void ShowAllLine() const
    显示模型中所有线段的信息。

    void ShowLine(int number) const
    显示模型中指定编号的线段信息。

    bool AddLine(const Point3D& pA, const Point3D& pB)
    通过指定线段的两个点向模型中添加一条新的线段。

    bool RemoveLine(int number)
    移除模型中指定编号的线段。

    bool ChangeLine(int number, const string& p_name, const Point3D& newPoint)
    更改模型中指定编号的线段的指定点。

    void UpdatePoints()
    更新模型中的点集合。

    void Display_Statistics() const
    显示模型的所有统计数据。

    void Display_FaceStatistics() const
    显示模型的面统计数据。

    void Display_LineStatistics() const
    显示模型的线段统计数据。

    double CalBoxVolume() const
    计算模型的最小包围盒体积。

    string ModelName
    模型的名称。

【开发者及日期】     刘东琛 2024.8.11
【更改记录】         （若修改过则必需注明）
*************************************************************************/
class Model {
public:
    //默认构造函数
    //默认模型名为Standard Model
    Model(const string& name = "Standard Model");
    //拷贝构造函数
    Model(const Model& Source);
    //析构函数
    virtual ~Model();
    //赋值运算符
    Model& operator=(const Model& Source);
    //重载判断相等运算符
    bool operator==(const Model& AModel);

    //显示model中所有的面的信息
    void ShowAllFace() const;

    //指定编号显示指定面的信息
    void ShowFace(int number) const;

    //通过指定三个顶点向model中添加一个新面
    bool AddFace(const Point3D& pA, const Point3D& pB, const Point3D& pC);

    //移除指定编号的面
    bool RemoveFace(int number);

    //更改指定编号的面的指定点
    bool ChangeFace(int number, const string& p_name, const Point3D& newPoint);

    //显示model中所有线段的信息
    void ShowAllLine() const;

    //显示指定编号的线段信息
    void ShowLine(int number) const;

    //通过指定线段的两个点添加一条线
    bool AddLine(const Point3D& pA, const Point3D& pB);

    //指定编号移除指定线段
    bool RemoveLine(int number);

    //更改指定线段的指定点
    bool ChangeLine(int number, const string& p_name, const Point3D& newPoint);

    //更新points中数据
    void UpdatePoints();

    //显示要求显示的所有数据
    void Display_Statistics() const;
    void Display_FaceStatistics() const;
    void Display_LineStatistics() const;

    //计算最小包围盒体积
    double CalBoxVolume() const;

    //常引用作为getter帮助获取模型信息
    const vector<Point3D>& Points{ m_Points };
    const vector<shared_ptr<Line3D>>& LinePtrs{ m_LinePtrs };
    const vector<shared_ptr<Face3D>>& FacePtrs{ m_FacePtrs };

    //一个没有任何修改要求的模型名应为公有的
    string ModelName;
private:
    //有一个points集合仅用于计算依赖于line和face的非重复点
    vector<Point3D> m_Points;
    vector<shared_ptr<Line3D>>  m_LinePtrs;
    vector<shared_ptr<Face3D>>  m_FacePtrs;
};

#endif
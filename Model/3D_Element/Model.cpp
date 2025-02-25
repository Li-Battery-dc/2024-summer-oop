/*************************************************************************
【文件名】                 MOodel.cpp
【功能模块和目的】         实现一个三维模型类
【开发者及日期】           刘东琛 2024.8.9
【更改记录】               （若修改过则必需注明）
*************************************************************************/
#include "Model.hpp"
#include "Face.hpp"
#include "Line.hpp"
#include "Point.hpp"
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <set>
#include <string>

using std::cout;
using std::endl;
using std::make_shared;
using std::string;

/*************************************************************************
【函数名称】       Model
【函数功能】       默认构造函数
【参数】           无
【返回值】         无
【开发者及日期】   刘东琛 2024.8.9
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Model::Model(const string& name): ModelName(name) {

}

/*************************************************************************
【函数名称】       Model
【函数功能】       拷贝构造函数
【参数】           被拷贝的Source
【返回值】         无
【开发者及日期】   刘东琛 2024.8.9
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Model::Model(const Model& Source) {
    ModelName = Source.ModelName;
    m_FacePtrs = Source.m_FacePtrs;
    m_LinePtrs = Source.m_LinePtrs;
    m_Points = Source.m_Points;
}

/*************************************************************************
【函数名称】       ~Model
【函数功能】       析构函数
【参数】           无
【返回值】         无
【开发者及日期】   刘东琛 2024.8.9
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Model:: ~Model() {

}

/*************************************************************************
【函数名称】       operator=
【函数功能】       重载赋值运算符
【参数】           参与赋值的Source
【返回值】         Model&
【开发者及日期】   刘东琛 2024.8.9
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Model& Model::operator=(const Model& Source) {
    if (this != &Source) {
        ModelName = Source.ModelName;
        m_FacePtrs = Source.m_FacePtrs;
        m_LinePtrs = Source.m_LinePtrs;
        m_Points = Source.m_Points;
    }
    return *this;
}

/*************************************************************************
【函数名称】       operator==
【函数功能】       重载判断相等运算符
【参数】           参与判断的另一个model
【返回值】         bool
【开发者及日期】   刘东琛 2024.8.9
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Model::operator==(const Model& AModel) {
    if (m_FacePtrs.size() != AModel.m_FacePtrs.size() || 
        m_LinePtrs.size() != AModel.m_LinePtrs.size()) {
            return false;
    }
    //两个model相同必须其中对象顺序也相同
    if (!m_FacePtrs.empty()) {
        for (size_t i = 0; i < m_FacePtrs.size(); i++) { 
            //地址不同的两个对象可能相等，通过解引用后的对象判断
            if (*m_FacePtrs[i] != *AModel.m_FacePtrs[i]) {
                return false;
            }
        }
    }
    if (!m_LinePtrs.empty()) {
        for (size_t i = 0; i < m_LinePtrs.size(); i++) {
            if (*m_LinePtrs[i] != *AModel.m_LinePtrs[i]) {
                return false;
            }
        }
    }
    return true;
}

/*************************************************************************
【函数名称】       ShowAllFace
【函数功能】       显示所有面的信息
【参数】           无
【返回值】         无
【开发者及日期】   刘东琛 2024.8.9
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
void Model::ShowAllFace() const {
    for (int i = 0; i < m_FacePtrs.size(); i++) {
        cout << "number " << i + 1 << " face's three points are" << endl
            << m_FacePtrs[i]->ToString() << endl
            << "and it's area is "  << m_FacePtrs[i]->CalArea() << endl;
    }
}

/*************************************************************************
【函数名称】       ShowFace
【函数功能】       显示指定编号的面的信息
【参数】           指定的编号
【返回值】         无
【开发者及日期】   刘东琛 2024.8.9
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
void Model::ShowFace(int number) const {
    if (number > 0 && number <= m_FacePtrs.size()) {
        cout << "number " << number << " face's three points are" << endl
            << m_FacePtrs[number - 1]->ToString() << endl
            << "and it's area is "  << m_FacePtrs[number - 1]->CalArea() << endl;
    }
    else {
        throw std::invalid_argument("the number is out of range");
    }
}

/*************************************************************************
【函数名称】       AddFace
【函数功能】       给定三个点添加一个三角面
【参数】           给定的三个点
【返回值】         bool 表示成功添加
【开发者及日期】   刘东琛 2024.8.9
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Model::AddFace(const Point3D& pA, const Point3D& pB, const Point3D& pC) {
    shared_ptr<Face3D> NewFace = make_shared<Face3D>(pA,pB,pC);
    bool HasSame = false;
    //先遍历内部搜索有没有相同的面
    for (auto ptr: m_FacePtrs) {
        if (*ptr == *NewFace) {  
            //要使用解引用后的对象比较，因为地址不同的面也可能是相等的
            HasSame = true;
        }
    }
    if (!HasSame) {
        m_FacePtrs.push_back(NewFace);
        UpdatePoints();
        return true;
    }
    else {
        throw std::invalid_argument("can not add same face element");
        return false;
    }
}

/*************************************************************************
【函数名称】       RemoveFace
【函数功能】       删除指定编号的face
【参数】           指定编号
【返回值】         bool 表示成功删除
【开发者及日期】   刘东琛 2024.8.9
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Model::RemoveFace(int number) {
    if (number > 0 && number <= m_FacePtrs.size()) {
        m_FacePtrs.erase(m_FacePtrs.begin() + (number - 1));    
        //指针被删除时其指向的对象也会被删除
        UpdatePoints();
        return true;
    }
    else {
        throw std::invalid_argument("the number is out of the range");
        return false;
    }
}

/*************************************************************************
【函数名称】       ChangeFace
【函数功能】       修改指定编号的面的指定点
【参数】           指定的编号number，指定的点名，需要修改为的新点
【返回值】         bool 表示成功修改
【开发者及日期】   刘东琛 2024.8.9
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Model::ChangeFace(int number, const std::string& p_name, const Point3D&  NewPoint) {
    if (number > 0 && number <= m_FacePtrs.size()) {
        m_FacePtrs[number - 1]->SetFace(p_name, NewPoint);
        UpdatePoints();
        return true;
    }
    else {
        throw std::invalid_argument("the number is out of the range");
        return false;
    }
}

/*************************************************************************
【函数名称】       ShowAllLine
【函数功能】       显示所有线段的信息
【参数】           无
【返回值】         无
【开发者及日期】   刘东琛 2024.8.9
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
void Model::ShowAllLine() const {
    for (int i = 0; i < m_LinePtrs.size(); i++) {
        cout << "number " << (i + 1) << " line's two points are" << endl
            << m_LinePtrs[i]->ToString() << endl
            << "and it's length is "  << m_LinePtrs[i]->GetLength() << endl;
    }
}

/*************************************************************************
【函数名称】       ShowLine
【函数功能】       显示指定编号的线段的信息
【参数】           指定的编号
【返回值】         无
【开发者及日期】   刘东琛 2024.8.9
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
void Model::ShowLine(int number) const {
    if (number > 0 && number <= m_LinePtrs.size()) {
        cout << "number " << number << " line's two points are" << endl
            << m_LinePtrs[number - 1]->ToString() << endl
            << "and it's length is "  << m_LinePtrs[number - 1]->GetLength() << endl;
    }
    else {
        throw std::invalid_argument("the number is out of range");
    }
}

/*************************************************************************
【函数名称】       AddLine
【函数功能】       指定两点添加一条线段
【参数】           指定的两个点
【返回值】         bool 表示成功添加
【开发者及日期】   刘东琛 2024.8.9
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Model::AddLine(const Point3D& pA, const Point3D& pB) {
    shared_ptr<Line3D> NewLine = make_shared<Line3D>(pA, pB);
    bool HasSame = false;
    for (auto ptr: m_LinePtrs) {
        if (*ptr == *NewLine) {
            HasSame = true;
        }
    }
    if (!HasSame) {
        m_LinePtrs.push_back(NewLine);
        UpdatePoints();
        return true;
    }
    else {
        throw std::invalid_argument("can not add same line element");
        return false;
    }
}

/*************************************************************************
【函数名称】       RemoveLine
【函数功能】       删除指定编号的线段
【参数】           指定的编号
【返回值】         bool 表示成功删除
【开发者及日期】   刘东琛 2024.8.9
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Model::RemoveLine(int number) {
    if (number > 0 && number <= m_LinePtrs.size()) {
        m_LinePtrs.erase(m_LinePtrs.begin() + (number - 1));
        UpdatePoints();
        return true;
    }
    else {
        throw std::invalid_argument("the number is out of the range");
        return false;
    }
}

/*************************************************************************
【函数名称】       ChangeLine
【函数功能】       指定编号和点来修改线段的顶点
【参数】           编号，需修改的点名，目标新点
【返回值】         bool 表示成功修改
【开发者及日期】   刘东琛 2024.8.9
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Model::ChangeLine(int number, const string&  p_name, const Point3D&  NewPoint) {
    if (number > 0 && number <= m_LinePtrs.size()) {
        m_LinePtrs[number - 1]->SetLine(p_name, NewPoint);
        UpdatePoints();
        return true;
    }
    else {
        throw std::invalid_argument("the number is out of the range");
        return false;
    }
}

/*************************************************************************
【函数名称】       UpdatePoints
【函数功能】       更新points中的点
【参数】           无
【返回值】         无
【开发者及日期】   刘东琛 2024.8.9
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
void Model::UpdatePoints() {
    //通过lamda表达式给出set的排序方式
    std::set<Point3D, bool(*)(const Point3D&, const Point3D&)> UniquePoints
        ([](const Point3D& a, const Point3D& b) {  
            return (a[Coord::x] < b[Coord::x] )||
                (a[Coord::x] == b[Coord::x] && a[Coord::y] < b[Coord::y]) ||
                (a[Coord::x] == b[Coord::x] && a[Coord::y] == b[Coord::y] && 
                a[Coord::z] < b[Coord::z]);
        }); //使用set保证不添加重复的点

    for (const auto& face : m_FacePtrs) {
        UniquePoints.insert(face->pA);
        UniquePoints.insert(face->pB);
        UniquePoints.insert(face->pC);
    }

    for (const auto& line : m_LinePtrs) {
        UniquePoints.insert(line->pA);
        UniquePoints.insert(line->pB);
    }
    //m_Points中存入排序好的点
    m_Points = vector<Point3D>(UniquePoints.begin(), UniquePoints.end());
}

/*************************************************************************
【函数名称】       Display_Statistics
【函数功能】       显示要求显示的相关信息
【参数】           无
【返回值】         无
【开发者及日期】   刘东琛 2024.8.9
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
void Model::Display_Statistics() const {
    cout << "the Model's name is " << ModelName << endl;
    Display_FaceStatistics();
    Display_LineStatistics();
    cout << "The number of points is " 
        << (m_FacePtrs.size() * 3 + m_LinePtrs.size() * 2) << endl;
    cout << "The volume of smallest cuboid containing all the points is " 
        << CalBoxVolume() << endl;
}

/*************************************************************************
【函数名称】       Display_Statistics
【函数功能】       显示面的总数和总面积
【参数】           无
【返回值】         无
【开发者及日期】   刘东琛 2024.8.9
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
void Model::Display_FaceStatistics() const {
    double SumArea = 0.0;
    for (auto ptr : m_FacePtrs) {
        SumArea += ptr->CalArea();
    }
    cout << "The number of faces is " << m_FacePtrs.size() << endl
        << "Their aera sum up is " << SumArea << endl;
}

/*************************************************************************
【函数名称】       Display_Statistics
【函数功能】       显示线段的总数和总长度
【参数】           无
【返回值】         无
【开发者及日期】   刘东琛 2024.8.9
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
void Model::Display_LineStatistics() const {
    double SumLength = 0.0;
    for (auto ptr: m_LinePtrs) {
        SumLength += ptr->GetLength();
    }
    cout << "The number of lines is " << m_LinePtrs.size() << endl
        << "Their length sum up is " << SumLength << endl;
}

/*************************************************************************
【函数名称】       CalBoxVolume
【函数功能】       计算包围所有点所需的最小包围盒体积
【参数】           无
【返回值】         无
【开发者及日期】   刘东琛 2024.8.9
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
double Model::CalBoxVolume() const {
    if (m_Points.empty()) {
        return 0.0;
    }
    //通过求出点坐标的xyz的最小和最大值来获取最小包围盒体积
    double minX = std::min_element(m_Points.begin(), m_Points.end(), 
        [](const Point3D& pa, const Point3D& pb) {
            return pa[Coord::x] < pb[Coord::x] ;
        })->GetPosition(Coord::x);

    double maxX = std::max_element(m_Points.begin(), m_Points.end(), 
        [](const Point3D& pa, const Point3D& pb) {
            return pa[Coord::x] < pb[Coord::x] ;
        })->GetPosition(Coord::x);

    double minY = std::min_element(m_Points.begin(), m_Points.end(), 
        [](const Point3D& pa, const Point3D& pb) {
            return pa[Coord::y] < pb[Coord::y] ;
        })->GetPosition(Coord::y);

    double maxY = std::max_element(m_Points.begin(), m_Points.end(), 
        [](const Point3D& pa, const Point3D& pb) {
            return pa[Coord::y] < pb[Coord::y] ;
        })->GetPosition(Coord::y);

    double minZ = std::min_element(m_Points.begin(), m_Points.end(), 
        [](const Point3D& pa, const Point3D& pb) {
            return pa[Coord::z] < pb[Coord::z] ;
        })->GetPosition(Coord::z);

    double maxZ = std::max_element(m_Points.begin(), m_Points.end(), 
        [](const Point3D& pa, const Point3D& pb) {
            return pa[Coord::z] < pb[Coord::z] ;
        })->GetPosition(Coord::z);

    return (maxX - minX) * (maxY - minY) * (maxZ - minZ); 
}
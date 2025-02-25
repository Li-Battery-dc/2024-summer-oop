/*************************************************************************
【文件名】                 Point3D.cpp
【功能模块和目的】         实现Point3D类
【开发者及日期】           刘东琛 2024.8.1
【更改记录】               （若修改过则必需注明）
*************************************************************************/

#include "Line.hpp"
#include "Point.hpp"
#include "Face.hpp"
#include <exception>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

/*************************************************************************
【函数名称】       Line_Constructor
【函数功能】       默认构造为一个三维空间中起点为原点，终点为(0,0,1)的直线
【参数】           无
【返回值】         无
【开发者及日期】   刘东琛 2024.8.1
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Line3D::Line3D() {
    m_pA = Point3D(0, 0, 0);
    m_pB = Point3D(0, 0, 1);
    m_Directionvector = UnitDirectionVector();
}

/*************************************************************************
【函数名称】       Line_Constructor
【函数功能】       指定起点和终点的直线
【参数】           输入起点和终点
【返回值】         无
【开发者及日期】   刘东琛 2024.8.1
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Line3D::Line3D(const Point3D& pA, const Point3D& pB) {
    SetLine(pA, pB);
    m_Directionvector = UnitDirectionVector();
}

/*************************************************************************
【函数名称】       ~Line3D
【函数功能】       完成函数析构
【参数】           无
【返回值】         无
【开发者及日期】   刘东琛 2024.8.1
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Line3D::~Line3D(){

}

/*************************************************************************
【函数名称】       Line3D
【函数功能】       完成拷贝构造函数
【参数】           拷贝对象
【返回值】         无
【开发者及日期】   刘东琛 2024.8.1
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Line3D::Line3D(const Line3D& Source) {
    SetLine(pA, pB);
    m_Directionvector = Source.m_Directionvector;
}

/*************************************************************************
【函数名称】       Operator=
【函数功能】       重载赋值运算符
【参数】           输入参数无符号整型维数
【返回值】         Line3D&
【开发者及日期】   刘东琛 2024.8.1
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Line3D& Line3D::operator=(const Line3D& Source) {
    if (this != &Source) {
        SetLine(pA, pB);
        m_Directionvector = Source.m_Directionvector;
    }
    return *this;
}

/*************************************************************************
【函数名称】       operator==
【函数功能】       重载判断相等运算符
【参数】           参与判断的第二条直线
【返回值】         bool
【开发者及日期】   刘东琛 2024.8.1
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Line3D::operator==(const Line3D& ALine) const {
    return (this->m_pA == ALine.pA && this->pB == ALine.pB) ||
        (this->pA == ALine.pB && this->pB == ALine.pA);
}

/*************************************************************************
【函数名称】       operator!=
【函数功能】       重载判断不等运算符
【参数】           参与判断的第二条直线
【返回值】         bool
【开发者及日期】   刘东琛 2024.8.1
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Line3D::operator!=(const Line3D& ALine) const {
    return !(*this == ALine);
}

/*************************************************************************
【函数名称】       GetLength
【函数功能】       计算直线长度
【参数】           无
【返回值】         double
【开发者及日期】   刘东琛 2024.8.1
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
double Line3D::GetLength() const {
    return Point3D::CalDistance(pA, pB);
}

/*************************************************************************
【函数名称】       operator<<
【函数功能】       重载判断流输出运算符，输出直线的相关信息
【参数】           输入参数为直线，输出参数为输出流
【返回值】         ostream&
【开发者及日期】   刘东琛 2024.8.1
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
std::ostream& operator<<(std::ostream& out, Line3D& ALine) {
    out << "PointA: " << ALine.m_pA << std::endl
        << "PointB: " << ALine.m_pB;
    return out;
}

/*************************************************************************
【函数名称】       ToString
【函数功能】       ToString方法输出直线的相关信息
【参数】           无
【返回值】         string
【开发者及日期】   刘东琛 2024.8.1
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
std::string Line3D::ToString() const {
    std::ostringstream out;
    out << "PointA: " << m_pA.ToString() << std::endl
        << "PointB: " << m_pB.ToString();
    return out.str();
}

/*************************************************************************
【函数名称】       SetLine
【函数功能】       更改直线的起点和终点
【参数】           输出直线的起点和终点
【返回值】         无
【开发者及日期】   刘东琛 2024.8.1
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
void Line3D::SetLine(const Point3D& pA, const Point3D& pB) {
    if (pA != pB) {
        m_pA = pA;
        m_pB = pB;
    }
    else {
        throw std::invalid_argument("can not set a line with two same point");
    }
}

/*************************************************************************
【函数名称】       SetLine
【函数功能】       指定更改的点
【参数】           输入希望更改的点的名字和需要设定的目标点
【返回值】         无
【开发者及日期】   刘东琛 2024.8.1
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
void Line3D::SetLine(const std::string& p_name, const Point3D& APoint) {
    switch (p_name[1]) {
        case 'A' : SetLine(APoint, pB);
        break;
        case 'B' : SetLine(pA, APoint);
        break;
        default: throw std::invalid_argument("invalid point name");
    }
}

/*************************************************************************
【函数名称】       UnitDirectionVector
【函数功能】       获取线段的方向向量
【参数】           无
【返回值】         Point3D
【开发者及日期】   刘东琛 2024.7.29
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Vector Line3D::UnitDirectionVector() const {
    Vector DirectionVector = pB - pA;    //获取方向向量
    return DirectionVector.Unitlize();
}

/*************************************************************************
【函数名称】       IntersectPoint()
【函数功能】       获取线段与另一个面的交点
【参数】           与线段相交的面
【返回值】         Point3D
【开发者及日期】   刘东琛 2024.7.29
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Point3D Line3D::IntersectPoint(const Face3D& AFace) const {
    if (!IsParallel(AFace)) {
        //构建平面方程
        //代入A点坐标计算标准平面方程ax + by + cz = Const中的常数项Const
        Vector Normal = AFace.NormalVector;
        double ConstPart = Normal * AFace.pA;
        //构建直线方程 P = pA + t * Direction
        //求出面上交点对应的t
        //t = pA到平面的距离 / 线面之间的夹角的cos值
        double t = abs(Normal[0] * pA[Coord::x] +
            Normal[1] * pA[Coord::y] + 
            Normal[2] * pA[Coord::z] - ConstPart) /
            (Normal * Directionvector);
            //注意到pA总是起点，所以t < 0 也说明没有相交
        if (t > 0 && t < GetLength()) {
            Point3D p = pA + Point3D(Directionvector * t); 
            return p;
        }
        else {
            throw std::exception
                ("The line is not intersected with the face");
        }
    }
    else {
        throw std::exception
            ("The line is not intersected with the face");
    }
}

/*************************************************************************
【函数名称】       IsOnLine
【函数功能】       判断点是否在直线上
【参数】           待判断的点
【返回值】         bool
【开发者及日期】   刘东琛 2024.7.29
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Line3D::IsOnLine(const Point3D& APoint3D) const {
    if (APoint3D != pA && APoint3D != pB) {
        return Line3D(pA, APoint3D).UnitDirectionVector() 
            == this->UnitDirectionVector();
    }
    else {
        return true;
    }
}

/*************************************************************************
【函数名称】       IsOnLine
【函数功能】       静态判断点是否在直线上
【参数】           待判断的点
【返回值】         bool
【开发者及日期】   刘东琛 2024.7.29
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Line3D::IsOnline(const Point3D &p, const Line3D &l) {
    return l.IsOnLine(p);
}

/*************************************************************************
【函数名称】       IsParallel
【函数功能】       判断两条线段是否平行
【参数】           待判断的线段
【返回值】         bool
【开发者及日期】   刘东琛 2024.7.29
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Line3D::IsParallel(const Line3D& OtherLIne) const {
    return UnitDirectionVector() == OtherLIne.UnitDirectionVector() && 
        *this != OtherLIne;  //且不重合
}

/*************************************************************************
【函数名称】       IsParallel
【函数功能】       静态调用判断两条线段是否平行
【参数】           待判断的两条线段
【返回值】         bool
【开发者及日期】   刘东琛 2024.7.29
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Line3D::IsParallel(const Line3D& Line1, const Line3D& Line2) {
    return Line1.IsParallel(Line2);
}

/*************************************************************************
【函数名称】       IsVertivcal
【函数功能】       静态调用判断两条线段是否垂直
【参数】           待判断的另一条线段
【返回值】         bool
【开发者及日期】   刘东琛 2024.8.4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Line3D::IsVertical(const Line3D& ALine) const {
    return abs(Directionvector * ALine.Directionvector - 0.0) < 1e-6;
}

/*************************************************************************
【函数名称】       IsVertivcal
【函数功能】       静态调用判断两条线段是否垂直
【参数】           待判断的两条线段
【返回值】         bool
【开发者及日期】   刘东琛 2024.8.4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Line3D::IsVertical(const Line3D& l1, const Line3D& l2) {
    return l1.IsVertical(l2);
}

/*************************************************************************
【函数名称】       IsInFace
【函数功能】       判断线段是否在面内
【参数】           待判断的面
【返回值】         bool
【开发者及日期】   刘东琛 2024.8.4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Line3D::IsInFace(const Face3D& AFace) const {
    return AFace.IsOnFace(pA) && AFace.IsOnFace(pB);
}

/*************************************************************************
【函数名称】       IsInFace
【函数功能】       静态调用判断线段是否在面内
【参数】           待判断的线与面
【返回值】         bool
【开发者及日期】   刘东琛 2024.8.4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Line3D::IsInFace(const Line3D& l, const Face3D& f) {
    return l.IsInFace(f);
}

/*************************************************************************
【函数名称】       IsParallel
【函数功能】       判断线与面是否平行
【参数】           待判断的面
【返回值】         bool
【开发者及日期】   刘东琛 2024.8.4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Line3D::IsParallel(const Face3D& AFace) const {
    return abs(AFace.NormalVector * Directionvector - 0.0) < 1e-6;
}

/*************************************************************************
【函数名称】       IsParallel
【函数功能】       静态调用判断两条线段是否垂直
【参数】           待判断的两条线段
【返回值】         bool
【开发者及日期】   刘东琛 2024.8.4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Line3D::IsParallel(const Line3D& l, const Face3D& f) {
    return abs(l.Directionvector * f.NormalVector - 0.0) < 1e-6;
}

/*************************************************************************
【函数名称】       IsIntersect
【函数功能】       判断线段与面是否相交
【参数】           待判断的面
【返回值】         bool
【开发者及日期】   刘东琛 2024.8.4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Line3D::IsIntersect(const Face3D& AFace) const {
    if (!IsParallel(AFace)) {
    //构建平面方程
    //代入A点坐标计算标准平面方程ax + by + cz = Const中的常数项Const
    Vector Normal = AFace.NormalVector;
    double ConstPart = Normal * AFace.pA;
    //构建直线方程 P = pA + t * Direction
    //求出面上交点对应的t
    //t = pA到平面的距离 / 线面之间的夹角的cos值
    double t = abs(Normal[0] * pA[Coord::x] +
        Normal[1] * pA[Coord::y] + 
        Normal[2] * pA[Coord::z] - ConstPart) /
        (Normal * Directionvector);
        //注意到pA总是起点，所以t < 0 也说明没有相交
        return t > 0 && t < GetLength();
    }
    else {
        return false;
    }
}

/*************************************************************************
【函数名称】       IsIntersect
【函数功能】       静态调用判断线段与面是否相交
【参数】           待判断的两条线段
【返回值】         bool
【开发者及日期】   刘东琛 2024.8.4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Line3D::IsIntersect(const Line3D& l, const Face3D& f) {
    return l.IsIntersect(f);
}
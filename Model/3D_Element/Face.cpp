/*************************************************************************
Face.hpp
实现一个三维空间的三角面类型
刘东琛 2024.7.29
【更改记录】               （若修改过则必需注明）
*************************************************************************/

#include "Face.hpp"
#include "Point.hpp"
#include "Vector.hpp"
#include <sstream>
#include <stdexcept>
#include <string>
#include <cmath>
#include <algorithm>

/*************************************************************************
【函数名称】       Face3D
【函数功能】       默认构造函数
【参数】           无
【返回值】         无
【开发者及日期】   刘东琛 2024.8.2
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Face3D::Face3D() {
    m_pA = Point3D(0, 0, 0);
    m_pB = Point3D(0, 0, 1);
    m_pC = Point3D(0, 1, 0);
    m_NormalVector = UnitNormalVector();
}

/*************************************************************************
【函数名称】       Face3D
【函数功能】       指定三个顶点的构造函数
【参数】           face的三个顶点
【返回值】         无
【开发者及日期】   刘东琛 2024.8.2
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Face3D::Face3D(const Point3D& pA, const Point3D& pB, const Point3D& pC) {
    SetFace(pA, pB, pC);
    m_NormalVector = UnitNormalVector();
}

/*************************************************************************
【函数名称】       ~Face3D
【函数功能】       默认析构函数
【参数】           无
【返回值】         无
【开发者及日期】   刘东琛 2024.8.2
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Face3D::~Face3D() {

}

/*************************************************************************
【函数名称】       Face3D
【函数功能】       拷贝构造函数
【参数】           拷贝对象
【返回值】         无
【开发者及日期】   刘东琛 2024.8.2
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Face3D::Face3D(const Face3D& Source) {
    SetFace(Source.pA, Source.pB, Source.pC);
    m_NormalVector = UnitNormalVector();
}

/*************************************************************************
【函数名称】       operator=
【函数功能】      重载赋值运算符
【参数】           被赋值的对象
【返回值】         face3D
【开发者及日期】   刘东琛 2024.8.2
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Face3D& Face3D::operator=(const Face3D& Source) {
    if (this != &Source) {
        SetFace(Source.pA, Source.pB, Source.pC);
        m_NormalVector = UnitNormalVector();
    }
    return *this;
}

/*************************************************************************
【函数名称】       operator==
【函数功能】       判断两个面是否相等
【参数】           被判断的对象
【返回值】         bool
【开发者及日期】   刘东琛 2024.8.2
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Face3D::operator==(const Face3D& AFace) const {
    std::vector<Point3D> m_Points = {pA, pB, pC};
    std::vector<Point3D> AFace_Points = {AFace.pA, AFace.pB, AFace.pC};
     //将三角形的三个点排序后进行比较，因为三个点相等有6种组合
    std::sort(m_Points.begin(), m_Points.end(), 
        [](const Point3D& p1, const Point3D& p2) { 
            return  (p1[Coord::x] < p2[Coord::x]) ||
                (p1[Coord::x] == p2[Coord::x] && p1[Coord::y] < p2[Coord::y]) ||
                (p1[Coord::x] == p2[Coord::x] && p1[Coord::y] == p2[Coord::y] && 
                p1[Coord::z] < p2[Coord::z]);
        }
    );

    std::sort(AFace_Points.begin(), AFace_Points.end(), 
        [](const Point3D& p1, const Point3D& p2) { 
            return  (p1[Coord::x] < p2[Coord::x]) ||
                (p1[Coord::x] == p2[Coord::x] && p1[Coord::y] < p2[Coord::y]) ||
                (p1[Coord::x] == p2[Coord::x] && p1[Coord::y] == p2[Coord::y] && 
                p1[Coord::z] < p2[Coord::z]);
        }
    );
    //实际上排序和判断的是点列的复制，不会因为排序更改原面中点的顺序
    return m_Points == AFace_Points;
}

/*************************************************************************
【函数名称】       operator!=
【函数功能】       判断两个函数不相等
【参数】           被判断的对象
【返回值】         无
【开发者及日期】   刘东琛 2024.8.2
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Face3D::operator!=(const Face3D& AFace) const {
    return !((*this) == AFace);
}

/*************************************************************************
【函数名称】       operator<<
【函数功能】       重载流操作运算符
【参数】           输出参数为输出流out，输入参数为需要输出的点
【返回值】         标准输出流
【开发者及日期】   刘东琛 2024.8.2
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
std::ostream& operator<<(std::ostream& out, const Face3D& AFace) {
    out << "PointA : " << AFace.pA.ToString() << std::endl
        << "PointB : " << AFace.pB.ToString() << std::endl
        << "PointC : " << AFace.pC.ToString();
    return out;
}

/*************************************************************************
【函数名称】       ToString
【函数功能】       通过获取对象的信息字符串输出对象信息
【参数】           无
【返回值】         string 对象信息的字符串
【开发者及日期】   刘东琛 2024.8.1
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
std::string Face3D::ToString() const {
    std::ostringstream out;
    out << "PointA : " << pA.ToString() << std::endl
        << "PointB : " << pB.ToString() << std::endl
        << "PointC : " << pC.ToString();
    return out.str();
}

/*************************************************************************
【函数名称】       SetFace
【函数功能】       更改face的点
【参数】           需要更改的点
【返回值】         无
【开发者及日期】   刘东琛 2024.8.2
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
void Face3D::SetFace(const Point3D& pA, const Point3D& pB, const Point3D& pC) {
    //要求任意两点不相等
    if (pA != pB && pA != pC && pB != pC) {
        m_pA = pA;
        m_pB = pB;
        m_pC = pC;
    }
    else {
        throw std::invalid_argument("can not set a face with any same point");
    }
}

/*************************************************************************
【函数名称】       SetFace
【函数功能】       通过指定某一点修改face中的点
【参数】           输入想要修改的点名和需要修改的点
【返回值】         无
【开发者及日期】   刘东琛 2024.8.2
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
void Face3D::SetFace(const std::string& p_name, const Point3D& APoint) {
    switch (p_name[1]) {
        case 'A' : SetFace(APoint, pB, pC);
        break;
        case 'B' : SetFace(pA, APoint, pC);
        break;
        case 'C' : SetFace(pA, pB, APoint);
        break;
        default: throw std::invalid_argument("Invalid point name");
    }
}

/*************************************************************************
【函数名称】       UnirNormalVector
【函数功能】       获取三角形的单位法向量
【参数】           无
【返回值】         Vector
【开发者及日期】   刘东琛 2024.8.2
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Vector Face3D::UnitNormalVector() const {
    Vector v1 = pC - pA;
    Vector v2 = pB - pA;
    return Vector::CrossProduct(v1, v2).Unitlize();
}

/*************************************************************************
【函数名称】       UnirNormalVector
【函数功能】       获取三角形的单位法向量
【参数】           无
【返回值】         Vector
【开发者及日期】   刘东琛 2024.8.2
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Face3D::IsOnFace(const Point3D& p) const {
    Vector PA = pA - p;
    Vector PB = pB - p;
    Vector PC = pC - p;
    //先计算点到面的距离判断是否在平面内
    if (abs(NormalVector * PA) < 1e-6) {
        //使用有向面积判断是否在三角形内部
        double S_PAB = Vector::CrossProduct(PA, PB).CalNorm() / 2.0;
        double S_PAC = Vector::CrossProduct(PA, PC).CalNorm() / 2.0;
        double S_PBC = Vector::CrossProduct(PB, PC).CalNorm() / 2.0;
        //有向面积之和为三角形面积说明其在三角形内部
        return S_PAB + S_PAC + S_PBC == CalArea();
    }
    else {
        return false;
    }
}

/*************************************************************************
【函数名称】       UnirNormalVector
【函数功能】       获取三角形的单位法向量
【参数】           无
【返回值】         Vector
【开发者及日期】   刘东琛 2024.8.2
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Face3D::IsOnFace(const Point3D& p, const Face3D& f) {
    return f.IsOnFace(p);
}

/*************************************************************************
【函数名称】       CalArea
【函数功能】       计算三角形面积
【参数】           无
【返回值】         double
【开发者及日期】   刘东琛 2024.8.2
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
double Face3D::CalArea() const {
    //使用海伦公式计算面积
    double a = Point3D::CalDistance(pA, pB);
    double b = Point3D::CalDistance(pA, pC);
    double c = Point3D::CalDistance(pC, pB);
    double p = CalPerimeter() / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

/*************************************************************************
【函数名称】       CalPerimeter
【函数功能】       计算三角形周长
【参数】           无
【返回值】         double
【开发者及日期】   刘东琛 2024.8.4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
double Face3D::CalPerimeter() const {
    double a = Point3D::CalDistance(pA, pB);
    double b = Point3D::CalDistance(pA, pC);
    double c = Point3D::CalDistance(pC, pB);
    return a + b + c;
}

/*************************************************************************
【函数名称】       IsSamePlane
【函数功能】       判断两个三角形是否共面
【参数】           参与判断的另一个三角形
【返回值】         bool
【开发者及日期】   刘东琛 2024.8.4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Face3D::IsSamePlane(const Face3D& AFace) const {
    if (IsParallel(AFace)) {
        //构建平面方程
        //代入A点坐标计算标准平面方程ax + by + cz = Const中的常数项Const
        double ConstPart = NormalVector * pA;
        //验算三个点都在平面内
        return NormalVector * AFace.pA == ConstPart &&
            NormalVector * AFace.pB == ConstPart &&
            NormalVector * AFace.pC == ConstPart;
    }
    else {
        return false;
    }
}

/*************************************************************************
【函数名称】       IsSamePlane
【函数功能】       静态调用判断两个三角形是否共面
【参数】           参与判断的两个三角形
【返回值】         bool
【开发者及日期】   刘东琛 2024.8.4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Face3D::IsSamePlane(const Face3D& f1, const Face3D& f2) {
    return f1.IsSamePlane(f2);
}

/*************************************************************************
【函数名称】       IsParallel
【函数功能】       判断两个三角形平面是否平行
【参数】           参与判断的另一个三角形
【返回值】         bool
【开发者及日期】   刘东琛 2024.8.4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Face3D::IsParallel(const Face3D& AFace) const {
    return NormalVector == AFace.NormalVector ||
        NormalVector == AFace.NormalVector * -1;
}

/*************************************************************************
【函数名称】       IsParallel
【函数功能】       静态调用判断两个三角形平面是否平行
【参数】           参与判断的两个三角形
【返回值】         bool
【开发者及日期】   刘东琛 2024.8.4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Face3D::IsParallel(const Face3D& f1, const Face3D& f2) {
    return f1.IsParallel(f2);
}
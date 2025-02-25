
/*************************************************************************
【文件名】                 Face.hpp
【功能模块和目的】         实现一个三维空间的三角面类型
【开发者及日期】           刘东琛 2024.8.1
【更改记录】               （若修改过则必需注明）
*************************************************************************/


#ifndef Face_hpp
#define Face_hpp

#include "Point.hpp"
#include <iostream>

/*************************************************************************
【类名】             Face3D
【功能】             构成三维世界所必须的面
【接口说明】         
Face3D()
默认构造函数，构造一个三个顶点分别为(0,0,0),(0,0,1),(0,1,0)的三角形。

Face3D(const Point3D& pA, const Point3D& pB, const Point3D& pC)
通过指定三个点构造一个三角形面。

virtual ~Face3D()
虚析构函数，保证派生类正确释放资源。

Face3D(const Face3D& Source)
拷贝构造函数，用于复制另一个三角形面的所有属性。

Face3D& operator=(const Face3D& Source)
赋值运算符，用于复制另一个三角形面的所有属性。

bool operator==(const Face3D& AFace) const
判断两个三角形面是否相等。

bool operator!=(const Face3D& AFace) const
判断两个三角形面是否不相等。

void SetFace(const Point3D& pA, const Point3D& pB, const Point3D& pC)
设置三角形面的三个顶点。

void SetFace(const std::string& p_name, const Point3D& pA)
修改三角形面的一个顶点。

Vector UnitNormalVector() const
获取三角形面的单位法向量。

bool IsOnFace(const Point3D& p) const
判断一个点是否在三角形面上。

double CalArea() const
计算三角形面的面积。

double CalPerimeter() const
计算三角形面的周长。

bool IsSamePlane(const Face3D& AFace) const
判断当前三角形面是否与另一个三角形面共面。

bool IsParallel(const Face3D& AFace) const;
判断当前三角形面是否与另一个三角形面共面。

static bool IsOnFace(const Point3D& p, const Face3D& f)
静态成员函数，判断一个点是否在三角形面上。

static bool IsSamePlane(const Face3D& f1, const Face3D& f2)
静态成员函数，判断两个三角形面是否共面。

static bool IsParallel(const Face3D& f1, const Face3D& f2);
静态成员函数，判断两个三角形面是否平行

friend std::ostream& operator<<(std::ostream& out, const Face3D& AFace)
重载流输出运算符，输出三角形面的相关信息。

【开发者及日期】     刘东琛 2024.8.1
【更改记录】         （若修改过则必需注明）
*************************************************************************/

class Face3D {
public:
    //默认构造出三个顶点分别为(0,0,0),(0,0,1),(0,1,0)的一个三角形
    Face3D();

    //指定三个顶点的构造函数
    Face3D(const Point3D& pA, const Point3D& pB, const Point3D& pC);

    //虚析构函数
    virtual ~Face3D();

    //拷贝构造函数
    Face3D(const Face3D& Source);

    //重载赋值运算符
    Face3D& operator=(const Face3D& Source);

    //重载判断相等运算符
    bool operator==(const Face3D& AFace) const;

    //重载判断不等运算符
    bool operator!=(const Face3D& AFace) const;

    //重载流运算符输出face相关信息
    friend std::ostream& operator<<(std::ostream& out, const Face3D& AFace);

    //使用ToString方法输出face相关信息
    std::string ToString() const;

    //给定三点坐标更改Face3D的属性
    void SetFace(const Point3D& pA, const Point3D& pB, const Point3D& pC);

    //指定修改某一顶点的坐标
    void SetFace(const std::string& p_name, const Point3D& pA);

    //获取face的单位法向量
    Vector UnitNormalVector() const;

    //判断点是否在面内
    bool IsOnFace(const Point3D& p) const;
    static bool IsOnFace(const Point3D& p, const Face3D& f);

    //计算面积
    double CalArea() const;

    //计算周长
    double CalPerimeter() const;

    //判断两个面是否共面
    bool IsSamePlane(const Face3D& AFace) const;
    static bool IsSamePlane(const Face3D& f1, const Face3D& f2);

    //判断两个面是否平行
    bool IsParallel(const Face3D& AFace) const;
    static bool IsParallel(const Face3D& f1, const Face3D& f2);

    //常引用作为Getter
    const Point3D& pA { m_pA };
    const Point3D& pB { m_pB };
    const Point3D& pC { m_pC };
    const Vector& NormalVector { m_NormalVector };
    
private:
    Point3D m_pA;
    Point3D m_pB;
    Point3D m_pC;
    Vector m_NormalVector;
};
#endif
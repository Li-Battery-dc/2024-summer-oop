
/*************************************************************************
【文件名】                 Line.hpp
【功能模块和目的】         实现一个三维空间的线段类型
【开发者及日期】           刘东琛 2024.8.1
【更改记录】               （若修改过则必需注明）
*************************************************************************/

#ifndef Line_hpp
#define Line_hpp

#include "Point.hpp"
#include "Face.hpp"
#include <iostream>

/*************************************************************************
【类名】             Line3D
【功能】             构成三维世界所必须的线段
【接口说明】         
    Line3D()
    默认构造函数，构造一个A点为原点，B点为(0,0,1)的直线。

    Line3D(const Point3D& pA, const Point3D& pB)
    通过指定两个点构造一条直线。

    virtual ~Line3D()
    虚析构函数，保证派生类正确释放资源。

    Line3D(const Line3D& Source)
    拷贝构造函数，用于复制另一条直线的所有属性。

    Line3D& operator=(const Line3D& Source)
    赋值运算符，用于复制另一条直线的所有属性。

    bool operator==(const Line3D& ALine) const
    判断两条直线是否相等。

    bool operator!=(const Line3D& ALine) const
    判断两条直线是否不相等

    double GetLength() const
    返回线段的长度。

    void SetLine(const Point3D& pA, const Point3D& pB)
    设置线段的两个端点。

    void SetLine(const std::string& p_name, const Point3D& APoint)
    修改线段的一个端点。

    Vector UnitDirectionVector() const
    获取直线的单位方向向量。

    Point3D IntersectPoint(const Face3D& AFace) const
    获取线段与面的交点。

    bool IsOnLine(const Point3D& APoint3D) const
    判断一个点是否在线段上。

    bool IsParallel(const Line3D& OtherLine) const
    判断当前直线是否与另一条直线平行。

    bool IsVertical(const Line3D& ALine) const
    判断当前直线是否与另一条直线垂直。

    bool IsInFace(const Face3D& AFace) const
    判断直线是否在面内。

    bool IsParallel(const Face3D& AFace) const
    判断直线是否与面平行。

    bool IsIntersect(const Face3D& AFace) const
    判断直线是否与面相交。

    static bool IsOnline(const Point3D& p, const Line3D& l)
    静态成员函数，判断一个点是否在线段上。

    static bool IsParallel(const Line3D& Line1, const Line3D& Line2)
    静态成员函数，判断两条直线是否平行。

    static bool IsVertical(const Line3D& l1, const Line3D& l2)
    静态成员函数，判断两条直线是否垂直。

    static bool IsInFace(const Line3D& l, const Face3D& f)
    静态成员函数，判断直线是否在面内。

    static bool IsParallel(const Line3D& l, const Face3D& f)
    静态成员函数，判断直线是否与面平行。

    static bool IsIntersect(const Line3D& l, const Face3D& f)
    静态成员函数，判断直线是否与面相交。

【开发者及日期】     刘东琛 2024.8.1
【更改记录】         （若修改过则必需注明）
*************************************************************************/

class Line3D {
public:
    //默认构造为一个三维空间中A点为原点，B点为(0,0,1)的直线
    Line3D();

    //通过指定两个点构造一条直线
    Line3D(const Point3D& pA, const Point3D& pB);

    //虚析构函数
    virtual ~Line3D();

    //拷贝构造函数
    Line3D(const Line3D& Source);

    //重载赋值运算符
    Line3D& operator=(const Line3D& Source);

    //重载判断相等运算符
    bool operator==(const Line3D& ALine) const;

    //重载不等运算符
    bool operator!=(const Line3D& ALine) const;

    //返回线段的长度
    double GetLength() const;

    //友元方法重载流输出线段相关信息
    friend std::ostream& operator<<(std::ostream& out, Line3D& ALine);

    //ToString方法输出线段信息
    std::string ToString() const;

    //Setter
    //输入两点坐标构成一条线段
    void SetLine(const Point3D& pA, const Point3D& pB);

    //单独修改一个点
    void SetLine(const std::string& p_name, const Point3D& APoint);

    //获取直线的单位方向向量
    Vector UnitDirectionVector() const;

    //获取线段与面的交点
    Point3D IntersectPoint(const Face3D& AFace) const;

    //判断点是否在线段上
    bool IsOnLine(const Point3D& APoint3D) const;
    static bool IsOnline(const Point3D& p, const Line3D& l);

    //判断两条线段是否平行
    bool IsParallel(const Line3D& OtherLIne) const;
    static bool IsParallel(const Line3D& Line1, const Line3D& Line2);

    //判断两条线段所在直线是否垂直
    bool IsVertical(const Line3D& ALine) const;
    static bool IsVertical(const Line3D& l1, const Line3D& l2);

    //判断线是否在面内
    bool IsInFace(const Face3D& AFace) const;
    static bool IsInFace(const Line3D& l, const Face3D& f);

    //判断线与面是否平行
    bool IsParallel(const Face3D& AFace) const;
    static bool IsParallel(const Line3D& l, const Face3D& f);

    //判断线段与面是否相交
    bool IsIntersect(const Face3D& AFace) const;
    static bool IsIntersect(const Line3D& l, const Face3D& f);

    //Getter
    const Point3D& pA { m_pA };
    const Point3D& pB { m_pB };
    const Vector& Directionvector { m_Directionvector };
private:
    Point3D m_pA;
    Point3D m_pB;
    Vector m_Directionvector;
};

#endif
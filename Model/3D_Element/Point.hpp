/*************************************************************************
Point3D.hpp
实现一个三维空间中的点类型
刘东琛 2024.8.1
【更改记录】               （若修改过则必需注明）
*************************************************************************/

#ifndef Point3D_hpp
#define Point3D_hpp

#include "Vector.hpp"
#include <iostream>

/*************************************************************************
【类名】             Coord
【功能】             使用枚举类来表示点的坐标
【接口说明】         （必需）
【开发者及日期】     （必需）
【更改记录】         （若修改过则必需注明）
*************************************************************************/
//将坐标vector中的三个坐标值绑定到x，y，z
enum class Coord {
    x, y, z
};

/*************************************************************************
【类名】             Point3D
【功能】             通过继承向量表示，构成三维世界所必须的点
【接口说明】         
    Point3D(double x = 0.0, double y = 0.0, double z = 0.0)
    构造一个具有给定坐标值的三维点。

    Point3D(const Point3D& Source)
    拷贝构造函数，用于复制另一个点的所有属性。

    virtual ~Point3D()
    虚析构函数，保证派生类正确释放资源。

    Point3D& operator=(const Point3D& Source)
    赋值运算符，用于复制另一个点的所有属性。

    Point3D& operator=(const Vector& Source)
    重写的赋值运算符，确保维度不变。

    bool operator==(const Point3D& APoint) const
    判断两个点是否相等。

    bool operator!=(const Point3D& APoint) const
    判断两个点是否不相等。

    double operator[](Coord Axis) const
    读取点中特定坐标轴上的坐标值。

    double& operator[](Coord Axis)
    获取点中特定坐标轴上的坐标值的引用，可用于修改该坐标值。

    friend std::ostream& operator<<(std::ostream& out, Point3D& APoint3D)
    重载流输出运算符，输出点的坐标。

    friend std::istream& operator>>(std::istream& in, Point3D& APoint3D)
    重载流输入运算符，输入点的坐标。

    double GetPosition(Coord Axis) const
    根据坐标轴获取点的坐标值。

    double CalDistance(const Point3D& APoint3D) const
    计算当前点与另一个点之间的距离。

    std::string ToString() const
    将点转换为字符串形式显示。

    static double CalDistance(const Point3D& p1, const Point3D& p2)
    静态成员函数，计算两点之间的距离。

【开发者及日期】     （必需）
【更改记录】         （若修改过则必需注明）
*************************************************************************/
//Point可看作一个向量的好处是，可以通过向量几何的一些运算进行几何关系的判断
class Point3D: public Vector {
public:
    // 添加一个接受三个double参数直接作为其坐标的构造函数
    Point3D(double x = 0.0, double y = 0.0, double z = 0.0);
                    
    // 重写使用Vector赋值点的赋值运算符，确保维度不变
    Point3D& operator=(const Vector& Source);

    //拷贝构造函数
    Point3D(const Point3D& Source);
    
    //考虑可能的继承使用，将析构函数设计为虚函数
    virtual ~Point3D();

    //重载赋值运算符
    Point3D& operator=(const Point3D& Source);

    //重载点与向量运算的+运算符表示点的移动
    Point3D operator+(const Vector& v) const;

    //判断相等运算符
    bool operator==(const Point3D& APoint) const;

    //重载判断不等运算符
    bool operator!=(const Point3D& APoint) const;

    //为点类指定使用枚举类指定x，y，z的访问方式
    //通过下标获得向量中的数据成员
    double GetPosition(Coord Axis) const;
    //重载下标运算符
    double operator[](Coord Axis) const;
    //通过下标更改向量中的数据成员
    double& operator[](Coord Axis);

    //计算点之间的距离
    //静态调用 输入两点
    static double CalDistance(const Point3D& p1, const Point3D& p2);
    //通过实例化对象调用计算距离
    double CalDistance(const Point3D& APoint3D) const;
    
    //重载流输出符来输出点的坐标
    friend std::ostream& operator<<(std::ostream& out, Point3D& APoint3D);
    //重载流输入运算符来按格式输入点的坐标
    friend std::istream& operator>>(std::istream& in, Point3D& APoint3D);
    //转化为字符串输出点的坐标
    std::string ToString() const;
private:
    //禁用点类进行向量的运算符
    //保留了-运算符因为点作差是有意义的
    double operator*(const Vector& AVector) const = delete;
    Vector operator*(double lamda) = delete;
    Vector operator/(double lamda) = delete;
    double CalNorm() const = delete;
    Vector Unitlize() const = delete;
    static Vector Mutiplication(const Vector& v1, const Vector& v2) = delete;
};
#endif
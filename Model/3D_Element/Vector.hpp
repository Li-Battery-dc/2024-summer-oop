/*************************************************************************
【文件名】                 Vector.cpp
【功能模块和目的】         实现一个可指定维数的向量类
【开发者及日期】           刘东琛 2024.8.1
【更改记录】               刘东琛 2024.8.16：将常引用getter改为函数式getter
*************************************************************************/
#ifndef Vector_hpp
#define Vector_hpp

#include <vector>
#include <initializer_list>

/*************************************************************************
【类名】             Vector
【功能】             实现一个三维空间中常用的向量类
【接口说明】         
    Vector() 
    默认构造函数，创建一个默认的向量。

    Vector(const std::initializer_list<double>& initList)
    使用初始化列表构造向量，列表中的元素数量决定向量的维度。

    Vector(unsigned int Dimension = 3)
    构造一个特定维度的向量，默认构造三维向量。

    Vector(const Vector& Source)
    拷贝构造函数，用于复制另一个向量的所有属性。

    virtual ~Vector()
    虚析构函数，保证派生类正确释放资源。

    Vector& operator=(const Vector& Source)
    赋值运算符，用于复制另一个向量的所有属性。

    bool operator==(const Vector& AVector) const
    判断两个向量是否相等。

    bool operator!=(const Vector& AVector) const
    判断两个向量是否不相等。

    double operator[](unsigned int index) const
    读取向量中特定位置的元素。

    double& operator[](unsigned int index)
    获取向量中特定位置元素的引用，可用于修改该元素。

    Vector operator+(const Vector& AVector) const
    向量加法。

    Vector operator-(const Vector& AVector) const
    向量减法。

    double operator*(const Vector& AVector) const
    向量点积（内积）。

    Vector operator*(double lambda)
    向量与标量相乘。

    double DotProduct(const Vector& AVector) const;
    计算两个向量点乘的结果

    Vector CrossProduct(const Vector& AVector)
    计算两个三维向量的叉乘结果。

    Vector operator/(double lambda)
    向量与标量相除。

    unsigned int Dimension() const
    返回向量的维度。

    double GetPosition(unsigned int index) const
    返回向量中特定位置的元素值。

    Vector Unitlize() const
    返回单位化后的向量。

    double CalNorm() const
    计算向量的模长（长度）。

    static Vector CrossProduct(const Vector& v1, const Vector& v2)
    静态成员函数，计算两个三维向量的叉乘结果。

    static double DotProduct(const Vector& v1, const Vector& v2);
    静态成员函数，计算两个向量的点乘结果.
【开发者及日期】     刘东琛 2024.8.1
【更改记录】         （若修改过则必需注明）
*************************************************************************/
class Vector {
public:
    //使用初始化列表来构造一个向量
    Vector(const std::initializer_list<double>& initList);

    //构造时指定其维数
    Vector(unsigned int Dimension = 3);

    //考虑可能的继承使用，将析构函数设计为虚函数
    virtual ~Vector();

    //重载赋值运算符
    Vector& operator=(const Vector& Source);

    //拷贝构造函数
    Vector(const Vector& Source);

    //重载多维向量相关运算符
    //判断相等运算符
    bool operator==(const Vector& AVector) const;

    //重载判断不等运算符
    bool operator!=(const Vector& AVector) const;

    //通过下标访问向量中某一数据成员
    //通过下标获得向量中的数据成员
    virtual double GetPosition(unsigned int index) const;

    //重载下标运算符
    double operator[](unsigned int index) const;

    //通过下标更改向量中的数据成员
    double& operator[](unsigned int index);

    //向量的加法
    Vector operator+(const Vector& AVector) const;

    //向量的减法
    Vector operator-(const Vector& AVector) const;

    //向量的内积
    double operator*(const Vector& AVector) const;
    double DotProduct(const Vector& AVector) const;
    static double DotProduct(const Vector& v1, const Vector& v2);

    //向量的数乘
    Vector operator*(double lamda);

    //向量的数乘作为除法
    Vector operator/(double lamda);

    //求向量的模长
    double CalNorm() const;

    //Getter
    unsigned int Dimension() const { return m_uiDimension; }
    
    //将一个向量单位化
    Vector Unitlize() const;

    //为三维向量添加叉乘运算
    Vector CrossProduct(const Vector& AVector) const;
    static Vector CrossProduct(const Vector& v1, const Vector& v2);

    //字面常量指定维数范围
    static const unsigned int MAXDIMENSION = 999;
    static const unsigned int MINDIMENSION = 1;

private:
    unsigned int m_uiDimension;

protected:
    //派生类将使用到vector的坐标
    std::vector<double> m_Coordinates;

};
#endif
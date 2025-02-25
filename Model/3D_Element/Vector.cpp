/*************************************************************************
【文件名】                 Vector.cpp
【功能模块和目的】         实现一个可指定维数的向量类
【开发者及日期】           刘东琛 2024.8.1
【更改记录】               （若修改过则必需注明）
*************************************************************************/

#include "Vector.hpp"
#include <cmath>
#include <stdexcept>

/*************************************************************************
【函数名称】       Vector_Constructor
【函数功能】       根据所给维数构造一个向量类,默认构造为一个三维的向量
【参数】           输入参数无符号整型维数
【返回值】         无
【开发者及日期】   刘东琛 2024.8.1
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Vector::Vector(unsigned  int Dimension) {
    if (Dimension > MAXDIMENSION || Dimension < MINDIMENSION) {
        throw std::invalid_argument("Invalid Dimension");
    }
    //空的坐标默认为0
    m_Coordinates = std::vector<double> (Dimension, 0.0);   
    m_uiDimension = Dimension;
}

/*************************************************************************
【函数名称】       Vector_Constructor
【函数功能】       使用初始化列表构造一个向量类
【参数】           输入一个初始化列表
【返回值】         无
【开发者及日期】   刘东琛 2024.8.1
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Vector::Vector(const std::initializer_list<double>& initList) {
    if (initList.size() >= MINDIMENSION && initList.size() < MAXDIMENSION) {
        m_uiDimension = initList.size();
        m_Coordinates = initList;
    }
    else {
        throw std::invalid_argument("Invalid initial list size");
    }
}

/*************************************************************************
【函数名称】       析构函数
【函数功能】       析构
【参数】           无
【返回值】         无
【开发者及日期】   刘东琛 2024.8.1
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Vector::~Vector() {
    
}

/*************************************************************************
【函数名称】       opetator=（）
【函数功能】       为Vector类重载赋值运算符
【参数】           输入一个Vector类的引用
【返回值】         返回被赋值后的该Vector类
【开发者及日期】   刘东琛 2024.8.1
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Vector& Vector::operator=(const Vector& Source) {
    if (this->m_uiDimension != Source.m_uiDimension) {
        throw std::invalid_argument
            ("Invalid = using two factors with different dimension");
    }
    if (this != &Source) {
        this->m_Coordinates = Source.m_Coordinates;
        this->m_uiDimension = Source.m_uiDimension;
    }
    return *this;
}

/*************************************************************************
【函数名称】       拷贝构造函数
【函数功能】       实现拷贝构造函数
【参数】           输入需要拷贝的vector
【返回值】         无
【开发者及日期】   刘东琛 2024.8.1
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Vector::Vector(const Vector& Source) {
    this->m_Coordinates = Source.m_Coordinates;
    this->m_uiDimension = Source.m_uiDimension;
}

/*************************************************************************
【函数名称】       opetator==
【函数功能】       为向量类重载相等逻辑运算符
【参数】           输入参与相等逻辑运算的另一个成员
【返回值】         bool
【开发者及日期】   刘东琛 2024.8.1
【更改记录】       2024.8.1 double的相等判断改为作差完成
*************************************************************************/
bool Vector::operator==(const Vector& AVector) const {
    bool flag = true;
    for (unsigned int i = 0; i < Dimension(); i++) {
        //浮点数的比较使用作差以e-6为单位
        if (!(abs(this->m_Coordinates[i] - AVector.m_Coordinates[i]) < 1e-6)) {
            flag = false;
        }
    }
    return flag;
}

/*************************************************************************
【函数名称】       opetator!=
【函数功能】       为向量类重载不等逻辑运算符
【参数】           输入参与不等逻辑运算的另一个成员
【返回值】         bool
【开发者及日期】   刘东琛 2024.7.22
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Vector::operator!=(const Vector& AVector) const {
    return !(*this == AVector);
}

/*************************************************************************
【函数名称】       operator[]
【函数功能】       重载下标运算符以通过下标运算符获得数据成员
【参数】           输入下标
【返回值】         double 返回对应下标中的坐标值
【开发者及日期】   刘东琛 2024.7.22
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
double Vector::operator[](unsigned int index) const {
    return GetPosition(index);
}

/*************************************************************************
【函数名称】       GetPosition
【函数功能】       通过下标获得数据成员
【参数】           输入下标
【返回值】         double 返回对应下标中的坐标值
【开发者及日期】   刘东琛 2024.7.22
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
double Vector::GetPosition(unsigned int index) const {
    if (index < Dimension()) {
        return m_Coordinates[index];
    }
    else{
        //下标越界
        throw std::exception("the Index out");  
    }
}

/*************************************************************************
【函数名称】       operator[]
【函数功能】       通过下标修改数据成员
【参数】           输入下标
【返回值】         double 返回对应下标中的坐标引用
【开发者及日期】   刘东琛 2024.7.22
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
double& Vector::operator[](unsigned int index) {
    if (index < Dimension()){
        return m_Coordinates[index];
    }
    else {
        throw std::invalid_argument("Invalid index");
    }       
}

/*************************************************************************
【函数名称】       operator+
【函数功能】       实现向量加法
【参数】           输入做加法的另一个向量
【返回值】         返回完成加法后的向量
【开发者及日期】   刘东琛 2024.7.22
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Vector Vector::operator+(const Vector& AVector) const {
    //向量加法只能对相同纬度使用
    if (this->Dimension() != AVector.Dimension()) {
        throw std::invalid_argument
            ("Invalid add using two Vector with different Dimension");
    }
    else {
        Vector Res(*this);
        for (unsigned int i = 0; i < Dimension(); i++) {
            Res[i] += AVector[i];
        }
        return Res;
    }
}

/*************************************************************************
【函数名称】       operator-
【函数功能】       实现向量减法
【参数】           输入做减法的另一个向量类
【返回值】         返回完成减法后的向量
【开发者及日期】   刘东琛 2024.7.22
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Vector Vector::operator-(const Vector& AVector) const {
    if (this->Dimension() != AVector.Dimension()) {
        throw std::invalid_argument
            ("Invalid sub using two Vector with different Dimension");
    }
    else {
        Vector Res(*this);
        for (unsigned int i = 0; i < Dimension(); i++) {
            Res[i] -= AVector[i];
        }
        return Res;
    }
}

/*************************************************************************
【函数名称】       operator*
【函数功能】       实现向量的数量积
【参数】           输入做数量积的另一个向量类
【返回值】         double 返回运算结果
【开发者及日期】   刘东琛 2024.7.22
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
double Vector::operator*(const Vector& AVector) const {
    if (this->Dimension() != AVector.Dimension()) {
        throw std::invalid_argument
            ("Invalid dot product using two Vector with different Dimension");
    }
    else {
        Vector Copy(*this);
        double Res = 0;
        for (unsigned int i = 0; i < Dimension(); i++) {
            Res += Copy[i] * AVector[i];
        }
        return Res;
    }
}

/*************************************************************************
【函数名称】       DotProduct
【函数功能】       实现向量的数量积
【参数】           输入做数量积的另一个向量类
【返回值】         double 返回运算结果
【开发者及日期】   刘东琛 2024.7.22
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
double Vector::DotProduct(const Vector& AVector) const {
    return AVector * (*this);
}

/*************************************************************************
【函数名称】       operator*
【函数功能】       静态调用实现向量的数量积
【参数】           输入做数量积的两个向量
【返回值】         double 返回运算结果
【开发者及日期】   刘东琛 2024.7.22
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
double Vector::DotProduct(const Vector& v1, const Vector& v2) {
    return v1 * v2;
}

/*************************************************************************
【函数名称】       operator*
【函数功能】       实现向量数乘运算
【参数】           输入数乘的倍数
【返回值】         Vector 数乘后的值
【开发者及日期】   刘东琛 2024.8.1
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Vector Vector::operator*(double lamda) {
    Vector Copy(*this);
    for (unsigned int i = 0; i < Dimension(); i++) {
        Copy[i] *= lamda;
    }
    return Copy;
}

/*************************************************************************
【函数名称】       operator/
【函数功能】       实现向量的数乘除法运算
【参数】           输入除数
【返回值】         Vector 数乘运算后的值
【开发者及日期】   刘东琛 2024.8.1
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Vector Vector::operator/(double lamba) {
    return (*this) * (1.0 / lamba);
}

/*************************************************************************
【函数名称】       CalNorm
【函数功能】       计算向量的模长
【参数】           无
【返回值】         double 返回向量的模长
【开发者及日期】   刘东琛 2024.8.1
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
double Vector::CalNorm() const {
    double Res = 0.0;
    for (unsigned int i = 0; i < Dimension(); i++) {
        Res += m_Coordinates[i] * m_Coordinates[i];
    }
    return sqrt(Res);
}

/*************************************************************************
【函数名称】       Unitlize
【函数功能】       实现向量的单位化
【参数】           无
【返回值】         Vector 单位化后的向量
【开发者及日期】   刘东琛 2024.8.1
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Vector Vector::Unitlize() const {
    Vector Copy(*this);
    return Copy / Copy.CalNorm();
}

/*************************************************************************
【函数名称】       CrossProduct
【函数功能】       实现向量的叉乘
【参数】           输入参与计算的另一个个向量
【返回值】         Vector 计算得到的向量
【开发者及日期】   刘东琛 2024.8.1
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Vector Vector::CrossProduct(const Vector& AVector) const {
    return Vector::CrossProduct(*this, AVector);
}

/*************************************************************************
【函数名称】       CrossProduct
【函数功能】       实现向量的叉乘
【参数】           输入参与计算的两个向量
【返回值】         Vector 计算得到的向量
【开发者及日期】   刘东琛 2024.8.1
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Vector Vector::CrossProduct(const Vector& v1, const Vector& v2) {
    //这里的叉乘只用于服务三维模型领域的使用
    if (v1.Dimension() == 3 && v2.Dimension() == 3) {
        Vector Res(3);
        Res[0] = v1[1] * v2[2] - v1[2] * v2[1];
        Res[1] = v1[0] * v2[2] - v1[2] * v2[0];
        Res[2] = v1[0] * v2[1] - v1[1] * v2[0];
        return Res;
    }
    else {
        throw std::invalid_argument
        ("mutiplication only for 3 dimension");
    }
}
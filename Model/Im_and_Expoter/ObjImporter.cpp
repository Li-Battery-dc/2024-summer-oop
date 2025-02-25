/*************************************************************************
【文件名】                 ObjImporter.cpp
【功能模块和目的】         实现obj导入类
【开发者及日期】           刘东琛 2024.8.11
【更改记录】               （若修改过则必需注明）
*************************************************************************/
#include "ObjImporter.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

/*************************************************************************
【函数名称】       ObjImporter
【函数功能】       ObjImporter默认构造函数
【参数】           无
【返回值】         无
【开发者及日期】   刘东琛 2024.8.11
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
ObjImporter::ObjImporter(){

}


/*************************************************************************
【函数名称】       ~ObjImporter
【函数功能】       ObjImporter析构函数
【参数】           无
【返回值】         无
【开发者及日期】   刘东琛 2024.8.11
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
ObjImporter::~ObjImporter() {

}

/*************************************************************************
【函数名称】       ObjImporter
【函数功能】       ObjImporter拷贝构造函数
【参数】           被拷贝的对象
【返回值】         无
【开发者及日期】   刘东琛 2024.8.11
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
ObjImporter::ObjImporter(const ObjImporter& Source) {

}

/*************************************************************************
【函数名称】       operator=()
【函数功能】       重载赋值运算符
【参数】           无
【返回值】         无
【开发者及日期】   刘东琛 2024.8.11
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
ObjImporter& ObjImporter::operator=(const ObjImporter& Source) {
    return *this;
}

/*************************************************************************
【函数名称】       Import
【函数功能】       实现obj文件的导入
【参数】           导入文件的路径
【返回值】         Model 导入得到的model实例
【开发者及日期】   刘东琛 2024.8.11
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Model ObjImporter::Import(const string& FileName) const { 
    //通过输入文件控制流实现导入
    std::ifstream file(FileName);
    if (!file.is_open()) {
        throw std::runtime_error("failed to open file " + FileName);
    }

    //循环外定义需要全函数使用的变量
    string TheLine;
    Model ImportedModel;
    vector<Point3D> ImportedPoints;
    while (std::getline(file, TheLine)) {
        //读取模型的名称
        if (TheLine.substr(0, 2) == "g ") {
            size_t FirstNotSpace = TheLine.find_first_not_of(" \t", 2); // 查找第一个非空白字符的位置
            if (FirstNotSpace != std::string::npos) {
                ImportedModel.ModelName = TheLine.substr(FirstNotSpace); 
            }
        }

        //读取文件中的点并存入ImportedPoints
        if (TheLine.substr(0,2) == "v ") {
            double x, y, z;
            std::istringstream iss(TheLine.substr(2));  //从“v ”后开始读
            if(!(iss >> x >> y >> z)) {
                continue;   //若读取失败则读取下一行
            }
            Point3D NewPoint(x, y, z);
            ImportedPoints.push_back(NewPoint);
        }

        //读取文件中线段点的索引，并添加到model中
        else if (TheLine.substr(0,2) == "l ") {
            unsigned int PointNumberA;
            unsigned int PointNumberB;
            std::istringstream iss(TheLine.substr(2));
            if (!(iss >> PointNumberA >> PointNumberB)) {
                continue;   //若读取失败则读取下一行
            }
            if (PointNumberA <= ImportedPoints.size() && PointNumberB <= ImportedPoints.size()) {
                ImportedModel.AddLine(ImportedPoints[PointNumberA - 1],
                    ImportedPoints[PointNumberB - 1]);
            }
        }

        //读取文件中三角面中点的索引，并添加到model中
        else if (TheLine.substr(0,2) == "f ") {
            unsigned int PointNumberA;
            unsigned int PointNumberB;
            unsigned int PointNumberC;
            std::istringstream iss(TheLine.substr(2));
            if (!(iss >> PointNumberA >> PointNumberB >> PointNumberC)) {
                continue;   //若读取失败则读取下一行
            }
            if (PointNumberA <= ImportedPoints.size() && PointNumberB <= ImportedPoints.size() 
                 && PointNumberC <= ImportedPoints.size()) {
                ImportedModel.AddFace(ImportedPoints[PointNumberA - 1],
                    ImportedPoints[PointNumberB - 1],
                    ImportedPoints[PointNumberC - 1]);
            }
        }
    }
    file.close();
    //通过返回值获取读取的模型
    return ImportedModel;
}
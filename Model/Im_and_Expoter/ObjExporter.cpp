/*************************************************************************
【文件名】                 ObjExporter.cpp
【功能模块和目的】         实现导出器类
【开发者及日期】           刘东琛 2024.8.11
【更改记录】               （若修改过则必需注明）
*************************************************************************/
#include "ObjExporter.hpp"
#include <fstream>
#include <map>
#include <functional>

const string& SPACE = " ";

/*************************************************************************
【函数名称】       ObjExporter
【函数功能】       ObjExporter默认构造函数
【参数】           无
【返回值】         无
【开发者及日期】   刘东琛 2024.8.11
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
ObjExporter::ObjExporter() {

}

/*************************************************************************
【函数名称】       ObjExporter
【函数功能】       ObjExporter拷贝构造函数
【参数】           被拷贝的对象
【返回值】         无
【开发者及日期】   刘东琛 2024.8.11
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
ObjExporter::ObjExporter(const ObjExporter& Source) {

}

/*************************************************************************
【函数名称】       ~ObjExporter
【函数功能】       ObjExporter析构函数
【参数】           无
【返回值】         无
【开发者及日期】   刘东琛 2024.8.11
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
ObjExporter::~ObjExporter() {

}

/*************************************************************************
【函数名称】       operator=()
【函数功能】       重载赋值运算符
【参数】           无
【返回值】         无
【开发者及日期】   刘东琛 2024.8.11
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
ObjExporter& ObjExporter::operator=(const ObjExporter& Source) {
	return *this;
}

/*************************************************************************
【函数名称】       Export
【函数功能】       导出一个obj文件
【参数】           需要导出的model和导出的路径
【返回值】         bool 表示导出成功
【开发者及日期】   刘东琛 2024.8.11
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool ObjExporter::Export(const Model& MyModel, const string& FileName) {
	//使用文件输出流完成导出
	std::ofstream file(FileName);
	if (!(file.is_open())) {
		return false;
	}

	// 文件开头为以#开头的文件名称和以g开头的模型名
	//文件名称从文件路径得到
	size_t Lastpath = FileName.find_last_of("/\\");
	if (Lastpath != string::npos) {
		string FileName_offPath = FileName.substr(Lastpath + 1);
		file << "# " + FileName_offPath << "\n";
	}
	file << "g " + MyModel.ModelName << "\n";

	//为使用map定义一个point的比较函数类
	using PointCompare = std::function<bool(const Point3D&, const Point3D&)>;
	PointCompare Compare = [](const Point3D& a, const Point3D& b) {
		return (a[Coord::x] < b[Coord::x]) ||
			(a[Coord::x] == b[Coord::x] && a[Coord::y] < b[Coord::y]) ||
			(a[Coord::x] == b[Coord::x] && a[Coord::y] == b[Coord::y] &&
			a[Coord::z] < b[Coord::z]);
		};
	//通过map来获取模型元素的点的索引
	std::map<Point3D, unsigned int, PointCompare> PointsIndexMap(Compare);

	//先导出模型中所有的点，并将其索引记录在map中
	for (unsigned int i = 0; i < MyModel.Points.size(); i++) {
		PointsIndexMap[MyModel.Points[i]] = i;
		file << "v " << MyModel.Points[i][Coord::x] << SPACE 
			<< MyModel.Points[i][Coord::y] << SPACE
			<< MyModel.Points[i][Coord::z] << "\n";
	}

	//通过map获取line中点的索引完成导出
	for (auto item : MyModel.LinePtrs) {
		unsigned int indexA = PointsIndexMap[item->pA];
		unsigned int indexB = PointsIndexMap[item->pB];
		file << "l " << indexA + 1 << SPACE << indexB + 1 << "\n";
	}

	//通过map获取face中点的索引完成导出
	for (auto item : MyModel.FacePtrs) {
		unsigned int indexA = PointsIndexMap[item->pA];
		unsigned int indexB = PointsIndexMap[item->pB];
		unsigned int indexC = PointsIndexMap[item->pC];
		file << "f " << indexA + 1 << SPACE << indexB + 1 << SPACE << indexC + 1 << "\n";
	}
	file.close();
	return true;
}
/*************************************************************************
【文件名】                 Controller.cpp
【功能模块和目的】         控制台类的实现
【开发者及日期】           刘东琛 2024.8.12
【更改记录】               （若修改过则必需注明）
*************************************************************************/
#include "Controller.hpp"
#include "../Model/Im_and_Expoter/ObjImporter.hpp"
#include "../Model/Im_and_Expoter/ObjExporter.hpp"
#include "../Viewer/Response.hpp"
#include <exception>
#include <sstream>

using std::cout;
using std::endl;
using std::cin;

/*************************************************************************
【函数名称】       GetInstance
【函数功能】       获取Controller类的单例引用
【参数】           无
【返回值】         无
【开发者及日期】   刘东琛 2024.8.13
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Controller& Controller::GetInstance() {
	static Controller ModelController;  //静态变量使得整个类都只有这一个单例
	return ModelController;
}

/*************************************************************************
【函数名称】       Controller
【函数功能】       Controller的构造函数
【参数】           无
【返回值】         无
【开发者及日期】   刘东琛 2024.8.13
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Controller::Controller() {

}

/*************************************************************************
【函数名称】       Controller
【函数功能】       Controller的析构函数，实现对store中的model自动保存
【参数】           无
【返回值】         无
【开发者及日期】   刘东琛 2024.8.13
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Controller::~Controller() {
    
}

/*************************************************************************
【函数名称】       AutolySave
【函数功能】       实现对store中的model自动保存
【参数】           viewer给出的choice
【返回值】         Response
【开发者及日期】   刘东琛 2024.8.13
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Response Controller::AutolySave(char choice) {
    if (choice == 'y') {
        cout << "Start exporting ...." << endl;
        cout << endl;
        for (int i = ModelStore.Size() - 1; i >= 0; i--) {
            //倒序导出避免store大小变化造成的越界问题
            string path;
            cout << "exporting number " << i + 1 << " model" << endl;
            cout << "input a save path for number " << i + 1 << " model" << endl;
            std::getline(cin, path);
            //输出一些空行使得输出更加美观
            cout << endl;
            if (!ObjExporter().Export(ModelStore.GetModel(i), path)) {
                //输入的文件路径无法打开时
                throw std::invalid_argument("invalid path");
            }
            else {
                cout << "Successfully exported number " << i + 1 << " model" << endl;                     
            }
        }
        return Response::Sucessfully_Export;
    }
}

/*************************************************************************
【函数名称】       ImportModel
【函数功能】       从文件中导入一个Model
【参数】           文件路径
【返回值】         给Viewer的处理信息
【开发者及日期】   刘东琛 2024.8.13
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Response Controller::ImportModel(const string& FileName) {
    if (ModelStore.AddModel(ObjImporter().Import(FileName))) {
        return Response::Successfully_Import;
    };
    return Response::Failed_to_Import;
}

/*************************************************************************
【函数名称】       ExportModel
【函数功能】       从文件中导出一个指定下标的Model
【参数】           指定的下标，文件路径
【返回值】         给Viewer的处理信息
【开发者及日期】   刘东琛 2024.8.13
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Response Controller::ExportModel(unsigned int index, const string& FileName) {
    if (ModelStore.Size() != 0){
        Model MyModel = ModelStore.GetModel(index);
        if (ObjExporter().Export(MyModel, FileName)) {
            //移出已经导出过的model止多次重复导出
            ModelStore.RemoveModel(MyModel);
            return Response::Sucessfully_Export;
        };
        return Response::Failed_to_Export;
    }
    else {
        cout << "Can not export. Store is empty!" << endl;
        return Response::None;
    }
}

/*************************************************************************
【函数名称】       ExportModel
【函数功能】       从文件中导出一个指定名称的Model
【参数】           模型名，文件路径
【返回值】         给Viewer的处理信息
【开发者及日期】   刘东琛 2024.8.13
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Response Controller::ExportModel(const string& ModelName, const string& FileName) {
    if (ModelStore.Size() != 0) {
        Model MyModel = ModelStore.GetModel(ModelName);
        if (ObjExporter().Export(MyModel, FileName)) {
            //移出已经导出过的model止多次重复导出
            ModelStore.RemoveModel(MyModel);
            return Response::Sucessfully_Export;
        };
        return Response::Failed_to_Export;
    }
    else {
        return Response::None;
    }
}

/*************************************************************************
【函数名称】       CreateNewModel
【函数功能】       创建一个新的model
【参数】           无
【返回值】         给Viewer的处理信息
【开发者及日期】   刘东琛 2024.8.13
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Response Controller::CreateNewModel(const string& name) {
    if (ModelStore.AddModel(Model(name))) {
        return Response::Sucessfully_create;
    }
    else {
        return Response::Failed_to_create;
    }
};
    
/*************************************************************************
【函数名称】       ChangeName
【函数功能】       改变模型的名称
【参数】           ModelIndex: 模型的索引，NewName: 新的模型名称
【返回值】         给Viewer的处理信息
【开发者及日期】   刘东琛 2024.8.13
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Response Controller::ChangeName(unsigned int ModelIndex, const string& NewName) {
    Model& CurrentModel = ModelStore.GetModel(ModelIndex);
    CurrentModel.ModelName = NewName;
    return Response::Sucessfully_change_name;
}

/*************************************************************************
【函数名称】       AddFaceByPoints
【函数功能】       通过输入的点字符串添加一个新面
【参数】           ModelIndex: 模型的索引，PointString: 点的字符串数组
【返回值】         给Viewer的处理信息
【开发者及日期】   刘东琛 2024.8.13
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Response Controller::AddFaceByPoints(unsigned int ModelIndex, const vector<string>& PointString) {
    Model& CurrentModel = ModelStore.GetModel(ModelIndex);
    Point3D pA; 
    Point3D pB; 
    Point3D pC;
    vector<Point3D> Points = {pA, pB, pC};
    for (int i = 0; i < 3 ; i++) {
        std::istringstream iss(PointString[i]);
        char openParen, comma1, comma2, closeParen;
        iss >> openParen >> Points[i][Coord::x] 
            >> comma1 >> Points[i][Coord::y] 
            >> comma2 >> Points[i][Coord::z] >> closeParen;
    }
    if (CurrentModel.AddFace(Points[0], Points[1], Points[2])) {
        return Response::Sucessfully_add_face;
    }
    else {
        return Response::Failed_to_edit;
    }
}

/*************************************************************************
【函数名称】       RemoveFace
【函数功能】       删除指定编号的面
【参数】           ModelIndex: 模型的索引，number: 要删除的面的编号
【返回值】         给Viewer的处理信息
【开发者及日期】   刘东琛 2024.8.13
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Response Controller::RemoveFace(unsigned int ModelIndex, int number) {
    Model& CurrentModel = ModelStore.GetModel(ModelIndex);
    if (CurrentModel.RemoveFace(number)) {
        return Response::Sucessfully_remove_face;
    }
    else {
        return Response::Failed_to_edit;
    }
}

/*************************************************************************
【函数名称】       ShowAllFace
【函数功能】       显示模型的所有面
【参数】           ModelIndex: 模型的索引
【返回值】         给Viewer的处理信息
【开发者及日期】   刘东琛 2024.8.13
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Response Controller::ShowAllFace(unsigned int ModelIndex) const {
    Model& CurrentModel = ModelStore.GetModel(ModelIndex);
    CurrentModel.ShowAllFace();
    return Response::Finished_show;
}

/*************************************************************************
【函数名称】       ShowFace
【函数功能】       显示模型中指定编号的面
【参数】           ModelIndex: 模型的索引，number: 要显示的面的编号
【返回值】         给Viewer的处理信息
【开发者及日期】   刘东琛 2024.8.13
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Response Controller::ShowFace(unsigned int ModelIndex, int number) const {
    Model& CurrentModel = ModelStore.GetModel(ModelIndex);
    CurrentModel.ShowFace(number);
    return Response::Finished_show;
}

/*************************************************************************
【函数名称】       ChangePointOfFace
【函数功能】       改变面的一个顶点
【参数】           ModelIndex: 模型的索引，number: 面的编号，PointName: 顶点的名称，NewPointString: 新顶点的字符串表示
【返回值】         给Viewer的处理信息
【开发者及日期】   刘东琛 2024.8.13
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Response Controller::ChangePointOfFace(unsigned int ModelIndex, 
    int number, const string& PointName, const string& NewPointString) {
        Model& CurrentModel = ModelStore.GetModel(ModelIndex);
        Point3D NewPoint;
        std::istringstream iss(NewPointString);
        char openParen, comma1, comma2, closeParen;
        iss >> openParen >> NewPoint[Coord::x] 
            >> comma1 >> NewPoint[Coord::y] 
            >> comma2 >> NewPoint[Coord::z] >> closeParen;
        if (CurrentModel.ChangeFace(number, PointName, NewPoint)) {
            return Response::Sucessfully_change_face;
        }
        else {
            return Response::Failed_to_edit;
        }
        
}

/*************************************************************************
【函数名称】       AddLineByPoints
【函数功能】       通过点集添加一条新线
【参数】           ModelIndex: 模型的索引，PointString: 点的字符串数组
【返回值】         给Viewer的处理信息
【开发者及日期】   刘东琛 2024.8.13
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Response Controller::AddLineByPoints(unsigned int ModelIndex, const vector<string> PointString) {
    Model& CurrentModel = ModelStore.GetModel(ModelIndex);
    Point3D pA; 
    Point3D pB; 
    vector<Point3D> Points = { pA, pB };
    for (int i = 0; i < 2 ; i++) {
        std::istringstream iss(PointString[i]);
        char openParen, comma1, comma2, closeParen;
        iss >> openParen >> Points[i][Coord::x] 
            >> comma1 >> Points[i][Coord::y] 
            >> comma2 >> Points[i][Coord::z] >> closeParen;
    }
    if (CurrentModel.AddLine(Points[0], Points[1])) {
        return Response::Sucessfully_add_face;
    }
    else {
        return Response::Failed_to_edit;
    }
    
}

/*************************************************************************
【函数名称】       RemoveLine
【函数功能】       删除指定编号的线
【参数】           ModelIndex: 模型的索引，number: 要删除的线的编号
【返回值】         给Viewer的处理信息
【开发者及日期】   刘东琛 2024.8.13
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Response Controller::RemoveLine(unsigned int ModelIndex, int number) {
    Model& CurrentModel = ModelStore.GetModel(ModelIndex);
    if (CurrentModel.RemoveLine(number)) {
        return Response::Sucessfully_remove_line;
    }
    else {
        return Response::Failed_to_edit;
    }
}

/*************************************************************************
【函数名称】       ShowAllLine
【函数功能】       显示模型的所有线
【参数】           ModelIndex: 模型的索引
【返回值】         给Viewer的处理信息
【开发者及日期】   刘东琛 2024.8.13
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Response Controller::ShowAllLine(unsigned int ModelIndex) const {
    Model& CurrentModel = ModelStore.GetModel(ModelIndex);
    CurrentModel.ShowAllLine();
    return Response::Finished_show;
}

/*************************************************************************
【函数名称】       ShowLine
【函数功能】       显示模型中指定编号的线
【参数】           ModelIndex: 模型的索引，number: 要显示的线的编号
【返回值】         给Viewer的处理信息
【开发者及日期】   刘东琛 2024.8.13
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Response Controller::ShowLine(unsigned int ModelIndex, int number) const {
    Model& CurrentModel = ModelStore.GetModel(ModelIndex);
    CurrentModel.ShowLine(number);
    return Response::Finished_show;
}

/*************************************************************************
【函数名称】       ChangePointOfLine
【函数功能】       改变线的顶点
【参数】           ModelIndex: 模型的索引，number: 线的编号，PointName: 顶点的名称，NewPointString: 新顶点的字符串表示
【返回值】         给Viewer的处理信息
【开发者及日期】   刘东琛 2024.8.13
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Response Controller::ChangePointOfLine(unsigned int ModelIndex, 
    int number, const string& PointName, const string& NewPointString) {
        Model& CurrentModel = ModelStore.GetModel(ModelIndex);
        Point3D NewPoint;
        std::istringstream iss(NewPointString);
        char openParen, comma1, comma2, closeParen;
        iss >> openParen >> NewPoint[Coord::x] 
            >> comma1 >> NewPoint[Coord::y] 
            >> comma2 >> NewPoint[Coord::z] >> closeParen;
        if (CurrentModel.ChangeLine(number, PointName, NewPoint)) {
            return Response::Sucessfully_change_face;
        }
        else {
        return Response::Failed_to_edit;
        }   
}

/*************************************************************************
【函数名称】       DisPlaySatatics
【函数功能】       显示模型的统计信息
【参数】           ModelIndex: 模型的索引
【返回值】         给Viewer的处理信息
【开发者及日期】   刘东琛 2024.8.13
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Response Controller::DisPlaySatatics(unsigned int ModelIndex) const {
    Model& CurrentModel = ModelStore.GetModel(ModelIndex);
    CurrentModel.Display_Statistics();
    return Response::Finished_show;
}

/*************************************************************************
【函数名称】       FindModel
【函数功能】       根据模型名称查找模型的索引
【参数】           ModelName: 模型的名称
【返回值】         模型的索引，如果找不到则抛出异常
【开发者及日期】   刘东琛 2024.8.13
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
unsigned int Controller::FindModel(const string& ModelName) const {
    for (unsigned int i = 0; i < ModelStore.Size(); i++) {
        if (ModelStore.GetModel(i).ModelName == ModelName) {
            return i;
        }
    }
    throw std::exception("The name is not found");
}
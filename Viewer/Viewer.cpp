/*************************************************************************
【文件名】                 Viewer.cpp
【功能模块和目的】         实现程序的界面类
【开发者及日期】           刘东琛 2024.8.15
【更改记录】               （若修改过则必需注明）
*************************************************************************/
#include"Viewer.hpp"
#include "../Controller/Controller.hpp"
#include <iostream>
#include <limits>
#include <string> 

using std::exception;
using std::cout;
using std::cin;
using std::endl;
using std::string;

/*************************************************************************
【函数名称】       Viewer
【函数功能】       Viewer默认构造函数
【参数】           无
【返回值】         无
【开发者及日期】   刘东琛 2024.8.15
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Viewer::Viewer(Controller& con): m_Controller(con){
    //构造函数直接作为主菜单入口
    Start();
}

Viewer::Viewer(const Viewer& Source): m_Controller(Source.m_Controller) {
    
}

/*************************************************************************
【函数名称】       Viewer
【函数功能】       Viewer默认析构函数
【参数】           无
【返回值】         无
【开发者及日期】   刘东琛 2024.8.15
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Viewer::~Viewer() {
    cout << "Do you want to save the Model left in Store ?(Enter y for yes, n for no)" << endl;
    char choice = ' ';
    cin >> choice;
    // 清除缓冲区中的换行符，防止影响后续读取
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //作为单例对象的controller会在最后析构,此时仍然可以调用
    m_Controller.AutolySave(choice);
}

/*************************************************************************
【函数名称】       operator=
【函数功能】       实现Viewer的赋值运算符
【参数】           被赋值的另一个对象
【返回值】         Viewer& 
【开发者及日期】   刘东琛 2024.8.15
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Viewer& Viewer::operator=(const Viewer& Source) {
    return *this;
}

/*************************************************************************
【函数名称】       Start
【函数功能】       Viewer的主菜单函数
【参数】           无
【返回值】         无
【开发者及日期】   刘东琛 2024.8.15
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
void Viewer::Start(){
    bool IsRunning = true;
    while (IsRunning){
        try {
            //展示主菜单
            cout << "--------------------------------" << endl;
            cout << "welcome, here is the main menu: " << endl;
            cout << "Enter a number to choose what you want to do" << endl;
            cout << "1. Add model to store" << endl;
            cout << "2. Export model from store" << endl;
            cout << "3. Edit or show model in store" << endl;
            cout << "0. Exit" << endl;
            cout << "--------------------------------" << endl;
            int arg = 0;
            if (!(cin >> arg)) { // 检查读取是否成功
                // 如果读取失败，清除失败状态并忽略剩余的输入
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("invalid input for main menu");
            }
            //根据输入打开不同的次级菜单
            switch (arg) {
                case 1 : {
                    AddModel();
                    cout << endl;   //菜单间加一些空行
                    break;
                }
                case 2 : {
                    ExportModel();
                    cout << endl;
                    break;
                }
                case 3 : {
                    Edit_or_ShowModel();
                    cout << endl;
                    break;
                }
                case 0 : {
                    cout << "Thank you for using. " << endl;
                    cout << "Exiting..." << endl;
                    IsRunning = false;
                    break;
                }
                default: throw std::invalid_argument("invalid input for main menu");
                    break;
            }
        }
        //Viewer只进行简单的错误显示帮助调试
        catch(exception e){
            cout << e.what() << endl;
        }
    }
}

/*************************************************************************
【函数名称】       InputArgument
【函数功能】       提示用户输入命令并返回命令
【参数】           无
【返回值】         Argument 用户输入的命令
【开发者及日期】   刘东琛 2024.8.15
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Argument Viewer::InputArgument() const {
    std::cout << "--------------------------------" << std::endl;
    std::cout << "Input a number to choose what you want to do:" << std::endl;
    std::cout << "1. Change Name" << std::endl;
    std::cout << "2. Add Face By Points" << std::endl;
    std::cout << "3. Remove Face" << std::endl;
    std::cout << "4. Show All Faces" << std::endl;
    std::cout << "5. Show Face" << std::endl;
    std::cout << "6. Change Point Of Face" << std::endl;
    std::cout << "7. Add Line By Points" << std::endl;
    std::cout << "8. Remove Line" << std::endl;
    std::cout << "9. Show All Lines" << std::endl;
    std::cout << "10. Show Line" << std::endl;
    std::cout << "11. Change Point Of Line" << std::endl;
    std::cout << "12. Display Statistics" << std::endl;
    std::cout << "0. Back to last menu" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    int choice = 0;
    bool IsRunning = true;
    //合法输入直接return跳出循环
    while (IsRunning) {
        if (!(cin >> choice)) { // 检查读取是否成功
            // 如果读取失败，清除失败状态并忽略剩余的输入
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw std::invalid_argument("invalid input for main menu");
        }
        switch (choice) {
            case 1 : return Argument::ChangeName;
            case 2 : return Argument::AddFaceByPoints;
            case 3 : return Argument::RemoveFace;
            case 4 : return Argument::ShowAllFace;
            case 5 : return Argument::ShowFace;
            case 6 : return Argument::ChangePointOfFace;
            case 7 : return Argument::AddLineByPoints;
            case 8 : return Argument::RemoveLine;
            case 9 : return Argument::ShowAllLine;
            case 10 : return Argument::ShowLine;
            case 11 : return Argument::ChangePointOfLine;
            case 12 : return Argument::DisplayStastics;
            case 0 : return Argument::Back;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                return Argument::None;
        }
    }
}

/*************************************************************************
【函数名称】       ShowResponse
【函数功能】       接受Controller返回的结果并打印
【参数】           Response Controller返回的结果
【返回值】         无
【开发者及日期】   刘东琛 2024.8.15
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
void Viewer::ShowResponse(Response res) const {
    switch (res) {
        //返回结果后打印一个空行再开启下一个菜单
        case Response::None :
            std::cout << "No response." << std::endl;
            std::cout << std::endl;
            break;
        case Response::Invalid_input :
            std::cout << "Invalid input detected." << std::endl;
            std::cout << std::endl;
            break;
        case Response::Successfully_Import :
            std::cout << "Successfully imported." << std::endl;
            std::cout << std::endl;
            break;
        case Response::Failed_to_Import :
            std::cout << "Failed to import." << std::endl;
            std::cout << std::endl;
            break;
        case Response::Sucessfully_Export :
            std::cout << "Successfully exported." << std::endl;
            std::cout << std::endl;
            break;
        case Response::Failed_to_Export :
            std::cout << "Failed to export." << std::endl;
            std::cout << std::endl;
            break;
        case Response::Sucessfully_create :
            std::cout << "Successfully created." << std::endl;
            std::cout << std::endl;
            break;
        case Response::Failed_to_create :
            std::cout << "Failed to create." << std::endl;
            std::cout << std::endl;
            break;
        case Response::Sucessfully_change_name :
            std::cout << "Successfully changed name." << std::endl;
            std::cout << std::endl;
            break;
        case Response::Sucessfully_add_face :
            std::cout << "Successfully added face." << std::endl;
            std::cout << std::endl;
            break;
        case Response::Sucessfully_remove_face :
            std::cout << "Successfully removed face." << std::endl;
            std::cout << std::endl;
            break;
        case Response::Sucessfully_change_face :
            std::cout << "Successfully changed face." << std::endl;
            std::cout << std::endl;
            break;
        case Response::Sucessfully_add_line :
            std::cout << "Successfully added line." << std::endl;
            std::cout << std::endl;
            break;
        case Response::Sucessfully_remove_line :
            std::cout << "Successfully removed line." << std::endl;
            std::cout << std::endl;
            break;
        case Response::Sucessfully_change_line :
            std::cout << "Successfully changed line." << std::endl;
            std::cout << std::endl;
            break;
        case Response::Failed_to_edit :
            std::cout << "Failed to edit" << std::endl;
            std::cout << std::endl;
            break;
        case Response::Finished_show :
            std::cout << "Finished showing model." << std::endl;
            std::cout << std::endl;
            break;
        default :
            std::cout << "Unknown response type." << std::endl;
            std::cout << std::endl;
            break;
    }
}

/*************************************************************************
【函数名称】       AddModel
【函数功能】       打开与向库中添加模型相关的的菜单
【参数】           无
【返回值】         无
【开发者及日期】   刘东琛 2024.8.15
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
void Viewer::AddModel(){
    bool IsRunning = true;
    try {
        while (IsRunning) {
            //添加模型的二级菜单
            cout << "--------------------------------" << endl;
            cout << "How do you want to add a new model? " << endl;
            cout << "input a number to choose: " << endl;
            cout << "1. import a model from a file " << endl;
            cout << "2. create a new model " << endl;
            cout << "0. back to the main menu " << endl;
            cout << "--------------------------------" << endl;
            int arg;
            if (!(cin >> arg)) { // 检查读取是否成功
                // 如果读取失败，清除失败状态并忽略剩余的输入
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("invalid input for main menu");
            }
            switch (arg) {
            //从文件中导入一个模型
            case 1 : {
                cout << "Where do you want to import a model from? " << endl;
                cout << "input a file path: " << endl;
                string path;
                //使用getline来获取整行路径，防止文件名中空格影响cin输入
                //输入前忽略上一次输入的换行符
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, path);
                ShowResponse(m_Controller.ImportModel(path));
                break;
            }
            //新建一个待操作的空模型
            case 2 : {
                cout << "input a name for your new model: " << endl;
                string name;
                cin >> name;
                ShowResponse(m_Controller.CreateNewModel(name));
                break;
            }
            //返回上级菜单
            case 0 : {
                IsRunning = false;
                break;
            }
            default :
                throw std::invalid_argument("invalid argument input ");
            }
        }
    }
    catch(exception e){
        cout << e.what() << endl;
    }
}

/*************************************************************************
【函数名称】       ExportModel
【函数功能】       打开与从库中导出模型相关的菜单
【参数】           无
【返回值】         无
【开发者及日期】   刘东琛 2024.8.15
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
void Viewer::ExportModel() {
    bool IsRunning = true;
    try {
        while (IsRunning) {
            //提供两种导出方式，使用下标导出指定model或者通过model名搜索导出
            cout << "Enter the a number to choose the way to get the model: " << endl
                << "1. by number " << endl
                << "2. by model name" << endl;
            int way = 0;
            if (!(cin >> way)) { // 检查读取是否成功
                // 如果读取失败，清除失败状态并忽略剩余的输入
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("invalid input for main menu");
            }
            if (way == 1) {
                cout << "input the number you want to export" << endl;
                int number = 0;
                cin >> number;
                cout << "Where do you want this model to be exported ? " << endl;
                cout << "input a path for export" << endl;
                string path;
                //输入前忽略上一次输入的换行符
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(cin, path);
                ShowResponse(m_Controller.ExportModel(number - 1, path));
            }
            else if (way == 2) {
                cout << "input the name of model you want to export" << endl;
                string ModelName;
                cin >> ModelName;
                string path;
                //输入前忽略上一次输入的换行符
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(cin, path);
                ShowResponse(m_Controller.ExportModel(ModelName, path));
            }
            else {
                throw std::exception("you have to choose a valid way");
            }

            cout << "Do you want to continue exporting ? (y/n)" << endl;
            cout << "y for continue, n for back to main menu. " << endl;
            char choice;
            if (!(cin >> choice)) { // 检查读取是否成功
                // 如果读取失败，清除失败状态并忽略剩余的输入
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("invalid input for main menu");
            }
            if (choice == 'n') {
                IsRunning = false;
            }
            //若输入y则循环继续
            else if (choice == 'y'){
                IsRunning = true;
            }
            //若输入非y非n则输入非法
            else if (choice != 'y') {
                throw std::invalid_argument("invalid input");
            }
        }
    }
    catch (std::exception e) {
        cout << e.what() << endl;
    }
}

/*************************************************************************
【函数名称】       Edit_or_ShowModel
【函数功能】       打开与操作库中模型相关的菜单
【参数】           无
【返回值】         无
【开发者及日期】   刘东琛 2024.8.15
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
void Viewer::Edit_or_ShowModel() {
    try {
        bool IsRunning = true;
        while (IsRunning) {
            //提供两种查找模型的方式，使用下标导出指定model或者通过model名搜索
            cout << "Enter the a number to choose the way to get the model: " << endl
                << "1. by number " << endl
                << "2. by model name " << endl
                <<"(enter 0 to back)" << endl;
            int way = 0;
            if (!(cin >> way)) { // 检查读取是否成功
                // 如果读取失败，清除失败状态并忽略剩余的输入
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("invalid input for main menu");
            }
            switch (way) {
                //通过序号来访问模型
                case 1 : {
                    cout << "input the number of the model you want to handle" << endl;
                    int number = 1;
                    cin >> number;
                    bool SecondIsRunning = true;
                    while (SecondIsRunning) {
                        Argument command = InputArgument();
                        if(command != Argument::Back) {
                            HandleArgument(number - 1, command);
                        }
                        else {
                            SecondIsRunning = false;
                        }
                    }
                    break;
                }
                //通过名称来搜索需要访问的模型
                case 2 : {
                    cout << "input the name of model you want to handle" << endl;
                    string ModelName;
                    cin >> ModelName;
                    //注意到修改名字后ModelIndex不变还可以通过下标访问到
                    unsigned int ModelIndex = m_Controller.FindModel(ModelName);
                    bool SecondIsRunning = true;
                    while (SecondIsRunning) {
                        Argument command = InputArgument();
                        if (command != Argument::Back) {
                            HandleArgument(ModelIndex, command);
                        }
                        else {
                            SecondIsRunning = false;
                        }
                    }
                    break;
                }
                case 0 : {
                    IsRunning = false;
                    break;
                }
                default :{
                    throw std::exception("you have to choose a valid way");
                }
            }
        }
    }
    catch (std::exception e) {
        cout << e.what() << endl;
    }
}

/*************************************************************************
【函数名称】       HandleArgument
【函数功能】       将用户输入的指定传递给controller并返回处理结果
【参数】           处理的模型的下标，用户输入的Argument
【返回值】         无
【开发者及日期】   刘东琛 2024.8.15
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
void Viewer::HandleArgument(unsigned int ModelIndex , Argument UserArguments) {
    //根据不同用户命令跳转到不同代码块
    //处理了所有的编辑和显示需求，该函数略长一些
    switch (UserArguments) {
        //更改模型名
        case Argument::ChangeName : {
            cout << "input NewName" << endl;
            string NewName;
            cin >> NewName;
            ShowResponse(m_Controller.ChangeName(ModelIndex, NewName));
            break;
            //模型名理论上都是合法的，不抛出错误
        }
        //输入三个点来向模型中添加一个三角面
        case Argument::AddFaceByPoints : {
            cout << "input three points to add a face: " << endl
                << "the point form is like (x,y,z) with no sapce" << endl;
            //Viewer只获取文本形式输入的点
            vector<string> PointString(3, " ");
            cout << "PointA : ";
            cin >> PointString[0];
            cout << "PointB : ";
            cin >> PointString[1];
            cout << "PointC : ";
            cin >> PointString[2];
            ShowResponse(m_Controller.AddFaceByPoints(ModelIndex, PointString));
            break;
        }
        //移除指定序号的面
        case Argument::RemoveFace : {
            cout << "input the number of the face you want to remove: " << endl;
            int number = 0;
            cin >> number;
            ShowResponse(m_Controller.RemoveFace(ModelIndex, number));
            break;
        }
        //显示模型中所有的面的所有点信息
        case Argument::ShowAllFace : {
            ShowResponse(m_Controller.ShowAllFace(ModelIndex));
            break;
        }

        case Argument::ShowFace : {
            cout << "input the number of face you want to show: " << endl;
            int number = 0;
            cin >> number;
            ShowResponse(m_Controller.ShowFace(ModelIndex, number));
            break;
        }

        //指定更改某一个序号面的指定点
        case Argument::ChangePointOfFace : {
            cout << "input the number of face you want to change: " << endl;
            int number = 0;
            cin >> number;
            cout << "input point name(pA or pB or pC) you want to change: " << endl;
            string PointName;
            cin >> PointName;
            //Viewer只获取文本形式输入的点
            cout << "input a new point(form as (x,y,z) with no sapce) to change: " << endl;
            string NewPointString;
            cin >> NewPointString;
            ShowResponse(m_Controller.ChangePointOfFace(ModelIndex, number, PointName, NewPointString));
            break;
        }
         //输入两个点来向模型中添加一条线段
        case Argument::AddLineByPoints : {
            cout << "input two points to add a line: " << endl
                << "the point form is like (x,y,z) with no sapce" << endl;
            vector<string> PointString(2," ");
            //Viewer只获取文本形式输入的点
            cout << "PointA : ";
            cin >> PointString[0];
            cout << "PointB : ";
            cin >> PointString[1];
            ShowResponse(m_Controller.AddLineByPoints(ModelIndex, PointString));
            break;
        }

        //移除某一指定序号的线段
        case Argument::RemoveLine : {
            cout << "input the number of the line you want to remove: " << endl;
            int number = 0;
            cin >> number;
            ShowResponse(m_Controller.RemoveFace(ModelIndex, number));
            break;
        }

        //显示模型中所有的线的所有点的信息
        case Argument::ShowAllLine : {
            ShowResponse(m_Controller.ShowAllLine(ModelIndex));
            break;
        }
        //显示某一个指定序号的线段
        case Argument::ShowLine : {
            cout << "input the number of line you want to show: " << endl;
            int number = 0;
            cin >> number;
            ShowResponse(m_Controller.ShowLine(ModelIndex, number));
            break;
        }
        //更改指定某一序号的线段的指定点
        case Argument::ChangePointOfLine : {
            cout << "input the number of line you want to change: " << endl;
            int number = 0;
            cin >> number;
            cout << "input point name ( pA or pB ) you want to change: " << endl;
            string PointName;
            cin >> PointName;
            cout << "input a new point(form as (x, y, z) with no sapce) to change: " << endl;
            //Viewer只获取文本形式输入的点
            string NewPointString;
            cin >> NewPointString;
            ShowResponse(m_Controller.ChangePointOfLine(ModelIndex, number, PointName, NewPointString));
            break;
        }
        //显示所有相关信息
        case Argument::DisplayStastics : {
            ShowResponse(m_Controller.DisPlaySatatics(ModelIndex));
            break;
        }
        default:
            throw std::invalid_argument("None Argument");
            break;
    }
}
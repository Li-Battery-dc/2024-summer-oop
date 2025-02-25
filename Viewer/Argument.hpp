/*************************************************************************
【文件名】                 Argument.hpp
【功能模块和目的】         处理输入信息的枚举类
【开发者及日期】           刘东琛 2024.8.14
【更改记录】               （若修改过则必需注明）
*************************************************************************/
#ifndef Argument_hpp
#define Argument_hpp
/*************************************************************************
【类名】             Argument
【功能】             处理用户输入的信息
【接口说明】         枚举类名称对应操作
【开发者及日期】     刘东琛 2024.8.14
【更改记录】         （若修改过则必需注明）
*************************************************************************/
enum class Argument {
    None = 0,
    ChangeName,

    AddFaceByPoints,
    RemoveFace,
    ShowAllFace,
    ShowFace,
    ChangePointOfFace,

    AddLineByPoints,
    RemoveLine,
    ShowAllLine,
    ShowLine,
    ChangePointOfLine,

    DisplayStastics,
    Back
};
#endif
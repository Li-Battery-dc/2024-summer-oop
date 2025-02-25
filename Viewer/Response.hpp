/*************************************************************************
【文件名】                 Response.hpp
【功能模块和目的】         返回信息的枚举类
【开发者及日期】           刘东琛 2024.8.14
【更改记录】               （若修改过则必需注明）
*************************************************************************/
#ifndef Response_hpp
#define Response_hpp
/*************************************************************************
【类名】             Response
【功能】             处理每次操作后返回给Viewer的信息
【接口说明】         结果枚举类代表操作结果
【开发者及日期】     刘东琛 2024.8.14
【更改记录】         （若修改过则必需注明）
*************************************************************************/
enum class Response {
    None = 0,
    Invalid_input,
    Successfully_Import,
    Failed_to_Import,
    Sucessfully_Export,
    Failed_to_Export,

    Sucessfully_create,
    Failed_to_create,
    Sucessfully_change_name,

    Sucessfully_add_face,
    Sucessfully_remove_face,
    Sucessfully_change_face,

    Sucessfully_add_line,
    Sucessfully_remove_line,
    Sucessfully_change_line,
    
    Failed_to_edit,
    Finished_show,
};
#endif
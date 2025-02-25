/*************************************************************************
【文件名】                 Viewer.hpp
【功能模块和目的】         建立程序的界面类
【开发者及日期】           刘东琛 2024.8.15
【更改记录】               （若修改过则必需注明）
*************************************************************************/
#ifndef Viewer_hpp
#define Viewer_hpp

#include "../Controller/Controller.hpp"
#include "Argument.hpp"
#include "Response.hpp"

/*************************************************************************
【类名】             Viewer
【功能】             作为程序的界面类
【接口说明】         
    Viewer(Controller& con = Controller::GetInstance())
    构造函数，在构造时传入 Controller 的实例，默认使用 Controller 的单例实例。

    Viewer(const Viewer& Source)
    拷贝构造函数，用于复制另一个 Viewer 对象的所有属性。

    virtual ~Viewer()
    虚析构函数，保证派生类正确释放资源。

    Viewer& operator=(const Viewer& Source)
    赋值运算符，用于复制另一个 Viewer 对象的所有属性。

    void Start()
    主菜单的入口函数，启动视图并显示菜单，等待用户输入。

【开发者及日期】     刘东琛 2024.8.15
【更改记录】         （若修改过则必需注明）
*************************************************************************/
class Viewer{
public:
    //显示给出类相关函数方便后续更改
    Viewer(Controller& con = Controller::GetInstance());   //构造时给出静态的controller
    Viewer(const Viewer& Source);
    virtual ~Viewer();
    Viewer& operator=(const Viewer& Source);

    //主菜单的入口
    void Start();

private:
    //传入Controller的单例引用
    Controller& m_Controller;

    //不同层级的展示菜单
    //设为private只能通过主菜单访问到
    //次级菜单函数
    void AddModel(); 
    void ExportModel();
    void Edit_or_ShowModel();

    //获取用户输入
    Argument InputArgument() const;
    //处理用户输入
    void HandleArgument(unsigned int ModelIndex , Argument UserArguments);

    //接收Controller的返回值并输出
    void ShowResponse(Response res) const;

};
#endif
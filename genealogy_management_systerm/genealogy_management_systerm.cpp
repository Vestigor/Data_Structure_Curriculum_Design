/***********************************************************
* File:     genealogy_management_system.cpp
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: Expression conversion and genealogy management
* Date:     2024.11.5
* Update:   2024.11.5
***********************************************************/
#include <iostream>
#include "my_binary_tree.h"
#include "my_string.h"

/***********************************************************
* Function Name:   ClearBuffer
* Function:        清除输入缓冲区，避免输入错误导致的阻塞
***********************************************************/
void ClearBuffer() {
    std::cin.clear();
    std::cin.ignore(2147483647,'\n');
}

/***********************************************************
* Function Name:   PrintChild
* Function:        打印指定成员的第一代子孙信息
* Input Parameter: genealogy - 家谱树对象
*                  parent - 父节点的名称
*                  current - 当前节点指针
***********************************************************/
void PrintChild(BinaryTree<mine::String>& genealogy,const mine::String& parent,BinTreeNode<mine::String>* current) {
    std::cout<<parent<<"的第一代子孙为：\n";
    current=genealogy.LeftChild(current);
    bool first=true;
    while(current!=nullptr) {
        if(!first)
            std::cout<<" ";
        std::cout<<genealogy.Data(current);// 打印子节点数据
        current=genealogy.RightChild(current); // 遍历右兄弟节点
        first=false;
    }
    std::cout<<"\n\n";
}

/***********************************************************
* Function Name:   MyBuild
* Function:        初始化家谱，创建祖先节点
* Input Parameter: genealogy - 家谱树对象
***********************************************************/
void MyBuild(BinaryTree< mine::String>& genealogy) {
    while(true) {
        std::cout<<"首先建立一个家谱！\n";
        std::cout<<"请输入祖先的姓名：";
        mine::String name;
        std::cin>>name;
        if(genealogy.rootInsert(name))
            std::cout<<"家谱管理系统建立成功！\n此族谱的祖先为："<<name<<"\n\n";
        else {
            std::cout<<"家谱管理系统建立失败,请重新建立！\n\n";
            continue;
        }
        break;
    }
}

/***********************************************************
* Function Name:   MySelect
* Function:        获取用户选择的操作选项
* Returned Value:  用户输入的合法操作选项
***********************************************************/
char MySelect() {

    char ch;
    while(true) {
        std::cout<<"请选择要执行的操作：";
        std::cin>>ch;
        if(ch<'A'||ch>'E') {
            std::cout<<"输入非法，请重新输入！\n";
            ClearBuffer();
            continue;;
        }
        ClearBuffer();
        break;
    }
    return ch;
}

/***********************************************************
* Function Name:   MyComplete
* Function:        为指定成员添加子女信息
* Input Parameter: genealogy - 家谱树对象
***********************************************************/
void MyComplete(BinaryTree< mine::String>& genealogy) {
    std::cout<<"请输入要建立家庭的人的姓名：";
    mine::String parent;
    std::cin>>parent;
    BinTreeNode< mine::String>* root=genealogy.GetRoot();
    BinTreeNode< mine::String>* current=genealogy.Search(parent,root);
    if(current==nullptr) {
        std::cout<<"未查找到该成员！\n\n";
        return;
    }
    if(genealogy.LeftChild(current)) {
        std::cout<<"该成员已存在家庭，只能添加家庭成员或者解散局部家庭！\n";
        return;
    }

    double n;
    while(true) {
        std::cout<<"请输入"<<parent<<"的儿女的人数：";
        std::cin>>n;
        if(std::cin.fail()||n!=static_cast<int>(n)||n<=0) {
            std::cout<<"输入非法，请重新输入！\n";
            ClearBuffer();
            continue;;
        }
        break;
    }
    int number = static_cast<int>(n);
    BinTreeNode< mine::String>* temp=current;
    std::cout<<"请依次输入"<<parent<<"的儿女的姓名：\n";
    for(int i=0;i<number;i++) {
        mine::String child;
        std::cin>>child;
        if(genealogy.Search(child,root)) {
            std::cout<<"族谱中的名字不能重复！请重新输入。\n";
            i-=1;
            continue;
        }
        if(i==0) {
            genealogy.leftInsert(temp,child);// 插入第一个子节点
            temp=genealogy.LeftChild(temp);
        }
        else {
            genealogy.rightInsert(temp,child);// 插入右兄弟节点
            temp=genealogy.RightChild(temp);
        }
    }
    PrintChild(genealogy,parent,current);// 打印子女信息
}

/***********************************************************
* Function Name:   MyAdd
* Function:        为指定成员添加一个子女
* Input Parameter: genealogy - 家谱树对象
***********************************************************/
void MyAdd(BinaryTree< mine::String>& genealogy) {
    std::cout<<"请输入要添加儿子（或女儿）的人的姓名：";
    mine::String parent;
    std::cin>>parent;
    BinTreeNode< mine::String>* root=genealogy.GetRoot();
    BinTreeNode< mine::String>* current=genealogy.Search(parent,root);
    if(current==nullptr) {
        std::cout<<"未查找到该成员！\n\n";
        ClearBuffer();
        return;
    }
    std::cout<<"请输入"<<parent<<"新添加的儿子（或女儿）的姓名：\n";
    mine::String child;
    while(true) {
        std::cin>>child;
        if(genealogy.Search(child,root)) {
            std::cout<<"族谱中的名字不能重复！请重新输入。\n";
            continue;
        }
        break;
    }
    BinTreeNode<mine::String>* temp=current;
    if(genealogy.LeftChild(temp)==nullptr)
        genealogy.leftInsert(temp,child);// 插入第一个子节点
    else {
        temp=genealogy.LeftChild(temp);
        while(genealogy.RightChild(temp)!=nullptr)
            temp=genealogy.RightChild(temp);// 遍历到最后一个右兄弟
        genealogy.rightInsert(temp,child); // 插入右兄弟
    }

    PrintChild(genealogy,parent,current);// 打印子女信息
}

/***********************************************************
* Function Name:   MyDissolve
* Function:        解散指定成员的一个家庭
* Input Parameter: genealogy - 家谱树对象
***********************************************************/
void MyDissolve(BinaryTree<mine::String>& genealogy) {
    std::cout << "请输入要解散家庭的人的姓名：";
    mine::String parent;
    std::cin >> parent;

    BinTreeNode<mine::String>* root = genealogy.GetRoot();
    BinTreeNode<mine::String>* current = genealogy.Search(parent, root);

    if (current == nullptr) {
        std::cout << "未查找到该成员！\n\n";
        ClearBuffer();
        return;
    }

    if (genealogy.LeftChild(current) == nullptr) {
        std::cout << "该成员不存在后代！\n\n";
        return;
    }

    std::cout << "要解散的家庭的人是：";
    mine::String son;
    std::cin >> son;

    BinTreeNode<mine::String>* temp = current;
    bool found = false;

    // 检查左子节点是否为待删除的子节点
    if (genealogy.Data(genealogy.LeftChild(temp)) == son) {
        BinTreeNode<mine::String>* to_del = genealogy.LeftChild(temp);
        genealogy.ChangeLeftChild(temp, genealogy.RightChild(to_del));
        genealogy.ChangeRightChild(to_del, nullptr);// 更新左子节点
        genealogy.Destory(to_del);// 释放节点
        found = true;
    }
    else {
        // 遍历右兄弟节点寻找匹配的子节点
        temp = genealogy.LeftChild(temp);
        while (genealogy.RightChild(temp) != nullptr) {
            if (genealogy.Data(genealogy.RightChild(temp)) == son) {
                BinTreeNode<mine::String>* to_del = genealogy.RightChild(temp);
                genealogy.ChangeRightChild(temp, genealogy.RightChild(to_del));// 更新右兄弟指针
                genealogy.ChangeRightChild(to_del, nullptr);
                genealogy.Destory(to_del);// 释放节点
                found = true;
                break;
            }
            temp = genealogy.RightChild(temp);
        }
    }

    if (!found) {
        std::cout<<"未找到需要解散家庭的人!\n\n";
        return;
    }
    PrintChild(genealogy,parent,current);// 打印剩余子女
}

/***********************************************************
* Function Name:   MyModify
* Function:        修改指定成员的姓名
* Input Parameter: genealogy - 家谱树对象
***********************************************************/
void MyModify(BinaryTree< mine::String>& genealogy) {
    std::cout<<"请输入要更改姓名的人的目前姓名：";
    mine::String name;
    std::cin>>name;

    // 获取家谱的根节点，并搜索对应姓名的节点
    BinTreeNode< mine::String>* root=genealogy.GetRoot();
    BinTreeNode< mine::String>* current=genealogy.Search(name,root);
    // 检查是否找到目标成员
    if(current==nullptr) {
        std::cout<<"未查找到该成员！\n\n";
        ClearBuffer();
        return;
    }
    std::cout<<"请输入修改后的姓名：";
    mine::String new_name;
    // 确保新姓名在族谱中没有重复
    while (true) {
        std::cin >> new_name;
        if(new_name==name) {
            std::cout<<"新名字不能与旧名字相同，请重新输入！\n";
            continue;
        }
        if (genealogy.Search(new_name, root)) {
            std::cout << "族谱中的名字不能重复，请重新输入！\n";
            continue;
        }
        break;
    }

    current->data=new_name;

    // 显示修改结果
    std::cout<<name<<"已更名为"<<new_name<<"\n\n";
}

/***********************************************************
* Function Name:   GenealogyManagementSystem
* Function:        启动家谱管理系统，提供用户操作界面
***********************************************************/
void GenealogyManagementSystem() {
    std::cout<<"+------------------------------------------+\n";
    std::cout<<"|               家谱管理系统               |\n";
    std::cout<<"|       Genealogy Management System        |\n";
    std::cout<<"+------------------------------------------+\n";

    // 创建家谱对象并初始化
    BinaryTree<mine::String> genealogy;
    MyBuild(genealogy);
    std::cout<<"+------------------------------------+\n";
    std::cout<<"|           操作类型                 |\n";
    std::cout<<"|        A --- 完善家谱              |\n";
    std::cout<<"|        B --- 添加家庭成员          |\n";
    std::cout<<"|        C --- 解散局部家庭          |\n";
    std::cout<<"|        D --- 更改家庭成员姓名      |\n";
    std::cout<<"|        E --- 退出程序员            |\n";
    std::cout<<"+------------------------------------+\n";

    // 开始循环接受用户指令
    while(true) {
        char select=MySelect();

        // 根据选择执行对应的功能
        if(select=='A')
            MyComplete(genealogy);
        else if(select=='B')
            MyAdd(genealogy);
        else if(select=='C')
            MyDissolve(genealogy);
        else if(select=='D')
            MyModify(genealogy);
        else
            break;
    }
    std::cout<<"\n成功退出家谱管理系统！\n";
}

/***********************************************************
* Function Name:   main
* Function:        程序入口
* Returned Value:  0
***********************************************************/
int main()
{
    GenealogyManagementSystem();

    return 0;
}
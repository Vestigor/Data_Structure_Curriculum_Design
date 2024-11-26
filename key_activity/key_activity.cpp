/***********************************************************
* File:     key_ctivity.cpp
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Function: Key Activity
* Encoding: UTF-8
* Date:     2024.11.24
* Update:   2024.11.24
***********************************************************/
#include <iostream>
#include <cassert>
#include "my_critical_path.h"

/***********************************************************
* Function Name:   Clear
* Function:        清理输入缓冲区，重置输入状态
* Input Parameter: 无
* Returned Value:  无
***********************************************************/
void Clear()
{
    std::cin.clear();
    std::cin.ignore(1000000000, '\n');
}

/***********************************************************
* Function Name:   Input1
* Function:        提示用户输入一个整数，并进行有效性校验
* Input Parameter: ret - 是否需要校验输入范围 [2-100]
*                  prompt - 提示信息
* Returned Value:  用户输入的整数
***********************************************************/
int Input1(const bool ret,const char* prompt)
{
    double temp;
    while (true) {
        std::cout << prompt;
        std::cin >> temp;
        if (std::cin.fail() ||temp != static_cast<int>(temp)||ret&& (temp <= 1 || temp > 100)||temp<=0) {
            std::cout << "输入非法，请重新输入！\n";
            Clear();
            continue;
        }
        Clear();
        break;
    }
    return static_cast<int>(temp);
}

/***********************************************************
* Function Name:   Input2
* Function:        从用户输入中任务开始和完成的交接点编号以
*                  及完成该任务所需要的时间
* Input Parameter: N - 图的顶点数，用于校验输入范围
*                  row - 当前输入的行号，用于错误提示
*                  src - 任务的起始点编号（输出参数）
*                  dst - 任务的结束点编号（输出参数）
*                  value - 任务的权重（输出参数）
* Returned Value:  无
***********************************************************/
void Input2(const int N,int row,int&src,int&dst,int& value)
{
    double temp[3];
    for (int i=0;i<3;i++) {
        std::cin >> temp[i];
        if (std::cin.fail() || temp[i] <= 0 || temp[i] != static_cast<int>(temp[i]) || i != 2 && temp[i] > N) {
            std::cout << "第" << row + 1 << "行输入错误，请从第" << row + 1 << "行开始重新输入！\n";
            Clear();
            i=-1;
        }
    }
    src = static_cast<int>(temp[0]);
    dst=static_cast<int>(temp[1]);
    value=static_cast<int>(temp[2]);
}

/***********************************************************
* Function Name:   KeyActivity
* Function:        实现关键活动算法的主流程
* Input Parameter: 无
* Returned Value:  无
***********************************************************/
void KeyActivity()
{
    std::cout << "+---------------------------+\n";
    std::cout << "|         关键活动          |\n";
    std::cout << "|       Key Activity        |\n";
    std::cout << "+---------------------------+\n";

    // 获取任务交接点数目
    const int N = Input1(true, "请输入任务交接点数目[2-100]:\n");
    // 获取任务数量
    const int M = Input1(false, "请输入任务数量:\n");

    Graph graph(N);

    bool **have_visited = new(std::nothrow) bool *[N+1];
    assert(have_visited);
    for (int i=0;i<N+1;i++) {
        have_visited[i]=new bool[N+1];
        assert(have_visited[i]);
    }

    for (int i=0;i<N+1;i++) {
        for (int j=0;j<N+1;j++) {
            have_visited[i][j]=false;
        }
    }

    std::cout<<"请输入任务开始和完成设计的交接点编号以及完成该任务所需要的时间：\n";
    for(int i = 0 ; i < M ; i++) {
        int src,dst,value;
        Input2(N,i ,src,dst, value);
        if (have_visited[src][dst]) {
            std::cout<<"任务调度点"<<src<<"与"<<dst<<"之间已经有任务！\n";
            i--;
            continue;
        }
        have_visited[src][dst]=true;
        graph.AddEdge(src,dst,value);
    }

    // 计算并获取关键路径结果
    CriticalPath result=graph.FindCriticalPath();

    std::cout << "关键路径总花费: ";
    if(!result.success) {
        std::cout<<'0'<<" \n";
        return;
    }
    std::cout<<result.total_cost << "\n";

    for (Path *path = result.paths; path!= nullptr; path = path->next)
        std::cout << path->start << "->" << path->end << "\n";

    for (int i=0;i<N+1;i++) {
        delete[] have_visited[i];
    }
    delete [] have_visited;
}

int main()
{
    KeyActivity();

    return 0;
}

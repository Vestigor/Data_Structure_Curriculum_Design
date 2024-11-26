/***********************************************************
* File:     power_grid_construction_cost_simulation_system.cpp
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Clion2024
* Function: Power Grid Construction Cost Simulation System
* Date:     2024.11.23
* Update:   2024.11.23
***********************************************************/
#include <iostream>
#include "my_graph_mst.h"
#include "my_string.h"
#include "my_hash.h"

/***********************************************************
* Function Name:   ClearBuffer
* Function:        清理输入缓冲区，重置输入状态
* Input Parameter: 无
* Returned Value:  无
***********************************************************/
void ClearBuffer()
{
    std::cin.clear();
    std::cin.ignore(2147483647, '\n');
}

/***********************************************************
* Function Name:   Select
* Function:        提供操作选择菜单，并获取用户选择的操作
* Input Parameter: 无
* Returned Value:  用户选择的字符
***********************************************************/
char Select()
{
    char ch;
    while (true) {
        std::cout << "\n请选择要执行的操作：";
        std::cin >> ch;
        if (ch < 'A' || ch > 'E') {
            std::cout << "输入非法，请重新输入！\n";
            ClearBuffer();
            continue;;
        }
        ClearBuffer();
        break;
    }
    return ch;
}

/***********************************************************
* Function Name:   CreateVertex
* Function:        创建电网的顶点集合
* Input Parameter: graph - 电网图的引用
*                  n - 用于存储顶点个数的变量
*                  vertexes - 用于存储顶点名称的字符串
*                  have_vertex - 是否已创建顶点的标志
*                  have_edge - 是否已添加边的标志
*                  have_prim - 是否已构建最小生成树的标志
* Returned Value:  无
***********************************************************/
void CreateVertex(Graph<mine::String>& graph,int &n,Hash<int, mine::String>& index_vertexes,Hash<mine::String,int> &vertexes_index, bool& have_vertex,bool& have_edge,bool& have_prim)
{
    have_prim =have_edge =have_vertex = false;
    index_vertexes.make_empty();
    vertexes_index.make_empty();

    double n_temp;
    while(true) {
        std::cout << "请输入顶点个数(至少为2个)：";
        std::cin>>n_temp;
        if(std::cin.fail()||n_temp!=static_cast<int>(n_temp)||n_temp<2) {
            std::cout << "输入非法，请重新输入！\n";
            ClearBuffer();
            continue;;
        }
        ClearBuffer();
        break;
    }

    n=static_cast<int>(n_temp);

    graph.Initial(n);//初始化图

    std::cout<<"请依次输入个顶点的名称：\n";
    for(int i=0;i<n;i++) {
        mine::String str;
        std::cin >> str;
        index_vertexes[i] = str;
        vertexes_index[str] =i;
        graph.SetDot(str);
    }
    ClearBuffer();
    have_vertex=true;

}

/***********************************************************
* Function Name:   AddEdge
* Function:        为电网添加边的权重
* Input Parameter: graph - 电网图的引用
*                  n - 顶点个数
*                  vertexes - 顶点名称集合
*                  have_vertex - 是否已创建顶点的标志
*                  have_edge - 是否已添加边的标志
*                  have_prim - 是否已构建最小生成树的标志
* Returned Value:  无
***********************************************************/
void AddEdge(Graph<mine::String> &graph, const int &n, Hash<mine::String, int> &
             vertexes_index, const bool &have_vertex, bool &have_edge, bool &have_prim)
{
    if (!have_vertex) {
        std::cout << "没有顶点，无法添加边！\n";
        return;
    }
    have_prim = have_edge = false;

    graph.InitialEdgeValue();
    bool **has_set = new(std::nothrow) bool *[n];
    assert(has_set!=nullptr);
    for (int i = 0; i < n; i++) {
        has_set[i] = new(std::nothrow) bool[n];
        assert(has_set[i]!=nullptr);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            has_set[i][j] = false;
        }
    }

    std::cout << "请确保输入的顶点已经在电网中，且边的权值在( 0~" << INF << " )范围内。\n";
    while (true) {
        std::cout << "请输入两个顶点及边(输入三个-1时结束输入)：";
        mine::String start, end;
        double edge_value;
        std::cin >> start >> end >> edge_value;
        if (start == "-1" && end == "-1" && edge_value == -1) {
            ClearBuffer();
            break;
        }

        if (vertexes_index.find(start) == nullptr) {
            std::cout << "第一个顶点不在顶点集合之中!\n";
            ClearBuffer();
            continue;
        }
        if (vertexes_index.find(end) == nullptr) {
            std::cout << "第二个顶点不在顶点集合之中!\n";
            ClearBuffer();
            continue;
        }
        if (start==end) {
            std::cout << "两个顶点不能相同!\n";
            ClearBuffer();
            continue;
        }
        if (std::cin.fail() || edge_value <= 0 || edge_value >= INF) {
            std::cout << "边输入非法！\n";
            ClearBuffer();
            continue;
        }
        graph.SetEdgeValue(start, end, edge_value);
        if (has_set[vertexes_index[start]][vertexes_index[end]]) {
            std::cout << "已更新" << start << "与" << end << "之间的边！\n";
        }
        has_set[vertexes_index[start]][vertexes_index[end]] = true;
        has_set[vertexes_index[end]][vertexes_index[start]] = true;
    }

    have_edge = true;

    for (int i = 0; i < n; i++) {
        delete has_set[i];
    }
    delete has_set;
}

/***********************************************************
* Function Name:   ConstructMST
* Function:        构建电网的最小生成树
* Input Parameter: graph - 电网图的引用
*                  n - 顶点个数
*                  vertexes - 顶点名称集合
*                  have_edge - 是否已添加边的标志
*                  have_prim - 是否已构建最小生成树的标志
* Returned Value:  无
***********************************************************/
void ConstructMST(Graph<mine::String> &graph,const int &n, Hash<mine::String,
                      int> &vertexes_index, const bool &have_edge,bool &have_prim)
{
    if(!have_edge) {
        std::cout<<"没有添加边，无法构造最小生成树！\n";
        return;
    }
    graph.MTSInitial();
    have_prim=false;
    mine::String start;
    while(true) {
        std::cout << "请输入起始顶点：";
        std::cin >> start;
        if(vertexes_index.find(start) == nullptr) {
            std::cout<<"未在顶点集合中找到 "<<start<<" !\n";
            ClearBuffer();
            continue;
        }
        break;
    }

    if(!graph.Prim(start)) {
        std::cout<<"构建最小生成树失败，请检查图是否连通！\n";
        return;
    }
    have_prim=true;
    std::cout<<"成功构建最小生成树！\n";
}

/***********************************************************
* Function Name:   DisplayMST
* Function:        显示最小生成树的顶点及边
* Input Parameter: graph - 电网图的引用
*                  have_prim - 是否已构建最小生成树的标志
* Returned Value:  无
***********************************************************/
void DisplayMST(const Graph<mine::String>& graph, const bool &have_prim)
{
    if(!have_prim) {
        std::cout<<"未构建最小生成树！\n";
        return;
    }
    std::cout<<"最小生成树顶点及边为：\n";
    graph.DisplayMST();
}


/***********************************************************
* Function Name:   PowerGridConstructionCostSimulationSystem
* Function:        模拟电网建设造价系统的主功能
* Input Parameter: 无
* Returned Value:  无
***********************************************************/
void PowerGridConstructionCostSimulationSystem()
{
    std::cout << "+-----------------------------------------------------+\n";
    std::cout << "|                电网建设造价模拟系统                 |\n";
    std::cout << "|   Power Grid Construction Cost Simulation System    |\n";
    std::cout << "+-----------------------------------------------------+\n";
    std::cout << "|                                                     |\n";
    std::cout << "+-----------------------------------------------------+\n";
    std::cout << "|                       操作类型                      |\n";
    std::cout << "|                A --- 创建电网顶点                   |\n";
    std::cout << "|                B --- 添加电网的边                   |\n";
    std::cout << "|                C --- 构建最小生成树                 |\n";
    std::cout << "|                D --- 显示最小生成树                 |\n";
    std::cout << "|                E --- 退出程序                       |\n";
    std::cout << "+-----------------------------------------------------+\n";
    Graph<mine::String> graph;
    bool have_vertex = false,have_edge=false,have_prim=false;
    Hash<int,mine::String> index_vertexes;
    Hash<mine::String,int> vertexes_index;
    int n;
    while(true) {
        char selection=Select();
        if(selection=='A')
            CreateVertex(graph,n,index_vertexes, vertexes_index,have_vertex,have_edge,have_prim);
        else if(selection=='B')
            AddEdge(graph, n,  vertexes_index, have_vertex, have_edge, have_prim);
        else if(selection=='C')
            ConstructMST(graph,n, vertexes_index,have_edge, have_prim);
        else if(selection=='D')
            DisplayMST(graph,have_prim);
        else
            break;
    }

    std::cout<<"成功退出电网建设造价模拟系统！\n";
}

/***********************************************************
* Function Name:   main
* Function:        程序入口，启动电网建设造价模拟系统
* Input Parameter: 无
* Returned Value:  程序执行状态（0表示正常）
***********************************************************/
int main()
{
    PowerGridConstructionCostSimulationSystem();

    return 0;
}
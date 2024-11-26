#ifndef MY_CRITICAL_PATH_H
#define MY_CRITICAL_PATH_H
/***********************************************************
* File:     my_critical_path.cpp
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Function:  Critical Path Method Implementation
* Encoding: UTF-8
* Date:     2024.11.24
* Update:   2024.11.24
***********************************************************/
#include <cassert>
#include <cstring>
#include <iostream>

/***********************************************************
* Structure Name:   Path
* Function:         用于表示路径结构，每条路径包含一个起点和终点
***********************************************************/
struct Path {
    int start; // 起点
    int end; // 终点
    Path *next;
    Path(int s = -1, int e = -1) : start(s), end(e) { next = nullptr; }
};

/***********************************************************
* Structure Name:   Edge
* Function:         表示图中的边，包含目标顶点、边的权重和指向下一条边的指针
***********************************************************/
struct Edge {
    int to; // 终点
    int weight; // 权重
    Edge *next; // 指向下一条边（链表形式）
    Edge(int t, int w, Edge *n = nullptr): to(t), weight(w), next(n) {}
};

/***********************************************************
* Class Name:   CriticalPath
* Function:     用于表示关键路径，包含路径和相关的项目数据
***********************************************************/
class CriticalPath {
public:
    bool success; // 是否生成成功
    Path *paths; // 存储关键路径的起点和终点对
    int path_count; // 关键路径对数量
    int total_cost; // 总花费

    CriticalPath(); // 构造函数
    CriticalPath(const CriticalPath &other); // 拷贝构造函数
    ~CriticalPath(); // 析构函数

    void CopyPaths(const Path *other_paths); // 深拷贝路径链表
    void ClearPaths(); // 清除所有路径节点
    void AddPath(int start, int end); // 添加路径
};

/***********************************************************
* Function Name:   CriticalPath
* Function:        构造函数，用于初始化关键路径对象
* Input Parameter: 无
* Returned Value:  无
***********************************************************/
inline CriticalPath::CriticalPath() : success(false), paths(nullptr), path_count(0), total_cost(0) {}


/***********************************************************
* Function Name:   CriticalPath
* Function:        拷贝构造函数，用于复制另一个关键路径对象
* Input Parameter: const CriticalPath& other - 需要复制的关键路径对象
* Returned Value:  无
***********************************************************/
inline CriticalPath::CriticalPath(const CriticalPath &other)
    : success(other.success), paths(nullptr), path_count(other.path_count), total_cost(other.total_cost)
{
    CopyPaths(other.paths); // 复制路径链表
}

/***********************************************************
* Function Name:   ~CriticalPath
* Function:        析构函数，用于清理内存，删除路径链表
* Input Parameter: 无
* Returned Value:  无
***********************************************************/
inline CriticalPath::~CriticalPath()
{
    ClearPaths();
}

/***********************************************************
* Function Name:   CopyPaths
* Function:        深拷贝路径链表，复制路径数据
* Input Parameter: const Path* other_paths - 需要复制的路径链表
* Returned Value:  无
***********************************************************/
inline void CriticalPath::CopyPaths(const Path *other_paths)
{
    if (!other_paths) return;// 如果路径为空，则无需复制
    paths = new(std::nothrow) Path(other_paths->start, other_paths->end);
    assert(paths != nullptr);

    Path *current = paths;
    const Path *other_current = other_paths->next;

    // 逐个复制链表中的每个路径节点
    while (other_current) {
        current->next = new(std::nothrow) Path(other_current->start, other_current->end);
        assert(current->next != nullptr);

        current = current->next;
        other_current = other_current->next;
    }
}

/***********************************************************
* Function Name:   ClearPaths
* Function:        清除路径链表，释放内存
* Input Parameter: 无
* Returned Value:  无
***********************************************************/
inline void CriticalPath::ClearPaths()
{
    while (paths) {
        Path *temp = paths;
        paths = paths->next;
        delete temp;
    }
    path_count = 0;
}

/***********************************************************
* Function Name:   AddPath
* Function:        向路径链表中添加一条路径
* Input Parameter: int start - 起点
*                  int end - 终点
* Returned Value:  无
***********************************************************/
inline void CriticalPath::AddPath(int start, int end)
{
    // 如果路径链表为空，则创建新的头节点
    if (!paths) {
        paths = new(std::nothrow) Path(start, end);
        assert(paths != nullptr);
    }
    else {
        Path *current = paths;
        while (current->next) {
            current = current->next;
        }
        // 在链表末尾添加新的路径
        current->next = new(std::nothrow) Path(start, end);
        assert(current->next != nullptr);
    }
    path_count++;
}

/***********************************************************
* Class Name:   Graph
* Function:    表示有向图，包含顶点、边以及用于关键路径计算的数据
***********************************************************/
class Graph {
private:
    int vertices; // 顶点数
    Edge **adj_list; // 邻接表
    int *in_degree; // 每个顶点的入度
    int *earliest; // 最早开始时间
    int *latest; // 最晚开始时间
    int *topo_order; // 拓扑排序结果
    int top_count; // 当前拓扑排序顶点数量

public:
    Graph(const int v); // 构造函数
    ~Graph(); // 析构函数

    void AddEdge(int from, int to, int weight); // 添加边
    bool TopologicalSort(); // 拓扑排序
    CriticalPath FindCriticalPath(); // 计算关键路径
};

/***********************************************************
* Function Name:   Graph
* Function:        构造函数，用于初始化图的相关数据结构
* Input Parameter: int v - 顶点数
* Returned Value:  无
***********************************************************/
inline Graph::Graph(const int v) : vertices(v), top_count(0)
{
    adj_list = new(std::nothrow) Edge *[v];
    assert(adj_list != nullptr);
    in_degree = new(std::nothrow) int[v];
    assert(in_degree != nullptr);
    earliest = new(std::nothrow) int[v];
    assert(earliest != nullptr);
    latest = new(std::nothrow) int[v];
    assert(latest != nullptr);
    topo_order = new(std::nothrow) int[v];
    assert(topo_order != nullptr);

    memset(adj_list, 0, sizeof(Edge *) * v);
    memset(in_degree, 0, sizeof(int) * v);
    memset(earliest, 0, sizeof(int) * v);
    memset(latest, 0x3f, sizeof(int) * v);
}

/***********************************************************
* Function Name:   ~Graph
* Function:        析构函数，用于清理图的资源
* Input Parameter: 无
* Returned Value:  无
***********************************************************/
inline Graph::~Graph()
{
    // 删除图中的所有边
    for (int i = 0; i < vertices; i++) {
        Edge *edge = adj_list[i];
        while (edge != nullptr) {
            Edge *next = edge->next;
            delete edge;
            edge = next;
        }
    }
    delete[] adj_list;
    delete[] in_degree;
    delete[] earliest;
    delete[] latest;
    delete[] topo_order;
}

/***********************************************************
* Function Name:   AddEdge
* Function:        为图添加一条边
* Input Parameter: int from - 起点
*                  int to - 终点
*                  int weight - 权重
* Returned Value:  无
***********************************************************/
inline void Graph::AddEdge(int from, int to, int weight)
{
    adj_list[from - 1] = new(std::nothrow) Edge(to - 1, weight, adj_list[from - 1]);
    assert(adj_list[from - 1] != nullptr);
    in_degree[to - 1]++;// 增加终点的入度
}

/***********************************************************
* Function Name:   TopologicalSort
* Function:        执行拓扑排序
* Input Parameter: 无
* Returned Value:  bool - 是否成功完成拓扑排序
***********************************************************/
inline bool Graph::TopologicalSort()
{
    int *stack = new int[vertices];// 用于存储临时栈
    int top = -1;

    // 将所有入度为0的顶点放入栈中
    for (int i = 0; i < vertices; i++) {
        if (in_degree[i] == 0) {
            stack[++top] = i;
        }
    }

    // 进行拓扑排序
    while (top >= 0) {
        int curr = stack[top--];
        topo_order[top_count++] = curr;

        for (Edge *edge = adj_list[curr]; edge != nullptr; edge = edge->next) {
            int neighbor = edge->to;
            in_degree[neighbor]--;
            if (in_degree[neighbor] == 0)
                stack[++top] = neighbor;

            earliest[neighbor] = std::max(earliest[neighbor], earliest[curr] + edge->weight);
        }
    }

    delete[] stack;
    return top_count == vertices;// 判断是否所有顶点都被访问过
}

/***********************************************************
* Function Name:   FindCriticalPath
* Function:        查找并返回关键路径
* Input Parameter: 无
* Returned Value:  CriticalPath - 关键路径对象
***********************************************************/
inline CriticalPath Graph::FindCriticalPath()
{
    CriticalPath result;

    // 执行拓扑排序，若排序失败说明存在环路，不能继续计算关键路径
    if (!TopologicalSort()) {
        std::cout << "有向图中存在环路，构建拓扑排序失败！" << std::endl;
        return result; // 如果拓扑排序失败，返回空结果
    }

    // 初始化所有顶点的最晚开始时间为最大值
    memset(latest, 0x3f, sizeof(int) * vertices);

    // 将最后一个顶点的最晚开始时间设置为其最早开始时间（对称计算）
    latest[topo_order[top_count - 1]] = earliest[topo_order[top_count - 1]];
    result.total_cost = earliest[topo_order[top_count - 1]];

    // 反向遍历拓扑排序的顶点集合，计算最晚开始时间
    for (int i = top_count - 1; i >= 0; i--) {
        int curr = topo_order[i];
        for (Edge *edge = adj_list[curr]; edge != nullptr; edge = edge->next) {
            int neighbor = edge->to;
            latest[curr] = std::min(latest[curr], latest[neighbor] - edge->weight);
        }
    }

    for (int i = 0; i < vertices; i++) {
        for (Edge *edge = adj_list[i]; edge != nullptr; edge = edge->next) {
            int neighbor = edge->to;
            int e = earliest[i];
            int l = latest[neighbor] - edge->weight;
            // 如果最早开始时间和最晚开始时间相同，说明这条边是关键路径上的一部分
            if (e == l) {
                result.AddPath(i + 1, neighbor + 1);// 将关键路径添加到结果
            }
        }
    }

    if (result.paths != nullptr)//判断是否存在关键路径
        result.success = true;

    return result;// 返回包含关键路径的对象
}

#endif //MY_CRITICAL_PATH_H
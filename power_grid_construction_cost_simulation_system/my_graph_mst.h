#ifndef  MY_GRAPH_MST_H
#define MY_GRAPH_MST
/***********************************************************
* File:     my_graph_mst.cpp
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Function: Graph & MinSpanTree
* Encoding: UTF-8
* Date:     2024.11.23
* Update:   2024.11.23
***********************************************************/
#include <cassert>
#include <iostream>
#include "my_hash.h"

#define INF 1000000000

/***********************************************************
* Struct: MSTEdgeNode
* Function: 表示最小生成树中的一条边
***********************************************************/
template<typename T>
struct MSTEdgeNode {
    T tail,head;// 边的起点和终点
    double key;// 边的权重
    MSTEdgeNode():tail(T()), head(T()),key(0){}
    MSTEdgeNode(T src,T end,double key):tail(src),head(end),key(key){}
    // Comparison operators for edge weights
    bool operator<=(MSTEdgeNode<T>& R) const {return key<=R.key;}
    bool operator<(MSTEdgeNode<T>& R) const {return key<R.key;}
    bool operator==(MSTEdgeNode<T>& R) const {return key==R.key;}
    bool operator!=(MSTEdgeNode<T>& R) const {return key!=R.key;}
    bool operator>(MSTEdgeNode<T>& R) const {return key>R.key;}
    bool operator>=(MSTEdgeNode<T>& R) const {return key>=R.key;}
};

/***********************************************************
* Class:    MinSpanTree
* Function: 管理最小生成树的边集合。
***********************************************************/
template<typename  T>
class MinSpanTree {
    public:
    MinSpanTree(){maxSize= n=0;edge_value = nullptr; };
    MinSpanTree(int size);
    ~MinSpanTree(){delete[] edge_value;}
    void Initial(int size);
    void MakeEmpty();
    void Insert(const MSTEdgeNode<T>& item);
    void PrintEdges() const;
    bool BuildSuccess(){return n==maxSize;}
private:
    int maxSize,n;
    MSTEdgeNode<T>* edge_value;
};

/***********************************************************
* Function Name:     MinSpanTree
* Function:         构造函数，存储内存
* Input Parameter:
*                   size - 最小生成树可以存储的边数。
***********************************************************/
template<typename T>
MinSpanTree<T>::MinSpanTree(int size)
{
    maxSize = size - 1;
    n = 0;
    edge_value = new(std::nothrow) MSTEdgeNode<T>[size];
    assert(edge_value!=nullptr);
}

/***********************************************************
* Function Name:    Initial
* Function:        初始化最小生成树，设置边数组大小并分配内存。
* Input Parameter: size - 最小生成树可以存储的边数。
***********************************************************/
template<typename T>
void MinSpanTree<T>::Initial(int size)
{
    assert(maxSize==0);
    maxSize = size-1;
    n = 0;
    edge_value = new(std::nothrow) MSTEdgeNode<T>[size];
    assert(edge_value!=nullptr);
}

/***********************************************************
* Function Name: MakeEmpty
* Function:     清空最小生成树的边集合，并释放内存。
***********************************************************/
template<typename T>
void MinSpanTree<T>::MakeEmpty()
{
    if (edge_value!=nullptr) {
        delete[] edge_value;
        edge_value = nullptr;
    }
    maxSize= n = 0;
}

/***********************************************************
* Function Name:    Insert
* Function:         向最小生成树中插入一条边。
* Input Parameter:  item - 要插入的边。
***********************************************************/
template<typename T>
void MinSpanTree<T>::Insert(const MSTEdgeNode<T>& item)
{
    assert(n< maxSize);
    assert(edge_value!=nullptr);
    edge_value[n]= item;
    n++;
}

/***********************************************************
* Function Name:  PrintEdges
* Function:      打印最小生成树中所有边的详细信息。
***********************************************************/
template<typename T>
void MinSpanTree<T>::PrintEdges() const
{
    double total_cost=0;
    for(int i=0;i<n;i++) {
        std::cout << edge_value[i].tail << " --( " << edge_value[i].key << " )--> " << edge_value[i].head << "\n";
        total_cost+=edge_value[i].key;
    }
    std::cout << "最小生成树花费为："<<total_cost << "\n";

}

/***********************************************************
* Class:    Graph
* Function: 表示加权无向图，并提供构建最小生成树的功能。
***********************************************************/
template<typename T>
class Graph {
public:
    Graph(){size=n=0; edge_value=nullptr; dots=nullptr;}
    Graph(int sz);
    ~Graph(){MakeEmpty();}
    void Initial(int sz);
    void MakeEmpty();
    void SetEdgeValue(T start, T end, double value);
    void SetDot(const T &dot);
    bool FindDot(const T &dot);
    bool Prim(T start);
    void DisplayMST() const {min_span_tree.PrintEdges();}
    void InitialEdgeValue();
    void MTSInitial();

private:
    int size, n;
    T *dots;
    double **edge_value;
    MinSpanTree<T> min_span_tree;
    Hash<T,int> hash_table;
};

/***********************************************************
* Function Name:    Graph<T>::Graph
* Function:         Graph 的构造函数，初始化图的结构。
* Input Parameter:  sz - 图中顶点的最大数量。
***********************************************************/
template<typename T>
Graph<T>::Graph(int sz)
{
    assert(sz>1);
    size = sz;
    n = 0;
    dots = new(std::nothrow) T[size];
    assert(dots!=nullptr);
    edge_value = new(std::nothrow) double *[size];
    assert(edge_value!=nullptr);
    for (int i = 0; i < size; i++) {
        edge_value[i] = new(std::nothrow) double[size];
        assert(edge_value[i]!=nullptr);
    }


    // Initialize adjacency matrix
    InitialEdgeValue();

    min_span_tree.Initial(size);
}

/***********************************************************
* Function Name:    Initial
* Function:        初始化图的结构，设置顶点和边的存储。
* Input Parameter: sz - 图中顶点的最大数量。
***********************************************************/
template<typename T>
void Graph<T>::Initial(const int sz)
{
    assert(size==0);
    assert(sz>1);
    size=sz;
    n=0;
    dots= new(std::nothrow) T[size];
    assert(dots!=nullptr);

    edge_value = new(std::nothrow) double*[size];
    assert(edge_value!=nullptr);
    for(int i=0;i<size;i++) {
        edge_value[i] = new(std::nothrow) double[size];
        assert(edge_value[i]!=nullptr);
    }

    InitialEdgeValue();
    min_span_tree.Initial(size);
}

/***********************************************************
* Function Name: MakeEmpty
* Function:     清空图的所有数据并释放内存。
***********************************************************/
template<typename T>
void Graph<T>::MakeEmpty()
{
    if(dots!=nullptr) {
        delete[] dots;
        dots=nullptr;
    }
    if(edge_value!=nullptr) {
        for (int i = 0; i < size; i++)
            delete[] edge_value[i];
        delete[] edge_value;
        edge_value=nullptr;
    }
    size=n=0;
    min_span_tree.MakeEmpty();
    hash_table.make_empty();
}

/***********************************************************
* Function Name:    FindDot
* Function:         检查给定的顶点是否已存在于图中。
* Input Parameter: dot - 要检查的顶点。
* Returned Value:  如果顶点存在，返回 true；否则返回 false。
***********************************************************/
template<typename T>
bool Graph<T>::FindDot(const T &dot)
{
    for(int i=0;i<n;i++ )
        if(dots[i]==dot)
            return true;
    return false;
}

/***********************************************************
* Function Name:   SetDot
* Function:        向图中添加一个顶点。
* Input Parameter: dot - 要添加的顶点。
***********************************************************/
template<typename T>
void Graph<T>::SetDot(const T& dot)
{
    if(FindDot(dot))
        return;
    if(hash_table.find(dot)==nullptr)
        hash_table[dot] = n;
    dots[n]=dot;
    n++;
}
/***********************************************************
* Function Name:    SetEdgeValue
* Function:         设置图中两顶点之间的边权重。
* Input Parameters: start - 边的起点。
*                   end - 边的终点。
*                   value - 边的权重值。
***********************************************************/
template<typename T>
void Graph<T>::SetEdgeValue(T start, T end, double value)
{
    edge_value[hash_table[start]][hash_table[end]] = value;
    edge_value[hash_table[end]][hash_table[start]] = value;
}

/***********************************************************
* Function Name:    Prim
* Function:        使用 Prim 算法构建图的最小生成树。
* Input Parameter: start - 最小生成树构建的起点。
* Returned Value:  如果最小生成树成功构建，返回 true；否则返回 false。
***********************************************************/
template<typename T>
bool Graph<T>::Prim(T start)
{
    assert(n==size);// 确保图中顶点数与声明的大小一致

    double* low_cost= new(std::nothrow) double[size];// 存储当前前顶点到每个顶点的最小边权值
    assert(low_cost!=nullptr);
    int* near_vex= new(std::nothrow) int[size];// 存储与当前顶点连接的最近顶点索引
    assert(near_vex!=nullptr);

    // 初始化辅助数组
    for( int i = 0;i < size;i++ ) {
        low_cost[i] = edge_value[hash_table[start]][i];
        near_vex[i] = hash_table[start];
    }

    near_vex[hash_table[start]] = -1;// 起点标记为已访问

    // Prim 算法的主循环
    for (int i = 1; i < size; i++) {
        double min = INF;
        int v = -1;

        // 找到当前未访问顶点中与已访问集合最近的顶点
        for (int j= 0; j < size; j++)
            if (near_vex[j] != -1 && low_cost[j] < min) {
                v = j;
                min = low_cost[j];
            }

        if (v == -1)
            break;
        // 如果找到有效的顶点，则将其加入最小生成树
        MSTEdgeNode<T> temp;
        temp.tail = dots[near_vex[v]];
        temp.head = dots[v];
        temp.key = low_cost[v];
        min_span_tree.Insert(temp);

        near_vex[v] = -1; // 标记顶点 v 为已访问

        // 更新与新加入顶点连接的边的权值
        for (int j = 0; j < size; j++)
            if (near_vex[j] != -1 && edge_value[v][j] < low_cost[j]) {
                low_cost[j] = edge_value[v][j];
                near_vex[j] = v;
            }
    }

    // 释放辅助数组内存
    delete[] low_cost;
    delete[] near_vex;
    return min_span_tree.BuildSuccess(); // 检查最小生成树是否构建完成
}

/***********************************************************
* Function Name:    InitialEdgeValue
* Function:        初始化邻接矩阵
* Input Parameter: None
* Returned Value:  None
***********************************************************/
template<typename T>
void Graph<T>::InitialEdgeValue()
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            edge_value[i][j] = (i == j) ? 0 : INF;
}

/***********************************************************
* Function Name:   MTSInitial
* Function:        初始化最小生成树
* Input Parameter: None
* Returned Value:  None
***********************************************************/
template<typename T>
void Graph<T>::MTSInitial()
{
    min_span_tree.MakeEmpty();
    min_span_tree.Initial(size);
}

#endif //MY_GRAPH_MST_H
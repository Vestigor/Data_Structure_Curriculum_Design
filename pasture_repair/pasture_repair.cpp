/***********************************************************
* File:     pasture_repair.cpp
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Clion2024
* Function: Pasture Repair
* Date:     2024.11.11
* Update:   2024.11.23
***********************************************************/
#include <iostream>
#include <cassert>
#include "my_min_heap.h"// 最大支持的木头块数

#define MAX 10000// 最大支持的木头块数

/***********************************************************
* Function Name:    Input
* Function:         提供用户输入的通用函数，并对输入内容进行有效性验证。
* Input Parameters: ret - 是否直接读取输入而不打印提示信息。
*                   str - 如果 ret 为 false，则作为提示字符串打印。
* Returned Value:   用户输入结果
***********************************************************/
int Input(const bool ret,const char* str=nullptr)
{
    double x;
    while(true) {
        if(!ret)
            std::cout<<str<<"\n";
        std::cin >> x;
        // 输入校验：是否为有效的数字以及范围是否合规
        if (std::cin.fail() || x!=static_cast<int>(x)|| x<=0 || (!ret && (x <= 1 || x > MAX))) {
            std::cout << "输入非法，请重新输入！\n";
            std::cin.clear();// 清除错误标志
            std::cin.ignore(2147483647, '\n');
            continue;
        }
        break;
    }
    return static_cast<int>(x);
}

/***********************************************************
* Function Name:    pasture_repair
* Function:         实现牧场修理问题，计算最小的修理花费。
* Input Parameters: 无
* Returned Value:   无
***********************************************************/
void PastureRepair()
{
    std::cout << "+-----------------------------+\n";
    std::cout << "|          牧场修理           |\n";
    std::cout << "|       Pasture Repair        |\n";
    std::cout << "+-----------------------------+\n";

    const int N=Input(false,"请输入木头需要被锯成的块数[2 - 10000]：");
    auto nums = new(std::nothrow) int[N];
    assert(nums!=nullptr);

    std::cout << "请输入每一段木头的长度\n";
    for (int i = 0; i < N; i++)
        nums[i] = Input(true);

    // 构建最小堆并初始化总花费
    MinHeap<int> min_heap(nums, N);
    int cost=0;
    while(min_heap.Size()>1) {
        int x,y;
        min_heap.Remove(x);// 从堆中取出最小值
        min_heap.Remove(y); // 从堆中取出次小值
        int total=x+y;// 合并后的总长度
        cost+=total;// 累加合并花费
        min_heap.Insert(total);// 将合并后的木头重新插入堆中
    }

    // 输出最终结果并释放内存
    std::cout<<"修理牧场最小花费为："<<cost<<"\n";
    delete [] nums;
}


/***********************************************************
* Function Name:    main
* Function:         主函数，启动牧场修理程序。
* Input Parameters: 无
* Returned Value:   0 - 程序正常退出。
***********************************************************/
int main()
{

    PastureRepair();// 调用牧场修理函数

    return 0;
}
/***********************************************************
* File:     bank_business.cpp
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: Bank Business
* Date:     2024.10.11
* Update:   2024.10.11
***********************************************************/

#include <iostream>
#include "my_queue.h"

#define INT_MAX 2147483647
#define MAX_CUSTOMER 1000

void ClearBuffer() {
    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');
}

bool IsSame(int num, Queue<int>& q)
{
    if (q.IsEmpty())
        return false;
    QueueNode<int>* current = q.FrontAddress();
    bool first = true;
    do {
        if (!first)
            current = current->link;
        if (current->data == num)
            return true;
        first = false;    
    } while (current != q.RearAddress());

    return false;
}

bool Input(Queue<int>& A, Queue<int>& B) 
{
    std::cout << "\n请依次输入顾客总数N以及N个顾客的编号；\n";
    int N; // 顾客总数
    std::cin >> N;
    if (std::cin.fail()) {
        std::cout << "输入顾客总数非法！\n";
        ClearBuffer();
        return false;
    }
    if (N <= 0 && N > MAX_CUSTOMER) {
        std::cout << "输入顾客总数不在范围[1-"<< MAX_CUSTOMER<<"]内！\n";
        ClearBuffer();
        return false;
    }
    for (int i = 0; i < N; ++i) {
        int customer;
        std::cin >> customer;
        if (std::cin.fail()) {
            std::cout << "输入顾客编号非法！\n";
            ClearBuffer();
            return false;
        }
        if (customer <= 0) {
            std::cout << "输入顾客编号不是正整数！\n";
            ClearBuffer();
            return false;
        }
        if (IsSame(customer,A) || IsSame(customer,B)) {
            std::cout << "重复输入相同编号的顾客！\n";
            ClearBuffer();
            return false;
        }
        if (customer % 2 == 1) {
            A.EnQueue(customer); // 奇数编号到A窗口
        }
        else {
            B.EnQueue(customer); // 偶数编号到B窗口
        }
    }
    return true;
}

void Output(Queue<int>& A, Queue<int>& B)
{
    std::cout << "业务处理完成顺序为：\n";
    bool first = true;
    while (!A.IsEmpty() || !B.IsEmpty()) {
        // A窗口每次处理2个顾客
        for (int i = 0; i < 2 && !A.IsEmpty(); ++i) {
            if (!first)
                std::cout << " ";
            std::cout << A.DeQueue();
            first = false;
        }

        // B窗口每次处理1个顾客
        if (!B.IsEmpty()) {
            if (!first)
                std::cout << " ";
            std::cout << B.DeQueue();
            first = false;
        }
    }
}

void BankBusiness() 
{
	Queue<int> A, B;
    std::cout << "**顾客总数以及顾客编号输入输出规则：\n"
        << "1.顾客总数以及顾客编号应该为正整数；\n"
        << "2.顾客总数应在范围[1-"<< MAX_CUSTOMER<<"]内，顾客编号不大于2147483647；\n"
        << "3.A窗口的顾客优先输出。\n";
    while (!Input(A, B))
        ;

    Output(A, B);
}

int main()
{
	BankBusiness();

	return 0;
}
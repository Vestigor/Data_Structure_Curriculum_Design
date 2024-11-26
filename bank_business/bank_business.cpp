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

#define MAX 2147483647
#define MAX_CUSTOMER 1000

/***********************************************************
* Function Name:   ClearBuffer
* Function:        清理输入缓冲区，重置输入状态
* Input Parameter: 无
* Returned Value:  无
***********************************************************/
void ClearBuffer() {
    std::cin.clear();
    std::cin.ignore(MAX, '\n');
}

/***********************************************************
* Function Name:   IsSame
* Function:        检查队列中是否存在与给定数字相同的元素
* Input Parameter: num - 待检查的数字
*                  q - 要检查的队列
* Returned Value:  如果找到相同元素返回 true，否则返回 false
***********************************************************/
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

/***********************************************************
* Function Name:   Input
* Function:        获取用户输入并将奇数和偶数编号的顾客分配到不同队列
* Input Parameter: A - 存放奇数编号顾客的队列
*                  B - 存放偶数编号顾客的队列
* Returned Value:  输入成功返回 true，否则返回 false
***********************************************************/
bool Input(Queue<int>& A, Queue<int>& B) 
{
    std::cout << "\n请依次输入顾客总数N以及N个顾客的编号；\n";
    double dN;
    std::cin >> dN;
    int N= static_cast<int>(dN); // 顾客总数
    if (std::cin.fail()||dN!=N) {
        std::cout << "输入顾客总数非法！\n";
        ClearBuffer();
        return false;
    }
    if (N <= 0 || N > MAX_CUSTOMER) {
        std::cout << "输入顾客总数不在范围[1-"<< MAX_CUSTOMER<<"]内！\n";
        ClearBuffer();
        return false;
    }
    for (int i = 0; i < N; ++i) {
        double d_customer;
        std::cin >> d_customer;
        int customer= static_cast<int>(d_customer);
        if (std::cin.fail()||d_customer!=customer) {
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

/***********************************************************
* Function Name:   Output
* Function:        按顺序输出队列中顾客的处理顺序
* Input Parameter: A - 存放奇数编号顾客的队列
*                  B - 存放偶数编号顾客的队列
* Returned Value:  无
***********************************************************/
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
    std::cout<<"\n";
}

/***********************************************************
* Function Name:   BankBusiness
* Function:        模拟银行业务处理逻辑
* Input Parameter: 无
* Returned Value:  无
***********************************************************/
void BankBusiness() 
{
    std::cout << "+--------------------------------------------+" << std::endl;
    std::cout << "|                  银行业务                  |" << std::endl;
    std::cout << "|                Bank Business               |" << std::endl;
    std::cout << "+--------------------------------------------+" << std::endl;

	Queue<int> A, B;
    std::cout << "**顾客总数以及顾客编号输入输出规则：\n"
        << "1.顾客总数以及顾客编号应该为正整数；\n"
        << "2.顾客总数应在范围[1-"<< MAX_CUSTOMER<<"]内，顾客编号不大于2147483647；\n"
        << "3.A窗口的顾客优先输出。\n";
    while (!Input(A, B))
        ;

    Output(A, B);
}
/***********************************************************
* Function Name:   main
* Function:        程序入口，启动银行业务处理
* Input Parameter: 无
* Returned Value:  程序执行状态（0表示正常）
***********************************************************/
int main()
{
	BankBusiness();

	return 0;
}

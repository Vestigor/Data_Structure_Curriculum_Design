/***********************************************************
* File:     bank_business.cpp
* Author:   Xiaolong Ma(��С��)
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
    std::cout << "\n����������˿�����N�Լ�N���˿͵ı�ţ�\n";
    int N; // �˿�����
    std::cin >> N;
    if (std::cin.fail()) {
        std::cout << "����˿������Ƿ���\n";
        ClearBuffer();
        return false;
    }
    if (N <= 0 && N > MAX_CUSTOMER) {
        std::cout << "����˿��������ڷ�Χ[1-"<< MAX_CUSTOMER<<"]�ڣ�\n";
        ClearBuffer();
        return false;
    }
    for (int i = 0; i < N; ++i) {
        int customer;
        std::cin >> customer;
        if (std::cin.fail()) {
            std::cout << "����˿ͱ�ŷǷ���\n";
            ClearBuffer();
            return false;
        }
        if (customer <= 0) {
            std::cout << "����˿ͱ�Ų�����������\n";
            ClearBuffer();
            return false;
        }
        if (IsSame(customer,A) || IsSame(customer,B)) {
            std::cout << "�ظ�������ͬ��ŵĹ˿ͣ�\n";
            ClearBuffer();
            return false;
        }
        if (customer % 2 == 1) {
            A.EnQueue(customer); // ������ŵ�A����
        }
        else {
            B.EnQueue(customer); // ż����ŵ�B����
        }
    }
    return true;
}

void Output(Queue<int>& A, Queue<int>& B)
{
    std::cout << "ҵ�������˳��Ϊ��\n";
    bool first = true;
    while (!A.IsEmpty() || !B.IsEmpty()) {
        // A����ÿ�δ���2���˿�
        for (int i = 0; i < 2 && !A.IsEmpty(); ++i) {
            if (!first)
                std::cout << " ";
            std::cout << A.DeQueue();
            first = false;
        }

        // B����ÿ�δ���1���˿�
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
    std::cout << "**�˿������Լ��˿ͱ�������������\n"
        << "1.�˿������Լ��˿ͱ��Ӧ��Ϊ��������\n"
        << "2.�˿�����Ӧ�ڷ�Χ[1-"<< MAX_CUSTOMER<<"]�ڣ��˿ͱ�Ų�����2147483647��\n"
        << "3.A���ڵĹ˿����������\n";
    while (!Input(A, B))
        ;

    Output(A, B);
}

int main()
{
	BankBusiness();

	return 0;
}
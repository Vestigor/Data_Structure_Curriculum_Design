/***********************************************************
* File:     intersection_of_ordered_linked_list_sequences.cpp
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Encoding: UTF-8
* Function: 两个有序链表序列的交集
* Date:     2024.10.5
* Update:   2024.10.5
***********************************************************/

#include <iostream>
#include "my_singly_link_list.h"

#define MAX 2147483647
#define MAX_BUFFER 1000000000

/***********************************************************
* Function Name:   constructor
* Function:        清除输入缓冲区，防止错误输入影响后续操作
* Input Parameter:
* Returned Value:  
***********************************************************/
void ClearBuffer() {
	std::cin.clear();// 清除输入状态
	std::cin.ignore(MAX_BUFFER, '\n');// 忽略缓冲区中的内容
}

/***********************************************************
* Function Name:   PrintOrderedLinkedList
* Function:        打印链表
* Input Parameter: link: 需要被打印的链表
* Returned Value:
***********************************************************/
void PrintOrderedLinkedList(LinkList<int>& link, const char* str)
{
	std::cout<<str;
	bool first=true;
	int n=0;
	if(link.Length()==0)
		std::cout<<"NULL";
	else
		for(auto node:link) {
			if(!first)
				std::cout<<" ";
			std::cout<<node;
			first=false;
			n++;
		}
	std::cout<<"\n有序链表元素总数为："<<n<<"\n";
}

/***********************************************************
* Function Name:   Intersection
* Function:        求两个有序链表的交集并存储到交集链表中
* Input Parameter: intersection: 用于存储交集的链表
*                  first:第一个有序链表
*                  second:第二个有序链表
* Returned Value:  temp：交集链表
***********************************************************/
LinkList<int> Intersection(LinkList<int>& first,LinkList<int>& second)
{
	LinkList<int> temp;
	auto node1=first.begin();
	auto node2=second.begin();
	int pre=0;
	while(node1 != first.end()&&node2 != second.end()) {
		if(*node1==*node2) {
			temp.inputRear(*node1);
			pre==*node1;
			++node1;
			++node2;
		}
		else if(*node1<*node2)
			++node1;
		else
			++node2;

	}
	return temp;
}

/***********************************************************
* Function Name:   constructor
* Function:        输入非降序的正整数序列
* Input Parameter: rank:用于指示输入的序列编号
* Returned Value:  返回输入的链表
***********************************************************/
LinkList<int> Input(int rank)
{
	std::cout << "请输入第" << rank << "个由若干正整数构成的非降序序列，其中-1表示输出结束\n";
	LinkList<int>temp;
	double temp_element, previous = 1;// 临时元素和前一个元素
	while (true) {
		std::cin >> temp_element;
		int element = static_cast<int>(temp_element);
		// 输入验证
		if (std::cin.fail() || (temp_element < -1) || temp_element == 0|| temp_element != element) {
			std::cout << "输入的元素包含非正整数项，请重新输入\n";
			ClearBuffer();
			continue;
		}
		if (element == -1) {
			ClearBuffer();
			break;
		}
		if (element < previous) {
			std::cout << "输入的元素中存在前项大于后项的情况，请从错误元素开始继续输入\n";
			ClearBuffer();
			continue;
		}
		temp.inputRear(element);
		previous = element;
	}
	return temp;
}
/***********************************************************
* Function Name:   IntersectionOfOrderedLinkedListSequences
* Function:        调用函数，实现输入两个字符串及求其交集
* Input Parameter:
* Returned Value:  0
***********************************************************/
void IntersectionOfOrderedLinkedListSequences()
{
	std::cout << "+----------------------------------------------------------+\n";
	std::cout << "|                    有序链表序列的交集                    |\n";
	std::cout << "|      Intersection Of Ordered Linked List Sequences       |\n";
	std::cout << "+----------------------------------------------------------+\n";
	LinkList<int> first = Input(1);// 输入第一个链表
	LinkList<int> second = Input(2);// 输入第二个链表
	LinkList<int> intersection = Intersection(first, second);
	std::cout<<"\n\n";
	PrintOrderedLinkedList(first,"第一个有序链表为：\n");
	PrintOrderedLinkedList(second, "第二个有序链表为：\n");
	PrintOrderedLinkedList(intersection,"两个有序链表序列的交集为：\n");
}
/***********************************************************
* Function Name:   main
* Function:        调用功能函数
* Input Parameter:
* Returned Value:  0
***********************************************************/
int main()
{
	// 调用主功能,求两个有序链表序列的交集
	IntersectionOfOrderedLinkedListSequences();

	return 0;
}

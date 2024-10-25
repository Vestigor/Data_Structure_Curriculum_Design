/***********************************************************
* File:     intersection_of_ordered_linked_list_sequences.cpp
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: 两个有序链表序列的交集
* Date:     2024.10.5
* Update:   2024.10.5
***********************************************************/

#include <iostream>
#include "my_singly_link_list.h"

#define INT_MAX 2147483647

/***********************************************************
* Function Name:   constructor
* Function:        清除输入缓冲区，防止错误输入影响后续操作
* Input Parameter:
* Returned Value:  
***********************************************************/
void ClearBuffer() {
	std::cin.clear();// 清除输入状态
	std::cin.ignore(INT_MAX, '\n');// 忽略缓冲区中的内容
}

/***********************************************************
* Function Name:   Intersection
* Function:        求两个有序链表的交集并存储到交集链表中
* Input Parameter: intersection: 用于存储交集的链表
*                  first:第一个有序链表
*                  second:第二个有序链表
* Returned Value:  
***********************************************************/
void Intersection(LinkList<int>& intersection,LinkList<int>& first,LinkList<int>& second)
{
	int previous = 0;
	for(int i=1;i<= first.Length();i++)
		// 检查当前元素是否在第二个链表中，并且大于前一个元素（避免重复）
		if (second.Search(first[i]) && first[i] > previous) {
			intersection.inputRear(first[i]); // 添加到交集链表的尾部
			previous = first[i]; // 更新前一个元素
		}
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
		while (1) {
			std::cin >> temp_element;
			int element = int(temp_element);
			// 输入验证
			if (std::cin.fail() || temp_element < -1 || temp_element == 0|| temp_element != element) {
				std::cout << "输入的元素包含非正整数项，请重新输入\n";
				temp.makeEmpty();
				previous = 1;
				ClearBuffer();
				continue;
			}
			if (element == -1) {
				ClearBuffer();
				break;
			}
			if (element < previous) {
				std::cout << "输入的元素中存在前项大于后项的情况，请重新输入\n";
				temp.makeEmpty();
				previous = 1;
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
	LinkList<int> first, second;
	first=Input(1);// 输入第一个链表
	second = Input(2);// 输入第二个链表
	LinkList<int> intersection; 
	Intersection(intersection, first, second);
	std::cout << "两个有序链表序列的交集为：\n";
	if (intersection.Length() == 0)// 检查交集是否为空
		std::cout << "NULL\n";
	else
		for (int i = 1; i <= intersection.Length(); i++) {
			if (i != 1)
				std::cout << " ";
			std::cout << intersection[i];
		}
	std::cout << "\n";
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
/***********************************************************
* File:     intersection_of_ordered_linked_list_sequences.cpp
* Author:   Xiaolong Ma(��С��)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: ���������������еĽ���
* Date:     2024.10.5
* Update:   2024.10.5
***********************************************************/

#include <iostream>
#include "my_singly_link_list.h"

#define INT_MAX 2147483647

/***********************************************************
* Function Name:   constructor
* Function:        ������뻺��������ֹ��������Ӱ���������
* Input Parameter:
* Returned Value:  
***********************************************************/
void ClearBuffer() {
	std::cin.clear();// �������״̬
	std::cin.ignore(INT_MAX, '\n');// ���Ի������е�����
}

/***********************************************************
* Function Name:   Intersection
* Function:        ��������������Ľ������洢������������
* Input Parameter: intersection: ���ڴ洢����������
*                  first:��һ����������
*                  second:�ڶ�����������
* Returned Value:  
***********************************************************/
void Intersection(LinkList<int>& intersection,LinkList<int>& first,LinkList<int>& second)
{
	int previous = 0;
	for(int i=1;i<= first.Length();i++)
		// ��鵱ǰԪ���Ƿ��ڵڶ��������У����Ҵ���ǰһ��Ԫ�أ������ظ���
		if (second.Search(first[i]) && first[i] > previous) {
			intersection.inputRear(first[i]); // ��ӵ����������β��
			previous = first[i]; // ����ǰһ��Ԫ��
		}
}
/***********************************************************
* Function Name:   constructor
* Function:        ����ǽ��������������
* Input Parameter: rank:����ָʾ��������б��
* Returned Value:  �������������
***********************************************************/
LinkList<int> Input(int rank)
{
	std::cout << "�������" << rank << "�����������������ɵķǽ������У�����-1��ʾ�������\n";
	LinkList<int>temp;
	double temp_element, previous = 1;// ��ʱԪ�غ�ǰһ��Ԫ��
		while (1) {
			std::cin >> temp_element;
			int element = int(temp_element);
			// ������֤
			if (std::cin.fail() || temp_element < -1 || temp_element == 0|| temp_element != element) {
				std::cout << "�����Ԫ�ذ����������������������\n";
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
				std::cout << "�����Ԫ���д���ǰ����ں�������������������\n";
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
* Function:        ���ú�����ʵ�����������ַ��������佻��
* Input Parameter:
* Returned Value:  0
***********************************************************/
void IntersectionOfOrderedLinkedListSequences()
{
	LinkList<int> first, second;
	first=Input(1);// �����һ������
	second = Input(2);// ����ڶ�������
	LinkList<int> intersection; 
	Intersection(intersection, first, second);
	std::cout << "���������������еĽ���Ϊ��\n";
	if (intersection.Length() == 0)// ��齻���Ƿ�Ϊ��
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
* Function:        ���ù��ܺ���
* Input Parameter:
* Returned Value:  0
***********************************************************/
int main()
{
	// ����������,�����������������еĽ���
	IntersectionOfOrderedLinkedListSequences();

	return 0;
}
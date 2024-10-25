#pragma once
/***********************************************************
* File:     my_stack.h
* Author:   Xiaolong Ma(��С��)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: template of stack
* Date:     2024.10.11
* Update:   2024.10.11
***********************************************************/

#define MEMORY_ALLOCATION_ERROR -1
#define STACK_OVER_FLOW -2
#define STACK_EMPTY -3

/***********************************************************
* Struct Name:   Node
* Function:      ջ�ڵ�ṹ��
* Template:      T - �ڵ���������
* Data Members:  data - �洢�ڵ������
*                next - ָ����һ���ڵ��ָ��
***********************************************************/
template <typename T>
struct Node {
	T data;       // �ڵ�����
	Node<T>* next;// ָ����һ���ڵ��ָ��
	// ���캯���������ڵ㲢ָ����һ���ڵ�
	Node(Node<T>* ptr = NULL) { next = ptr; }
	// ���캯���������ڵ㲢��ʼ�����ݺ�ָ��
	Node(const T& item, Node<T>* ptr = NULL) { data = item, next = ptr; }
};

/***********************************************************
* Class Name:       Stack
* Function:         ջ�࣬�ṩջ�Ļ�������
* Template:         T - ջ�д洢����������
* Data Members:     top - ָ��ջ���ڵ��ָ��
*                  size - ջ��Ԫ������
* Member Functions:
*                   Stack() - Ĭ�Ϲ��캯��
*                   ~Stack() - ��������
*                   void Push(const T& x) - ���Ԫ�ص�ջ
*                   T Pop() - �Ƴ�������ջ��Ԫ��
*                   T getTop() - ��ȡջ��Ԫ�ص����Ƴ�
*                   bool IsEmpty() - ���ջ�Ƿ�Ϊ��
*                   int getSize() - ��ȡջ�Ĵ�С
*                   void makeEmpty() - ���ջ
***********************************************************/
template <typename T>
class Stack {
public:
	Stack() :top(NULL),size(0) {}// Ĭ�Ϲ��캯��
	~Stack() { makeEmpty(); }// �������������ջ
	void Push(const T& x);// ���Ԫ�ص�ջ
	T Pop(); // �Ƴ�������ջ��Ԫ��
	T getTop();
	bool IsEmpty()const { return top == NULL; }
	int getSize()const { return size; };
	void makeEmpty();
private:
	Node<T>* top; // ָ��ջ���ڵ��ָ��
	int size;
};

/***********************************************************
* Function Name:   Push
* Function:        ��Ԫ��xѹ��ջ��
* Input Parameter: x: Ҫѹ��ջ��Ԫ��
* Returned Value:
***********************************************************/
template <typename T>
void Stack<T>::Push(const T& x)
{
	if (top == NULL) {
		top = new(std::nothrow) Node<T>(x);
		// �ڴ����ʧ�ܣ��׳��쳣
		if (top == NULL) {
			std::cout << "�ڴ�������\n";
			exit(MEMORY_ALLOCATION_ERROR);
		}
		size++;
		return;
	}
	Node<T>* newNode = new(std::nothrow) Node<T>(x);
	// �ڴ����ʧ�ܣ��׳��쳣
	if (newNode == NULL) {
		std::cout << "�ڴ�������\n";
		exit(MEMORY_ALLOCATION_ERROR);
	}
	newNode->next = top;
	top = newNode;
	size++;
}

/***********************************************************
* Function Name:   Pop
* Function:        �Ƴ�������ջ��Ԫ��
* Input Parameter:
* Returned Value:  ����ջ��Ԫ�ص�ֵ
***********************************************************/
template <typename T>
T Stack<T>::Pop()
{
	if (IsEmpty()) {
		std::cout << "ջΪ��,����ɾ��Ԫ��!\n";
		exit(STACK_EMPTY);
	}
	Node<T>* p = top;
	T x = top->data;
	top = top->next;
	delete p;
	size--;
	return x;
}

/***********************************************************
* Function Name:   getTop
* Function:        ��ȡջ��Ԫ�ص�ֵ�������Ƴ�
* Input Parameter:
* Returned Value:  ����ջ��Ԫ�ص�ֵ
***********************************************************/
template <typename T>
T Stack<T>::getTop()
{
	if (IsEmpty()) {
		std::cout << "ջΪ��,����ȡ��Ԫ��!\n";
		exit(STACK_EMPTY);
	}
	return top->data;
}

/***********************************************************
* Function Name:   makeEmpty
* Function:        ���ջ���ͷ����нڵ���ڴ�
* Input Parameter:
* Returned Value:
***********************************************************/
template <typename T>
void Stack<T>::makeEmpty()
{
	Node<T>* p;
	while (!IsEmpty()) 
		Pop();// ���ϵ���Ԫ��ֱ��ջΪ��
	size = 0;
}
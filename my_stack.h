#pragma once
/***********************************************************
* File:     my_stack.h
* Author:   Xiaolong Ma(马小龙)
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
* Function:      栈节点结构体
* Template:      T - 节点数据类型
* Data Members:  data - 存储节点的数据
*                next - 指向下一个节点的指针
***********************************************************/
template <typename T>
struct Node {
	T data;       // 节点数据
	Node<T>* next;// 指向下一个节点的指针
	// 构造函数，创建节点并指向下一个节点
	Node(Node<T>* ptr = NULL) { next = ptr; }
	// 构造函数，创建节点并初始化数据和指针
	Node(const T& item, Node<T>* ptr = NULL) { data = item, next = ptr; }
};

/***********************************************************
* Class Name:       Stack
* Function:         栈类，提供栈的基本操作
* Template:         T - 栈中存储的数据类型
* Data Members:     top - 指向栈顶节点的指针
*                  size - 栈的元素数量
* Member Functions:
*                   Stack() - 默认构造函数
*                   ~Stack() - 析构函数
*                   void Push(const T& x) - 添加元素到栈
*                   T Pop() - 移除并返回栈顶元素
*                   T getTop() - 获取栈顶元素但不移除
*                   bool IsEmpty() - 检查栈是否为空
*                   int getSize() - 获取栈的大小
*                   void makeEmpty() - 清空栈
***********************************************************/
template <typename T>
class Stack {
public:
	Stack() :top(NULL),size(0) {}// 默认构造函数
	~Stack() { makeEmpty(); }// 析构函数，清空栈
	void Push(const T& x);// 添加元素到栈
	T Pop(); // 移除并返回栈顶元素
	T getTop();
	bool IsEmpty()const { return top == NULL; }
	int getSize()const { return size; };
	void makeEmpty();
private:
	Node<T>* top; // 指向栈顶节点的指针
	int size;
};

/***********************************************************
* Function Name:   Push
* Function:        将元素x压入栈中
* Input Parameter: x: 要压入栈的元素
* Returned Value:
***********************************************************/
template <typename T>
void Stack<T>::Push(const T& x)
{
	if (top == NULL) {
		top = new(std::nothrow) Node<T>(x);
		// 内存分配失败，抛出异常
		if (top == NULL) {
			std::cout << "内存分配错误！\n";
			exit(MEMORY_ALLOCATION_ERROR);
		}
		size++;
		return;
	}
	Node<T>* newNode = new(std::nothrow) Node<T>(x);
	// 内存分配失败，抛出异常
	if (newNode == NULL) {
		std::cout << "内存分配错误！\n";
		exit(MEMORY_ALLOCATION_ERROR);
	}
	newNode->next = top;
	top = newNode;
	size++;
}

/***********************************************************
* Function Name:   Pop
* Function:        移除并返回栈顶元素
* Input Parameter:
* Returned Value:  返回栈顶元素的值
***********************************************************/
template <typename T>
T Stack<T>::Pop()
{
	if (IsEmpty()) {
		std::cout << "栈为空,不能删除元素!\n";
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
* Function:        获取栈顶元素的值，但不移除
* Input Parameter:
* Returned Value:  返回栈顶元素的值
***********************************************************/
template <typename T>
T Stack<T>::getTop()
{
	if (IsEmpty()) {
		std::cout << "栈为空,不能取出元素!\n";
		exit(STACK_EMPTY);
	}
	return top->data;
}

/***********************************************************
* Function Name:   makeEmpty
* Function:        清空栈，释放所有节点的内存
* Input Parameter:
* Returned Value:
***********************************************************/
template <typename T>
void Stack<T>::makeEmpty()
{
	Node<T>* p;
	while (!IsEmpty()) 
		Pop();// 不断弹出元素直到栈为空
	size = 0;
}
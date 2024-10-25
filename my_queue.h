#pragma once
/***********************************************************
* File:     my_queue.h
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: template of squeue
* Date:     2024.10.11
* Update:   2024.10.11
***********************************************************/

#define MEMORY_ALLOCATION_ERROR -1
#define STACK_EMPTY -2
#define EMPTY_ADDRESS -3

/***********************************************************
* Struct Name:   QueueNode
* Function:      队列节点结构体
* Template:      T - 节点数据类型
* Data Members:  data - 存储节点的数据
*                link - 指向下一个节点的指针
***********************************************************/
template <typename T>
struct QueueNode {
	T data;// 节点数据
	QueueNode<T>* link;// 指向下一个节点的指针
	// 构造函数，初始化节点数据和指针
	QueueNode(T d = 0, QueueNode* l = NULL) :data(d), link(l) {}

	//QueueNode<T>* operator++(int);
};

/***********************************************************
*Class Name : Queue
* Function : 队列类，提供队列的基本操作
* Template : T - 队列中存储的数据类型
* Data Members : front - 指向队头节点的指针
* rear - 指向队尾节点的指针
* Member Functions :
*Queue() - 默认构造函数
* ~Queue() - 析构函数
* void EnQueue(const T & x) - 入队操作
* T DeQueue() - 出队操作
* T GetFront() - 获取队头元素
* QueueNode<T>*FrontAddress() - 获取队头节点地址
* QueueNode<T>*RearAddress() - 获取队尾节点地址
* void makeEmpty() - 清空队列
* bool IsEmpty() - 检查队列是否为空
* **********************************************************/
template <typename T>
class Queue {
public:
	Queue():rear(NULL), front(NULL) {}// 默认构造函数
	~Queue() { makeEmpty(); }// 析构函数，释放所有节点
	void EnQueue(const T& x);// 入队操作
	T DeQueue();// 出队操作
	T GetFront(); // 获取队头元素
	QueueNode<T>* FrontAddress() { return front; }// 获取队头节点地址
	QueueNode<T>* RearAddress() { return rear; } // 获取队尾节点地址
	void makeEmpty();// 清空队列
	bool IsEmpty()const { return front == NULL; }// 检查队列是否为空
private:
	QueueNode<T>* front, * rear;
};

/***********************************************************
* Function Name:   EnQueue
* Function:        将元素x加入队列
* Input Parameter: x - 要加入队列的元素
* Returned Value:  无
***********************************************************/
template <typename T>
void Queue<T>::EnQueue(const T& x)
{
	if (front == NULL) {
		front = rear = new(std::nothrow) QueueNode<T>(x, NULL);
		if (front == NULL) {
			std::cout << "内存分配错误！\n";
			exit(MEMORY_ALLOCATION_ERROR);
		}
	}
	else {
		rear = rear->link = new(std::nothrow) QueueNode<T>(x, NULL);
		if (rear == NULL) {
			std::cout << "内存分配错误！\n";
			exit(MEMORY_ALLOCATION_ERROR);
		}
	}
		
}

/***********************************************************
* Function Name:   DeQueue
* Function:        从队列中删除并返回队头元素
* Input Parameter: 无
* Returned Value:  返回队头元素
***********************************************************/
template <typename T>
T Queue<T>::DeQueue()
{
	if (IsEmpty()) {
		std::cout << "队列为空,不能删除元素!\n";
		exit(STACK_EMPTY);
	}
	QueueNode<T>* p = front;
	T retvalue = p->data;// 保存队头元素
	front = front->link;// 移动队头指针
	delete p;
	return retvalue;// 返回队头元素
}

/***********************************************************
* Function Name:   GetFront
* Function:        获取队头元素而不删除
* Input Parameter: 无
* Returned Value:  返回队头元素
***********************************************************/
template <typename T>
T Queue<T>::GetFront() 
{
	if (IsEmpty()) {
		std::cout << "队列为空,不能提取队头元素!\n";
		exit(STACK_EMPTY);
	}
	return front->data;
}

/***********************************************************
* Function Name:   makeEmpty
* Function:        清空队列，释放所有节点的内存
* Input Parameter: 无
* Returned Value:  无
***********************************************************/
template <typename T>
void  Queue<T>::makeEmpty()
{
	QueueNode<T>* p;
	while (front != NULL) {
		p = front;
		front = front->link;// 移动队头指针
		delete p;
	}
}
/*************************************
template <typename T>
QueueNode<T>* QueueNode<T>::operator++(int)
{
	QueueNode<T>* temp = this;
	this = this->link;
	return temp;
}
***************************************/
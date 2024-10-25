#pragma once
/***********************************************************
* File:     my_queue.h
* Author:   Xiaolong Ma(��С��)
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
* Function:      ���нڵ�ṹ��
* Template:      T - �ڵ���������
* Data Members:  data - �洢�ڵ������
*                link - ָ����һ���ڵ��ָ��
***********************************************************/
template <typename T>
struct QueueNode {
	T data;// �ڵ�����
	QueueNode<T>* link;// ָ����һ���ڵ��ָ��
	// ���캯������ʼ���ڵ����ݺ�ָ��
	QueueNode(T d = 0, QueueNode* l = NULL) :data(d), link(l) {}

	//QueueNode<T>* operator++(int);
};

/***********************************************************
*Class Name : Queue
* Function : �����࣬�ṩ���еĻ�������
* Template : T - �����д洢����������
* Data Members : front - ָ���ͷ�ڵ��ָ��
* rear - ָ���β�ڵ��ָ��
* Member Functions :
*Queue() - Ĭ�Ϲ��캯��
* ~Queue() - ��������
* void EnQueue(const T & x) - ��Ӳ���
* T DeQueue() - ���Ӳ���
* T GetFront() - ��ȡ��ͷԪ��
* QueueNode<T>*FrontAddress() - ��ȡ��ͷ�ڵ��ַ
* QueueNode<T>*RearAddress() - ��ȡ��β�ڵ��ַ
* void makeEmpty() - ��ն���
* bool IsEmpty() - �������Ƿ�Ϊ��
* **********************************************************/
template <typename T>
class Queue {
public:
	Queue():rear(NULL), front(NULL) {}// Ĭ�Ϲ��캯��
	~Queue() { makeEmpty(); }// �����������ͷ����нڵ�
	void EnQueue(const T& x);// ��Ӳ���
	T DeQueue();// ���Ӳ���
	T GetFront(); // ��ȡ��ͷԪ��
	QueueNode<T>* FrontAddress() { return front; }// ��ȡ��ͷ�ڵ��ַ
	QueueNode<T>* RearAddress() { return rear; } // ��ȡ��β�ڵ��ַ
	void makeEmpty();// ��ն���
	bool IsEmpty()const { return front == NULL; }// �������Ƿ�Ϊ��
private:
	QueueNode<T>* front, * rear;
};

/***********************************************************
* Function Name:   EnQueue
* Function:        ��Ԫ��x�������
* Input Parameter: x - Ҫ������е�Ԫ��
* Returned Value:  ��
***********************************************************/
template <typename T>
void Queue<T>::EnQueue(const T& x)
{
	if (front == NULL) {
		front = rear = new(std::nothrow) QueueNode<T>(x, NULL);
		if (front == NULL) {
			std::cout << "�ڴ�������\n";
			exit(MEMORY_ALLOCATION_ERROR);
		}
	}
	else {
		rear = rear->link = new(std::nothrow) QueueNode<T>(x, NULL);
		if (rear == NULL) {
			std::cout << "�ڴ�������\n";
			exit(MEMORY_ALLOCATION_ERROR);
		}
	}
		
}

/***********************************************************
* Function Name:   DeQueue
* Function:        �Ӷ�����ɾ�������ض�ͷԪ��
* Input Parameter: ��
* Returned Value:  ���ض�ͷԪ��
***********************************************************/
template <typename T>
T Queue<T>::DeQueue()
{
	if (IsEmpty()) {
		std::cout << "����Ϊ��,����ɾ��Ԫ��!\n";
		exit(STACK_EMPTY);
	}
	QueueNode<T>* p = front;
	T retvalue = p->data;// �����ͷԪ��
	front = front->link;// �ƶ���ͷָ��
	delete p;
	return retvalue;// ���ض�ͷԪ��
}

/***********************************************************
* Function Name:   GetFront
* Function:        ��ȡ��ͷԪ�ض���ɾ��
* Input Parameter: ��
* Returned Value:  ���ض�ͷԪ��
***********************************************************/
template <typename T>
T Queue<T>::GetFront() 
{
	if (IsEmpty()) {
		std::cout << "����Ϊ��,������ȡ��ͷԪ��!\n";
		exit(STACK_EMPTY);
	}
	return front->data;
}

/***********************************************************
* Function Name:   makeEmpty
* Function:        ��ն��У��ͷ����нڵ���ڴ�
* Input Parameter: ��
* Returned Value:  ��
***********************************************************/
template <typename T>
void  Queue<T>::makeEmpty()
{
	QueueNode<T>* p;
	while (front != NULL) {
		p = front;
		front = front->link;// �ƶ���ͷָ��
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
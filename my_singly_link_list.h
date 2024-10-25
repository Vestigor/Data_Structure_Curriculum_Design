#pragma once
/***********************************************************
* File:     my_singly_link_list.h
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: template of singly link list
* Date:     2024.9.17
* Update:   2024.9.28
***********************************************************/
#include <iostream>

#define MEMORY_ALLOCATION_ERROR -1
#define OUT_OF_RANGE -2

/***********************************************************
* Struct Name:   Node
* Function:      链表结点结构体
* Template:      T - 节点数据类型
* Data Members:  data - 存储节点的数据
*                next - 指向下一个节点的指针
***********************************************************/
template <typename T>
struct Node {
    T data;// 节点数据
    Node<T>* next;

    operator T() const { return data; }
    operator T& () { return data; }
    operator const T& () const { return data; }
    Node<T>& operator=(const Node<T>& node){this->data = node.data;return *this;}
    bool operator==(const Node<T>& node) const { return this->data == node.data && this->next == node.next;  }
    Node(Node<T>* ptr = NULL) { next = ptr; }
    Node(const T& item, Node<T>* ptr = NULL) { data = item, next = ptr; }
};

/***********************************************************
* Class Name:       LinkList
* Function:         链表类，提供链表的基本操作
* Template:         T - 链表中存储的数据类型
* Data Members:     head - 指向链表头节点的指针
* Member Functions:
*                   LinkList() - 默认构造函数
*                   LinkList(const T& x) - 带初始值的构造函数
*                   LinkList(LinkList<T>& L) - 拷贝构造函数
*                   ~LinkList() - 析构函数
*                   void makeEmpty() - 清空链表
*                   int Length() - 返回链表长度
*                   Node<T>* getHead() - 获取链表头节点
*                   Node<T>* Search(const T x) - 查找节点
*                   Node<T>* Locate(int i) - 定位节点
*                   bool getData(int i, T& x) - 获取节点数据
*                   bool setData(int i, const T& x) - 设置节点数据
*                   bool Insert(int i, const T& x) - 插入节点
*                   bool Remove(int i, T& x) - 删除节点
*                   bool IsEmpty() - 检查链表是否为空
*                   bool IsFull() - 检查链表是否满
*                   void inputFront(const T& x) - 从前面输入节点数据
*                   void inputRear(const T& x) - 从后面输入节点数据
*                   void output() - 输出链表数据
*                   LinkList<T>& operator=(const LinkList<T>& other) - 赋值运算符重载
*                   T& operator[](int index) - 下标运算符重载
***********************************************************/
template <typename T>
class LinkList {
public:

    class iterator {
    private:
        Node<T>* current;
    public:
        iterator(Node<T>* ptr = NULL):current(ptr){}
        iterator& operator++() { current = current->next; return *this; }
        T& operator*() { return current->data; }
        bool operator==(const iterator& other) const { return current == other.current; }
        bool operator!=(const iterator& other) const { return current != other.current; }
    };
    iterator begin() { return iterator(head->next); }
    iterator end() { return iterator(NULL); }
    

    LinkList();
    LinkList(const T& x);
    LinkList(LinkList<T>& L);
    ~LinkList() { makeEmpty(); }
    void makeEmpty();
    int Length();
    Node<T>* getHead(){ return head; }
    Node<T>* Search(const T x);
    Node<T>* Locate(int i);
    bool getData(int i, T& x);
    bool setData(int i, const T& x);
    bool Insert(int i,const T& x);
    bool Remove(int i, T& x);
    bool IsEmpty() { return head->next == NULL ? true : false; }
    bool IsFull() { return false;}
    void inputFront(const T& x);
    void inputRear(const T& x);
    void output();
    LinkList<T>& operator=(const LinkList<T>& other);


    T& operator[](int index);

private:
    Node<T>* head;
};
 
/********************************************************
*Function Name :    LinkList
* Function :        构造函数，头结点不储存数据，只用于定位
* Input Parameter : 
* Returned Value :
***********************************************************/
template <typename T>
LinkList<T>::LinkList(){
    head = new(std::nothrow) Node<T>;

    // 内存分配失败，抛出异常
    if (head == NULL) {
        std::cout << "内存分配错误！\n";
        exit(MEMORY_ALLOCATION_ERROR);
    }
}
/********************************************************
*Function Name :    LinkList
* Function :        含参构造函数
* Input Parameter : x
* Returned Value :
***********************************************************/
template <typename T>
LinkList<T>::LinkList(const T& x){
    head = new(std::nothrow) Node<T>;

    // 内存分配失败，抛出异常
    if (head == NULL) {
        std::cout << "内存分配错误！\n";
        exit(MEMORY_ALLOCATION_ERROR);
    }

    Node<T>newNode = new(std::nothrow) Node<T>(x);
    if (newNode == NULL) {
        std::cout << "内存分配错误！\n";
        exit(MEMORY_ALLOCATION_ERROR);
    }
    head->next = newNode;
}
/***********************************************************
* Function Name:   LinkList
* Function:        拷贝构造函数，复制链表L的元素
* Input Parameter: L - 被复制的链表
* Returned Value:  
***********************************************************/
template <typename T>
LinkList<T>::LinkList(LinkList& L) {
    Node<T>* destptr = head = new Node<T>;// 创建新链表的头节点
    if (head == NULL) {
        std::cout << "内存分配错误！\n";
        exit(MEMORY_ALLOCATION_ERROR);
    }
    T value;
    Node<T>* srcptr = L.head;
    while (srcptr->next != NULL) {
        value = srcptr->next->data;
        destptr -> next = new Node<T>(value);

        // 内存分配失败，抛出异常
        if (destptr->next == NULL) {
            std::cout << "内存分配错误！\n";
            exit(MEMORY_ALLOCATION_ERROR);
        }
        destptr = destptr -> next;
        srcptr = srcptr->next;
    }
    destptr -> next = NULL;
}

/***********************************************************
* Function Name:   makeEmpty
* Function:        清空链表，释放所有节点的内存
* Input Parameter: 
* Returned Value:  
***********************************************************/
template <typename T>
void LinkList<T>::makeEmpty()
{
    Node<T>* q;
    while (head->next != NULL) {
        q = head->next;
        head->next = q->next;
        delete q;
    }
}

/***********************************************************
* Function Name:   Length
* Function:        获取链表的长度
* Input Parameter: 
* Returned Value:  返回链表的节点数（除头节点）
***********************************************************/
template <typename T>
int LinkList<T>::Length()
{
    Node<T>* p = head->next;
    int count = 0;
    while (p != NULL) {
        p = p->next;
        count++;
    }
    return count;
}

/***********************************************************
* Function Name:   Search
* Function:        查找链表中是否存在值为x的节点
* Input Parameter: x:要查找的值
* Returned Value:  返回找到的节点指针，如果未找到则返回NULL
***********************************************************/
template <typename T>
Node<T>* LinkList<T>::Search(const T x)
{
    Node<T>* current = head->next;
    while (current != NULL) {
        if (current->data == x)
            break;
        else
            current = current->next;
    }
    return current;
}

/***********************************************************
* Function Name:   Locate
* Function:        定位到链表中的第i个节点
* Input Parameter: i:要定位的节点索引
* Returned Value:  返回第i个节点的指针，如果未找到则返回NULL
***********************************************************/
template <typename T>
Node<T>* LinkList<T>::Locate(int i)
{
    if (i < 0)
        return NULL;
    Node<T>* current = head;
    int k = 0;
    while (current != NULL && k < i) {
        current = current->next;
        k++;
    }
    return current;
}

/***********************************************************
* Function Name:   getData
* Function:        获取链表中第i个节点的数据
* Input Parameter: i:节点索引
*                  x:存储获取的数据的引用
* Returned Value:  如果成功获取数据返回true，否则返回false
***********************************************************/
template <typename T>
bool LinkList<T>::getData(int i, T& x) {
    if (i <= 0)
        return false;
    Node<T>* current = Locate(i);
    if (current == NULL)
        return false;
    else {
        x = current->data;
        return true;
    }
}
/***********************************************************
* Function Name:   setData
* Function:        设置链表中第i个节点的数据
* Input Parameter: i:节点索引
*                  x :要设置的数据
* Returned Value:  如果成功设置数据返回true，否则返回false
***********************************************************/
template <typename T>
bool LinkList<T>::setData(int i,const T& x)
{
    if (i <= 0)
        return false;
    Node<T>* current = Locate(i);
    if (current == NULL)
        return false;
    current->data = x;
    return true;
}

/***********************************************************
* Function Name:   Insert
* Function:        在链表中第i个位置插入一个新节点
* Input Parameter: i:插入位置的索引
*                  x:要插入的数据
* Returned Value:  如果成功插入返回true，否则返回false
***********************************************************/
template <typename T>
bool LinkList<T>::Insert(int i, const T& x) {
    Node<T>* current = Locate(i-1);//要插入在第i个位置，需要定位到第i-1个节点
    if (current == NULL)
        return false;
    Node<T>* newNode = new(std::nothrow) Node<T>(x);

    // 内存分配失败，抛出异常
    if (newNode == NULL) {
        std::cout << "内存分配错误！\n";
        exit(MEMORY_ALLOCATION_ERROR);
    }
    newNode->next = current->next;
    current->next = newNode;
    return true;
}

/***********************************************************
* Function Name:   Remove
* Function:        删除链表中的第i个节点并获取该节点的数据
* Input Parameter: i:要删除的节点的索引
*                  x:存储删除节点的数据的引用
* Returned Value:  如果成功删除返回true，否则返回false
***********************************************************/
template <typename T>
bool LinkList<T>::Remove(int i,T& x) {
    Node<T>* current = Locate(i - 1);//要删除第i个结点，需要定位到第i-1个结点
    if (current == NULL || current->next == NULL)
        return false;
    Node<T>* del = current->next;
    current->next = del->next;
    x = del->data;
    delete del;
    return true;
}

/***********************************************************
* Function Name:   output
* Function:        输出链表中所有节点的数据
* Input Parameter: 
* Returned Value:  
***********************************************************/
template <typename T>
void LinkList<T>::output() {
    Node<T>* current = head->next;
    while (current != NULL) {
        std::cout << current->data << std::endl;
        current = current->next;
    }
}

/***********************************************************
* Function Name:   inputFront
* Function:        在链表的前面插入一个新节点
* Input Parameter: x:要插入的数据
* Returned Value:
***********************************************************/
template <typename T>
void LinkList<T>::inputFront(const T& x)
{
    Node<T>* newNode = new(std::nothrow) Node<T>(x);

    // 内存分配失败，抛出异常
    if (newNode == NULL) {
        std::cout << "内存分配错误！\n";
        exit(MEMORY_ALLOCATION_ERROR);
    }
    newNode->next = head->next;// 新节点的next指向当前头节点的下一个节点
    head->next = newNode; // 将链表的头节点的next指向新节点
}

/***********************************************************
* Function Name:   inputRear
* Function:        在链表的后面插入一个新节点
* Input Parameter: x:要插入的数据
* Returned Value:  
***********************************************************/
template <typename T>
void LinkList<T>::inputRear(const T& x)
{
    Node<T>* newNode = new(std::nothrow) Node<T>(x);

    // 内存分配失败，抛出异常
    if (newNode == NULL) {
        std::cout << "内存分配错误！\n";
        exit(MEMORY_ALLOCATION_ERROR);
    }
    Node<T>* current = head;
    while (current->next != NULL)
        current= current->next;
    current->next = newNode;
    newNode->next = NULL;
    
}

/***********************************************************
* Function Name:   operator[]
* Function:        下标运算符重载，根据索引获取节点数据
* Input Parameter: index:节点索引
* Returned Value:  返回对应节点的数据，如果索引超出范围则抛出异常
***********************************************************/
template <typename T>
T& LinkList<T>::operator[](int index) {
    Node<T>* current = head->next;
    int count = 1;
    while (current != NULL) {
        if (count == index) {
            return current->data;
        }
        current = current->next;
        count++;
    }

    // 如果索引超出链表长度，抛出异常
    std::cout << "索引超出链表长度，非法访问！";
    exit(OUT_OF_RANGE);
}

/***********************************************************
* Function Name:   operator=
* Function:        赋值运算符重载，实现链表的复制
* Input Parameter: other:要复制的链表
* Returned Value:  返回当前对象的引用
***********************************************************/
template <typename T>
LinkList<T>& LinkList<T>::operator=(const LinkList<T>& other)
{
    if (this == &other)
        return *this;// 检测自赋值

    // 清除现有链表
    makeEmpty();

    // 复制链表
    if (other.head == NULL) {
        head = NULL;
    }
    else {
        Node<T>* current_new = head;
        Node<T>* current_old = other.head->next;

        while (current_old != NULL) {
            current_new->next = new(std::nothrow) Node<T>(current_old->data);
            if (current_new == NULL) {
                std::cout << "内存分配错误！\n";
                exit(MEMORY_ALLOCATION_ERROR);
            }
            current_new = current_new->next;
            current_old = current_old->next;
        }
    }
    return *this;  // 返回当前对象的引用
}
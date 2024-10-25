#pragma once
/***********************************************************
* File:     my_singly_link_list.h
* Author:   Xiaolong Ma(��С��)
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
* Function:      ������ṹ��
* Template:      T - �ڵ���������
* Data Members:  data - �洢�ڵ������
*                next - ָ����һ���ڵ��ָ��
***********************************************************/
template <typename T>
struct Node {
    T data;// �ڵ�����
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
* Function:         �����࣬�ṩ����Ļ�������
* Template:         T - �����д洢����������
* Data Members:     head - ָ������ͷ�ڵ��ָ��
* Member Functions:
*                   LinkList() - Ĭ�Ϲ��캯��
*                   LinkList(const T& x) - ����ʼֵ�Ĺ��캯��
*                   LinkList(LinkList<T>& L) - �������캯��
*                   ~LinkList() - ��������
*                   void makeEmpty() - �������
*                   int Length() - ����������
*                   Node<T>* getHead() - ��ȡ����ͷ�ڵ�
*                   Node<T>* Search(const T x) - ���ҽڵ�
*                   Node<T>* Locate(int i) - ��λ�ڵ�
*                   bool getData(int i, T& x) - ��ȡ�ڵ�����
*                   bool setData(int i, const T& x) - ���ýڵ�����
*                   bool Insert(int i, const T& x) - ����ڵ�
*                   bool Remove(int i, T& x) - ɾ���ڵ�
*                   bool IsEmpty() - ��������Ƿ�Ϊ��
*                   bool IsFull() - ��������Ƿ���
*                   void inputFront(const T& x) - ��ǰ������ڵ�����
*                   void inputRear(const T& x) - �Ӻ�������ڵ�����
*                   void output() - �����������
*                   LinkList<T>& operator=(const LinkList<T>& other) - ��ֵ���������
*                   T& operator[](int index) - �±����������
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
* Function :        ���캯����ͷ��㲻�������ݣ�ֻ���ڶ�λ
* Input Parameter : 
* Returned Value :
***********************************************************/
template <typename T>
LinkList<T>::LinkList(){
    head = new(std::nothrow) Node<T>;

    // �ڴ����ʧ�ܣ��׳��쳣
    if (head == NULL) {
        std::cout << "�ڴ�������\n";
        exit(MEMORY_ALLOCATION_ERROR);
    }
}
/********************************************************
*Function Name :    LinkList
* Function :        ���ι��캯��
* Input Parameter : x
* Returned Value :
***********************************************************/
template <typename T>
LinkList<T>::LinkList(const T& x){
    head = new(std::nothrow) Node<T>;

    // �ڴ����ʧ�ܣ��׳��쳣
    if (head == NULL) {
        std::cout << "�ڴ�������\n";
        exit(MEMORY_ALLOCATION_ERROR);
    }

    Node<T>newNode = new(std::nothrow) Node<T>(x);
    if (newNode == NULL) {
        std::cout << "�ڴ�������\n";
        exit(MEMORY_ALLOCATION_ERROR);
    }
    head->next = newNode;
}
/***********************************************************
* Function Name:   LinkList
* Function:        �������캯������������L��Ԫ��
* Input Parameter: L - �����Ƶ�����
* Returned Value:  
***********************************************************/
template <typename T>
LinkList<T>::LinkList(LinkList& L) {
    Node<T>* destptr = head = new Node<T>;// �����������ͷ�ڵ�
    if (head == NULL) {
        std::cout << "�ڴ�������\n";
        exit(MEMORY_ALLOCATION_ERROR);
    }
    T value;
    Node<T>* srcptr = L.head;
    while (srcptr->next != NULL) {
        value = srcptr->next->data;
        destptr -> next = new Node<T>(value);

        // �ڴ����ʧ�ܣ��׳��쳣
        if (destptr->next == NULL) {
            std::cout << "�ڴ�������\n";
            exit(MEMORY_ALLOCATION_ERROR);
        }
        destptr = destptr -> next;
        srcptr = srcptr->next;
    }
    destptr -> next = NULL;
}

/***********************************************************
* Function Name:   makeEmpty
* Function:        ��������ͷ����нڵ���ڴ�
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
* Function:        ��ȡ����ĳ���
* Input Parameter: 
* Returned Value:  ��������Ľڵ�������ͷ�ڵ㣩
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
* Function:        �����������Ƿ����ֵΪx�Ľڵ�
* Input Parameter: x:Ҫ���ҵ�ֵ
* Returned Value:  �����ҵ��Ľڵ�ָ�룬���δ�ҵ��򷵻�NULL
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
* Function:        ��λ�������еĵ�i���ڵ�
* Input Parameter: i:Ҫ��λ�Ľڵ�����
* Returned Value:  ���ص�i���ڵ��ָ�룬���δ�ҵ��򷵻�NULL
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
* Function:        ��ȡ�����е�i���ڵ������
* Input Parameter: i:�ڵ�����
*                  x:�洢��ȡ�����ݵ�����
* Returned Value:  ����ɹ���ȡ���ݷ���true�����򷵻�false
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
* Function:        ���������е�i���ڵ������
* Input Parameter: i:�ڵ�����
*                  x :Ҫ���õ�����
* Returned Value:  ����ɹ��������ݷ���true�����򷵻�false
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
* Function:        �������е�i��λ�ò���һ���½ڵ�
* Input Parameter: i:����λ�õ�����
*                  x:Ҫ���������
* Returned Value:  ����ɹ����뷵��true�����򷵻�false
***********************************************************/
template <typename T>
bool LinkList<T>::Insert(int i, const T& x) {
    Node<T>* current = Locate(i-1);//Ҫ�����ڵ�i��λ�ã���Ҫ��λ����i-1���ڵ�
    if (current == NULL)
        return false;
    Node<T>* newNode = new(std::nothrow) Node<T>(x);

    // �ڴ����ʧ�ܣ��׳��쳣
    if (newNode == NULL) {
        std::cout << "�ڴ�������\n";
        exit(MEMORY_ALLOCATION_ERROR);
    }
    newNode->next = current->next;
    current->next = newNode;
    return true;
}

/***********************************************************
* Function Name:   Remove
* Function:        ɾ�������еĵ�i���ڵ㲢��ȡ�ýڵ������
* Input Parameter: i:Ҫɾ���Ľڵ������
*                  x:�洢ɾ���ڵ�����ݵ�����
* Returned Value:  ����ɹ�ɾ������true�����򷵻�false
***********************************************************/
template <typename T>
bool LinkList<T>::Remove(int i,T& x) {
    Node<T>* current = Locate(i - 1);//Ҫɾ����i����㣬��Ҫ��λ����i-1�����
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
* Function:        ������������нڵ������
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
* Function:        �������ǰ�����һ���½ڵ�
* Input Parameter: x:Ҫ���������
* Returned Value:
***********************************************************/
template <typename T>
void LinkList<T>::inputFront(const T& x)
{
    Node<T>* newNode = new(std::nothrow) Node<T>(x);

    // �ڴ����ʧ�ܣ��׳��쳣
    if (newNode == NULL) {
        std::cout << "�ڴ�������\n";
        exit(MEMORY_ALLOCATION_ERROR);
    }
    newNode->next = head->next;// �½ڵ��nextָ��ǰͷ�ڵ����һ���ڵ�
    head->next = newNode; // �������ͷ�ڵ��nextָ���½ڵ�
}

/***********************************************************
* Function Name:   inputRear
* Function:        ������ĺ������һ���½ڵ�
* Input Parameter: x:Ҫ���������
* Returned Value:  
***********************************************************/
template <typename T>
void LinkList<T>::inputRear(const T& x)
{
    Node<T>* newNode = new(std::nothrow) Node<T>(x);

    // �ڴ����ʧ�ܣ��׳��쳣
    if (newNode == NULL) {
        std::cout << "�ڴ�������\n";
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
* Function:        �±���������أ�����������ȡ�ڵ�����
* Input Parameter: index:�ڵ�����
* Returned Value:  ���ض�Ӧ�ڵ�����ݣ��������������Χ���׳��쳣
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

    // ����������������ȣ��׳��쳣
    std::cout << "�������������ȣ��Ƿ����ʣ�";
    exit(OUT_OF_RANGE);
}

/***********************************************************
* Function Name:   operator=
* Function:        ��ֵ��������أ�ʵ������ĸ���
* Input Parameter: other:Ҫ���Ƶ�����
* Returned Value:  ���ص�ǰ���������
***********************************************************/
template <typename T>
LinkList<T>& LinkList<T>::operator=(const LinkList<T>& other)
{
    if (this == &other)
        return *this;// ����Ը�ֵ

    // �����������
    makeEmpty();

    // ��������
    if (other.head == NULL) {
        head = NULL;
    }
    else {
        Node<T>* current_new = head;
        Node<T>* current_old = other.head->next;

        while (current_old != NULL) {
            current_new->next = new(std::nothrow) Node<T>(current_old->data);
            if (current_new == NULL) {
                std::cout << "�ڴ�������\n";
                exit(MEMORY_ALLOCATION_ERROR);
            }
            current_new = current_new->next;
            current_old = current_old->next;
        }
    }
    return *this;  // ���ص�ǰ���������
}
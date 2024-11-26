#ifndef MY_MIN_HEAP_H
#define MY_MIN_HEAP_H
/***********************************************************
* File:     my_min_heap.h
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Clion2024
* Function: Min Heap
* Date:     2024.11.11
* Update:   2024.11.23
***********************************************************/
#include<cassert>
#include<iostream>

/*************************************************************
* Class Name: MinHeap
* Class Function: 实现一个通用的最小堆（模板类），支持插入、删除等操作。
*************************************************************/
template<typename T>
class MinHeap {
public:
    MinHeap(int maxSize);
    MinHeap(T arr[],int n);
    ~MinHeap(){delete[] heap;};
    bool Insert(const T& x);
    bool Remove(T& x);
    bool isEmpty()const{return currentSize==0;}
    bool isFull()const{return currentSize==maxHeapSize;}
    void makeEmpty(){delete[] heap; currentSize=0;}
    int Size(){return currentSize;}
    MinHeap<T>& operator=(const MinHeap<T>& R);
private:
    enum{DefaultSize = 10};
    T* heap;
    int currentSize;
    int maxHeapSize;
    void FilterDown(int start,int end_of_heap);
    void FilterUp(int start);
};

/*********************************************************
* Constructor:      MinHeap
* Function:         初始化一个空堆，指定堆的最大容量。
* Input Parameters: maxSize - 堆的最大容量。
*********************************************************/
template<typename T>
MinHeap<T>::MinHeap(int maxSize)
{
    maxHeapSize =  maxSize>DefaultSize?maxSize:DefaultSize;
    heap = new(std::nothrow) T[maxHeapSize];
    assert(heap!=nullptr);
    currentSize = 0;
}

/*********************************************************
* Constructor:     MinHeap
* Function:        使用一个数组构建最小堆。
* Input Parameters:
*                   arr - 输入数组。
*                    n - 数组的长度。
*********************************************************/
template<typename T>
MinHeap<T>::MinHeap(T arr[], int n)
{
    maxHeapSize = n>DefaultSize?n:DefaultSize;
    heap = new(std::nothrow) T[maxHeapSize];
    assert(heap!=nullptr);
    for(int i=0;i<n;i++)
        heap[i] = arr[i]; // 将数组元素复制到堆中
    currentSize = n;
    int currentPos =(currentSize-2)/2;
    while(currentPos>=0) {
        FilterDown(currentPos,currentSize-1);
        currentPos--;
    }
}

/*********************************************************
* Function Name:    FilterUp
* Function:         从堆底向上调整堆，恢复最小堆性质。
* Input Parameters: start - 起始节点索引。
*********************************************************/
template<typename T>
void MinHeap<T>::FilterDown(int start,int end_of_heap)
{
    int i = start; // 当前节点索引
    int j = 2*i+1; // 左孩子索引
    T temp=heap[i];; // 暂存当前节点的值
    while(j<=end_of_heap) {
        if(j<end_of_heap&&heap[j]>heap[j+1])
            j++;
        if(temp <= heap[j])
            break;
        else {
            heap[i] = heap[j];// 子节点上移
            i = j;
            j = 2 * j + 1; // 继续向下调整
        }
    }
    heap[i] = temp;
}

/*********************************************************
* Function Name:     Insert
* Function:          向最小堆中插入一个新元素。
* Input Parameters: x - 待插入的元素。
* Returned Value:   true - 插入成功。
*********************************************************/
template<typename T>
bool MinHeap<T>::Insert(const T &x)
{
    assert(currentSize!=maxHeapSize);
    heap[currentSize] = x;
    FilterUp(currentSize);
    currentSize++;
    return true;
}

/*********************************************************
* Function Name:     FilterUp
* Function:         从堆底向上调整堆，恢复最小堆性质。
* Input Parameters: start - 起始节点索引。
*********************************************************/
template<typename T>
void MinHeap<T>::FilterUp(int start)
{
    int j=start;
    int i = (j-1)/2;
    T temp=heap[j];
    while(j>0) {
        if(heap[i] <= temp)// 父节点值小于当前节点，调整完成
            break;
        else {
            heap[j] = heap[i];// 父节点下移
            j = i;
            i = (i-1)/2;
        }
    }
    heap[j] = temp;
}

/*********************************************************
* Function Name:    Remove
* Function:         删除堆顶元素（最小值）。
* Input Parameters: x - 用于接收删除的堆顶元素。
* Returned Value:   true - 删除成功。
*********************************************************/
template<typename T>
bool MinHeap<T>::Remove(T &x)
{
    assert(currentSize!=0);// 确保堆不为空
    x = heap[0];
    heap[0] = heap[currentSize-1];
    currentSize--;
    FilterDown(0,currentSize-1);
    return true;
}

/*************************************************************
* Function Name: operator=
* Function: 重载赋值运算符，实现堆对象的深拷贝。
*************************************************************/
template <typename T>
MinHeap<T>& MinHeap<T>::operator=(const MinHeap<T> &R)
{
    if (this != &R) {
        // 检查是否自赋值
        delete[] heap; // 释放当前对象的内存

        maxHeapSize = R.maxHeapSize;
        currentSize = R.currentSize;

        // 为新堆分配内存
        heap = new(std::nothrow) T[maxHeapSize];
        assert(heap != nullptr);

        // 复制元素
        for (int i = 0; i < currentSize; ++i) {
            heap[i] = R.heap[i];
        }
    }
    return *this;
}

#endif //MY_MIN_HEAP_H
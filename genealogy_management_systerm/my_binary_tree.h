#ifndef MY_BINARY_TREE
#define MY_BINARY_TREE
/***********************************************************
* File:     my_binary_tree.h
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: template of binary tree
* Date:     2024.10.21
* Update:   2024.10.21
***********************************************************/

#include <iostream>
#include <cassert>


/***********************************************************
* Struct Name:   BinTreeNode
* Function:      二叉树节点结构体
* Template:      T - 节点数据类型
* Data Members:  parent - 指向父节点的指针
*                data - 存储节点的数据
*                leftChild - 指向左子节点的指针
*                rightChild - 指向右子节点的指针
***********************************************************/
template <typename T>
struct BinTreeNode {
	BinTreeNode<T>* parent;// 指向父节点的指针
	T data;// 节点数据
	BinTreeNode<T>* leftChild, * rightChild;
	// 默认构造函数，初始化节点指针
	BinTreeNode() :parent(nullptr),leftChild(nullptr), rightChild(nullptr) {}
	// 构造函数，创建节点并初始化数据和指针
	BinTreeNode(T x, BinTreeNode<T>* par = nullptr, BinTreeNode<T>* left =nullptr, BinTreeNode<T>* right = nullptr) : data{x},parent(par), leftChild(left), rightChild(right) { }
};

/***********************************************************
* Class Name:       BinaryTree
* Function:         二叉树类，提供二叉树的基本操作
* Template:         T - 二叉树中存储的数据类型
* Data Members:     root - 指向根节点的指针
* Member Functions:
*                   BinaryTree() - 默认构造函数
*                   BinaryTree(T& item) - 带参数的构造函数
*                   ~BinaryTree() - 析构函数
*                   bool IsEmpty() - 检查树是否为空
*                   BinTreeNode<T>* Parent(BinTreeNode<T>* current) - 获取当前节点的父节点
*                   BinTreeNode<T>* LeftChild(BinTreeNode<T>* current) - 获取当前节点的左子节点
*                   BinTreeNode<T>* RightChild(BinTreeNode<T>* current) - 获取当前节点的右子节点
*                   bool rootInsert(const T& item) - 在树根插入新节点
*                   bool leftInsert(BinTreeNode<T>* current, const T& item) - 在指定节点的左侧插入新节点
*                   bool rightInsert(BinTreeNode<T>* current, const T& item) - 在指定节点的右侧插入新节点
*                   void StoreRoot(BinTreeNode<T>* subTree) - 存储根节点
*                   BinTreeNode<T>* GetRoot() - 获取根节点
*                   BinTreeNode<T>* Search(const T& item, BinTreeNode<T>* subTree = root) - 在树中查找指定值的节点
***********************************************************/
template <typename T>
class BinaryTree {
public:
	BinaryTree():root(nullptr){}// 默认构造函数
	BinaryTree(T& item); // 带参数的构造函数
	~BinaryTree(){Destory(root); }// 析构函数，释放内存
	bool IsEmpty() { return root == nullptr; }// 检查树是否为空

	BinTreeNode<T>* Parent(BinTreeNode<T>* current);

	BinTreeNode<T>* LeftChild(BinTreeNode<T>* current);

	BinTreeNode<T>* RightChild(BinTreeNode<T>* current);

	T Data(BinTreeNode<T>* current);

	bool rootInsert(const T& item);
	bool leftInsert(BinTreeNode<T>* current, const T& item);
	bool rightInsert(BinTreeNode<T>* current, const T& item);
	void StoreRoot(BinTreeNode<T>* subTree) { root = subTree; }
	void ChangeLeftChild(BinTreeNode<T>* parent,BinTreeNode<T>* child){assert(parent!=nullptr);parent->leftChild=child;}
	void ChangeRightChild(BinTreeNode<T>* parent,BinTreeNode<T>* child){assert(parent!=nullptr);parent->rightChild=child;}
	BinTreeNode<T>* GetRoot() { return root; }
	BinTreeNode<T>* Search(const T& item, BinTreeNode<T>* subTree);
	void Destory(BinTreeNode<T>* subTree); // 释放树的内存

private:
	BinTreeNode<T>* root;// 指向树的根节点

};

/***********************************************************
* Function Name:   BinaryTree
* Function:        带参数的构造函数，创建二叉树并初始化根节点
* Input Parameter: item - 要插入的节点数据
* Returned Value:
***********************************************************/
template <typename T>
BinaryTree<T>::BinaryTree(T& item)
{
	root = new(std::nothrow) BinTreeNode<T>(item);// 创建根节点
	assert(root != nullptr);
}

/***********************************************************
* Function Name:   Parent
* Function:        获取指定节点的父节点
* Input Parameter: current - 当前节点
* Returned Value:  返回当前节点的父节点
***********************************************************/
template <typename T>
BinTreeNode<T>* BinaryTree<T>::Parent(BinTreeNode<T>* current)
{
	if (current == nullptr)
		return current;
	return current->parent;
}

/***********************************************************
* Function Name:   LeftChild
* Function:        获取指定节点的左子节点
* Input Parameter: current - 当前节点
* Returned Value:  返回当前节点的左子节点
***********************************************************/
template <typename T>
BinTreeNode<T>* BinaryTree<T>::LeftChild(BinTreeNode<T>* current)
{
	if (current == nullptr)
		return current;
	return current->leftChild;
}

/***********************************************************
* Function Name:   RightChild
* Function:        获取指定节点的右子节点
* Input Parameter: current - 当前节点
* Returned Value:  返回当前节点的右子节点
***********************************************************/
template <typename T>
BinTreeNode<T>* BinaryTree<T>::RightChild(BinTreeNode<T>* current)
{
	if (current == nullptr)
		return current;
	return current->rightChild;
}

template <typename T>
T BinaryTree<T>::Data(BinTreeNode<T>* current)
{
	assert(current != nullptr);
	return current->data;
}
/***********************************************************
* Function Name:   rootInsert
* Function:        在树的根节点插入新节点
* Input Parameter: item - 要插入的新节点数据
* Returned Value:  如果插入成功返回true，否则返回false
***********************************************************/
template <typename T>
bool BinaryTree<T>::rootInsert(const T& item)
{
	root = new(std::nothrow) BinTreeNode<T>(item);
	assert(root != nullptr);
	return true; // 插入成功
}

/***********************************************************
* Function Name:   leftInsert
* Function:        在指定节点的左侧插入新节点
* Input Parameter: current - 当前节点, item - 要插入的新节点数据
* Returned Value:  如果插入成功返回true，否则返回false
***********************************************************/
template <typename T>
bool BinaryTree<T>::leftInsert(BinTreeNode<T>* current, const T& item)
{
	assert(root != nullptr);
	if (current == nullptr || current->leftChild != nullptr)
		return false;// 当前节点为空或左子节点已存在，插入失败
	current->leftChild = new(std::nothrow) BinTreeNode<T>(item,current);
	assert(current->leftChild != nullptr);
	return true; // 插入成功
}

/***********************************************************
* Function Name:   rightInsert
* Function:        在指定节点的右侧插入新节点
* Input Parameter: current - 当前节点, item - 要插入的新节点数据
* Returned Value:  如果插入成功返回true，否则返回false
***********************************************************/
template <typename T>
bool BinaryTree<T>::rightInsert(BinTreeNode<T>* current, const T& item)
{
	assert(root != nullptr);
	if (current ==nullptr || current->rightChild != nullptr)
		return false;
	current->rightChild = new(std::nothrow) BinTreeNode<T>(item, current);
	assert(current->rightChild != nullptr);
	return true;
}

/***********************************************************
* Function Name:   Search
* Function:        在树中查找指定值的节点
* Input Parameter: item - 要查找的值, subTree - 子树的根节点
* Returned Value:  返回找到的节点，如果没有找到则返回NULL
***********************************************************/
template <typename T>
BinTreeNode<T>* BinaryTree<T>::Search(const T& item, BinTreeNode<T>* subTree)
{
	if (subTree == nullptr)
		return nullptr;// 子树为空，返回NUL
	if (subTree->data == item)
		return subTree;// 找到节点，返回
	BinTreeNode<T>* found = Search(item, subTree->leftChild);// 在左子树中查找
	if (found != nullptr)
		return found; // 如果在左子树中找到，返回结果
	return Search(item, subTree->rightChild);// 在右子树中查找
}

/***********************************************************
* Function Name:   Destory
* Function:        释放树的内存
* Input Parameter: root - 树的根节点
***********************************************************/
template <typename T>
void BinaryTree<T>::Destory(BinTreeNode<T>* subTree)
{
	if (subTree != nullptr) {
		if (subTree->leftChild !=nullptr)
			Destory(subTree->leftChild);// 递归释放左子树
		if (subTree->rightChild != nullptr)
			Destory(subTree->rightChild);// 递归释放右子树
		delete subTree; // 释放当前节点
		subTree = nullptr;
	}
}

#endif //MY_BINARY_TREE
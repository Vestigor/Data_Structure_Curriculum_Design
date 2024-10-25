#pragma once
/***********************************************************
* File:     my_binary_tree.h
* Author:   Xiaolong Ma(��С��)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: template of binary tree
* Date:     2024.10.21
* Update:   2024.10.21
***********************************************************/

#include <iostream>

#define MEMORY_ALLOCATION_ERROR -1
#define FIND_NO_ROOT -2

/***********************************************************
* Struct Name:   BinTreeNode
* Function:      �������ڵ�ṹ��
* Template:      T - �ڵ���������
* Data Members:  parent - ָ�򸸽ڵ��ָ��
*                data - �洢�ڵ������
*                leftChild - ָ�����ӽڵ��ָ��
*                rightChild - ָ�����ӽڵ��ָ��
***********************************************************/
template <typename T>
struct BinTreeNode {
	BinTreeNode<T>* parent;// ָ�򸸽ڵ��ָ��
	T data;// �ڵ�����
	BinTreeNode<T>* leftChild, * rightChild;
	// Ĭ�Ϲ��캯������ʼ���ڵ�ָ��
	BinTreeNode() :parent(NULL),leftChild(NULL), rightChild(NULL) {}
	// ���캯���������ڵ㲢��ʼ�����ݺ�ָ��
	BinTreeNode(T x, BinTreeNode<T>* par = NULL, BinTreeNode<T>* left = NULL, BinTreeNode<T>* right = NULL) : data{x},parent(par), leftChild(left), rightChild(right) { }
};

/***********************************************************
* Class Name:       BinaryTree
* Function:         �������࣬�ṩ�������Ļ�������
* Template:         T - �������д洢����������
* Data Members:     root - ָ����ڵ��ָ��
* Member Functions:
*                   BinaryTree() - Ĭ�Ϲ��캯��
*                   BinaryTree(T& item) - �������Ĺ��캯��
*                   ~BinaryTree() - ��������
*                   bool IsEmpty() - ������Ƿ�Ϊ��
*                   BinTreeNode<T>* Parent(BinTreeNode<T>* current) - ��ȡ��ǰ�ڵ�ĸ��ڵ�
*                   BinTreeNode<T>* LeftChild(BinTreeNode<T>* current) - ��ȡ��ǰ�ڵ�����ӽڵ�
*                   BinTreeNode<T>* RightChild(BinTreeNode<T>* current) - ��ȡ��ǰ�ڵ�����ӽڵ�
*                   bool rootInsert(const T& item) - �����������½ڵ�
*                   bool leftInsert(BinTreeNode<T>* current, const T& item) - ��ָ���ڵ���������½ڵ�
*                   bool rightInsert(BinTreeNode<T>* current, const T& item) - ��ָ���ڵ���Ҳ�����½ڵ�
*                   void StoreRoot(BinTreeNode<T>* subTree) - �洢���ڵ�
*                   BinTreeNode<T>* GetRoot() - ��ȡ���ڵ�
*                   BinTreeNode<T>* Search(const T& item, BinTreeNode<T>* subTree = root) - �����в���ָ��ֵ�Ľڵ�
***********************************************************/
template <typename T>
class BinaryTree {
public:
	BinaryTree():root(NULL){}// Ĭ�Ϲ��캯��
	BinaryTree(T& item); // �������Ĺ��캯��
	~BinaryTree(){Destory(root); }// �����������ͷ��ڴ�
	bool IsEmpty() { return root == NULL; }// ������Ƿ�Ϊ��
	//int Heigth(BinTreeNode<T>* subTree=root) { return Heigth(subTree); }
	//int Size(BinTreeNode<T>* subTree = root) { return Size(subTree); }
	BinTreeNode<T>* Parent(BinTreeNode<T>* current);
	BinTreeNode<T>* LeftChild(BinTreeNode<T>* current);
	BinTreeNode<T>* RightChild(BinTreeNode<T>* current);
	bool rootInsert(const T& item);
	bool leftInsert(BinTreeNode<T>* current, const T& item);
	bool rightInsert(BinTreeNode<T>* current, const T& item);
	void StoreRoot(BinTreeNode<T>* subTree) { root = subTree; }
	BinTreeNode<T>* GetRoot() { return root; }
	BinTreeNode<T>* Search(const T& item, BinTreeNode<T>* subTree = root);
private:
	BinTreeNode<T>* root;// ָ�����ĸ��ڵ�
	void Destory(BinTreeNode<T>* root); // �ͷ������ڴ�
};

/***********************************************************
* Function Name:   BinaryTree
* Function:        �������Ĺ��캯������������������ʼ�����ڵ�
* Input Parameter: item - Ҫ����Ľڵ�����
* Returned Value:
***********************************************************/
template <typename T>
BinaryTree<T>::BinaryTree(T& item)
{
	root = new(std::nothrow) BinTreeNode<T>(item);// �������ڵ�
	if (root == NULL) {
		std::cout << "�ڴ����ʧ�ܣ�" << std::endl;
		exit(MEMORY_ALLOCATION_ERROR);// �ڴ����ʧ�ܣ��׳��쳣
	}
}

/***********************************************************
* Function Name:   Parent
* Function:        ��ȡָ���ڵ�ĸ��ڵ�
* Input Parameter: current - ��ǰ�ڵ�
* Returned Value:  ���ص�ǰ�ڵ�ĸ��ڵ�
***********************************************************/
template <typename T>
BinTreeNode<T>* BinaryTree<T>::Parent(BinTreeNode<T>* current)
{
	if (current == NULL)
		return current;
	return current->parent;
}

/***********************************************************
* Function Name:   LeftChild
* Function:        ��ȡָ���ڵ�����ӽڵ�
* Input Parameter: current - ��ǰ�ڵ�
* Returned Value:  ���ص�ǰ�ڵ�����ӽڵ�
***********************************************************/
template <typename T>
BinTreeNode<T>* BinaryTree<T>::LeftChild(BinTreeNode<T>* current)
{
	if (current == NULL)
		return current;
	return current->leftChild;
}

/***********************************************************
* Function Name:   RightChild
* Function:        ��ȡָ���ڵ�����ӽڵ�
* Input Parameter: current - ��ǰ�ڵ�
* Returned Value:  ���ص�ǰ�ڵ�����ӽڵ�
***********************************************************/
template <typename T>
BinTreeNode<T>* BinaryTree<T>::RightChild(BinTreeNode<T>* current)
{
	if (current == NULL)
		return current;
	return current->rightChild;
}

/***********************************************************
* Function Name:   rootInsert
* Function:        �����ĸ��ڵ�����½ڵ�
* Input Parameter: item - Ҫ������½ڵ�����
* Returned Value:  �������ɹ�����true�����򷵻�false
***********************************************************/
template <typename T>
bool BinaryTree<T>::rootInsert(const T& item)
{
	root = new(std::nothrow) BinTreeNode<T>(item);
	if (root == NULL) {
		std::cout << "�ڴ����ʧ�ܣ�" << std::endl;
		exit(MEMORY_ALLOCATION_ERROR);
	}
	return true; // ����ɹ�
}

/***********************************************************
* Function Name:   leftInsert
* Function:        ��ָ���ڵ���������½ڵ�
* Input Parameter: current - ��ǰ�ڵ�, item - Ҫ������½ڵ�����
* Returned Value:  �������ɹ�����true�����򷵻�false
***********************************************************/
template <typename T>
bool BinaryTree<T>::leftInsert(BinTreeNode<T>* current, const T& item)
{
	if (root == NULL) {
		std::cout << "û�н�������㣡" << std::endl;
		exit(FIND_NO_ROOT);// ������ڵ㲻���ڣ��׳��쳣
	}
	if (current == NULL || current->leftChild != NULL)
		return false;// ��ǰ�ڵ�Ϊ�ջ����ӽڵ��Ѵ��ڣ�����ʧ��
	current->leftChild = new(std::nothrow) BinTreeNode<T>(item,current);
	if (current->leftChild == NULL) {
		std::cout << "�ڴ����ʧ�ܣ�" << std::endl;
		exit(MEMORY_ALLOCATION_ERROR);// �ڴ����ʧ�ܣ��׳��쳣
	}
	return true; // ����ɹ�
}

/***********************************************************
* Function Name:   rightInsert
* Function:        ��ָ���ڵ���Ҳ�����½ڵ�
* Input Parameter: current - ��ǰ�ڵ�, item - Ҫ������½ڵ�����
* Returned Value:  �������ɹ�����true�����򷵻�false
***********************************************************/
template <typename T>
bool BinaryTree<T>::rightInsert(BinTreeNode<T>* current, const T& item)
{
	if (root == NULL) {
		std::cout << "û�н�������㣡" << std::endl;
		exit(FIND_NO_ROOT);
	}
	if (current == NULL || current->rightChild != NULL)
		return false;
	current->rightChild = new(std::nothrow) BinTreeNode<T>(item, current);
	if (current->rightChild == NULL) {
		std::cout << "�ڴ����ʧ�ܣ�" << std::endl;
		exit(MEMORY_ALLOCATION_ERROR);
	}
	return true;
}

/***********************************************************
* Function Name:   Search
* Function:        �����в���ָ��ֵ�Ľڵ�
* Input Parameter: item - Ҫ���ҵ�ֵ, subTree - �����ĸ��ڵ�
* Returned Value:  �����ҵ��Ľڵ㣬���û���ҵ��򷵻�NULL
***********************************************************/
template <typename T>
BinTreeNode<T>* BinaryTree<T>::Search(const T& item, BinTreeNode<T>* subTree)
{
	if (subTree == NULL)
		return NULL;// ����Ϊ�գ�����NUL
	if (subTree->data == item)
		return subTree;// �ҵ��ڵ㣬����
	BinTreeNode<T>* found = findNode(item, subTree->leftChild);// ���������в���
	if (found != NULL)
		return found; // ��������������ҵ������ؽ��
	return findNode(item, subTree->rightChild)// ���������в���
}

/***********************************************************
* Function Name:   Destory
* Function:        �ͷ������ڴ�
* Input Parameter: root - ���ĸ��ڵ�
***********************************************************/
template <typename T>
void BinaryTree<T>::Destory(BinTreeNode<T>* subTree)
{
	if (subTree != NULL) {
		if (subTree->leftChild != NULL)
			Destory(subTree->leftChild);// �ݹ��ͷ�������
		if (subTree->rightChild != NULL)
			Destory(subTree->rightChild);// �ݹ��ͷ�������
		delete subTree; // �ͷŵ�ǰ�ڵ�
		subTree = NULL;
	}
}

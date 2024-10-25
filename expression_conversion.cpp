/***********************************************************
* File:     expression_conversion.cpp
* Author:   Xiaolong Ma(��С��)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: expression conversion
* Date:     2024.10.23
* Update:   2024.10.23
***********************************************************/

#include <iostream>
#include <cstring>
#include "my_stack.h"
#include "my_binary_tree.h"
#include "my_string.h"

#define MAX_SIZE 100// ������ʽ������ַ���
#define MAX_NUM 20 // ���ʽ��Ԫ�ص��������
#define INT_MAX 2147483647// ���������ֵ

/***********************************************************
* Function Name:   PostorderTraversal
* Function:        ����������ʽ��
* Input Parameter: tree - ���ʽ��
***********************************************************/
void PostorderTraversal(BinaryTree<mine::String>& tree)
{
    Stack<BinTreeNode<mine::String>*> s1, s2;// ��������ջ���ڱ���
    BinTreeNode<mine::String>* root = tree.GetRoot();// ��ȡ���ĸ��ڵ�
    s1.Push(root); // �����ڵ�ѹ���һ��ջ

    // ���б���
    while (!s1.IsEmpty()) {
        BinTreeNode<mine::String>* node = s1.getTop(); // ��ȡջ���ڵ�
        s2.Push(node); // ���ڵ�ѹ��ڶ���ջ
        s1.Pop();
        // ��ѹ�����ӽڵ㣬��ѹ�����ӽڵ�
        if (node->leftChild) {
            s1.Push(node->leftChild);
        }
        if (node->rightChild) {
            s1.Push(node->rightChild);
        }
    }

    // ��ӡ����������
    std::cout << "��׺���ʽΪ��\n";
    while (!s2.IsEmpty()) {
        std::cout << s2.getTop()->data << " "; // ��ӡ��ǰ�ڵ������
        s2.Pop();
    }
}
/***********************************************************
* Function Name:   LegalCharacter
* Function:        ����ַ��Ƿ��ǺϷ������
* Input Parameter: ch - Ҫ�����ַ�
* Returned Value:  ����ǺϷ����������true�����򷵻�false
***********************************************************/
bool LegalCharacter(char ch) { return (ch == '+' || ch == '-' || ch == '*' || ch == '/'); }

/***********************************************************
* Function Name:   LegalFigure
* Function:        ����ַ��Ƿ��ǺϷ�����
* Input Parameter: ch - Ҫ�����ַ�
* Returned Value:  ����ǺϷ����ַ���true�����򷵻�false
***********************************************************/
bool LegalFigure(char ch) { return (ch >= '0' && ch <= '9'); }

/***********************************************************
* Function Name:   getPriority
* Function:        ��ȡ����������ȼ�
* Input Parameter: op - �����
* Returned Value:  ����������ȼ�
***********************************************************/
int getPriority(char op) {
    if (op == '+' || op == '-') return 1;// �Ӽ��������ȼ�
    if (op == '*' || op == '/') return 2;// �˳��������ȼ�
    return 0;// �����ȼ�
}

/***********************************************************
* Function Name:   BuildExpressionTree
* Function:        ������׺���ʽ�������ʽ��
* Input Parameter: tree - ���ʽ��
*                  expression - ��׺���ʽ
***********************************************************/
void BuildExpressionTree(BinaryTree<mine::String>& tree,const char expression[MAX_NUM + 1][MAX_NUM + 1])
{
    Stack<BinTreeNode<mine::String>*> operandStack; // �洢���������ӱ��ʽ��
    Stack<char> operatorStack; // �洢�����

    for (int i = 0; expression[i][0]!='\0'; i++) {
        mine::String expr;// ��ǰ���ʽ�ַ���
        for (int j = 0; expression[i][j] != '\0'; j++)
            expr.PushBack(expression[i][j]);

        // �����������С��������
        if (expr.Size() != 1 && expr[0] == '+')
            expr.Erase(0, 1);
        if (expr[0] == '.')
            expr.Insert(0, '0');
        if(expr[0] == '-'&& expr[1]=='.')
            expr.Insert(1, '0');
        if (expr[expr.Size()-1] == '.')
            expr.Erase(expr.Size() - 1, 1);
        char ch = expr[0];
        if (expr.Size() != 1 && (expr[0] == '+' || expr[0] == '-'))
            ch = expr[1];

        // ��������֣�����Ҷ�ӽڵ�
        if (LegalFigure(ch)||ch=='.') {
            BinTreeNode<mine::String>* newNode = new BinTreeNode<mine::String>(expr);
            operandStack.Push(newNode);
        }

        // ����������ţ�ֱ����ջ
        else if (ch == '(') {
            operatorStack.Push(ch);
        }

        // ����������ţ���ʼ����
        else if (ch == ')') {
            while (!operatorStack.IsEmpty() && operatorStack.getTop() != '(') {
                char op = operatorStack.Pop();
                BinTreeNode<mine::String>* right = operandStack.Pop();
                BinTreeNode<mine::String>* left = operandStack.Pop();
                mine::String temp;
                temp.PushBack(op);
                BinTreeNode<mine::String>* newNode = new BinTreeNode<mine::String>(temp, NULL, left, right);
                operandStack.Push(newNode);// ���½ڵ�ѹ�������ջ
            }
            // ����������
            if (!operatorStack.IsEmpty()) operatorStack.Pop();
        }
        // ����������
        else if (LegalCharacter(ch)) {
            while (!operatorStack.IsEmpty() && getPriority(operatorStack.getTop()) >= getPriority(ch)) {
                char op = operatorStack.Pop();
                BinTreeNode<mine::String>* right = operandStack.Pop();
                BinTreeNode<mine::String>* left = operandStack.Pop();
                mine::String temp;
                temp.PushBack(op);
                BinTreeNode<mine::String>* newNode = new BinTreeNode<mine::String>(temp, NULL, left, right);
                operandStack.Push(newNode);// ���½ڵ�ѹ�������ջ
            }
            operatorStack.Push(ch); // �������ѹ��ջ
        }
    }

    // ����ʣ�µ�ջ
    while (!operatorStack.IsEmpty()) {
        char op = operatorStack.Pop();// ���������
        BinTreeNode<mine::String>* right = operandStack.Pop();
        BinTreeNode<mine::String>* left = operandStack.Pop();
        mine::String temp;
        temp.PushBack(op);
        BinTreeNode<mine::String>* newNode = new BinTreeNode<mine::String>(temp, NULL, left, right);
        operandStack.Push(newNode);// ���½ڵ�ѹ�������ջ
    }

    // ���ս�������ĸ��ڵ�
    BinTreeNode<mine::String>* subTree = operandStack.Pop();
    tree.StoreRoot(subTree); // �洢���ڵ�
}

void Copy(char str1[MAX_NUM +1][MAX_NUM +1], const char str2[MAX_NUM])
{
    for (int i = 0, k = 0, j = 0; str2[i] != '\0'; i++) {
        if (str2[i] == ' ') {
            k++;// �ƶ�����һ���ַ���
            j = 0;// ����������
            continue;
        }
        str1[k][j] = str2[i];
        j++;
    }	
}

/***********************************************************
* Function Name:   isLegal
* Function:        �����ʽ�Ƿ�Ϸ�
* Input Parameter: expr - ����ı��ʽ
* Returned Value:  ����Ϸ�����true�����򷵻�false
***********************************************************/
bool isLegal(const char expr[])
{
	if (expr[0] == '\0') {
		std::cout << "������ʽΪ�գ����������룡\n";
		return false;
	}
    int len = 0;
    for (int i = 0; expr[i] != '\0'; i++)
        if (expr[i] != ' ')
            len++;
    if (len > MAX_NUM) {
        std::cout << "������ʽ�е��ַ���������"<< MAX_NUM <<"�����������룡\n";
        return false;
    }
	char temp[MAX_NUM +1][MAX_NUM +1] = { '\0' };
    Copy(temp, expr);
    for (int i = 0; temp[i][0] != '\0'; i++) {
        for (int j = 0; temp[i][j] != '\0'; j++) {
            //���Ƿ��ַ�
            if (!(temp[i][j] >= '0' && temp[i][j] <= '9') && !LegalCharacter(temp[i][j]) && temp[i][j] != '(' && temp[i][j] != ')' && temp[i][j] != '.') {
                std::cout << "������ʽ���ڷǷ��ַ����룬���������룡\n";
                return false;
            }
            //��������ʽ
            if(temp[i][j] == '('|| temp[i][j] == ')'|| LegalCharacter(temp[i][j]))
                if ((j != 0 || temp[i][j + 1] != '\0') && !((temp[i][j] == '+' || temp[i][j] == '-') && j == 0 && (i == 0 || i != 0 && temp[i - 1][1] == '\0' && !LegalFigure(temp[i - 1][0])))) {
                    std::cout << "������ʽδʹ�ÿո�ָ���ͬ�������������룡\n";
                    return false;
                }
            //���С�����Ƿ񵥶�����
            if (temp[i][j] == '.')
                if (!(LegalFigure(temp[i][j + 1]) || j != 0 && LegalFigure(temp[i][j - 1]))) {
                    std::cout << "������ʽ��С���㲻�ܵ������֣����������룡\n";
                    return false;
                }
        }
    }
    for (int i = 0; temp[i][0] != '\0'; i++)
        if (temp[i][1] != '\0') {
            int num_dot = 0;
            for (int j = 0; temp[i][j] != '\0'; j++)
                if (temp[i][j] == '.')
                    num_dot++;
            //���С�����Ƿ����
            if (num_dot > 1) {
                std::cout << "������ʽ�д��������ж�����㣬���������룡\n";
                return false;
            }
        }
    Stack<char> parentheses;// ���ڴ洢����
    char previous = '\0';
    for (int i = 0; temp[i][0] != '\0';i++) {
        char ch = temp[i][0];
        if (temp[i][1] != '\0' && (temp[i][0] == '+' || temp[i][0] == '-'))
            ch = temp[i][1];

        // ��鹫ʽ�Ƿ��Գ˺Ż���ſ�ʼ
        if (i==0 && LegalCharacter(ch)) {
            std::cout << "������ʽ�������������ʼ�����������룡\n";
            return false;
        }

        // ��������
        if (previous == '(' && ch == ')') {
            std::cout << "������ʽ���ڿ����ţ����������룡\n";
            return false;
        }
       
        // �����������ŵ�����
        if ((LegalFigure(ch) && previous == ')') || (ch == '(' && LegalFigure(previous))) {
            std::cout << "������ʽ�б��������ŵ����Ӳ���ȷ�����������룡\n";
            return false;
        }

        // �洢������
        if (ch == '(')
            parentheses.Push(ch);

        // ����������
        else if (ch == ')') {
            if (parentheses.IsEmpty()) {
                std::cout << "������ʽ���Ų�ƥ�䣬���������룡\n";
                return false;// ������û��ƥ���������
            }
            parentheses.Pop();// ƥ�䵽һ�����ţ�����ջ��Ԫ��
        }

        if ((LegalFigure(ch)||ch=='.') && (LegalFigure(previous)|| previous=='.')) {
            std::cout << "������ʽ�г��������ʹ����������ӣ����������룡\n";
            return false;
        }

        // ��������ǰ�������
        if (LegalCharacter(ch)&& (!LegalFigure(previous) && previous != ')'&& previous!='.')) {
            std::cout << "������ʽ��ÿ����Ԫ�����ǰ��������ӱ��������������룡\n";
            return false;
        }
        previous = ch;
    }

    // ��鹫ʽ�Ƿ����������β
    if (LegalCharacter(previous)) {
        std::cout << "������ʽ�������������β�����������룡\n";
        return false;
    }

    // ��������Ƿ�ƥ��
    if (!parentheses.IsEmpty()) {
        std::cout << "������ʽ���Ų�ƥ�䣬���������룡\n";
        return false;
    }

    return true;// ���ʽ�Ϸ�
}

/***********************************************************
* Function Name:   Input
* Function:        ��ȡ�û��������׺���ʽ�����кϷ��Լ��
* Input Parameter: expression - ���ڴ洢������ʽ�Ķ�ά�ַ�����
***********************************************************/
void Input(char expression[MAX_NUM + 1][MAX_NUM + 1])
{
	char expr[MAX_SIZE] = { '\0' };
	do {
		std::cout << "��������׺���ʽ\n";
		std::cin.getline(expr, MAX_SIZE);
	} while (!isLegal(expr));
	Copy(expression, expr);
}

/***********************************************************
* Function Name:   ExpressionConversion
* Function:        �������벢�������ʽ��
***********************************************************/
void ExpressionConversion()
{
	char expression[MAX_NUM +1][MAX_NUM + 1] = { '\0' };
	std::cout << "*����˵����\n"
		<< "1.��׺���ʽ���԰���+��-��*��/�Լ��������ţ�\n"
		<< "2.�ÿո�ָ���ͬ���������������ֲ��ÿո�ָ���\n"
		<< "3.���ʽ���ܳ���20���ַ����������ո񣩣�\n"
		<< "4.���볤�Ȳ��ܳ���100�������ضϣ�\n"
		<< "5.ʾ����2 + 3 * ( 7 - 4 ) + 8 / 4\n";
	Input(expression);
    BinaryTree<mine::String> tree;
    BuildExpressionTree(tree, expression);
    PostorderTraversal(tree);
}

/***********************************************************
* Function Name:   main
* Function:        ������ڣ����ñ��ʽת������
* Returned Value:  0
***********************************************************/
int main() 
{
	ExpressionConversion();

	return 0;
}
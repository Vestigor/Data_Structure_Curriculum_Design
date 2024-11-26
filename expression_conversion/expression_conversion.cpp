/***********************************************************
* File:     expression_conversion.cpp
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: expression conversion
* Date:     2024.10.23
* Update:   2024.10.23
***********************************************************/

#include <iostream>
#include <cassert>
#include "my_stack.h"
#include "my_string.h"

#define MAX_SIZE 100// 输入表达式的最大字符数
#define MAX_NUM 20 // 表达式中元素的最大数量

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

    T data;// 节点数据
    BinTreeNode<T>* leftChild, * rightChild;
    // 默认构造函数，初始化节点指针
    BinTreeNode() :leftChild(nullptr), rightChild(nullptr) {}
    // 构造函数，创建节点并初始化数据和指针
    BinTreeNode(T x,  BinTreeNode<T>* left =nullptr, BinTreeNode<T>* right = nullptr) : data{x}, leftChild(left), rightChild(right) { }
};


/***********************************************************
* Function Name:   DeleteTree
* Function:        删除树，释放分配的内存
* Input Parameter: subTree - 需要删除的树
***********************************************************/
void DeleteTree(BinTreeNode<mine::String>* subTree)
{
    if (subTree == nullptr)
        return;
    if(subTree->leftChild != nullptr)
        DeleteTree(subTree->leftChild);
    if(subTree->rightChild != nullptr)
        DeleteTree(subTree->rightChild);
    delete subTree;
}

/***********************************************************
* Function Name:   PostorderTraversal
* Function:        后序遍历表达式树
* Input Parameter: tree - 表达式树
***********************************************************/
void PostorderTraversal(BinTreeNode<mine::String> *const root)
{
    if (root == nullptr)
        return;
    Stack<BinTreeNode<mine::String>*> s1, s2;// 创建两个栈用于遍历
    s1.Push(root); // 将根节点压入第一个栈

    // 进行遍历
    while (!s1.IsEmpty()) {
        BinTreeNode<mine::String>* node = s1.getTop(); // 获取栈顶节点
        s2.Push(node); // 将节点压入第二个栈
        s1.Pop();
        // 先压入左子节点，再压入右子节点
        if (node->leftChild!=nullptr) {
            s1.Push(node->leftChild);
        }
        if (node->rightChild!= nullptr) {
            s1.Push(node->rightChild);
        }
    }

    // 打印后序遍历结果
    bool first = true;
    std::cout << "后缀表达式为：\n";
    while (!s2.IsEmpty()) {
        if (!first)
            std::cout << " ";
        std::cout << s2.getTop()->data ; // 打印当前节点的数据
        s2.Pop();
        first = false;
    }
    std::cout<<"\n";
}
/***********************************************************
* Function Name:   LegalCharacter
* Function:        检查字符是否是合法运算符
* Input Parameter: ch - 要检查的字符
* Returned Value:  如果是合法运算符返回true，否则返回false
***********************************************************/
bool LegalCharacter(char ch) { return (ch == '+' || ch == '-' || ch == '*' || ch == '/'); }

/***********************************************************
* Function Name:   LegalFigure
* Function:        检查字符是否是合法数字
* Input Parameter: ch - 要检查的字符
* Returned Value:  如果是合法数字返回true，否则返回false
***********************************************************/
bool LegalFigure(char ch) { return (ch >= '0' && ch <= '9'); }

/***********************************************************
* Function Name:   getPriority
* Function:        获取运算符的优先级
* Input Parameter: op - 运算符
* Returned Value:  运算符的优先级
***********************************************************/
int getPriority(char op) {
    if (op == '+' || op == '-') return 1;// 加减运算优先级
    if (op == '*' || op == '/') return 2;// 乘除运算优先级
    return 0;// 无优先级
}

/***********************************************************
* Function Name:   BuildExpressionTree
* Function:        根据中缀表达式构建表达式树
* Input Parameter: tree - 表达式树
*                  expression - 中缀表达式
***********************************************************/
BinTreeNode<mine::String>* BuildExpressionTree(const char expression[MAX_NUM + 1][MAX_NUM + 1])
{
    Stack<BinTreeNode<mine::String>*> operandStack; // 存储操作数（子表达式）
    Stack<char> operatorStack; // 存储运算符

    for (int i = 0; expression[i][0]!='\0'; i++) {
        mine::String expr;// 当前表达式字符串
        for (int j = 0; expression[i][j] != '\0'; j++)
            expr.PushBack(expression[i][j]);
            
        if (expr.Size() < 1) 
            continue;
        // 处理运算符和小数点的情况
        if (expr.Size() > 1 && expr[0] == '+')
            expr.Erase(0, 1);
        if (expr[0] == '.')
            expr.Insert(0, '0');
        if(expr.Size() > 1&&expr[0] == '-'&& expr[1]=='.')
            expr.Insert(1, '0');
        if (expr[expr.Size()-1] == '.')
            expr.Erase(expr.Size() - 1, 1);

        char ch = expr[0];
        if (expr.Size() > 1 && (expr[0] == '+' || expr[0] == '-'))
            ch = expr[1];

        // 如果是数字，创建叶子节点
        if (LegalFigure(ch)||ch=='.') {
            auto* newNode = new(std::nothrow) BinTreeNode<mine::String>(expr);
            assert(newNode != nullptr);
            operandStack.Push(newNode);
        }

        // 如果是左括号，直接入栈
        else if (ch == '(') {
            operatorStack.Push(ch);
        }

        // 如果是右括号，开始处理
        else if (ch == ')') {
            while (!operatorStack.IsEmpty() && operatorStack.getTop() != '(') {
                char op = operatorStack.Pop();
                BinTreeNode<mine::String>* right = operandStack.Pop();
                BinTreeNode<mine::String>* left = operandStack.Pop();
                mine::String temp;
                temp.PushBack(op);
                auto* newNode = new(std::nothrow) BinTreeNode<mine::String>(temp, left, right);
                assert(newNode!=nullptr);
                operandStack.Push(newNode);// 将新节点压入操作数栈
            }
            // 弹出左括号
            if (!operatorStack.IsEmpty()) operatorStack.Pop();
        }
        // 如果是运算符
        else if (LegalCharacter(ch)) {
            while (!operatorStack.IsEmpty() && getPriority(operatorStack.getTop()) >= getPriority(ch)) {
                char op = operatorStack.Pop();
                BinTreeNode<mine::String>* right = operandStack.Pop();
                BinTreeNode<mine::String>* left = operandStack.Pop();
                mine::String temp;
                temp.PushBack(op);
                auto* newNode = new(std::nothrow) BinTreeNode<mine::String>(temp,  left, right);
                assert(newNode!=nullptr);
                operandStack.Push(newNode);// 将新节点压入操作数栈
            }
            operatorStack.Push(ch); // 将运算符压入栈
        }
    }

    // 清理剩下的栈
    while (!operatorStack.IsEmpty()) {
        char op = operatorStack.Pop();// 弹出运算符
        BinTreeNode<mine::String>* right = operandStack.Pop();
        BinTreeNode<mine::String>* left = operandStack.Pop();
        mine::String temp;
        temp.PushBack(op);
        auto* newNode = new(std::nothrow) BinTreeNode<mine::String>(temp, left, right);
        assert(newNode!=nullptr);
        operandStack.Push(newNode);// 将新节点压入操作数栈
    }

    // 最终结果是树的根节点
    BinTreeNode<mine::String>* subTree = operandStack.Pop();
    return subTree;
}

void Copy(char str1[MAX_NUM +1][MAX_NUM +1], const char str2[MAX_NUM])
{
    for (int i = 0, k = 0, j = 0; str2[i] != '\0'; i++) {
        if (str2[i] == ' ') {
            k++;// 移动到下一个字符串
            j = 0;// 重置列索引
            continue;
        }
        str1[k][j] = str2[i];
        j++;
    }	
}

/***********************************************************
* Function Name:   isLegal
* Function:        检查表达式是否合法
* Input Parameter: expr - 输入的表达式
* Returned Value:  如果合法返回true，否则返回false
***********************************************************/
bool isLegal(const char expr[])
{
	if (expr[0] == '\0') {
		std::cout << "计算表达式为空，请重新输入！\n";
		return false;
	}
    int len = 0;
    for (int i = 0; expr[i] != '\0'; i++)
        if (expr[i] != ' ')
            len++;
    if (len > MAX_NUM) {
        std::cout << "计算表达式中的字符个数大于"<< MAX_NUM <<"，请重新输入！\n";
        return false;
    }
	char temp[MAX_NUM +1][MAX_NUM +1] = { '\0' };
    Copy(temp, expr);
    for (int i = 0; temp[i][0] != '\0'; i++) {
        for (int j = 0; temp[i][j] != '\0'; j++) {
            //检查非法字符
            if (!(temp[i][j] >= '0' && temp[i][j] <= '9') && !LegalCharacter(temp[i][j]) && temp[i][j] != '(' && temp[i][j] != ')' && temp[i][j] != '.') {
                std::cout << "计算表达式存在非法字符输入，请重新输入！\n";
                return false;
            }
            //检查输入格式
            if(temp[i][j] == '('|| temp[i][j] == ')'|| LegalCharacter(temp[i][j]))
                if ((j != 0 || temp[i][j + 1] != '\0') && !((temp[i][j] == '+' || temp[i][j] == '-') && j == 0 )) {
                    std::cout << "计算表达式未使用空格分隔不同对象，请重新输入！\n";
                    return false;
                }

            if((temp[i][j] == '+' || temp[i][j] == '-') && j == 0&&temp[i][1]!='\0' &&i != 0 && temp[i - 1][0] !='(') {
                std::cout << "计算表达式除第一项外，所有带正负号的数前一项必须为左括号！\n";
                return false;
            }

            //检查小数点是否单独出现
            if (temp[i][j] == '.')
                if (!(LegalFigure(temp[i][j + 1]) || j != 0 && LegalFigure(temp[i][j - 1]))) {
                    std::cout << "计算表达式中小数点不能单独出现，请重新输入！\n";
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
            //检查小数点是否合理
            if (num_dot > 1) {
                std::cout << "计算表达式中存在有某个数有多个小数点，请重新输入！\n";
                return false;
            }
        }
    Stack<char> parentheses;// 用于存储括号
    char previous = '\0';
    for (int i = 0; temp[i][0] != '\0';i++) {
        char ch = temp[i][0];
        if (temp[i][1] != '\0' && (temp[i][0] == '+' || temp[i][0] == '-'))
            ch = temp[i][1];

        // 检查公式是否以乘号或除号开始
        if (i==0 && LegalCharacter(ch)) {
            std::cout << "计算表达式不能以运算符开始，请重新输入！\n";
            return false;
        }

        // 检查空括号
        if (previous == '(' && ch == ')') {
            std::cout << "计算表达式存在空括号，请重新输入！\n";
            return false;
        }
       
        // 检查变量与括号的连接
        if ((LegalFigure(ch) && previous == ')') || (ch == '(' && LegalFigure(previous))) {
            std::cout << "计算表达式中变量与括号的连接不正确，请重新输入！\n";
            return false;
        }
        // 检查运算符与括号的连接
        if ((LegalCharacter(ch) && previous == '(') || (ch == ')' && LegalCharacter(previous))) {
            std::cout << "计算表达式中运算符与括号的连接不正确，请重新输入！\n";
            return false;
        }


        // 存储左括号
        if (ch == '(')
            parentheses.Push(ch);

        // 处理右括号
        else if (ch == ')') {
            if (parentheses.IsEmpty()) {
                std::cout << "计算表达式括号不匹配，请重新输入！\n";
                return false;// 右括号没有匹配的左括号
            }
            parentheses.Pop();// 匹配到一对括号，弹出栈顶元素
        }

        if ((LegalFigure(ch)||ch=='.') && (LegalFigure(previous)|| previous=='.')) {
            std::cout << "计算表达式中常数间必须使用运算符连接，请重新输入！\n";
            return false;
        }

        // 检查运算符前后的连接
        if (LegalCharacter(ch)&& (!LegalFigure(previous) && previous != ')'&& previous!='.')) {
            std::cout << "计算表达式中每个二元运算符前后必须连接变量，请重新输入！\n";
            return false;
        }
        previous = ch;
    }

    // 检查公式是否以运算符结尾
    if (LegalCharacter(previous)) {
        std::cout << "计算表达式不能以运算符结尾，请重新输入！\n";
        return false;
    }

    // 检查括号是否匹配
    if (!parentheses.IsEmpty()) {
        std::cout << "计算表达式括号不匹配，请重新输入！\n";
        return false;
    }

    return true;// 表达式合法
}

/***********************************************************
* Function Name:   Input
* Function:        读取用户输入的中缀表达式并进行合法性检查
* Input Parameter: expression - 用于存储输入表达式的二维字符数组
***********************************************************/
void Input(char expression[MAX_NUM + 1][MAX_NUM + 1])
{
	char expr[MAX_SIZE] = { '\0' };
	do {
		std::cout << "请输入中缀表达式\n";
		std::cin.getline(expr, MAX_SIZE);
	} while (!isLegal(expr));
	Copy(expression, expr);
}

/***********************************************************
* Function Name:   ExpressionConversion
* Function:        处理输入并构建表达式树
***********************************************************/
void ExpressionConversion()
{
    std::cout << "+---------------------------------------------+\n";
    std::cout << "|                 表达式转换                  |\n";
    std::cout << "|            Expression Conversion            |\n";
    std::cout << "+---------------------------------------------+\n";
	char expression[MAX_NUM +1][MAX_NUM + 1] = { '\0' };
	std::cout << "*输入说明：\n"
		<< "1.中缀表达式可以包含+，-，*，/以及左右括号；\n"
		<< "2.用空格分隔不同对象，正负号与数字不用空格分隔（若分隔则视为运算符）；\n"
		<< "3.表达式不能超过20个字符（不包含空格）；\n"
		<< "4.输入长度不能超过100，否则会截断；\n"
		<< "5.示例：2 + 3 * ( 7 - 4 ) + 8 / 4 * ( -3 + 2 ).\n";
	Input(expression);
    BinTreeNode<mine::String> *root = BuildExpressionTree(expression);
    PostorderTraversal(root);
    DeleteTree(root);
}

/***********************************************************
* Function Name:   main
* Function:        程序入口，调用表达式转换函数
* Returned Value:  0
***********************************************************/
int main() 
{
	ExpressionConversion();

	return 0;
}

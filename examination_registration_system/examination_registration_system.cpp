/***********************************************************
* File:     examination_registration_system.cpp
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Function: Examination registration system
* Encoding: UTF-8
* Date:     2024.9.17
* Update:   2024.10.27
***********************************************************/

#include <iostream>
#include <iomanip>
#include "my_singly_link_list.h"
#include "my_string.h"

#define MIX_LENGTH 100
#define MAX_BUFFER 1000000000
constexpr int kMinAge=1;
constexpr int kMaxAge=150;

constexpr int gbk_chinese_char_len=2;

const mine::String demo="马";

/***********************************************************
* Function Name:   EncodingDeviation
* Function:        补齐编码差异带来的字符显示差异
* Input Parameter: str - 需要输出的字符
*                  num - 转化成功的数字
* Returned Value:  deviation_value - 需要补的长度
***********************************************************/
size_t EncodingDeviation(const mine::String& str) {
	size_t normal_chinese_char_len=demo.Size();//当前编码下单个中文字符（常用）长度
	if(normal_chinese_char_len==gbk_chinese_char_len)
		return 0;
	size_t deviation_value=str.Size()/normal_chinese_char_len;
	return deviation_value;
}

/***********************************************************
* Function Name:   Check
* Function:        检查字符串是否为数字串
* Input Parameter: str - 字符串
* Returned Value:  false - 不是数字串
*                  true - 是数字串
***********************************************************/
bool Check(const mine::String& str)
{
	for(auto ch:str)
		if(ch<'0'||ch>'9')
			return false;
	return true;
}

/***********************************************************
* Function Name:   Switch
* Function:        将数字串转化为int型数据
* Input Parameter: str - 包含数据的数字串
*                  num - 转化成功的数字
* Returned Value:  false - 未转化成功
*                  true - 转化成功
***********************************************************/
bool Switch(const mine::String& str,int& num)
{
	if(str.Size()>10)
		return false;
	size_t temp=0;
	for(auto ch:str)
		temp=temp*10+(ch-'0');
	if(temp>2147483647)
		return false;
	num=temp;
	return true;
}
/***********************************************************
* Struct Name:   Examinee
* Function:      用于存储考生的基本信息
* Members:       examination_number - 考生的考号，唯一标识
*                name - 考生的姓名，字符串形式
*                sex - 考生的性别，"男" 或 "女"
*                age - 考生的年龄
*                entry_category - 考生的报考类别
***********************************************************/
struct Examinee {
	int examination_number;
	mine::String name;
	mine::String sex;
	int age;
	mine::String entry_category;
};

/***********************************************************
* Struct Name:   Category
* Function:      用于存储报考类别的统计信息
* Members:       entry_category - 报考类别的名称，字符串形式
*                number - 报考该类别的考生人数
***********************************************************/
struct Category {
	mine::String entry_category;
	int number;
};

/***********************************************************
* Function Name:   ClearBuffer
* Function:        清除标准输入缓冲区中的内容
* Input Parameter: 无
* Returned Value:  无
***********************************************************/
void ClearBuffer() {
	std::cin.clear();
	std::cin.ignore(MAX_BUFFER, '\n');
}

/***********************************************************
* Function Name:   IsSameExaminationNumber
* Function:        检查给定考号是否在考生链表中存在
* Input Parameter: number - 要检查的考号
*                  examinee - 存储考生的链表
* Returned Value:  如果考号存在则返回 1，否则返回 0
***********************************************************/
int IsSameExaminationNumber(const int number, LinkList<Examinee>& examinee)
{
	for (auto exa : examinee) {
		if (number == exa.examination_number)
			return 1;// 返回1表示考号重复
	}
	return 0; // 返回0表示考号不重复
}

/***********************************************************
* Function Name:   Input
* Function:        输入考生信息，检查输入的合法性并确保考号不重复
* Input Parameter: examinee - 存储考生的链表
* Returned Value:  返回包含考生信息的 Examinee 结构体
***********************************************************/
Examinee Input(LinkList<Examinee>& examinee)
{
	Examinee temp;
	while (true) {
		mine::String num_temp;
		// 输入考号并检查合法性及唯一性
		std::cin >> num_temp;
		if (!Check(num_temp) || !Switch(num_temp,temp.examination_number)||temp.examination_number==0) {
			std::cout << "考号输入不合法，请重新输入考生信息\n";
			ClearBuffer();
			continue;
		}
		if (IsSameExaminationNumber(temp.examination_number, examinee)) {
			std::cout << "已存在考号相同的考生，请重新输入考生信息\n";
			ClearBuffer();
			continue;
		}
		// 输入姓名
		std::cin >> temp.name;

		// 输入性别并进行合法性验证，只能输入“男”或“女”
		std::cin >> temp.sex;
		if (temp.sex!="男" && temp.sex!= "女"){
			std::cout << "性别输入不合法，请重新输入考生信息\n";
			ClearBuffer();
			continue;
		}

		// 输入年龄并检查范围是否有效
		std::cin >> num_temp;
		if (!Check(num_temp) ||!Switch(num_temp,temp.age)|| temp.age < kMinAge|| temp.age>kMaxAge) {
			std::cout << "年龄输入不合法，请重新输入考生信息\n";
			ClearBuffer();
			continue;
		}

		// 输入报考类别
		std::cin >> temp.entry_category;

		break;
	}
	return temp;
}

/***********************************************************
* Function Name:   MyBuild
* Function:        根据用户输入，建立考生信息链表
* Input Parameter: examinee - 存储考生的链表
* Returned Value:
***********************************************************/
void MyBuild(LinkList<Examinee>& examinee)
{
	int num_examinee;
	mine::String number_examinee;
	while (true) {
		std::cout << "请输入考生人数： ";
		std::cin >> number_examinee;
		if (!Check(number_examinee)||!Switch(number_examinee,num_examinee)) {
			std::cout << "输入人数不合法，请重新输入！\n";
			ClearBuffer();
			continue;
		}
		break;
	}
	std::cout << "请依次输入考生的考号，姓名，性别，年龄以及报考类别！\n";
	for (int i = 1; i <=num_examinee; i++) {
		Examinee student;
		student = Input(examinee);// 调用输入函数
		examinee.inputRear(student);// 将考生信息插入链表
	}
}

/***********************************************************
* Function Name:   ExamineePrintTemplate
* Function:        格式化输出单个考生信息
* Input Parameter: student - 包含考生信息的 Examinee 结构体
* Returned Value:  无
***********************************************************/
void ExamineePrintTemplate(const Examinee& student) {
	std::cout << "|-------------------+-------------------+-------------------+-------------------+-------------------|\n";
	std::cout << std::setiosflags(std::ios::left)
		<< "| " << std::setw(18) << student.examination_number
		<< "| " << std::setw(18+EncodingDeviation(student.name))<<student.name
		<< "| " << std::setw(18+EncodingDeviation(student.sex)) << student.sex
		<< "| " << std::setw(18) << student.age
		<< "| " << std::setw(18+EncodingDeviation(student.entry_category))<< student.entry_category
		<< std::resetiosflags(std::ios::left);
	std::cout << "|\n";
}

/***********************************************************
* Function Name:   MyPrint
* Function:        输出所有考生信息
* Input Parameter: examinee - 存储考生的链表
* Returned Value:
***********************************************************/
void MyPrint(LinkList<Examinee>& examinee) {
	std::cout << "\n\n";
	std::cout << "+---------------------------------------------------------------------------------------------------+\n";
	std::cout << "|                                           考生信息系统                                            |\n";
	std::cout << "+-------------------+-------------------+-------------------+-------------------+-------------------+\n";
	std::cout << "| 考号              | 姓名              | 性别              | 年龄              | 报考类别          |\n";
	int n=0;
	for (auto exam_people: examinee){
	ExamineePrintTemplate(exam_people); // 使用模板函数输出信息
		n++;
    }
	std::cout << "+-------------------+-------------------+-------------------+-------------------+-------------------+\n";
	std::cout<<"考生总人数为："<<n<<"\n";
}

/***********************************************************
* Function Name:   MySelect
* Function:        选择操作选项并进行合法性检查
* Input Parameter: examinee - 存储考生的链表
* Returned Value:  返回用户选择的操作选项
***********************************************************/
int MySelect(LinkList<Examinee>& examinee)
{
	mine::String num_temp;
	int select;
	while (true) {
		std::cout << "\n请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）：";
		std::cin >> num_temp;
		if (!Check(num_temp)||!Switch(num_temp,select)|| select>5) {
			std::cout << "输入非法！请重新输入\n";
			ClearBuffer();
			continue;
		}
		break;
	}
	return select;
}

/***********************************************************
* Function Name:   MyInsert
* Function:        插入新的考生信息到指定位置
* Input Parameter: examinee - 存储考生的链表
* Returned Value:
***********************************************************/
void MyInsert(LinkList<Examinee>& examinee)
{
	mine::String num_temp;
	int position;
	while (true) {
		std::cout << "请您选择要插入考生的位置[1-" << examinee.Length() + 1 << "]： ";
		std::cin >> num_temp;
		if (!Check(num_temp)||!Switch(num_temp,position) || position<1 || position>examinee.Length() + 1) {
			std::cout << "输入非法！请重新输入\n";
			ClearBuffer();
			continue;
		}
		break;
	}

	std::cout << "请依次输入考生的考号，姓名，性别，年龄以及报考类别！\n";
	Examinee student = Input(examinee);// 获取新的考生信息
	std::cout << "插入的考生信息为： \n";
	std::cout << "+-------------------+-------------------+-------------------+-------------------+-------------------+\n";
	std::cout << "| 考号              | 姓名              | 性别              | 年龄              | 报考类别          |\n";
	ExamineePrintTemplate(student);// 输出插入的考生信息
	std::cout << "+-------------------+-------------------+-------------------+-------------------+-------------------+\n";
	examinee.Insert(position,student);// 插入到指定位置
}

/***********************************************************
* Function Name:   PositionFind
* Function:        根据考号查找考生在链表中的位置
* Input Parameter: examinee - 存储考生的链表
*                  prompt - 提示用户输入的提示语
* Returned Value:  返回考生在链表中的位置，未找到则返回 -1
***********************************************************/
int PositionFind(LinkList<Examinee>& examinee,const char* prompt)
{
	mine::String num_temp;
	int temp_number;
	while (true) {
		std::cout << "请输入要" << prompt << "的考生的考号：";
		std::cin >> num_temp;
		if (!Check(num_temp)||!Switch(num_temp,temp_number)||temp_number==0) {
			std::cout << "输入非法！请重新输入\n";
			ClearBuffer();
			continue;
		}
		break;
	}
	int n=0;
	for (auto exa:examinee) {
		n++;
		if (temp_number == exa.examination_number)
			return n;// 返回考生所在的位置
	}
	return -1;// 未找到返回-1
}

/***********************************************************
* Function Name:   MyExpurgate
* Function:        删除指定考号的考生
* Input Parameter: examinee - 存储考生的链表
* Returned Value:
***********************************************************/
void MyExpurgate(LinkList<Examinee>& examinee)
{
	int position= PositionFind(examinee,"删除"); // 查找要删除的考生位置
	Examinee student;
	if (examinee.Remove(position, student)) {// 删除并返回考生信息
		std::cout << "删除的考生信息为： \n";
		std::cout << "+-------------------+-------------------+-------------------+-------------------+-------------------+\n";
		std::cout << "| 考号              | 姓名              | 性别              | 年龄              | 报考类别          |\n";
		ExamineePrintTemplate(student);// 输出被删除的考生信息
		std::cout << "+-------------------+-------------------+-------------------+-------------------+-------------------+\n";
	}
	else
		std::cout << "未查找到考生信息！\n";
}

/***********************************************************
* Function Name:   MyFind
* Function:        查找并输出指定考号的考生信息
* Input Parameter: examinee - 存储考生的链表
* Returned Value:
***********************************************************/
void MyFind(LinkList<Examinee>& examinee)
{
	int position = PositionFind(examinee, "查找");// 查找考生位置
	Examinee student;
	if (examinee.getData(position, student)) {// 查找到考生并获取数据
		std::cout << "+-------------------+-------------------+-------------------+-------------------+-------------------+\n";
		std::cout << "| 考号              | 姓名              | 性别              | 年龄              | 报考类别          |\n";
		ExamineePrintTemplate(student);// 输出查找到的考生信息
		std::cout << "+-------------------+-------------------+-------------------+-------------------+-------------------+\n";
	}
	else
		std::cout << "未查找到考生信息！\n";
}

/***********************************************************
* Function Name:   MyModify
* Function:        修改指定考号的考生信息
* Input Parameter: examinee - 存储考生的链表
* Returned Value:
***********************************************************/
void MyModify(LinkList<Examinee>& examinee)
{
	int position = PositionFind(examinee, "修改");// 查找需要修改的考生位置
	Examinee student;
	if (examinee.Remove(position, student)) {
		std::cout << "需要修改的信息为：\n";
		std::cout << "+-------------------+-------------------+-------------------+-------------------+-------------------+\n";
		std::cout << "| 考号              | 姓名              | 性别              | 年龄              | 报考类别          |\n";
		ExamineePrintTemplate(student);// 输出需要修改的考生信息
		std::cout << "+-------------------+-------------------+-------------------+-------------------+-------------------+\n";
	}
	else {
		std::cout << "未查找到考生信息！\n";
		return;
	}
	std::cout << "请输入修改后的考生信息\n";
	student = Input(examinee);// 输入修改后的考生信息
	std::cout << "+-------------------+-------------------+-------------------+-------------------+-------------------+\n";
	std::cout << "| 考号              | 姓名              | 性别              | 年龄              | 报考类别          |\n";
	ExamineePrintTemplate(student);// 输出需要修改的考生信息
	std::cout << "+-------------------+-------------------+-------------------+-------------------+-------------------+\n";
	examinee.Insert(position, student);// 将修改后的考生信息插入到原位置

}

/***********************************************************
* Function Name:   MyStatisc
* Function:        统计并输出考生的报考类别、年龄和性别分布信息
* Input Parameter: examinee - 存储考生的链表
* Returned Value:
***********************************************************/
void MyStatisc(LinkList<Examinee>& examinee)
{
	int total = examinee.Length(), male_num = 0, age_number[kMaxAge+1] = { 0 };// 获取考生总人数、统计男性考生人数、统计年龄分布，数组索引表示年龄
	LinkList<Category> category_statisc;//建立新链表以方便报考类别统计

	for (auto exam: examinee) {
		// 统计男性考生
		if (exam.sex=="男")
			male_num++;

		// 统计各年龄段考生人数
		age_number[exam.age]++;

		// 标记是否已经统计该报考类别
		bool is_stored = false;
		int n=0;
		for (auto category: category_statisc) {
			n++;
			if (category.entry_category== exam.entry_category) {
				category_statisc.Remove(n,category);
				is_stored = true;
				category.number++;// 更新已存在类别的人数
				category_statisc.Insert(n,category);
				break;
			}
		}

		if (!is_stored) { // 如果是新类别，插入类别链表
			Category temp;
			temp.entry_category= exam.entry_category;
			temp.number = 1;
			category_statisc.inputRear(temp);// 将新类别插入链表末尾
		}
	}
	// 输出报考类别统计信息
	std::cout << "\n考生报考类别统计（比例保留四位小数）\n"
		<< "考生总人数：" << total << "\n";
    std::cout << "+-------------------+-------------------+-------------------+\n";
	std::cout << "| 报考类别          | 人数              | 比例(%)           |\n";
	for (auto category : category_statisc)
		std::cout << std::setiosflags(std::ios::left)
		<< "| " << std::setw(18+EncodingDeviation(category.entry_category)) << category.entry_category
		<< "| " << std::setw(18) << category.number
		<< "| " << std::setw(18) << std::fixed << std::setprecision(4) << static_cast<double>(category.number) / static_cast<double>(total) * 100 << "|"
		<< "\n";
	std::cout << "+-------------------+-------------------+-------------------+\n";

	// 输出考生年龄统计信息
	std::cout << "\n考生年龄统计（比例保留四位小数）\n"
		<< "考生总人数：" << total << "\n";
	std::cout << "+-------------------+-------------------+-------------------+\n";
	std::cout << "| 年龄              | 人数              | 比例(%)           |\n";
	for (int i = 0; i <= 150; i++)
		if(age_number[i]!=0)
		std::cout<< "| " << std::setw(18) << i
			<< "| " << std::setw(18) << age_number[i]
			<< "| " << std::setw(18) << std::fixed << std::setprecision(4) << static_cast<double>(age_number[i]) / static_cast<double>(total)*100 << "|"
		<< "\n";
	std::cout << "+-------------------+-------------------+-------------------+\n";

	// 输出考生性别统计信息
	std::cout << "\n考生性别统计（比例保留四位小数）\n"
		<< "考生总人数：" << total << "\n";
	std::cout << "+-------------------+-------------------+-------------------+\n";
	std::cout << "| 性别              | 人数              | 比例(%)           |\n";
	std::cout << "| "<<std::setw(18+EncodingDeviation("男")) << "男" << "| "<<std::setw(18) << male_num <<"| "<<std::setw(18)<< std::fixed << std::setprecision(4) << static_cast<double>(male_num) / static_cast<double>(total) * 100 << "|\n"
		      << "| "<<std::setw(18+EncodingDeviation("女")) << "女" <<  "| "<<std::setw(18) << total - male_num <<"| "<<std::setw(18)<< std::fixed << std::setprecision(4) << static_cast<double>(total - male_num) / static_cast<double>(total) * 100 << "|\n";
	std::cout << "+-------------------+-------------------+-------------------+\n";
	std::cout << std::resetiosflags(std::ios::left);// 重置格式化标记
}


/***********************************************************
* Function Name:   ExaminationRegistrationSystem
* Function:        运行考试报名系统，允许用户进行插入、删除、查找、修改、统计操作
* Input Parameter:
* Returned Value:
***********************************************************/
void ExaminationRegistrationSystem()
{
	std::cout << "+----------------------------------------------+\n";
	std::cout << "|                  考生报名系统                |\n" ;
	std::cout << "|       Examination Registration System        |\n" ;
	std::cout << "+----------------------------------------------+\n" ;
	std::cout << "首先请建立考生信息系统！\n";
	LinkList<Examinee> examinee;// 定义考生链表
	MyBuild(examinee);// 初始化考生信息系统
	MyPrint(examinee); // 打印当前考生信息
	while (true) {

		int ret = MySelect(examinee); // 获取用户的操作选择
		if (ret == 1)
			MyInsert(examinee);// 插入考生
		else if (ret == 2)
			MyExpurgate(examinee);// 删除考生
		else if (ret == 3)
			MyFind(examinee); // 查找考生
		else if (ret == 4)
			MyModify(examinee);// 修改考生信息
		else if (ret == 5)
			MyStatisc(examinee);// 统计考生信息
		else {
			break; // 退出系统
		}
		if(ret!=0)
		    MyPrint(examinee); // 打印当前考生信息
	}
	std::cout << "成功退出考试报名系统！\n";
}
/***********************************************************
* Function Name:   main
* Function:        程序入口，调用考试报名系统
* Input Parameter:
* Returned Value:  0
***********************************************************/
int main()
{
	// 启动考试报名系统
	ExaminationRegistrationSystem();

	return 0;
}

/*******************************************
测试用数据：
2014199 张伟 男 21 软件开发师
2223540 李娜 女 22 软件测试师
2033638 王磊 男 20 软件运营师
2044268 刘洋 男 23 软件设计师
2213716 赵敏 女 22 软件开发师
2024286 陈佳 男 20 软件测试师
2131423 刘莉 女 21 软件运营师
2042141 孙强 男 23 软件设计师
2053086 朱莉 女 21 软件开发师
2236224 何俊 男 20 软件测试师
*********************************************/

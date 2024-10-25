/***********************************************************
* File:     examination_registration_system.cpp
* Author:   Xiaolong Ma(��С��)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: Examination registration system
* Date:     2024.9.17
* Update:   2024.10.1
***********************************************************/

#include <iostream>
#include <cstring>
#include <iomanip>
#include "my_singly_link_list.h"
#include "my_string.h"

#define MIX_LENGTH 100
#define MAX_BUFFER 1000000000

/***********************************************************
* Struct Name:   Examinee
* Function:      ���ڴ洢�����Ļ�����Ϣ
* Members:       examination_number - �����Ŀ��ţ�Ψһ��ʶ
*                name - �������������ַ�����ʽ
*                sex - �������Ա�"��" �� "Ů"
*                age - ����������
*                entry_category - �����ı������
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
* Function:      ���ڴ洢��������ͳ����Ϣ
* Members:       entry_category - �����������ƣ��ַ�����ʽ
*                number - ���������Ŀ�������
***********************************************************/
struct Category {
	mine::String entry_category;
	int number=0;
};

/***********************************************************
* Function Name:   ClearBuffer
* Function:        �����׼���뻺�����е�����
* Input Parameter: ��
* Returned Value:  ��
***********************************************************/
void ClearBuffer() {
	std::cin.clear();
	std::cin.ignore(MAX_BUFFER, '\n');
}

/***********************************************************
* Function Name:   IsSameExaminationNumber
* Function:        �����������Ƿ��ڿ��������д���
* Input Parameter: number - Ҫ���Ŀ���
*                  examinee - �洢����������
* Returned Value:  ������Ŵ����򷵻� 1�����򷵻� 0
***********************************************************/
int IsSameExaminationNumber(const int number, LinkList<Examinee>& examinee)
{
	for (auto exa : examinee) {
		if (number == exa.examination_number)
			return 1;// ����1��ʾ�����ظ�
	}
	return 0; // ����0��ʾ���Ų��ظ�
}

/***********************************************************
* Function Name:   Input
* Function:        ���뿼����Ϣ���������ĺϷ��Բ�ȷ�����Ų��ظ�
* Input Parameter: examinee - �洢����������
* Returned Value:  ���ذ���������Ϣ�� Examinee �ṹ��
***********************************************************/
Examinee Input(LinkList<Examinee>& examinee)
{
	Examinee temp;
	while (true) {
		// ���뿼�Ų����Ϸ��Լ�Ψһ��
		std::cin >> temp.examination_number;
		if (temp.examination_number <= 0 || std::cin.fail()) {
			std::cout << "�������벻�Ϸ������������뿼����Ϣ\n";
			ClearBuffer();
			continue;
		}
		if (IsSameExaminationNumber(temp.examination_number, examinee)) {
			std::cout << "�Ѵ��ڿ�����ͬ�Ŀ��������������뿼����Ϣ\n";
			ClearBuffer();
			continue;
		}

		// ��������
		std::cin >> temp.name;

		// �����Ա𲢽��кϷ�����֤��ֻ�����롰�С���Ů��
		std::cin >> temp.sex;
		if (temp.sex!="��" && temp.sex!= "Ů"){
			std::cout << "�Ա����벻�Ϸ������������뿼����Ϣ\n";
			ClearBuffer();
			continue;
		}

		// �������䲢��鷶Χ�Ƿ���Ч
		std::cin >> temp.age;
		if (std::cin.fail() || temp.age < 0 || temp.age>150) {
			std::cout << "�������벻�Ϸ������������뿼����Ϣ\n";
			ClearBuffer();
			continue;
		}

		// ���뱨�����
		std::cin >> temp.entry_category;

		break;
	}
	return temp;
}

/***********************************************************
* Function Name:   MyBuild
* Function:        �����û����룬����������Ϣ����
* Input Parameter: examinee - �洢����������
* Returned Value:  
***********************************************************/
void MyBuild(LinkList<Examinee>& examinee)
{
	int num_examinee;
	while (true) {
		std::cout << "�����뿼�������� ";
		std::cin >> num_examinee;
		if (std::cin.fail() || num_examinee < 0 ) {
			std::cout << "�����������Ϸ������������룡\n";
			ClearBuffer();
		}
		break;
	}
	std::cout << "���������뿼���Ŀ��ţ��������Ա������Լ��������\n";
	for (int i = 1; i <=num_examinee; i++) {
		Examinee student;
		student = Input(examinee);// �������뺯��
		examinee.inputRear(student);// ��������Ϣ��������
	}
}

/***********************************************************
* Function Name:   ExamineePrintTemplate
* Function:        ��ʽ���������������Ϣ
* Input Parameter: student - ����������Ϣ�� Examinee �ṹ��
* Returned Value:  ��
***********************************************************/
/*1 1 �� 2 2
2 2 �� 3 3
4 4 Ů 3 3*/
void ExamineePrintTemplate(Examinee& student) {
	std::cout << "|-------------------+-------------------+-------------------+-------------------+-------------------|\n";
	std::cout << std::setiosflags(std::ios::left)
		<< "| " << std::setw(18) << student.examination_number
		<< "| " << std::setw(18)<<student.name
		<< "| " << std::setw(18) << student.sex
		<< "| " << std::setw(18) << student.age
		<< "| " << std::setw(18)<< student.entry_category<<"|"
		<< std::resetiosflags(std::ios::left);
	std::cout << "\n";
}

/***********************************************************
* Function Name:   MyPrint
* Function:        ������п�����Ϣ
* Input Parameter: examinee - �洢����������
* Returned Value:  
***********************************************************/
void MyPrint(LinkList<Examinee>& examinee)
{
	std::cout << "\n\n\n";
	std::cout << "+---------------------------------------------------------------------------------------------------+\n";
	std::cout << "|                                             ����ϵͳ                                              |\n";
	std::cout << "+-------------------+-------------------+-------------------+-------------------+-------------------+\n";
	std::cout << "| ����              | ����              | �Ա�              | ����              | �������          |\n";
	for (auto exam_people: examinee)
		ExamineePrintTemplate(exam_people); // ʹ��ģ�庯�������Ϣ
	std::cout << "+-------------------+-------------------+-------------------+-------------------+-------------------+\n";
}

/***********************************************************
* Function Name:   MySelect
* Function:        ѡ�����ѡ����кϷ��Լ��
* Input Parameter: examinee - �洢����������
* Returned Value:  �����û�ѡ��Ĳ���ѡ��
***********************************************************/
int MySelect(LinkList<Examinee>& examinee)
{
	int select;
	while (true) {
		std::cout << "\n��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ����������";
		std::cin >> select;
		if (std::cin.fail() || select < 0 || select>5) {
			std::cout << "����Ƿ�������������\n";
			ClearBuffer();
			continue;
		}
		break;
	}
	return select;
}

/***********************************************************
* Function Name:   MyInsert
* Function:        �����µĿ�����Ϣ��ָ��λ��
* Input Parameter: examinee - �洢����������
* Returned Value:  
***********************************************************/
void MyInsert(LinkList<Examinee>& examinee)
{
	int position;
	while (true) {
		std::cout << "����ѡ��Ҫ���뿼����λ��[1-" << examinee.Length() + 1 << "]�� ";
		std::cin >> position;
		if (std::cin.fail() || position<1 || position>examinee.Length() + 1) {
			std::cout << "����Ƿ�������������\n";
			ClearBuffer();
			continue;
		}
		break;
	}

	std::cout << "���������뿼���Ŀ��ţ��������Ա������Լ��������\n";
	Examinee student = Input(examinee);// ��ȡ�µĿ�����Ϣ
	std::cout << "����Ŀ�����ϢΪ�� \n";
	std::cout << "+-------------------+-------------------+-------------------+-------------------+-------------------+\n";
	std::cout << "| ����              | ����              | �Ա�              | ����              | �������          |\n";
	ExamineePrintTemplate(student);// �������Ŀ�����Ϣ
	std::cout << "+-------------------+-------------------+-------------------+-------------------+-------------------+\n";
	examinee.Insert(position,student);// ���뵽ָ��λ��
}

/***********************************************************
* Function Name:   PositionFind
* Function:        ���ݿ��Ų��ҿ����������е�λ��
* Input Parameter: examinee - �洢����������
*                  prompt - ��ʾ�û��������ʾ��
* Returned Value:  ���ؿ����������е�λ�ã�δ�ҵ��򷵻� -1
***********************************************************/
int PositionFind(LinkList<Examinee>& examinee,const char* prompt)
{
	int temp_number;
	while (true) {
		std::cout << "������Ҫ" << prompt << "�Ŀ����Ŀ��ţ�";
		std::cin >> temp_number;
		if (std::cin.fail()) {
			std::cout << "����Ƿ�������������\n";
			ClearBuffer();
			continue;
		}
		break;
	}
	int i = 1;
	for (; i <= examinee.Length(); i++) {
		if (temp_number == examinee[i].examination_number)
			return i;// ���ؿ������ڵ�λ��
	}
	return -1;// δ�ҵ�����-1
}

/***********************************************************
* Function Name:   MyExpurgate
* Function:        ɾ��ָ�����ŵĿ���
* Input Parameter: examinee - �洢����������
* Returned Value:  
***********************************************************/
void MyExpurgate(LinkList<Examinee>& examinee)
{
	int position= PositionFind(examinee,"ɾ��"); // ����Ҫɾ���Ŀ���λ��
	Examinee student;
	if (examinee.Remove(position, student)) {// ɾ�������ؿ�����Ϣ
		std::cout << "ɾ���Ŀ�����ϢΪ�� \n";
		std::cout << "+-------------------+-------------------+-------------------+-------------------+-------------------+\n";
		std::cout << "| ����              | ����              | �Ա�              | ����              | �������          |\n";
		ExamineePrintTemplate(student);// �����ɾ���Ŀ�����Ϣ
		std::cout << "+-------------------+-------------------+-------------------+-------------------+-------------------+\n";
	}
	else
		std::cout << "δ���ҵ�������Ϣ��\n";
}

/***********************************************************
* Function Name:   MyFind
* Function:        ���Ҳ����ָ�����ŵĿ�����Ϣ
* Input Parameter: examinee - �洢����������
* Returned Value:  
***********************************************************/
void MyFind(LinkList<Examinee>& examinee)
{
	int position = PositionFind(examinee, "����");// ���ҿ���λ��
	Examinee student;
	if (examinee.getData(position, student)) {// ���ҵ���������ȡ����
		std::cout << "+-------------------+-------------------+-------------------+-------------------+-------------------+\n";
		std::cout << "| ����              | ����              | �Ա�              | ����              | �������          |\n";
		ExamineePrintTemplate(student);// ������ҵ��Ŀ�����Ϣ
		std::cout << "+-------------------+-------------------+-------------------+-------------------+-------------------+\n";
	}
	else
		std::cout << "δ���ҵ�������Ϣ��\n";
}

/***********************************************************
* Function Name:   MyModify
* Function:        �޸�ָ�����ŵĿ�����Ϣ
* Input Parameter: examinee - �洢����������
* Returned Value:  
***********************************************************/
void MyModify(LinkList<Examinee>& examinee)
{
	int position = PositionFind(examinee, "�޸�");// ������Ҫ�޸ĵĿ���λ��
	Examinee student;
	examinee.Remove(position, student);// ɾ��ԭ�п�����Ϣ,��ֹ����������Ϣʱ����ѧ���ظ����
	if (position>0) {
		std::cout << "��Ҫ�޸ĵ���ϢΪ��\n";
		std::cout << "+-------------------+-------------------+-------------------+-------------------+-------------------+\n";
		std::cout << "| ����              | ����              | �Ա�              | ����              | �������          |\n";
		ExamineePrintTemplate(student);// �����Ҫ�޸ĵĿ�����Ϣ
		std::cout << "+-------------------+-------------------+-------------------+-------------------+-------------------+\n";
	}
	else {
		std::cout << "δ���ҵ�������Ϣ��\n";
		return;
	}
	std::cout << "�������޸ĺ�Ŀ�����Ϣ\n";
	student = Input(examinee);// �����޸ĺ�Ŀ�����Ϣ
	ExamineePrintTemplate(student);// ����޸ĺ�Ŀ�����Ϣ
	std::cout << "+-------------------+-------------------+-------------------+-------------------+-------------------+\n";
	std::cout << "| ����              | ����              | �Ա�              | ����              | �������          |\n";
	ExamineePrintTemplate(student);// �����Ҫ�޸ĵĿ�����Ϣ
	std::cout << "+-------------------+-------------------+-------------------+-------------------+-------------------+\n";
	examinee.Insert(position, student);// ���޸ĺ�Ŀ�����Ϣ���뵽ԭλ��
	
}

/***********************************************************
* Function Name:   MyStatisc
* Function:        ͳ�Ʋ���������ı������������Ա�ֲ���Ϣ
* Input Parameter: examinee - �洢����������
* Returned Value:  
***********************************************************/
void MyStatisc(LinkList<Examinee>& examinee)
{
	int total = examinee.Length(), male_num = 0, age_number[151] = { 0 };// ��ȡ������������ͳ�����Կ���������ͳ������ֲ�������������ʾ����
	LinkList<Category> category_statisc;//�����������Է��㱨�����ͳ��
	for (auto exam: examinee) {
		// ͳ�����Կ���
		if (exam.sex=="��")
			male_num++;

		// ͳ�Ƹ�����ο�������
		age_number[exam.age]++;

		// ����Ƿ��Ѿ�ͳ�Ƹñ������
		bool is_stored = false;
		for (auto category: category_statisc) {
			if (category.entry_category== exam.entry_category) {
				is_stored = true;
				category.number++;// �����Ѵ�����������
			}
		}
		if (!is_stored) { // ���������𣬲����������
			Category temp;
			temp.entry_category= exam.entry_category;
			temp.number = 1;
			category_statisc.inputRear(temp);// ��������������ĩβ
		}
	}

	// ����������ͳ����Ϣ
	std::cout << "\n�����������ͳ�ƣ�����������λС����\n"
		<< "������������" << total << "\n";
    std::cout << "+-------------------+-------------------+-------------------+\n";
	std::cout << "| �������          | ����              | ����(%)           |\n";
	for (auto category : category_statisc)
		std::cout << std::setiosflags(std::ios::left)
		<< "| " << std::setw(18) << category.entry_category
		<< "| " << std::setw(18) << category.number
		<< "| " << std::setw(18) << std::fixed << std::setprecision(4) << double(category.number) / double(total) * 100 << "|"
		<< "\n";
	std::cout << "+-------------------+-------------------+-------------------+\n";

	// �����������ͳ����Ϣ
	std::cout << "\n��������ͳ�ƣ�����������λС����\n"
		<< "������������" << total << "\n";
	std::cout << "+-------------------+-------------------+-------------------+\n";
	std::cout << "| ����              | ����              | ����(%)           |\n";
	for (int i = 0; i <= 150; i++)
		if(age_number[i]!=0)
		std::cout<< "| " << std::setw(18) << i
			<< "| " << std::setw(18) << age_number[i]
			<< "| " << std::setw(18) << std::fixed << std::setprecision(4) << double(age_number[i]) / double(total)*100 << "|"
		<< "\n";
	std::cout << "+-------------------+-------------------+-------------------+\n";

	// ��������Ա�ͳ����Ϣ
	std::cout << "\n�����Ա�ͳ�ƣ�����������λС����\n"
		<< "������������" << total << "\n";
	std::cout << "+-------------------+-------------------+-------------------+\n";
	std::cout << "| �Ա�              | ����              | ����(%)           |\n";
	std::cout << std::setw(18) << "��" << std::setw(12) << male_num << std::fixed << std::setprecision(4) << double(male_num) / double(total) * 100 << "\n"
		<< std::setw(18) << "Ů" << std::setw(12) << total - male_num << std::fixed << std::setprecision(4) << double(total - male_num) / double(total) * 100 << "\n";
	std::cout << "+-------------------+-------------------+-------------------+\n";
	std::cout << std::resetiosflags(std::ios::left);// ���ø�ʽ�����
}

/***********************************************************
* Function Name:   ExaminationRegistrationSystem
* Function:        ���п��Ա���ϵͳ�������û����в��롢ɾ�������ҡ��޸ġ�ͳ�Ʋ���
* Input Parameter: 
* Returned Value:  
***********************************************************/
void ExaminationRegistrationSystem()
{
	std::cout << "+--------------------------------------------+" << std::endl;
	std::cout << "|                ��������ϵͳ                |" << std::endl;
	std::cout << "|       Examination Registration System      |" << std::endl;
	std::cout << "+--------------------------------------------+" << std::endl;
	std::cout << "�����뽨��������Ϣϵͳ��\n";
	LinkList<Examinee> examinee;// ���忼������
	MyBuild(examinee);// ��ʼ��������Ϣϵͳ
	while (true) {
		MyPrint(examinee); // ��ӡ��ǰ������Ϣ
		int ret = MySelect(examinee); // ��ȡ�û��Ĳ���ѡ��
		if (ret == 1)
			MyInsert(examinee);// ���뿼��
		else if (ret == 2) 
			MyExpurgate(examinee);// ɾ������
		else if (ret == 3) 
			MyFind(examinee); // ���ҿ���
		else if (ret == 4) 
			MyModify(examinee);// �޸Ŀ�����Ϣ
		else if (ret == 5) 
			MyStatisc(examinee);// ͳ�ƿ�����Ϣ
		else {
			break; // �˳�ϵͳ
		}
	}
	std::cout << "�ɹ��˳����Ա���ϵͳ��\n";
}

/***********************************************************
* Function Name:   main
* Function:        ������ڣ����ÿ��Ա���ϵͳ
* Input Parameter: 
* Returned Value:  0
***********************************************************/
int main()
{
	// �������Ա���ϵͳ
	ExaminationRegistrationSystem();

	return 0;
}
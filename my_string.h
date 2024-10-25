#pragma once

/***********************************************************
* File:     my_string.h
* Author:   Xiaolong Ma(��С��)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: Custom string class implementation
* Date:     2024.10.23
***********************************************************/

#include <iostream>
#include <assert.h>

namespace mine
{
	/***********************************************************
	* Class Name:   String
	* Function:     �Զ����ַ����࣬�ṩ�ַ����Ļ�������
	* Data Members: _str - �洢�ַ������ַ�����
	*                _str_len - �ַ�����ǰ����
	*                _str_cap - �ַ�����ǰ����
	* Member Functions:
	*                String(const char* str = "") - ���캯��
	*                String(const String& s) - �������캯��
	*                ~String() - ��������
	*                const char* C_str(const String& s) - ��ȡ�ַ���C����ʾ
	*                size_t Size()const - ��ȡ�ַ�������
	*                size_t Capacity()const - ��ȡ�ַ�������
	*                void Swap(String& s) - �����ַ�������
	*                void Reserve(size_t n) - Ԥ������
	*                void Resize(size_t n, char ch = '\0') - �����ַ�����С
	*                void PushBack(char ch) - ��ĩβ����ַ�
	*                void Append(const char* str) - ��ĩβ����ַ���
	*                void Insert(size_t pos, char ch, size_t n=1) - ��ָ��λ�ò����ַ�
	*                void Insert(size_t pos, const char* str) - ��ָ��λ�ò����ַ���
	*                void Erase(size_t pos, size_t len = npos) - ɾ��ָ��λ�õ��ַ�
	*                size_t Find(char ch, size_t pos = 0) - �����ַ�λ��
	*                size_t Find(const char* str, size_t pos = 0) - �����ַ���λ��
	*                String Substr(size_t pos = 0, size_t len = npos) - ��ȡ�Ӵ�
	*                void Clear() - ����ַ���
	*                String& operator+=(char ch) - �ַ�������������
	*                String& operator+=(const char* str) - �ַ���������������
	*                bool operator<(const String& s) const - С�����������
	*                bool operator==(const String& s) const - �������������
	*                bool operator<=(const String& s) const - С�ڵ������������
	*                bool operator>(const String& s) const - �������������
	*                bool operator>=(const String& s) const - ���ڵ������������
	*                bool operator!=(const String& s) const - ���������������
	*                char& operator[](size_t pos) - �±����������
	*                const char& operator[](size_t pos) const - �±���������أ�const��
	*                String& operator=(const String& s) - ��ֵ���������
	***********************************************************/
	class String
	{
	private:
		char* _str;// �洢�ַ������ַ�����
		size_t _str_len;  // ��ǰ����
		size_t _str_cap;  // ��ǰ����
	public:
		typedef char* iterator;
		typedef const char* const_iterator;

		iterator begin() { return _str; }// ��ȡ��������ʼλ��
		iterator end() { return _str + _str_len; }// ��ȡ����������λ��
		const_iterator begin() const { return _str; }// ��ȡ������������ʼλ��
		const_iterator end() const { return _str + _str_len; }// ��ȡ��������������λ��



		const static size_t npos = -1;// npos������ʾ��Чλ��
		String(const char* str = ""); // ���캯����Ĭ�Ͽ��ַ���
		String(const String& s); // �������캯��
		~String();// ��������
		const char* C_str ()const { return _str; }// ��ȡC����ַ���
		size_t Size()const { return _str_len; }// ��ȡ�ַ�������
		size_t Capacity()const { return _str_cap; }// ��ȡ�ַ�������
		// �����ַ�������
		void Swap(String& s) { std::swap(_str, s._str); std::swap(_str_len, s._str_len); std::swap(_str_cap, s._str_cap); }
		void Reserve(size_t n);// Ԥ������
		void Resize(size_t n, char ch = '\0');// �����ַ�����С
		void PushBack(char ch); // ��ĩβ����ַ�
		void Append(const char* str);
		void Insert(size_t pos, char ch, size_t n=1);// ��ָ��λ�ò����ַ�
		void Insert(size_t pos, const char* str);// ��ָ��λ�ò����ַ���
		void Erase(size_t pos, size_t len = npos);// ɾ��ָ��λ�õ��ַ�
		size_t Find(char ch, size_t pos = 0); // �����ַ�λ��
		size_t Find(const char* str, size_t pos = 0);// �����ַ���λ��
		String Substr(size_t pos = 0, size_t len = npos);// ��ȡ�Ӵ�
		void Clear(){_str[0] = '\0'; _str_len = 0;}// ����ַ���


		String& operator+=(char ch) { PushBack(ch); return *this; }// �ַ�������������
		String& operator+=(const char* str) { Append(str); return *this; }// �ַ���������������
		// С�����������
		bool operator<(const String& s) const { int ret = memcmp(_str, s._str, _str_len < s._str_len ? _str_len : s._str_len); return ret == 0 ? _str_len < s._str_len : ret < 0; }
		// �������������
		bool operator==(const String& s) const { return _str_len == s._str_len && memcmp(_str, s._str, _str_len) == 0; }
		// С�ڵ������������
		bool operator<=(const String& s) const { return *this < s || *this == s; }
		bool operator>(const String& s) const { return !(*this <= s); }// �������������
		bool operator>=(const String& s) const { return !(*this < s); }// ���ڵ������������
		bool operator!=(const String& s) const { return !(*this == s); }// ���������������
		char& operator[](size_t pos) { assert(pos < _str_len); return _str[pos]; } // �±����������
		const char& operator[](size_t pos) const { assert(pos < _str_len); return _str[pos]; }// �±���������أ�const��
		String& operator=(const String& s); // ��ֵ���������
	};

	/***********************************************************
	* Function Name:   String
	* Function:        ���캯������ʼ���ַ���
	* Input Parameter: str - ��ʼ�����ַ�����Ĭ�Ͽ��ַ�����
	* Returned Value:  ��
	***********************************************************/
	String::String(const char* str)
	{
		_str_len = strlen(str);
		_str_cap = _str_len;
		_str = new char[_str_cap + 1];//�࿪һλ�������'\0'
		memcpy(_str, str, _str_len + 1);
	}

	/***********************************************************
	* Function Name:   String
	* Function:        �������캯����������һ���ַ���
	* Input Parameter: s - �����Ƶ��ַ���
	* Returned Value:  ��
	***********************************************************/
	String::String(const String& s) :_str(new char[s._str_cap + 1]), _str_len(s._str_len), _str_cap(s._str_cap)
	{
		memcpy(_str, s._str, _str_len + 1);
	}

	/***********************************************************
	* Function Name:   ~String
	* Function:        �����������ͷ���Դ
	* Input Parameter:  ��
	* Returned Value:   ��
	***********************************************************/
	String::~String()
	{
		if (_str)
		{
			delete[] _str;// �ͷ��ڴ�
			_str = nullptr;// ��������ָ��
			_str_len = _str_cap = 0;// ���ó��Ⱥ�����
		}
	}

	/***********************************************************
    * Function Name:   Reserve
    * Function:        Ԥ����������չ�ַ�������
    * Input Parameter: n - �µ�����
    * Returned Value:  ��
    ***********************************************************/
	void String::Reserve(size_t n)
	{
		if (n > _str_cap){
			char* tmp = new char[n + 1];
			memcpy(tmp, _str, _str_len + 1);// ���Ƶ�ǰ����

			delete[] _str;
			_str = tmp;
			_str_cap = n;// ��������
		}
	}

	/***********************************************************
	* Function Name:   Resize
	* Function:        �����ַ�����С
	* Input Parameter: n - �µĴ�С, ch - ����ַ���Ĭ��Ϊ'\0'��
	* Returned Value:  ��
	***********************************************************/
	void String::Resize(size_t n, char ch)
	{
		if (n >= _str_len)
			Reserve(n);// Ԥ���㹻����
		for (size_t i = _str_len; i < n; i++)
			_str[i] = ch; // �����λ��
		_str_len = n;
		_str[_str_len] = '\0';
	}

	/***********************************************************
	* Function Name:   PushBack
	* Function:        ��ĩβ����ַ�
	* Input Parameter: ch - Ҫ��ӵ��ַ�
	* Returned Value:  ��
	***********************************************************/
	void String::PushBack(char ch)
	{
		Resize(_str_len + 1); // ��չ����
		_str[_str_len - 1] = ch; // ����ַ�
		_str[_str_len] = '\0'; // ������
	}

	/***********************************************************
	* Function Name:   Append
	* Function:        ��ĩβ����ַ���
	* Input Parameter: str - Ҫ��ӵ��ַ���
	* Returned Value:  ��
	***********************************************************/
	void String::Append(const char* str)
	{
		size_t len = strlen(str);
		Resize(_str_len + len); // ������С
		memcpy(_str + _str_len - len, str, len);
		_str[_str_len] = '\0';
	}

	/***********************************************************
	* Function Name:   Insert
	* Function:        ��ָ��λ�ò����ַ���
	* Input Parameter: pos - ����λ��, str - Ҫ������ַ���
	* Returned Value:  ��
	***********************************************************/
	void String::Insert(size_t pos, char ch, size_t n)
	{
		assert(pos <= _str_len);// ȷ��λ����Ч

		if (_str_len + n > _str_cap)
			Reserve(_str_len + n);// ��չ����
		// Ų������
		size_t end = _str_len;
		while (end >= pos && end != npos) {
			_str[end + n] = _str[end];
			--end;
		}
		//��������
		for (size_t i = 0; i < n; i++)
			_str[pos + i] = ch;

		_str_len += n;
	}

	/***********************************************************
	* Function Name:   Insert
	* Function:        ��ָ��λ�ò����ַ���
	* Input Parameter: pos - ����λ��, str - Ҫ������ַ���
	* Returned Value:  ��
	***********************************************************/
	void String::Insert(size_t pos, const char* str)
	{
		assert(pos <= _str_len);// ȷ��λ����Ч

		size_t len = strlen(str);
		if (_str_len + len > _str_cap)
			Reserve(_str_len + len);// ��չ����

		// Ų������
		size_t end = _str_len;
		while (end >= pos && end != npos) {
			_str[end + len] = _str[end];
			--end;
		}
		//��������
		for (size_t i = 0; i < len; i++)
			_str[pos + i] = str[i];

		_str_len += len;
	}

	/***********************************************************
	* Function Name:   Erase
	* Function:        ɾ��ָ��λ�õ��ַ�
	* Input Parameter: pos - Ҫɾ����λ��, len - ɾ������
	* Returned Value:  ��
	***********************************************************/
	void String::Erase(size_t pos, size_t len)
	{
		assert(pos <= _str_len);// ȷ��λ����Ч

		if (len == npos || pos + len >= _str_len) {
			_str_len = pos;
			_str[_str_len] = '\0';
		}
		else {
			size_t end = pos + len;
			while (end <= _str_len)
			{
				_str[pos++] = _str[end++];
			}
			_str_len -= len;// ���³���
		}
	}

	size_t String::Find(char ch, size_t pos)
	{
		assert(pos < _str_len);

		for (size_t i = pos; i < _str_len; i++)
			if (_str[i] == ch)
				return i;

		return npos;
	}

	/***********************************************************
	* Function Name:   Find
	* Function:        �����ַ�λ��
	* Input Parameter: ch - Ҫ���ҵ��ַ�, pos - ��ʼ���ҵ�λ��
	* Returned Value:  �ҵ���λ�ã�δ�ҵ�����npos
	***********************************************************/
	size_t String::Find(const char* str, size_t pos)
	{
		assert(pos < _str_len);

		const char* ptr = strstr(_str + pos, str);
		if (ptr)
			return ptr - _str;// �ҵ�����λ��
		else
			return npos;// δ�ҵ�����npos
	}

	/***********************************************************
	* Function Name:   Find
	* Function:        �����ַ���λ��
	* Input Parameter: str - Ҫ���ҵ��ַ���, pos - ��ʼ���ҵ�λ��
	* Returned Value:  �ҵ���λ�ã�δ�ҵ�����npos
	***********************************************************/
	String String::Substr(size_t pos, size_t len)
	{
		assert(pos < _str_len);// ȷ����ʼλ����Ч

		size_t n = len;
		if (len == npos || pos + len > _str_len)// ���������ȵ����
			n = _str_len - pos;

		String tmp;
		tmp.Reserve(n);
		for (size_t i = pos; i < pos + n; i++)
			tmp += _str[i];

		return tmp;
	}

	/***********************************************************
	* Function Name:   operator=
	* Function:        ��ֵ���������
	* Input Parameter: s - ��һ���ַ���
	* Returned Value:  ���ص�ǰ����
	***********************************************************/
	String& String::operator=(const String& s)
	{
		if (this != &s) { // ���Ҹ�ֵ���
			String tmp(s);
			Swap(tmp);
		}
		return *this;
	}

	/***********************************************************
    * Function Name:   operator<<
    * Function:        ���������������
    * Input Parameter: output - �������s - Ҫ������ַ���
    * Returned Value:  ���������
    ***********************************************************/
	std::ostream& operator<<(std::ostream& output, const String& s)
	{
		output << s.C_str();
		output.width(0);
		return output;
		
	}

	/***********************************************************
	*Function Name : operator>>
	*Function : ����������������
	* Input Parameter : input - ��������s - Ҫ�����ַ���
	* Returned Value : ����������
	* **********************************************************/
	std::istream& operator>>(std::istream& input, String& s)
	{
		s.Clear();// ��� String ������׼���µ�����

		char ch = input.get();
		// ����ǰ������ǰ��Ŀո���߻���
		while (ch == ' ' || ch == '\n')
			ch = input.get();

		//in >> ch;
		char buff[128];
		int i = 0;

		// �������ж�ȡ�ַ���ֱ�������ո���з�
		while (ch != ' ' && ch != '\n')
		{
			buff[i++] = ch;
			if (i == 127)
			{
				buff[i] = '\0';
				s += buff;
				
				i = 0;
			}
			ch = input.get();
		}

		if (i != 0)
		{
			buff[i] = '\0';
			s += buff;
		}

		return input;// ������������֧����ʽ����
	}
}
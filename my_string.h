#pragma once

/***********************************************************
* File:     my_string.h
* Author:   Xiaolong Ma(马小龙)
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
	* Function:     自定义字符串类，提供字符串的基本操作
	* Data Members: _str - 存储字符串的字符数组
	*                _str_len - 字符串当前长度
	*                _str_cap - 字符串当前容量
	* Member Functions:
	*                String(const char* str = "") - 构造函数
	*                String(const String& s) - 拷贝构造函数
	*                ~String() - 析构函数
	*                const char* C_str(const String& s) - 获取字符串C风格表示
	*                size_t Size()const - 获取字符串长度
	*                size_t Capacity()const - 获取字符串容量
	*                void Swap(String& s) - 交换字符串内容
	*                void Reserve(size_t n) - 预留容量
	*                void Resize(size_t n, char ch = '\0') - 调整字符串大小
	*                void PushBack(char ch) - 在末尾添加字符
	*                void Append(const char* str) - 在末尾添加字符串
	*                void Insert(size_t pos, char ch, size_t n=1) - 在指定位置插入字符
	*                void Insert(size_t pos, const char* str) - 在指定位置插入字符串
	*                void Erase(size_t pos, size_t len = npos) - 删除指定位置的字符
	*                size_t Find(char ch, size_t pos = 0) - 查找字符位置
	*                size_t Find(const char* str, size_t pos = 0) - 查找字符串位置
	*                String Substr(size_t pos = 0, size_t len = npos) - 获取子串
	*                void Clear() - 清空字符串
	*                String& operator+=(char ch) - 字符添加运算符重载
	*                String& operator+=(const char* str) - 字符串添加运算符重载
	*                bool operator<(const String& s) const - 小于运算符重载
	*                bool operator==(const String& s) const - 等于运算符重载
	*                bool operator<=(const String& s) const - 小于等于运算符重载
	*                bool operator>(const String& s) const - 大于运算符重载
	*                bool operator>=(const String& s) const - 大于等于运算符重载
	*                bool operator!=(const String& s) const - 不等于运算符重载
	*                char& operator[](size_t pos) - 下标运算符重载
	*                const char& operator[](size_t pos) const - 下标运算符重载（const）
	*                String& operator=(const String& s) - 赋值运算符重载
	***********************************************************/
	class String
	{
	private:
		char* _str;// 存储字符串的字符数组
		size_t _str_len;  // 当前长度
		size_t _str_cap;  // 当前容量
	public:
		typedef char* iterator;
		typedef const char* const_iterator;

		iterator begin() { return _str; }// 获取迭代器开始位置
		iterator end() { return _str + _str_len; }// 获取迭代器结束位置
		const_iterator begin() const { return _str; }// 获取常量迭代器开始位置
		const_iterator end() const { return _str + _str_len; }// 获取常量迭代器结束位置



		const static size_t npos = -1;// npos常量表示无效位置
		String(const char* str = ""); // 构造函数，默认空字符串
		String(const String& s); // 拷贝构造函数
		~String();// 析构函数
		const char* C_str ()const { return _str; }// 获取C风格字符串
		size_t Size()const { return _str_len; }// 获取字符串长度
		size_t Capacity()const { return _str_cap; }// 获取字符串容量
		// 交换字符串内容
		void Swap(String& s) { std::swap(_str, s._str); std::swap(_str_len, s._str_len); std::swap(_str_cap, s._str_cap); }
		void Reserve(size_t n);// 预留容量
		void Resize(size_t n, char ch = '\0');// 调整字符串大小
		void PushBack(char ch); // 在末尾添加字符
		void Append(const char* str);
		void Insert(size_t pos, char ch, size_t n=1);// 在指定位置插入字符
		void Insert(size_t pos, const char* str);// 在指定位置插入字符串
		void Erase(size_t pos, size_t len = npos);// 删除指定位置的字符
		size_t Find(char ch, size_t pos = 0); // 查找字符位置
		size_t Find(const char* str, size_t pos = 0);// 查找字符串位置
		String Substr(size_t pos = 0, size_t len = npos);// 获取子串
		void Clear(){_str[0] = '\0'; _str_len = 0;}// 清空字符串


		String& operator+=(char ch) { PushBack(ch); return *this; }// 字符添加运算符重载
		String& operator+=(const char* str) { Append(str); return *this; }// 字符串添加运算符重载
		// 小于运算符重载
		bool operator<(const String& s) const { int ret = memcmp(_str, s._str, _str_len < s._str_len ? _str_len : s._str_len); return ret == 0 ? _str_len < s._str_len : ret < 0; }
		// 等于运算符重载
		bool operator==(const String& s) const { return _str_len == s._str_len && memcmp(_str, s._str, _str_len) == 0; }
		// 小于等于运算符重载
		bool operator<=(const String& s) const { return *this < s || *this == s; }
		bool operator>(const String& s) const { return !(*this <= s); }// 大于运算符重载
		bool operator>=(const String& s) const { return !(*this < s); }// 大于等于运算符重载
		bool operator!=(const String& s) const { return !(*this == s); }// 不等于运算符重载
		char& operator[](size_t pos) { assert(pos < _str_len); return _str[pos]; } // 下标运算符重载
		const char& operator[](size_t pos) const { assert(pos < _str_len); return _str[pos]; }// 下标运算符重载（const）
		String& operator=(const String& s); // 赋值运算符重载
	};

	/***********************************************************
	* Function Name:   String
	* Function:        构造函数，初始化字符串
	* Input Parameter: str - 初始化的字符串（默认空字符串）
	* Returned Value:  无
	***********************************************************/
	String::String(const char* str)
	{
		_str_len = strlen(str);
		_str_cap = _str_len;
		_str = new char[_str_cap + 1];//多开一位用来存放'\0'
		memcpy(_str, str, _str_len + 1);
	}

	/***********************************************************
	* Function Name:   String
	* Function:        拷贝构造函数，复制另一个字符串
	* Input Parameter: s - 被复制的字符串
	* Returned Value:  无
	***********************************************************/
	String::String(const String& s) :_str(new char[s._str_cap + 1]), _str_len(s._str_len), _str_cap(s._str_cap)
	{
		memcpy(_str, s._str, _str_len + 1);
	}

	/***********************************************************
	* Function Name:   ~String
	* Function:        析构函数，释放资源
	* Input Parameter:  无
	* Returned Value:   无
	***********************************************************/
	String::~String()
	{
		if (_str)
		{
			delete[] _str;// 释放内存
			_str = nullptr;// 避免悬挂指针
			_str_len = _str_cap = 0;// 重置长度和容量
		}
	}

	/***********************************************************
    * Function Name:   Reserve
    * Function:        预留容量，扩展字符串容量
    * Input Parameter: n - 新的容量
    * Returned Value:  无
    ***********************************************************/
	void String::Reserve(size_t n)
	{
		if (n > _str_cap){
			char* tmp = new char[n + 1];
			memcpy(tmp, _str, _str_len + 1);// 复制当前内容

			delete[] _str;
			_str = tmp;
			_str_cap = n;// 更新容量
		}
	}

	/***********************************************************
	* Function Name:   Resize
	* Function:        调整字符串大小
	* Input Parameter: n - 新的大小, ch - 填充字符（默认为'\0'）
	* Returned Value:  无
	***********************************************************/
	void String::Resize(size_t n, char ch)
	{
		if (n >= _str_len)
			Reserve(n);// 预留足够容量
		for (size_t i = _str_len; i < n; i++)
			_str[i] = ch; // 填充新位置
		_str_len = n;
		_str[_str_len] = '\0';
	}

	/***********************************************************
	* Function Name:   PushBack
	* Function:        在末尾添加字符
	* Input Parameter: ch - 要添加的字符
	* Returned Value:  无
	***********************************************************/
	void String::PushBack(char ch)
	{
		Resize(_str_len + 1); // 扩展容量
		_str[_str_len - 1] = ch; // 添加字符
		_str[_str_len] = '\0'; // 结束符
	}

	/***********************************************************
	* Function Name:   Append
	* Function:        在末尾添加字符串
	* Input Parameter: str - 要添加的字符串
	* Returned Value:  无
	***********************************************************/
	void String::Append(const char* str)
	{
		size_t len = strlen(str);
		Resize(_str_len + len); // 调整大小
		memcpy(_str + _str_len - len, str, len);
		_str[_str_len] = '\0';
	}

	/***********************************************************
	* Function Name:   Insert
	* Function:        在指定位置插入字符串
	* Input Parameter: pos - 插入位置, str - 要插入的字符串
	* Returned Value:  无
	***********************************************************/
	void String::Insert(size_t pos, char ch, size_t n)
	{
		assert(pos <= _str_len);// 确保位置有效

		if (_str_len + n > _str_cap)
			Reserve(_str_len + n);// 扩展容量
		// 挪动数据
		size_t end = _str_len;
		while (end >= pos && end != npos) {
			_str[end + n] = _str[end];
			--end;
		}
		//插入数据
		for (size_t i = 0; i < n; i++)
			_str[pos + i] = ch;

		_str_len += n;
	}

	/***********************************************************
	* Function Name:   Insert
	* Function:        在指定位置插入字符串
	* Input Parameter: pos - 插入位置, str - 要插入的字符串
	* Returned Value:  无
	***********************************************************/
	void String::Insert(size_t pos, const char* str)
	{
		assert(pos <= _str_len);// 确保位置有效

		size_t len = strlen(str);
		if (_str_len + len > _str_cap)
			Reserve(_str_len + len);// 扩展容量

		// 挪动数据
		size_t end = _str_len;
		while (end >= pos && end != npos) {
			_str[end + len] = _str[end];
			--end;
		}
		//插入数据
		for (size_t i = 0; i < len; i++)
			_str[pos + i] = str[i];

		_str_len += len;
	}

	/***********************************************************
	* Function Name:   Erase
	* Function:        删除指定位置的字符
	* Input Parameter: pos - 要删除的位置, len - 删除长度
	* Returned Value:  无
	***********************************************************/
	void String::Erase(size_t pos, size_t len)
	{
		assert(pos <= _str_len);// 确保位置有效

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
			_str_len -= len;// 更新长度
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
	* Function:        查找字符位置
	* Input Parameter: ch - 要查找的字符, pos - 开始查找的位置
	* Returned Value:  找到的位置，未找到返回npos
	***********************************************************/
	size_t String::Find(const char* str, size_t pos)
	{
		assert(pos < _str_len);

		const char* ptr = strstr(_str + pos, str);
		if (ptr)
			return ptr - _str;// 找到返回位置
		else
			return npos;// 未找到返回npos
	}

	/***********************************************************
	* Function Name:   Find
	* Function:        查找字符串位置
	* Input Parameter: str - 要查找的字符串, pos - 开始查找的位置
	* Returned Value:  找到的位置，未找到返回npos
	***********************************************************/
	String String::Substr(size_t pos, size_t len)
	{
		assert(pos < _str_len);// 确保起始位置有效

		size_t n = len;
		if (len == npos || pos + len > _str_len)// 处理超出长度的情况
			n = _str_len - pos;

		String tmp;
		tmp.Reserve(n);
		for (size_t i = pos; i < pos + n; i++)
			tmp += _str[i];

		return tmp;
	}

	/***********************************************************
	* Function Name:   operator=
	* Function:        赋值运算符重载
	* Input Parameter: s - 另一个字符串
	* Returned Value:  返回当前对象
	***********************************************************/
	String& String::operator=(const String& s)
	{
		if (this != &s) { // 自我赋值检查
			String tmp(s);
			Swap(tmp);
		}
		return *this;
	}

	/***********************************************************
    * Function Name:   operator<<
    * Function:        输出流操作符重载
    * Input Parameter: output - 输出流，s - 要输出的字符串
    * Returned Value:  返回输出流
    ***********************************************************/
	std::ostream& operator<<(std::ostream& output, const String& s)
	{
		output << s.C_str();
		output.width(0);
		return output;
		
	}

	/***********************************************************
	*Function Name : operator>>
	*Function : 输入流操作符重载
	* Input Parameter : input - 输入流，s - 要填充的字符串
	* Returned Value : 返回输入流
	* **********************************************************/
	std::istream& operator>>(std::istream& input, String& s)
	{
		s.Clear();// 清空 String 对象以准备新的输入

		char ch = input.get();
		// 处理前缓冲区前面的空格或者换行
		while (ch == ' ' || ch == '\n')
			ch = input.get();

		//in >> ch;
		char buff[128];
		int i = 0;

		// 从输入中读取字符，直到遇到空格或换行符
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

		return input;// 返回输入流以支持链式操作
	}
}
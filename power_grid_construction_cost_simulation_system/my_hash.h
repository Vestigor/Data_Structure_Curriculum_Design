#ifndef MY_HASH_H
#define MY_HASH_H
/***********************************************************
* File:     my_hash.h
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Function: Hash Table
* Encoding: UTF-8
* Date:     2024.11.23
* Update:   2024.11.23
***********************************************************/
#include <cassert>
#include <cstring>
#include "my_string.h"

/***********************************************************
* Class:      Hash
* Function:   哈希表模板类，实现键值对存储与处理
***********************************************************/
template<typename Key, typename Value>
class Hash {
private:
    struct Node {
        Key key; // 键
        Value value; // 值
        Node *next; // 指向下一个节点，用于链表处理哈希冲突
        Node(const Key &k, const Value &v) : key(k), value(v), next(nullptr) {}
    };

    Node **buckets; // 哈希桶数组
    size_t bucket_count; // 哈希桶数量
    size_t size; // 当前存储的键值对数量

    size_t hash(const char key);

    size_t hash(const int key);

    size_t hash(const long key);

    size_t hash(const long long key);

    size_t hash_float(const float key);

    size_t hash(const double key);

    size_t hash(const unsigned int key);

    size_t hash(const unsigned long key);

    size_t hash(const unsigned long long key);

    size_t hash(const unsigned char key);

    size_t hash(const mine::String &key);

public:
    Hash(size_t bucket_count = 16);

    ~Hash();

    void make_empty();

    void insert(const Key &key, const Value &value);

    Value *find(const Key &key);

    void erase(const Key &key);

    size_t getSize() const;

    Value &operator[](const Key &key);
};


/***********************************************************
* Function Name:   Hash
* Function:        构造函数，初始化哈希表
* Input Parameter: bucket_count - 哈希桶数量，默认值为16
* Returned Value:  无
***********************************************************/
template<typename Key, typename Value>
Hash<Key, Value>::Hash(size_t bucket_count) : bucket_count(bucket_count), size(0)
{
    buckets = new(std::nothrow) Node *[bucket_count];
    assert(buckets != nullptr);
    for (size_t i = 0; i < bucket_count; i++)
        buckets[i] = nullptr;
    std::memset(buckets, 0, bucket_count * sizeof(Node *)); // 初始化为空
}

/***********************************************************
* Function Name:   ~Hash
* Function:        析构函数，释放哈希表资源
* Input Parameter: 无
* Returned Value:  无
***********************************************************/
template<typename Key, typename Value>
Hash<Key, Value>::~Hash()
{
    make_empty();
    delete[] buckets;
}

/***********************************************************
* Function Name:   make_empty
* Function:        清空哈希表，删除所有节点
* Input Parameter: 无
* Returned Value:  无
***********************************************************/
template<typename Key, typename Value>
void Hash<Key, Value>::make_empty()
{
    for (size_t i = 0; i < bucket_count; ++i) {
        Node *current = buckets[i];
        while (current != nullptr) {
            Node *to_delete = current;
            current = current->next;
            delete to_delete;
        }
        buckets[i]= nullptr;
    }
    size = 0;
}

/***********************************************************
* Function Name:   insert
* Function:        插入一个新的键值对，如果键已存在则更新值
* Input Parameter: key - 键
*                  value - 值
* Returned Value:  无
***********************************************************/
template<typename Key, typename Value>
void Hash<Key, Value>::insert(const Key &key, const Value &value)
{
    size_t index = hash(key);
    Node *current = buckets[index];
    while (current) {
        if (current->key == key) {
            current->value = value;// 如果键已存在，更新值
            return;
        }
        current = current->next;
    }
    Node *new_node = new(std::nothrow) Node(key, value);
    assert(new_node != nullptr);
    new_node->next = buckets[index];
    buckets[index] = new_node;
    ++size;
}

/***********************************************************
 * Function Name:   find
* Function:        查找给定键的值
* Input Parameter: key - 键
* Returned Value:  键对应的值指针，如果键不存在则返回 nullptr
***********************************************************/
template<typename Key, typename Value>
Value *Hash<Key, Value>::find(const Key &key)
{
    size_t index = hash(key);
    Node *current = buckets[index];
    while (current) {
        if (current->key == key) {
            return &current->value; // 返回键对应的值的地址
        }
        current = current->next;
    }
    return nullptr; // 键不存在，返回 nullptr
}

/***********************************************************
* Function Name:   erase
* Function:        删除给定键的键值对
* Input Parameter: key - 键
* Returned Value:  无
***********************************************************/
template<typename Key, typename Value>
void Hash<Key, Value>::erase(const Key &key)
{
    size_t index = hash(key);
    Node *current = buckets[index];
    Node *prev = nullptr;
    while (current) {
        if (current->key == key) {
            if (prev) {
                prev->next = current->next;
            }
            else {
                buckets[index] = current->next;
            }
            delete current;
            --size;
            return;// 删除并退出
        }
        prev = current;
        current = current->next;
    }
}

/***********************************************************
* Function Name:   getSize
* Function:        获取当前哈希表中键值对的数量
* Input Parameter: 无
* Returned Value:  当前键值对的数量
***********************************************************/
template<typename Key, typename Value>
size_t Hash<Key, Value>::getSize() const
{
    return size;
}

/***********************************************************
* Function Name:   operator[]
* Function:        重载索引操作符，查找键对应的值，如果键不存在则创建新节点
* Input Parameter: key - 键
* Returned Value:  键对应的值引用
***********************************************************/
template<typename Key, typename Value>
Value &Hash<Key, Value>::operator[](const Key &key)
{
    size_t index = hash(key);
    Node *current = buckets[index];
    while (current) {
        if (current->key == key) {
            return current->value;// 键存在，返回值
        }
        current = current->next;
    }
    Node *new_node = new(std::nothrow) Node(key, Value());
    assert(new_node != nullptr);
    new_node->next = buckets[index];
    buckets[index] = new_node;
    ++size;
    return new_node->value;// 键不存在，创建新节点并返回值
}


/***********************************************************
* Function Name:   hash
* Function:        各种类型哈希函数
* Input Parameter: key - 键
* Returned Value:  返回当前键对应的桶的索引
***********************************************************/

// 字符类型键的哈希函数
template<typename Key, typename Value>
size_t Hash<Key, Value>::hash(const char key)
{
    return static_cast<size_t>(key) % bucket_count;
}

// 整型键的哈希函数
template<typename Key, typename Value>
size_t Hash<Key, Value>::hash(const int key)
{
    return (key ^ (key >> 16)) % bucket_count;
}

// 长整型键的哈希函数
template<typename Key, typename Value>
size_t Hash<Key, Value>::hash(const long key)
{
    return (static_cast<size_t>(key) ^ (static_cast<size_t>(key) >> 16)) % bucket_count;
}

// 长长整型键的哈希函数
template<typename Key, typename Value>
size_t Hash<Key, Value>::hash(const long long key)
{
    return (static_cast<size_t>(key) ^ (static_cast<size_t>(key) >> 32)) % bucket_count;
}

// 单精度浮点类型键的哈希函数
template<typename Key, typename Value>
size_t Hash<Key, Value>::hash_float(const float key)
{
    union {
        float f;
        int i;
    } u;
    u.f = key;
    return hash(u.i);//借助整型键的哈希函数计算
}

// 双精度浮点类型键的哈希函数
template<typename Key, typename Value>
size_t Hash<Key, Value>::hash(const double key)
{
    union {
        double d;
        long long ll;
    } u;
    u.d = key;
    return hash(u.ll);//借助长长整型键的哈希函数计算
}

// 无符号整型键的哈希函数
template<typename Key, typename Value>
size_t Hash<Key, Value>::hash(const unsigned int key)
{
    return (key ^ (key >> 16)) % bucket_count;
}

// 无符号长整型键的哈希函数
template<typename Key, typename Value>
size_t Hash<Key, Value>::hash(const unsigned long key)
{
    return (static_cast<size_t>(key) ^ (static_cast<size_t>(key) >> 16)) % bucket_count;
}

// 无符号长长整型键的哈希函数
template<typename Key, typename Value>
size_t Hash<Key, Value>::hash(const unsigned long long key)
{
    return (static_cast<size_t>(key) ^ (static_cast<size_t>(key) >> 32)) % bucket_count;
}

// 无符号字符类型键的哈希函数
template<typename Key, typename Value>
size_t Hash<Key, Value>::hash(const unsigned char key)
{
    return static_cast<size_t>(key) % bucket_count;
}
// 字符串类型键的哈希函数
template<typename Key, typename Value>
size_t Hash<Key, Value>::hash(const mine::String &key)
{
    size_t hash = 5381; // djb2 初始哈希值
    for (char c: key) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % bucket_count;
}

#endif //MY_HASH_H
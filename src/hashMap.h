//
// Created by ll.md on 2022/4/8.
//

#ifndef COURSE_AUXILIARY_SYSTEM_HASHMAP_H
#define COURSE_AUXILIARY_SYSTEM_HASHMAP_H
#include <iostream>
#include <cassert>

using namespace std;

template<class T>
class Array{
public:
    T* vals;
    int size;
    int maxSize;
    Array(int _size) {
        size = 0;
        vals = new T[_size];
        maxSize = _size;
    }

    int getSize() const {
        return size;
    }

    const T *getVals() const {
        return vals;
    }

    T get(int i){
        if (i < size)
            return vals[i];
        else {
            cout << "出现错误，请联系开发者\n";
            return vals[0];
        }
    }

    bool push(T t){
        if (size >= maxSize)    return false;
        try {
            vals[size] = t;
        } catch (...){
            cout << "出现错误，请联系开发者\n";
            return false;
        }
        size++;
        return true;
    }

    virtual ~Array() {
        size = 0;
    }
};


static int primes[27] =
        {
                57, 97, 193, 389, 769,
                1543, 3079, 6151, 12289, 24593,
                49157, 98317, 196613, 393241, 786433,
                1572869, 3145739, 6291469, 12582917, 25165843,
                50331653, 100663319, 201326611, 402653189, 805306457,
        };//from web

template<class T1, class T2>
struct Pair {
    T1 first;
    T2 second;

    Pair() : first(T1()), second(T2()) {}

    Pair(T1 a, T2 b) : first(a), second(b) {}
};

template<class T>
struct TreeNode {// no use
    TreeNode *left, *right;
    T val;

    TreeNode() : left(nullptr), right(nullptr) {}

    TreeNode(T _val) : left(nullptr), right(nullptr), val(_val) {}
};

template<class T>
struct Node {//no use
    T val;
    Node *next;

    Node() : next(nullptr) {}

    Node(T _val) : next(nullptr), val(_val) {}
};

template<class T1, class T2>
class HashNode {
public:
    T1 key;
    T2 value;
    HashNode *next;

    HashNode(T1 _key, T2 _value) {
        key = _key;
        value = _value;
        next = nullptr;
    }

    HashNode &operator = (const HashNode &node) {
        key = node.key;
        value = node.value;
        next = node.next;
        return *this;
    }
};

template<class T1, class T2>
class HashMap {

public:
    HashMap(int);

    int put(T1 key, T2 value);

    Pair<bool, T2> * get(T1 key);

    int hash(int h) {
        h ^= (h >> 20) ^ (h >> 12);
        return h ^ (h >> 7) ^ (h >> 4);
    }//steal


    ~HashMap();

private:
    HashNode<T1, T2> **table;//指针数组
    int size{};
    T2* valNull = new T2();
};

template<class T1, class T2>
int HashMap<T1, T2>::put(T1 _key, T2 _value) {
    int index = hash(_key) % size;
    HashNode<T1, T2> *node = table[index];
    while (node) {
        if (node->key == _key) {
            node->value = _value;
            return -1;//已有该值,[修改]
        }
        node = node->next;
    }
    node = new HashNode<T1, T2>(_key, _value);
    node->next = table[index];
    table[index] = node;
    return index;
}

template<class T1, class T2>
HashMap<T1, T2>::~HashMap() {
    for (int i = 0; i < size; i++) {
        HashNode<T1, T2> *node = table[i];
        while (node) {
            HashNode<T1, T2> *tmp = node;
            node = node->next;
            delete tmp;
        }
    }
    delete table;
}

template<class T1, class T2>
Pair<bool, T2>* HashMap<T1, T2>::get(T1 _key) {
    int index = hash(_key) % size;
    HashNode<T1, T2> *node = table[index];
    while (node) {
        if (node->key == _key) {
            return new Pair<bool, T2>(true, node->value);
        }
        node = node->next;
    }
    return new Pair<bool, T2>(false, *valNull);
}

template<class T1, class T2>
HashMap<T1, T2>::HashMap(int _size) {
    this->size = _size;
    table = new HashNode<T1, T2> *[_size];
    for (int i = 0; i < _size; i++) {
        table[i] = nullptr;
    }
}


#endif //COURSE_AUXILIARY_SYSTEM_HASHMAP_H

#pragma once

#include<iostream>
#include "BST.h"

// ƽ�����������
template<class T>
class BBST : public BST<T> {
protected:
    BinNode<T>* leftRotation(BinNode<T>*);
    BinNode<T>* rightRotation(BinNode<T>*);
    BinNode<T>* leftRightRotation(BinNode<T>*);
    BinNode<T>* rightLeftRotation(BinNode<T>*);
    void inOrder(BinNode<T>*) const;
    void preOrder(BinNode<T>*) const;
    void postOrder(BinNode<T>*) const;
    void visitor(BinNode<T>*) const;
    BinNode<T>* insert(const T&);
    BinNode<T>* remove(BinNode<T>*);
    int height(BinNode<T>*) const; // ���߶�
    void updateHeight(BinNode<T>*); // ���½��߶�
public:
    BinNode<T>* Max() const;
    BinNode<T>* Min() const;
    BinNode<T>* search(const T&);
    bool erase(const T&);
    BinNode<T>* add(const T&);
    int Size() const { return this->size; }; // ���ؽ����
    void inOrder() const {
        if (this->root) inOrder(this->root);
        else std::cout << "Null";
    }; // �������
    void preOrder() const {
        if (this->root) preOrder(this->root);
        else std::cout << "Null";
    }; // ǰ�����
    void postOrder() const {
        if (this->root) postOrder(this->root);
        else std::cout << "Null";
    }; // �������
};

// �������ֵ���
template<class T>
BinNode<T>* BBST<T>::Max() const {
    BinNode<T>* p = this->root, * pp = nullptr;
    while (p) {
        pp = p;
        p = p->right;
    }
    return pp;
}

// ������Сֵ���
template<class T>
BinNode<T>* BBST<T>::Min() const {
    BinNode<T>* p = this->root, * pp = nullptr;
    while (p) {
        pp = p;
        p = p->left;
    }
    return pp;
}

// ����
template<class T>
BinNode<T>* BBST<T>::leftRotation(BinNode<T>* node) {
    BinNode<T>* child = node->right,
        * parent = node->parent;

    node->right = child->left;
    // ��㲻Ϊ��, ��Ҫ���¹����丸���
    if (node->right) node->right->parent = node;
    
    child->left = node;
    node->parent = child;
    
    child->parent = parent;
    
    // ���½��߶�
    updateHeight(node);
    updateHeight(child);

    return child;
}

// ����
template<class T>
BinNode<T>* BBST<T>::rightRotation(BinNode<T>* node) {
    BinNode<T>* child = node->left,
        *parent = node->parent;

    node->left = child->right;
    if (node->left) node->left->parent = node;
    
    child->right = node;
    node->parent = child;
    
    child->parent = parent;

    updateHeight(node);
    updateHeight(child);

    return child;
}

// ������������
template<class T>
BinNode<T>* BBST<T>::leftRightRotation(BinNode<T>* node) {
    node->left = leftRotation(node->left);
    return rightRotation(node);
}

// ������������
template<class T>
BinNode<T>* BBST<T>::rightLeftRotation(BinNode<T>* node) {
    node->right = rightRotation(node->right);
    return leftRotation(node);
}

// �������
template<class T>
void BBST<T>::inOrder(BinNode<T>* node) const {
    if (node) {
        inOrder(node->left);
        visitor(node);
        inOrder(node->right);
    }
}

// ǰ�����
template<class T>
void BBST<T>::preOrder(BinNode<T>* node) const  {
    if (node) {
        visitor(node);
        preOrder(node->left);
        preOrder(node->right);
    }
}

// �������
template<class T>
void BBST<T>::postOrder(BinNode<T>* node) const  {
    if (node) {
        postOrder(node->left);
        postOrder(node->right);
        visitor(node);
    }
}

// �鿴�����Ϣ
template<class T>
inline void BBST<T>::visitor(BinNode<T>* node) const {
    std::cout << node->data << "(" << node->height << ") ";
}

// ɾ��
template<class T>
BinNode<T>* BBST<T>::remove(BinNode<T>* x) {
    BinNode<T>* succ = nullptr, * w = x;

    if (w->left == nullptr || w->right == nullptr) { // ����֧�ṹ
        if (w->left == nullptr) succ = w->right;
        else succ = x->left;

        if (w->isLeftChild()) {
            w->parent->left = succ;
        }
        else if (w->isRightChild()) {
            w->parent->right = succ;
        }
        else {
            this->root = succ;
        }
    }
    else { // ˫��֧�ṹ
        w = w->right;
        
        // ��������������Сֵ���
        while (w->left) {
            w = w->left;
        }

        // ������ɾ�������������Сֵ��������
        std::swap(x->data, w->data);

        BinNode<T>* u = w->parent;
        
        // ʵ�ʱ�ɾ������������ʵ�ʱ�ɾ���ĸ����
        ((u == x) ? u->right : u->left) = succ = w->right;
    }

    this->hot = w->parent;

    if (succ) succ->parent = this->hot;
    
    delete w; // ɾ�����ս��
    
    return succ; // ���ش�����
}

template<class T>
bool BBST<T>::erase(const T& e) {
    BinNode<T>* x = search(e);
    if (!x) return false; // Ŀ�겻����

    remove(x);
    if (--this->size <= 0) return true;

    // ���ϸ��¸����߶�
    for (BinNode<T>* p = this->hot; p; p = p->parent) {
        updateHeight(p);
    }

    return true;
}

// ��ȡ���ĸ߶�
template<class T>
int BBST<T>::height(BinNode<T>* node) const {
    if (node) return node->height;
    else return 0;
}

// ���½��߶�
template<class T>
void BBST<T>::updateHeight(BinNode<T>* node) {
    int h1 = height(node->left),
        h2 = height(node->right);
    node->height = h1 > h2 ? h1 + 1 : h2 + 1;
}; 

// ����
template<class T>
BinNode<T>* BBST<T>::search(const T& e) {
    BinNode<T>* p = this->root;
    this->hot = nullptr;

    while (p) {
        if (e == p->data) {
            return p;
        }
        else {
            this->hot = p;
            if (e < p->data) {
                p = p->left;
            }
            else if (e > p->data) {
                p = p->right;
            }
        }
    }
    // ��ƥ�����
    return nullptr;
}

// ����
template<class T>
BinNode<T>* BBST<T>::add(const T& e) {
    BinNode<T>* x = search(e);
    if (x) return x; // ���������, ���ظý��

    // ��㲻����, ������ֵ
    x = insert(e);

    // ���ϸ��½�� x ���������ȵĸ߶�
    for (BinNode<T>* p = x->parent; p; p = p->parent) {
        updateHeight(p);
    }

    return x;
}

template<class T>
BinNode<T>* BBST<T>::insert(const T& e) {
    BinNode<T>* x = new BinNode<T>(e, this->hot);
    
    if (!x->isRoot()) {
        if (x->data > this->hot->data) {
            this->hot->right = x;
        }
        else {
            this->hot->left = x;
        }
    }
    else {
        this->root = x;
    }

    this->size++;

    return x;
}
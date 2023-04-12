#pragma once

#include "BBST.h"

// AVL ��
template<class T>
class AVLTree: public BBST<T> {
    bool isBalence(BinNode<T>*) const;
    void reBalence(BinNode<T>*);
    int bf(BinNode<T>* node) const;
public:
    bool erase(const T&);
    BinNode<T>* add(const T&);
};

// ����Ƿ�ƽ��
template<class T>
bool AVLTree<T>::isBalence(BinNode<T>* node) const {
    int delta = bf(node);
    if (delta > -2 && delta < 2) return true;
    else return false;
}

// �������ƽ��
template<class T>
void AVLTree<T>::reBalence(BinNode<T>* node) {
    // ���ж� node �Ǹ�, ���ӻ����Һ���
    bool left = false, right = false;
    if (node->isLeftChild()) left = true;
    else if (node->isRightChild()) right = true;

    BinNode<T>* n = nullptr, * p = node->parent;

    if (bf(node) == 2) { // ƽ������Ϊ 2
        if (this->height(node->left->left) >= this->height(node->left->right)) {
            // node ���ӵ�����������, ��������
            n = this->rightRotation(node);
        }
        else {
            // ������������
            n = this->leftRightRotation(node);
        }
    }
    else {
        if (this->height(node->right->left) <= this->height(node->right->right)) {
            // node �Һ��ӵ�����������, ��������
            n = this->leftRotation(node);
        }
        else {
            // ������������
            n = this->rightLeftRotation(node);
        }
    }

    if (left) {
        p->left = n;
    }
    else if (right) {
        p->right = n;
    }
    else {
        this->root = n;
    }
}

// ���ؽ���ƽ������
template<class T>
int AVLTree<T>::bf(BinNode<T>* node) const {
    return this->height(node->left) - this->height(node->right);
}

// ɾ��
template<class T>
bool AVLTree<T>::erase(const T& e) {
    BinNode<T>* x = this->search(e);
    if (!x) return false; // Ԫ�ز�����, ɾ��ʧ��

    this->remove(x);
    if (--this->size <= 0) return true;

    for (BinNode<T>* g = this->hot; g; g = g->parent) {
        if (!isBalence(g)) {
            reBalence(g);
        }
        this->updateHeight(g);
    }

    return true;
}

// ���
template<class T>
BinNode<T>* AVLTree<T>::add(const T& e) {
    BinNode<T>* x = this->search(e);
    if (x) return x; // ���������, ���ظý��

    x = this->insert(e); // ������ֵ
    
    for (BinNode<T>* p = x->parent; p; p = p->parent) {
        if (!isBalence(p)) {
            reBalence(p);
            // ֻҪĳ����ƽ����ƽ����
            // ���Ӧ���ȶ���ƽ��
            // ��˿���ֱ���˳���ƽ�����
            break;
        }
        else {
            // ��Ϊ������ĸ���һ����ƽ���
            // ���ֻ��Ҫ������߶�
            // ʵ����ƽ���Ǵ����游��㿪ʼ
            this->updateHeight(p);
        }
    }

    return x;
}
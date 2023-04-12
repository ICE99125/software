#pragma once

// �����ɫ
enum class Color { RED, BLACK };

// �����
template<class T>
struct BinNode {
    T data;
    BinNode<T>* parent; // �����
    BinNode<T>* left; // ����
    BinNode<T>* right; // �ҽ��
    int height; // �߶�
    int blackHeight; // �ڸ߶�
    Color color; // �����ɫ
    
    // ���캯��
    BinNode() : parent(nullptr), left(nullptr), right(nullptr), height(1), blackHeight(0), color(Color::RED) {};
    BinNode(T e, BinNode<T>* p = nullptr, int h = 1, BinNode<T>* l = nullptr, BinNode<T>* r = nullptr,
        Color c = Color::RED) :data(e), parent(p), left(l), right(r), height(h), color(c), blackHeight(0) {};
    
    // �Ƿ��Ǹ����
    bool isRoot() const { return parent == nullptr; };
    
    // �Ƿ�������
    // ��������Ǹ����, �Ͳ���ʲô����
    // ��β����丸�����Һ���
    bool isLeftChild() { return !isRoot() && this == parent->left; };
    
    // �Ƿ����Һ���
    bool isRightChild() { return !isRoot() && this == parent->right; };
    
    // ��ȡ����
    BinNode<T>* uncle() const;
};

template<class T>
BinNode<T>* BinNode<T>::uncle() const {
    if (isRoot()) { return nullptr; } // ����㲻��������
    else if (parent->isLeftChild()) {
        // ����丸����������ȵ�����
        // ���������ȵ��Һ���
        return parent->parent->right;
    }
    else if (parent->isRightChild()) {
        return parent->parent->left;
    }
    else {
        // ������Ǹ����, û������
        return nullptr;
    }
}
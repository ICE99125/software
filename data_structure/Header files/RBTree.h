#pragma once

#include<iostream>
#include "BBST.h"

// �����
template <class T>
class RedBlack: public BBST<T> {
protected:
    void solveDoubleRed(BinNode<T>* const); // ˫������
    void solveDoubleBlack(BinNode<T>* const); // ˫������
    int updateBlackHeight(BinNode<T>*); // ���ºڽڵ�߶�
    bool blackHeightUpdated(BinNode<T>*); // �Ƿ���Ҫ���ºڸ߶�
    bool isBlack(BinNode<T>* const) const;
    void visitor(BinNode<T>* const) const;
    int blackHeight(BinNode<T>* const) const;
public:
    bool erase(const T&);
    BinNode<T>* add(const T&);
};

// �ж�ĳ���ڵ��Ƿ��Ǻ�ɫ�ڵ�
template<class T>
bool RedBlack<T>::isBlack(BinNode<T>* const x) const {
    // �ⲿ�ڵ�(nullptr)Ҳ�Ǻ�ɫ�ڵ�
    if (x == nullptr || x->color == Color::BLACK) {
        return true;
    }
    else {
        return false;
    }
}

// ˫������
template<class T>
void RedBlack<T>::solveDoubleRed(BinNode<T>* const x) {
    if (x->isRoot()) { // �ݹ�����, ��������
        this->root->color = Color::BLACK; // ˫����������ʱ(��ʱ��Ϊ��), ����ֻ��Ϊ��
        this->root->blackHeight++;
        return;
    }

    BinNode<T>* p = x->parent;
    if (isBlack(p)) return; // �� p Ϊ��ɫ�ڵ�, ˵������˫����, �����˳�

    // p Ϊ��ɫ, ˵�� p �������Ǹ�, g �������ǿ�
    BinNode<T>* g = p->parent;
    BinNode<T>* u = x->uncle(); // ��ȡ x ����ڵ�, ����Ϊ null

    if (isBlack(u)) {
        // x ����ڵ��Ǻ�ɫ, ���ǡ�˫������-1��
        // ֻ�������������
        BinNode<T>* gg = g->parent, // �游�ڵ�(����Ϊ null)
            * root_ = nullptr;
        // ���ж� gg �����ӻ����Һ���, �����Ǹ�
        bool left = g->isLeftChild();
        bool right = g->isRightChild();

        if (x->isLeftChild() && p->isLeftChild()) {
            // x �� p ��������, ��������
            p->blackHeight++; // ��ʱ p ���ɺڽڵ�, �ڸ߶�����
            p->color = Color::BLACK;
            root_ = this->rightRotation(g); // ��᷵�����������ĸ��ڵ�
        }
        else if (x->isRightChild() && p->isLeftChild()) {
            // p ������, x ���Һ���, ������������
            x->blackHeight++;
            x->color = Color::BLACK;
            root_ = this->leftRightRotation(g);
        }
        else if (x->isRightChild() && p->isRightChild()) {
            // x �� p �����Һ���, ��������
            p->blackHeight++;
            p->color = Color::BLACK;
            root_ = this->leftRotation(g);
        }
        else {
            // x ������, p ���Һ���, ������������
            x->blackHeight++;
            x->color = Color::BLACK;
            root_ = this->rightLeftRotation(g);
        }

        // g һ������
        g->blackHeight--;
        g->color = Color::RED;

        if (left) {
            gg->left = root_;
        }
        else if (right) {
            gg->right = root_;
        }
        else {
            // g �Ǹ��ڵ�
            this->root = root_;
        }
    }
    else {
        // ��ڵ��Ǻ�ɫ, ���ǡ�˫������-2��
        p->color = Color::BLACK;
        p->blackHeight++;
        u->color = Color::BLACK;
        u->blackHeight++;
        if (!g->isRoot()) g->color = Color::RED; // g ���Ǹ�, ��ת��
        solveDoubleRed(g);
    }
}

// ˫������
template<class T>
void RedBlack<T>::solveDoubleBlack(BinNode<T>* const x) {
    BinNode<T>* p = x ? x->parent : this->hot;
    if (!p) return; // ���ڵ㲻����, ����Ҫ����

    // x ����Ϊ��, ����ʹ�� x.isLeftChild()
    BinNode<T>* s = (x == p->left) ? p->right : p->left; // x ���ֵ�

    BinNode<T>* t = nullptr, /*��ʱ�ڵ�*/* g = p->parent; // �游�ڵ�

    if (isBlack(s)) { // �ֵ�Ϊ��ɫ�ڵ�
        if (!isBlack(s->left) || !isBlack(s->right)) {
            // �ֵܵĺ캢�Ӵ���, ���С�˫������-1��
            Color color = p->color; // ���ݸ��ڵ���ɫ

            bool left = p->isLeftChild();
            bool right = p->isRightChild();

            if (!isBlack(s->left)) {
                // �ֵ�����Ϊ��
                if (s->isLeftChild()) {
                    // �ֵ�Ϊ����, ��������
                    t = this->rightRotation(p);
                }
                else {
                    // �ֵ�Ϊ�Һ���, ������������
                    t = this->rightLeftRotation(p);
                }
            }
            else {
                // �ֵ��Һ���Ϊ��
                if (s->isLeftChild()) {
                    // �ֵ�Ϊ����, ������������
                    t = this->leftRightRotation(p);
                }
                else {
                    // �ֵ�Ϊ�Һ���, ��������
                    t = this->leftRotation(p);
                }
            }

            if (left) {
                g->left = t;
            }
            else if (right) {
                g->right = t;
            }
            else {
                // p ԭ���Ǹ��ڵ�, ��ת����Ҫ�Ѹ��ڵ㻻���µ�
                this->root = t;
            }

            // ����Ⱦ��
            t->left->color = Color::BLACK;
            updateBlackHeight(t->left);

            t->right->color = Color::BLACK;
            updateBlackHeight(t->right);

            // �ָ���ɫ
            t->color = color;
            updateBlackHeight(t);
        }
        else {
            // �ֵܵĺ캢�Ӳ�����
            s->color = Color::RED;
            s->blackHeight--;
            if (!isBlack(p)) {
                // ���ڵ�Ϊ��ɫ, ���С�˫������-2��
                p->color = Color::BLACK;
            }
            else {
                // ���ڵ�Ϊ��ɫ, ���С�˫������-3��
                p->blackHeight--;
                solveDoubleBlack(p);
            }
        }
    }
    else {
        // �ֵ�Ϊ��ɫ�ڵ�, ����˫���޸�-4��
        // s һ������ڸ��ڵ�
        s->color = Color::BLACK;
        s->blackHeight++;
        p->color = Color::RED;
        p->blackHeight--;

        bool left = p->isLeftChild();
        bool right = p->isRightChild();

        if (s->isLeftChild()) {
            // �ֵܽڵ�������, ��������
            t = this->rightRotation(p);
        }
        else {
            // �ֵܽڵ����Һ���, ��������
            t = this->leftRotation(p);
        }

        // p �Ǹ��ڵ�Ͳ���Ҫ���� g �ĺ���
        if (left) {
            g->left = t;
        }
        else if (right) {
            g->right = t;
        }
        else {
            this->root = t;
        }

        solveDoubleBlack(x);
    }
}

// ���ºڽڵ�߶�
template<class T>
int RedBlack<T>::updateBlackHeight(BinNode<T>* const x) {
    int h1 = blackHeight(x->left), h2 = blackHeight(x->right);
    x->blackHeight = h1 > h2 ? h1 : h2;
    return isBlack(x) ? x->blackHeight++ : x->blackHeight;
}

// �ڸ߶ȸ�������
template<class T>
bool RedBlack<T>::blackHeightUpdated(BinNode<T>* const x) {
    // ���������ڸ߶����, �ҵ�ǰ�ڵ�ڸ߶ȵ��������ڸ߶�(��Ϊ�ڽڵ�ʱ+1)
    return blackHeight(x->left) == blackHeight(x->right) &&
        x->blackHeight == (isBlack(x) ? blackHeight(x->left) + 1 : blackHeight(x->left));
}

// ����
template<class T>
BinNode<T>* RedBlack<T>::add(const T& e) {
    BinNode<T>* x = this->search(e);
    if (x) return x; // ����ڵ����, ���ظýڵ�

    x = this->insert(e);

    solveDoubleRed(x); // ˫������
    
    return x;
}

// ��д�鿴�����Ϣ�ķ���
template<class T>
void RedBlack<T>::visitor(BinNode<T>* node) const {
    std::cout << node->data << "("
        << (node->color == Color::BLACK ? "B" : "R")
        << ", " << node->blackHeight
        << ")\n";
}

// ��ȡ���ڸ߶�
template<class T>
inline int RedBlack<T>::blackHeight(BinNode<T>* node) const {
    if (node) return node->blackHeight;
    else return 0;
}

// ɾ��
template<class T>
bool RedBlack<T>::erase(const T& e) {
    BinNode<T>* x = this->search(e);
    if (!x) return false; // Ŀ�겻����

    BinNode<T>* r = this->remove(x);

    // �ڵ㶼ɾ����, ɶ�������޸�, ֱ���˳�
    if (--this->size <= 0) return true;

    // ���ٴ���һ�����ڵ�...
    if (!this->hot) { // ��ɾ�ڵ�Ϊ���ڵ�
        this->root->color = Color::BLACK;
        this->root->blackHeight++;
        return true;
    }

    // δ����˫��...
    if (blackHeightUpdated(this->hot)) return true;

    // �滻�ڵ�Ϊ��ɫ
    if (!isBlack(r)) {
        r->color = Color::BLACK;
        r->blackHeight++;
        return true;
    }

    solveDoubleBlack(r); // ˫������

    return true;
}
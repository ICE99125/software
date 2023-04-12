#pragma once

#include<iostream>
#include<vector>

// B �����
template<class T>
struct BTNode {
    BTNode<T>* parent;
    std::vector<T> key; // �ؼ���
    std::vector<BTNode<T>*> child;
    BTNode() { parent = nullptr;  child.push_back(nullptr); };
    BTNode(T e, BTNode<T>* left = nullptr, BTNode<T>* right = nullptr);
    int search(const T& e) const;
};

template<class T>
inline BTNode<T>::BTNode(T e, BTNode<T>* left, BTNode<T>* right) {
    parent = nullptr;
    key.push_back(e);
    child.push_back(left);
    child.push_back(right);
    if (left) left->parent = this;
    if (right) right->parent = this;
}

// �ڹؼ���������˳�����Ԫ��
template<class T>
int BTNode<T>::search(const T& e) const {
    for (int i = 0; i < key.size(); i++) {
        // ƥ��ͷ���������
        // ��ƥ�䷵�����һ��С�� e ������
        if (e == key[i]) return i;
        else if (e < key[i]) return i - 1;
    }

    // e �����йؼ��붼��
    // �������һ��ֵ������
    return key.size() - 1;
}


// B ��
template<class T>
class BTree {
    int size; // �ؼ�����
    int order; // ��
    BTNode<T>* root;
    BTNode<T>* hot;
    void solveOverFlow(BTNode<T>*);
    void solveUnderFlow(BTNode<T>*);
    void ASC(BTNode<T>* node) const;
    void inOrder(BTNode<T>*) const;
    void preOrder(BTNode<T>*) const;
    void postOrder(BTNode<T>*) const;
public:
    BTree(int o) : order(o), size(0), hot(nullptr) { root = new BTNode<T>(); };
    BTNode<T>* search(const T&);
    bool add(const T&);
    bool erase(const T&);
    void ASC() const { if (root->key.size()) ASC(root); else std::cout << "Null"; };
    void inOrder() const { if (root->key.size()) inOrder(root); else std::cout << "Null"; };
    void preOrder() const { if (root->key.size()) preOrder(root); else std::cout << "Null"; };
    void postOrder() const { if (root->key.size()) postOrder(root); else std::cout << "Null"; };
};

// �������
template<class T>
void BTree<T>::solveOverFlow(BTNode<T>* node) {
    if (node->child.size() > order) { // ��������
        int mid = node->key.size() / 2;

        // ���ѳ�������
        BTNode<T>* right = new BTNode<T>();
        int len = node->key.size() - mid - 1; // ������ key �ĸ���
        for (int i = 0; i < len; i++) {
            right->key.insert(right->key.begin() + i, node->key[mid + 1]);
            node->key.erase(node->key.begin() + (mid + 1)); // ������������ͬʱɾ�����Ԫ��
            right->child.insert(right->child.begin() + i, node->child[mid + 1]);
            node->child.erase(node->child.begin() + (mid + 1));
        }
        // child �� key ��һ��(ע�����ﲻ�ǲ���, �����滻, new ��ʱ���Ѿ���һ���ӽ��)
        right->child[len] = node->child[mid + 1];
        node->child.erase(node->child.begin() + (mid + 1));

        // ͳһ�������ĸ����
        if (right->child[0]) {
            // right ��Ҷ������ӽ����и����
            for (int j = 0; j < right->child.size(); j++) {
                right->child[j]->parent = right;
            }
        }

        BTNode<T>* p = node->parent;
        if (!p) {
            // �����ǰ����Ǹ����
            // �½�һ���½����Ϊ�¸����
            root = p = new BTNode<T>();
            p->child[0] = node;
            node->parent = p;
        }

        int r = p->search(node->key[mid]);
        p->key.insert(p->key.begin() + (r + 1), node->key[mid]);
        // ��Ҫ����ɾ�� mid Ԫ��
        node->key.erase(node->key.begin() + mid);
        p->child.insert(p->child.begin() + (r + 2), right);
        // ����������
        right->parent = p;

        // ���������⸸���
        solveOverFlow(p);
    }
}

// ����ϲ�
template<class T>
void BTree<T>::solveUnderFlow(BTNode<T>* node) {
    if ((order + 1) / 2 > node->child.size()) { // ��������

        BTNode<T>* p = node->parent;
        if (!p) { // �� node �Ǹ����
            if (!node->key.size() && node->child[0]) {
                // ���ҽ����Ϊ��, ��������ڷǿպ���
                // root ָ����ǿպ���
                root = node->child[0];
                root->parent = nullptr;
                delete node;
            }
            return;
        }

        // node �� p �ĵ� r ������
        int r = 0;
        while (p->child[r] != node) {
            r++;
        }

        // ��ת
        if (r > 0) { // node �ǵ�һ������
            BTNode<T>* ls = p->child[r - 1]; // �ȿ����ֵ�

            if ((order + 1) / 2 < ls->child.size()) { // ���ֵ���һ����������
                // �򸸽���һ��
                node->key.insert(node->key.begin(), p->key[r - 1]);
                // �ֵܽ�����ֵ�������
                p->key[r - 1] = ls->key.back();
                ls->key.pop_back();
                // �ֵ����һ�����ӹ��̸� node
                node->child.insert(node->child.begin(), ls->child.back());
                ls->child.pop_back(); // ��Ҫ����ɾ�����ֵ����һ������
                // ������Ӳ�Ϊ null, ��Ҫ�޸��丸��
                if (node->child[0]) node->child[0]->parent = node;
                return;
            }
        }

        if (r < p->child.size() - 1) {
            BTNode<T>* rs = p->child[r + 1]; // �������ֵ�

            if ((order + 1) / 2 < rs->child.size()) {
                // �� node �����λ�ò��븸���ֵ
                node->key.push_back(p->key[r]);
                // ���ֵܽ���һ��ֵ�������
                p->key[r] = rs->key[0];
                // ɾ�����ֵܵ�һ�����
                rs->key.erase(rs->key.begin());
                // �����ֵܵĵ�һ�����ӹ��̸� node
                node->child.push_back(rs->child[0]);
                rs->child.erase(rs->child.begin()); // ��Ҫ���˰����ֵܵ�һ������ɾ��
                if (node->child.back()) node->child.back()->parent = node;
                return;
            }
        }

        // �ϲ�
        if (r > 0) {
            BTNode<T>* ls = p->child[r - 1];
            // ���ֵܼ���ճ�ϼ�
            ls->key.push_back(p->key[r - 1]);
            // ����Ϊճ�ϼ��ĸ����Ĺؼ���Ӹ�������Ƴ�
            p->key.erase(p->key.begin() + (r - 1));
            // �� node �� p.child ���Ƴ�
            p->child.erase(p->child.begin() + r);

            // ��Ϊ child ���Ǳ� key ��һ��, Ϊ��� while д����һ��
            ls->child.push_back(node->child[0]);
            node->child.erase(node->child.begin());
            if (ls->child.back()) {
                ls->child.back()->parent = ls;
            }
            // �� node ʣ�ຢ���𲽹��̸����ֵ�
            while (!node->key.empty()) {
                ls->key.push_back(node->key[0]);
                node->key.erase(node->key.begin());
                ls->child.push_back(node->child[0]);
                node->child.erase(node->child.begin());
                // ������Ӳ�Ϊ null, �丸�׸ĳ����ֵ�
                if (ls->child.back()) {
                    ls->child.back()->parent = ls;
                }
            }
            delete node;
        }
        else {
            BTNode<T>* rs = p->child[r + 1];
            node->key.push_back(p->key[r]);
            p->key.erase(p->key.begin() + r);
            // �����ֵܴӸ������ɾ��
            p->child.erase(p->child.begin() + (r + 1));

            // �����ֵܵĺ��ӹ��̸� node
            node->child.push_back(rs->child[0]);
            rs->child.erase(rs->child.begin());
            if (node->child.back()) node->child.back()->parent = node;
            while (!rs->key.empty()) {
                node->key.push_back(rs->key[0]);
                rs->key.erase(rs->key.begin());
                node->child.push_back(rs->child[0]);
                rs->child.erase(rs->child.begin());
                if (node->child.back()) node->child.back()->parent = node;
            }
            delete rs;
        }
        // p ɾ��һ��������ܳ�������
        solveUnderFlow(p);
    }
}

// ����������
template<class T>
void BTree<T>::ASC(BTNode<T>* node) const {
    if (node) {
        int i = 0;
        for (; i < node->key.size(); i++) {
            ASC(node->child[i]);
            std::cout << node->key[i] << " ";
        }
        ASC(node->child[i]);
    }
}

// �������
template<class T>
void BTree<T>::inOrder(BTNode<T>* node) const {
    if (node) {
        inOrder(node->child[0]);
        std::cout << "[";
        int i = 0;
        for (; i < node->key.size() - 1; i++) {
            std::cout << node->key[i] << " ";
        }
        std::cout << node->key[i] << "] ";
        for (int j = 1; j < node->child.size(); j++) {
            inOrder(node->child[j]);
        }
    }
}

// ǰ�����
template<class T>
void BTree<T>::preOrder(BTNode<T>* node) const {
    if (node) {
        std::cout << "[";
        int i = 0;
        for (; i < node->key.size() - 1; i++) {
            std::cout << node->key[i] << " ";
        }
        std::cout << node->key[i] << "] ";
        for (int j = 0; j < node->child.size(); j++) {
            preOrder(node->child[j]);
        }
    }
}

// �������
template<class T>
void BTree<T>::postOrder(BTNode<T>* node) const {
    if (node) {
        for (int j = 0; j < node->child.size(); j++) {
            preOrder(node->child[j]);
        }
        std::cout << "[";
        int i = 0;
        for (; i < node->key.size() - 1; i++) {
            std::cout << node->key[i] << " ";
        }
        std::cout << node->key[i] << "] ";
    }
}

// ����Ԫ��
template<class T>
BTNode<T>* BTree<T>::search(const T& e) {
    BTNode<T>* v = root;
    hot = nullptr;

    while (v) {
        int r = v->search(e);
        if (r >= 0 && e == v->key[r]) return v; // �ҵ�Ԫ��

        // hot ���� e �ĸ����(�� e ������)
        // ���� e ��Ӧ���ڵĽ��(�� e ��������)
        // �� v->child[r] == null, hot ָ��Ҷ���
        hot = v;
        v = v->child[r + 1];
    }

    return nullptr;
}

// ������
template<class T>
bool BTree<T>::add(const T& e) {
    BTNode<T>* v = search(e);
    if (v) return false; // ����ظ�, ����ʧ��

    int r = hot->search(e);
    hot->key.insert(hot->key.begin() + (r + 1), e);
    hot->child.insert(hot->child.begin() + (r + 2), nullptr);

    size++;
    solveOverFlow(hot); // �������
    return true;
}

// ɾ�����
template<class T>
bool BTree<T>::erase(const T& e) {
    BTNode<T>* v = search(e); // ���ұ�ɾԪ��
    if (!v) return false;
    
    int r = v->search(e); // ���λ�ÿ϶��Ǿ�ȷ��
    //std::cout << "�ҵ���ɾԪ��" << e << "λ��" << r << "Ԫ�ظ��ڵ�" << v->parent << "\n";
    
    if (v->child[0]) {
        // v ��Ҷ���
        BTNode<T>* u = v->child[r + 1];
        while (u->child[0]) {
            u = u->child[0];
        }
        v->key[r] = u->key[0];
        v = u;
        r = 0;
    }

    v->key.erase(v->key.begin() + r);
    // ɾ�ĸ�������, Ҷ���� child ���� nullptr
    v->child.erase(v->child.begin() + r);
    size--;

    solveUnderFlow(v); // ����ϲ�

    return true;
}


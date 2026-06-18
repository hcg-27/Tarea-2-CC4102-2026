#include "avl.hpp"
#include <algorithm>

NodoAVL::NodoAVL(unsigned int k) : key(k), height(1), left(nullptr), right(nullptr) {}

AVL::AVL() : root(nullptr) {}

AVL::~AVL() {
    destroyTree(root);
}

void AVL::destroyTree(NodoAVL* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

int AVL::height(NodoAVL* node) {
    if (node == nullptr) return 0;
    return node->height;
}

int AVL::BF(NodoAVL* node) {
    if (node == nullptr) return 0;
    return height(node->left) - height(node->right);
}

void AVL::updateHeight(NodoAVL* node) {
    if (node != nullptr) {
        node->height = 1 + std::max(height(node->left), height(node->right));
    }
}

NodoAVL* AVL::zig(NodoAVL* y) {
    NodoAVL* x = y->left;
    NodoAVL* B = x->right;

    x->right = y;
    y->left = B;

    updateHeight(y);
    updateHeight(x);

    return x;
}

NodoAVL* AVL::zag(NodoAVL* y) {
    NodoAVL* x = y->right;
    NodoAVL* B = x->left;

    x->left = y;
    y->right = B;

    updateHeight(y);
    updateHeight(x);

    return x;
}

NodoAVL* AVL::insertNode(NodoAVL* node, unsigned int key) {
    if (node == nullptr) return new NodoAVL(key);

    if (key < node->key) {
        node->left = insertNode(node->left, key);
    } else if (key > node->key) {
        node->right = insertNode(node->right, key);
    } else {
        return node;
    }

    updateHeight(node);

    int balance = BF(node);

    if (balance == 2 && BF(node->left) >= 0) {
        return zig(node);
    }

    if (balance == -2 && BF(node->right) <= 0) {
        return zag(node);
    }

    if (balance == 2 && BF(node->left) < 0) {
        node->left = zag(node->left);
        return zig(node);
    }

    if (balance == -2 && BF(node->right) > 0) {
        node->right = zig(node->right);
        return zag(node);
    }

    return node;
}

bool AVL::searchNode(NodoAVL* node, unsigned int key) {
    if (node == nullptr) return false;

    if (node->key == key) return true;

    if (key < node->key) {
        return searchNode(node->left, key);
    } else {
        return searchNode(node->right, key);
    }
}

void AVL::insert(unsigned int x) {
    root = insertNode(root, x);
}

bool AVL::search(unsigned int x) {
    return searchNode(root, x);
}
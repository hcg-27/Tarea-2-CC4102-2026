#include "splay.hpp"

NodoSplay::NodoSplay(unsigned int k) : key(k), left(nullptr), right(nullptr), parent(nullptr) {}

Splay::Splay() : root(nullptr) {}

Splay::~Splay() {
    destroyTree(root);
}

void Splay::destroyTree(NodoSplay* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

void Splay::setParent(NodoSplay* child, NodoSplay* parent) {
    if (child)
        child->parent = parent;
}

void Splay::rotate(NodoSplay* child, NodoSplay* parent) {
    NodoSplay* grandparent = parent->parent;

    if (grandparent && grandparent->left == parent)
        grandparent->left = child;
    else if (grandparent && grandparent->right == parent)
        grandparent->right = child;

    if (parent->left == child) {
        parent->left = child->right;
        child->right = parent;
    }
    else {
        parent->right = child->left;
        child->left = parent;
    }

    setParent(child->left, child);
    setParent(child->right, child);
    setParent(parent->left, parent);
    setParent(parent->right, parent);
    child->parent = grandparent;
    if (!child->parent)
        root = child;
}

NodoSplay* Splay::splay(NodoSplay* vertex) {
    if (!vertex->parent) {
        root = vertex;
        return vertex;
    }

    NodoSplay* parent = vertex->parent;
    NodoSplay* grandparent = parent->parent;

    if (!grandparent) {
        rotate(vertex, parent);
        root = vertex;
        return vertex;
    }

    if ((grandparent->left == parent && parent->left == vertex) ||
        (grandparent->right == parent && parent->right == vertex)) {
        rotate(parent, grandparent);
        rotate(vertex, parent);
    }
    else {
        rotate(vertex, parent);
        rotate(vertex, grandparent);
    }
    return splay(vertex);
}

NodoSplay* Splay::find(NodoSplay* vertex, unsigned int data) {
    if (!vertex)
        return nullptr;
    if (vertex->key < data && vertex->right)
        return find(vertex->right, data);
    else if (vertex->key > data && vertex->left)
        return find(vertex->left, data);
    return splay(vertex);
}

NodoSplay** Splay::split(NodoSplay* vertex, unsigned int data) {
    NodoSplay** splitted = new NodoSplay*[2];

    if (!vertex) {
        splitted[0] = splitted[1] = nullptr;
        return splitted;
    }

    vertex = find(vertex, data);

    if (vertex->key < data) {
        splitted[0] = vertex;
        splitted[1] = vertex->right;
        setParent(vertex->right, nullptr);
        vertex->right = nullptr;
    }
    else {
        splitted[0] = vertex->left;
        splitted[1] = vertex;
        setParent(vertex->left, nullptr);
        vertex->left = nullptr;
    }
    return splitted;
}

NodoSplay* Splay::merge(NodoSplay* treeRoot, NodoSplay* rootNode) {
    if (treeRoot == nullptr)
        return rootNode;
    if (rootNode == nullptr)
        return treeRoot;
    
    NodoSplay* right = find(rootNode, treeRoot->key);
    right->right = treeRoot;
    treeRoot->parent = right;
    
    return right;
}

NodoSplay* Splay::insertNode(NodoSplay* vertex, unsigned int data) {
    NodoSplay** splitted = split(vertex, data);
    NodoSplay* newRoot = new NodoSplay(data);
    newRoot->left = splitted[0];
    newRoot->right = splitted[1];
    setParent(newRoot->left, newRoot);
    setParent(newRoot->right, newRoot);
    root = newRoot;
    delete[] splitted;
    return newRoot;
}

NodoSplay* Splay::removeNode(NodoSplay* vertex, unsigned int data) {
    vertex = find(vertex, data);
    setParent(vertex->left, nullptr);
    setParent(vertex->right, nullptr);
    NodoSplay* merged = merge(vertex->left, vertex->right);
    vertex->left = vertex->right = nullptr;
    delete vertex;
    root = merged;
    return merged;
}

void Splay::insert(unsigned int x) {
    root = insertNode(root, x);
}

bool Splay::search(unsigned int x) {
    if (root == nullptr)
        return false;
    root = find(root, x);
    return root && root->key == x;
}

void Splay::remove(unsigned int x) {
    if (root != nullptr)
        root = removeNode(root, x);
}

#ifndef SPLAY_HPP
#define SPLAY_HPP

#include "utils.hpp"

struct NodoSplay {
    unsigned int key;
    NodoSplay* left;
    NodoSplay* right;
    NodoSplay* parent;

    NodoSplay(unsigned int k);
};

class Splay : public Arbol<NodoSplay> {
private:
    NodoSplay* root;

    void setParent(NodoSplay* child, NodoSplay* parent);
    void rotate(NodoSplay* child, NodoSplay* parent);
    NodoSplay* splay(NodoSplay* vertex);
    NodoSplay* find(NodoSplay* vertex, unsigned int data);
    NodoSplay** split(NodoSplay* vertex, unsigned int data);
    NodoSplay* merge(NodoSplay* treeRoot, NodoSplay* root);
    NodoSplay* insertNode(NodoSplay* vertex, unsigned int data);
    NodoSplay* removeNode(NodoSplay* vertex, unsigned int data);
    void destroyTree(NodoSplay* node);

public:
    Splay();
    ~Splay();
    void insert(unsigned int x);
    bool search(unsigned int x);
    void remove(unsigned int x);
};

#endif

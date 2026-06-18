#ifndef AVL_HPP
#define AVL_HPP

#include "utils.hpp"

struct NodoAVL {
    unsigned int key;
    int height;
    NodoAVL* left;
    NodoAVL* right;

    NodoAVL(unsigned int k);
};

class AVL : public Arbol<NodoAVL> {
private:
    NodoAVL* root;

    int height(NodoAVL* node);
    int BF(NodoAVL* node);
    void updateHeight(NodoAVL* node);
    NodoAVL* zig(NodoAVL* y);
    NodoAVL* zag(NodoAVL* y);
    NodoAVL* insertNode(NodoAVL* node, unsigned int key);
    bool searchNode(NodoAVL* node, unsigned int key);
    void destroyTree(NodoAVL* node);

public:
    AVL();
    ~AVL();
    void insert(unsigned int x);
    bool search(unsigned int x);
};

#endif
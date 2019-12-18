//
// Created by Андрей Москалёв on 24.10.2019.
//

#ifndef TREESPRESENTATION_SPLAYTREE_H
#define TREESPRESENTATION_SPLAYTREE_H

#include "Node.h"
#include <algorithm>

class SplayTree {
public:
    Node * root = nullptr;
    void insert(int key) {
        root = _insert(key, root);
    }
    void remove(int key) {
        root = _remove(key, root);
    }
    int height() {
        return _height(root);
    }

private:
    Node * _rotateRight(Node * k2);

    Node * _rotateLeft(Node * k2);

    Node * _splay(int key, Node * root);

    Node * _insert(int key, Node * root);

    Node * _remove(int key, Node * root);

    Node * _findNode(int key, Node * root);

    int _height(Node * x);
};


#endif //TREESPRESENTATION_SPLAYTREE_H

//
// Created by Андрей Москалёв on 2019-10-14.
//

#ifndef TREESPRESENTATION_AVLTREE_H
#define TREESPRESENTATION_AVLTREE_H

#include "Node.h"

class AVLTree {
public:
    Node * root;

    AVLTree() {
        this->root = nullptr;
    }

    int height() {
        return _height(root);
    }

    void insert(int k) {
        if (_findKey(root, k) == nullptr)
            root = _insert(root, k);
    }

    void remove(int k) {
        root = _remove(root, k);
    }

    int maxLen() {
        return _maxLen(root);
    }

private:
    int _height(Node * p);

    int _balanceDiff(Node * p);

    void _fixHeight(Node * p);

    int _maxLen(Node * p);

    Node * _rotateRight(Node * p);

    Node * _rotateLeft(Node * q);

    Node * _balance(Node * p);

    Node * _insert(Node * p, int k);

    Node * _findMin(Node * p);

    Node * _removeMin(Node * p);

    Node * _remove(Node * p, int k);

    Node * _findKey(Node * p, int k);

};

#endif //TREESPRESENTATION_AVLTREE_H

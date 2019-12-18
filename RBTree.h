//
// Created by Андрей Москалёв on 24.10.2019.
//

#ifndef TREESPRESENTATION_RBTREE_H
#define TREESPRESENTATION_RBTREE_H

#include "Node.h"

class RBTree {
public:
    Node * root;
    RBTree();
    void insert(int key) {
        _insert(key);
    }

    void remove(int key) {
        _remove(key);
    }

private:
    void _rotateLeft(Node * x);

    void _rotateRight(Node * x);

    void _balance_insert(Node *&x);

    void _insert(int key);

    void _balance_remove(Node *&x);

    void _removeNode(Node *&z);

    void _remove(int key);

    Node * _find(int key);

    int _recountHeights(Node *&p);

};


#endif //TREESPRESENTATION_RBTREE_H

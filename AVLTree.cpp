//
// Created by Андрей Москалёв on 2019-10-14.
//

#include <string>
#include "AVLTree.h"

int AVLTree::_height(Node * p) {
    return p != nullptr ? p->height : 0;
}

int AVLTree::_balanceDiff(Node * p) {
    return _height(p->right) - _height(p->left);
}

void AVLTree::_fixHeight(Node * p) {
    int height_left = _height(p->left);
    int height_right = _height(p->right);
    p->height = (height_left > height_right ? height_left : height_right) + 1;
}

Node * AVLTree::_rotateRight(Node * p) {
    Node * q = p->left;
    p->left = q->right;
    q->right = p;
    _fixHeight(p);
    _fixHeight(q);
    return q;
}

Node * AVLTree::_rotateLeft(Node * q) {
    Node * p = q->right;
    q->right = p->left;
    p->left = q;
    _fixHeight(q);
    _fixHeight(p);
    return p;
}

Node * AVLTree::_balance(Node * p) {
    _fixHeight(p);
    if (_balanceDiff(p) == 2) {
        if (_balanceDiff(p->right) < 0) {
            p->right = _rotateRight(p->right);
        }
        return _rotateLeft(p);
    }
    if (_balanceDiff(p) == -2) {
        if (_balanceDiff(p->left) > 0) {
            p->left = _rotateLeft(p->left);
        }
        return _rotateRight(p);
    }
    return p;
}

Node * AVLTree::_insert(Node * p, int k) {
    if (p == nullptr)
        return new Node(k);
    if (k < p->key)
        p->left = _insert(p->left, k);
    else
        p->right = _insert(p->right, k);
    return _balance(p);
}

Node * AVLTree::_findMin(Node * p) {
    return p->left != nullptr ? _findMin(p->left) : p;
}

Node * AVLTree::_removeMin(Node * p) {
    if (p->left == nullptr) {
        return p->right;
    }
    p->left = _removeMin(p->left);
    return _balance(p);
}

Node * AVLTree::_remove(Node * p, int k) {
    if (p == nullptr) {
        return nullptr;
    }
    if (k < p->key) {
        p->left = _remove(p->left, k);
    } else if (k > p->key) {
        p->right = _remove(p->right, k);
    } else {
        Node * q = p->left;
        Node * r = p->right;
        delete p;
        if (r == nullptr) {
            return q;
        }
        Node * min = _findMin(r);
        min->right = _removeMin(r);
        min->left = q;
        return _balance(min);
    }
    return _balance(p);
}

Node * AVLTree::_findKey(Node * p, int k) {
    if (p == nullptr)
        return nullptr;
    if (p->key == k) {
        return p;
    }
    if (p->key > k) {
        return _findKey(p->left, k);
    }
    else {
        return _findKey(p->right, k);
    }
}

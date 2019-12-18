//
// Created by Андрей Москалёв on 24.10.2019.
//

#include "RBTree.h"

void RBTree::_rotateLeft(Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
        y->left->parent = x;
    }
    if (y != nullptr) {
        y->parent = x->parent;
    }
    if (x->parent != nullptr) {
        if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
    } else {
        root = y;
    }
    y->left = x;
    if (x != nullptr) {
        x->parent = y;
    }
}

void RBTree::_rotateRight(Node *x) {
    Node *y = x->left;
    x->left = y->right;
    if (y->right != nullptr) {
        y->right->parent = x;
    }
    if (y != nullptr) {
        y->parent = x->parent;
    }
    if (x->parent) {
        if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
    } else {
        root = y;
    }
    y->right = x;
    if (x != nullptr) {
        x->parent = y;
    }
}

void RBTree::_balance_insert(Node *&x) {
    while (x != root && x->parent->color == 1) {
        if (x->parent == x->parent->parent->left) {
            Node *y = x->parent->parent->right;
            if (y != nullptr && y->color == 1) {
                x->parent->color = 0;
                y->color = 0;
                x->parent->parent->color = 1;
                x = x->parent->parent;
            } else {
                if (x == x->parent->right) {
                    x = x->parent;
                    _rotateLeft(x);
                }
                x->parent->color = 0;
                x->parent->parent->color = 1;
                _rotateRight(x->parent->parent);
            }
        } else {
            Node *y = x->parent->parent->left;
            if (y != nullptr && y->color == 1) {
                x->parent->color = 0;
                y->color = 0;
                x->parent->parent->color = 1;
                x = x->parent->parent;
            } else {
                if (x == x->parent->left) {
                    x = x->parent;
                    _rotateRight(x);
                }
                x->parent->color = 0;
                x->parent->parent->color = 1;
                _rotateLeft(x->parent->parent);
            }
        }
    }
    root->color = 0;
}

void RBTree::_insert(int key) {
    Node *current, *parent, *x;
    current = root;
    parent = nullptr;
    while (current != nullptr) {
        if (key == current->key) {
            return;
        }
        parent = current;
        current = key < current->key ? current->left : current->right;
    }
    x = new Node();
    x->parent = parent;
    x->left = nullptr;
    x->right = nullptr;
    x->color = 1;
    x->key = key;
    if (parent != nullptr) {
        if (key < parent->key)
            parent->left = x;
        else
            parent->right = x;
    } else {
        root = x;
    }

    _balance_insert(x);
    _recountHeights(root);
}

void RBTree::_balance_remove(Node *&x) {
    if (x == nullptr) {
        return;
    }
    while (x != root && x->color == 0) {
        if (x == x->parent->left) {
            Node *w = x->parent->right;
            if (w->color == 1) {
                w->color = 0;
                x->parent->color = 1;
                _rotateLeft(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == 0 && w->right->color == 0) {
                w->color = 1;
                x = x->parent;
            } else {
                if (w->right->color == 0) {
                    w->left->color = 0;
                    w->color = 1;
                    _rotateRight(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = 0;
                w->right->color = 0;
                _rotateLeft(x->parent);
                x = root;
            }
        } else {
            Node *w = x->parent->left;
            if (w->color == 1) {
                w->color = 0;
                x->parent->color = 1;
                _rotateRight(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == 0 && w->left->color == 0) {
                w->color = 1;
                x = x->parent;
            } else {
                if (w->left->color == 0) {
                    w->right->color = 0;
                    w->color = 1;
                    _rotateLeft(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = 0;
                w->left->color = 0;
                _rotateRight(x->parent);
                x = root;
            }
        }
    }
    x->color = 0;
}

void RBTree::_removeNode(Node *&z) {
    Node *x, *y;
    if (z->left == nullptr || z->right == nullptr) {
        y = z;
    } else {
        y = z->right;
        while (y->left != nullptr) {
            y = y->left;
        }
    }
    if (y->left != nullptr) {
        x = y->left;
    } else {
        x = y->right;
    }
    if (x != nullptr) {
        x->parent = y->parent;
    }
    if (y->parent != nullptr)
        if (y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }
    else {
        root = x;
    }
    if (y != z) {
        z->key = y->key;
    }
    if (y->color == 0) {
        _balance_remove(x);
    }
}

void RBTree::_remove(int key) {
    auto v = _find(key);
    if (v == nullptr) {
        return;
    }
    _removeNode(v);
    _recountHeights(root);
}

Node * RBTree::_find(int key) {
    Node * current = root;
    while (current != nullptr) {
        if (key == current->key) {
            return current;
        } else {
            current = key < current->key ? current->left : current->right;
        }
    }
    return current;
}

RBTree::RBTree() {
    root = nullptr;
}

int RBTree::_recountHeights(Node *&p) {
    if (p == nullptr) {
        return 0;
    }
    return p->height = std::max(_recountHeights(p->right),
                           _recountHeights(p->left)) + 1;
}

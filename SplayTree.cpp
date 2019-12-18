//
// Created by Андрей Москалёв on 24.10.2019.
//

#include "SplayTree.h"


Node * SplayTree::_rotateRight(Node * k2) {
    Node * k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    return k1;
}

Node * SplayTree::_rotateLeft(Node * k2) {
    Node * k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    return k1;
}

Node * SplayTree::_splay(int key, Node * root) {
    if (root == nullptr)
        return nullptr;
    Node head;
    head.left = head.right = nullptr;
    Node * leftMx = &head;
    Node * rightMn = &head;
    while (true) {
        if (key < root->key) {
            if (root->left == nullptr) {
                break;
            }
            if (key < root->left->key) {
                root = _rotateRight(root);
                if (root->left == nullptr)
                    break;
            }
            rightMn->left = root;
            rightMn = rightMn->left;
            root = root->left;
            rightMn->left = nullptr;
        }
        else if (key > root->key) {
            if (root->right == nullptr)
                break;
            if (key > root->right->key) {
                root = _rotateLeft(root);
                if (root->right == nullptr)
                    break;
            }
            leftMx->right = root;
            leftMx = leftMx->right;
            root = root->right;
            leftMx->right = nullptr;
        }
        else
            break;
    }
    leftMx->right = root->left;
    rightMn->left = root->right;
    root->left = head.right;
    root->right = head.left;
    return root;
}

Node * SplayTree::_insert(int key, Node * root) {
    static Node * p_node = nullptr;
    if (p_node == nullptr)
        p_node = new Node(key);
    else
        p_node->key = key;
    if (root == nullptr) {
        root = p_node;
        p_node = nullptr;
        return root;
    }
    root = _splay(key, root);
    if (key < root->key) {
        p_node->left = root->left;
        p_node->right = root;
        root->left = nullptr;
        root = p_node;
    } else if (key > root->key) {
        p_node->right = root->right;
        p_node->left = root;
        root->right = nullptr;
        root = p_node;
    } else
        return root;
    p_node = nullptr;
    return root;
}

Node * SplayTree::_remove(int key, Node * root) {
    Node * tmp;
    if (root == nullptr) {
        return nullptr;
    }
    root = _splay(key, root);
    if (key != root->key)
        return root;
    else {
        if (root->left == nullptr) {
            tmp = root;
            root = root->right;
        } else {
            tmp = root;

            root = _splay(key, root->left);
            root->right = tmp->right;
        }
        delete tmp;
        return root;
    }
}

Node * SplayTree::_findNode(int key, Node * root) {
    return _splay(key, root);
}

int SplayTree::_height(Node * x) {
    if (x == nullptr) {
        return 0;
    }
    int hLeft = 0, hRight = 0;
    if (x->left != nullptr) {
        hLeft = _height(x->left);
    }
    if (x->right != nullptr) {
        hRight = _height(x->right);
    }
    return 1 + std::max(hLeft, hRight);
}

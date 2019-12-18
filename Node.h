//
// Created by Андрей Москалёв on 24.10.2019.
//

#ifndef TREESPRESENTATION_NODE_H
#define TREESPRESENTATION_NODE_H

#include <string>

struct Node {
    int key, height, color = 0;
    Node * left, * right, * parent;
    explicit Node(bool IS_RED = false) {
        this->left = this->right = nullptr;
        this->color = IS_RED;
    }
    explicit Node(int k, bool IS_RED = false) {
        this->key = k;
        this->left = this->right = nullptr;
        this->height = 1;
        this->color = IS_RED;
    }
    explicit Node(int k, Node * parent, bool IS_RED = false) {
        this->key = k;
        this->left = this->right = nullptr;
        this->height = 1;
        this->color = IS_RED;
    }
    int treeSize() {
        int szL = 0, szR = 0;
        if (left != nullptr)
            szL = left->treeSize();
        if (right != nullptr)
            szR = right->treeSize();
        return szL + szR + 1;
    }
    int maxLen() {
        int szL = 0, szR = 0;
        if (left != nullptr)
            szL = left->maxLen();
        if (right != nullptr)
            szR = right->maxLen();
        int sz = std::to_string(key).size();
        return std::max(sz, std::max(szL, szR));
    }
};

#endif //TREESPRESENTATION_NODE_H

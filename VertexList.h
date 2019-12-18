//
// Created by Андрей Москалёв on 21.10.2019.
//

#ifndef TREESPRESENTATION_VERTEXLIST_H
#define TREESPRESENTATION_VERTEXLIST_H


#include <QWidget>
#include <QVBoxLayout>
#include <QToolButton>
#include <QLabel>
#include <vector>
#include <QListWidget>
#include <QLineEdit>
#include <QDebug>

class VertexListItem : public QWidget {
Q_OBJECT

public:
    explicit VertexListItem(int value, QListWidget * list, QWidget * parent = nullptr);
    ~VertexListItem() override = default;
    int value;
    void remove();
    QListWidget * list;
    signals:
        void removedItem();
private:
    QHBoxLayout * mainHBoxLayout;
};

class VertexList : public QWidget {
Q_OBJECT
public:
    explicit VertexList(QWidget * parent = nullptr);
    ~VertexList() override = default;
    bool add(int vToAdd);
    int itemsCount();
    void removeProxy();
    bool remove(int key);
    std::vector<VertexListItem *> getItems();
    QListWidget * mainList;
    signals:
    void removedItem(int key);
};


#endif //TREESPRESENTATION_VERTEXLIST_H

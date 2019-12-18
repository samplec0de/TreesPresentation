//
// Created by Андрей Москалёв on 21.10.2019.
//

#include <QScrollArea>
#include "VertexList.h"

VertexList::VertexList(QWidget * parent) : QWidget(parent) {
    auto mainLayout = new QVBoxLayout(this);
    this->setStyleSheet("background-color: rgb(43, 43, 43);");
    auto scrollArea = new QScrollArea();
    scrollArea->setContentsMargins(0, 0, 0, 0);
    mainList = new QListWidget;
    mainList->setSpacing(5);
    mainLayout->addWidget(scrollArea);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    scrollArea->setWidget(mainList);
    scrollArea->setWidgetResizable(true);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void VertexList::removeProxy() {
    int key = ((VertexListItem*)(sender()))->value;
    VertexList::removedItem(key);
}

std::vector<VertexListItem *> VertexList::getItems() {
    std::vector<VertexListItem *> result;
    for (int i = 0; i < mainList->count(); ++i) {
        auto item = mainList->item(i);
        VertexListItem * vertexItem = ((VertexListItem*)(this->mainList->itemWidget(item)));
        if (vertexItem != nullptr)
            result.push_back(vertexItem);
    }
    return result;
}

bool VertexList::add(int vToAdd) {
    bool exist = false;
    for (auto now : this->getItems()) {
        if (now == nullptr) continue;
        if (vToAdd == now->value) {
            exist = true;
            break;
        }
    }
    if (exist) {
        return false;
    }
    auto item = new QListWidgetItem(mainList);
    auto elem = new VertexListItem(vToAdd, mainList);
    connect(elem, &VertexListItem::removedItem, this, &VertexList::removeProxy);
    elem->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    item->setSizeHint(elem->sizeHint());
    mainList->setItemWidget(item, elem);
    mainList->addItem(item);
    return true;
}

bool VertexList::remove(int key) {
    bool exist = false;
    for (auto now : this->getItems()) {
        if (now == nullptr) continue;
        if (key == now->value) {
            exist = true;
            break;
        }
    }
    if (!exist) {
        return false;
    }
    for (int i = 0; i < mainList->count(); ++i) {
        auto item = ((VertexListItem*)(mainList->itemWidget(mainList->item(i))));
        if (item->value == key) {
            mainList->removeItemWidget(mainList->takeItem(i));
            break;
        }
    }
    return true;
}

void VertexListItem::remove() {
    auto parent = sender()->property("item").value<VertexListItem *>();
    auto parentList = parent->list;
    for (int i = 0; i < parentList->count(); ++i) {
        QListWidgetItem * item = parentList->item(i);
        if (((VertexListItem*)(parentList->itemWidget(item)))->value == parent->value) {
            parentList->removeItemWidget(parentList->takeItem(i));
            break;
        }
    }
    VertexListItem::removedItem();
}

VertexListItem::VertexListItem(int value, QListWidget * list, QWidget *parent) : QWidget(parent) {
    this->list = list;
    this->setStyleSheet("VertexListItem {"
                        "background-color: grey;"
                        "}");
    mainHBoxLayout = new QHBoxLayout(this);
    mainHBoxLayout->setContentsMargins(0, 0, 10, 0);
    auto removeButton = new QToolButton;
    removeButton->setAutoRaise(true);
    removeButton->setStyleSheet("QToolButton {"
                                "background-color: rgba(250, 10, 10, 0.5);"
                                "}"
                                "QToolButton:hover {"
                                "background-color: rgb(240, 10, 10);"
                                "}"
                                "QToolButton:pressed {"
                                "background-color: rgb(250, 10, 10);"
                                "}");
    QPixmap trashIconPixmap("://trash.png");
    removeButton->setIcon(QIcon(trashIconPixmap));
    removeButton->setIconSize(QSize(24, 24));
    removeButton->setFixedSize(24, 24);
    removeButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    removeButton->setProperty("item", QVariant::fromValue(this));
    connect(removeButton, &QToolButton::clicked, this, &VertexListItem::remove);
    auto valueLabel = new QLineEdit();
    valueLabel->setReadOnly(true);
    valueLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    valueLabel->setContentsMargins(0, 0, 0, 1);
    valueLabel->setText(" " + QString::number(value));
    valueLabel->setStyleSheet("QLineEdit {"
                              "font: 20px;"
                              "}");
    mainHBoxLayout->addWidget(valueLabel, 10);
    mainHBoxLayout->addWidget(removeButton, 1, Qt::AlignRight);
    valueLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    removeButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->setMaximumHeight(24);
    this->setMinimumWidth(50);
    this->value = value;
}

int VertexList::itemsCount() {
    return mainList->count();
}

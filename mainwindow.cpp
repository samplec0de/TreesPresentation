//
// Created by Андрей Москалёв on 2019-10-14.
//

#include "mainwindow.h"

QString zoomStyleSheet = "QSlider::groove:horizontal {"
                         "background-color: black;"
                         "border: 0px solid #424242;"
                         "height: 10px;"
                         "border-radius: 4px;"
                         "}"
                         ""
                         "QSlider::handle:horizontal {"
                         "background-color: rgb(200, 200, 200);"
                         "border: 2px solid rgb(100, 100, 100);"
                         "width: 16px;"
                         "height: 20px;"
                         "line-height: 20px;"
                         "margin-top: -5px;"
                         "margin-bottom: -5px;"
                         "border-radius: 10px;"
                         "}";

void MainWindow::commandChanged(const QString &s) {
    for (auto item : vertex->getItems()) {
        if (item == nullptr) continue;
        if (curTreeType == AVL) {
            avl->remove(item->value);
        }
        else if (curTreeType == Splay) {
            splay->remove(item->value);
        }
        else {
            rb->remove(item->value);
        }
    }
    if (s == "Splay") {
        curTreeType = Splay;
    }
    else if (s == "АВЛ") {
        curTreeType = AVL;
    }
    else {
        curTreeType = RB;
    }
    for (auto item : vertex->getItems()) {
        if (item == nullptr) continue;
        if (curTreeType == AVL) {
            avl->insert(item->value);
        }
        else if (curTreeType == Splay) {
            splay->insert(item->value);
        }
        else {
            rb->insert(item->value);
        }
    }
    drawTree();
}

void MainWindow::zoomer(int val) {
    double delta = val / 30.0;
    view->scale(1 / scaleCF, 1 / scaleCF);
    view->scale(delta, delta);
    scaleCF = delta;
}

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent) {
    scaleCF = 1;
    this->setMinimumSize(1000, 348);
    this->setWindowTitle("Визуализация деревьев");
    auto central = new QWidget;
    this->setCentralWidget(central);
    grid = new QGridLayout(central);
    scene = new QGraphicsScene;
    view = new QGraphicsView(scene);
    view->show();
    grid->addWidget(view, 1, 1, 20, 30);
    zoom = new QSlider(Qt::Horizontal);
    connect(zoom, &QSlider::valueChanged, this, &MainWindow::zoomer);
    zoom->setMinimum(10);
    zoom->setMaximum(110);
    zoom->setValue(60);
    zoom->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    zoom->setStyleSheet(zoomStyleSheet);
    auto zoomPlus = new QLabel("+");
    auto zoomMinus = new QLabel("-");
    zoomPlus->setStyleSheet("QLabel {"
                            "font: 24px;"
                            "}");
    zoomMinus->setStyleSheet("QLabel {"
                             "font: 30px;"
                             "}");
    grid->addWidget(zoomPlus, 20, 38, 1, 1, Qt::AlignLeft | Qt::AlignHCenter);
    grid->addWidget(zoom, 20, 32, 1, 6);
    grid->addWidget(zoomMinus, 20, 31, 1, 1, Qt::AlignRight | Qt::AlignHCenter);
    auto settingsLabel = new QLabel("Настройки");
    grid->addWidget(settingsLabel, 1, 31, 1, 8, Qt::AlignLeft);
    settingsLabel->setStyleSheet("QLabel {"
                                 "font: bold 35px;"
                                 "width: 100%"
                                 "}");
//    QStringList treeTypes = { "АВЛ", "Splay"};
    QStringList treeTypes = { "АВЛ", "Splay", "Красно-чёрное"};
    auto dropDown = new QComboBox();
    dropDown->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    dropDown->setMinimumHeight(30);
    dropDown->addItems(treeTypes);
    dropDown->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    connect(dropDown, &QComboBox::currentTextChanged, this, &MainWindow::commandChanged);
    grid->addWidget(dropDown, 3 , 32, 1, 7);
    auto presentType = new QLabel("Тип:");
    presentType->setStyleSheet("QLabel {"
                               "font: 18px;"
                               "}");
    grid->addWidget(presentType, 3 , 31, 1, 1, Qt::AlignHCenter);
    insertLineEdit = new QLineEdit;
    QValidator * validator = new QRegExpValidator(QRegExp("[-0-9 ]*"), this);
    insertLineEdit->setValidator(validator);
    insertLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    insertLineEdit->setPlaceholderText("Значения через пробел");
    insertLineEdit->setStyleSheet("QLineEdit {"
                                  "background-color: rgb(53, 53, 53);"
                                  "font: 20px;"
                                  "}");
    auto addButton = new QToolButton;
    connect(addButton, &QToolButton::clicked, this, &MainWindow::vertexListAdd);
    addButton->setText("+");
    addButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    addButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    addButton->setStyleSheet("QToolButton {"
                             "font: bold 35px;"
                             "color: white;"
                             "background-color: green;"
                             "border-radius: 5px;"
                             "}"
                             "QToolButton:hover {"
                             "font: bold 40px;"
                             "color: white;"
                             "background-color: rgb(34, 139, 34);"
                             "border-radius: 5px;"
                             "}"
                             "QToolButton:pressed {"
                             "font: bold 40px;"
                             "color: white;"
                             "background-color: rgb(43, 181, 43);"
                             "border-radius: 5px;"
                             "}");

    auto removeButton = new QToolButton;
    connect(removeButton, &QToolButton::clicked, this, &MainWindow::vertexListRemove);
    removeButton->setText("-");
    removeButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    removeButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    removeButton->setStyleSheet("QToolButton {"
                             "font: bold 35px;"
                             "color: white;"
                             "background-color: rgb(250, 10, 10);"
                             "border-radius: 5px;"
                             "}"
                             "QToolButton:hover {"
                             "font: bold 40px;"
                             "color: white;"
                             "background-color: rgb(240, 10, 10);"
                             "border-radius: 5px;"
                             "}"
                             "QToolButton:pressed {"
                             "font: bold 40px;"
                             "color: white;"
                             "background-color: rgb(250, 10, 10);"
                             "border-radius: 5px;"
                             "}");
    vertex = new VertexList;
    connect(vertex, &VertexList::removedItem, this, &MainWindow::vertexRemoved);
    grid->addWidget(insertLineEdit, 4 , 31, 2, 6);
    grid->addWidget(addButton, 4 , 37, 1, 2);
    grid->addWidget(removeButton, 5 , 37, 1, 2);
    grid->addWidget(vertex, 6 , 31, 1, 8);
    auto clearAllPushButton = new QPushButton;
    connect(clearAllPushButton, &QPushButton::clicked, this, &MainWindow::clearAll);
    clearAllPushButton->setText("Очистить холст");
    clearAllPushButton->setStyleSheet("QPushButton {"
                                      "background-color: rgba(250, 10, 10, 0.5);"
                                      "font: 20px;"
                                      "}");
    grid->addWidget(clearAllPushButton, 7 , 31, 1, 8);
    auto elementsCntLegendLabel = new QLabel("Элементов: ");
    elementsCntLegendLabel->setStyleSheet("QLabel {"
                                          "font: 20px;"
                                          "}");
    grid->addWidget(elementsCntLegendLabel, 19 , 32, 1, 4, Qt::AlignRight);
    elementsCountLabel = new QLabel("0");
    elementsCountLabel->setStyleSheet("QLabel {"
                                      "font: bold 22px;"
                                      "}");
    grid->addWidget(elementsCountLabel, 19 , 36, 1, 1, Qt::AlignLeft);
//    qDebug() << grid->columnCount();
}

void MainWindow::drawVertex(int sizeX, int key, int x, int y, bool red) {
    int sizeY = 24;
    auto elipse = scene->addEllipse(x, y, sizeX, sizeY);
    auto text = scene->addText("", QFont("Times 14"));
    text->setHtml("<center><p style=\"color:" + (red ? QString::fromStdString("red") : QString::fromStdString("black")) + ";\">" + QString::number(key) + "</p></center>");
    text->setTextWidth(sizeX);
    text->setPos(x, y);
}

void MainWindow::drawChildrens(int sizeX, Node * p, int px, int py) {
    if (p->left != nullptr) {
        int treeSz = p->left->treeSize();
        int nx = px - 64 * treeSz;
        int ny = py + 64;
        drawVertex(sizeX, p->left->key, nx, ny, p->color);
        scene->addLine(px + sizeX / 2, py + 24, nx + sizeX / 2, ny);
        drawChildrens(sizeX, p->left, nx, ny);
    }
    if (p->right != nullptr) {
        int treeSz = p->right->treeSize();
        int nx = px + 64 * treeSz;
        int ny = py + 64;
        scene->addLine(px + sizeX / 2, py + 24, nx + sizeX / 2, ny);
        drawVertex(sizeX, p->right->key, nx, ny, p->color);
        drawChildrens(sizeX, p->right, nx, ny);
    }
}

void MainWindow::drawTree() {
    scene->clear();
    scene->deleteLater();
    scene = new QGraphicsScene;
    view->setScene(scene);
    Node * start = nullptr;
    if (curTreeType == AVL) {
        start = avl->root;
    }
    else if (curTreeType == Splay) {
        start = splay->root;
    }
    else {
        start = rb->root;
    }
    if (start == nullptr) {
        return;
    }
    int mxSize = std::max(24, start->maxLen() * 15);
    drawVertex(mxSize, start->key, 100, 20, start->color);
    drawChildrens(mxSize, start, 100, 20);
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::vertexListAdd() {
    std::string content = insertLineEdit->text().replace("  ", " ").toStdString(), s = "";
    std::stringstream ss(content);
    while (ss >> s) {
        int len = s.size();
        if (s[0] == '-') {
            --len;
        }
        if (len > 15 || stoll(s) > INT_MAX) {
            QMessageBox msgBox;
            msgBox.setText("Ключ " + QString::fromStdString(s) + " выходит за границы типа INT");
            msgBox.exec();
            continue;
        }
        int64_t key = stoll(s);
        if (vertex->add(key)) {
            if (curTreeType == AVL) {
                avl->insert(key);
            }
            else if (curTreeType == Splay) {
                splay->insert(key);
            }
            else {
                rb->insert(key);
            }
        }
    }
    elementsCountLabel->setText(QString::number(vertex->itemsCount()));
    drawTree();
}

void MainWindow::vertexListRemove() {
    std::string content = insertLineEdit->text().replace("  ", " ").toStdString(), s = "";
    std::stringstream ss(content);
    while (ss >> s) {
        int len = s.size();
        if (s[0] == '-') {
            --len;
        }
        if (len > 15 || stoll(s) > INT_MAX) {
            QMessageBox msgBox;
            msgBox.setText("Ключ " + QString::fromStdString(s) + " выходит за границы типа INT");
            msgBox.exec();
            continue;
        }
        int64_t key = stoll(s);
        if (vertex->remove(key)) {
            if (curTreeType == AVL) {
                avl->remove(key);
            }
            else if (curTreeType == Splay) {
                splay->remove(key);
            }
            else {
                rb->remove(key);
            }
        }
    }
    elementsCountLabel->setText(QString::number(vertex->itemsCount()));
    drawTree();
}

void MainWindow::vertexRemoved(int key) {
    elementsCountLabel->setText(QString::number(vertex->itemsCount()));
    if (curTreeType == AVL) {
        avl->remove(key);
    }
    else if (curTreeType == Splay) {
        splay->remove(key);
    }
    else {
        rb->remove(key);
    }
    drawTree();
}

void MainWindow::clearAll() {
    for (auto item : vertex->getItems()) {
        if (curTreeType == AVL) {
            avl->remove(item->value);
        }
        else if (curTreeType == Splay) {
            splay->remove(item->value);
        }
        else {
            rb->remove(item->value);
        }
    }
    while (vertex->mainList->count()) {
        vertex->mainList->removeItemWidget(vertex->mainList->takeItem(0));
    }
    elementsCountLabel->setText(QString::number(vertex->itemsCount()));
    drawTree();
}

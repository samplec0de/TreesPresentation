//
// Created by Андрей Москалёв on 2019-10-14.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QWheelEvent>
#include <QGridLayout>
#include <QToolButton>
#include <QSlider>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <cmath>
#include <QRegExpValidator>
#include <QValidator>
#include <string>
#include <sstream>
#include <QGraphicsTextItem>
#include <QMessageBox>
#include <QPushButton>
#include "VertexList.h"
#include "AVLTree.h"
#include "SplayTree.h"
#include "RBTree.h"

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget * parent = nullptr);
    ~MainWindow() override = default;
    void commandChanged(const QString &s);
    void zoomer(int val);
    AVLTree * avl = new AVLTree;
    SplayTree * splay = new SplayTree;
    RBTree * rb = new RBTree;
    enum Tree {AVL, Splay, RB};
    Tree curTreeType = AVL;
    void clearAll();
private:
    QGraphicsView * view{};
    QGridLayout * grid{};
    double scaleCF;
    QLineEdit * insertLineEdit;
    VertexList * vertex;
    QLabel * elementsCountLabel;
    QSlider * zoom;
    void vertexListAdd();
    void vertexListRemove();
    void vertexRemoved(int key);
    void drawVertex(int sizeX, int key, int x, int y, bool red = false);
    void drawTree();
    void drawChildrens(int sizeX, Node * p, int px, int py);
    QGraphicsScene * scene;
};

#endif // MAINWINDOW_H

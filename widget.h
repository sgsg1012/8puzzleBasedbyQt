#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "fun.h"
#include "node.h"
#include <QButtonGroup>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void paintEvent(QPaintEvent * pe);
    void paintTree();
    void paintRoad();
    node *init=nullptr;
    node *last=nullptr;
    Fun * searchTool=nullptr;
    void search(int algo,int h=2);
    void createTool();
    void algoSelect(QButtonGroup * a);
    int maxNum=2000;

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H

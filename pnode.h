#ifndef PNODE_H
#define PNODE_H

#include <QWidget>
#include <QString>

namespace Ui {
class Pnode;
}

class Pnode : public QWidget
{
    Q_OBJECT

public:
    explicit Pnode(QString s,QWidget *parent = nullptr);
    ~Pnode();
    void paintEvent(QPaintEvent * e);
    QString str;

private:
    Ui::Pnode *ui;
};

#endif // PNODE_H

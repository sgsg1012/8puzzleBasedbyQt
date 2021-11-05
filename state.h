#ifndef STATE_H
#define STATE_H

#include <QWidget>
#include <QString>

namespace Ui {
class State;
}

class State : public QWidget
{
    Q_OBJECT

public:
    explicit State(QWidget *parent = nullptr,QString s="12345678*");
    ~State();
    void paintEvent(QPaintEvent * e);
    QString str="12345678*";

private:
    Ui::State *ui;

};

#endif // STATE_H

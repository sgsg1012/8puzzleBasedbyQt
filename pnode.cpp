#include "pnode.h"
#include "ui_pnode.h"
#include <QPainter>
#include <QBrush>

Pnode::Pnode(QString s,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pnode)
{
    ui->setupUi(this);
    this->str=s;
}
void Pnode::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    int width=this->frameGeometry().width();
    int height=this->frameGeometry().height();
    QBrush brush(Qt::green);
    painter.setBrush(brush);
    painter.drawRect(0,0,width-1,height-1);
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            painter.setFont(QFont("Open Sans Semibold",10));
            painter.drawText(width/6+width/3*j-5,width/6+width/3*i+6,(QString)str[i*3+j]);
        }
    }
}

Pnode::~Pnode()
{
    delete ui;
}

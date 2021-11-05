#include "state.h"
#include "ui_state.h"
#include <QPainter>
State::State(QWidget *parent,QString s) :
    QWidget(parent),
    ui(new Ui::State)
{
    ui->setupUi(this);
    this->str=s;
}
void State::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    int width=this->frameGeometry().width();
    int height=this->frameGeometry().height();
    painter.drawRect(0,0,width-1,height-1);
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            painter.drawEllipse(QPoint(width/6+width/3*i,width/6+width/3*j+5),width/6-2,width/6-2);
            painter.setFont(QFont("Open Sans Semibold",30));
            painter.drawText(width/6+width/3*j-13,width/6+width/3*i+20,(QString)str[i*3+j]);
        }
    }
//    painter.drawEllipse(QPoint(50,50),50,50);
//    painter.drawText(QPoint(10,10),str);


}
State::~State()
{
    delete ui;
}

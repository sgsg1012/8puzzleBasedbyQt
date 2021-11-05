#include "widget.h"
#include "ui_widget.h"
#include "node.h"
#include "bfs.h"
#include "dfs.h"
#include "aStar.h"
#include <QPixmap>
#include <QString>
#include <QPainter>
#include <QPaintEvent>
#include "pnode.h"
#include <QSize>
#include <QDebug>
#include <QMessageBox>
#include <QTime>
#include <QButtonGroup>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->state->str="23415*768";
    ui->goal->str="12345678*";
//    createTool();


//    clock_t starttime = clock();
//    BFS b("64785*321", "12345678*");
//    cout <<"bfs  :"<< b.algo() << endl;
//    b.printRoad();
//    cout<<"--------------------------"<<endl;
//    b.freeMemory();
//    DFS d("64785*321", "12345678*");
//    cout <<"dfs  :"<< d.algo() << endl;
//    d.printRoad();
//    cout<<"--------------------------"<<endl;
//    d.freeMemory();
//    AStar a("64785*321", "12345678*");
//    cout <<"astar  :"<< a.algo(2) << endl;
//    a.printRoad();
//    cout<<"--------------------------"<<endl;
//    a.freeMemory();
//    clock_t endtime = clock();
//    cout << (double)(endtime - starttime) / CLOCKS_PER_SEC << endl;
    QPixmap pixmap;
    pixmap.load(":/img/arrow.jfif");
    ui->arrow->setPixmap(pixmap);
    ui->arrow->setScaledContents(true);
    ui->label1->setFont(QFont("Open Sans Semibold",20));
    ui->label2->setFont(QFont("Open Sans Semibold",20));
    connect(ui->printRoad,&QPushButton::clicked,[=]()
    {
        this->paintRoad();
    });
    connect(ui->printTree,&QPushButton::clicked,[=]()
    {
        this->paintTree();
    });

    connect(ui->stateChange,&QPushButton::clicked,[=](){
        ui->state->str=ui->stateInput->text();
        this->update();
    });
    connect(ui->goalChange,&QPushButton::clicked,[=](){
        ui->goal->str=ui->goalInput->text();
        this->update();
    });
    connect(ui->goBack,&QPushButton::clicked,[=](){
        ui->state->str="23415*768";
        ui->goal->str="12345678*";
        this->update();
    });
    ui->stackedWidget->setCurrentIndex(0);

    QButtonGroup * algoGroup = new QButtonGroup(this);
    algoGroup->addButton(ui->bfs,0);
    algoGroup->addButton(ui->dfs,1);
    algoGroup->addButton(ui->astar,2);
    algoGroup->addButton(ui->bestFirst,3);
    ui->bfs->setChecked(true);

    QButtonGroup * ahGroup = new QButtonGroup(this);
    ahGroup->addButton(ui->ah1,1);
    ahGroup->addButton(ui->ah2,2);
    ahGroup->addButton(ui->ah3,3);
    ui->ah2->setChecked(true);

    QButtonGroup * bhGroup = new QButtonGroup(this);
    bhGroup->addButton(ui->bh1,1);
    bhGroup->addButton(ui->bh2,2);
    bhGroup->addButton(ui->bh3,3);
    ui->bh3->setChecked(true);

    connect(ui->search,&QPushButton::clicked,[=]()
    {
        int algo=algoGroup->checkedId();
        int h=2;
        if(algo==2)
        {
            h=ahGroup->checkedId();
        }
        else if(algo==3)
        {
            h=-1*bhGroup->checkedId();
        }
        QDialog * dlg = new QDialog(this);
        dlg->setFixedSize(QSize(200,100));
        QLabel * label=new QLabel(dlg);
        label->setText("搜索结束");
        label->show();
        dlg->show();
        dlg->setAttribute(Qt::WA_DeleteOnClose);
        QTime time;
        time.start();
        this->search(algo,h);
        QString str=QString::number(time.elapsed()/1000.0, 'f', 3)+"s";
        ui->time->setText(str);

    });
    connect(ui->bfs,&QRadioButton::clicked,this,[=](){
        this->algoSelect(algoGroup);
    });
    connect(ui->dfs,&QRadioButton::clicked,this,[=](){
        this->algoSelect(algoGroup);
    });
    connect(ui->astar,&QRadioButton::clicked,this,[=](){
        this->algoSelect(algoGroup);
    });
    connect(ui->bestFirst,&QRadioButton::clicked,this,[=](){
        this->algoSelect(algoGroup);
    });
    connect(ui->ah3 ,&QRadioButton::clicked,this,[=](){
        QMessageBox::information(this,"info","注意：此启发式函数不能保证最优解");
    });
    connect(ui->bNumChange,&QPushButton::clicked,[=](){
       QString str=ui->bnum->text();
       if(str!="") maxNum=str.toInt();
       else maxNum=2000;
       QMessageBox::information(this,"info","注意：节点数过大会导致程序崩溃，默认节点数为2000");
    });
    connect(ui->dNumChange,&QPushButton::clicked,[=](){
       QString str=ui->dnum->text();
       if(str!="") maxNum=str.toInt();
       else maxNum=2000;
       QMessageBox::information(this,"info","注意：节点数过大会导致程序崩溃");
    });
    connect(ui->algorithmAna,&QPushButton::clicked,[=](){
       int algo= algoGroup->checkedId();
       if(algo==0)
       {
           QMessageBox::information(this,"info","bfs速度很快，但是只有在路径代价相同时才能保证最优解，有很大局限性，并且搜索是盲目的，搜索树较为庞大，节点数往往很多");
       }
       else if(algo==1)
       {
            QMessageBox::information(this,"info","dfs速度很快，但是不能保证最优解，并且搜索是盲目的，搜索树较为庞大，节点数往往很多");
       }
       else if(algo==2)
       {
            QMessageBox::information(this,"info","astar算法可以降低搜索次数，搜索树的深度和广度大大降低，并且可以保证最优解，缺点是运行速度慢，时间复杂度高，如果问题无解会耗费大量时间");
       }
       else if(algo==3)
       {
            QMessageBox::information(this,"info","最佳优先算法可以进一步降低搜索次数，搜索树的深度和广度大大降低，但是不可以保证最优解，缺点是运行速度慢（比astar算法快），时间复杂度高，如果问题无解会耗费大量时间");
       }
    });




}
void Widget::algoSelect(QButtonGroup * group)
{
    ui->stackedWidget->setCurrentIndex(group->checkedId());
    this->maxNum=2000;
    this->init=nullptr;
    this->last=nullptr;
}
void Widget::createTool()
{
//    this->searchTool=new AStar(ui->state->str.toStdString(), ui->goal->str.toStdString());
}
void Widget::search(int algo,int h)
{
//    searchTool->freeMemory();
//    searchTool->state=ui->state->str.toStdString();
//    searchTool->end=ui->goal->str.toStdString();
//    int steps=((AStar *)searchTool)->algo(2);
//    ui->steps->setText(QString::number(steps));
//    this->init=searchTool->init;
//    this->last=searchTool->last;
    this->init=nullptr;
    this->last=nullptr;
    if(algo==0)
    {
        BFS b(ui->state->str.toStdString(), ui->goal->str.toStdString());
        int steps=b.algo();
        ui->steps->setText(QString::number(steps));
        if(steps==-1)
        {
            QMessageBox::critical(this,"错误","此状态无解");
        }
        else{
            this->init=b.init;
            this->last=b.last;
        }
    }
    else if(algo==1)
    {
        DFS d(ui->state->str.toStdString(), ui->goal->str.toStdString());
        int steps=d.algo();
        ui->steps->setText(QString::number(steps));
        if(steps==-1)
        {
            QMessageBox::critical(this,"错误","此状态无解");
        }
        else{
            this->init=d.init;
            this->last=d.last;
        }
    }
    else if(algo==2)
    {
        BFS b(ui->state->str.toStdString(), ui->goal->str.toStdString());
        if(b.algo()==-1)
        {
            QMessageBox::critical(this,"错误","此状态无解");
            return ;
        }
        AStar a(ui->state->str.toStdString(), ui->goal->str.toStdString());
        int steps=a.algo(h);
        ui->steps->setText(QString::number(steps));
        this->init=a.init;
        this->last=a.last;
    }
    else if(algo==3)
    {
        BFS b(ui->state->str.toStdString(), ui->goal->str.toStdString());
        if(b.algo()==-1)
        {
            QMessageBox::critical(this,"错误","此状态无解");
            return ;
        }
        AStar a(ui->state->str.toStdString(), ui->goal->str.toStdString());
        int steps=a.algo(h);
        ui->steps->setText(QString::number(steps));
        this->init=a.init;
        this->last=a.last;
    }
}
void Widget::paintRoad()
{
    ui->treeWidget->clear();
    if(last==nullptr)
    {
        QMessageBox::critical(this,"critical","还未开始搜索");
        return ;
    }
    node * tem=last;
    vector<node *> seq;
    int num=1;
    while(tem!=nullptr)
    {
        seq.push_back(tem);
        tem=tem->father;
        num++;
        if(num>maxNum)
        {
            QMessageBox::information(this,"info","节点过多，中断树的输出");
            break;
        }
    }
    tem=seq[seq.size()-1];
//    ui->treeWidget->setHeaderLabels(QStringList()<<"节点");
    Pnode * p=new Pnode(QString::fromStdString(tem->s),this);
    QTreeWidgetItem *root=new QTreeWidgetItem(0);
    ui->treeWidget->addTopLevelItem(root);
    ui->treeWidget->setItemWidget(root,0,p);
    QTreeWidgetItem * ntem=root;
    for(int i=seq.size()-2;i>=0;i--)
    {
        QTreeWidgetItem * a=new QTreeWidgetItem(0);
        Pnode * p=new Pnode(QString::fromStdString(seq[i]->s),this);
        ntem->addChild(a);
        ui->treeWidget->setItemWidget(a,0,p);
        ntem=a;
    }
    ui->num->setText(QString::number(seq.size()));
//    this->update();
}
void Widget::paintTree()
{
    ui->treeWidget->clear();
    if(init==nullptr)
    {
        QMessageBox::critical(this,"critical","还未开始搜索");
        return ;
    }
    unordered_map<string, int> d;
    node * tem=init;
//    cout<<tem->son.size()<<endl;
//    ui->treeWidget->setHeaderLabels(QStringList()<<"节点");
    Pnode * p=new Pnode(QString::fromStdString(tem->s),this);
    QTreeWidgetItem *root=new QTreeWidgetItem(0);
    ui->treeWidget->addTopLevelItem(root);
    ui->treeWidget->setItemWidget(root,0,p);
    QTreeWidgetItem * ntem=root;
    int num=1;
    while(tem!=nullptr)
    {
        bool tag=false;
        for(int i=0;i<tem->son.size();i++)
        {
            node * a=tem->son[i];
            if(!d.count(a->s))
            {
                tag=true;
                d[a->s]=1;
                tem=a;
                Pnode * p=new Pnode(QString::fromStdString(tem->s),this);
                QTreeWidgetItem *b=new QTreeWidgetItem(0);
                ntem->addChild(b);
                ui->treeWidget->setItemWidget(b,0,p);
                ntem=b;
                num++;
                break;
            }
        }
        if(!tag)
        {
            tem=tem->father;
            ntem=ntem->parent();
        }
        if(num>maxNum)
        {
            QMessageBox::information(this,"info","节点过多，中断树的输出");
            break;
        }
    }
    ui->num->setText(QString::number(num));
//    this->update();
}
void Widget::paintEvent(QPaintEvent *e)
{
//    QPainter painter(this);
//    painter.drawEllipse(QPoint(0,0),50,50);
}

Widget::~Widget()
{
    delete ui;
}

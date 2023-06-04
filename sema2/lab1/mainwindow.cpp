#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPainter>
#include<QMouseEvent>
#include<QMessageBox>
#include <QString>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter (this);

    QLineF line1(h1,h2);
    QLineF line2(h1,h2);
    line2.setAngle(line1.angle() + 15);

    QLineF line4(h1,h2);
    line4.setAngle(line1.angle() - 15);
    QLineF line3(line2.p2(),line4.p2());
    QLineF line5(h1,h2);
    line5.setAngle(line1.angle() + 90);

    QPointF a1=line4.p2()-line4.p1();
    QPointF a2=line2.p2()-line2.p1();
    QPointF a3=line3.p2()-line3.p1();
    QPointF a4=line5.p2()-line5.p1();

    if (!(h1.isNull()&&!(h2.isNull()))){
        painter.drawLine(line2);
        painter.drawLine(line3);
        painter.drawLine(line4);

        QRect screen =contentsRect();
        QPen pen1(QColor(255,255,0,85));
        QPen pen2(Qt::black);

    }
    if((!(h3.isNull()))&&(!(h1.isNull())&&!(h2.isNull()))){
        painter.drawEllipse(h3,4,4);

        QPointF b1=h3-line4.p1();
        QPointF b2=h3-line2.p1();
        QPointF b3=h3-line3.p1();
        QPointF b4=h3-line5.p1();

        int sign1=a1.x()*b1.y()-a1.y()*b1.x();
        int sign2=a2.x()*b2.y()-a2.y()*b2.x();
        int sign3=a3.x()*b3.y()-a3.y()*b3.x();
        int sign4=a4.x()*b4.y()-a4.y()*b4.x();
        QString message=QString();

        if(sign1<=0 && sign2>=0 && sign3>=0 ){
            message+="see";
        }
        if(sign1>=0 && sign2>=0 && sign3>=0 && sign4>=0 ){
            message+="not see right";
        }
        if(sign1<=0 && sign2<=0 && sign3>=0 && sign4>=0 ){
            message+="not see left";
        }
        if(sign3<=0){
            message+="not see top";
        }
        if (sign4<=0){
            message+="not see back";

        }
        QMessageBox::information(this,"lab1",message);
        MainWindow::close();
    }

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(!(Qt::ControlModifier& event->modifiers())&&(Qt::LeftButton & event->buttons() ))
        h1=event->pos();
    if((Qt::RightButton & event->buttons() ))
        h2=event->pos();
    if((Qt::ControlModifier& event->modifiers())&&(Qt::LeftButton & event->buttons() ))
        h3=event->pos();
    repaint();

}


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QVector>
#include <QPoint>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
bool ContainsCircle(Circle c1,Circle c2){
    QPoint l1=c2.center-c1.center;
    return (QPoint::dotProduct(l1,l1)<=(c2.radius+c1.radius)*(c2.radius+c1.radius))?true:false;
}
bool Point(Circle q, QPoint p)
{
    QPoint dp=q.center-p;
    return (QPoint::dotProduct(dp,dp)<=q.radius*q.radius);
}
bool IntersectRects (QRect r1,QRect r2){
    QRect inter(r2.intersected (r1));
    if (((r1.width()*r1.height())-(inter.width()*inter.height()))<(r1.width()*r1.height())*0.6){
        return true;
    }
    return false;
}
bool ContainsRect11 (Circle l,QRect r){
    return Point(l,r.topLeft())&& Point(l,r.bottomRight());
}
bool ContainsRect12 (Circle l,QRect r){
    return r.marginsAdded(QMargins(l.radius,l.radius,l.radius,l.radius)).contains(l.center);
}
bool ContainsRect13 (Circle l,QRect r){
    return Point(l,r.topLeft())|| Point(l,r.bottomRight())||Point(l,r.bottomLeft())||Point(l,r.topRight()) ;
}
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter (this);
    QImage grass16("C:/Users/HP/OneDrive/grass16.JPG");
    QBrush brush;
    brush.setTextureImage(grass16);
    painter.setBrush(brush);
    painter.drawRect(contentsRect());
    QBrush brush1 (QColor(5,20,100));
    painter.setBrush(brush1);
    painter.drawRect(pool);
    QBrush brush2(QColor(100,10,5));
    painter.setBrush(brush2);
    for (int i=0;i<q.size();i++){
        painter.drawEllipse(q[i].center,q[i].radius,q[i].radius);
    }
    for (QRect r:clumb){
        painter.drawRect(r);
    }
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    bool sovpad=false;
    QPoint dot1=event->pos();
    if (event->modifiers() & Qt::ControlModifier){
        qDebug("Ctrl");
        Circle h={dot1,20};
        if (pool.contains(event->pos())){
            sovpad=true;
        }
        for(int j=0;j<q.size();j++){
            if(ContainsCircle(q[j],h)){
                sovpad=true;
            }
        }
        for(int j=0;j<clumb.size();j++){
            if(ContainsRect11(h,clumb[j])){
                sovpad=true;
            }
        }
        for(int j=0;j<clumb.size();j++){
            if(ContainsRect13(h,clumb[j])){
                sovpad=true;
            }
        }
        if (!sovpad){
            q.append(h);
        }
    }

    if (event->modifiers()&Qt::AltModifier){
        qDebug("Click");

        //QRect r2=QRect (event->pos(),QSize(30,30));
        QRect r2= QRect(QPoint(dot1.x(),dot1.y()),pool.size()*0.2);
        if (pool.contains(r2)){
            sovpad=true;
        }
        for(int j=0;j<q.size();j++){
            if(ContainsRect11(q[j],r2))
                break;
            if(ContainsRect12(q[j],r2))
                sovpad=true;

        }
        for (int j=0;j<clumb.size();j++){
            if(IntersectRects(r2,clumb[j]))
                sovpad=true;

        }
        if(!sovpad){
            clumb.append(r2);
        }
    }
    repaint();
}




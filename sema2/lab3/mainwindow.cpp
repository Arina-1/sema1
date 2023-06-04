#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <math.h>

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

    for (int i = 0; i<contentsRect().width(); i++){
        for (int j = 0; j<contentsRect().height(); j++){
            painter.drawRect(cell.translated(h*i, h*j));
        }
    }

    painter.drawEllipse(derevo.cen, derevo.radius, derevo.radius);
    painter.setBrush(QColor(128, 128, 100, 200));
    painter.drawEllipse(ant, 5, 5);
    painter.drawEllipse(muha, 5, 5);

    for (int i = 0; i<repeat_point.size()-1; i++){
        QPen pen (Qt::blue, 3);
        painter.setPen(pen);
        painter.drawLine(repeat_point[i], repeat_point[i+1]);

    }

}
//по клику
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (k == 0)
        derevo = {event->pos(), 60};
    if (k == 1)
      ant = on_net(event->pos());

    if (k >= 2){
        repeat_point.clear();
        muha = on_net(event->pos());

        QPoint ant_newstep = ant;
        while (ant_newstep != muha){
            newp[0] = ant_newstep - QPoint (0, h);//вверх
            newp[1] = ant_newstep + QPoint (0, h);//вниз
            newp[2] = ant_newstep - QPoint (h, 0);//лево
            newp[3] = ant_newstep + QPoint (h, 0);//право
            repeat_point.append(ant_newstep);
            int min = 100*100;
            QPoint move_ok;

            for (int i = 0; i<4; i++){
                for (int j = 0; j< repeat_point.size(); j++){
                    if (in_circle(newp[i], derevo) && newp[i] != repeat_point[j]){
                     int dlina = dlina0(muha, newp[i]);
                        if (dlina < min){
                            min = dlina;
                            move_ok = newp[i];
                        }
                    }
                }
            }
            qDebug()<<move_ok;//иногда
            ant_newstep = move_ok;

       }
        repeat_point.append(muha);
    }
    k++;
    repaint();
}

//надо по радиусу

QPoint MainWindow::on_net(QPoint p)//на сетке
{
    for (int i= 0; i<contentsRect().width();i++){
        for (int j = 0; j<contentsRect().height(); j++){
            QRect translated_k = cell.translated(h*i, h*j);
            pt_k.append(translated_k.topLeft());
        }
    }
    int min = 100*100;
    QPoint real_p;
    for (int i = 0; i<pt_k.size(); i++){
        QPoint point = pt_k[i] - p;
        int dlin = dlina0(pt_k[i], p);
        if (dlin < min){
            min = dlin;
            real_p = pt_k[i];
        }
    }
    return real_p;
}

bool MainWindow::in_circle(QPoint p, Circle c)
{
    if (dlina0(c.cen, p) <= c.radius)
        return false;
    return true;
}

int MainWindow::dlina0(QPoint l1, QPoint l2)
{
    QPoint p_dlin = l1 - l2;
    return sqrt(pow(p_dlin.x(),2)+pow(p_dlin.y(),2));
}

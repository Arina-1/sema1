#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    struct Circle
    {
       QPoint cen;
       int radius;
    };
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    QPoint on_net (QPoint p);
    bool in_circle (QPoint p, Circle c);
    int dlina0 (QPoint l1, QPoint l2);
private:
    Ui::MainWindow *ui;
    int h = 30;
    int k = 0;
    QRect cell = QRect (QPoint (0,0), QSize(h, h));
    QPoint ant, muha;
    Circle derevo;
    QVector <QPoint> pt_k, repeat_point;
    QPoint newp[4];


};
#endif // MAINWINDOW_H

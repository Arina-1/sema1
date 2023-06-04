        #ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
struct Circle{
    QPoint center;
    int radius;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::MainWindow *ui;
    int count =6;
    QRect r1,pool=QRect(QPoint(170,170),QSize(300,200));
    QVector <QRect> clumb;
    QVector <Circle> q;

};
#endif // MAINWINDOW_H

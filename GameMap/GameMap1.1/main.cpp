#include "figure.h"
#include "ui_figure.h"
#include "gamemap.h"
#include "ui_gamemap.h"
#include "taskbuff.h"
#include "ui_taskbuff.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QString>
#include <QRect>
#include "utils.cpp"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    MainWindow *pwindow = new MainWindow("1");
    pwindow->showFullScreen();
    qDebug()<<pwindow->height()<<" "<<pwindow->width();
    pwindow->show();
    //pwindow->pgamemap->pfigure->embed_image(":/images/images/player_lion.jpg");
    pwindow->pgamemap->pfigure->show();
    //pwindow->ptaskbuff_board->show();


    //画格子工具，可注释掉
    GridWidget gridWidget(pwindow);
    gridWidget.resize(1280, 720);
    gridWidget.show();


    return a.exec();
}

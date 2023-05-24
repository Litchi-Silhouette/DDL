#include "init.cpp"
#include "utils.cpp"
#include "obstacle.cpp"


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    MainWindow *pwindow = new MainWindow("1");

    qDebug()<<"window size "<<pwindow->height()<<" "<<pwindow->width();
    pwindow->show();
    //pwindow->pgamemap->pfigure->show();


    //画格子工具，可注释掉
   /* GridWidget gridWidget(pwindow);
    gridWidget.resize(MainWindow::WIDTH, MainWindow::HEIGHT);
    gridWidget.show();*/


    return a.exec();
}

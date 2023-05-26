#include "init.cpp"
#include "obstacle.cpp"


Game LevelWindow::gamePages;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    MainWindow *pwindow = new MainWindow();

    qDebug()<<"window size "<<pwindow->height()<<" "<<pwindow->width();
    pwindow->show();
    //pwindow->pgamemap->pfigure->show();


    //画格子工具，可注释掉
   /* GridWidget gridWidget(pwindow);
    gridWidget.resize(MainWindow::WIDTH, MainWindow::HEIGHT);
    gridWidget.show();*/


    return a.exec();
}
